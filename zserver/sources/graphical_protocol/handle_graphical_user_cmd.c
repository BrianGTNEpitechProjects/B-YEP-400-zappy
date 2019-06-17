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
    {NULL, NULL}
};

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