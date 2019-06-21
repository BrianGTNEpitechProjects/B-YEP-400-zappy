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
    {FOOD,      (const uint8_t *)"Food",        5},
    {LINEMATE,  (const uint8_t *)"Linemate",    5},
    {DERAUMERE, (const uint8_t *)"Deraumere",   10},
    {SIBUR,     (const uint8_t *)"Sibur",       20},
    {MENDIANE,  (const uint8_t *)"Mendiane",    30},
    {PHIRAS,    (const uint8_t *)"Phiras",      40},
    {THYSTAME,  (const uint8_t *)"Thystame",    50},
};