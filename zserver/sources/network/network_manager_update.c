/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_manager_update.c
*/

/* Created the 21/05/2019 at 17:26 by jfrabel */

#include <stdio.h>
#include <time.h>
#include "network_manager.h"

static void fill_fd_infos_users(fd_infos_t *infos, network_server_t *ns)
{
    map_t current_node = ns->client_user_map->client_user_map;
    client_user_pair_t *current_pair;

    while (current_node) {
        current_pair = current_node->value;
        if (current_pair->user != NULL &&
        current_pair->user->user_event_timeout != 0 &&
        (infos->smallest_timestamp > current_pair->user->user_event_timeout ||
        infos->smallest_timestamp == 0)) {
            infos->smallest_timestamp = current_pair->user->user_event_timeout;
            infos->to_disconnect_if_timeout = NULL;
        }
        current_node = current_node->next;
    }
}

static void fill_fd_infos_client(fd_infos_t *infos, network_client_t *client,
    network_server_t *server)
{
    time_t time_out = client->last_data_out_timestamp;
    time_t time_in = client->last_data_in_timestamp;
    time_t client_time = time_out < time_in ? time_in : time_out;
    time_t timeout = client_time + client->user_disconnect_timeout;

    if (client->user_disconnect_timeout != 0 &&
    (infos->smallest_timestamp > timeout || infos->smallest_timestamp == 0)) {
        infos->smallest_timestamp = timeout;
        infos->to_disconnect_if_timeout = client;
        infos->client_server = server;
    }
    FD_SET(client->socket, &infos->read_set);
    if (client->cb_out.nb_buffered_bytes != 0)
        FD_SET(client->socket, &infos->write_set);
    if (client->socket > infos->biggest_fd)
        infos->biggest_fd = client->socket;
}

static void fill_fd_infos_clients(fd_infos_t *infos, network_server_t *ns)
{
    map_t current_node = ns->client_user_map->client_user_map;
    client_user_pair_t *current_pair;

    while (current_node) {
        current_pair = current_node->value;
        if (current_pair->client != NULL) {
            fill_fd_infos_client(infos, current_pair->client, ns);
        }
        current_node = current_node->next;
    }
}

static void fill_fd_infos_server(fd_infos_t *infos, network_server_t *ns)
{
    if (ns->world_event_timeout != 0 &&
    (infos->smallest_timestamp > ns->world_event_timeout ||
    infos->smallest_timestamp == 0)) {
        infos->smallest_timestamp = ns->world_event_timeout;
        infos->to_disconnect_if_timeout = NULL;
    }
    if (ns->connexion_socket != invalid_socket) {
        FD_SET(ns->connexion_socket, &infos->read_set);
        if (infos->biggest_fd < ns->connexion_socket)
            infos->biggest_fd = ns->connexion_socket;
    }
    fill_fd_infos_users(infos, ns);
    fill_fd_infos_clients(infos, ns);
}

bool update_manager(network_manager_t *nm)
{
    fd_infos_t infos = {{}, {}, invalid_socket, 0, NULL, NULL};
    fd_set *read_set = &infos.read_set;
    fd_set *write_set = &infos.write_set;
    struct timeval to = {0, 1};

    FD_ZERO(read_set);
    FD_ZERO(write_set);
    if (nm->timeout_on_stdin)
        FD_SET(0, read_set);
    for (list_t curr = nm->servers; curr; curr = curr->next)
        fill_fd_infos_server(&infos, curr->value);
    if (infos.smallest_timestamp != 0) {
        to.tv_sec = infos.smallest_timestamp - time(NULL);
        to.tv_usec = 0;
    }
    if (select(infos.biggest_fd + 1, read_set, write_set, NULL, &to) > 0) {
        for (list_t curr = nm->servers; curr; curr = curr->next)
            update_server(curr->value, &infos);
    } else if (infos.to_disconnect_if_timeout != NULL)
        disconnect_client(infos.client_server, infos.to_disconnect_if_timeout);
    return (nm->timeout_on_stdin ? FD_ISSET(0, read_set) : false);
}