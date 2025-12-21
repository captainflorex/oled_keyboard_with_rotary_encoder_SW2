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
void afficherEcritureMessage();

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

void afficherEcritureMessage() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0); display.print(F("Message (")); display.print(positionCurseur); display.print(F(")"));
  display.setCursor(0, 15); display.print(message);
  display.fillRect(0, 50, 128, 14, SSD1306_WHITE);
  display.setTextColor(SSD1306_BLACK);
  
  if (listeCaracteres[indexCaractereSelectionne] == '<') { display.setCursor(45, 53); display.print(F("EFFACER")); } 
  else { display.setCursor(60, 53); display.print(listeCaracteres[indexCaractereSelectionne]); }
  display.display();
}

void setup() {
  pinMode(PIN_ENCODEUR_CLK, INPUT_PULLUP);
  pinMode(PIN_ENCODEUR_DT, INPUT_PULLUP); // IF LAKING EXTERN RES
  pinMode(PIN_ENCODEUR_SW, INPUT_PULLUP); //SI ABSENCE DE RESISTANCES EXTERNES
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
   }
  }
  display.display(); delay(500); display.clearDisplay();
  dernierEtatClk = digitalRead(PIN_ENCODEUR_CLK);
switch(etatActuel) {
    /*case ETAT_MENU: afficherMenu(); break;
    case ETAT_MENU_REGLAGES: afficherMenuReglages(); break;*/
    case ETAT_ECRITURE: afficherEcritureMessage(); break;
    /*case ETAT_PRIORITE: afficherChoixPriorite(); break;
    case ETAT_EDIT_PSEUDO: afficherEcriturePseudo(); break;
    case ETAT_CONFIG_CANAL: afficherConfigCanal(); break;
    case ETAT_CONFIG_SON: afficherConfigSon(); break;
    case ETAT_LECTURE: afficherMessageRecu(); break;*/
    default: etatActuel = ETAT_ECRITURE; afficherEcritureMessage(); break;
  }
}
