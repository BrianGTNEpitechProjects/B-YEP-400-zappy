/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <stdbool.h>
#include <stdio.h>
#include "network_client_user_map.h"
#include "zcommands.h"

bool kill_client(client_user_pair_t *c)
{
    write_to_buffer(&c->client->cb_out, DEAD_MSG, DEAD_MSG_LEN);
    c->client->lost_connection = true;
    printf("he dead mf\n");
    return (true);
}