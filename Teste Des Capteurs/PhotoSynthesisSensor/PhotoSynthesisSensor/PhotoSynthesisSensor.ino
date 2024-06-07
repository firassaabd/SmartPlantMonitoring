#define PHOTO_PIN A0 // Broche analogique utilisée pour le capteur de lumière

void setup() {
  Serial.begin(9600);
  pinMode(PHOTO_PIN, INPUT); // Définir la broche PHOTO_PIN comme une entrée
}

void loop() {
  // Lire la valeur du capteur de lumière
  int lightValue = analogRead(PHOTO_PIN);
  
  // Afficher la valeur lue sur le moniteur série
  Serial.print("Valeur du capteur de lumière : ");
  Serial.println(lightValue);

  // Attendre un court délai avant de lire à nouveau
  delay(1000);
}
