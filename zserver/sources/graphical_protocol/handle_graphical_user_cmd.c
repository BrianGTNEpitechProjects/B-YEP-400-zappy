/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** handle_graphical_user_cmd.c
*/

/* Created the 17/06/2019 at 20:22 by jfrabel */

#include <string.h>
#include "graphical_protocol.h"

static const guser_possible_cmds_t guser_cmds[] = {
    {"msz\n", &msz},
    {"bct ", &bct},
    {"tna\n", &tna},
    {"pia ", &pia},
    {"ppo #", &ppo},
    {"plv #", &plv},
    {"pin #", &pin},
    {"sgt\n", &sgt},
    {"sst ", &sst},
    {NULL, NULL}
};

void send_to_all_ws_clients(zappy_t *world, uint8_t *msg, size_t len)
{
    network_server_t *server = get_server(world->nm, world->websocket_id);
    map_t curr;
    client_user_pair_t *pair;

    if (server == NULL)
        return;
    curr = server->client_user_map->client_user_map;
    for (; curr; curr = curr->next) {
        pair = curr->value;
        if (((graphical_user_t *)pair->user)->base.sock_type == WEBSOCKET) {
            send_websocket(pair->client, msg, len, 1);
        }
    }
}

void handle_graphical_user_cmd(graphical_user_t *user,
    network_client_t *client, uint8_t *data, size_t data_size)
{
    char extracted[C_BUFFER_SIZE] = {0};
    bool func_ret = false;
    bool found_cmd = false;

    memcpy(extracted, data, data_size);
    for (int i = 0; guser_cmds[i].cmd != NULL; i++) {
        if (!strncmp(guser_cmds[i].cmd, extracted, strlen(guser_cmds[i].cmd))) {
            func_ret = guser_cmds[i].func(user, client, data, data_size);
            found_cmd = true;
        }
        if (found_cmd && !func_ret)
            sbp(user, client, data, data_size);
        if (found_cmd)
            return;
    }
    suc(user, client, data, data_size);
}