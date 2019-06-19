/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** network_user_base.h
*/

/* Created the 17/05/2019 at 19:30 by jfrabel */

#ifndef PSU_ZAPPY_2018_NETWORK_USER_BASE_H
#define PSU_ZAPPY_2018_NETWORK_USER_BASE_H

#include <stddef.h>
#include <stdint.h>
#include "network_client.h"

typedef struct user_base_s user_base_t;

typedef void (*on_extracted_func)(
    user_base_t *, network_client_t *, uint8_t *, size_t);
typedef void (*on_disconnect_func)(user_base_t *, network_client_t *);

struct user_base_s {
    on_extracted_func on_extracted;
    on_disconnect_func on_disconnect;
    struct timeval user_event_timeout;
};

#endif //PSU_ZAPPY_2018_NETWORK_USER_BASE_H
