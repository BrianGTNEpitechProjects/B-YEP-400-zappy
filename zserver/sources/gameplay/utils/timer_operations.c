/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** Timeval operations (from libnet)
*/


#include <time.h>

void timeradd(struct timespec *a, struct timespec *b, struct timespec *res)
{
    res->tv_sec = a->tv_sec + b->tv_sec;
    res->tv_nsec = a->tv_nsec+ b->tv_nsec;
    while (res->tv_nsec >= 1000000000) {
	    res->tv_sec++;
	    res->tv_nsec -= 1000000000;
    }
}

void timersub(struct timespec *a, struct timespec *b, struct timespec *res)
{
    res->tv_sec = a->tv_sec - b->tv_sec;
    res->tv_nsec = (a)->tv_nsec - (b)->tv_nsec;
    while (res->tv_nsec < 0) {
      res->tv_sec--;
      res->tv_nsec += 1000000000;
    }
}

void timermul(struct timespec *a, double mul, struct timespec *res)
{
    double value = (a->tv_sec + a->tv_nsec / 1000000000.0) * mul;

    res->tv_sec = (long)value;
    res->tv_nsec = (value - (long)value) * 1000000000;
}