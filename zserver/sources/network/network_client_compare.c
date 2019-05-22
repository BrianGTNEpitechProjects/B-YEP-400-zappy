/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_client_compare.c
*/

/* Created the 19/05/2019 at 21:51 by jfrabel */

#include "network_client.h"

int network_client_cmp(network_client_t *a, network_client_t *b)
{
    if (a->socket == b->socket)
        return (0);
    return (a->socket - b->socket);
}