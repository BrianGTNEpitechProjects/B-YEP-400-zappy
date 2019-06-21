/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include "zcommands.h"
#include "zworld.h"
#include "zitem.h"

const uint8_t OK_MSG[] = "ok\n";
const size_t OK_MSG_LEN = sizeof(OK_MSG);

const uint8_t KO_MSG[] = "ko\n";
const size_t KO_MSG_LEN = sizeof(KO_MSG);

const uint8_t WELCOME_MSG[] = "WELCOME\n";
const size_t WELCOME_MSG_LEN = sizeof(WELCOME_MSG);

const uint8_t DEAD_MSG[] = "dead\n";
const size_t DEAD_MSG_LEN = sizeof(DEAD_MSG);

const uint8_t CURR_MSG[] = "Current level: ";
const size_t CURR_MSG_LEN = sizeof(CURR_MSG);

const uint8_t INCANT_MSG[] = "Elevation underway\n";
const size_t INCANT_MSG_LEN = sizeof(INCANT_MSG);

const double resources_per_tile = 1.0 / 4.0;

const item_t item_map[TOT_ITEM_NB] = {
{.id = FOOD,      .name = (const uint8_t *)"Food", .spawn_frequency = 50},
{.id = LINEMATE,  .name = (const uint8_t *)"Linemate", .spawn_frequency = 50},
{.id = DERAUMERE, .name = (const uint8_t *)"Deraumere", .spawn_frequency = 60},
{.id = SIBUR,     .name = (const uint8_t *)"Sibur", .spawn_frequency = 70},
{.id = MENDIANE,  .name = (const uint8_t *)"Mendiane", .spawn_frequency = 80},
{.id = PHIRAS,    .name = (const uint8_t *)"Phiras", .spawn_frequency = 90},
{.id = THYSTAME,  .name = (const uint8_t *)"Thystame", .spawn_frequency = 100},
};