/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_manager_accept_connections.c
*/

/* Created the 20/05/2019 at 12:50 by jfrabel */

#include <unistd.h>
#include <time.h>
#include "network_manager.h"

static int reject_connection(network_manager_t *nm)
{
    int sock;
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);

    sock = accept(nm->connexion_socket, (struct sockaddr *)&addr, &len);
    if (sock != invalid_socket)
        close(sock);
    return (0);
}

static int create_new_connection(network_manager_t *nm)
{
    network_client_t *client = get_empty_client(nm->client_pool);
    struct sockaddr *addr;
    socklen_t len;

    if (client == NULL)
        return (reject_connection(nm));
    addr = (struct sockaddr *)&client->address;
    len = sizeof(*addr);
    if (!insert_client_in_map(nm->client_user_map, client))
        return (reject_connection(nm));
    client->socket = accept(nm->connexion_socket, addr, &len);
    if (client->socket == invalid_socket) {
        remove_client_from_map(nm->client_user_map, client);
        return (0);
    }
    client->last_data_in_timestamp = time(NULL);
    client->last_data_out_timestamp = time(NULL);
    return (1);
}

int accept_connections(network_manager_t *nm)
{
    fd_set conn_fd;
    struct timeval to;

    to.tv_sec = 0;
    to.tv_usec = 1;
    FD_ZERO(&conn_fd);
    FD_SET(nm->connexion_socket, &conn_fd);
    if (select(nm->connexion_socket + 1, &conn_fd, NULL, NULL, &to) > 0) {
        return (create_new_connection(nm));
    }
    return (0);
}