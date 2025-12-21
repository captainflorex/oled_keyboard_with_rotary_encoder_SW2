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
void biper();

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

void biper() {
  tone(PIN_BUZZER, 2000, 50); 
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
}

void loop() {
  int rotation = lireRotationEncodeur();
  bool clicEncodeur = (digitalRead(PIN_ENCODEUR_SW) == LOW);
  bool clicBoutonSW3 = (analogRead(PIN_BOUTON_SW3) < 100); 

  if ((clicEncodeur || clicBoutonSW3) && (millis() - dernierAppuiBouton > 200)) {
    dernierAppuiBouton = millis(); 
    biper(); 
  } else {
    clicEncodeur = false;
    clicBoutonSW3 = false;
  }
if (rotation != 0) {
        indexCaractereSelectionne += rotation;
        if (indexCaractereSelectionne >= tailleListe) indexCaractereSelectionne = 0;
        else if (indexCaractereSelectionne < 0) indexCaractereSelectionne = tailleListe - 1;
        afficherEcritureMessage();
      }
      if (clicEncodeur) {
        if (listeCaracteres[indexCaractereSelectionne] == '<') { 
           etatActuel = ETAT_MENU; 
           sauvegarderTout();
           afficherMenu(); 
        } 
        else if (positionCurseur < MAX_LONGUEUR_MSG) {
           message[positionCurseur] = listeCaracteres[indexCaractereSelectionne];
           positionCurseur++;
           message[positionCurseur] = '\0';
           sauvegarderTout(); 
           afficherEcritureMessage();
        }
      }
      if (clicBoutonSW3) {
        etatActuel = ETAT_PRIORITE;
        prioriteMessage = 1; 
        changerCouleurLed(0, 0, 255); 
        sauvegarderTout();
        afficherChoixPriorite();
      }
}
