/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** Avengers
*/

#include <string.h>
#include "zworld.h"
#include "zserver.h"
#include "graphical_protocol.h"

static team_t *get_normal_winner(zappy_t *zap)
{
    uint team_count = (uint)count_teams(zap);
    int max_level_players[team_count];

    memset(&max_level_players, 0, sizeof(uint) * team_count);
    for (trantorian_t *node = zap->players; node; node = node->next) {
        if (node->lvl == MAX_LEVEL)
            max_level_players[node->team->id]++;
        if (max_level_players[node->team->id] >= TEAM_PLAYERS_TO_WIN)
            return (node->team);
    }
    return (NULL);
}

static void add_if_greater(uint *array, uint level, uint size)
{
    uint min = 0;
    id_t min_id = invalid_id;

    for (uint i = 0; i < size; i++) {
        if (min < level) {
            min_id = i;
            min = level;
        }
    }
    if (min_id != invalid_id)
        array[min_id] = level;
}

static team_t *get_default_winners(zappy_t *zap)
{
    uint team_count = (uint)count_teams(zap);
    team_t *team = NULL;
    uint best_score = 0;
    uint team_score = 0;
    uint highest_players[team_count][TEAM_PLAYERS_TO_WIN];

    memset(&highest_players, 0, sizeof(uint) * team_count * \
TEAM_PLAYERS_TO_WIN);
    for (trantorian_t *node = zap->players; node; node = node->next)
        add_if_greater((uint *)&(highest_players[node->team->id]), \
node->lvl, TEAM_PLAYERS_TO_WIN);
    for (uint i = 0; i < team_count; i++) {
        for (uint j = 0; j < TEAM_PLAYERS_TO_WIN; j++)
            team_score += highest_players[i][j];
        if (team_score > best_score) {
            best_score = team_score;
            team = &(zap->teams[i]);
        }
    }
    return (team);
}

void end_game(zappy_t *zap, team_t *winners)
{
    if (winners == NULL)
        winners = get_default_winners(zap);
    if (winners == NULL) {
        printf("Draw\n");
        seg(zap, "drawn");
    } else {
        printf("Team %s (#%i) won !!!\n", winners->name, winners->id);
        seg(zap, winners->name);
    }
    shutdown_server();
}

void check_end_game(zappy_t *zap)
{
    team_t *winners = get_normal_winner(zap);

    if (winners != NULL) {
        end_game(zap, winners);
    }
}