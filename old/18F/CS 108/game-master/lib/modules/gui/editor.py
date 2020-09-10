if __name__ == '__main__':
    from text import Text
    from events import Event
    from view import View
    from camera import Camera
else:
    from lib.modules.gui.text import Text
    from lib.modules.gui.events import Event
    from lib.modules.gui.view import View
    from lib.modules.gui.camera import Camera
    from lib.modules.gui.menu import Menu

import pygame

def init():
    pygame.init()
    screen = pygame.display.set_mode((640,480))
    pygame.display.set_caption('The Game')
    pygame.display.flip()

    return screen



class Editor(Menu):

    def __init__(self, screen, level, quit_callback):
        '''Constructs an editor object derived from base class View. The editor object allows for easy creation of new levels.'''

        # construct view object that will handle all rendering and blitting stuff
        super().__init__(screen, 'right', 'Editor: Controls: (z: undo), ()', ('Exit', quit_callback))

        self._platforms = []
        self._level = level

        self._camera = Camera(pygame.Rect((0,0), super().return_screen_dimensions()))

        self._first_click = False
        self.first_pos = None
        self.second_pos = None

        self.read_level()

    def write_level(self):
        '''Write to level every time a new rectangle is made'''
        with open(self._level, 'a') as level_file:
            print('writing new rectangle...')
            level_file.write(str(self._platforms[-1].x)+ ' ' + str(self._platforms[-1].y) + ' ' + str(self._platforms[-1].w) + ' ' + str(self._platforms[-1].h) + '\n')

    def read_level(self):
        '''Load level platforms into level editor'''
        with open(self._level) as level_file:
            [self._platforms.append(pygame.Rect([int(string_integer) for string_integer in line.strip().split()])) for line in level_file]

    def move_camera(self, events):
        '''With given events, controls camera movement.'''

        keys_pressed = events.keyboard()
        delta_x = 0
        delta_y = 0

        change = 5

        if keys_pressed.is_pressed('a'):
            delta_x -= change

        if keys_pressed.is_pressed('d'):
            delta_x += change

        if keys_pressed.is_pressed('w'):
            delta_y -= change

        if keys_pressed.is_pressed('s'):
            delta_y += change

        self._camera.move(delta_x*events.delta_time(), delta_y*events.delta_time())

    def _return_rect(self, first_pos, second_pos):
        '''Transforms two mouse position points into rectangle.'''

        width = second_pos[0] - first_pos[0]
        height = second_pos[1] - first_pos[1]
        return pygame.Rect(first_pos[0], first_pos[1], width, height)


    def update(self, events, screen):
        '''Use mouse to drag and make rectangle platforms'''

        current_click = events.mouse().left_button()

        # first click event
        if current_click and not self._first_click:

            self._first_click = True

            # get true first position
            self.first_pos = self._camera.return_true_position(events.mouse().get_position())


        # dragging event
        if current_click and self._first_click:

            self.second_pos = self._camera.return_true_position(events.mouse().get_position())

            pygame.draw.rect(self._screen, (0, 255,0), self._camera.return_disp_rect(self._return_rect( self.first_pos, self.second_pos )))


        # second click event
        if self._first_click == True and current_click == False:

            # reset first click so new rectangle can be created
            self._first_click = False

            # get true second position
            self.second_pos = self._camera.return_true_position(events.mouse().get_position())

            # return rectangles with from two true positions
            self._platforms.append(self._return_rect(self.first_pos, self.second_pos))

            self.write_level()

        for rectangle in self._platforms:
            pygame.draw.rect(self._screen, (0, 100, 0), (self._camera.return_display_position((rectangle.x, rectangle.y)), (rectangle.width, rectangle.height)))

        super().update(events, screen)
        self.move_camera(events)

if __name__ == '__main__':

    screen = init()
    editor = Editor('level', screen)
    event_handler = Event()

    running = True

    while running:
        screen.fill((0,0,0))
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        event_handler.update(pygame.key.get_pressed(), pygame.mouse.get_pressed(), pygame.mouse.get_pos())
        pygame.time.Clock().tick(60)
        editor.update(event_handler)
        pygame.display.flip()
