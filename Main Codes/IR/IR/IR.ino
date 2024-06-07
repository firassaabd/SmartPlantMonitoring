#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#define RECEIVER_PIN 5 // Broche de réception IR
#define BUTTON_PIN 4    // Broche du bouton poussoir

#define LAMP_RELAY_PIN 8   // Broche de commande du relais de la lampe
#define PUMP_RELAY_PIN 9   // Broche de commande du relais de la pompe

#define ON_CODE 0xF7C03F         // Code pour allumer
#define OFF_CODE 0xF740BF        // Code pour éteindre
#define LAMP_ON_CODE 0xF7807F    // Code pour allumer la lampe
#define LAMP_OFF_CODE 0xF700FF   // Code pour éteindre la lampe
#define PUMP_ON_CODE 0xF7E01F    // Code pour allumer la pompe

IRrecv irReceiver(RECEIVER_PIN);
decode_results results;

bool systemState = false; // État du système
bool lampState = false;   // État de la lampe
bool pumpState = false;   // État de la pompe

void setup() {
  Serial.begin(115200);
  irReceiver.enableIRIn(); // Activation du récepteur IR
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Définir le bouton poussoir en entrée avec pull-up
  pinMode(LAMP_RELAY_PIN, OUTPUT);   // Définir la broche du relais de la lampe en sortie
  pinMode(PUMP_RELAY_PIN, OUTPUT);   // Définir la broche du relais de la pompe en sortie
}

void loop() {
  // Vérifier si un signal infrarouge a été reçu
  if (irReceiver.decode(&results)) {
    // Afficher le code reçu
    Serial.print("Code IR reçu : 0x");
    Serial.println(results.value, HEX);
    // Traiter le code reçu
    handleIRCode(results.value);
    irReceiver.resume(); // Continuer à écouter les signaux infrarouges
  }

  // Vérifier si le bouton poussoir est enfoncé
  if (digitalRead(BUTTON_PIN) == LOW) {
    // Inverser l'état du système
    systemState = !systemState;
    // Attendre un court délai pour éviter les rebonds
    delay(100);
  }

  // Si le système est activé
  if (systemState) {
    // Vérifier l'état de la lampe et allumer ou éteindre si nécessaire
    if (lampState) {
      digitalWrite(LAMP_RELAY_PIN, HIGH); // Allumer la lampe
    } else {
      digitalWrite(LAMP_RELAY_PIN, LOW); // Éteindre la lampe
    }
    // Vérifier l'état de la pompe et allumer ou éteindre si nécessaire
    if (pumpState) {
      digitalWrite(PUMP_RELAY_PIN, HIGH); // Allumer la pompe
    } else {
      digitalWrite(PUMP_RELAY_PIN, LOW); // Éteindre la pompe
    }
  } else {
    // Éteindre la lampe et la pompe si le système est désactivé
    digitalWrite(LAMP_RELAY_PIN, LOW);
    digitalWrite(PUMP_RELAY_PIN, LOW);
  }
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
      // Activer la pompe si elle est actuellement éteinte, sinon la désactiver
      pumpState = !pumpState;
      break;
    default:
      // Code IR non reconnu
      break;
  }
}
