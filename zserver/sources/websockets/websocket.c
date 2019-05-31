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

void send_websocket(network_client_t *client, uint8_t *data,
        size_t length)
{
    uint8_t to_write = 0b10000001;

    write_to_buffer(&client->cb_out, &to_write, 1);
    to_write = length & 0b011111111;
    write_to_buffer(&client->cb_out, &to_write, 1);
    write_to_buffer(&client->cb_out, data, length);
}

static void read_ws_client_data(struct zuser *user, network_client_t *client)
{
    uint8_t tmp[C_BUFFER_SIZE];
    size_t bytes_flushed = flush_buffer(&client->cb_in, tmp);
    size_t bytes_used = 0;
    char *str;
    size_t payload_size = 0;
    uint8_t *masking_key;
    bool need_mask = false;

    if (bytes_flushed <= 0)
        return;
    if ((tmp[0] & 0b00001111) != 1)
        return;
    need_mask = tmp[1] & 0b10000000;
    payload_size = tmp[1] & 0b01111111;
    str = calloc(payload_size, sizeof(*str));
    if (str == NULL)
        return;
    bytes_used = 2;
    if (need_mask)
        masking_key = (uint8_t[]) {tmp[2], tmp[3], tmp[4], tmp[5]};
    for (size_t i = 0; i < payload_size; i++) {
        char c = tmp[bytes_used - 1];
        if (need_mask)
            c ^= masking_key[i % 4];
        bytes_used++;
    }
    user->on_extracted((user_base_t *) user, client, (uint8_t *) str,
            payload_size);
    free(str);
}

void read_ws_clients_data(network_manager_t *nm)
{
    client_user_pair_t *pair = NULL;
    struct zuser *user = NULL;
    map_t map = nm->client_user_map->client_user_map;

    for (map_t curr = map; curr != NULL; curr = curr->next) {
        pair = curr->value;
        if (pair->user == NULL)
            continue;
        user = (struct zuser *) pair->user;
        if (user->sock_type == WEBSOCKET)
            read_ws_client_data((struct zuser *) pair->user, pair->client);
    }
}

void parse_websocket_protocol(char *extracted, struct zuser *user,
        network_client_t *client)
{
    int match = 0;
    regex_t preg = {0};
    regmatch_t regmatch[10] = {0};
    int err = 0;

    if (user->sock_type == CLASSIC)
        return;
    for (int i = 0; header_lines[i].line_regex != NULL; i++) {
        //TODO: Norme (Regex manager)
        err = regcomp(&preg, header_lines[i].line_regex, REG_EXTENDED);
        if (!err) {
            match = regexec(&preg, extracted, 10, regmatch, 0);
            if (match == 0) {
                header_lines[i].func(extracted, user, regmatch, client);
            }
        }
        regfree(&preg);
    }
}