/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** pnw.c
*/

/* Created the 17/06/2019 at 20:05 by jfrabel */

#include "graphical_protocol.h"

void pnw(zappy_t *world, trantorian_t *new_player)
{
    char to_send[116] = {0};
    int data_len = 0;
    id_t id = new_player->id;
    int x = new_player->pos->coords.x;
    int y = new_player->pos->coords.y;
    int o = cardinal_to_int(new_player->orientation);
    int level = new_player->lvl;

    data_len = snprintf(to_send, 116, "pnw #%i %i %i %i %i %s\n",
        id, x, y, o, level, new_player->team.name);
    send_to_all_ws_clients(world, (uint8_t *)to_send, data_len);
}