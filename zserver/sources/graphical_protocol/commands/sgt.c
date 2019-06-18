/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** sgt.c
*/

/* Created the 17/06/2019 at 20:08 by jfrabel */

#include "graphical_protocol.h"

bool sgt(graphical_user_t *user, network_client_t *client,
    UNUSED uint8_t *data, UNUSED size_t size)
{
    char to_send[16] = {0};
    int time_scale = user->world_infos->time_scale;
    int data_size = 0;

    data_size = snprintf(to_send, 29, "sgt %i\n", time_scale);
    send_websocket(client, (uint8_t *)to_send, data_size, 1);
    return (true);
}