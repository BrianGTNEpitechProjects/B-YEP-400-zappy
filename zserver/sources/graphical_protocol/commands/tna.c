/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** tna.c
*/

/* Created the 17/06/2019 at 20:05 by jfrabel */

#include <string.h>
#include "graphical_protocol.h"

bool tna(graphical_user_t *user, network_client_t *client,
    UNUSED uint8_t *data, UNUSED size_t size)
{
    char *name;
    size_t data_len = 0;
    uint8_t to_write = 0b10000000 + 1;

    for (int i = 0; user->world_infos->teams[i].name != NULL; ++i)
        data_len += (5 + strlen(user->world_infos->teams[i].name));
    write_to_buffer(&client->cb_out, &to_write, 1);
    to_write = data_len & 0b011111111;
    write_to_buffer(&client->cb_out, &to_write, 1);
    for (int i = 0; user->world_infos->teams[i].name != NULL; ++i) {
        name = user->world_infos->teams[i].name;
        write_to_buffer(&client->cb_out, (uint8_t *)"tna ", 4);
        write_to_buffer(&client->cb_out, (uint8_t *)name, strlen(name));
        write_to_buffer(&client->cb_out, (uint8_t *)"\n", 1);
    }
    return (true);
}