#ifndef RFYF_HH
# define RFYF_HH

# include <Gamebuino.h>
# include "constants.hh"
# include "player.hh"

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
        {}

        void setupGame() {
            _player = new Player(_gb, PLAYER_START_X);
        }

        void loop() {
            update();
            drawScene();
        }

        void update() {
            // Player actions
            if (_gb.buttons.repeat(BTN_LEFT, 1)) {
                _player->moveLeft();
            } else if (_gb.buttons.repeat(BTN_RIGHT, 1)) {
                _player->moveRight();
            }
            if (_gb.buttons.repeat(BTN_A, 1)) {
                _player->jump();
            }
        }

        void drawScene() {
            // Draw the ground
            _gb.display.fillRect(0, LCDHEIGHT - constants::GROUND_HEIGHT, LCDWIDTH, 1);
            // Draw the player
            _player->draw();
        }

    private:
        Gamebuino&  _gb;
        Player*     _player;
    }; // End of class RunForYourFood

} // End of namespace RFYF



#endif // ! RFYF_HH
