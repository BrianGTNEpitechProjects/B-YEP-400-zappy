/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** Zappy
*/

#include <stdlib.h>
#include <string.h>
#include "zserver.h"
#include "zcommands.h"

void on_disconnect(user_base_t *base, __attribute__((unused)) \
network_client_t *client)
{
    trantorian_t *trantorian = (trantorian_t *)base;

    trantorian_move(trantorian, NULL);
    if (trantorian->zappy->players == trantorian) {
        trantorian->zappy->players = trantorian->next;
        free(trantorian);
        return;
    }
    for (trantorian_t *t = trantorian->zappy->players; t; t = t->next) {
        if (t->next == trantorian) {
            t->next = trantorian->next;
            free(trantorian);
            return;
        }
    }
    free(trantorian);
}

void on_extract_not_connected(user_base_t *b, network_client_t *c, \
uint8_t *data, size_t sz)
{
    client_user_pair_t pair = {c, b};
    trantorian_t *tranto = ((trantorian_t *)b);

    if (c->has_overflow) {
        kill_client(&pair);
        return;
    }
    data[sz - 1] = 0;
    for (int i = 0; tranto->zappy->teams[i].name != NULL; i++) {
        if (cmpstr((char *) data, tranto->zappy->teams[i].name, \
tranto->zappy->case_sensitive_inputs) == 0)
            tranto = add_user_to_team(&pair, &tranto->zappy->teams[i]);
    }
    if (tranto->team == NULL) {
        write_to_buffer(&pair.client->cb_out, KO_MSG, KO_MSG_LEN);
    } else {
        response_success_connection((trantorian_t *)b, c);
        b->on_extracted = &on_extract_connected;
    }
}