/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <string.h>
#include <stdio.h>
#include "zcommands.h"
#include "zworld.h"
#include "zitem.h"

void inventory(client_user_pair_t *client, char *arg)
{
    trantorian_t *self = (trantorian_t *)client->user;
    char nb[11] = {0};
    uint8_t *name;
    size_t len;

    write_to_buffer(&client->client->cb_out, (const uint8_t *)"[", 1);
    for (int i = 0; i < TOT_ITEM_NB; ++i) {
        name = (uint8_t *)item_map[i].name;
        len = strlen((const char *)name);
        snprintf(nb, 10, "%d", self->inventory[i]);
        write_to_buffer(&client->client->cb_out, name, len);
        write_to_buffer(&client->client->cb_out, (const uint8_t *)" ", 1);
        write_to_buffer(&client->client->cb_out, (const uint8_t *)nb, 10);
        if (i != TOT_ITEM_NB - 1)
            write_to_buffer(&client->client->cb_out, (const uint8_t *)",", 1);
    }
    write_to_buffer(&client->client->cb_out, (const uint8_t *)"]\n", 2);
}