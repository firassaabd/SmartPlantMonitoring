#include <IRremoteESP8266.h>
#include <IRrecv.h>
//#include <IRsend.h>
#include <IRutils.h>

#define RECEIVER_PIN 5 // Broche de réception IR
//#define TRANSMITTER_PIN 4 // Broche de l'émetteur IR
//#define BUTTON_PIN 2 // Broche du bouton-poussoir

IRrecv irReceiver(RECEIVER_PIN);
//IRsend irTransmitter(TRANSMITTER_PIN);

decode_results results;

bool receiverEnabled = true; // Définit l'état initial du récepteur IR à activé

void setup() {
  Serial.begin(115200);
  irReceiver.enableIRIn(); // Démarre la réception IR
  //pinMode(BUTTON_PIN, INPUT_PULLUP); // Configure le bouton-poussoir en entrée avec une résistance de pull-up interne
  //Serial.println("Initialisation terminée.");
}

void loop() {
  /* Vérifie si le bouton-poussoir est enfoncé
  if (digitalRead(BUTTON_PIN) == LOW) {
    // Inverse l'état du récepteur IR lorsque le bouton est enfoncé
    receiverEnabled = !receiverEnabled;
    Serial.print("Bouton-poussoir enfoncé. Récepteur IR ");
    Serial.println(receiverEnabled ? "activé." : "désactivé.");
    delay(500); // Attente pour éviter les rebonds
  }*/

  // Si le récepteur IR est activé, vérifie la réception de signaux IR
  if (receiverEnabled && irReceiver.decode(&results)) {
    // Affiche le code de la télécommande reçu
    Serial.print("Code IR reçu : 0x");
    Serial.println(results.value, HEX);
    irReceiver.resume(); // Continue la réception IR
  }

  /* Si le récepteur IR est désactivé, envoie un signal IR à intervalles réguliers
  if (!receiverEnabled) {
    Serial.println("Récepteur IR désactivé. Envoi du signal IR...");
    irTransmitter.sendNEC(0x00FF30CF, 32); // Code NEC pour la commande ON/OFF
    delay(1000); // Attente entre les transmissions
    Serial.println("Signal IR envoyé.");
  }*/
}
