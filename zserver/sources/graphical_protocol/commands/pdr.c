/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** pdr.c
*/

/* Created the 17/06/2019 at 20:07 by jfrabel */

#include "graphical_protocol.h"

void pdr(zappy_t *world, trantorian_t *player_dropping, e_item_t item)
{
    char to_send[28] = {0};
    int data_len = 0;
    id_t id = player_dropping->id;
    int item_id = item_to_int(item);

    data_len = snprintf(to_send, 28, "pdr %i %i\n", id, item_id);
    send_to_all_ws_clients(world, (uint8_t *)to_send, data_len);
}