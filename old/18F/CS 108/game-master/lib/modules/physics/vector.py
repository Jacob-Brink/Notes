import math

class Vector:
    '''Vector class used for velocity, force, and acceleration in physics stuff'''

    def __init__(self, direction, magnitude):
        '''Constructs a new vector given direction (degrees :0 for facing right) and magnitude (any num type)'''
        self._direction = direction
        self._magnitude = magnitude

    def return_x_component(self):
        '''Returns the x component of the vector via Trig'''
        return math.cos(math.radians(self._direction))*self._magnitude

    def return_y_component(self):
        '''Returns the y component of the vector via Trig'''
        return math.sin(math.radians(self._direction))*self._magnitude

    def return_direction(self):
        '''Returns the direction (degrees)'''
        return self._direction

    def return_magnitude(self):
        '''Returns the magnitude'''
        return self._magnitude

    def modify_magnitude(self, new_magnitude):
        '''Modifies by replacing value'''
        self._magnitude = new_magnitude

    def modify_direction(self, new_direction):
        '''Modifies by replacing value'''
        self._direction = new_direction

    def alter_magnitude(self, diff_magnitude):
        '''Modifies magnitude by adding diff_magnitude'''
        self._magnitude += diff_magnitude

    def alter_direction(self, diff_direction):
        '''Modifies direction by adding diff_direction'''
        self._direction += diff_direction

    def __str__(self):
        '''Pretty print enabled for class'''
        return 'Direction: ' + str(self.return_direction()) + ', Magnitude: ' + str(self.return_magnitude())

    def __mul__(self, other):
        '''Allows for scalar multiplication of vectors'''

        if isinstance(other, int) or isinstance(other, float):

            return Vector(self.return_direction(), other * self.return_magnitude())

    def __add__(self, other):
        '''Addition overloading of vectors when both terms are vectors'''

        x_component = self.return_x_component() + other.return_x_component()
        y_component = self.return_y_component() + other.return_y_component()

        return Vector( math.degrees(math.atan2(y_component, x_component)), math.sqrt((x_component)**2 + (y_component)**2) )



if __name__ == '__main__':
    '''
    Test each part of the vector class
    '''


    #initialize vector v
    v = Vector(90, 100)

    #test component returning functions
    assert(round(v.return_x_component()) == 0)
    assert(round(v.return_y_component()) == 100)

    #test direction and magnitude returning functions
    assert(round(v.return_direction()) == 90)
    assert(round(v.return_magnitude()) == 100)

    #test modify_magnitude function
    v.modify_magnitude(1000)
    assert(round(v.return_magnitude()) == 1000)

    #test modify_direction function
    v.modify_direction(180)
    assert(round(v.return_direction()) == 180)

    #test alter function
    v.alter_magnitude(1000)
    assert(round(v.return_magnitude()) == 2000)

    v.alter_direction(-1)
    assert(round(v.return_direction()) == 179)

    #test overloading
    v1 = Vector(45, 100)
    v2 = Vector(180+45, 100)

    v3 = v1+v2

    assert(round(v3.return_magnitude()) == 0)

    #test scalar

    v1 = Vector(45, 100)
    v = v1 * 2

    assert(round(v.return_magnitude()) == 200)

    print('Vector Tests passed')
