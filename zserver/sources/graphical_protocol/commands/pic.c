/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** pic.c
*/

/* Created the 17/06/2019 at 20:06 by jfrabel */

#include "graphical_protocol.h"

void pic(zappy_t *world, trantorian_t *player_incanting)
{
    char to_send[52] = {0};
    int data_len = 0;
    int x = player_incanting->pos->coords.x;
    int y = player_incanting->pos->coords.y;
    int level = player_incanting->lvl + 1;
    int id = player_incanting->id;

    data_len = snprintf(to_send, 52, "pic %i %i %i %i\n", x, y, level, id);
    send_to_all_ws_clients(world, (uint8_t *)to_send, data_len);
}