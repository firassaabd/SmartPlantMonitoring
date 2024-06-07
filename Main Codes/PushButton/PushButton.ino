#define buttonPin 5 // Broche à laquelle le bouton est connecté
bool systemState = false; // État initial du système (éteint)

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Configure la broche du bouton comme entrée avec une résistance de tirage
  Serial.begin(115200);
}

void loop() {
  // Lecture de l'état du bouton
  int buttonState = digitalRead(buttonPin);

  // Si le bouton est enfoncé (état bas), bascule l'état du système
  if (buttonState == LOW) {
    systemState = !systemState; // Bascule l'état du système
    delay(100); // Anti-rebond (débouncing)
  }

  // Si le système est allumé, effectuez les actions correspondantes
  if (systemState) {
    // Actions lorsque le système est allumé
    Serial.println("Le système est allumé !");
  } else {
    // Actions lorsque le système est éteint
    Serial.println("Le système est éteint !");
  }
  delay(800);
}
