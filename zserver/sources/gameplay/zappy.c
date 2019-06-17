/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** zappy.c
*/

#include <stdlib.h>
#include <string.h>
#include "zserver.h"
#include "zcommands.h"

//TODO: maybe move this define elsewhere
#define COMMAND_NB (12)

const command_info_t commands[] = {
    {.code = EMPTY,         .command = NULL,            .callback = NULL},
    {.code = FORWARD,       .command = "Forward",       .callback = &forward},
    {.code = RIGHT,         .command = "Right",         .callback = &right},
    {.code = LEFT,          .command = "Left",          .callback = &left},
    {.code = LOOK,          .command = "Look",          .callback = &look},
    {.code = INVENTORY,     .command = "Inventory",     .callback = NULL},
    {.code = BROADCAST,     .command = "Broadcast",     .callback = NULL},
    {.code = CONNECT_NBR,   .command = "Connect_nbr",   .callback = NULL},
    {.code = FORK,          .command = "Fork",          .callback = NULL},
    {.code = EJECT,         .command = "Eject",         .callback = &eject},
    {.code = TAKE_OBJECT,   .command = "Take",          .callback = NULL},
    {.code = SET_OBJECT,    .command = "Set",           .callback = NULL},
    {.code = INCANTATION,   .command = "Incantation",   .callback = NULL},
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

static bool init_server(zappy_t *res, int port, int wsport)
{
    res->classic_id = add_server(res->nm, port);
    if (res->classic_id == invalid_id)
        return (false);
    if (wsport != 0) {
        res->websocket_id = add_server(res->nm, wsport);
        if (res->websocket_id == invalid_id)
            return (false);
    }
    return (true);
}

void on_disconnect(user_base_t *base, network_client_t *client)
{
    puts("client disconnect");
}

static int emplace_command(trantorian_t *player, e_command_t id, char *arg)
{
    int ind;

    for (int i = 0; i < COMMAND_QUEUE_LEN; i++) {
        ind = (player->command_ind + i) % COMMAND_QUEUE_LEN;
        if (player->queue[ind].code == EMPTY) {
            player->queue[ind].code = id;
            strcpy(player->queue[ind].arg, arg);
            return (i);
        }
    }
    return (-1);
}

void on_extract(user_base_t *b, network_client_t *c, uint8_t *data, size_t sz)
{
    int i;
    size_t separator_ind = strcspn(data, " \n");
    char *arg;
    client_user_pair_t pair = {c, b};

#ifdef DEBUG_PRINT_RECV
    printf("RECEIVED: %.*s\n", (int)sz, data);
#endif
    for (i = 1; i <= COMMAND_NB; i++)
        if (strncmp(data, commands[i].command, separator_ind) == 0)
            break;
    if (data[separator_ind] == '\n')
        arg = "";
    else
        arg = (char *)&(data[separator_ind + 1]);
    data[sz - 1] = '\0';
    if (i <= COMMAND_NB && emplace_command((trantorian_t *)b, i, arg) < 0)
        write_to_buffer(&c->cb_out, KO_MSG, KO_MSG_LEN);
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
    if (init_server(res, args->port, args->wsport) == false) {
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
    args_t arguments = DEFAULT_ARGS;
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