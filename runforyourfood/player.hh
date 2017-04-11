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
        const int8_t MAX_JUMP_HEIGHT = HEIGHT;

        Player(Gamebuino& gb, int8_t x) :
            _gb(gb), _x(x), _y(0), _jumpState(0)
        {}

        void draw() {
            if (_jumpState < 0 || _jumpState == 3) { // We were falling before or stopped jumping, let's keep falling
                fall();
            } else if (_jumpState == 2) { // We just reached the top, let's make sure we fall next tick
                _jumpState = -1;
            } else if (_jumpState > 0) { // We were jumping, keep that in mind
                _jumpState = 3;
            }
            _gb.display.fillRect(_x, LCDHEIGHT - constants::GROUND_HEIGHT - HEIGHT - _y, WIDTH, HEIGHT);
        }

        void jump() {
            if (_jumpState >= 0) {
                _jumpState = 1;
                if (++_y > MAX_JUMP_HEIGHT) {
                    _y = MAX_JUMP_HEIGHT;
                    _jumpState = 2;
                }
            }
        }

        void moveLeft() {
            if (--_x < 0) {
                _x = 0;
            }
        }

        void moveRight() {
            if (++_x > LCDWIDTH - WIDTH) {
                _x = LCDWIDTH - WIDTH;
            }
        }

    private:
        void fall() {
            _jumpState = -1;
            if (--_y < 0) {
                _y = 0;
                _jumpState = 0;
            }
        }

        Gamebuino& _gb;
        int8_t _x;
        int8_t _y;
        int8_t _jumpState;
    }; // End of class Player

} // End of namespace RFYF

#endif // ! PLAYER_HH
