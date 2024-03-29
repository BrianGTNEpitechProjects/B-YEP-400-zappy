/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** graphical_user.c
*/

/* Created the 17/06/2019 at 17:00 by jfrabel */

#include <stdlib.h>
#include <string.h>
#include "graphical_protocol.h"

static void graphical_user_websocket_handshake(graphical_user_t *guser,
    network_client_t *client, uint8_t *data, size_t data_size)
{
    char extracted_as_char[C_BUFFER_SIZE + 1] = {0};

    if (!check_data_encoding(data, data_size))
        return;
    memcpy(extracted_as_char, data, data_size);
    parse_websocket_protocol(extracted_as_char, (zuser_ws_t *)guser, client);
}

static void graphical_user_on_extracted(user_base_t *user,
    network_client_t *client, uint8_t *data, size_t data_size)
{
    graphical_user_t *guser = (graphical_user_t *)user;

    if (guser->base.sock_type == WEBSOCKET) {
        handle_graphical_user_cmd(guser, client, data, data_size);
    } else {
        graphical_user_websocket_handshake(guser, client, data, data_size);
    }
    if (client->has_overflow)
        client->should_disconnect = 1;
}

static void graphical_user_on_disconnected(user_base_t *user,
    UNUSED network_client_t *client)
{
    delete_graphical_user((graphical_user_t *)user);
}

graphical_user_t *create_new_graphical_user(zappy_t *world_data)
{
    graphical_user_t *new_user = malloc(sizeof(*new_user));

    if (new_user == NULL)
        return (NULL);
    new_user->world_infos = world_data;
    new_user->base.websocket_hdr = NULL;
    new_user->base.sock_type = UNDEFINED;
    new_user->base.base.user_event_timeout.tv_sec = 0;
    new_user->base.base.user_event_timeout.tv_usec = 0;
    new_user->base.base.on_extracted = &graphical_user_on_extracted;
    new_user->base.base.on_disconnect = &graphical_user_on_disconnected;
    return (new_user);
}

void delete_graphical_user(graphical_user_t *user)
{
    if (user != NULL) {
        if (user->base.websocket_hdr) {
            free(user->base.websocket_hdr->connection);
            free(user->base.websocket_hdr->http_version);
            free(user->base.websocket_hdr->key);
            free(user->base.websocket_hdr->upgrade);
        }
        free(user->base.websocket_hdr);
    }
    free(user);
}