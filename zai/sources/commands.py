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
            elif item == "player":
                line = int(math.sqrt(index))
                player.spot_player([line, index - (line * (line + 1))])
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
        try:
            player.update_item(item.split(' ')[0], int(item.split(' ')[1]))
        except ValueError:
            return True
        except IndexError:
            return True
    return True


def broadcast(_):
    return True


def message(buffer):
    message_body = buffer.split(',')
    direction = int(message_body[0])
    content = message_body[1]
    content = content.lstrip()
    if content.startswith("elevation "):
        elevation = content.split(' ')
        if player.get_current_level() == int(elevation[1]) - 1 and player.get_elevation_id() <= int(elevation[2]):
            player.set_hold_position(False)
            player.set_elevation_target(direction, int(elevation[2]))
    elif content.startswith("here ") and direction == 0:
        elevation = content.split(' ')
        if int(elevation[1]) == player.get_elevation_id():
            player.add_elevation_member()
    elif content.startswith("beginning ") and player.get_target() == "elevation":
        elevation = content.split(' ')
        if int(elevation[1]) == player.get_elevation_id():
            player.start_elevation()
    return True


def connect_nbr(_):
    return True


def fork(_):
    return True


def eject(_):
    return True


def take_object(_):
    return True


def set_object(_):
    return True
