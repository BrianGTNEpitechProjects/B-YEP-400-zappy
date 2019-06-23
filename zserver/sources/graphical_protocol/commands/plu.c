/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** plu.c
*/

/* Created the 19/06/2019 at 02:13 by jfrabel */

#include <string.h>
#include "graphical_protocol.h"

void plu(zappy_t *world, trantorian_t *player)
{
    char to_send[28] = {0};
    size_t data_size = 0;
    int id = player->id;
    int level = player->lvl;

    data_size = snprintf(to_send, 28, "plu %i %i\n", id, level);
    send_to_all_ws_clients(world, (uint8_t *)to_send, data_size);
}