/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** ppo.c
*/

/* Created the 17/06/2019 at 20:05 by jfrabel */

#include <stdlib.h>
#include <string.h>
#include "graphical_protocol.h"

static bool send_awnser(graphical_user_t *user,
    network_client_t *client, long id)
{
    char awnser[53] = {0};
    size_t awnser_size = 0;
    trantorian_t *trantorian = find_trantorian_by_id(user->world_infos, id);
    int x;
    int y;
    int o;

    if (trantorian == NULL || trantorian->pos == NULL)
        return (false);
    x = trantorian->pos->coords.x;
    y = trantorian->pos->coords.y;
    o = cardinal_to_int(trantorian->orientation);
    awnser_size = snprintf(awnser, 52, "ppo %i %i %i %i\n", (int)id, x, y, o);
    send_websocket(client, (uint8_t *)awnser, awnser_size, 1);
    return (true);
}

static long extract_number(char *data, bool *validator)
{
    regex_t preg = {0};
    regmatch_t regmatch[10] = {0};
    char *nb_start = strstr(data, "#") + 1;
    long nb;
    char *end_ptr = NULL;

    if (regcomp(&preg, "^ppo #[0-9]{1,11}\n", REG_EXTENDED))
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

bool ppo(graphical_user_t *user, network_client_t *client,
    uint8_t *data, size_t size)
{
    bool is_valid_number = true;
    char extracted[C_BUFFER_SIZE + 1] = {0};
    long player_nb;

    memcpy(extracted, data, size);
    player_nb = extract_number(extracted, &is_valid_number);
    if (!is_valid_number)
        return (false);
    return (send_awnser(user, client, player_nb));
}