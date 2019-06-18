/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#ifndef PSU_ZAPPY_2018_ZITEM_H
#define PSU_ZAPPY_2018_ZITEM_H

#include <stdint.h>

/*
 * ITEM
 */
typedef enum {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    TOT_ITEM_NB
} e_item_t;
typedef struct {
    e_item_t id;
    const uint8_t *name;
} item_t;
extern const item_t item_map[TOT_ITEM_NB];

#endif //PSU_ZAPPY_2018_ZITEM_H
