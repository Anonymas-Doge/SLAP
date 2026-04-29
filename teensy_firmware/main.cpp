#include <Arduino.h>


void main_setup()
{
    // UART Setup with Jetson
    UART_Jetson_setup();
}

void main_loop()
{
    // UART Main Operations with Jetson
    UART_Jetson_loop();
}