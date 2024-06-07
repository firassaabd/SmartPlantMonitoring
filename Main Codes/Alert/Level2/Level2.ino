#include <DHT.h>

#define DHTPIN 5 // Broche de données du capteur DHT11
#define DHTTYPE DHT11 // Type de capteur (DHT11 ou DHT22)
#define buzzerPin 16 // Broche pour le buzzer actif
#define waterLevelPin 13 // Broche à laquelle le capteur de niveau d'eau est connecté
//#define motionSensorPin 4 // Broche à laquelle le capteur de mouvement est connecté

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
 
  pinMode(buzzerPin, OUTPUT); // Initialise la broche du buzzer actif en tant que sortie
  pinMode(waterLevelPin, INPUT); // Initialise la broche du capteur de niveau d'eau comme une entrée
  //pinMode(motionSensorPin, INPUT); // Initialise la broche du capteur de mouvement comme une entrée
  dht.begin(); // Initialise le capteur DHT11
}

void loop() {
  float temperature = dht.readTemperature(); // Lire la température en Celsius
  int waterLevel = digitalRead(waterLevelPin); // Lecture de l'état du capteur de niveau d'eau
 // int motionState = digitalRead(motionSensorPin); // Lecture de l'état du capteur de mouvement

  // Vérification de la température
  if (temperature > 38 || temperature < 0) {
    buzz(1000); // Activer le buzzer pendant 1 seconde
    Serial.println("Alerte : Température critique !");
  }

  // Vérification du niveau d'eau
  if (waterLevel == LOW) {
    buzz(1000); // Activer le buzzer pendant 1 seconde
    Serial.println("Alerte : Niveau d'eau bas !");
  }

  // Vérification du capteur de mouvement
  //if (motionState == HIGH) {
  //  buzz(1000); // Activer le buzzer pendant 1 seconde
  //  Serial.println("Alerte : Mouvement détecté !");
  //}

  // Affichage des valeurs lues dans le moniteur série
  Serial.print("Température: ");
  Serial.print(temperature);
  Serial.println("°C");
  Serial.print("Niveau d'eau: ");
  if (waterLevel == HIGH) {
    Serial.println("Niveau d'eau élevé");
  } else {
    Serial.println("Niveau d'eau bas");
  }
  //Serial.println(waterLevel == HIGH ? "Élevé" : "Bas");
  //Serial.print("Détection de mouvement: ");
  //Serial.println(motionState == HIGH ? "Oui" : "Non");

  delay(2000); // Attente d'une seconde avant la prochaine vérification
}

// Fonction pour activer le buzzer pendant une durée spécifiée en millisecondes
void buzz(unsigned int duration) {
  tone(buzzerPin, 1000); // Joue un signal à une fréquence de 1000 Hz sur la broche du buzzer
  delay(duration); // Active le buzzer pendant la durée spécifiée
  noTone(buzzerPin); // Désactive le buzzer après la durée spécifiée
}
