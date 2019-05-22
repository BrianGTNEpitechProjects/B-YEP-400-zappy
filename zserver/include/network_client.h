/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_client.h
*/

/* Created the 15/05/2019 at 13:05 by jfrabel */

#ifndef PSU_ZAPPY_2018_NETWORK_CLIENT_H
#define PSU_ZAPPY_2018_NETWORK_CLIENT_H

#include <netinet/in.h>
#include "circular_buffer.h"

extern const int invalid_socket;

#define NETWORK_CLIENT_DEFAULT \
{\
    invalid_socket,\
    {0},\
    0,\
    0,\
    0,\
    C_BUFFER_DEFAULT,\
    C_BUFFER_DEFAULT\
}

typedef struct network_client_s {
    int socket;
    struct sockaddr_in address;
    time_t last_data_in_timestamp;
    time_t last_data_out_timestamp;
    int lost_connection;
    circular_buffer_t cb_in;
    circular_buffer_t cb_out;
} network_client_t;

int network_client_cmp(network_client_t *a, network_client_t *b);

bool flush_socket_to_in(network_client_t *client);
void flush_out_to_socket(network_client_t *client);

#endif //PSU_ZAPPY_2018_NETWORK_CLIENT_H
