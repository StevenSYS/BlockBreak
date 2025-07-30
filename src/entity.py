import pygame
from object import *
from sharedVars import *
#/* Enum - entity_directions */
ENTITY_DIR_NONE = 0
ENTITY_DIR_UP = 1
ENTITY_DIR_DOWN = 2
ENTITY_DIR_LEFT = 3
ENTITY_DIR_RIGHT = 4
#/* Enum End */
class entity:
    def __init__(
        self,
        red, green, blue,
        direction,
        width, height,
        x, y,
        speed,
        visible
        ):
        self.direction = direction
        self.speed = speed
        self.object = objectClass(
            red, green, blue,
            width, height,
            x, y,
            visible
            )
        return
    def draw(
        self,
        screen
        ):
        #/* Why doesn't Python have switches? */
        if (self.direction == ENTITY_DIR_UP):
            self.object.position[1] -= self.speed
        elif (self.direction == ENTITY_DIR_DOWN):
            self.object.position[1] += self.speed
        elif (self.direction == ENTITY_DIR_LEFT):
            self.object.position[0] -= self.speed
        elif (self.direction == ENTITY_DIR_RIGHT):
            self.object.position[0] += self.speed
        return self.object.draw(screen)
