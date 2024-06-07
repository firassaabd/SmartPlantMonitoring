// Définition de la broche à laquelle le capteur de mouvement est connecté
#define motionSensorPin 5

void setup() {
  // Initialise la communication série à une vitesse de 9600 bauds
  Serial.begin(9600);

  // Configure la broche du capteur de mouvement comme une entrée
  pinMode(motionSensorPin, INPUT);
  
}

void loop() {

  // Lit l'état du capteur de mouvement
  int motionState = digitalRead(motionSensorPin);

  Serial.print("Valeur de motionState : ");
  Serial.println(motionState);

  // Affiche l'état du capteur de mouvement
  if (motionState == HIGH) {
    Serial.println("Mouvement détecté !");
  } else {
    Serial.println("Aucun mouvement détecté.");
  }

  // Attends un court délai avant de lire à nouveau
  delay(1000);
}
