/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** zappy.c
*/

#include <stdlib.h>
#include "zserver.h"

void delete_zappy(zappy_t *zappy)
{
    if (zappy == NULL)
        return;
    if (zappy->nm != NULL)
        delete_manager(zappy->nm);
    free(zappy->map);
    free(zappy->players);
}

static zappy_t *create_zappy(args_t *args){
    zappy_t *res = calloc(sizeof(*res), 1);

    if (res == NULL)
        return (NULL);
    res->nm = create_manager(args->port);
    res->map = create_map(args->x, args->y);
    res->players = calloc(sizeof(*res->players), args->tc * args->ppt);
    if (res->nm == NULL || res->map == NULL || res->players == NULL) {
        delete_zappy(res);
        return (NULL);
    }
    res->teams = (team_t *)args->teams;
    return (res);
}

bool zappy(int ac, char **av)
{
    args_t arguments = {0};
    zappy_t *zap = NULL;

    if (parse_args(&arguments, ac, av) == false)
        return (false);
    zap = create_zappy(&arguments);
    if (zap == NULL)
        return (false);
    delete_zappy(zap);
    return (true);
}