// Broche pour le buzzer actif
#define buzzerPin 16

void setup() {
  // Initialise la broche du buzzer actif en tant que sortie
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Exemple de chaque fonction de base

  // 1. Activer le buzzer pour une durée de 1 seconde
  buzz(1000);
  delay(1000);

  // 2. Activer le buzzer pour une durée de 500 millisecondes
  buzz(500);
  delay(1000);

  // 3. Activer le buzzer pour une durée de 2 secondes
  buzz(2000);
  delay(1000);

  // 4. Activer le buzzer pour une durée de 300 millisecondes
  buzz(300);
  delay(1000);

  // 5. Activer le buzzer pour une durée de 1.5 secondes
  buzz(1500);
  delay(1000);

  // 6. Activer le buzzer pour une durée de 400 millisecondes
  buzz(400);
  delay(1000);

  // 7. Désactiver le buzzer
  noBuzz();
  delay(1000);
}

// Fonction pour activer le buzzer pendant une durée spécifiée en millisecondes
void buzz(unsigned int duration) {
  tone(buzzerPin, 1000); // Joue un signal à une fréquence de 1000 Hz sur la broche du buzzer
  delay(duration);       // Active le buzzer pendant la durée spécifiée
  noBuzz();              // Désactive le buzzer après la durée spécifiée
}

// Fonction pour désactiver le buzzer
void noBuzz() {
  noTone(buzzerPin); // Arrête de jouer le signal sur la broche du buzzer
} 
