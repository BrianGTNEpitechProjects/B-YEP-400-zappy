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

void parse_websocket_protocol(char *extracted, struct zuser *user, network_client_t *client)
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
    }
}