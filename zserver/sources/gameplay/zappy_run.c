/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** Zappy
*/

#include <stdlib.h>
#include <time.h>
#include "zserver.h"
#include "cli.h"
#include "zcommands.h"
#include "graphical_protocol.h"

static void process_welcome_procedure(zappy_t *zap, network_server_t *server)
{
    client_user_pair_t *client = NULL;

    do {
        client = get_next_client_without_user(server->client_user_map);
        if (!client)
            return;
        client->user = (user_base_t *) accept_player(zap);
        if (client->user == NULL)
            return;
                write_to_buffer(&client->client->cb_out, \
(uint8_t *)WELCOME_MSG, WELCOME_MSG_LEN);
    } while (1);
}

void init_spawn_timeouts(zappy_t *res)
{
    double scaled;

    for (e_item_t i = 0; i < TOT_ITEM_NB; i++) {
        scaled = item_map[i].spawn_frequency / res->time_scale;
        set_timeout(&(res->resources_spawn[i]), scaled);
    }
    set_min_timeout(res, res->resources_spawn);
}

bool run_zappy(zappy_t *zap)
{
    network_server_t *server = get_server(zap->nm, zap->classic_id);

    if (server == NULL)
        return (false);
    setup_catch_signals();
    while (running()) {
        if (update_manager(zap->nm))
            handle_stdin(zap);
        extract_to_users(server, (uint8_t *)ZAPPY_DELIM, ZAPPY_DELIM_SIZE);
        process_welcome_procedure(zap, server);
        process_command_on_users(zap, server->client_user_map);
        process_spawn_resources(zap);
        update_ws_server(zap);
        check_end_game(zap);
    }
    remove_sig_catch();
    return (true);
}