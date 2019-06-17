/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include "zcommands.h"
#include "zworld.h"

const uint8_t OK_MSG[] = "ok\n";
const size_t OK_MSG_LEN = sizeof(OK_MSG);

const uint8_t KO_MSG[] = "ko\n";
const size_t KO_MSG_LEN = sizeof(KO_MSG);

const item_t item_map[] = {
    {LINEMATE,  (const uint8_t *)"Linemate"},
    {DERAUMERE, (const uint8_t *)"Deraumere"},
    {SIBUR,     (const uint8_t *)"Sibur"},
    {MENDIANE,  (const uint8_t *)"Mendiane"},
    {PHIRAS,    (const uint8_t *)"Phiras"},
    {THYSTAME,  (const uint8_t *)"Thystame"}
};