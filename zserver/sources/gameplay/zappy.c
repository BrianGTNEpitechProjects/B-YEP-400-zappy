/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** zappy.c
*/

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "zserver.h"
#include "zcommands.h"

//TODO: norm -> too many fx

//TODO: maybe move this define elsewhere
#define COMMAND_NB (12)

const command_info_t commands[] = {
    {
        .code = EMPTY,
        .command = NULL,
        .charge_time = 0,
        .need_arg = false,
        .is_valid = &always_true,
        .callback = NULL
    },
    {
        .code = FORWARD,
        .command = "Forward",
        .charge_time = 7,
        .need_arg = false,
        .is_valid = &always_true,
        .callback = &forward
    },
    {
        .code = RIGHT,
        .command = "Right",
        .charge_time = 7,
        .need_arg = false,
        .is_valid = &always_true,
        .callback = &right
    },
    {
        .code = LEFT,
        .command = "Left",
        .charge_time = 7,
        .need_arg = false,
        .is_valid = &always_true,
        .callback = &left
    },
    {
        .code = LOOK,
        .command = "Look",
        .charge_time = 7,
        .need_arg = false,
        .is_valid = &always_true,
        .callback = &look
    },
    {
        .code = INVENTORY,
        .command = "Inventory",
        .charge_time = 1,
        .need_arg = false,
        .is_valid = &always_true,
        .callback = &inventory
    },
    {
        .code = BROADCAST,
        .command = "Broadcast",
        .charge_time = 7,
        .need_arg = true,
        .is_valid = &always_true,
        .callback = &broadcast
    },
    {
        .code = CONNECT_NBR,
        .command = "Connect_nbr",
        .charge_time = 0,
        .need_arg = false,
        .is_valid = &always_true,
        .callback = &connect_nbr
    },
    {
        .code = FORK,
        .command = "Fork",
        .charge_time = 42,
        .need_arg = false,
        .is_valid = &always_true,
        .callback = NULL
    },
    {
        .code = EJECT,
        .command = "Eject",
        .charge_time = 7,
        .need_arg = false,
        .is_valid = &always_true,
        .callback = &eject
    },
    {
        .code = TAKE_OBJECT,
        .command = "Take",
        .charge_time = 7,
        .need_arg = true,
        .is_valid = &always_true,
        .callback = &take_object
    },
    {
        .code = SET_OBJECT,
        .command = "Set",
        .charge_time = 7,
        .need_arg = true,
        .is_valid = &always_true,
        .callback = &put_object
    },
    {
        .code = INCANTATION,
        .command = "Incantation",
        .charge_time = 300,
        .need_arg = false,
        .is_valid = &always_true,
        .callback = NULL
    }
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
    network_server_t *server = NULL;

    res->classic_id = add_server(res->nm, port);
    if (res->classic_id == invalid_id)
        return (false);
    server = get_server(res->nm, res->classic_id);
    server->default_client_disconnect_timeout = 20;
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
    //TODO cleanup user from zappy
}

static int emplace_command(trantorian_t *player, e_command_t id, char *arg)
{
    int ind;

    for (int i = 0; i < COMMAND_QUEUE_LEN; i++) {
        ind = (player->command_ind + i) % COMMAND_QUEUE_LEN;
        if (player->queue[ind].code == EMPTY) {
            player->queue[ind].code = id;
            player->queue[ind].remaining_time = commands[id].charge_time;
            strcpy(player->queue[ind].arg, arg);
            printf("DEBUG: %d\n", ind);
            return (ind);
        }
    }
    printf("DEBUG: -1\n");
    return (-1);
}

void on_extract_connected(user_base_t *b, network_client_t *c, \
uint8_t *data, size_t sz)
{
    int i;
    size_t sep_ind = strcspn((char *)data, " \n");
    char *arg;

#ifdef DEBUG_PRINT_RECV
    printf("RECEIVED: %.*s\n", (int)sz - 1, data);
#endif
    if (c->has_overflow) {
        c->lost_connection = true;
        return;
    }
    for (i = 1; i <= COMMAND_NB; i++)
        if (sep_ind && \
strncmp(data, commands[i].command, strlen(commands[i].command)) == 0)
            break;
    arg = (data[sep_ind] == '\n') ? "" : (char *)&(data[sep_ind + 1]);
    data[sz - 1] = '\0';
    if (COMMAND_NB < i || (commands[i].need_arg && strlen(arg) == 0) || \
emplace_command((trantorian_t *)b, i, arg) < 0)
        write_to_buffer(&c->cb_out, KO_MSG, KO_MSG_LEN);
}

void on_extract_not_connected(user_base_t *b, network_client_t *c, \
uint8_t *data, size_t sz)
{
    client_user_pair_t pair = {c, b};
    trantorian_t *tranto = ((trantorian_t *)b);

    if (c->has_overflow) {
        c->lost_connection = true;
        return;
    }
    data[sz - 1] = 0;
    for (int i = 0; tranto->zappy->teams[i].name != NULL; i++) {
        if (strcmp((char *) data, tranto->zappy->teams[i].name) == 0)
            add_user_to_team(&pair, tranto->zappy->teams[i].name);
    }
    if (tranto->team.name == NULL) {
        write_to_buffer(&pair.client->cb_out, KO_MSG, KO_MSG_LEN);
    } else {
        response_success_connection((trantorian_t *)b, c);
        b->on_extracted = &on_extract_connected;
    }
}

//TODO: norm -> too long fx
static zappy_t *create_zappy(args_t *args)
{
    zappy_t *res = calloc(sizeof(*res), 1);

    if (res == NULL)
        return (NULL);
    res->nm = create_manager();
    res->map = create_map(args->x, args->y);
    if (res->nm == NULL || res->map == NULL) {
        delete_zappy(res);
        return (NULL);
    }
    if (init_server(res, args->port, args->wsport) == false) {
        delete_zappy(res);
        return (NULL);
    }
    res->default_slots_teams = args->ppt;
    res->time_scale = args->freq;
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
    srand(time(NULL));
    ret = run_zappy(zap);
    delete_zappy(zap);
    free(arguments.teams);
    return (ret);
}