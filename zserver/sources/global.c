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

const item_t item_map[TOT_ITEM_NB] = {
    {.id = FOOD,        .name = (const uint8_t *)"Food"},
    {.id = LINEMATE,    .name = (const uint8_t *)"Linemate"},
    {.id = DERAUMERE,   .name = (const uint8_t *)"Deraumere"},
    {.id = SIBUR,       .name = (const uint8_t *)"Sibur"},
    {.id = MENDIANE,    .name = (const uint8_t *)"Mendiane"},
    {.id = PHIRAS,      .name = (const uint8_t *)"Phiras"},
    {.id = THYSTAME,    .name = (const uint8_t *)"Thystame"},
};