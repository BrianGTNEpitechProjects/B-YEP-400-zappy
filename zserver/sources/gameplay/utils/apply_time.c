/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

bool apply_time(double *ref, struct timespec *delta_start, int scale)
{
    struct timespec now;
    double delta;

    clock_gettime(0, &now);
    delta = now.tv_sec - delta_start->tv_sec;
    delta += (now.tv_nsec - delta_start->tv_nsec) / pow(10, 9);
    delta *= (double)scale;
    *ref -= delta;
    return (*ref <= .0);
}