/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include "zcommands.h"
#include "zworld.h"

void eject(client_user_pair_t *client, __attribute__((unused)) char *arg)
{
    trantorian_t *self = (trantorian_t *)client->user;
    trantorian_t *trantorian;

    if (tile_population_size(self->pos) == 1) {
        write_to_buffer(&client->client->cb_out, KO_MSG, KO_MSG_LEN);
        return;
    }
    for (trantorian_t *tmp = self->neighbour; tmp != self;) {
        trantorian = tmp->neighbour;
        trantorian_move_forward(tmp);
        tmp = trantorian;
    }
    write_to_buffer(&client->client->cb_out, OK_MSG, OK_MSG_LEN);
}