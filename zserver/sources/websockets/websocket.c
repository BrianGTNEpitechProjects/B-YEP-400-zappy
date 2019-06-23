/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** websocket.c
*/

/* Created the 28/05/2019 at 13:14 by brian */

#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include "network_manager.h"
#include "zserver.h"

struct websocket_header_line header_lines[] = {
    {"GET \\/ (HTTP\\/[0-9\\.]+)", &header_start},
    {"Upgrade:[ \t]*([a-z]+)", &set_upgrade},
    {"Connection:[ \t]*([a-zA-Z]+)", &set_connection},
    {"Sec-WebSocket-Key:[ \t]*([a-zA-Z0-9\\+\\/\\=]+)", &set_key},
    {"^\r\n", &header_end},
    {NULL, NULL}
};

static char *send_readed(size_t size, uint8_t *tmp, size_t *bytes_used,
        uint8_t *masking_key)
{
    char *str = calloc(size, sizeof(*str));

    if (str == NULL)
        return (NULL);
    for (size_t i = 0; i < size; i++) {
        char c = tmp[++(*bytes_used) - 1];
        if (tmp[1] & 0b10000000) {
            c ^= masking_key[i % 4];
        }
        str[i] = c;
    }
    return (str);
}

static void read_ws_client_data(zuser_ws_t *user, network_client_t *client)
{
    uint8_t tmp[C_BUFFER_SIZE + 1] = {0};
    size_t sz_flushed = flush_buffer(&client->cb_in, tmp);
    size_t bu = 0;
    size_t size = 0;
    char *str = NULL;
    uint8_t *mask = NULL;

    while (bu < sz_flushed) {
        if (sz_flushed <= 0 || (tmp[bu++] & 0b00001111) > 2)
            return;
        size = tmp[bu] & 0b01111111;
        if (tmp[bu++] & 0b10000000)
            mask = (uint8_t[]) {tmp[bu++], tmp[bu++], tmp[bu++], tmp[bu++]};
        str = send_readed(size, tmp, &bu, mask);
        if (str == NULL)
            return;
        user->base.on_extracted((user_base_t *)user, client, (uint8_t *)str,
            size);
        free(str);
    }
}

void read_ws_clients_data(network_server_t *server)
{
    client_user_pair_t *pair = NULL;
    zuser_ws_t *user = NULL;
    map_t map = server->client_user_map->client_user_map;

    for (map_t curr = map; curr != NULL; curr = curr->next) {
        pair = curr->value;
        if (pair->user == NULL)
            continue;
        user = (zuser_ws_t *)pair->user;
        if (user->sock_type == WEBSOCKET)
            read_ws_client_data((zuser_ws_t *)pair->user, pair->client);
    }
}

void parse_websocket_protocol(char *extracted, zuser_ws_t *user,
        network_client_t *client)
{
    regex_t preg = {0};
    regmatch_t regmatch[10] = {0};

    if (user->sock_type == CLASSIC)
        return;
    for (int i = 0; header_lines[i].line_regex != NULL; i++) {
        if (!regcomp(&preg, header_lines[i].line_regex, REG_EXTENDED) &&
        !regexec(&preg, extracted, 10, regmatch, 0)) {
                header_lines[i].func(extracted, user, regmatch, client);
        }
        regfree(&preg);
    }
}