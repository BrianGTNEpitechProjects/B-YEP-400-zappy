/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "zserver.h"

static inline void write_to_client(struct client_user_pair_s *client, \
                                   uint8_t *msg, \
                                   size_t len)
{
    write_to_buffer(&client->client->cb_out, msg, len);
}

static void process_welcome_procedure(zappy_t *zap, network_server_t *server)
{
    client_user_pair_t *client = NULL;

    do {
        client = get_next_client_without_user(server->client_user_map);
        if (!client)
            return;
        client->user = (user_base_t *)&zap->players[0];
        write_to_client(client, (uint8_t *)WELCOME_MSG, WELCOME_MSG_LEN);
    } while (1);
}

static void process_command_on_users(zappy_t *z, network_client_user_map_t *m)
{
    static clockid_t clk = 0;
    struct timespec time;
    trantorian_t *trantorian;
    command_t *command;

    clock_gettime(clk, &time);
    for (map_t node = m->client_user_map; node; node = node->next) {
        trantorian = (trantorian_t *)((client_user_pair_t *)node->value)->user;
        command = &(trantorian->queue[trantorian->command_ind]);
        command->remaining_time -= time.tv_sec * z->time_scale;
        command->remaining_time -= time.tv_nsec * \
((float)z->time_scale) / pow(10, 9);
        if (command->remaining_time < 0) {
            commands[command->code].callback(node->value, command->arg);
            ++trantorian->command_ind;
            command->code = EMPTY;
            memset(command->arg, 0, ARG_BUFFER_SIZE);
        }
    }
    clk = 0;
}

bool run_zappy(zappy_t *zap)
{
    network_server_t *server = get_server(zap->nm, zap->classic_id);

    if (server == NULL)
        return (false);
    setup_catch_signals();
    while (running()) {
        update_manager(zap->nm);
        extract_to_users(server, (uint8_t *)ZAPPY_DELIM, ZAPPY_DELIM_SIZE);
        process_welcome_procedure(zap, server);
        process_command_on_users(zap, server->client_user_map);
    }
    remove_sig_catch();
    return (true);
}