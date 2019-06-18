/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include "zcommand_proto.h"
#include "zcommands.h"
#include "zserver.h"

#define CURR_MSG ("Current level: ")
#define CURR_MSG_LEN (sizeof(CURR_MSG))

static const incantation_requirement_t REQUIREMENTS[] = {
    {1, {0, 1, 0, 0, 0, 0, 0}},
    {2, {0, 1, 1, 1, 0, 0, 0}},
    {2, {0, 2, 0, 1, 0, 2, 0}},
    {4, {0, 1, 1, 2, 0, 1, 0}},
    {4, {0, 1, 2, 1, 3, 0, 0}},
    {6, {0, 1, 2, 3, 0, 1, 0}},
    {6, {0, 2, 2, 2, 2, 2, 1}}
};

static void write_lvl_msg(client_user_pair_t *client, int lvl)
{
    char buff[11] = {0};

    snprintf(buff, 11, "%d", lvl);
    write_to_client(client, (uint8_t *)CURR_MSG, CURR_MSG_LEN);
    write_to_client(client, (uint8_t *)buff, 10);
    write_to_client(client, (uint8_t *)"\n", 1);
}

void incantation(client_user_pair_t *client, __attribute__((unused)) char *arg)
{
    trantorian_t *trantorian = (trantorian_t *)client->user;
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
    if (is_ok) {
        trantorian->lvl += 1;
        write_lvl_msg(client, trantorian->lvl);
    } else
        write_to_buffer(&client->client->cb_out, KO_MSG, KO_MSG_LEN);
}