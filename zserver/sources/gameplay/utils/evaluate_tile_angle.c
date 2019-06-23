/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <stdlib.h>
#include "zposition.h"

int evaluate_tile_angle(e_cardinal_t dir, int i, int lim)
{
    double relative_angle = ((double)i * 360.0) / (double)lim;
    double absolute_angle;

    relative_angle = (size_t)(relative_angle + 315.0) % 360;
    absolute_angle = relative_angle + (dir * 90.0);
    return ((int)absolute_angle % 360);
}