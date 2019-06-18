/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** suc.c
*/

/* Created the 17/06/2019 at 20:09 by jfrabel */

#include "graphical_protocol.h"

bool suc(UNUSED graphical_user_t *user, network_client_t *client,
    UNUSED uint8_t *data, UNUSED size_t size)
{
    send_websocket(client, (uint8_t *)"suc\n", 4, 1);
    return (true);
}