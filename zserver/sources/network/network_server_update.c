/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_server_update.c
*/

/* Created the 03/06/2019 at 22:15 by jfrabel */

#include "network_server.h"

void update_server(network_server_t *ns, fd_infos_t *infos)
{
    accept_connections(ns, infos);
    sync_buffers(ns, infos);
    update_disconnected(ns);
}