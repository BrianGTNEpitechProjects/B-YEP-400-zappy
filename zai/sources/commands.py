#!/usr/bin/env python3

import sys
import os
import re
from main import connect_clients
from player import player


def forward(buffer):
    if buffer == "ok":
        player.forward()


def right(buffer):
    if buffer == "ok":
        player.right()


def left(buffer):
    if buffer == "ok":
        player.left()


def look(buffer):
    i = 0
    tile_list = buffer[1:-1].split(',')
    if player.get_current_direction() == 0:
        for y in range(0, -player.get_current_level() - 1, -1):
            for x in range(player.get_current_position()[0] + y, player.get_current_position()[0] - y + 1):
                print("slt")
                print("X : " + str(x) + " Y : " + str(y + player.get_current_position()[1]))
                item_list = tile_list[i].split(' ')
                for item in item_list:
                    player.append_item_to_map(y + player.get_current_position()[1], x, item)
                i += 1
    elif player.get_current_direction() == 90:
        for y in range(0, player.get_current_level() + 1):
            for x in range(player.get_current_position()[0] + y, player.get_current_position()[0] - y - 1, -1):
                print("slt")
                print("X : " + str(x) + " Y : " + str(y + player.get_current_position()[1]))
                item_list = tile_list[i].split(' ')
                for item in item_list:
                    player.append_item_to_map(x, y + player.get_current_position()[1], item)
                i += 1
    elif player.get_current_direction() == 180:
        for y in range(0, player.get_current_level() + 1):
            for x in range(player.get_current_position()[0] + y, player.get_current_position()[0] - y - 1, -1):
                print("slt")
                print("X : " + str(x) + " Y : " + str(y + player.get_current_position()[1]))
                item_list = tile_list[i].split(' ')
                for item in item_list:
                    player.append_item_to_map(y + player.get_current_position()[1], x, item)
                i += 1
    else:
        for y in range(0, -player.get_current_level() - 1, -1):
            for x in range(player.get_current_position()[0] + y, player.get_current_position()[0] - y + 1):
                print("slt")
                print("X : " + str(x) + " Y : " + str(y + player.get_current_position()[1]))
                item_list = tile_list[i].split(' ')
                for item in item_list:
                    player.append_item_to_map(x, y + player.get_current_position()[1], item)
                i += 1

    for x in range(player.get_map_size()[0]):
        print(player.get_map2d()[x])


def inventory(buffer):
    print(buffer)


def broadcast(_):
    return


def connect_nbr(buffer):
    if int(buffer) > 0:
        if os.fork() == 0:
            connect_clients()
            sys.exit(0)


def fork(buffer):
    if buffer == "ok":
        if os.fork() == 0:
            connect_clients()
            sys.exit(0)


def eject(_):
    return


def take_object(buffer):
    if buffer == "ok":
        player.take_object(True)
    else:
        player.take_object(False)


def set_object(buffer):
    if buffer == "ok":
        player.set_object(True)
    else:
        player.set_object(False)


def start_incantation(buffer):
    if buffer != "ko":
        player.level_up(int(buffer))
