/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** pfk.c
*/

/* Created the 17/06/2019 at 20:06 by jfrabel */

#include "graphical_protocol.h"

void pfk(zappy_t *world, trantorian_t *player_laying)
{
    char to_send[16] = {0};
    int data_len = 0;

    data_len = snprintf(to_send, 16, "pfk %i\n", player_laying->id);
    send_to_all_ws_clients(world, (uint8_t *)to_send, data_len);
}