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
        update_ws_server(zap);
    }
    remove_sig_catch();
    return (true);
}