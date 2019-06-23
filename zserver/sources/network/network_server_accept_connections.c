/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_manager_accept_connections.c
*/

/* Created the 20/05/2019 at 12:50 by jfrabel */

#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "network_server.h"

static int reject_connection(network_server_t *ns)
{
    int sock;
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);

    sock = accept(ns->connexion_socket, (struct sockaddr *)&addr, &len);
    if (sock != invalid_socket)
        close(sock);
    return (0);
}

static int create_new_connection(network_server_t *ns)
{
    network_client_t *client = get_empty_client(ns->client_pool);
    struct sockaddr *addr;
    socklen_t len;

    if (client == NULL)
        return (reject_connection(ns));
    addr = (struct sockaddr *)&client->address;
    len = sizeof(*addr);
    if (!insert_client_in_map(ns->client_user_map, client))
        return (reject_connection(ns));
    client->socket = accept(ns->connexion_socket, addr, &len);
    if (client->socket == invalid_socket) {
        remove_client_from_map(ns->client_user_map, client);
        return (0);
    }
    client->user_disconnect_timeout = ns->default_client_disconnect_timeout;
    client->last_data_in_timestamp = time(NULL);
    client->last_data_out_timestamp = time(NULL);
    return (1);
}

int accept_connections(network_server_t *ns, fd_infos_t *infos)
{
    if (FD_ISSET(ns->connexion_socket, &infos->read_set)
    && !FD_ISSET(ns->connexion_socket, &infos->error_set)) {
        return (create_new_connection(ns));
    }
    return (0);
}