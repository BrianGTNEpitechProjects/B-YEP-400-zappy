/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <string.h>
#include "zcommand_proto.h"
#include "zworld.h"
#include "zcommands.h"
#include "graphical_protocol.h"

bool take_valid(client_user_pair_t *client, char *arg)
{
    trantorian_t *trantorian = (trantorian_t *)client->user;
    int item_id = get_item_id_from_name(arg, \
trantorian->zappy->case_sensitive_inputs);

    return (!(item_id == -1 || trantorian->pos->content[item_id] <= 0));
}

void take_object(client_user_pair_t *client, char *arg)
{
    trantorian_t *trantorian = (trantorian_t *)client->user;
    int item_id = get_item_id_from_name(arg, \
trantorian->zappy->case_sensitive_inputs);

    if (item_id == -1 || trantorian->pos->content[item_id] <= 0) {
        write_to_buffer(&client->client->cb_out, KO_MSG, KO_MSG_LEN);
        return;
    }
    trantorian->inventory[item_id] += 1;
    trantorian->pos->content[item_id] -= 1;
    write_to_buffer(&client->client->cb_out, OK_MSG, OK_MSG_LEN);
    pgt(trantorian->zappy, trantorian, item_id);
}