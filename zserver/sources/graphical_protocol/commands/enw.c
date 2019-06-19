/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** enw.c
*/

/* Created the 17/06/2019 at 20:07 by jfrabel */

#include "graphical_protocol.h"

void enw(zappy_t *world, trantorian_t *egg)
{
    char to_send[52] = {0};
    int data_len = 0;
    int x = egg->pos->coords.x;
    int y = egg->pos->coords.y;
    int egg_id = egg->id;
    int player_id = egg->egg_owner;

    data_len = snprintf(to_send, 52, "pic %i %i %i %i\n",
        egg_id, player_id, x, y);
    send_to_all_ws_clients(world, (uint8_t *)to_send, data_len);
}