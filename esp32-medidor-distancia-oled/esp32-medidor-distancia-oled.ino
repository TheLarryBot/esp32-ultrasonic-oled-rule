#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define ANCHO_PANTALLA 128
#define ALTO_PANTALLA 64

#define OLED_RESET -1
#define DIRECCION_PANTALLA 0x3C

Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, OLED_RESET);

const int pinTrig = 25;  // Pin de trigger del sensor ultrasónico
const int pinEcho = 26;  // Pin de echo del sensor ultrasónico
const int led = 2;      // Pin del LED que se enciende cuando la distancia es muy cercana

void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);  // Asegurarse de que el LED esté apagado al inicio

  if (!display.begin(SSD1306_SWITCHCAPVCC, DIRECCION_PANTALLA)) {
    Serial.println(F("Fallo en la asignacion de SSD1306"));
    for (;;);  // Detener la ejecución si la pantalla no se inicializa correctamente
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.setTextSize(3);
  display.println("SENSOR");
  display.display();

  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  Serial.begin(115200);
  digitalWrite(pinTrig, LOW);
}

void loop() {
  // Generar un pulso de 10 microsegundos en el pin de trigger
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);

  // Medir el tiempo que tarda en llegar el eco
  long duration = pulseIn(pinEcho, HIGH);

  // Calcular la distancia en centímetros
  int distance = duration / 59;

  // Mostrar la distancia en la pantalla OLED
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(32, 10);
  display.print(distance);
  display.print("CM");
  display.display();

  // Encender el LED si la distancia es menor a 5 cm
  if (distance < 5) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }

  delay(30);  // Pequeño retardo para evitar lecturas demasiado rápidas
}