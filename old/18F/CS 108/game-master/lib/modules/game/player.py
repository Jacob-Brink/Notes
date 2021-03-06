import math
import pygame

from lib.modules.physics.vector import Vector
from lib.modules.physics.rigid_body import RigidBody
from lib.modules.gui.image import Image

image_path = 'lib/data/assets/'

class Player(RigidBody):
    '''Models a player'''

    def __init__(self):
        '''Constructs a new player with rigid body as Base Class'''
        self._health = 10
        super().__init__(pygame.Rect(0, 0, 192, 192), 100)
        self._surface = Image(image_path+'test.png').return_surface()

    def update(self, events):
        '''To be called on every game tick'''
        keys_pressed = events.keyboard()
        delta_x = 0
        delta_y = 0

        change = events.delta_time()*10

        if keys_pressed.is_pressed('a'):
            delta_x -= change

        if keys_pressed.is_pressed('d'):
            delta_x += change

        if keys_pressed.is_pressed('w'):
            delta_y -= change

        if keys_pressed.is_pressed('s'):
            delta_y += change

        gravity_vector = Vector(270, -1*events.delta_time())

        super().apply_force(gravity_vector)

        super().apply_force(Vector(math.degrees(math.atan2(delta_y, delta_x)), math.sqrt((delta_x)**2+(delta_y)**2)))
        super().update()

    def return_surface_and_pos(self):
        '''Returns array of surface and tuple of x and y position. (Used for easy blitting)'''
        return [self._surface, (self.return_rect()[0], self.return_rect()[1])]
