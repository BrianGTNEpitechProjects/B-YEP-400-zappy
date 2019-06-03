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
    free(zappy);
}

static bool init_server(zappy_t *res, int port) {
    res->classic_id = add_server(res->nm, port);
    if (res->classic_id == invalid_id)
        return (false);
    //TODO Websocket server
    return (true);
}

static zappy_t *create_zappy(args_t *args)
{
    zappy_t *res = calloc(sizeof(*res), 1);

    if (res == NULL)
        return (NULL);
    res->nm = create_manager();
    res->map = create_map(args->x, args->y);
    res->players = calloc(sizeof(*res->players), args->tc * args->ppt);
    if (res->nm == NULL || res->map == NULL || res->players == NULL) {
        delete_zappy(res);
        return (NULL);
    }
    if (init_server(res, args->port) == false) {
        delete_zappy(res);
        return (NULL);
    }
    res->teams = (team_t *)args->teams;
    res->map_size.x = args->x;
    res->map_size.y = args->y;
    return (res);
}

bool run_zappy(zappy_t *zap) {
    network_server_t *server = get_server(zap->nm, zap->classic_id);

    if (server == NULL)
        return (false);
    setup_catch_signals();
    while (running()) {
        update_manager(zap->nm);
        extract_to_users(server, ZAPPY_DELIM, ZAPPY_DELIM_SIZE);
    }
    remove_sig_catch();
    return (true);
}

bool zappy(int ac, char **av)
{
    args_t arguments = {0};
    zappy_t *zap = NULL;
    bool ret = false;

    if (parse_args(&arguments, ac, av) == false)
        return (ret);
    zap = create_zappy(&arguments);
    if (zap == NULL) {
        free(arguments.teams);
        return (ret);
    }
    ret = run_zappy(zap);
    delete_zappy(zap);
    free(arguments.teams);
    return (ret);
}