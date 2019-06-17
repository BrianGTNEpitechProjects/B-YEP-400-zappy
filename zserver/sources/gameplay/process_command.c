/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "zserver.h"

static void set_to_next_command(trantorian_t *trantorian)
{
    command_t *command = &trantorian->queue[trantorian->command_ind];

    trantorian->command_ind = \
(unsigned char)((trantorian->command_ind + 1) % COMMAND_QUEUE_LEN);
    command->code = EMPTY;
    memset(command->arg, 0, ARG_BUFFER_SIZE);
}

static bool command_valid(client_user_pair_t *client, command_t *command)
{
    trantorian_t *trantorian = (trantorian_t *)client->user;

    if (commands[command->code].is_valid(client, command->arg))
        return (true);
    set_to_next_command(trantorian);
    write_to_client(client, (uint8_t *)KO_MSG, KO_MSG_LEN);
    return (false);
}

static bool exec_command(client_user_pair_t *client, command_t *command)
{
    trantorian_t *trantorian = (trantorian_t *)client->user;

    if (command->code == EMPTY)
        return (false);
    commands[command->code].callback(client, command->arg);
    set_to_next_command(trantorian);
    return (false);
}

static void evaluate_time(command_t *command, struct timespec *time, int scale)
{
    command->remaining_time -= time->tv_sec * scale;
    command->remaining_time -= time->tv_nsec * ((float)scale) / pow(10, 9);
}

void process_command_on_users(zappy_t *z, network_client_user_map_t *m)
{
    static clockid_t clk = 0;
    struct timespec time;
    trantorian_t *trantorian;
    command_t *command;

    clock_gettime(clk, &time);
    for (map_t node = m->client_user_map; node; node = node->next) {
        trantorian = (trantorian_t *)((client_user_pair_t *)node->value)->user;
        command = &(trantorian->queue[trantorian->command_ind]);
        if (command->code == EMPTY)
            continue;
        evaluate_time(command, &time, z->time_scale);
        if (command_valid(node->value, command) && command->remaining_time < 0) {
            exec_command(node->value, command);
            set_to_next_command(trantorian);
        }
    }
    clk = 0;
}