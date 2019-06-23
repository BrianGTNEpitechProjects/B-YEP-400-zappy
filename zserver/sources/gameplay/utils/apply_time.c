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

static int timespec_sub(struct timespec *res, \
struct timespec *x, struct timespec *y)
{
    int nsec;

    if (x->tv_nsec < y->tv_nsec) {
        nsec = (int)((y->tv_nsec - x->tv_nsec) / 1000000000 + 1);
        y->tv_nsec -= 1000000000 * nsec;
        y->tv_sec += nsec;
    }
    if (x->tv_nsec - y->tv_nsec > 1000000000) {
        nsec = (int)((x->tv_nsec - y->tv_nsec) / 1000000000);
        y->tv_nsec += 1000000000 * nsec;
        y->tv_sec -= nsec;
    }
    res->tv_sec = x->tv_sec - y->tv_sec;
    res->tv_nsec = x->tv_nsec - y->tv_nsec;
    return (x->tv_sec < y->tv_sec);
}

bool apply_time(double *ref, struct timespec *start, int scale)
{
    struct timespec now;
    struct timespec res;
    double delta;

    clock_gettime(0, &now);
    timespec_sub(&res, &now, start);
    delta = res.tv_sec;
    delta += res.tv_nsec / pow(10, 9);
    delta *= (double)scale;
    delta = fabs(delta);
    *ref -= delta;
    return (*ref <= .0);
}