#include <DHT.h>
#include <WiFi.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define PIR_PIN 4
#define RELAY_PIN 12
#define buzzerPin 16
#define waterLevelPin 2
#define RED_PIN 5
#define GREEN_PIN 4
#define BLUE_PIN 0
//#define PHOTO_PIN 16
#define YELLOW_LED_PIN 5
#define RECEIVER_PIN 5
#define BUTTON_PIN 4
#define LAMP_RELAY_PIN D1
//#define PUMP_RELAY_PIN D2
#define ON_CODE 0xF7C03F
#define OFF_CODE 0xF740BF
#define LAMP_ON_CODE 0xF7807F
#define LAMP_OFF_CODE 0xF700FF
#define PUMP_ON_CODE 0xF7E01F
#define TEMPERATURE_THRESHOLD 30.0
#define HUMIDITY_THRESHOLD 50
#define SEUIL_LUMIERE 500

DHT dht(DHTPIN, DHTTYPE);
IRrecv irReceiver(RECEIVER_PIN);
decode_results results;

bool systemState = false;
bool lampState = false;
bool pumpState = false;

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(waterLevelPin, INPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  //pinMode(PHOTO_PIN, INPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LAMP_RELAY_PIN, OUTPUT);
  //pinMode(PUMP_RELAY_PIN, OUTPUT);
  dht.begin();
  irReceiver.enableIRIn();
}

void loop() {
  // Niveau 3: Allumer lampe si mouvement ou température < 5
  float temperature = dht.readTemperature();
  int motionDetected = digitalRead(PIR_PIN);
  Serial.print("Température: ");
  Serial.print(temperature);
  Serial.println("°C");
  Serial.print("Détection de mouvement: ");
  Serial.println(motionDetected ? "Détecté" : "Non détecté");
  if (temperature < 5 || motionDetected) {
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Lampe allumée");
    delay(59000);
  } else {
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Lampe éteinte");
  }

  // Niveau 2: Buzzer pour température critique ou niveau d'eau bas
  int waterLevel = digitalRead(waterLevelPin);
  if (temperature > 38 || temperature < 0) {
    buzz(1000);
    Serial.println("Alerte : Température critique !");
  }
  if (waterLevel == LOW) {
    buzz(1000);
    Serial.println("Alerte : Niveau d'eau bas !");
  }
  Serial.print("Niveau d'eau: ");
  Serial.println(waterLevel == HIGH ? "Élevé" : "Bas");

  // Niveau 1: LED RGB pour état de la plante
  float humidity = dht.readHumidity();
  float tempScore = 0.5 * (abs(temperature - TEMPERATURE_THRESHOLD) - 5);
  float humiScore = 0.2 * abs(humidity - HUMIDITY_THRESHOLD);
  float totalScore = tempScore + humiScore;
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Échec de lecture du capteur DHT !");
  } else {
    Serial.print("Humidité: ");
    Serial.print(humidity);
    Serial.print("%\t");
    Serial.print("Température: ");
    Serial.print(temperature);
    Serial.println("°C");
    Serial.print("Le rapport : ");
    Serial.println(totalScore);
    if (totalScore <= 10) {
      setColor(0, 255, 0);
    } else if (totalScore <= 15) {
      setColor(255, 0, 255);
    } else {
      setColor(255, 0, 0);
    }
  }

  /* Indicateur de lumière avec LED jaune
  int lightValue = analogRead(PHOTO_PIN);
  Serial.print("Valeur du capteur de lumière : ");
  Serial.println(lightValue);
  if (lightValue < SEUIL_LUMIERE) {
    digitalWrite(YELLOW_LED_PIN, HIGH);
  } else {
    digitalWrite(YELLOW_LED_PIN, LOW);
  }*/

  // Contrôle via télécommande IR
  if (irReceiver.decode(&results)) {
    Serial.print("Code IR reçu : 0x");
    Serial.println(results.value, HEX);
    handleIRCode(results.value);
    irReceiver.resume();
  }

  // Contrôle manuel avec bouton poussoir
  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == LOW) {
    systemState = !systemState;
    delay(100);
  }
  if (systemState) {
    Serial.println("Le système est allumé !");
    if (lampState) {
      digitalWrite(LAMP_RELAY_PIN, HIGH);
    } else {
      digitalWrite(LAMP_RELAY_PIN, LOW);
    }
    /*if (pumpState) {
      digitalWrite(PUMP_RELAY_PIN, HIGH);
    } else {
      digitalWrite(PUMP_RELAY_PIN, LOW);
    }*/
  } else {
    Serial.println("Le système est éteint !");
    digitalWrite(LAMP_RELAY_PIN, LOW);
    digitalWrite(PUMP_RELAY_PIN, LOW);
  }

  delay(1000); // Délai général pour stabiliser le système
}

void buzz(unsigned int duration) {
  tone(buzzerPin, 1000);
  delay(duration);
  noTone(buzzerPin);
}

void setColor(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}

void handleIRCode(uint32_t code) {
  switch (code) {
    case ON_CODE:
      systemState = true;
      break;
    case OFF_CODE:
      systemState = false;
      break;
    case LAMP_ON_CODE:
      lampState = true;
      break;
    case LAMP_OFF_CODE:
      lampState = false;
      break;
    case PUMP_ON_CODE:
      pumpState = !pumpState;
      break;
    default:
      break;
  }
}
