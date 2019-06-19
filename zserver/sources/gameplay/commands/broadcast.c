/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <string.h>
#include <stdio.h>
#include "zcommands.h"
#include "zworld.h"

static void write_msg(network_client_t *client, char buff[10], char *a)
{
    write_to_buffer(&client->cb_out, (const uint8_t *)"message ", 8);
    write_to_buffer(&client->cb_out, (const uint8_t *)buff, 10);
    write_to_buffer(&client->cb_out, (const uint8_t *)", ", 2);
    write_to_buffer(&client->cb_out, (const uint8_t *)a, strlen(a));
    write_to_buffer(&client->cb_out, (const uint8_t *)"\n", 1);
}

static void broadcast_to_tile(tile_t *dest, char *a, int angle)
{
    network_server_t *server = (dest->first) ? \
get_server(dest->first->zappy->nm, dest->first->zappy->classic_id) : NULL;
    network_client_t *client;
    char buff[11] = {0};
    trantorian_t *p = dest->first;

    if (!server)
        return;
    do {
        client = get_client(server->client_user_map, (user_base_t *)p);
        if (!client)
            continue;
        angle = (angle == -1) ? 0 : \
(360 + (int)(p->orientation * 90) - angle) * 8 / 360;
        snprintf(buff, 10, "%d", angle);
        write_msg(client, buff, a);
        p = p->neighbour;
    } while (p != dest->first);
}

static int evaluate_tile_angle(e_cardinal_t dir, int i, int lim)
{
    return ((int)((((double)i / (double)lim) * 360.0 + 235) + dir * 90) % 360);
}

static void broadcast_at_lvl(trantorian_t *tran, char *a, \
unsigned int l, unsigned long long x)
{
    tile_t *t = top_left_corner_tile_at(tran->pos, tran->orientation, l);
    e_cardinal_t dir = cardinal_rotate_right(tran->orientation);
    int lim = tile_look_limit(l);
    int angle;

    for (int i = 0; i < lim; i++) {
        if (x <= t->broadcasted)
            continue;
        angle = (l == 0) ? -1 : evaluate_tile_angle(tran->orientation, i, lim);
        broadcast_to_tile(t, a, angle);
        t->broadcasted = x;
        if (4 <= lim && i % (lim / 4) == 0)
            dir = cardinal_rotate_right(dir);
        t = tile_forward(t, dir);
    }
}

void broadcast(client_user_pair_t *client, char *arg)
{
    static unsigned long long broadcasted_nb = 0;
    trantorian_t *trantorian = (trantorian_t *)client->user;
    int lim;

    if (!trantorian)
        return;
    if (trantorian->zappy->map_size.x < trantorian->zappy->map_size.y)
        lim = trantorian->zappy->map_size.y;
    else
        lim = trantorian->zappy->map_size.x;
    broadcasted_nb += 1;
    for (unsigned int i = 0; (int)i <= lim; i++) {
        broadcast_at_lvl(trantorian, arg, i, broadcasted_nb);
    }
    write_to_buffer(&client->client->cb_out, OK_MSG, OK_MSG_LEN);
}