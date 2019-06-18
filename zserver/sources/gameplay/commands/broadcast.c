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

static int max(int a, int b)
{
    return ((a < b) ? b : a);
}

static void broadcast_to_tile(tile_t *dest, char *a, int angle)
{
    trantorian_t *last = last_neighbour(dest->first);
    network_server_t *server;
    network_client_t *client;
    char buff[11] = {0};

    if (last)
        server = get_server(last->zappy->nm, last->zappy->classic_id);
    else
        return;
    for (trantorian_t *p = dest->first; p; p = p->next) {
        client = get_client(server->client_user_map, (user_base_t *)p);
        if (!client)
            continue;
        snprintf(buff, 10, "%d", (angle * 8 / 360) + 1);
        write_to_buffer(&client->cb_out, (const uint8_t *)"message ", 8);
        write_to_buffer(&client->cb_out, (const uint8_t *)", ", 2);
        write_to_buffer(&client->cb_out, (const uint8_t *)buff, 10);
        write_to_buffer(&client->cb_out, (const uint8_t *)"\n", 1);
    }
}

static int evaluate_tile_angle(e_cardinal_t dir, int i, int lim)
{
    return ((int)(((double)i / (double)lim) * 360.0 + 235) % 360 + dir * 90);
}

static void broadcast_at_lvl(client_user_pair_t *c, char *a, \
unsigned int l, unsigned long long x)
{
    trantorian_t *tranto = (trantorian_t *)c->user;
    tile_t *t = top_left_corner_tile_at(tranto->pos, tranto->orientation, l);
    e_cardinal_t dir = cardinal_rotate_right(tranto->orientation);
    int lim = tile_look_limit(l);

    for (int i = 0; i < lim; i++) {
        if (x <= t->broadcasted)
            continue;
        broadcast_to_tile(t, a, \
evaluate_tile_angle(tranto->orientation, i, lim));
        t->broadcasted = x;
        if (i % (lim / 4) == 0)
            dir = cardinal_rotate_right(dir);
        t = tile_forward(t, dir);
    }
}

void broadcast(client_user_pair_t *client, char *arg)
{
    static unsigned long long broadcasted_nb = 0;
    trantorian_t *trantorian = (trantorian_t *)client->user;
    int lim = max(trantorian->zappy->map_size.x, trantorian->zappy->map_size.y);

    broadcasted_nb += 1;
    for (unsigned int i = 0; (int)i < lim; i++) {
        broadcast_at_lvl(client, arg, i, broadcasted_nb);
    }
}