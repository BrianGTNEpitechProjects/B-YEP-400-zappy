/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <string.h>
#include "zcommands.h"
#include "zworld.h"
#include "zserver.h"

void connect_nbr(client_user_pair_t *client, __attribute__((unused)) char *arg)
{
    trantorian_t *trantorian = (trantorian_t *)client->user;
    int unused = count_unused_slot(trantorian->zappy, trantorian->team->name);
    char nb[11] = {0};

    snprintf(nb, 10, "%d", unused);
    write_to_buffer(&client->client->cb_out, (const uint8_t *)nb, strlen(nb));
    write_to_buffer(&client->client->cb_out, (const uint8_t *)"\n", 1);
}