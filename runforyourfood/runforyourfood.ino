#include <Gamebuino.h>
#include "RFYF.hh"

Gamebuino gb;
RFYF::RunForYourFood* rfyf;

//////////////////////////////////////////////////////////////////////
// Setup
void setup() {
  // put your setup code here, to run once:
  gb.begin();
  rfyf = new RFYF::RunForYourFood(gb);
  rfyf->titleScreen();
}

//////////////////////////////////////////////////////////////////////
// MainLoop
void loop() {
    rfyf->loop();
}
