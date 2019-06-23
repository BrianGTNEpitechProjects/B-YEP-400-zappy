/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** pex.c
*/

/* Created the 17/06/2019 at 20:06 by jfrabel */

#include "graphical_protocol.h"

void pex(zappy_t *world, trantorian_t *player_expulsing)
{
    char to_send[16] = {0};
    int data_len = 0;
    id_t id = player_expulsing->id;

    data_len = snprintf(to_send, 16, "pex %i\n", id);
    send_to_all_ws_clients(world, (uint8_t *)to_send, data_len);
}