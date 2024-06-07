#define waterLevelPin 2 // Broche à laquelle le capteur de niveau d'eau est connecté

void setup() {
  Serial.begin(9600); // Démarre la communication série
  pinMode(waterLevelPin, INPUT); // Définit la broche du capteur de niveau d'eau comme une entrée
}

void loop() {
  int waterLevel = digitalRead(waterLevelPin); // Lecture de l'état du capteur de niveau d'eau

  if (waterLevel == HIGH) {
    Serial.println("Niveau d'eau élevé");
  } else {
    Serial.println("Niveau d'eau bas");
  }

  delay(1000); // Attente d'une seconde avant la prochaine lecture
}
