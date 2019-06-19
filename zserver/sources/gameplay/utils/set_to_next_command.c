/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <string.h>
#include "zworld.h"
#include "zcommands.h"

void set_to_next_command(trantorian_t *t)
{
    command_t *command = &t->queue[t->command_ind];
    network_server_t *server = get_server(t->zappy->nm, t->zappy->classic_id);
    network_client_user_map_t *map = server->client_user_map;
    network_client_t *client = get_client(map, (user_base_t *)t);
    client_user_pair_t pair = {client, (user_base_t *)t};

    t->command_ind = \
(unsigned char)((t->command_ind + 1) % COMMAND_QUEUE_LEN);
    command->code = EMPTY;
    command->remaining_time = .0;
    memset(command->arg, 0, ARG_BUFFER_SIZE);
    if (!commands[t->queue[t->command_ind].code].is_startable(&pair, \
t->queue[t->command_ind].arg)) {
        write_to_buffer(&client->cb_out, KO_MSG, KO_MSG_LEN);
        set_to_next_command(t);
    }
}