#include <Gamebuino.h>

Gamebuino gb;
extern const byte font5x7[]; //get the default large font

//////////////////////////////////////////////////////////////////////
// Setup
void setup() {
  // put your setup code here, to run once:
  gb.begin();
  gb.display.setFont(font5x7); //change the font to the large one
  gb.titleScreen(F("RunForYourFood"));
}

//////////////////////////////////////////////////////////////////////
// MainLoop
void loop() {
  // put your main code here, to run repeatedly:
}
