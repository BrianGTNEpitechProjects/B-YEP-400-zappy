/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <stdbool.h>
#include <string.h>
#include "network_client_user_map.h"
#include "zcommands.h"
#include "graphical_protocol.h"

__attribute__((unused)) static void force_command(trantorian_t *t, \
e_command_t id)
{
    int c_ind = t->command_ind;

    c_ind = (c_ind - 1 < 0) ? COMMAND_QUEUE_LEN - 1 : c_ind - 1;
    t->queue[c_ind].code = id;
    t->queue[c_ind].remaining_time = (double)commands[id].charge_time;
    memset(t->queue[c_ind].arg, 0, ARG_BUFFER_SIZE);
}

static void force_incant_on_neighbours(network_server_t *s, trantorian_t *ref)
{
    trantorian_t *t = ref->neighbour;
    int lim = REQUIREMENTS[ref->lvl - 1].player_nb;
    int i = 0;
    network_client_t *c;

    if (t != NULL)
        pic(t->zappy, t);
    do {
        if (t == NULL)
            return;
        if (t->lvl == ref->lvl) {
            c = get_client(s->client_user_map, (user_base_t *)t);
            pic(t->zappy, t);
            write_to_buffer(&c->cb_out, INCANT_MSG, INCANT_MSG_LEN);
            i++;
        }
        t = t->next;
    } while (t != ref && i < lim);
}

bool incantation_startable(client_user_pair_t *c, \
__attribute__((unused)) char *a)
{
    trantorian_t *t = (trantorian_t *)c->user;
    network_server_t *server = get_server(t->zappy->nm, t->zappy->classic_id);

    if (incantation_valid(c, a)) {
        force_incant_on_neighbours(server, t);
        return (true);
    } else {
        return (false);
    }
}
