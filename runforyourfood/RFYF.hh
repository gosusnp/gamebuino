#ifndef RFYF_HH
# define RFYF_HH

# include <Gamebuino.h>
# include "constants.hh"
# include "player.hh"
# include "bird.hh"

extern const byte font3x5[]; //get the default large font
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
        , _score(0)
        , _player(0)
        , _birds(new Bird*[5])
        {}

        void titleScreen() {
            _gb.display.setFont(font5x7); //change the font to the large one
            _gb.display.fontSize = 2;
            _gb.titleScreen(F("RunForYourFood"));
            _gb.pickRandomSeed();
            _gb.battery.show = false;
        }

        void loop() {
            if (_gb.update()) {
                update();
                drawScene();
                drawScore();
            }
        }

        void update() {
            // Let's see if we need to add a player
            if (!_player) {
                _player = new Player(_gb, PLAYER_START_X, constants::player::HSPEED, constants::player::VSPEED);
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
            for (int i = 0; i < getNumberOfBirds(); ++i) {
                if (!_birds[i]) {
                    if (random(0, 10) > 8)
                        _birds[i] = new Bird(_gb, random(0, 10) % 2);
                } else if (_birds[i]->isOut()) {
                    delete _birds[i];
                    _birds[i] = 0;
                    ++_score;
                } else if (_birds[i]) {
                    _birds[i]->update();

                    // Check if collide
                    if (_player->kicked(*_birds[i])) {
                        delete _birds[i];
                        _birds[i] = 0;
                        _score += 5;
                    } else if (_player->collide(*_birds[i])) {
                        gameOver();
                    }
                }
            }
        }

        void drawScene() {
            // Draw the ground
            _gb.display.fillRect(0, LCDHEIGHT - constants::GROUND_HEIGHT, LCDWIDTH, 1);

            // Draw the player
            if (_player) {
                _player->draw();
            }

            // Draw the bird if needed
            for (int i = 0; i < getNumberOfBirds(); ++i) {
                if (_birds[i]) {
                    _birds[i]->draw();
                }
            }
        }

        void drawScore() {
            _gb.display.setFont(font3x5);
            _gb.display.fontSize = 1;
            _gb.display.cursorX = LCDWIDTH - 10 - (_score > 9 ? 3 : 0) - (_score > 99 ? 3 : 0);
            _gb.display.cursorY = 5;
            _gb.display.print(_score);
        }

        void gameOver() {
            delete _player;
            _player = 0;
            for (int i = 0; i < 5; ++i) {
                if (_birds[i]) {
                    delete _birds[i];
                    _birds[i] = 0;
                }
            }
            _score = 0;
            _gb.titleScreen(F("RunForYourFood"));
        }

        int8_t getNumberOfBirds() {
            if (_score < 5) {
                return 1;
            } else if (_score < 15) {
                return 2;
            } else if (_score < 30) {
                return 3;
            } else if (_score < 60) {
                return 4;
            }
            return 5;
        }

    private:
        Gamebuino&  _gb;
        int8_t      _score;
        Player*     _player;
        Bird**       _birds;
    }; // End of class RunForYourFood

} // End of namespace RFYF



#endif // ! RFYF_HH
