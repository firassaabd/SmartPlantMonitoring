#include <DHT.h>
#define DHTPIN 2 // Définir le pin de données du capteur DHT11
#define DHTTYPE DHT11 // Définir le type de capteur (DHT11 ou DHT22)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000); // Attente de 2 secondes entre les lectures
  float humidity = dht.readHumidity(); // Lire l'humidité
  float temperature = dht.readTemperature(); // Lire la température en Celsius
  // Vérifier si la lecture a réussi
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Échec de lecture du capteur DHT !");
    return;
  }
  // Afficher les valeurs lues
  Serial.print("Humidité: ");
  Serial.print(humidity);
  Serial.print("%\t");
  Serial.print("Température: ");
  Serial.print(temperature);
  Serial.println("°C");
}
