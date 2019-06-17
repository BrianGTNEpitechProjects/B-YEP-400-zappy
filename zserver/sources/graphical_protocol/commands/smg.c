/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** smg.c
*/

/* Created the 17/06/2019 at 20:09 by jfrabel */

#include "graphical_protocol.h"

void smg(zappy_t *world, const char *msg)
{
    network_server_t *server = get_server(world->nm, world->websocket_id);
    char to_send[C_BUFFER_SIZE] = {0};
    int data_len = 0;
    map_t curr;
    client_user_pair_t *pair;

    if (server == NULL)
        return;
    data_len = snprintf(to_send, C_BUFFER_SIZE, "smg %s\n", msg);
    curr = server->client_user_map->client_user_map;
    for (; curr; curr = curr->next) {
        pair = curr->value;
        if (((graphical_user_t *)pair->user)->base.sock_type == WEBSOCKET) {
            send_websocket(pair->client, to_send, data_len, 1);
        }
    }
}