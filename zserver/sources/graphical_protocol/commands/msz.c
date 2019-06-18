/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** msz.c
*/

/* Created the 17/06/2019 at 20:04 by jfrabel */

#include "graphical_protocol.h"

bool msz(graphical_user_t *user, network_client_t *client,
    uint8_t *data, size_t size)
{
    char to_send[29] = {0};
    int map_size_x = user->world_infos->map_size.x;
    int map_size_y = user->world_infos->map_size.y;
    int data_size = 0;

    data_size = snprintf(to_send, 29, "msz %i %i\n", map_size_x, map_size_y);
    send_websocket(client, (uint8_t *)to_send, data_size, 1);
    return (true);
}