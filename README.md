# OLED Keyboard with Rotary Encoder

[🇫🇷 Français](#français) | [🇬🇧 English](#english)

---

## Français

### 📝 Description

Ce projet Arduino permet de créer une interface de saisie de texte interactive utilisant :
- Un **écran OLED 128x64** (SSD1306)
- Un **encodeur rotatif** avec bouton intégré
- Un système de menu navigable

L'utilisateur peut écrire des messages en sélectionnant des caractères via l'encodeur rotatif et naviguer dans différents menus.

### 🔧 Composants requis

- Arduino (Uno, Nano, ou compatible)
- Écran OLED 128x64 (SSD1306) avec interface I2C
- Encodeur rotatif avec bouton (KY-040 ou similaire)
- Bouton supplémentaire (optionnel - SW3)
- Câbles de connexion

### 📌 Branchements

| Composant | Pin Arduino |
|-----------|-------------|
| Encodeur CLK | D3 |
| Encodeur DT | D4 |
| Encodeur SW | D2 |
| Bouton SW3 | A6 |
| OLED SDA | A4 (SDA) |
| OLED SCL | A5 (SCL) |

### 📚 Bibliothèques nécessaires

Installez ces bibliothèques via le gestionnaire de bibliothèques Arduino :

```
- Wire (incluse avec Arduino)
- Adafruit GFX Library
- Adafruit SSD1306
```

### 🚀 Installation

1. Clonez ce dépôt ou téléchargez le fichier `code.ino`
2. Ouvrez le fichier avec l'IDE Arduino
3. Installez les bibliothèques requises
4. Connectez les composants selon le schéma de branchement
5. Téléversez le code sur votre Arduino

### 💡 Utilisation

#### Menu principal
- **Tourner l'encodeur** : Naviguer entre les options
- **Appuyer sur l'encodeur** : Sélectionner une option

#### Options disponibles
1. **Écrire Message** : Interface de saisie de texte
2. **Réglages** : Menu de configuration (à compléter)

#### Mode écriture
- **Tourner l'encodeur** : Parcourir les caractères disponibles
- **Appuyer sur l'encodeur** : Valider le caractère sélectionné
- **Sélectionner "<"** : Retour au menu principal

### 📋 Caractères disponibles

Le système permet de saisir :
- Lettres minuscules (a-z)
- Caractères accentués (é, è, ê, ë, à)
- Lettres majuscules (A-Z)
- Chiffres (0-9)
- Ponctuation (.,?!)
- Espace

### ⚙️ Configuration

Vous pouvez modifier ces paramètres dans le code :

```cpp
#define MAX_LONGUEUR_MSG 100  // Longueur maximale du message
#define LARGEUR_ECRAN 128     // Largeur de l'écran OLED
#define HAUTEUR_ECRAN 64      // Hauteur de l'écran OLED
```

### 🔮 Fonctionnalités à venir

- Envoi de messages
- Réception de messages
- Configuration du pseudo
- Réglages personnalisables

### 📄 Licence

Ce projet est sous licence MIT. Voir le fichier [LICENSE](LICENSE) pour plus de détails.

---

## English

### 📝 Description

This Arduino project creates an interactive text input interface using:
- A **128x64 OLED display** (SSD1306)
- A **rotary encoder** with integrated button
- A navigable menu system

Users can write messages by selecting characters via the rotary encoder and navigate through different menus.

### 🔧 Required Components

- Arduino (Uno, Nano, or compatible)
- 128x64 OLED display (SSD1306) with I2C interface
- Rotary encoder with button (KY-040 or similar)
- Additional button (optional - SW3)
- Connection wires

### 📌 Wiring

| Component | Arduino Pin |
|-----------|-------------|
| Encoder CLK | D3 |
| Encoder DT | D4 |
| Encoder SW | D2 |
| Button SW3 | A6 |
| OLED SDA | A4 (SDA) |
| OLED SCL | A5 (SCL) |

### 📚 Required Libraries

Install these libraries through the Arduino Library Manager:

```
- Wire (included with Arduino)
- Adafruit GFX Library
- Adafruit SSD1306
```

### 🚀 Installation

1. Clone this repository or download the `code.ino` file
2. Open the file with Arduino IDE
3. Install the required libraries
4. Connect the components according to the wiring diagram
5. Upload the code to your Arduino

### 💡 Usage

#### Main Menu
- **Rotate encoder**: Navigate between options
- **Press encoder**: Select an option

#### Available Options
1. **Write Message**: Text input interface
2. **Settings**: Configuration menu (to be completed)

#### Writing Mode
- **Rotate encoder**: Browse available characters
- **Press encoder**: Validate selected character
- **Select "<"**: Return to main menu

### 📋 Available Characters

The system allows input of:
- Lowercase letters (a-z)
- Accented characters (é, è, ê, ë, à)
- Uppercase letters (A-Z)
- Numbers (0-9)
- Punctuation (.,?!)
- Space

### ⚙️ Configuration

You can modify these parameters in the code:

```cpp
#define MAX_LONGUEUR_MSG 100  // Maximum message length
#define LARGEUR_ECRAN 128     // OLED screen width
#define HAUTEUR_ECRAN 64      // OLED screen height
```

### 🔮 Upcoming Features

- Message sending
- Message receiving
- Nickname configuration
- Customizable settings

### 📄 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

---

**Made with ❤️ for Arduino enthusiasts**
