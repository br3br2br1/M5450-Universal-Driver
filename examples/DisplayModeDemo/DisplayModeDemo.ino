/*
 * DisplayModeDemo.ino - Esempio per M5450 in Modalita' Display
 *
 * Questo sketch mostra come usare la libreria per pilotare
 * 4 display a 7 segmenti, realizzando un semplice contatore.
 *
 * This sketch shows how to use the library to drive
 * 4 seven-segment displays, creating a simple counter.
 */
#include <M5450.h>

const uint8_t DATA_PIN = 2;
const uint8_t CLOCK_PIN = 3;
const uint8_t STROBE_PIN = 4;
const uint8_t NUM_DIGITS = 4; // Vogliamo pilotare 4 display
                             // We want to drive 4 digits

// Inizializza la libreria in modalita' display, specificando il numero di digit
// Initialize the library in display mode, specifying the number of digits
M5450 display(DATA_PIN, CLOCK_PIN, STROBE_PIN, NUM_DIGITS);

int counter = 0;

void setup() {
  Serial.begin(115200);
  display.begin();
  Serial.println("Demo Modalita' Display Avviata...");
}

void loop() {
  // Mostra il valore del contatore
  // Show the counter's value
  display.print(counter);
  display.update();

  // Incrementa il contatore
  // Increment the counter
  counter++;
  if (counter > 9999) {
    counter = 0;
  }
  
  delay(100); // Rallenta il conteggio per renderlo visibile
}
