#ifndef BIRD_HH
# define BIRD_HH

# include <Gamebuino.h>
# include "constants.hh"

namespace RFYF
{
    class Bird
    {
    public:
        const int8_t HEIGHT = 3;
        const int8_t WIDTH = 6;

        Bird(Gamebuino& gb, bool orientation)
        : _gb(gb)
        {
            _orientation = orientation;
            _verticalOrientation = false;
            _y = random(constants::GROUND_HEIGHT, LCDHEIGHT - HEIGHT);
            _x = orientation ? LCDWIDTH : 0;
        }

        void draw() {
            if (_orientation) {
                moveLeft();
            } else {
                moveRight();
            }
            _gb.display.fillRect(_x, LCDHEIGHT - HEIGHT - _y, WIDTH, HEIGHT);
        }

        bool isOut() {
            return _x < -WIDTH || _x > LCDWIDTH;
        }

    private:
        void moveLeft() {
            if (--_x < -WIDTH) {
                _x = -WIDTH - 1;
            }
            changeHeight();
        }

        void moveRight() {
            if (++_x > LCDWIDTH) {
                _x = LCDWIDTH + 1;
            }
            changeHeight();
        }

        void changeHeight() {
            if (_verticalOrientation) {
                if (++_y >= LCDHEIGHT - HEIGHT) {
                    _verticalOrientation = false;
                }
            } else {
                if (--_y <= constants::GROUND_HEIGHT) {
                    _verticalOrientation = true;
                }
            }
        }

        Gamebuino& _gb;
        int8_t     _x;
        int8_t     _y;
        bool       _orientation;
        bool       _verticalOrientation;
    }; // End of class Player

} // End of namespace RFYF

#endif // ! BIRD_HH
