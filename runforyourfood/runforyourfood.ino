#include <Gamebuino.h>
#include "RFYF.hh"

Gamebuino gb;
RFYF::RunForYourFood* rfyf;

//////////////////////////////////////////////////////////////////////
// Setup
void setup() {
  // put your setup code here, to run once:
  gb.begin();
  gb.display.setFont(font5x7); //change the font to the large one
  gb.titleScreen(F("RunForYourFood"));
  gb.pickRandomSeed();
  gb.battery.show = false;
  rfyf = new RFYF::RunForYourFood(gb);
}

//////////////////////////////////////////////////////////////////////
// MainLoop
void loop() {
    rfyf->loop();
}
