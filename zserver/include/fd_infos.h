/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** fd_infos.h
*/

/* Created the 03/06/2019 at 21:12 by jfrabel */

#ifndef PSU_ZAPPY_2018_FD_INFOS_H
#define PSU_ZAPPY_2018_FD_INFOS_H

#include "network_client.h"

typedef struct fd_infos_s {
    fd_set read_set;
    fd_set write_set;
    int biggest_fd;
    time_t smallest_timestamp;
    network_client_t *to_disconnect_if_timeout;
    struct network_server_s *client_server;
} fd_infos_t;

#endif //PSU_ZAPPY_2018_FD_INFOS_H
