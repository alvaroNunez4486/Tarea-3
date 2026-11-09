#include <Arduino.h>
//Esclavo (Transmisor)
const int pinX = A0;
const int pinY = A1;
const int pinBoton = 2;
const int pinLedX = 3; // LED PWM para retroalimentación del eje X
const int pinLedY = 5; // LED PWM para retroalimentación del eje Y

unsigned long tiempoAnterior = 0;
const unsigned long intervalo = 50; 

void setup() {
    Serial.begin(9600);              // Inicialización UART
    pinMode(pinBoton, INPUT_PULLUP); // Configuración del pulsador de inicio
    pinMode(pinLedX, OUTPUT);        // Configurar pin LED X como salida
    pinMode(pinLedY, OUTPUT);        // Configurar pin LED Y como salida
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

        analogWrite(pinLedX, lecturaX / 4); // Actualizar brillo del LED X según la posición

        // Eje Y (Rango 101 - 200)
        int lecturaY = analogRead(pinY);
        uint8_t coordY = ((long)lecturaY * 100L / 1024) + 100;
        Serial.write(coordY);

        analogWrite(pinLedY, lecturaY / 4); // Actualizar brillo del LED Y según la posición
    }

    // Detección del botón de inicio
    if (digitalRead(pinBoton) == LOW) {
        Serial.write(255); 
        delay(200); // Pausa breve para evitar rebotes múltiples al presionar
    }
}