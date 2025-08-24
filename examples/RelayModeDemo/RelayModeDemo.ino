/*
 * RelayModeDemo.ino - Esempio per M5450 in Modalità Relè
 *
 * Questo sketch dimostra come usare la libreria per controllare
 * uscite indipendenti (relè, LED, etc.) usando la numerazione da 1 a 34.
 *
 * This sketch demonstrates how to use the library to control
 * independent outputs (relays, LEDs, etc.) using 1-to-34 numbering.
 */
#include <M5450.h>

const uint8_t DATA_PIN = 2;
const uint8_t CLOCK_PIN = 3;
const uint8_t STROBE_PIN = 4;

// Inizializza la libreria in modalità relè (parametro numDigits omesso o a 0)
// Initialize the library in relay mode (numDigits parameter omitted or set to 0)
M5450 relays(DATA_PIN, CLOCK_PIN, STROBE_PIN);

void setup() {
  Serial.begin(115200);
  relays.begin();
  Serial.println("Demo Modalità Relè Avviata...");
}

void loop() {
  // 1. Controllare un singolo relè (OUT1)
  // 1. Control a single relay (OUT1)
  Serial.println("Accendo il relè 1 per 1 secondo...");
  relays.setRelay(1, true);
  relays.update();
  delay(1000);

  Serial.println("Spengo il relè 1 per 1 secondo...");
  relays.setRelay(1, false);
  relays.update();
  delay(1000);

  // 2. Controllare un gruppo di relè
  // 2. Control a group of relays
  uint8_t mioGruppo[] = {15, 20, 25, 34};
  uint8_t dimensioneGruppo = sizeof(mioGruppo) / sizeof(mioGruppo[0]);
  
  Serial.println("Accendo il gruppo {15, 20, 25, 34} per 2 secondi...");
  relays.setRelayGroup(mioGruppo, dimensioneGruppo, true);
  relays.update();
  delay(2000);

  Serial.println("Spengo il gruppo {15, 20, 25, 34}");
  relays.setRelayGroup(mioGruppo, dimensioneGruppo, false);
  relays.update();
}

