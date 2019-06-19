/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <string.h>
#include <math.h>
#include <stdio.h>
#include "zcommands.h"
#include "zworld.h"
#include "graphical_protocol.h"

static void write_msg(network_client_t *client, char buff[10], char *a)
{
    write_to_buffer(&client->cb_out, (const uint8_t *)"message ", 8);
    write_to_buffer(&client->cb_out, (const uint8_t *)buff, 10);
    write_to_buffer(&client->cb_out, (const uint8_t *)", ", 2);
    write_to_buffer(&client->cb_out, (const uint8_t *)a, strlen(a));
    write_to_buffer(&client->cb_out, (const uint8_t *)"\n", 1);
}

static int clkwise_to_cclkwise(int a)
{
    switch (a) {
    case 1:
    case 5: return (a);
    case 2: return (8);
    case 8: return (2);
    case 3: return (7);
    case 7: return (3);
    case 4: return (6);
    case 6: return (4);
    default: return (0);
    }
}

static void broadcast_to_tile(tile_t *dest, char *a, int angle)
{
    network_server_t *server = (dest->first) ? \
get_server(dest->first->zappy->nm, dest->first->zappy->classic_id) : NULL;
    network_client_t *client;
    char buff[11] = {0};
    trantorian_t *p = dest->first;
    int ang;

    if (!server)
        return;
    do {
        client = get_client(server->client_user_map, (user_base_t *)p);
        if (!client)
            continue;
        ang = (angle == -1) ? 0 : \
floor((((180 + angle - (int)(p->orientation * 90.0)) % 360) * 8) / 360) + 1;
        ang = clkwise_to_cclkwise(ang);
        snprintf(buff, 10, "%d", ang);
        write_msg(client, buff, a);
        p = p->neighbour;
    } while (p != dest->first);
}

static void broadcast_at_lvl(trantorian_t *tran, char *arg, \
unsigned int l, unsigned long long broadcast_nb)
{
    tile_t *t = top_left_corner_tile_at(tran->pos, tran->orientation, l);
    e_cardinal_t dir = tran->orientation;
    int lim = tile_look_limit(l);
    int angle;

    for (int i = 0; i < (lim - (l != 0)) * 4; i++, t = tile_forward(t, dir)) {
        if (1 < lim && i % (lim - 1) == 0)
            dir = cardinal_rotate_right(dir);
        if (broadcast_nb <= t->broadcasted)
            continue;
        angle = (l == 0) ? -1 : \
evaluate_tile_angle(tran->orientation, i, (lim - 1) * 4);
        broadcast_to_tile(t, arg, angle);
        t->broadcasted = broadcast_nb;
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
    pbc(trantorian->zappy, trantorian, arg);
    for (unsigned int i = 0; (int)i <= (lim / 2) + 1; i++)
        broadcast_at_lvl(trantorian, arg, i, broadcasted_nb);
    write_to_buffer(&client->client->cb_out, OK_MSG, OK_MSG_LEN);
}