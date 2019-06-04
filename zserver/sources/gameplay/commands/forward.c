/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include "zcommands.h"

void forward(client_user_pair_t *client, char *arg)
{
    write_to_buffer(&client->client->cb_out, (const uint8_t *)"OK", 2);
}