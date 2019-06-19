/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_manager_extract.c
*/

/* Created the 21/05/2019 at 15:07 by jfrabel */

#include "network_server.h"

static void run_extraction_loop(user_base_t *user, network_client_t *client,
    uint8_t *delim, size_t delim_size)
{
    uint8_t buffer[C_BUFFER_SIZE + 1] = {0};
    size_t size;

    do {
        size = read_from_buffer(&client->cb_in, buffer, delim, delim_size);
        if (size != (size_t)-1)
            user->on_extracted(user, client, buffer, size);
    } while (size != (size_t)-1);
}

void extract_to_users(network_server_t *ns, uint8_t *delim, size_t delim_size)
{
    network_client_t *client;
    user_base_t *user;
    map_t curr = ns->client_user_map->client_user_map;

    for (; curr; curr = curr->next) {
        user = ((client_user_pair_t *)curr->value)->user;
        if (user == NULL)
            continue;
        client = ((client_user_pair_t *)curr->value)->client;
        run_extraction_loop(user, client, delim, delim_size);
    }
}