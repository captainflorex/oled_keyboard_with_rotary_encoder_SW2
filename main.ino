#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LARGEUR_ECRAN 128
#define HAUTEUR_ECRAN 64
Adafruit_SSD1306 display(LARGEUR_ECRAN, HAUTEUR_ECRAN, &Wire, -1);

const int PIN_ENCODEUR_CLK = 3; 
const int PIN_ENCODEUR_DT  = 4; 
const int PIN_ENCODEUR_SW  = 2;  
const int PIN_BOUTON_SW3   = A6; 
