/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <string.h>
#include "zcommand_proto.h"
#include "zcommands.h"
#include "zserver.h"
#include "graphical_protocol.h"

static void write_lvl_msg(client_user_pair_t *client, int lvl)
{
    char buff[11] = {0};

    snprintf(buff, 11, "%d", lvl);
    write_to_client(client, CURR_MSG, CURR_MSG_LEN);
    write_to_client(client, (uint8_t *)buff, strlen(buff));
    write_to_client(client, (uint8_t *)"\n", 1);
}

bool incantation_valid(client_user_pair_t *c, __attribute__((unused)) char *a)
{
    trantorian_t *trantorian = (trantorian_t *)c->user;
    tile_t *t = trantorian->pos;
    int pop = tile_population_size_with_lvl(t, trantorian->lvl);
    const incantation_requirement_t *req = &REQUIREMENTS[trantorian->lvl - 1];
    bool is_ok = (pop == req->player_nb);

    for (int i = 0; i < TOT_ITEM_NB; i++) {
        if (t->content[i] < req->stones[i]) {
            is_ok = false;
            break;
        }
    }
    return (is_ok);
}

static void notify_lvl(trantorian_t *t)
{
    zappy_t *zappy = t->zappy;
    network_server_t *s = get_server(zappy->nm, zappy->classic_id);
    network_client_t *tmp;
    client_user_pair_t p = {0};

    tmp = get_client(s->client_user_map, (user_base_t *)t);
    p = (client_user_pair_t){.client = tmp, .user = (user_base_t *)t};
    write_lvl_msg(&p, t->lvl);
    plu(t->zappy, t);
}

static void upgrade_trantorians(client_user_pair_t *c, unsigned int lvl)
{
    trantorian_t *trantorian = (trantorian_t *)c->user;
    trantorian_t *t = trantorian;
    const incantation_requirement_t *req = &REQUIREMENTS[lvl - 1];
    int j = 0;
    int lim = tile_population_size(trantorian->pos);

    for (int i = 0; i < req->player_nb && j < lim; t = t->neighbour) {
        if (t->lvl == lvl) {
            i += 1;
            t->lvl += 1;
            notify_lvl(t);
        }
        j++;
    }
    for (int i = 0; i < TOT_ITEM_NB; i++)
        trantorian->pos->content[i] -= req->stones[i];
}

void incantation(client_user_pair_t *client, __attribute__((unused)) char *arg)
{
    trantorian_t *trantorian = (trantorian_t *)client->user;
    unsigned int inc_lvl = trantorian->lvl;

    if (incantation_valid(client, arg)) {
        pie(trantorian->zappy, trantorian->pos->coords.x,
            trantorian->pos->coords.y, GP_INCANTATION_RESULT_SUCCESS);
        upgrade_trantorians(client, inc_lvl);
    } else {
        pie(trantorian->zappy, trantorian->pos->coords.x,
            trantorian->pos->coords.y, GP_INCANTATION_RESULT_FAILURE);
        write_to_buffer(&client->client->cb_out, KO_MSG, KO_MSG_LEN);
    }
}