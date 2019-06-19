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
#include "cli.h"
#include "graphical_protocol.h"

//TODO: norm -> too many fx

const command_info_t commands[] = {
    {
        .code = EMPTY,
        .command = NULL,
        .charge_time = 0,
        .need_arg = false,
        .is_startable = &always_true,
        .is_valid = &always_true,
        .callback = NULL
    },
    {
        .code = FORWARD,
        .command = "Forward",
        .charge_time = 7,
        .need_arg = false,
        .is_startable = &always_true,
        .is_valid = &always_true,
        .callback = &forward
    },
    {
        .code = RIGHT,
        .command = "Right",
        .charge_time = 7,
        .need_arg = false,
        .is_startable = &always_true,
        .is_valid = &always_true,
        .callback = &right
    },
    {
        .code = LEFT,
        .command = "Left",
        .charge_time = 7,
        .need_arg = false,
        .is_startable = &always_true,
        .is_valid = &always_true,
        .callback = &left
    },
    {
        .code = LOOK,
        .command = "Look",
        .charge_time = 7,
        .need_arg = false,
        .is_startable = &always_true,
        .is_valid = &always_true,
        .callback = &look
    },
    {
        .code = INVENTORY,
        .command = "Inventory",
        .charge_time = 1,
        .need_arg = false,
        .is_startable = &always_true,
        .is_valid = &always_true,
        .callback = &inventory
    },
    {
        .code = BROADCAST,
        .command = "Broadcast",
        .charge_time = 7,
        .need_arg = true,
        .is_startable = &always_true,
        .is_valid = &always_true,
        .callback = &broadcast
    },
    {
        .code = CONNECT_NBR,
        .command = "Connect_nbr",
        .charge_time = 0,
        .need_arg = false,
        .is_startable = &always_true,
        .is_valid = &always_true,
        .callback = &connect_nbr
    },
    {
        .code = FORK,
        .command = "Fork",
        .charge_time = 42,
        .need_arg = false,
        .is_startable = &fork_start,
        .is_valid = &always_true,
        .callback = &fork_command
    },
    {
        .code = EJECT,
        .command = "Eject",
        .charge_time = 7,
        .need_arg = false,
        .is_startable = &always_true,
        .is_valid = &always_true,
        .callback = &eject
    },
    {
        .code = TAKE_OBJECT,
        .command = "Take",
        .charge_time = 7,
        .need_arg = true,
        .is_startable = &take_valid,
        .is_valid = &always_true,
        .callback = &take_object
    },
    {
        .code = SET_OBJECT,
        .command = "Set",
        .charge_time = 7,
        .need_arg = true,
        .is_startable = &always_true,
        .is_valid = &always_true,
        .callback = &put_object
    },
    {
        .code = INCANTATION,
        .command = "Incantation",
        .charge_time = 300,
        .need_arg = false,
        .is_startable = &incantation_startable,
        .is_valid = &always_true,
        .callback = &incantation
    },
    {
        .code = HATCH,
        .command = "Hatch Egg",
        .charge_time = 600,
        .need_arg = false,
        .is_startable = &always_true,
        .is_valid = &always_true,
        .callback = &hatch_egg
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

static bool init_server(zappy_t *res, args_t *args)
{
    network_server_t *server = NULL;

    if (args->interactive_mode) {
        res->nm->timeout_on_stdin = true;
        print_cli_welcome();
    }
    res->classic_id = add_server(res->nm, args->port);
    if (res->classic_id == invalid_id)
        return (false);
    server = get_server(res->nm, res->classic_id);
    server->default_client_disconnect_timeout = 60;
    if (args->wsport != 0) {
        res->websocket_id = add_server(res->nm, args->wsport);
        if (res->websocket_id == invalid_id)
            return (false);
    }
    return (true);
}

void on_disconnect(user_base_t *base, __attribute__((unused)) \
network_client_t *client)
{
    trantorian_t *trantorian = (trantorian_t *)base;

    trantorian_move(trantorian, NULL);
    if (trantorian->zappy->players == trantorian) {
        trantorian->zappy->players = trantorian->next;
        free(trantorian);
        return;
    }
    for (trantorian_t *t = trantorian->zappy->players; t; t = t->next) {
        if (t->next == trantorian) {
            t->next = trantorian->next;
            free(trantorian);
            return;
        }
    }
}
void on_extract_not_connected(user_base_t *b, network_client_t *c, \
uint8_t *data, size_t sz)
{
    client_user_pair_t pair = {c, b};
    trantorian_t *tranto = ((trantorian_t *)b);

    if (c->has_overflow) {
        kill_client(&pair);
        return;
    }
    data[sz - 1] = 0;
    for (int i = 0; tranto->zappy->teams[i].name != NULL; i++) {
        if (strcmp((char *) data, tranto->zappy->teams[i].name) == 0)
            tranto = add_user_to_team(&pair, tranto->zappy->teams[i].name);
    }
    if (tranto->team.name == NULL) {
        write_to_buffer(&pair.client->cb_out, KO_MSG, KO_MSG_LEN);
    } else {
        response_success_connection((trantorian_t *)b, c);
        b->on_extracted = &on_extract_connected;
    }
}

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
    if (init_server(res, args) == false) {
        delete_zappy(res);
        return (NULL);
    }
    res->default_slots_teams = args->ppt;
    res->time_scale = args->freq;
    res->teams = (team_t *)args->teams;
    res->map_size.x = args->x;
    res->map_size.y = args->y;
    init_spawn_timeouts(res);
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
    srandom(time(NULL));
    ret = run_zappy(zap);
    delete_zappy(zap);
    free(arguments.teams);
    return (ret);
}