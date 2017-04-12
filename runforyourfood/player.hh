#ifndef PLAYER_HH
# define PLAYER_HH

# include <Gamebuino.h>
# include "constants.hh"

namespace RFYF
{
    class Player
    {
    public:
        const int8_t HEIGHT = 8;
        const int8_t WIDTH = 5;
        const int8_t MAX_JUMP_HEIGHT = 1.5 * HEIGHT;

        Player(Gamebuino& gb, int8_t x, int8_t hSpeed, int8_t vSpeed)
            : _gb(gb)
            , _x(x)
            , _y(constants::GROUND_HEIGHT)
            , _jumpState(0)
            , _hSpeed(hSpeed)
            , _vSpeed(vSpeed)
        {}

        void draw() {
            if (_jumpState < 0 || _jumpState == 3) { // We were falling before or stopped jumping, let's keep falling
                fall();
            } else if (_jumpState == 2) { // We just reached the top, let's make sure we fall next tick
                _jumpState = -1;
            } else if (_jumpState > 0) { // We were jumping, keep that in mind
                _jumpState = 3;
            }
            _gb.display.fillRect(_x, LCDHEIGHT - HEIGHT - _y, WIDTH, HEIGHT);
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
            if (_x < 0) {
                _x = 0;
            }
        }

        void moveRight() {
            _x += _hSpeed;
            if (_x > LCDWIDTH - WIDTH) {
                _x = LCDWIDTH - WIDTH;
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
    }; // End of class Player

} // End of namespace RFYF

#endif // ! PLAYER_HH
