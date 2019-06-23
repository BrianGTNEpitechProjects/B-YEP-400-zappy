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
    if (zappy->teams != NULL)
        free(zappy->teams);
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
    res->websocket_id = (id_t)-1;
    if (args->wsport != 0) {
        res->websocket_id = add_server(res->nm, args->wsport);
        if (res->websocket_id == invalid_id)
            return (false);
    }
    return (true);
}

static bool create_teams(zappy_t *res, args_t *args) {
    uint size = 0;

    for (; args->teams[size]; size++);
    res->teams = calloc(size + 1, sizeof(team_t));
    if (res->teams == NULL)
        return (bool)(handle_error_return("calloc: %s\n", 0));
    for (id_t i = 0; i < size; i++) {
        res->teams[i].id = i;
        res->teams[i].name = args->teams[i];
    }
    res->teams[size].id = invalid_id;
    return (true);
}

static zappy_t *create_zappy(args_t *args)
{
    zappy_t *res = calloc(sizeof(*res), 1);

    if (res == NULL)
        return (NULL);
    res->nm = create_manager();
    res->map = create_map(args->x, args->y);
    if (res->nm == NULL || res->map == NULL || init_server(res, args) == false
|| create_teams(res, args) == false) {
        delete_zappy(res);
        return (NULL);
    }
    res->natural_spawn_activated = true;
    res->default_slots_teams = args->ppt;
    res->time_scale = args->freq;
    res->map_size.x = args->x;
    res->map_size.y = args->y;
    res->case_sensitive_inputs = true;
    res->resources_spawn_cap = DEFAULT_RESOURCES_CAP;
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
    srandom((unsigned int)time(NULL));
    ret = run_zappy(zap);
    delete_zappy(zap);
    free(arguments.teams);
    return (ret);
}