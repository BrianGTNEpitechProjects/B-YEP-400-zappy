/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <string.h>
#include "zcommands.h"
#include "zworld.h"
#include "graphical_protocol.h"

static network_client_user_map_t *retrieve_client_map(zappy_t *zap)
{
    id_t id = zap->classic_id;
    network_server_t *server;

    for (node_t *n = zap->nm->servers; n; n = n->next) {
        server = n->value;
        if (server->id == id)
            return (server->client_user_map);
    }
    return (NULL);
}

static void notify_user(network_client_t *c, e_cardinal_t s_d, e_cardinal_t e_d)
{
    char buff[11] = {0};
    double ang = (int)((e_d * 90.0 - s_d * 90) + 90 * 6) % 360;
    e_cardinal_t dir = (e_cardinal_t)((int)ang / 90);

    if (dir == EAST)
        dir = WEST;
    else if (dir == WEST)
        dir = EAST;
    snprintf(buff, 10, "%d", dir * 2 + 1);
    if (!c)
        return;
    write_to_buffer(&c->cb_out, (const uint8_t *)EJECT_MSG, EJECT_MSG_LEN);
    write_to_buffer(&c->cb_out, (const uint8_t *)buff, strlen(buff));
    write_to_buffer(&c->cb_out, (const uint8_t *)"\n", 1);
}

void eject(client_user_pair_t *client, __attribute__((unused)) char *arg)
{
    trantorian_t *self = (trantorian_t *)client->user;
    tile_t *tile = tile_forward(self->pos, self->orientation);
    network_client_user_map_t *map = retrieve_client_map(self->zappy);
    trantorian_t *trantorian;

    if (tile_population_size(self->pos) == 1) {
        write_to_buffer(&client->client->cb_out, KO_MSG, KO_MSG_LEN);
        return;
    }
    pex(self->zappy, self);
    for (trantorian_t *tmp = self->neighbour; tmp != self;) {
        trantorian = tmp->neighbour;
        notify_user(get_client(map, (user_base_t *)tmp), \
trantorian->orientation, self->orientation);
        trantorian_move(tmp, tile);
        tmp = trantorian;
    }
    write_to_buffer(&client->client->cb_out, OK_MSG, OK_MSG_LEN);
}