/*
 * HybridDemo.ino - Esempio ibrido della Libreria M5450
 *
 * Questo sketch dimostra l'uso della libreria in modalita' ibrida
 * e testa la funzionalita' di debug, stampando lo stato dei bit sul Serial Monitor.
 *
 * This sketch demonstrates the use of the library in hybrid mode
 * and tests the debug functionality by printing the bit state to the Serial Monitor.
 */

#include <M5450.h>

// --- Configurazione / Configuration ---
const uint8_t DATA_PIN = 2;
const uint8_t CLOCK_PIN = 3;
const uint8_t STROBE_PIN = 4;

// Usiamo 2 display 
// We are using 2 digits
// vedi specifiche in M5450.h
// see specification in M5450.h
const uint8_t NUM_DIGITS = 2; 

// I pin 0-13 sono ora riservati per il display.
// Pins 0-13 are now reserved for the display.
// I pin 14-33 sono disponibili come rele'.
// Pins 14-33 are available as relays.

M5450 m5450_controller(DATA_PIN, CLOCK_PIN, STROBE_PIN, NUM_DIGITS);
//M5450 m5450_controller(DATA_PIN, CLOCK_PIN, STROBE_PIN);
void setup() {
  Serial.begin(115200);
  // Scommenta la riga dopo, per il debug monitor sull'IDE Arduino /  Uncomment the line after, for debug monitor on IDE Arduino
  m5450_controller.enableDebug(true);
  // Attende che il monitor seriale sia pronto, utile per alcune schede
  // Waits for the serial monitor to be ready, useful for some boards
  while (!Serial) { 
    ; 
  }
  Serial.println("\n\nAvvio Demo Ibrida M5450... / Starting M5450 Hybrid Demo...");

  // --- ATTIVIAMO IL DEBUG! ---
  // --- LET'S ENABLE DEBUG! ---
  m5450_controller.enableDebug(true);

  // Inizializza la libreria. Questo chiamera' clear() e quindi update(),
  // vedremo la prima stampa di debug qui.
  // Initialize the library. This will call clear() and then update(),
  // so we will see the first debug print here.
  Serial.println("\nAzione: begin() -> clear()");
  m5450_controller.begin();
  delay(2000);
  
  // --- TEST DEI METODI DI GRUPPO ---
  // --- GROUP METHODS TEST ---
  
  Serial.println("\n--- Test 1: Impostare Display e Rele' insieme ---");
  Serial.println("Azione: print(12)");
  m5450_controller.print(12);

  uint8_t gruppoDaAccendere[] = {16,20,30,34};
  uint8_t dimensioneGruppo = sizeof(gruppoDaAccendere) / sizeof(gruppoDaAccendere[0]);

  Serial.println("Azione: setRelayGroup({16, 20, 30, 34}, ON)");
  m5450_controller.setRelayGroup(gruppoDaAccendere, dimensioneGruppo, true);

  // Invia lo stato combinato: il display mostrera' '12' e i 4 rele' si accenderanno
  // Send the combined state: the display will show '12' and the 4 relays will turn on
  Serial.println("Azione: update()");
  m5450_controller.update();
  delay(3000);

  // --- TEST DI clearRelays ---
  Serial.println("\n--- Test 2: Spegnere solo i rele' ---");
  Serial.println("Azione: clearRelays()");
  m5450_controller.clearRelays();
  
  // Aggiorniamo per vedere il cambiamento
  // We update to see the change
  Serial.println("Azione: update()");
  m5450_controller.update();
  delay(4000);
  
  Serial.println("\nTest concluso. Il loop non eseguira' altre azioni.");
  Serial.println("Test finished. The loop will not perform other actions.");
}

void loop() {
  // Lasciamo il loop vuoto per un test pulito e controllato nel setup.
  // We leave the loop empty for a clean and controlled test in the setup.
}
