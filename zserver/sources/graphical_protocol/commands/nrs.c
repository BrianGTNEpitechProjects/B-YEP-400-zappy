/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** nrs.c
*/

/* Created the 20/06/2019 at 15:16 by jfrabel */

#include "graphical_protocol.h"

void nrs(zappy_t *world, tile_t *tile, e_item_t ressource)
{
    char to_send[52] = {0};
    int data_len = 0;
    int x = tile->coords.x;
    int y = tile->coords.y;
    int r = item_to_int(ressource);

    data_len = snprintf(to_send, 52, "nrs %i %i %i\n", x, y, r);
    send_to_all_ws_clients(world, (uint8_t *)to_send, data_len);
}