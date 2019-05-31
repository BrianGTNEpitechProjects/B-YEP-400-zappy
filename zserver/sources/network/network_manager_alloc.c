/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_manager_alloc.c
*/

/* Created the 20/05/2019 at 00:53 by jfrabel */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "network_manager.h"

static int listen_server(network_manager_t *nm)
{
    if (nm->connexion_socket == invalid_socket)
        return (-1);
    if (listen(nm->connexion_socket, MAX_PENDING_CONNECTIONS) == -1) {
        perror("listen");
        close(nm->connexion_socket);
        nm->connexion_socket = invalid_socket;
        return (-1);
    }
    return (0);
}

static int bind_server(network_manager_t *nm, int port)
{
    struct sockaddr *addr = (struct sockaddr *)(&nm->addr);
    socklen_t addr_len = sizeof(nm->addr);

    if (nm->connexion_socket == invalid_socket)
        return (-1);
    memset(addr, 0, addr_len);
    nm->addr.sin_family = AF_INET;
    nm->addr.sin_port = htons(port);
    nm->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(nm->connexion_socket, addr, addr_len) == -1) {
        perror("bind");
        close(nm->connexion_socket);
        nm->connexion_socket = invalid_socket;
        return (-1);
    }
    return (0);
}

network_manager_t *create_manager(int port)
{
    network_manager_t *nm = malloc(sizeof(*nm));

    if (nm != NULL) {
        nm->world_event_timeout = 0;
        nm->default_client_disconnect_timeout = 0;
        nm->connexion_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (nm->connexion_socket == invalid_socket)
            perror("socket");
        nm->client_user_map = create_network_client_user_map();
        nm->client_pool = create_new_pool();
        bind_server(nm, port);
        listen_server(nm);
    }
    if (nm != NULL &&
    (nm->connexion_socket == invalid_socket ||
    nm->client_user_map == NULL ||
    nm->client_pool == NULL)) {
        delete_manager(nm);
        nm = NULL;
    }
    return (nm);
}

void delete_manager(network_manager_t *nm)
{
    if (nm == NULL)
        return;
    delete_network_client_user_map(nm->client_user_map);
    delete_pool(nm->client_pool);
    if (nm->connexion_socket != invalid_socket)
        close(nm->connexion_socket);
    free(nm);
}