#!/usr/bin/env python3

import sys
import os
import re
from main import connect_clients
from player import player
import math


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
    items = [
        "linemate",
        "deraumere",
        "sibur",
        "mendiane",
        "phiras",
        "thystame",
        "food"
    ]
    index = 0
    tile_list = buffer[1:-1].split(',')
    for tile in tile_list:
        item_list = tile.split(' ')
        if "food" in item_list:
            line = int(math.sqrt(index))
            player.set_target_position([line, index - (line * (line + 1))])
            player.set_target("food")
            return
        for item in item_list:
            item = item.lstrip()
            item = item.rstrip()
            item = re.sub(' +', ' ', item)
            print(item)
            if item in items:
                line = int(math.sqrt(index))
                if player.set_target_position([line, index - (line * (line + 1))]):
                    player.set_target(item)
                return
        index += 1
    player.set_target_position([0, 0])


def inventory(buffer):
    item_list = buffer[1:-1].split(',')
    for item in item_list:
        item = item.lstrip()
        item = item.rstrip()
        item = re.sub(' +', ' ', item)
        player.update_item(item.split(' ')[0], int(item.split(' ')[1]))


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
