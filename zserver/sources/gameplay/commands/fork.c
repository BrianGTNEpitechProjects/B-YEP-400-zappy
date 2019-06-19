/*
** EPITECH PROJECT, 2018
** fork.c
** File description:
** Fork (laying egg) command
*/

#include <stdlib.h>
#include "zcommands.h"
#include "zworld.h"
#include "zserver.h"
#include "graphical_protocol.h"

bool fork_start(client_user_pair_t *pair, char *cmd)
{
    trantorian_t *trantorian = (trantorian_t *)pair->user;

    pfk(trantorian->zappy, trantorian);
    return (true);
}

void fork_command(client_user_pair_t *client, __attribute__((unused)) char *arg)
{
    trantorian_t *trantorian = (trantorian_t *)client->user;
    trantorian_t *egg = create_player();

    if (egg == NULL) {
        write_to_buffer(&client->client->cb_out, OK_MSG, OK_MSG_LEN);
        return;
    }
    egg->is_egg = true;
    egg->base.on_extracted = NULL;
    egg->egg_owner = trantorian->id;
    egg->zappy = trantorian->zappy;
    egg->team = trantorian->team;
    set_position(egg, trantorian->pos);
    while (trantorian->next != NULL)
        trantorian = trantorian->next;
    trantorian->next = egg;
    write_to_buffer(&client->client->cb_out, OK_MSG, OK_MSG_LEN);
    enw(trantorian->zappy, egg);
}