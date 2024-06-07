// Broches pour la LED RGB (connectez-les aux broches PWM de votre ESP8266)
#define redPin 16
#define greenPin 5
#define bluePin 4

void setup() {
  // Initialise les broches de la LED RGB en tant que sorties
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // Exemple de chaque fonction de base

  // 1. Allumer la LED en rouge
  setColor(255, 0, 0);
  delay(1000);

  // 2. Allumer la LED en vert
  setColor(0, 255, 0);
  delay(1000);

  // 3. Allumer la LED en bleu
  setColor(0, 0, 255);
  delay(1000);

  // 4. Mélanger les couleurs (cyan)
  setColor(0, 255, 255);
  delay(1000);

  // 5. Mélanger les couleurs (magenta)
  setColor(255, 0, 255);
  delay(1000);

  // 6. Mélanger les couleurs (jaune)
  setColor(255, 255, 0);
  delay(1000);

  // 7. Éteindre la LED
  turnOff();
  delay(1000);
}

// Fonction pour définir la couleur de la LED RGB
void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);     // Définit l'intensité lumineuse de la LED rouge
  analogWrite(greenPin, greenValue); // Définit l'intensité lumineuse de la LED verte
  analogWrite(bluePin, blueValue);   // Définit l'intensité lumineuse de la LED bleue
}

// Fonction pour éteindre la LED RGB
void turnOff() {
  setColor(0, 0, 0); // Définit toutes les couleurs à 0 (éteint la LED)
} 
