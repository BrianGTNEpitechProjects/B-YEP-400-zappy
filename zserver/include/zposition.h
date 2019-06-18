/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#ifndef PSU_ZAPPY_2018_ZPOSITION_H
#define PSU_ZAPPY_2018_ZPOSITION_H

/*
 * POSITION
 */
typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST
} e_cardinal_t;

typedef union {
    struct {
        int x;
        int y;
    };
    int arr[2];
} pos_t;

#endif //PSU_ZAPPY_2018_ZPOSITION_H
