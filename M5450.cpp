


#include "M5450.h"

// Tabella di consultazione (lookup table) per i segmenti.
// L'ordine dei bit è: (unused) g f e d c b a
// Segment lookup table. Bit order is: (unused) g f e d c b a
const uint8_t M5450::_segmentMap[10] = {
  0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, // 0-4
  0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111  // 5-9
};

// Costruttore / Constructor
M5450::M5450(uint8_t dataPin, uint8_t clockPin, uint8_t strobePin, uint8_t numDigits) {
  _dataPin = dataPin;
  _clockPin = clockPin;
  _strobePin = strobePin;

  // Sanifichiamo il numero di digit per essere sicuri che sia tra 0 e 4
  // Sanitize the number of digits to ensure it is between 0 and 4
  _numDigits = constrain(numDigits, 0, 4);

  // Inizializziamo lo stato di tutte le uscite a 0 (spente)
  // Initialize the state of all outputs to 0 (off)
  _outputState = 0;

  // Il debug è disabilitato di default
  // Debug is disabled by default
  _debugEnabled = false;
}

// Inizializzazione / Initialization
void M5450::begin() {
  pinMode(_dataPin, OUTPUT);
  pinMode(_clockPin, OUTPUT);
  pinMode(_strobePin, OUTPUT);
  clear();
}

// Imposta un singolo relè / Set a single relay
void M5450::setRelay(uint8_t relayNumber, bool state) {

  // Convertiamo il numero del relè (1-34) nell'indice del bit (0-33).
  // We convert the relay number (1-34) to the bit index (0-33).
  uint8_t bitIndex = relayNumber - 1;

  // Calcoliamo quanti pin sono riservati ai display.
  // We calculate how many pins are reserved for the displays.
  uint8_t displayPins = _numDigits * 7;

  // Controlliamo che il pin richiesto sia valido (0-33) e non sia usato dal display.
  // We check that the requested pin is valid (0-33) and not used by the display.
  if (bitIndex >= displayPins) {
    if (state) {
      _outputState |= (1ULL << bitIndex);
    } else {
      _outputState &= ~(1ULL << bitIndex);
    }
  }
}

// Legge lo stato di un'uscita / Get the state of an output
bool M5450::getOutputState(uint8_t pinNumber) {
  // Controlliamo che il pin sia valido (1-34)
  // Check that the pin is valid (1-34)
  if (pinNumber < 1 || pinNumber > 34) return false;

  //  Conversione
  //  Conversion
  uint8_t bitIndex = pinNumber - 1;
  return (_outputState >> bitIndex) & 1;
}

// Visualizza un numero / Display a number
void M5450::print(long number) {
  // Se non siamo in modalità display, non fare nulla.
  // If we are not in display mode, do nothing.
  if (_numDigits == 0) return;

  // 1. Puliamo solo i bit del display, lasciando i relè intatti
  // 1. Clear only the display bits, leaving the relays untouched
  uint8_t displayPins = _numDigits * 7;
  uint64_t clearMask = (1ULL << displayPins) - 1;
  _outputState &= ~clearMask;

  // 2. Calcoliamo i nuovi dati per il display
  // 2. Calculate the new data for the display
  uint64_t displayData = 0;
  bool isNegative = false;
  if (number < 0) { isNegative = true; number = -number; }
  for (int i = 0; i < _numDigits; i++) {
    uint8_t digit;
    if (isNegative && i == (_numDigits - 1)) {
      digit = 0b01000000; // Segno '-' / '-' sign
      displayData |= (uint64_t)digit << (i * 7);
      break;
    }
    digit = number % 10;
    uint8_t segments = _segmentMap[digit];
    displayData |= (uint64_t)segments << (i * 7);
    number /= 10;
    if (number == 0 && !isNegative) break;
  }

  // Uniamo i dati del display con lo stato esistente.
  // Merge the display data with the existing state.
  _outputState |= displayData;
}

// Imposta un gruppo di relè / Set a group of relays
void M5450::setRelayGroup(const uint8_t relays[], uint8_t numRelays, bool state) {
  // Calcoliamo quali pin sono riservati al display
  // We calculate which pins are reserved for the display
  uint8_t displayPins = _numDigits * 7;

  // Cicliamo attraverso l'array fornito dall'utente
  // We loop through the array provided by the user
  for (uint8_t i = 0; i < numRelays; i++) {
    uint8_t relayNumber = relays[i];

    // Applichiamo la modifica solo se il relè è valido e non è usato dal display
    // We apply the change only if the relay is valid and not used by the display
    if (relayNumber >= 1 && relayNumber <= 34) {
      uint8_t bitIndex = relayNumber - 1;

      if (bitIndex >= displayPins) {
        if (state) {
         _outputState |= (1ULL << bitIndex);
        } else {
        _outputState &= ~(1ULL << bitIndex);
        }
      }
    }
  }  // for
}  // void M5450::setRelayGroup

// Spegne tutti i relè / Clears all relays
void M5450::clearRelays() {
  // Calcoliamo la maschera che rappresenta i pin usati dal display
  // We calculate the mask representing the pins used by the display
  uint8_t displayPins = _numDigits * 7;
  uint64_t displayMask = (1ULL << displayPins) - 1;

  // Manteniamo solo i bit del display e spegniamo tutto il resto.
  // We keep only the display bits and turn off everything else.
  _outputState &= displayMask;
}

// Abilita la stampa di debug / Enable debug printing
void M5450::enableDebug(bool enabled) {
  _debugEnabled = enabled;
  if (_debugEnabled) {
    Serial.println(F("--- M5450 Debug Abilitato / Debug Enabled ---"));
  }
}

// Invia lo stato al chip / Send the state to the chip
void M5450::update() {
  // Se il debug è attivo, stampiamo lo stato prima di inviarlo
  // If debug is enabled, print the state before sending it
  if (_debugEnabled) {
    Serial.print(F("M5450::update() -> Invio (Pin 34..1): 0b"));
    // Stampiamo i 35 bit del nostro stato
    // Print the 35 bits of our state
    for (int i = 33; i >= 0; i--) {
    Serial.print( (int)((_outputState >> i) & 1) );
    }
    Serial.println();
  }
  sendData(_outputState);
}

// Pulisce tutto / Clear everything
void M5450::clear() {
  _outputState = 0;
  update();
}

// Metodo privato per inviare dati grezzi / Private method to send raw data
void M5450::sendData(uint64_t data) {
  digitalWrite(_strobePin, LOW);
  // Il ciclo invia 35 bit per riempire l'intero registro del chip.
  // The loop sends 35 bits to fill the chip's entire register.
  for (int i = 34; i >= 0; i--) {
    bool bitToSend = (data >> i) & 1;
    digitalWrite(_dataPin, bitToSend);
    digitalWrite(_clockPin, HIGH);
    digitalWrite(_clockPin, LOW);
  }
  digitalWrite(_strobePin, HIGH);
}
