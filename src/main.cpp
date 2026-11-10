#include <Arduino.h>
//Esclavo (Transmisor)
const int PIN_POT_X = A0;
const int PIN_POT_Y = A1;
const int PIN_BTN = 2;
const int PIN_LED_X = 3; // LED PWM para retroalimentación del eje X
const int PIN_LED_Y = 5; // LED PWM para retroalimentación del eje Y

unsigned long ultimoEnvio = 0;
const unsigned long INTERVALO_ENVIO = 50; // 50 ms

// Variables para antirrebote del botón
unsigned long ultimoDebounce = 0;
bool estadoAnteriorBtn = HIGH;

void setup() {
    Serial.begin(9600);               // Inicialización UART
    pinMode(PIN_BTN, INPUT_PULLUP);   // Configuración del pulsador de inicio
    pinMode(PIN_LED_X, OUTPUT);       // Configurar pin LED X como salida
    pinMode(PIN_LED_Y, OUTPUT);       // Configurar pin LED Y como salida
};

void loop() {
  
  	// 1. Detección del botón para enviar código de inicio (255)
    if (digitalRead(PIN_BTN) == LOW) {
        Serial.write(255);
        delay(200); // Pausa simple de protección
    }

  	// 2. Lectura del botón con antirrebote por millis()
    bool lecturaBtn = digitalRead(PIN_BTN);
    if (lecturaBtn != estadoAnteriorBtn) {
        ultimoDebounce = millis();
    }
    if ((millis() - ultimoDebounce) > 50) {
        if (lecturaBtn == LOW && estadoAnteriorBtn == HIGH) {
            // Envía la solicitud de inicio (código 255) al Maestro
            Serial.write(255);
        }
    }
    estadoAnteriorBtn = lecturaBtn;
  
  	// 3. Envío periódico de coordenadas (cada 50 ms)
    if (millis() - ultimoEnvio >= INTERVALO_ENVIO) {
        ultimoEnvio = millis();

        int lecturaX = analogRead(PIN_POT_X);
        int lecturaY = analogRead(PIN_POT_Y);

        // Conversión uniforme de 10 bits a rango 0-100
        uint8_t valX = (lecturaX * 100L) / 1023;
        uint8_t valY = (lecturaY * 100L) / 1023;

        Serial.write(valX);          // Eje X: 0 a 100
        Serial.write(valY + 100);    // Eje Y: 101 a 200
    }
  
    // 4. Envío periódico de coordenadas
    if (millis() - ultimoEnvio >= INTERVALO_ENVIO) {
        ultimoEnvio = millis();

        uint8_t valX = (analogRead(PIN_POT_X) * 100L) / 1023;
        uint8_t valY = (analogRead(PIN_POT_Y) * 100L) / 1023;

        Serial.write(valX);
        Serial.write(valY + 100);
    }
 
    // 5. Envío periódico de coordenadas (cada 50 ms)
    if (millis() - ultimoEnvio >= INTERVALO_ENVIO) {
        ultimoEnvio = millis();

        int lecturaX = analogRead(PIN_POT_X);
        int lecturaY = analogRead(PIN_POT_Y);

        // Conversión uniforme de 10 bits a rango 0-100
        uint8_t valX = (lecturaX * 100L) / 1023;
        uint8_t valY = (lecturaY * 100L) / 1023;

        Serial.write(valX);          // Eje X: 0 a 100
        Serial.write(valY + 100);    // Eje Y: 101 a 200
    }

    // 6. Recepción de niveles de proximidad enviados por el Maestro
    if (Serial.available() >= 2) {
        uint8_t nivelX = Serial.read();
        uint8_t nivelY = Serial.read();

        // Mapeo de niveles de proximidad a brillo PWM 
        int pwmX = (nivelX == 3) ? 255 : (nivelX == 2 ? 80 : (nivelX == 1 ? 20 : 0));
        int pwmY = (nivelY == 3) ? 255 : (nivelY == 2 ? 80 : (nivelY == 1 ? 20 : 0));

        analogWrite(PIN_LED_X, pwmX);
        analogWrite(PIN_LED_Y, pwmY);
    }
  }




