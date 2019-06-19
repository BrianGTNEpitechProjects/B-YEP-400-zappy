/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** sst.c
*/

/* Created the 17/06/2019 at 20:08 by jfrabel */

#include <stdlib.h>
#include <string.h>
#include "graphical_protocol.h"

static bool send_awnser(graphical_user_t *user,
    network_client_t *client, long new_time_unit)
{
    char awnser[53] = {0};
    size_t awnser_size = 0;
    int time_unit = new_time_unit;

    user->world_infos->time_scale = new_time_unit;
    awnser_size = snprintf(awnser, 52, "sst %i\n", time_unit);
    send_websocket(client, (uint8_t *)awnser, awnser_size, 1);
    return (true);
}

static long extract_number(char *data, bool *validator)
{
    regex_t preg = {0};
    regmatch_t regmatch[10] = {0};
    char *nb_start = strstr(data, " ") + 1;
    long nb;
    char *end_ptr = NULL;

    if (regcomp(&preg, "^sst [0-9]{1,11}\n", REG_EXTENDED))
        return (false);
    if (regexec(&preg, data, 10, regmatch, 0)) {
        regfree(&preg);
        *validator = false;
        return (0);
    }
    regfree(&preg);
    nb = strtol(nb_start, &end_ptr, 10);
    *validator = end_ptr != nb_start;
    return (nb);
}

bool sst(graphical_user_t *user, network_client_t *client,
    uint8_t *data, size_t size)
{
    bool is_valid_number = true;
    char extracted[C_BUFFER_SIZE + 1] = {0};
    long new_time_unit;

    memcpy(extracted, data, size);
    new_time_unit = extract_number(extracted, &is_valid_number);
    if (!is_valid_number || new_time_unit == 0)
        return (false);
    return (send_awnser(user, client, new_time_unit));
}