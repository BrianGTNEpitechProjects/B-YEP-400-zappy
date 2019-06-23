/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** eht.c
*/

/* Created the 17/06/2019 at 20:08 by jfrabel */

#include "graphical_protocol.h"

void eht(zappy_t *world, trantorian_t *egg)
{
    char to_send[16] = {0};
    int data_len = 0;
    int egg_id = egg->id;

    data_len = snprintf(to_send, 16, "eht %i\n", egg_id);
    send_to_all_ws_clients(world, (uint8_t *)to_send, data_len);
}
