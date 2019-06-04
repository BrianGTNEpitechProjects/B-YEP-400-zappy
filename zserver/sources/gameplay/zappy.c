/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** zappy.c
*/

#include <stdlib.h>
#include "zserver.h"
#include "zcommands.h"

const command_info_t commands[] = {
    {.code = EMPTY, .command = NULL, .callback = NULL},
    {.code = FORWARD, .command = "Forward", .callback = &forward},
    {.code = RIGHT, .command = "Right", .callback = NULL},
    {.code = LEFT, .command = "Left", .callback = NULL},
    {.code = LOOK, .command = "Look", .callback = NULL},
    {.code = INVENTORY, .command = "Inventory", .callback = NULL},
    {.code = BROADCAST, .command = "Broadcast", .callback = NULL},
    {.code = CONNECT_NBR, .command = "Connect_nbr", .callback = NULL},
    {.code = FORK, .command = "Fork", .callback = NULL},
    {.code = EJECT, .command = "Eject", .callback = NULL},
    {.code = TAKE_OBJECT, .command = "Take", .callback = NULL},
    {.code = SET_OBJECT, .command = "Set", .callback = NULL},
    {.code = INCANTATION, .command = "Incantation", .callback = NULL},
};

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

static bool init_server(zappy_t *res, int port)
{
    res->classic_id = add_server(res->nm, port);
    if (res->classic_id == invalid_id)
        return (false);
    //TODO Websocket server
    return (true);
}

void on_disconnect(user_base_t *base, network_client_t *client)
{
    puts("client disconnect");
}

void on_extract(user_base_t *base, network_client_t *client, uint8_t *data, size_t size)
{
#ifdef DEBUG_PRINT_RECV
    printf("%.*s\n", (int)size, data);
#endif
}

static zappy_t *create_zappy(args_t *args)
{
    zappy_t *res = calloc(sizeof(*res), 1);

    if (res == NULL)
        return (NULL);
    res->nm = create_manager();
    res->map = create_map(args->x, args->y);
    res->players = calloc(sizeof(*res->players), args->tc * args->ppt);
    for (int i = 0; i < args->tc * args->ppt; i++) {
        res->players->base.on_extracted = &on_extract;
        res->players->base.on_disconnect = &on_disconnect;
    }
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