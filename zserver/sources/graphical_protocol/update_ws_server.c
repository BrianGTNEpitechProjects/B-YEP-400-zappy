/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** update_ws_server.c
*/

/* Created the 17/06/2019 at 16:38 by jfrabel */

#include "graphical_protocol.h"

static void accept_connexions(zappy_t *zap, network_server_t *server)
{
    client_user_pair_t *client = NULL;
    graphical_user_t *guser = NULL;

    do {
        client = get_next_client_without_user(server->client_user_map);
        if (!client)
            return;
        guser = create_new_graphical_user(zap);
        if (guser != NULL)
            client->user = (user_base_t *)guser;
    } while (1);
}

void update_ws_server(zappy_t *zap)
{
    network_server_t *server = get_server(zap->nm, zap->websocket_id);

    if (server == NULL)
        return;
    accept_connexions(zap, server);
    read_ws_clients_data(server);
    extract_to_users(server, (uint8_t *)"\n", 1);
}