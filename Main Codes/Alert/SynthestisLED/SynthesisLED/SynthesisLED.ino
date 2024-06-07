#define PHOTO_PIN 16   // Broche analogique utilisée pour le capteur de lumière
#define YELLOW_LED_PIN 5  // Broche du LED jaune

void setup() {
  Serial.begin(9600);
  pinMode(PHOTO_PIN, INPUT);    // Définir la broche PHOTO_PIN comme une entrée
  pinMode(YELLOW_LED_PIN, OUTPUT); // Définir la broche du LED jaune comme une sortie
}

void loop() {
  // Lire la valeur du capteur de lumière
  int lightValue = analogRead(PHOTO_PIN);
  
  // Afficher la valeur lue sur le moniteur série
  Serial.print("Valeur du capteur de lumière : ");
  Serial.println(lightValue);

  // Contrôler la LED jaune en fonction de la luminosité mesurée
  if (lightValue < SEUIL_LUMIERE) {
    digitalWrite(YELLOW_LED_PIN, HIGH); // Allumer la LED jaune si la luminosité est inférieure au seuil
  } else {
    digitalWrite(YELLOW_LED_PIN, LOW); // Éteindre la LED jaune sinon
  }

  // Attendre un court délai avant de lire à nouveau
  delay(1000);
}
