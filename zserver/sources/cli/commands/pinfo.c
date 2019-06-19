/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** pinfo.c
*/

/* Created the 19/06/2019 at 04:22 by jfrabel */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cli.h"
#include "common.h"
#include "graphical_protocol.h"

static long extract_id(char *cmd, bool *validator)
{
    char *nb_start = strstr(cmd, " ") + 1;
    long nb;
    char *end_ptr = NULL;

    nb = strtol(nb_start, &end_ptr, 10);
    *validator = (*end_ptr == '\0');
    return (nb);
}

static void display_player(trantorian_t *player)
{
    char *item_str[] = {"food", "linemate", "deraumere", "sibur",
"mendiane", "phiras", "thystame"};
    char orientation[] = {'N', 'E', 'S', 'W'};

    printf("%s ", player->is_egg ? "Egg" : "Trantorian");
    printf("%i (%s)\n", player->id, player->team.name);
    printf("-HP %i\n", player->life_unit);
    printf("-Level %i\n", player->lvl);
    printf("-Position %i %i\n", player->pos->coords.x, player->pos->coords.y);
    printf("-Orientation: %i(%c)\n", cardinal_to_int(player->orientation),
orientation[player->orientation]);
    printf("Inventory:\n");
    for (int i = 0; i < 7; i++) {
        printf("-[%i](%s) => %i\n", i, item_str[i], player->inventory[i]);
    }
    printf("\n");
}

static void display_all_players(zappy_t *world)
{
    for (trantorian_t *curr = world->players; curr; curr = curr->next) {
        display_player(curr);
    }
}

bool cli_pinfo(zappy_t *world, char *cmd)
{
    bool is_valid_id;
    long id = 0;
    trantorian_t *player;

    if (strstr(cmd, " ") != NULL) {
        id = extract_id(cmd, &is_valid_id);
        player = find_trantorian_by_id(world, id);
        if (!is_valid_id || player == NULL)
            return (false);
        display_player(player);
    } else {
        display_all_players(world);
    }
    return (true);
}