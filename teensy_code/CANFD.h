#ifndef CANFD_H
#define CANFD_H

// include connected files later
#include <Arduino.h>
#include <ACAN2517FD.h>
#include <SPI.h>

void CANFD_setup();
void CANFD_loop();

#endif