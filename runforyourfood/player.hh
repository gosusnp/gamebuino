#ifndef PLAYER_HH
# define PLAYER_HH

# include <Gamebuino.h>
# include "constants.hh"
# include "drawable.hh"

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
          0b000100000,
        }, { // Kick
          constants::player::WIDTH, constants::player::HEIGHT,
          0b011100000,
          0b010100000,
          0b011100000,
          0b001000000,
          0b011100000,
          0b001000000,
          0b001111000,
          0b010000000,
          0b010000000,
        }, { // Kick (body)
          constants::player::WIDTH, constants::player::HEIGHT,
          0b011100000,
          0b010100000,
          0b011100000,
          0b001000000,
          0b011100000,
          0b001000000,
          0b001000000,
          0b010000000,
          0b010000000,
        }, { // Kick (leg)
          constants::player::WIDTH, constants::player::HEIGHT,
          0b000000000,
          0b000000000,
          0b000000000,
          0b000000000,
          0b000000000,
          0b000000000,
          0b000111000,
          0b000000000,
          0b000000000,
        }
    };
    const byte playerReversedBitmaps[][11] PROGMEM = {
        {
          constants::player::WIDTH, constants::player::HEIGHT,
          0b000111000,
          0b000101000,
          0b000111000,
          0b000010000,
          0b001110000,
          0b000010000,
          0b000010000,
          0b000010000,
          0b000010000,
        }, {
          constants::player::WIDTH, constants::player::HEIGHT,
          0b000111000,
          0b000101000,
          0b000111000,
          0b000010000,
          0b001110000,
          0b000010000,
          0b000110000,
          0b000011000,
          0b000010000,
        }, {
          constants::player::WIDTH, constants::player::HEIGHT,
          0b000111000,
          0b000101000,
          0b000111000,
          0b000010000,
          0b001110000,
          0b000010000,
          0b000110000,
          0b000101000,
          0b000001000,
        }, {
          constants::player::WIDTH, constants::player::HEIGHT,
          0b000111000,
          0b000101000,
          0b000111000,
          0b000010000,
          0b001110000,
          0b000010000,
          0b000010000,
          0b000101000,
          0b000100000,
        }, { // Kick
          constants::player::WIDTH, constants::player::HEIGHT,
          0b000111000,
          0b000101000,
          0b000111000,
          0b000010000,
          0b000111000,
          0b000010000,
          0b011110000,
          0b000001000,
          0b000001000,
        }, { // Kick (body)
          constants::player::WIDTH, constants::player::HEIGHT,
          0b000111000,
          0b000101000,
          0b000111000,
          0b000010000,
          0b000111000,
          0b000010000,
          0b000010000,
          0b000001000,
          0b000001000,
        }, { // Kick (leg)
          constants::player::WIDTH, constants::player::HEIGHT,
          0b000000000,
          0b000000000,
          0b000000000,
          0b000000000,
          0b000000000,
          0b000000000,
          0b011100000,
          0b000000000,
          0b000000000,
        }
    };
    class Player : public Drawable
    {
    public:
        const int8_t MAX_JUMP_HEIGHT = 1.5 * constants::player::HEIGHT;

        Player(Gamebuino& gb, int8_t x, int8_t hSpeed, int8_t vSpeed)
            : Drawable(gb, constants::player::WIDTH, constants::player::HEIGHT, x, constants::GROUND_HEIGHT)
            , _jumpState(0)
            , _hSpeed(hSpeed)
            , _vSpeed(vSpeed)
            , _drawAction(0)
            , _drawFrame(0)
            , _kick(0)
        {}

        void update() {
            if (_jumpState < 0 || _jumpState == 3) { // We were falling before or stopped jumping, let's keep falling
                fall();
            } else if (_jumpState == 2) { // We just reached the top, let's make sure we fall next tick
                _jumpState = -1;
            } else if (_jumpState > 0) { // We were jumping, keep that in mind
                _jumpState = 3;
            }

            if (_kick > 0) {
                --_kick;
                _drawAction = (_drawAction % 2) + 4;
            }
        }

        void draw() {
            Drawable::draw();
            switch (_drawAction) {
                case 0:
                case 1:
                    _drawFrame = 0;
                    break;
                case 2:
                case 3:
                    ++_drawFrame;
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

        void kick() {
            if (_kick == 0) {
                _kick = 2;
            }
        }

        void moveLeft() {
            if (_kick && !_jumpState) {
                return;
            }
            _x -= _hSpeed;
            _drawAction = 3;
            if (_x < 0) {
                _x = -1;
                _drawAction = 1;
            }
        }

        void moveRight() {
            if (_kick && !_jumpState) {
                return;
            }
            _x += _hSpeed;
            _drawAction = 2;
            if (_x > LCDWIDTH - constants::player::WIDTH) {
                _x = LCDWIDTH - constants::player::WIDTH + 1;
                _drawAction = 0;
            }
        }

        bool kicked(Drawable& other) {
            return _kick &&
                   _gb.collideBitmapBitmap(getLeft(), getBottom(),
                                           orientation() ? playerBitmaps[6] : playerReversedBitmaps[6],
                                           other.getLeft(), other.getBottom(), other.getFrame());
        }
        bool collide(Drawable& other) {
            return _gb.collideBitmapBitmap(getLeft(), getBottom(), getFrame(),
                                           other.getLeft(), other.getBottom(), other.getFrame());
        }

        bool orientation() { return !(_drawAction % 2); }

        const byte* getFrame() {
            int8_t frame = 0;
            if (_jumpState) {
                frame = _kick ? 4 : 2;
            } else {
                switch (_drawAction) {
                    case 0:
                    case 1:
                        frame = 0;
                        break;
                    case 2:
                    case 3:
                        frame = _drawFrame;
                        break;
                    case 4:
                    case 5:
                        frame = 4;
                        break;
                }
            }
            return orientation() ? playerBitmaps[frame] : playerReversedBitmaps[frame];
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

        int8_t     _jumpState;
        int8_t     _hSpeed;
        int8_t     _vSpeed;
        int8_t     _drawAction;
        int8_t     _drawFrame;
        int8_t     _kick;
    }; // End of class Player

} // End of namespace RFYF

#endif // ! PLAYER_HH
