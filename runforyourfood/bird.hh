#ifndef BIRD_HH
# define BIRD_HH

# include <Gamebuino.h>
# include "constants.hh"

namespace RFYF
{
    const byte birdBitmaps[][11] PROGMEM = {
        {
          constants::bird::WIDTH, constants::bird::HEIGHT,
          0b000110000,
          0b011111100,
          0b001110000,
        }
    };

    class Bird
    {
    public:
        Bird(Gamebuino& gb, bool orientation)
        : _gb(gb)
        {
            _orientation = orientation;
            _verticalOrientation = false;
            _y = random(constants::GROUND_HEIGHT, LCDHEIGHT - constants::bird::HEIGHT);
            _x = orientation ? LCDWIDTH : 0;
            _hSpeed = constants::bird::HSPEED;
            _vSpeed = constants::bird::VSPEED;
        }

        void update() {
            if (_orientation) {
                moveLeft();
            } else {
                moveRight();
            }
        }

        void draw() {
            if (_orientation) {
                _gb.display.drawBitmap(_x, LCDHEIGHT - constants::bird::HEIGHT - _y, birdBitmaps[0]);
            } else {
                _gb.display.drawBitmap(_x, LCDHEIGHT - constants::bird::HEIGHT - _y, birdBitmaps[0], NOROT, FLIPH);
            }
        }

        bool isOut() {
            return _x < -constants::bird::WIDTH || _x > LCDWIDTH;
        }

    private:
        void moveLeft() {
            _x -= _hSpeed;
            if (_x < -constants::bird::WIDTH) {
                _x = -constants::bird::WIDTH - 1;
            }
            changeHeight();
        }

        void moveRight() {
            _x += _hSpeed;
            if (_x > LCDWIDTH) {
                _x = LCDWIDTH + 1;
            }
            changeHeight();
        }

        void changeHeight() {
            if (_verticalOrientation) {
                _y += _vSpeed;
                if (_y >= LCDHEIGHT - constants::bird::HEIGHT) {
                    _verticalOrientation = false;
                }
            } else {
                _y -= _vSpeed;
                if (_y <= constants::GROUND_HEIGHT) {
                    _verticalOrientation = true;
                }
            }
        }

        Gamebuino& _gb;
        int8_t     _x;
        int8_t     _y;
        int8_t     _hSpeed;
        int8_t     _vSpeed;
        bool       _orientation;
        bool       _verticalOrientation;
    }; // End of class Player

} // End of namespace RFYF

#endif // ! BIRD_HH
