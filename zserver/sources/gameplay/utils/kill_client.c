/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <stdbool.h>
#include <stdio.h>
#include "network_client_user_map.h"
#include "zcommands.h"
#include "graphical_protocol.h"

bool kill_player(trantorian_t *p)
{
    zappy_t *world = p->zappy;
    network_server_t *server = get_server(world->nm, world->classic_id);
    network_client_t *client;
    client_user_pair_t pair;

    if (server == NULL)
        return (false);
    client = get_client(server->client_user_map, (user_base_t *)p);
    pair.client = client;
    pair.user = (user_base_t *)p;
    return (kill_client(&pair));
}

bool kill_client(client_user_pair_t *c)
{
    trantorian_t *p = (trantorian_t *)c->user;

    if (c->client != NULL) {
        write_to_buffer(&c->client->cb_out, DEAD_MSG, DEAD_MSG_LEN);
        c->client->should_disconnect = true;
    } else if (p->base.on_disconnect) {
        p->base.on_disconnect((user_base_t *)p, NULL);
    }
    pdi(p->zappy, p);
    return (true);
}