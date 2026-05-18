#include "CANFD.h"
#include "IMU.h"
#include "UART_Jetson.h"


void main_setup()
{
    // CAN FD Setup
    CANFD_setup();

    // IMU Setup
    IMU_setup();

    // UART Setup with Jetson
    // UART_Jetson_setup();
}

void main_loop()
{
    // CAN FD Main
    CANFD_loop();

    // IMU Main
    IMU_loop();

    // UART Main Operations with Jetson
    // UART_Jetson_loop();
}