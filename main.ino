#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LARGEUR_ECRAN 128
#define HAUTEUR_ECRAN 64
Adafruit_SSD1306 display(LARGEUR_ECRAN, HAUTEUR_ECRAN, &Wire, -1);

const int PIN_ENCODEUR_CLK = 3; 
const int PIN_ENCODEUR_DT  = 4; 
const int PIN_ENCODEUR_SW  = 2;  
const int PIN_BOUTON_SW3   = A6; 

const char listeCaracteres[] = "< abcdefghijklmnopqrstuvwxyz\x85\x82\x8A\x88\x87 ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,?!";
const int tailleListe = sizeof(listeCaracteres) - 1;
int indexCaractereSelectionne = 1; 

unsigned long dernierAppuiBouton = 0;
int dernierEtatClk;
int lireRotationEncodeur();

int lireRotationEncodeur() {
  int etatClkActuel = digitalRead(PIN_ENCODEUR_CLK);
  int resultat = 0;
  if (etatClkActuel != dernierEtatClk && etatClkActuel == 1) {
    if (digitalRead(PIN_ENCODEUR_DT) != etatClkActuel) resultat = 1;
    else resultat = -1;
  }
  dernierEtatClk = etatClkActuel;
  return resultat;
}
