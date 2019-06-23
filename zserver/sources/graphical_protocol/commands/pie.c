/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** pie.c
*/

/* Created the 17/06/2019 at 20:06 by jfrabel */

#include "graphical_protocol.h"

void pie(zappy_t *world, int x, int y, incantation_result_t result)
{
    char to_send[37] = {0};
    int data_len = 0;

    data_len = snprintf(to_send, 37, "pie %i %i %s\n", x, y,
        (result == GP_INCANTATION_RESULT_SUCCESS) ? "success" : "failure");
    send_to_all_ws_clients(world, (uint8_t *)to_send, data_len);
}