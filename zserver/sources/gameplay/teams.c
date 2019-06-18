/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** teams.c
*/

#include <string.h>
#include <stdio.h>
#include <regex.h>
#include "zserver.h"
#include "common.h"
#include "network_client.h"
#include "network_user_base.h"
#include "network_manager.h"
#include "zworld.h"

int count_unused_slot(zappy_t *zap, char *team_name)
{
    int total = 0;
    int res = zap->default_slots_teams;

    for (trantorian_t *node = zap->players; node; node = node->next) {
        if (strcmp(node->team.name, team_name) == 0) {
            if (node->is_egg && node->base.on_extracted == NULL) {
                res++;
            } else {
                total++;
            }
        }
    }
    return (res - total);
}

int count_players_team(zappy_t *zap, char *team_name)
{
    int players = 0;

    for (trantorian_t *curr = zap->players; curr != NULL; curr = curr->next) {
        if (strcmp(team_name, curr->team.name) == 0)
            players++;
    }
    return (players);
}