/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include "zcommands.h"
#include "zworld.h"

void left(client_user_pair_t *client, __attribute__((unused)) char *arg)
{
    trantorian_t *trantorian = (trantorian_t *)client->user;

    trantorian->orientation = cardinal_rotate_left(trantorian->orientation);
    if (trantorian->orientation < 0)
        trantorian->orientation = 3;
    write_to_buffer(&client->client->cb_out, OK_MSG, OK_MSG_LEN);
}