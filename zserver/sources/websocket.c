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

void DumpHex(const void* data, size_t size) {
    char ascii[17];
    size_t i, j;
    ascii[16] = '\0';
    for (i = 0; i < size; ++i) {
        printf("%02X ", ((unsigned char*)data)[i]);
        if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~') {
            ascii[i % 16] = ((unsigned char*)data)[i];
        } else {
            ascii[i % 16] = '.';
        }
        if ((i+1) % 8 == 0 || i+1 == size) {
            printf(" ");
            if ((i+1) % 16 == 0) {
                printf("|  %s \n", ascii);
            } else if (i+1 == size) {
                ascii[(i+1) % 16] = '\0';
                if ((i+1) % 16 <= 8) {
                    printf(" ");
                }
                for (j = (i+1) % 16; j < 16; ++j) {
                    printf("   ");
                }
                printf("|  %s \n", ascii);
            }
        }
    }
}

void parse_websocket_protocol(char *extracted, struct zuser *user, network_client_t *client)
{
    int match = 0;
    regex_t preg = {0};
    regmatch_t regmatch[10] = {0};
    int err = 0;

    if (user->sock_type == CLASSIC)
        return;
    DumpHex(extracted, strlen(extracted));
    for (int i = 0; header_lines[i].line_regex != NULL; i++) {
        //TODO: Norme (Regex manager)
        err = regcomp(&preg, header_lines[i].line_regex, REG_EXTENDED);
        if (!err) {
            match = regexec(&preg, extracted, 10, regmatch, 0);
            printf("%i %s\n", match, header_lines[i].line_regex);
            if (match == 0) {
                header_lines[i].func(extracted, user, regmatch, client);
            }
        }
    }
}

void header_start(char *extracted, struct zuser *user,
        regmatch_t *regex, __attribute__((unused)) network_client_t *client)
{
    int size;
    char *tmp;

    if (user->sock_type == UNDEFINED) {
        user->websocket_hdr = calloc(1, sizeof(*user->websocket_hdr));
        if (user->websocket_hdr == NULL)
            return;
        size = regex[1].rm_eo - regex[1].rm_so;
        tmp = calloc(size + 1, sizeof(*tmp));
        if (tmp == NULL) {
            free(user->websocket_hdr);
            return;
        }
        memcpy(tmp, extracted + regex[1].rm_so, size);
        user->sock_type = WEBSOCKET_INIT;
        user->websocket_hdr->http_version = tmp;
    }
}

void set_upgrade(char *extracted, struct zuser *user,
        regmatch_t *regex, __attribute__((unused)) network_client_t *client)
{
    int size;
    char *tmp;

    if (user->sock_type == WEBSOCKET_INIT) {
        size = regex[1].rm_eo - regex[1].rm_so;
        tmp = calloc(size + 1, sizeof(*tmp));
        if (tmp == NULL) {
            return;
        }
        memcpy(tmp, extracted + regex[1].rm_so, size);
        user->websocket_hdr->upgrade = tmp;
    }
}

void set_connection(char *extracted, struct zuser *user,
        regmatch_t *regex, __attribute__((unused)) network_client_t *client)
{
    int size;
    char *tmp;

    if (user->sock_type == WEBSOCKET_INIT) {
        size = regex[1].rm_eo - regex[1].rm_so;
        tmp = calloc(size + 1, sizeof(*tmp));
        if (tmp == NULL) {
            return;
        }
        memcpy(tmp, extracted + regex[1].rm_so, size);
        user->websocket_hdr->connection = tmp;
    }
}

void set_key(char *extracted, struct zuser *user,
        regmatch_t *regex, __attribute__((unused)) network_client_t *client)
{
    int size;
    char *tmp;

    if (user->sock_type == WEBSOCKET_INIT) {
        size = regex[1].rm_eo - regex[1].rm_so;
        tmp = calloc(size + 1, sizeof(*tmp));
        if (tmp == NULL) {
            return;
        }
        memcpy(tmp, extracted + regex[1].rm_so, size);
        user->websocket_hdr->key = tmp;
    }
}

void header_end(__attribute__((unused)) char *extracted, struct zuser *user,
                __attribute__((unused)) regmatch_t *regex, __attribute__((unused)) network_client_t *client)
{
    char *magic = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    char *res = calloc(strlen(magic) + strlen(user->websocket_hdr->key) + 1, sizeof(*res));
    unsigned char hash[SHA_DIGEST_LENGTH];

    write_to_buffer(&client->cb_out, (uint8_t *) user->websocket_hdr->http_version, strlen(user->websocket_hdr->http_version));
    write_to_buffer(&client->cb_out, (uint8_t *) " 101 Switching Protocols\r\n", 26);
    if (user->websocket_hdr->upgrade) {
        write_to_buffer(&client->cb_out, (uint8_t *) "Upgrade: ", 9);
        write_to_buffer(&client->cb_out, (uint8_t *) user->websocket_hdr->upgrade, strlen(user->websocket_hdr->upgrade));
        write_to_buffer(&client->cb_out, (uint8_t *) "\r\n", 2);
    }
    if (user->websocket_hdr->connection) {
        write_to_buffer(&client->cb_out, (uint8_t *) "Connection: ", 12);
        write_to_buffer(&client->cb_out, (uint8_t *) user->websocket_hdr->connection, strlen(user->websocket_hdr->connection));
        write_to_buffer(&client->cb_out, (uint8_t *) "\r\n", 2);
    }
    strcat(res, user->websocket_hdr->key);
    strcat(res, magic);

    printf("%s\n", res);
    SHA1((unsigned char *) res, strlen(res), hash);
    char *base64 = base64_encode(hash, SHA_DIGEST_LENGTH);
    printf("%s\n", base64);

    write_to_buffer(&client->cb_out, (uint8_t *) "Sec-WebSocket-Accept: ", 22);
    printf("=> %i\n", get_base64_size(SHA_DIGEST_LENGTH));
    write_to_buffer(&client->cb_out, (uint8_t *) base64, get_base64_size(SHA_DIGEST_LENGTH));

    write_to_buffer(&client->cb_out, (uint8_t *) "\r\n", 2);
    write_to_buffer(&client->cb_out, (uint8_t *) "\r\n", 2);
    printf("\n");
}