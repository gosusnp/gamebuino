#ifndef RFYF_HH
# define RFYF_HH

# include <Gamebuino.h>
# include "constants.hh"
# include "player.hh"
# include "bird.hh"

extern const byte font5x7[]; //get the default large font

namespace RFYF
{

    class RunForYourFood
    {
    private:
        // Constants
        const int8_t PLAYER_START_X = 5;

    public:
        RunForYourFood(Gamebuino& gb)
        : _gb(gb)
        , _player(0)
        , _bird(0)
        {}

        void titleScreen() {
            _gb.display.setFont(font5x7); //change the font to the large one
            _gb.titleScreen(F("RunForYourFood"));
            if (_player) {
                delete _player;
                _player = 0;
            }
        }

        void loop() {
            update();
            drawScene();
        }

        void update() {
            // Let's see if we need to add a player
            if (!_player) {
                _player = new Player(_gb, PLAYER_START_X, constants::player::HSPEED, constants::player::VSPEED);
            }
            // Let's see if we need to add a bird
            if (!_bird) {
                _bird = new Bird(_gb, random(0, 10) % 2);
            } else if (_bird->isOut()) {
                delete _bird;
                _bird = 0;
            }

            // Player actions
            if (_gb.buttons.repeat(BTN_A, 1)) {
                _player->jump();
            }
            if (_gb.buttons.repeat(BTN_B, 1)) {
                _player->kick();
            }
            if (_gb.buttons.repeat(BTN_LEFT, 1)) {
                _player->moveLeft();
            } else if (_gb.buttons.repeat(BTN_RIGHT, 1)) {
                _player->moveRight();
            }

            _player->update();
            if (_bird) {
                _bird->update();

                // Check if collide
                if (_player->kicked(*_bird)) {
                    delete _bird;
                    _bird = 0;
                } else if (_player->collide(*_bird)) {
                    titleScreen();
                }
            }
        }

        void drawScene() {
            // Draw the ground
            _gb.display.fillRect(0, LCDHEIGHT - constants::GROUND_HEIGHT, LCDWIDTH, 1);

            // Draw the player
            _player->draw();

            // Draw the bird if needed
            if (_bird) {
                _bird->draw();
            }
        }

    private:
        Gamebuino&  _gb;
        Player*     _player;
        Bird*       _bird;
    }; // End of class RunForYourFood

} // End of namespace RFYF



#endif // ! RFYF_HH
