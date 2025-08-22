// File: M5450.h

#ifndef M5450_H
#define M5450_H

#include "Arduino.h"

class M5450 {
  public:
    // Costruttore:
    //  numDigit specifica il numero di digit:
    //  0 = modalità da 1 a 34 solo relè o uscite digitali
    //  1 = un solo digit 7 segmenti
    //  2 = due digit         "
    //  4 = quattro digit     "

    // Constructor:
    // numDigit specifies the number of digits:
    // 0 = Mode 1 to 34, relays or digital outputs only
    // 1 = Single digit, 7 segments
    // 2 = Two digits         "
    // 4 = Four digits        "
    M5450(uint8_t dataPin, uint8_t clockPin, uint8_t strobePin, uint8_t numDigits = 2);

    // Inizializza la libreria e i pin
    // Initializes the library and the pins
    void begin();

    // --- METODI IBRIDI ---
    // --- HYBRID METHODS ---

    // Imposta lo stato di un singolo relè (`true`=ON, `false`=OFF). Ignorato se il pin è usato dal display.
    // Sets the state of a single relay (`true`=ON, `false`=OFF). Ignored if the pin is used by the display.
    void setRelay(uint8_t relayNumber, bool state);

    // Legge lo stato di un'uscita (0-33) dalla memoria interna.
    // Reads the state of an output (0-33) from the internal memory.
    bool getOutputState(uint8_t pinNumber);

    // Prepara la visualizzazione di un numero sul display.
    // Prepares a number to be shown on the display.
    void print(long number);

    // Imposta un gruppo di relè (definito da un array) a uno stato specifico (true=ON, false=OFF).
    // Ignora i pin usati dal display. Non modifica lo stato degli altri relè.
    // Sets a group of relays (defined by an array) to a specific state (true=ON, false=OFF).
    // Ignores pins used by the display. Does not modify the state of other relays.
    void setRelayGroup(const uint8_t relays[], uint8_t numRelays, bool state);

    // Spegne tutti i relè disponibili senza modificare il display.
    // Turns off all available relays without modifying the display.
    void clearRelays();

    // Invia lo stato corrente (display e relè) al chip.
    // Sends the current state (display and relays) to the chip.
    void update();

    // Pulisce tutte le uscite (display e relè).
    // Clears all outputs (display and relays).
    void clear();

    // Abilita la stampa di debug sul Serial Monitor.
    // Richiede che il Serial.begin() sia stato chiamato nello sketch.
    // Enables debug printing on the Serial Monitor.
    // Requires Serial.begin() to have been called in the sketch.
    void enableDebug(bool enabled = true);

  private:
    // Metodo privato per l'invio fisico dei dati
    // Private method for the physical data transmission
    void sendData(uint64_t data);

    uint8_t _dataPin;
    uint8_t _clockPin;
    uint8_t _strobePin;
    uint8_t _numDigits;

    // Variabile di stato unificata per tutte le 34 uscite
    // Unified state variable for all 34 outputs
    uint64_t _outputState;

    // Tabella di consultazione statica per i segmenti
    // Static lookup table for the segments
    static const uint8_t _segmentMap[10];

    bool _debugEnabled;
};

#endif
