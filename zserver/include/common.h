/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** common.h
*/

#ifndef PSU_ZAPPY_2018_COMMON_H
#define PSU_ZAPPY_2018_COMMON_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define ERROR (-1)
#define SUCCESS 0
#define ERROR_EXIT 84
#define SUCCESS_EXIT 0
#define UNUSED __attribute__((unused))

bool check_data_encoding(const uint8_t *data, size_t data_len);

#endif