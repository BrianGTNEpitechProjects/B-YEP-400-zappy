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
    int tot = 0;
    int if_no_eggs = zap->default_slots_teams;

    for (trantorian_t *node = zap->players; node; node = node->next) {
        if (team_name == NULL || strcmp(node->team.name, team_name) == 0) {
            tot += (node->base.on_disconnect == NULL);
            if_no_eggs -= (node->base.on_disconnect == NULL);
        }
    }
    return (tot < zap->default_slots_teams ? if_no_eggs : tot);
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