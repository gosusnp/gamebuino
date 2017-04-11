#include <Gamebuino.h>
#include "RFYF.hh"

Gamebuino gb;
RFYF::RunForYourFood* rfyf;
extern const byte font5x7[]; //get the default large font

//////////////////////////////////////////////////////////////////////
// Setup
void setup() {
  // put your setup code here, to run once:
  gb.begin();
  gb.display.setFont(font5x7); //change the font to the large one
  gb.titleScreen(F("RunForYourFood"));
  rfyf = new RFYF::RunForYourFood(gb);
  rfyf->setupGame();
}

//////////////////////////////////////////////////////////////////////
// MainLoop
void loop() {
  // put your main code here, to run repeatedly:
  if (gb.update()) {
    rfyf->loop();
  }
}
