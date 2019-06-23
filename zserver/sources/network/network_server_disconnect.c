/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_manager_disconnect.c
*/

/* Created the 20/05/2019 at 01:08 by jfrabel */

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "network_server.h"

static void disconnect(
    network_server_t *ns, network_client_t *client, user_base_t *user)
{
    network_client_t default_client = NETWORK_CLIENT_DEFAULT;

    if (user && user->on_disconnect)
        user->on_disconnect(user, client);
    remove_client_from_map(ns->client_user_map, client);
    if (client && client->socket != invalid_socket) {
        close(client->socket);
    }
    if (client)
        memcpy(client, &default_client, sizeof(default_client));
}

void disconnect_client(network_server_t *ns, network_client_t *client)
{
    user_base_t *user;

    if (ns == NULL || client == NULL)
        return;
    user = get_user(ns->client_user_map, client);
    disconnect(ns, client, user);
}

void disconnect_user(network_server_t *ns, user_base_t *user)
{
    network_client_t *client;

    if (ns == NULL || user == NULL)
        return;
    client = get_client(ns->client_user_map, user);
    disconnect(ns, client, user);
}

void update_disconnected(network_server_t *ns)
{
    map_t curr = ns->client_user_map->client_user_map;
    client_user_pair_t *pair;

    while (curr != EMPTY_MAP) {
        pair = curr->value;
        if (pair->client->should_disconnect || pair->client->lost_connection) {
            curr = curr->next;
            disconnect_client(ns, pair->client);
        } else {
            curr = curr->next;
        }
    }
}