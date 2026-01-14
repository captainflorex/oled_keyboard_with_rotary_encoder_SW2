#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- CONFIGURATION ---
#define MAX_LONGUEUR_MSG 100 

#define LARGEUR_ECRAN 128
#define HAUTEUR_ECRAN 64
Adafruit_SSD1306 display(LARGEUR_ECRAN, HAUTEUR_ECRAN, &Wire, -1);

// --- BRANCHEMENTS (PINS) ---
const int PIN_ENCODEUR_CLK = 3;
const int PIN_ENCODEUR_DT  = 4;
const int PIN_ENCODEUR_SW  = 2;
const int PIN_BOUTON_SW3   = A6;  

// Ajout d'un état pour le sous-menu réglages
enum Etat { ETAT_MENU, ETAT_MENU_REGLAGES, ETAT_ECRITURE};
Etat etatActuel = ETAT_MENU;

// DONNEES TEXTE
char message[MAX_LONGUEUR_MSG + 1];           
char messageRecu[MAX_LONGUEUR_MSG + 1];  
int positionCurseur = 0; 

char monPseudo[MAX_LONGUEUR_PSEUDO + 1]; 
char pseudoRecu[MAX_LONGUEUR_PSEUDO + 1];
int curseurPseudo = 0; 

const char listeCaracteres[] = "< abcdefghijklmnopqrstuvwxyz\x85\x82\x8A\x88\x87 ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,?!";
const int tailleListe = sizeof(listeCaracteres) - 1;
int indexCaractereSelectionne = 1; 

int optionMenu = 0; 
int optionSousMenu = 0; // Pour le menu réglages

unsigned long dernierAppuiBouton = 0;
int dernierEtatClk;

// --- PROTOTYPES ---
int lireRotationEncodeur();
void afficherMenu();
void afficherMenuReglages(); // NOUVEAU
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

// --- AFFICHAGES AVEC CADRES ---

void afficherMenu() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(40, 0); display.println(F("- MENU -"));
  
  // Cadre autour de la sélection
  if (optionMenu == 0) display.drawRoundRect(0, 20, 128, 18, 4, SSD1306_WHITE);
  else if (optionMenu == 1) display.drawRoundRect(0, 42, 128, 18, 4, SSD1306_WHITE);

  display.setCursor(10, 25); display.print(F("Ecrire Message")); 
  display.setCursor(10, 47); display.print(F("Reglages"));
  
  display.display();
}

void afficherMenuReglages() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(30, 0); display.println(F("- REGLAGES -"));
  
  // Cadre dynamique
  int y = 15 + (optionSousMenu * 12);
  display.drawRoundRect(0, y-2, 128, 13, 3, SSD1306_WHITE);

  display.setCursor(10, 15); display.print(F("TO FILL"));
  display.setCursor(10, 27); display.print(F("TO FILL"));
  display.setCursor(10, 39); display.print(F("TO FILL"));
  display.setCursor(10, 51); display.print(F("Retour"));

  display.display();
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

// --- SETUP & LOOP ---

void setup() {
  pinMode(PIN_ENCODEUR_CLK, INPUT_PULLUP);
  pinMode(PIN_ENCODEUR_DT, INPUT_PULLUP);
  pinMode(PIN_ENCODEUR_SW, INPUT_PULLUP);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
    }
  }
  display.display(); delay(500); display.clearDisplay();
  dernierEtatClk = digitalRead(PIN_ENCODEUR_CLK);
  
  switch(etatActuel) {
    case ETAT_MENU: afficherMenu(); break;
    case ETAT_MENU_REGLAGES: afficherMenuReglages(); break;
    case ETAT_ECRITURE: afficherEcritureMessage(); break;
    default: etatActuel = ETAT_MENU; afficherMenu(); break;
  }
}

void loop() {
  int rotation = lireRotationEncodeur();
  bool clicEncodeur = (digitalRead(PIN_ENCODEUR_SW) == LOW);
  bool clicBoutonSW3 = (analogRead(PIN_BOUTON_SW3) < 100); 

  if ((clicEncodeur || clicBoutonSW3) && (millis() - dernierAppuiBouton > 200)) {
    dernierAppuiBouton = millis(); 
  } else {
    clicEncodeur = false;
    clicBoutonSW3 = false;
  }

  // --- LOGIQUE D'ETATS MODIFIEE ---

  switch (etatActuel) {
    case ETAT_MENU:
      if (rotation != 0) {
        optionMenu += rotation;
        if (optionMenu < 0) optionMenu = 1; else if (optionMenu > 1) optionMenu = 0;
        afficherMenu();
      }
      if (clicEncodeur) {
        if (optionMenu == 0) { // ECRIRE MESSAGE
           etatActuel = ETAT_ECRITURE;
           positionCurseur = 0;
           memset(message, 0, sizeof(message)); 
           indexCaractereSelectionne = 1; 
        } else if (optionMenu == 1) { // REGLAGES
           etatActuel = ETAT_MENU_REGLAGES;
           optionSousMenu = 0;
        }
      }
      break;

    case ETAT_MENU_REGLAGES: // NOUVEAU SOUS-MENU
      if (rotation != 0) {
        optionSousMenu += rotation;
        if (optionSousMenu < 0) optionSousMenu = 3; else if (optionSousMenu > 3) optionSousMenu = 0;
        afficherMenuReglages();
      }
      if (clicEncodeur) {
        if (optionSousMenu == 0) { // TO FILL
        } else if (optionSousMenu == 1) { // TO FILL
        } else if (optionSousMenu == 2) { // TO FILL
        } else if (optionSousMenu == 3) { // Retour
           etatActuel = ETAT_MENU;
        }
      }
      break;

    case ETAT_ECRITURE:
      if (rotation != 0) {
        indexCaractereSelectionne += rotation;
        if (indexCaractereSelectionne >= tailleListe) indexCaractereSelectionne = 0;
        else if (indexCaractereSelectionne < 0) indexCaractereSelectionne = tailleListe - 1;
        afficherEcritureMessage();
      }
      if (clicEncodeur) {
        if (listeCaracteres[indexCaractereSelectionne] == '<') { 
           etatActuel = ETAT_MENU; 
        } 
        else if (positionCurseur < MAX_LONGUEUR_MSG) {
           message[positionCurseur] = listeCaracteres[indexCaractereSelectionne];
           positionCurseur++;
           message[positionCurseur] = '\0';
           afficherEcritureMessage();
        }
      }
      break;
  }
}