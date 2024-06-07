#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define TEMPERATURE_THRESHOLD 30.0 // Seuil de température (en degrés Celsius)
#define HUMIDITY_THRESHOLD 50 // Seuil d'humidité (en pourcentage)
//#define SOIL_MOISTURE_THRESHOLD 300 // Seuil d'humidité du sol (valeur analogique)

#define RED_PIN 5
#define GREEN_PIN 4
#define BLUE_PIN 0

#define TEMPERATURE_WEIGHT 0.5 // Pondération pour la température
//#define HUMIDITY_WEIGHT 0.3 // Pondération pour l'humidité du sol
#define AMBIENT_HUMIDITY_WEIGHT 0.2 // Pondération pour l'humidité ambiante

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  delay(2000);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  //int soilMoisture = analogRead(A0); // Lecture de l'humidité du sol
  
  // Calcul des scores pondérés pour chaque paramètre
  float tempScore = TEMPERATURE_WEIGHT * (abs(temperature - TEMPERATURE_THRESHOLD)-5);
  float humiScore = AMBIENT_HUMIDITY_WEIGHT * abs(humidity - AMBIENT_HUMIDITY_WEIGHT);
 // float soilScore = SOIL_MOISTURE_THRESHOLD * abs(soilMoisture - SOIL_MOISTURE_THRESHOLD);

  // Calcul du rapport global
  float totalScore = tempScore + humiScore; //+ soilScore
  
  //Affichage
  // Vérifier si la lecture a réussi
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Échec de lecture du capteur DHT !");
  }
  else
  {
  // Afficher les valeurs lues
  Serial.print("Humidité: ");
  Serial.print(humidity);
  Serial.print("%\t");
  Serial.print("Température: ");
  Serial.print(temperature);
  Serial.println("°C");
  Serial.print(" Le rapport : ");
  Serial.println(totalScore);
    // Ajustement de la couleur en fonction du score total
  if (totalScore <= 10) {
    setColor(0, 255, 0); // Vert
  } else if (totalScore <= 15) {
    setColor(255, 0, 255); // Bleu
  } else {
    setColor(255, 0, 0); // Rouge
  }
  }
}

void setColor(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}
