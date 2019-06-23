/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** pbc.c
*/

/* Created the 17/06/2019 at 20:06 by jfrabel */

#include "graphical_protocol.h"

void pbc(zappy_t *world, trantorian_t *player, const char *msg)
{
    char to_send[C_BUFFER_SIZE + 1] = {0};
    int data_len = 0;

    data_len = snprintf(to_send, C_BUFFER_SIZE, "pbc %i %s\n", \
player->id, msg);
    send_to_all_ws_clients(world, (uint8_t *)to_send, data_len);
}