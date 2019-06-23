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
#include "network_server.h"

static int listen_server(network_server_t *ns)
{
    if (ns->connexion_socket == invalid_socket)
        return (-1);
    if (listen(ns->connexion_socket, MAX_PENDING_CONNECTIONS) == -1) {
        perror("listen");
        close(ns->connexion_socket);
        ns->connexion_socket = invalid_socket;
        return (-1);
    }
    return (0);
}

static int bind_server(network_server_t *ns, int port)
{
    struct sockaddr *addr = (struct sockaddr *)(&ns->addr);
    socklen_t addr_len = sizeof(ns->addr);

    if (ns->connexion_socket == invalid_socket)
        return (-1);
    memset(addr, 0, addr_len);
    ns->addr.sin_family = AF_INET;
    ns->addr.sin_port = htons(port);
    ns->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(ns->connexion_socket, addr, addr_len) == -1) {
        perror("bind");
        close(ns->connexion_socket);
        ns->connexion_socket = invalid_socket;
        return (-1);
    }
    return (0);
}

network_server_t *create_server(int port, id_t id)
{
    network_server_t *ns = malloc(sizeof(*ns));

    if (ns != NULL) {
        ns->id = id;
        ns->world_event_timeout.tv_sec = 0;
        ns->world_event_timeout.tv_usec = 0;
        ns->default_client_disconnect_timeout = 0;
        ns->connexion_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (ns->connexion_socket == invalid_socket)
            perror("socket");
        ns->client_user_map = create_network_client_user_map();
        ns->client_pool = create_new_pool();
        bind_server(ns, port);
        listen_server(ns);
    }
    if (ns != NULL && (ns->connexion_socket == invalid_socket ||
    ns->client_user_map == NULL || ns->client_pool == NULL)) {
        delete_server(ns);
        ns = NULL;
    }
    return (ns);
}

void delete_server(network_server_t *ns)
{
    map_t curr = NULL;
    map_t last = NULL;

    if (ns == NULL)
        return;
    curr = ns->client_user_map->client_user_map;
    while (curr != NULL) {
        last = curr;
        curr = curr->next;
        disconnect_client(ns, ((client_user_pair_t *)last->value)->client);
    }
    delete_network_client_user_map(ns->client_user_map);
    delete_pool(ns->client_pool);
    if (ns->connexion_socket != invalid_socket)
        close(ns->connexion_socket);
    free(ns);
}