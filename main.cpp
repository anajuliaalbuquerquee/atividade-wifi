/*
 * Ex 5 - Semáforo de 3 fases com millis()
 *
 * Fases: VERDE (4 s) → AMARELO (1,5 s) → VERMELHO (4 s) → VERDE ...
 *
 * Em vez de delay(), o programa guarda em que fase está e quando ela
 * começou. A cada volta do loop verifica se o tempo da fase acabou e,
 * se sim, passa para a próxima (máquina de estados).
 *
 * Circuito (Tinkercad):
 *   pino 10 → 220 Ω → LED vermelho → GND
 *   pino 9  → 220 Ω → LED amarelo  → GND
 *   pino 8  → 220 Ω → LED verde    → GND
 */

#include <Arduino.h>

const int LED_VERMELHO = 10;
const int LED_AMARELO = 9;
const int LED_VERDE = 8;

// Fases
const int VERDE = 0;
const int AMARELO = 1;
const int VERMELHO = 2;

// Duração de cada fase (ms), na mesma ordem das fases acima
const unsigned long DURACAO[3] = {4000, 1500, 4000};

int faseAtual = VERDE;
unsigned long inicioFase = 0;

void aplicarFase(int fase);  // protótipo (necessário em .cpp)

void setup() {
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  Serial.begin(9600);

  inicioFase = millis();
  aplicarFase(faseAtual);
}

// Liga só o LED da fase indicada
void aplicarFase(int fase) {
  digitalWrite(LED_VERDE, fase == VERDE);
  digitalWrite(LED_AMARELO, fase == AMARELO);
  digitalWrite(LED_VERMELHO, fase == VERMELHO);

  if (fase == VERDE) Serial.println("Fase: VERDE");
  else if (fase == AMARELO) Serial.println("Fase: AMARELO");
  else Serial.println("Fase: VERMELHO");
}

void loop() {
  if (millis() - inicioFase >= DURACAO[faseAtual]) {
    faseAtual = (faseAtual + 1) % 3;  // próxima fase (volta ao 0 depois do 2)
    inicioFase = millis();
    aplicarFase(faseAtual);
  }

  // Aqui o Arduino está livre para ler botões, sensores etc.
}
