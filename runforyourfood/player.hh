#ifndef PLAYER_HH
# define PLAYER_HH

# include <Gamebuino.h>
# include "constants.hh"

namespace RFYF
{
    const byte playerBitmaps[][11] PROGMEM = {
        {
          constants::player::WIDTH, constants::player::HEIGHT,
          0b011100000,
          0b010100000,
          0b011100000,
          0b001000000,
          0b001110000,
          0b001000000,
          0b001000000,
          0b001000000,
          0b001000000,
        }, {
          constants::player::WIDTH, constants::player::HEIGHT,
          0b011100000,
          0b010100000,
          0b011100000,
          0b001000000,
          0b001110000,
          0b001000000,
          0b001100000,
          0b011000000,
          0b001000000,
        }, {
          constants::player::WIDTH, constants::player::HEIGHT,
          0b011100000,
          0b010100000,
          0b011100000,
          0b001000000,
          0b001110000,
          0b001000000,
          0b001100000,
          0b010100000,
          0b010000000,
        }, {
          constants::player::WIDTH, constants::player::HEIGHT,
          0b011100000,
          0b010100000,
          0b011100000,
          0b001000000,
          0b001110000,
          0b001000000,
          0b001000000,
          0b010100000,
          0b010100000,
        }
    };

    class Player
    {
    public:
        const int8_t MAX_JUMP_HEIGHT = 1.5 * constants::player::HEIGHT;

        Player(Gamebuino& gb, int8_t x, int8_t hSpeed, int8_t vSpeed)
            : _gb(gb)
            , _x(x)
            , _y(constants::GROUND_HEIGHT)
            , _jumpState(0)
            , _hSpeed(hSpeed)
            , _vSpeed(vSpeed)
            , _drawAction(0)
            , _drawFrame(0)
        {}

        void draw() {
            if (_jumpState < 0 || _jumpState == 3) { // We were falling before or stopped jumping, let's keep falling
                fall();
            } else if (_jumpState == 2) { // We just reached the top, let's make sure we fall next tick
                _jumpState = -1;
            } else if (_jumpState > 0) { // We were jumping, keep that in mind
                _jumpState = 3;
            }
            if (_drawAction == 0) { // stading still looking to the right
                _gb.display.drawBitmap(_x, LCDHEIGHT - constants::player::HEIGHT - _y, playerBitmaps[_jumpState ? 2 : 0]);
                _drawFrame = 0;
            } else if (_drawAction == 1) { // standing still looking to the left
                _gb.display.drawBitmap(_x, LCDHEIGHT - constants::player::HEIGHT - _y, playerBitmaps[_jumpState ? 2 : 0], NOROT, FLIPH);
                _drawFrame = 0;
            } else if (_drawAction == 2) { // run right
                _gb.display.drawBitmap(_x, LCDHEIGHT - constants::player::HEIGHT - _y, playerBitmaps[_jumpState ? 2 : _drawFrame++]);
            } else if (_drawAction == 3) { // run left
                _gb.display.drawBitmap(_x, LCDHEIGHT - constants::player::HEIGHT - _y, playerBitmaps[_jumpState ? 2 : _drawFrame++], NOROT, FLIPH);
            }
            if (_drawFrame > 3) {
                _drawFrame = 0;
            }
            _drawAction = _drawAction % 2;
        }

        void jump() {
            if (_jumpState >= 0) {
                _jumpState = 1;
                _y += _vSpeed;
                if (_y > constants::GROUND_HEIGHT + MAX_JUMP_HEIGHT) {
                    _y = constants::GROUND_HEIGHT + MAX_JUMP_HEIGHT;
                    _jumpState = 2;
                }
            }
        }

        void moveLeft() {
            _x -= _hSpeed;
            _drawAction = 3;
            if (_x < 0) {
                _x = -1;
                _drawAction = 1;
            }
        }

        void moveRight() {
            _x += _hSpeed;
            _drawAction = 2;
            if (_x > LCDWIDTH - constants::player::WIDTH) {
                _x = LCDWIDTH - constants::player::WIDTH + 1;
                _drawAction = 0;
            }
        }

    private:
        void fall() {
            _jumpState = -1;
            _y -= _vSpeed;
            if (_y < constants::GROUND_HEIGHT) {
                _y = constants::GROUND_HEIGHT;
                _jumpState = 0;
            }
        }

        Gamebuino& _gb;
        int8_t     _x;
        int8_t     _y;
        int8_t     _jumpState;
        int8_t     _hSpeed;
        int8_t     _vSpeed;
        int8_t     _drawAction;
        int8_t     _drawFrame;
    }; // End of class Player

} // End of namespace RFYF

#endif // ! PLAYER_HH
