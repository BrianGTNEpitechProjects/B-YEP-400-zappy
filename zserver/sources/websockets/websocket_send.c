/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** websocket_send.c
*/

#include <stdio.h>
#include <limits.h>
#include "network_client.h"

/* Created the 18/06/2019 at 15:54 by brian */

uint64_t htonll(uint64_t value) {
    int test_value = 1234;
    if (*(char *)&test_value== 42) {
        uint32_t high_part = htonl((uint32_t)(value >> 32));
        uint32_t low_part = htonl((uint32_t)(value & 0xFFFFFFFFLL));
        return (((uint64_t)low_part) << 32) | high_part;
    } else {
        return value;
    }
}

void send_websocket_header(network_client_t *client, size_t size, uint8_t op) {
    uint8_t to_write = 0b10000000 + op;
    uint16_t size16 = htons(size);
    uint64_t size64 = htonll(size);

    write_to_buffer(&client->cb_out, &to_write, 1);
    if (size < 126) {
        to_write = size & 0b01111111;
        write_to_buffer(&client->cb_out, &to_write, 1);
        printf("%x\n", to_write);
    } else if (size <= USHRT_MAX) {
        to_write = 126;
        write_to_buffer(&client->cb_out, &to_write, 1);
        write_to_buffer(&client->cb_out, (uint8_t *)&size16, 2);
    } else {
        to_write = 127;
        write_to_buffer(&client->cb_out, &to_write, 1);
        write_to_buffer(&client->cb_out, (uint8_t *)&size64, 8);
    }
}

void send_websocket(network_client_t *client, uint8_t *data,
                    size_t length, uint8_t opcode)
{
    send_websocket_header(client, length, opcode);
    write_to_buffer(&client->cb_out, data, length);
}