/*
 * Esempio avanzato per la libreria M5450 per il controllo di relè
 * Advanced example for the M5450 library for relay control
 *
 * Questo sketch dimostra come usare i metodi di alto livello
 * per controllare i singoli relè in modo facile e intuitivo.
 *
 * This sketch demonstrates how to use the high-level methods
 * to control individual relays easily and intuitively.
 *
 * Collegamenti (esempio):
 * Connections (example):
 *  - Pin 2 Arduino -> DATA pin del M5450
 *  - Pin 3 Arduino -> CLOCK pin del M5450
 *  - Pin 4 Arduino -> STROBE pin del M5450
 */


//  Includi la libreria.
//  Include the library.
#include <M5450.h>

// Definisci i pin che userai.
// Define the pins you will use.
const uint8_t DATA_PIN = 2;
const uint8_t CLOCK_PIN = 3;
const uint8_t STROBE_PIN = 4;

// Crea un "oggetto" (un'istanza) della classe.
// Create an "object" (an instance) of class.
M5450 relays(DATA_PIN, CLOCK_PIN, STROBE_PIN);

void setup() {
  Serial.begin(115200);
  Serial.println("Test della libreria M5450 per relè.../ M5450 relay library test...");

  // Inizializza la libreria con tutti i pin a 0.
  // Initialize the library with all pin to 0
  relays.begin();

  Serial.println("Tutti i relè sono stati spenti. / All relays have been turned off.");
  delay(2000);
}

void loop() {

  // Esempio 1 / Example 1
  // Accende e spegne i relè in sequenza.
  // Turns relays on and off in sequence.
  Serial.println("\nAvvio sequenza... / Starting sequence...");

  // Accende i relè da 0 a 34
  // Turns on relays from 0 to 34
  for (int i = 0; i <= 34; i++) {
    relays.setRelay(i, true);  // Accende il relè 'i' / Turn on relay 'i'
    relays.update();           // aggiorna M5450 / update M5450
    delay(50);
  }

  // Spegne i relè da 34 a 0
  // Turns on relays from 0 to 34
  for (int i = 34; i >= 0; i--) {
    relays.setRelay(i, false); 
    relays.update();            
    delay(50);
  }

  delay(1000);

  // Esempio 2 / Example 2
  // Accendo più relè e aggiorno una volta sola
  // Turn on multiple relays and update only once
  Serial.println("\nAccendo i relè 0, 10, 20 e 30.../Turning on relays 0, 10, 20, and 30... ");

  relays.clear(); // Partiamo da una situazione pulita (anche se già lo era)

  relays.setRelay(0, true);   // Aggiorna lo stato interno / Updates the internal state
  relays.setRelay(10, true);  //                       "         "
  relays.setRelay(20, true);  //                       "         "
  relays.setRelay(30, true);  //                       "         "

  // INVIA! Ora i 4 relè si accendono tutti insieme.
  // SEND! Now the 4 relays turn on all at once.
  relays.update(); 

  Serial.println("4 relè accesi. Rimarranno così per 5 secondi. / 4 relays on. They will stay on for 5 seconds.");
  delay(5000); 

  // Esempio 3 / Example 3
  // Invertire lo stato del relè 10
  // Toggling  state of relay's stat
  Serial.println("\nInverto lo stato del relè 10.../ Toggling state of relay 10...");

  // Leggo lo stato attuale del relè 10
  // Read the current state of relay 10
  bool statoAttuale = relays.getRelayState(10);
 
  relays.setRelay(10, !statoAttuale); 
  relays.update();

  Serial.println("Lo stato del relè 10 è stato invertito. Attendo 3 secondi. / Relay 10 state has been toggled. Waiting 3 seconds.");
  delay(3000);

  Serial.println("\nPulisco tutto e ricomincio il ciclo. / Clearing all and restarting the loop.");
  relays.clear();
  delay(2000);

  // Esempio 4 / Example 4
  // Attivare un gruppo predefinito di relè con un solo comando.
  // Activate a predefined group of relays with a single command.
  Serial.println("\nAttivo il preset 'gruppoReleUno'... / Activating 'gruppoReleUno' preset...");

  relays.gruppoReleUno();

  Serial.println("Relè 2, 5, 9, 28, 32 sono ora accesi. Attendo 5 secondi. / Relays 2, 5, 9, 28, 32 are now ON. Waiting 5 seconds.");
  delay(5000);

}
