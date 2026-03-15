#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

// Definição dos pinos
const int pinoRele = 15;
const int pinoBotao = 23;
const int pinoSDA = 27;
const int pinoSCL = 14;

const int tempoLigado = 5000; // 5 segundos

void acionarMotor() {
    Serial.println(">>> MOTOR EM EXECUÇÃO (5s) <<<");
    digitalWrite(pinoRele, LOW);  // Liga o relé
    delay(tempoLigado);           // 5 segundos
    digitalWrite(pinoRele, HIGH); // Desliga o relé
    Serial.println(">>> CICLO FINALIZADO <<<");
}

void setup() {
    Serial.begin(115200);
    
    pinMode(pinoRele, OUTPUT);
    digitalWrite(pinoRele, HIGH); 

    pinMode(pinoBotao, INPUT_PULLUP);

    Wire.begin(pinoSDA, pinoSCL);

    if (!rtc.begin()) {
	    Serial.println("RTC nao encontrado.");
    }


    if (rtc.lostPower()) {
        Serial.println("Ajustar hora do RTC");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    
    Serial.println("Aguardando horario ou botao.");
}

void loop() {
    DateTime agora = rtc.now();

    if (digitalRead(pinoBotao) == LOW) {
        delay(50); 
        if (digitalRead(pinoBotao) == LOW) {
            Serial.println("Botao pressionado!");
            acionarMotor();
            while(digitalRead(pinoBotao) == LOW) { delay(10); }
        }
    }

    if (agora.second() == 0 && agora.minute() == 0) {
        
        bool horaDeComer = false;

        if (agora.hour() == 7)  horaDeComer = true;  // Café da manhã
        if (agora.hour() == 13) horaDeComer = true;  // Almoço
        if (agora.hour() == 19) horaDeComer = true;  // Jantar

        if (horaDeComer) {
            Serial.printf("Horário oficial atingido: %02d:00\n", agora.hour());
            acionarMotor();
            delay(1000); 
        }
    }

    if (agora.second() % 5 == 0) {
        Serial.printf("Hora atual: %02d:%02d:%02d | Botao D23: %s\n", 
                      agora.hour(), agora.minute(), agora.second(),
                      digitalRead(pinoBotao) == LOW ? "PRESSIONADO" : "SOLTO");
        delay(1000);
    }
}
//.............................................................................