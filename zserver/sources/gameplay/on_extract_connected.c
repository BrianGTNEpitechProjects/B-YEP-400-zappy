/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <stdlib.h>
#include <string.h>
#include "zserver.h"
#include "zcommands.h"

static int emplace_command(trantorian_t *player, e_command_t id, char *arg)
{
    int ind;

    for (int i = 0; i < COMMAND_QUEUE_LEN; i++) {
        ind = (player->command_ind + i) % COMMAND_QUEUE_LEN;
        if (player->queue[ind].code == EMPTY) {
            player->queue[ind].code = id;
            player->queue[ind].remaining_time = commands[id].charge_time;
            strcpy(player->queue[ind].arg, arg);
            printf("DEBUG: %d\n", ind);
            return (ind);
        }
    }
    printf("DEBUG: -1\n");
    return (-1);
}

static bool is_command_valid(const uint8_t *data, int command_ind)
{
    char *command = commands[command_ind].command;
    size_t len = strlen(command);

    if (*data == ' ')
        return (false);
    if (strncmp((const char *)data, command, len) != 0)
        return (false);
    return (data[len] == ' ' || data[len] == '\n');
}

static bool fx(client_user_pair_t *p, char *arg, int command_ind)
{
    trantorian_t *t = (trantorian_t *)p->user;
    bool ret = COMMAND_NB < command_ind;
    const command_info_t *command = &(commands[command_ind]);

    ret = ret || (command->need_arg && strlen(arg) == 0);
    ret = ret || !command->is_startable(p, arg);
    return (ret);
}

void on_extract_connected(user_base_t *b, network_client_t *c, \
uint8_t *data, size_t sz)
{
    int i;
    size_t sep_ind = strcspn((char *)data, " \n");
    char *arg;
    client_user_pair_t pair = {.user = b, .client = c};

    if (c->has_overflow) {
        c->lost_connection = true;
        return;
    }
    for (i = 1; i <= COMMAND_NB; i++)
        if (sep_ind && is_command_valid(data, i))
            break;
    arg = (data[sep_ind] == '\n') ? "" : (char *)&(data[sep_ind + 1]);
    data[sz - 1] = '\0';
    if (fx(&pair, arg, i) || emplace_command((trantorian_t *)b, i, arg) < 0)
        write_to_buffer(&c->cb_out, KO_MSG, KO_MSG_LEN);
}