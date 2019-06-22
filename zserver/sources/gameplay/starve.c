/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include "zserver.h"

void starve(client_user_pair_t *c)
{
    trantorian_t *trantorian = (trantorian_t *)c->user;

    if (0 < trantorian->inventory[FOOD])
        trantorian->inventory[FOOD] -= 1;
    else
        trantorian->life_unit -= 1;
    if (trantorian->life_unit <= 0) {
        kill_client(c);
        return;
    } else
        trantorian->food_time = FOOD_TTL;
}