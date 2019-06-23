/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** pdi.c
*/

/* Created the 17/06/2019 at 20:07 by jfrabel */

#include "graphical_protocol.h"

void pdi(zappy_t *world, trantorian_t *player_dying)
{
    char to_send[16] = {0};
    int data_len = 0;
    id_t id = player_dying->id;

    data_len = snprintf(to_send, 16, "pdi %i\n", id);
    send_to_all_ws_clients(world, (uint8_t *)to_send, data_len);
}