/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <stdlib.h>
#include "zserver.h"
#include "graphical_protocol.h"

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
        write_to_client(client, (uint8_t *)"WELCOME\n", sizeof("WELCOME\n"));
    } while (1);
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
        update_ws_server(zap);
    }
    remove_sig_catch();
    return (true);
}