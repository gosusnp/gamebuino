#ifndef BIRD_HH
# define BIRD_HH

# include <Gamebuino.h>
# include "constants.hh"
# include "drawable.hh"

namespace RFYF
{
    const byte birdBitmaps[][11] PROGMEM = {
        {
          constants::bird::WIDTH, constants::bird::HEIGHT,
          0b000110000,
          0b011111100,
          0b000111000,
        }, {
          constants::bird::WIDTH, constants::bird::HEIGHT,
          0b000110000,
          0b011111100,
          0b001110000,
        }
    };

    class Bird : public Drawable
    {
    public:
        Bird(Gamebuino& gb, bool orientation)
        : Drawable(gb, constants::bird::WIDTH, constants::bird::HEIGHT, orientation ? LCDWIDTH : 0, random(constants::GROUND_HEIGHT, LCDHEIGHT - constants::bird::HEIGHT))
        {
            _orientation = orientation;
            _verticalOrientation = false;
            _hSpeed = constants::bird::HSPEED;
            _vSpeed = constants::bird::VSPEED;
        }

        void update() {
            if (orientation()) {
                moveLeft();
            } else {
                moveRight();
            }
        }

        bool isOut() {
            return _x < -constants::bird::WIDTH || _x > LCDWIDTH;
        }

        bool orientation() { return _orientation; }

        const byte* getFrame() { return birdBitmaps[orientation()]; }

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

        int8_t     _hSpeed;
        int8_t     _vSpeed;
        bool       _orientation;
        bool       _verticalOrientation;
    }; // End of class Player

} // End of namespace RFYF

#endif // ! BIRD_HH
