/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** smg.c
*/

/* Created the 17/06/2019 at 20:09 by jfrabel */

#include "graphical_protocol.h"

void smg(zappy_t *world, const char *msg)
{
    char to_send[C_BUFFER_SIZE] = {0};
    int data_len = 0;

    data_len = snprintf(to_send, C_BUFFER_SIZE, "smg %s\n", msg);
    send_to_all_ws_clients(world, (uint8_t *)to_send, data_len);
}