#include "UART_Jetson.h"

void UART_Jetson_setup() {
    // Serial.begin(9600);
    pinMode(13, OUTPUT);
}

void UART_Jetson_loop() {
    // Serial.println ("UART Loop") ;
    if (Serial.available()) {
        String command = Serial.readString();
        command.trim();
        if (command == "LED_ON") {
            digitalWrite(13, HIGH);
            Serial.println("LED ON");
        } else if (command == "LED_OFF") {
            digitalWrite(13, LOW);
            Serial.println("LED OFF");
        } else if (command == "PING") {
            Serial.println("PONG");
        }
    }
}