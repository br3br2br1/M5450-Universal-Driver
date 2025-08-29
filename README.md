

https://www.alldatasheet.com/datasheet-pdf/pdf/99727/STMICROELECTRONICS/M5450.html


# M5450 Universal Driver - API Reference

This document provides a quick reference guide for all public methods available in the M5450 Universal Driver library. This is the user documentation for the library.

## Features

-   Intuitive "1-based" pin numbering (1 to 34), matching the datasheet labels.
-   Shadow state management: prepare your outputs and update them all simultaneously with `update()`.
-   Smart hybrid mode that prevents conflicts between display and relays.
-   Safe group methods to manage multiple relays without interfering with the display.
-   Integrated debug mode to view the bit state on the Serial Monitor.
-   Efficient and portable code, compatible with AVR (Arduino UNO, etc.) and other architectures.

## Installation

1.  Download the library as a `.zip` file.
2.  Open the Arduino IDE.
3.  Navigate to `Sketch > Include Library > Add .ZIP Library...`.
4.  Select the downloaded `.zip` file.
5.  The examples will be available under the `File > Examples > M5450 Universal Driver` menu.

## Hardware Connections (Logical Layout)

When used in display mode, the library assumes the following logical connection scheme:
-   **Digit 1:** Controlled by M5450 outputs **1-7**.
-   **Digit 2:** Controlled by M5450 outputs **8-14**.
-   **Digit 3:** Controlled by M5450 outputs **15-21**.
-   **Digit 4:** Controlled by M5450 outputs **22-28**.

Any remaining outputs (up to 34) are available for use as relays.

---

## Complete API Guide

The API includes:
-   `M5450(...)`
-   `begin()`
-   `update()`
-   `clear()`
-   `print(long number)`
-   `setRelay(uint8_t relayNumber, bool state)`
-   `setRelayGroup(...)`
-   `clearRelays()`
-   `getOutputState(uint8_t pinNumber)`
-   `enableDebug(bool enabled)`

### Library Initialization

#### `M5450(dataPin, clockPin, strobePin, numDigits)`
**Description:** Class constructor. Creates a driver instance and sets its operating mode.
-   `dataPin`: `uint8_t` - Arduino pin for DATA.
-   `clockPin`: `uint8_t` - Arduino pin for CLOCK.
-   `strobePin`: `uint8_t` - Arduino pin for STROBE.
-   `numDigits`: `uint8_t` (optional) - Number of 7-segment digits (1-4). If `0` or omitted, enables relay-only mode.
**Usage:**
M5450 relays(2, 3, 4);          // Relay mode
M5450 display(2, 3, 4, 4);      // 4-digit display mode

#### `void begin()`
**Description:** Initializes the library and hardware pins. Must be called once in `setup()`.
**Usage:**
void setup() {
  myController.begin();
}

### General Control

#### `void update()`
**Description:** Sends the current internal state (the "shadow state") to the M5450 chip. Changes made by `print()`, `setRelay()`, `setRelayGroup()`, and `clearRelays()` are only made visible after calling this method.
**Usage:**
myController.setRelay(15, true);
myController.update(); // The relay turns on now

#### `void clear()`
**Description:** Turns off all 34 outputs (both relays and display segments) and immediately updates the chip.
**Usage:**
myController.clear();

### Display Methods

#### `void print(long number)`
**Description:** Prepares an integer number to be shown on the display. This only works if the library is in display or hybrid mode (`numDigits > 0`). It handles negative numbers by showing a dash.
-   `number`: `long` - The integer to display.
**Usage:**
display.print(-123);
display.update();

### Relay & Output Methods

#### `void setRelay(uint8_t relayNumber, bool state)`
**Description:** Prepares a single output to be turned on or off. The command is ignored if `relayNumber` is reserved for the display.
-   `relayNumber`: `uint8_t` - The output number to control (1-34).
-   `state`: `bool` - `true` for ON, `false` for OFF.
**Usage:**
// Prepare to turn relay 16 ON and relay 17 OFF
relays.setRelay(16, true);
relays.setRelay(17, false);
relays.update(); // Both changes happen now

#### `void setRelayGroup(const uint8_t relays[], uint8_t numRelays, bool state)`
**Description:** Prepares a group of outputs, defined in an array, to be set to a specific state.
-   `relays[]`: `const uint8_t` - An array of output numbers (1-34).
-   `numRelays`: `uint8_t` - The size of the array.
-   `state`: `bool` - The state (`true`/`false`) to apply to the group.
**Usage:**
uint8_t myGroup[] = {15, 21, 34};
relays.setRelayGroup(myGroup, 3, true);
relays.update();

#### `void clearRelays()`
**Description:** Prepares to turn off all available relay outputs without affecting the display.
**Usage:**
hybridController.clearRelays();
hybridController.update(); // Display remains on, relays turn off

#### `bool getOutputState(uint8_t pinNumber)`
**Description:** Returns the internally stored state (`true` or `false`) of any given output.
-   `pinNumber`: `uint8_t` - The output number to check (1-34).
**Returns:** `bool` - `true` if the output is set to ON in the shadow state, `false` otherwise.
**Usage:**
bool isRelayOn = relays.getOutputState(20);

### Debugging

#### `void enableDebug(bool enabled)`
**Description:** Enables or disables printing the 34-bit state to the Serial Monitor on every `update()` call.
-   `enabled`: `bool` (optional) - `true` to enable (default), `false` to disable.
**Usage:**
void setup() {
  Serial.begin(115200);
  myController.enableDebug();
}

====================================================================================
====================================================================================

# M5450 Universal Driver - Guida di Riferimento API (Italiano)

Questo documento fornisce una guida di riferimento rapida per tutti i metodi pubblici disponibili nella libreria M5450 Universal Driver. 
E' la documentazione utente per la libreria.

## Caratteristiche

-   Interfaccia intuitiva con numerazione dei pin da 1 a 34, corrispondente alle etichette dei pin nel datasheet.
-   Gestione della "variabile ombra": prepara le tue uscite e aggiornale tutte simultaneamente con `update()`.
-   Modalita' ibrida intelligente che previene conflitti tra display e rele'.
-   Metodi di gruppo sicuri per gestire piu' rele' senza interferire con il display.
-   Modalita' di debug integrata per visualizzare lo stato dei bit sul Serial Monitor dell'IDE Arduino.
-   Codice efficiente e portabile, compatibile con architetture AVR (Arduino UNO, ESP32, ESP8266, ecc... ) 

## Installazione

1.  Scarica la libreria come file `.zip`.
2.  Apri l'IDE di Arduino.
3.  Vai su `Sketch > #include Libreria > Aggiungi libreria da file .ZIP...`.
4.  Seleziona il file `.zip` scaricato.
5.  Gli esempi saranno disponibili nel menu `File > Esempi > M5450 Universal Driver`.

## Collegamenti Hardware (Schema Logico)

Quando usata in modalita' display, la libreria assume il seguente schema di collegamento logico:
-   **Digit 1:** Controllato dalle uscite **1-7** del M5450.
-   **Digit 2:** Controllato dalle uscite **8-14** del M5450.
-   **Digit 3:** Controllato dalle uscite **15-21** del M5450.
-   **Digit 4:** Controllato dalle uscite **22-28** del M5450.

Le uscite rimanenti (fino alla 34) sono disponibili per l'uso come rele'.

---

## Guida Completa all'Uso (API)

L'API include:
-   `M5450(...)`
-   `begin()`
-   `update()`
-   `clear()`
-   `print(long number)`
-   `setRelay(uint8_t relayNumber, bool state)`
-   `setRelayGroup(...)`
-   `clearRelays()`
-   `getOutputState(uint8_t pinNumber)`
-   `enableDebug(bool enabled)`

### Inizializzazione della Libreria

#### `M5450(dataPin, clockPin, strobePin, numDigits)`
**Descrizione:** Costruttore della classe. Crea un'istanza del driver e ne imposta la modalita' operativa.
-   `dataPin`  : `uint8_t`  - Pin di Arduino per DATA.
-   `clockPin` : `uint8_t`  - Pin di Arduino per CLOCK.
-   `strobePin`: `uint8_t`  - Pin di Arduino per STROBE.
-   `numDigits`: `uint8_t`  (opzionale) - Numero di display a 7 segmenti (1-4). Se omesso(numDigits=0), si abilita la modalita' solo rele'.
**Uso:**
M5450 relays(2, 3, 4);          // Modalita' da 1 a 34 rele'
M5450 display(2, 3, 4, 4);      // Modalita' display a 4 digit

#### `void begin()`
**Descrizione:** Inizializza la libreria e i pin hardware. Da chiamare una sola volta nel "setup()".
**Uso:**
void setup() {
  mioController.begin();
}

### Controllo Generale

#### `void update()`
**Descrizione:** 
Invia lo stato interno corrente (la "variabile ombra") al chip M5450. I cambiamenti preparati con `print()`, `setRelay()`, `setRelayGroup()` e `clearRelays()` diventano visibili e attivi solo dopo aver chiamato questo metodo.
**Uso:**
mioController.setRelay(15, true);
mioController.update(); // Il rele' 15 ora si accende

#### `void clear()`
**Descrizione:** Spegne tutte le 34 uscite (sia rele' che segmenti del display) e aggiorna immediatamente il chip.
**Uso:**
mioController.clear(); resetta la "variabile ombra"

### Metodi per Display

#### `void print(long number)`
**Descrizione:** Prepara un numero intero per essere visualizzato sul display. Funziona solo se la libreria e' in modalita' display o ibrida (`numDigits > 0`). Gestisce i numeri negativi mostrando un trattino.
-   `number`: `long` - L'intero da visualizzare.
**Uso:**
display.print(-123); 
display.update();

### Metodi per Rele' e Uscite

#### `void setRelay(uint8_t relayNumber, bool state)`
**Descrizione:** Prepara una singola uscita per essere accesa o spenta. Il comando viene ignorato se `relayNumber` e' riservato per il display.
-   `relayNumber`: `uint8_t` - Il numero dell'uscita da controllare (da 1 a 34).
-   `state`: `bool` - `true` per ON, `false` per OFF.
**Uso:**
// Prepara l'accensione del rele' 16 e lo spegnimento del 17
relays.setRelay(16, true);
relays.setRelay(17, false);
relays.update(); // Entrambi i cambiamenti avvengono ora

#### `void setRelayGroup(const uint8_t relays[], uint8_t numRelays, bool state)`
**Descrizione:** Prepara un gruppo di uscite, definite in un array, per essere impostate a uno stato specifico.
-   `relays[]`: `const uint8_t` - Un array di numeri di uscita (1-34).
-   `numRelays`: `uint8_t` - La dimensione dell'array.
-   `state`: `bool` - Lo stato (`true`/`false`) da applicare al gruppo.
**Uso:**
uint8_t mioGruppo[] = {15, 21, 34};
relays.setRelayGroup(mioGruppo, 3, true);
relays.update();

#### `void clearRelays()`
**Descrizione:** Prepara lo spegnimento di tutte le uscite disponibili come rele' senza influenzare il display.
**Uso:**
controllerIbrido.clearRelays();
controllerIbrido.update(); // Il display resta acceso, i rele' si spengono

#### `bool getOutputState(uint8_t pinNumber)`
**Descrizione:** Restituisce lo stato memorizzato internamente (`true` o
`false`) di una qualsiasi uscita.
-   `pinNumber`: `uint8_t` - Il numero dell'uscita da controllare (da 1 a 34).
**Restituisce:** `bool` - `true` se l'uscita e' impostata su ON nella variabile ombra, altrimenti `false`.
**Uso:**
bool releAcceso = relays.getOutputState(20);

### Debug

#### `void enableDebug(bool enabled)`
**Descrizione:** Abilita o disabilita la stampa dello stato a 34 bit sul Monitor Seriale a ogni chiamata di `update()`.
-   `enabled`: `bool` (opzionale) - `true` per abilitare (default), `false` per disabilitare.
**Uso:**
void setup() {
  Serial.begin(115200);
  mioController.enableDebug();
}
