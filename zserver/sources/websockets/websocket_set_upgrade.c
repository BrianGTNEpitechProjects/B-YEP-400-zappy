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