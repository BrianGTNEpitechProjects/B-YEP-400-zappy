/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** graphical_user.c
*/

/* Created the 17/06/2019 at 17:00 by jfrabel */

#include <stdlib.h>
#include "graphical_protocol.h"

static void graphical_user_websocket_handshake(graphical_user_t *guser,
    network_client_t *client, uint8_t *data, size_t data_size)
{
    if (!data_isalnum(data, data_size))
        return;
    parse_websocket_protocol((char *)data, (zuser_ws_t *)guser, client);
}

static void graphical_user_on_extracted(user_base_t *user,
    network_client_t *client, uint8_t *data, size_t data_size)
{
    graphical_user_t *guser = (graphical_user_t *)user;

#ifdef GRAPHICAL_SERVER_DEBUG
    printf("[DEBUG][graphical_user_on_extracted] received from user\n[");
    for (size_t i = 0; i < data_size; ++i)
        printf("%x%s", data[i], (i + 1 == data_size) ? "" : " ");
    printf("]\n[");
    for (size_t i = 0; i < data_size; ++i)
        printf("%c", data[i]);
    printf("]\n");
#endif
    if (guser->base.sock_type == WEBSOCKET) {
        send_websocket(client, (uint8_t *)"already authentificated", 23, 1);
    } else {
        graphical_user_websocket_handshake(guser, client, data, data_size);
    }
}

static void graphical_user_on_disconnected(user_base_t *user,
    UNUSED network_client_t *client)
{
#ifdef GRAPHICAL_SERVER_DEBUG
    puts("[DEBUG][graphical_user_on_disconnected] user disconnected.");
#endif
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
    new_user->base.base.user_event_timeout = 0;
    new_user->base.base.on_extracted = &graphical_user_on_extracted;
    new_user->base.base.on_disconnect = &graphical_user_on_disconnected;
    return (new_user);
}

void delete_graphical_user(graphical_user_t *user)
{
    free(user);
}