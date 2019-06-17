/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include "zcommands.h"
#include "zworld.h"

void right(client_user_pair_t *client, __attribute__((unused)) char *arg)
{
    trantorian_t *trantorian = (trantorian_t *)client->user;

    trantorian->orientation = (trantorian->orientation + 1) % 4;
    write_to_buffer(&client->client->cb_out, OK_MSG, OK_MSG_LEN);
}