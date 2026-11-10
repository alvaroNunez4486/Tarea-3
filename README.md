Juego de Búsqueda del Tesoro con Doble Arduino

Sistema embebido interactivo basado en una arquitectura de doble microcontrolador comunicados por puerto serie (UART), diseñado para un juego de exploración de coordenadas en cuadrícula.


Arquitectura del Sistema
El proyecto divide las responsabilidades del sistema en dos placas Arduino Uno para optimizar el rendimiento y la modularidad:

Arduino Maestro (Placa Izquierda):
  Gestiona la máquina de estados del juego (INACTIVO, JUGANDO, VICTORIA, DERROTA).
  Controla la pantalla LCD 16x2 vía protocolo I2C.
  Administra el temporizador de la partida mediante un LED indicador con atenuación PWM.
  Realiza el sorteo aleatorio de las coordenadas del tesoro.

Arduino Esclavo (Placa Derecha):
  Lee las entradas analógicas de los potenciómetros.
  Captura la señal del pulsador físico de inicio mediante resistencia de pull-up interna (INPUT_PULLUP).
  Mapea los niveles de proximidad recibidos del Maestro para actualizar el brillo de los LEDs indicadores de los ejes.


Protocolo de Comunicación UART
La comunicación entre ambas placas se realiza a 9600 baudios utilizando una línea de tierra común y conexión cruzada TX/RX:
  Inicio de Partida: El Esclavo envía el valor 255 al presionar el botón, indicando al Maestro que inicie el juego.
Transmisión de Coordenadas:
  Eje X: Valores del 0 al 100.
  Eje Y: Valores desplazados del 101 al 200 (se resta 100 en el Maestro para normalizar a 0-100).


Conexiones de Hardware
Arduino Maestro
|Pin / Periférico | Conexión Destino|
|Pin 9 | Ánodo de LED Verde (Temporizador)|
|Pin A4 (SDA) | Pin SDA de Pantalla LCD I2C|
|Pin A5 (SCL) | Pin SCL de Pantalla LCD I2C|
|Pin 5V | VCC de Pantalla LCD I2C|
|Pin GND | GND de Pantalla LCD y GND Común|
|Pin TX | Pin RX del Arduino Esclavo|
|Pin RX | Pin TX del Arduino Esclavo|

Arduino Esclavo
|Pin / Periférico | Conexión Destino|
|Pin A0 | Pin central (cursor) del potenciómetro Eje X|
|Pin A1 | Pin central (cursor) del potenciómetro Eje Y|
|Pin 2 | Un extremo del pulsador de inicio|
|Pin 3 (PWM) | Ánodo de LED Eje X|
|Pin 5 (PWM) | Ánodo de LED Eje Y|
|Pin GND | GND Común|
|Pin TX | Pin RX del Arduino Maestro|
|Pin RX | Pin TX del Arduino Maestro|

<img width="1391" height="721" alt="Captura de pantalla 2026-11-10 165713" src="https://github.com/user-attachments/assets/b90f7863-525b-4ad8-a4ba-652660191b7a" />

URL DEL REPOSITORIO DEL MAESTRO:
https://github.com/alvaroNunez4486/Tarea-3.2
