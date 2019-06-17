/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** websocket_header_start.c
*/

/* Created the 31/05/2019 at 11:33 by brian */

#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include "network_manager.h"
#include "zserver.h"

static void send_header(zuser_ws_t *user, network_client_t *client)
{
    char *str = user->websocket_hdr->http_version;

    write_to_buffer(&client->cb_out, (uint8_t *) str, strlen(str));
    str = " 101 Switching Protocols\r\n";
    write_to_buffer(&client->cb_out, (uint8_t *) str, strlen(str));
}

static void send_upgrade(zuser_ws_t *user, network_client_t *client)
{
    char *str = "Upgrade: ";

    write_to_buffer(&client->cb_out, (uint8_t *) str, strlen(str));
    str = user->websocket_hdr->upgrade;
    write_to_buffer(&client->cb_out, (uint8_t *) str, strlen(str));
    write_to_buffer(&client->cb_out, (uint8_t *) "\r\n", 2);
}

static void send_connection(zuser_ws_t *user, network_client_t *client)
{
    char *str = "Connection: ";

    write_to_buffer(&client->cb_out, (uint8_t *) str, strlen(str));
    str = user->websocket_hdr->connection;
    write_to_buffer(&client->cb_out, (uint8_t *) str, strlen(str));
    write_to_buffer(&client->cb_out, (uint8_t *) "\r\n", 2);
}

static void send_accept(zuser_ws_t *user, network_client_t *client)
{
    char *magic = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    char *key = user->websocket_hdr->key;
    char *res = calloc(strlen(magic) + strlen(key) + 1, sizeof(*res));
    unsigned char hash[SHA_DIGEST_LENGTH];
    const size_t size = get_base64_size(SHA_DIGEST_LENGTH);

    if (res == NULL)
        return;
    strcat(res, key);
    strcat(res, magic);
    SHA1((unsigned char *) res, strlen(res), hash);
    free(res);
    char *base64 = base64_encode(hash, SHA_DIGEST_LENGTH);
    if (base64 == NULL)
        return;
    write_to_buffer(&client->cb_out, (uint8_t *) "Sec-WebSocket-Accept: ", 22);
    write_to_buffer(&client->cb_out, (uint8_t *) base64, size);
    write_to_buffer(&client->cb_out, (uint8_t *) "\r\n", 2);
    free(base64);
}

void header_end(__attribute__((unused)) char *extracted, zuser_ws_t *user,
    __attribute__((unused)) regmatch_t *regex, network_client_t *client)
{
    send_header(user, client);
    if (user->websocket_hdr->upgrade)
        send_upgrade(user, client);
    if (user->websocket_hdr->connection)
        send_connection(user, client);
    send_accept(user, client);
    write_to_buffer(&client->cb_out, (uint8_t *) "\r\n", 2);
    user->sock_type = WEBSOCKET;
}