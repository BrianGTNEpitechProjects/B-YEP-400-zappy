#!/usr/bin/env python3

import time


class Player:
    def __init__(self):
        self.map_size = [0, 0]
        self.target_position = [0, 0]
        self.target = None
        self.current_level = 1
        self.commands_count = 0
        self.inventory = {
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0,
            "food": 0
        }
        self.taken_objects = []
        self.thrown_objects = []
        self.hold_position = False
        self.target_locked = False
        self.elevation_id = 0
        self.elevation_ready = False
        self.elevation_started = False
        self.elevation_members = 1
        self.waiting = 0

    def get_current_level(self):
        return self.current_level

    def set_map_size(self, size):
        self.map_size = size

    def get_map_size(self):
        return self.map_size

    def forward(self):
        self.target_position[0] -= 1

    def right(self):
        tmp = self.target_position[0]
        self.target_position[0] = self.target_position[1]
        self.target_position[1] = -tmp

    def left(self):
        tmp = self.target_position[0]
        self.target_position[0] = -self.target_position[1]
        self.target_position[1] = tmp

    def level_up(self, level):
        self.current_level = level

    def can_level_up(self):
        level_requirement = [
            {"linemate": 1, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0},
            {"linemate": 1, "deraumere": 1, "sibur": 1, "mendiane": 0, "phiras": 0, "thystame": 0},
            {"linemate": 2, "deraumere": 0, "sibur": 1, "mendiane": 0, "phiras": 2, "thystame": 0},
            {"linemate": 1, "deraumere": 1, "sibur": 2, "mendiane": 0, "phiras": 1, "thystame": 0},
            {"linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3, "phiras": 0, "thystame": 0},
            {"linemate": 1, "deraumere": 2, "sibur": 3, "mendiane": 0, "phiras": 1, "thystame": 0},
            {"linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1}
        ]
        for item in level_requirement[self.current_level - 1]:
            if self.inventory[item] < level_requirement[self.current_level - 1][item]:
                return False
        return True

    def new_action(self):
        globals().update()
        if self.can_level_up() and not self.hold_position and not self.target_locked and self.inventory["food"] > 50:
            self.hold_position = True
            self.elevation_id = int(time.time())
            if self.elevation_members < self.required_members():
                return "Broadcast elevation " + str(self.current_level + 1) + " " + str(self.elevation_id) + "\n"
        if self.can_level_up() and self.elevation_members >= self.required_members():
            if not self.elevation_ready:
                if len(self.thrown_objects) == 0:
                    self.throw_elevation_items()
                item = self.thrown_objects.pop()
                if len(self.thrown_objects) == 0:
                    self.elevation_ready = True
                return "Set " + item + "\n"
            elif not self.elevation_started:
                self.start_elevation()
                return "Broadcast beginning " + str(self.elevation_id) + "\n"
            else:
                return "Incantation\n"
        if self.commands_count == 10:
            self.commands_count = 0
            return "Inventory\n"
        elif self.commands_count % 2 == 0 and not self.hold_position:
            self.commands_count += 1
            if not self.target:
                return "Forward\n"
            elif self.target_position[0] == 0:
                if self.target_position[1] == 0:
                    if self.target == "elevation":
                        command = "Broadcast here " + str(self.elevation_id) + "\n"
                        self.hold_position = True
                    else:
                        command = "Take " + self.target + "\n"
                        self.target = None
                    return command
                elif self.target_position[1] < 0:
                    return "Left\n"
                else:
                    return "Right\n"
            elif self.target_position[0] < 0:
                if self.target_position[1] < 0:
                    return "Left\n"
                else:
                    return "Right\n"
            else:
                return "Forward\n"
        elif self.commands_count % 2 == 0 and self.hold_position:
            self.commands_count += 1
            if self.inventory["food"] > 10:
                self.waiting += 1
                if self.waiting > 10:
                    self.waiting = 0
                    return "Fork\n"
                return "Broadcast elevation " + str(self.current_level + 1) + " " + str(self.elevation_id) + "\n"
            else:
                self.reset()
                return "Look\n"
        else:
            self.commands_count += 1
            return "Look\n"

    def set_target_position(self, target_position):
        if (abs(target_position[0]) + abs(target_position[1]) < abs(self.target_position[0]) + abs(self.target_position[1])\
                or not self.target) and not self.target_locked:
            self.target_position = target_position
            return True
        return False

    def set_target(self, target):
        if self.inventory["food"] < 5 and target != "food":
            self.target_position = [0, 0]
            self.target = None
        else:
            self.target = target

    def get_target(self):
        return self.target

    def update_item(self, item, quantity):
        self.inventory[item] = quantity

    def set_elevation_target(self, broadcast_direction, elevation_id):
        max_range = self.map_size[0] if self.map_size[0] > self.map_size[1] else self.map_size[1]
        switcher = {
            0: [0, 0],
            1: [max_range, 0],
            2: [max_range, -max_range],
            3: [0, -max_range],
            4: [-max_range, -max_range],
            5: [-max_range, 0],
            6: [-max_range, max_range],
            7: [0, max_range],
            8: [max_range, max_range]
        }
        self.target_position = switcher.get(broadcast_direction)
        self.set_target("elevation")
        self.elevation_id = elevation_id
        self.target_locked = True

    def set_hold_position(self, hold_position):
        self.hold_position = hold_position

    def get_hold_position(self):
        return self.hold_position

    def set_target_locked(self, locked):
        self.target_locked = locked

    def is_target_locked(self):
        return self.target_locked

    def spot_player(self, position):
        if self.target_locked and self.target == "elevation":
            self.target_position = position

    def add_elevation_member(self):
        self.elevation_members += 1

    def required_members(self):
        switcher = {
            2: 1,
            3: 2,
            4: 2,
            5: 4,
            6: 4,
            7: 6,
            8: 6
        }
        return switcher.get(self.current_level + 1)

    def throw_elevation_items(self):
        items_to_throw = [
            ["linemate"],
            ["linemate", "deraumere", "sibur"],
            ["linemate", "linemate", "sibur", "phiras", "phiras"],
            ["linemate", "deraumere", "sibur", "sibur", "phiras"],
            ["linemate", "deraumere", "deraumere", "sibur", "mendiane", "mendiane", "mendiane"],
            ["linemate", "deraumere", "deraumere", "sibur", "sibur", "sibur", "phiras"],
            ["linemate", "linemate", "deraumere", "deraumere", "sibur", "sibur", "mendiane", "mendiane", "phiras", "phiras", "thystame"]
        ]
        self.thrown_objects = items_to_throw[self.current_level - 1]

    def set_elevation_id(self, elevation_id):
        self.elevation_id = elevation_id

    def get_elevation_id(self):
        return self.elevation_id

    def start_elevation(self):
        self.elevation_started = True

    def get_elevation_started(self):
        return self.elevation_started

    def reset(self):
        self.target_position = [0, 0]
        self.target = ""
        self.hold_position = False
        self.target_locked = False
        self.elevation_members = 1
        self.elevation_ready = False
        self.elevation_started = False


player = Player()
