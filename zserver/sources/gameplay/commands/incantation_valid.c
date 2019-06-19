/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <stdbool.h>
#include "network_client_user_map.h"
#include "zcommands.h"
#include "graphical_protocol.h"

bool incantation_startable(client_user_pair_t *c, \
__attribute__((unused)) char *a)
{
    trantorian_t *player = c->user;

    if (incantation_valid(c, a)) {
        pic(player->zappy, player);
        return (true);
    } else {
        return (false);
    }
}
