#include <Arduino.h>
//Esclavo (Transmisor)
const int pinX = A0;
const int pinY = A1;
const int pinBoton = 2;

unsigned long tiempoAnterior = 0;
const unsigned long intervalo = 50; 

void setup() {
    Serial.begin(9600);              // Inicialización UART
    pinMode(pinBoton, INPUT_PULLUP); // Configuración del pulsador de inicio
}

void loop() {
    unsigned long tiempoActual = millis();

    // Envío periódico de coordenadas (cada 50 ms)
    if (tiempoActual - tiempoAnterior >= intervalo) {
        tiempoAnterior = tiempoActual;

        // Eje X (Rango 0 - 100)
        int lecturaX = analogRead(pinX);
        uint8_t coordX = (long)lecturaX * 100L / 1024;
        Serial.write(coordX);

        // Eje Y (Rango 101 - 200)
        int lecturaY = analogRead(pinY);
        uint8_t coordY = ((long)lecturaY * 100L / 1024) + 100;
        Serial.write(coordY);
    }

    // Detección del botón de inicio
    if (digitalRead(pinBoton) == LOW) {
        Serial.write(255); 
        delay(200); // Pausa breve para evitar rebotes múltiples al presionar
    }
}