/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_manager_update.c
*/

/* Created the 21/05/2019 at 17:26 by jfrabel */

#include <stdio.h>
#include "network_manager.h"

void update_manager(network_manager_t *nm,
    uint8_t *delim, size_t delim_size, time_t timeout_at)
{
    if (accept_connections(nm) && PRINT_DEBUG) {
        fprintf(stderr, "[DEBUG] accepted client\n");
    }
    sync_buffers(nm);
    extract_to_users(nm, delim, delim_size);
    timeout_clients(nm, timeout_at);
}