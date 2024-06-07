#include <DHT.h>
#include <ESP8266WiFi.h>

#define DHTPIN 5        // Broche de données du capteur DHT11
#define DHTTYPE DHT11   // Type de capteur (DHT11 ou DHT22)
#define PIR_PIN 4       // Broche du capteur de mouvement (PIR)
#define RELAY_PIN 12    // Broche du relais pour la lampe

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  dht.begin();
}

void loop() {
  // Lecture de la température
  float temperature = dht.readTemperature();

  // Lecture de la détection de mouvement
  int motionDetected = digitalRead(PIR_PIN);

  // Affichage de la température
  Serial.print("Température: ");
  Serial.print(temperature);
  Serial.println("°C");

  // Affichage de la détection de mouvement
  Serial.print("Détection de mouvement: ");
  Serial.println(motionDetected ? "Détecté" : "Non détecté");

  // Contrôle de la lampe en fonction des conditions
  if (temperature < 5 || motionDetected) {
    digitalWrite(RELAY_PIN, HIGH);  // Allumer la lampe
    Serial.println("Lampe allumée");
    delay(59000);
  } else {
    digitalWrite(RELAY_PIN, LOW);   // Éteindre la lampe
    Serial.println("Lampe éteinte");
  }

  delay(1000);  // Attente d'une seconde entre chaque lecture
}
