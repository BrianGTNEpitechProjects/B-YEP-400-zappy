/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** Zappy
*/

#include <stdlib.h>
#include "zserver.h"

trantorian_t *accept_player(zappy_t *zap) {
    trantorian_t *res = calloc(sizeof(*res), 1);

    if (res == NULL) {
        handle_error_return("calloc: %s\n", 0);
        return (NULL);
    }
    res->base.on_disconnect = &on_disconnect;
    res->base.on_extracted = &on_extract_not_connected;
    res->zappy = zap;
    return (res);
}