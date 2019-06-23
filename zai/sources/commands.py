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
    return True


def right(buffer):
    if buffer == "ok":
        player.right()
    return True


def left(buffer):
    if buffer == "ok":
        player.left()
    return True


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
    if not buffer.endswith(']'):
        return False
    target_found = False
    index = 0
    tile_list = buffer[1:-1].split(',')
    for tile in tile_list:
        item_list = tile.split(' ')
        if "food" in item_list and not target_found:
            line = int(math.sqrt(index))
            player.set_target_position([line, index - (line * (line + 1))])
            player.set_target("food")
            target_found = True
        for item in item_list:
            item = item.lstrip()
            item = item.rstrip()
            item = re.sub(' +', ' ', item)
            if item in items and not target_found:
                line = int(math.sqrt(index))
                if player.set_target_position([line, index - (line * (line + 1))]):
                    player.set_target(item)
                target_found = True
        index += 1
    if not target_found:
        player.set_target_position([0, 0])
    return True


def inventory(buffer):
    if not buffer.endswith(']'):
        return False
    item_list = buffer[1:-1].split(',')
    for item in item_list:
        item = item.lstrip()
        item = item.rstrip()
        item = re.sub(' +', ' ', item)
        player.update_item(item.split(' ')[0], int(item.split(' ')[1]))
    return True


def broadcast(_):
    return True


def message(buffer):
    message_body = buffer.spit(',')
    direction = int(message_body[0])
    content = message_body[1]
    if content == "HEHO COPAINS !":
        player.set_elevation_target(direction)
    elif content == "JUI LA !" and direction == 0:
        player.add_elevation_member()
    elif content == "LET'S GO !" and player.get_target() == "elevation":
        player.start_elevation()
    return True


def connect_nbr(buffer):
    if int(buffer) > 0:
        if os.fork() == 0:
            connect_clients()
            sys.exit(0)
    return True


def fork(buffer):
    if buffer == "ok":
        if os.fork() == 0:
            connect_clients()
            sys.exit(0)
    return True


def eject(_):
    return True


def take_object(_):
    return True


def set_object(buffer):
    print(buffer)
    print("plop")
    sys.exit(0)
    return True


def start_incantation(buffer):
    if buffer != "ko":
        player.level_up(int(buffer))
    return True
