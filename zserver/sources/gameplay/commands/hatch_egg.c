/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** Command for layed eggs to wait them to hatch
*/

#include <string.h>
#include "zcommand_proto.h"
#include "zworld.h"
#include "zserver.h"
#include "zcommands.h"

void hatch_egg(client_user_pair_t *client, __attribute__((unused)) char *arg)
{
    trantorian_t *egg = (trantorian_t *)client->user;

    egg->base.on_extracted = &on_extract_connected;
}