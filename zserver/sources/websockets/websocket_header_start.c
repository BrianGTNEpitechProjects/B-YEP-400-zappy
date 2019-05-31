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