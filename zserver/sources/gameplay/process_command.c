/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "zserver.h"
#include "zcommands.h"

static void apply_timeout(trantorian_t *trantorian)
{
    double min = trantorian->food_time;
    command_t *command_info = &trantorian->queue[trantorian->command_ind];

    if (command_info->code != EMPTY && command_info->remaining_time < min)
        min = command_info->remaining_time;
    min /= trantorian->zappy->time_scale;
    trantorian->base.user_event_timeout.tv_sec = (__time_t)floor(min);
    trantorian->base.user_event_timeout.tv_usec = \
(__suseconds_t)((min - trunc(min)) * pow(10, 6));
}

static bool command_valid(client_user_pair_t *client, command_t *command)
{
    trantorian_t *trantorian = (trantorian_t *)client->user;

    if (trantorian->is_egg)
        return (false);
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

static bool evaluate_time_and_command(client_user_pair_t *c, \
struct timespec *t, int scale)
{
    trantorian_t *trantorian = (trantorian_t *)c->user;
    command_t *command;

    if (apply_time(&trantorian->food_time, t, scale))
        starve(c);
    command = &(trantorian->queue[trantorian->command_ind]);
    if (command->code == EMPTY)
        return (true);
    else if (commands[command->code].charge_time == command->remaining_time) {
        if (!trantorian->is_egg && \
commands[command->code].is_startable(c, command->arg)) {
        } else {
            write_to_client(c, KO_MSG, KO_MSG_LEN);
            set_to_next_command(trantorian);
        }
    }
    return (!apply_time(&command->remaining_time, t, scale));
}

void process_command_on_users(zappy_t *z, network_client_user_map_t *m)
{
    static struct timespec t = {0};
    command_t *command;
    client_user_pair_t pair;
    trantorian_t *tmp = NULL;

    for (trantorian_t *node = z->players; node;) {
        pair = (client_user_pair_t){get_client(m, (user_base_t *)node), \
(user_base_t *)node};
        if (node->life_unit <= 0 && node->base.on_disconnect) {
            tmp = node;
            node = node->next;
            tmp->base.on_disconnect((user_base_t *)tmp, NULL);
            continue;
        }
        command = &(node->queue[node->command_ind]);
        if (evaluate_time_and_command(&pair, &t, z->time_scale))
            apply_timeout(node);
        else if (command_valid(&pair, command) && command->remaining_time < 0)
            exec_command(&pair, command);
        node = node->next;
    }
    clock_gettime(0, &t);
}