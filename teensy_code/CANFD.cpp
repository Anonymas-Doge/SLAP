//——————————————————————————————————————————————————————————————————————————————
// Demonstration of control and monitoring of 2 moteus controllers
// using a Teensy 4.x board with on-board CAN-FD hardware.
//  * https://mjbots.com/products/moteus-r4-11
//
// Requires a CAN-FD transceiver connected to Teensy CAN3 (pins 30/31).
//
// Controller IDs are moved through a sine wave pattern.
// ——————————————————————————————————————————————————————————————————————————————

#include "CANFD.h"

//——————————————————————————————————————————————————————————————————————————————
//  CAN-FD configuration
//——————————————————————————————————————————————————————————————————————————————

// 1 Mbps arbitration and data rate.
ACAN_T4FD_Settings canSettings(1000000, DataBitRateFactor::x1);

MoteusTeensyCanFD canBus(ACAN_T4::can3, canSettings);

static uint32_t gNextSendMillis = 0;

//——————————————————————————————————————————————————————————————————————————————
//  Moteus controller objects
//——————————————————————————————————————————————————————————————————————————————

Moteus moteus1(canBus, []() {
  Moteus::Options options;
  options.id = 1;
  return options;
}());
Moteus moteus2(canBus, []() {
  Moteus::Options options;
  options.id = 2;
  return options;
}());
Moteus moteus3(canBus, []() {
  Moteus::Options options;
  options.id = 3;
  return options;
}());
Moteus moteus4(canBus, []() {
  Moteus::Options options;
  options.id = 4;
  return options;
}());
Moteus moteus5(canBus, []() {
  Moteus::Options options;
  options.id = 5;
  return options;
}());
Moteus moteus6(canBus, []() {
  Moteus::Options options;
  options.id = 6;
  return options;
}());
Moteus moteus7(canBus, []() {
  Moteus::Options options;
  options.id = 7;
  return options;
}());
Moteus moteus8(canBus, []() {
  Moteus::Options options;
  options.id = 8;
  return options;
}());
Moteus moteus9(canBus, []() {
  Moteus::Options options;
  options.id = 9;
  return options;
}());
Moteus moteus10(canBus, []() {
  Moteus::Options options;
  options.id = 10;
  return options;
}());
Moteus moteus11(canBus, []() {
  Moteus::Options options;
  options.id = 11;
  return options;
}());
Moteus moteus12(canBus, []() {
  Moteus::Options options;
  options.id = 12;
  return options;
}());

Moteus::PositionMode::Command position_cmd;

Moteus allMoteus[12] = { moteus1, moteus2, moteus3, moteus4, moteus5, moteus6, moteus7, moteus8, moteus9, moteus10, moteus11, moteus12};

float velocity_val = 0.1;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  while (!Serial) {}
  Serial.println(F("started"));

  // Initialize CAN3 for CAN-FD operation.
  const uint32_t errorCode = ACAN_T4::can3.beginFD(canSettings);
  while (errorCode != 0) {
    Serial.print(F("CAN error 0x"));
    Serial.println(errorCode, HEX);
    delay(1000);
  }

  // To clear any faults the controllers may have, we start by sending
  // a stop command to each.
  for (uint16_t i = 1; i < 12; i++)
    allMoteus[i].SetStop();
  
  Serial.println(F("all stopped"));
}

uint16_t gLoopCount = 0;

void loop() {
  // We intend to send control frames every 20ms.
  const auto time = millis();
  if (gNextSendMillis >= time) { return; }

  gNextSendMillis += 20;
  gLoopCount++;

  Moteus::PositionMode::Command cmd;
  cmd.position = NaN;
  cmd.velocity = velocity_val * ::sin(time / 10000.0);

  for (uint16_t i = 1; i < 12; i++) {
    Serial.print(F(" V: "));
    Serial.print(cmd.velocity);
    allMoteus[i].SetPosition(cmd);
    cmd.velocity = velocity_val * ::sin((ceil(i / 2) * time) / 10000.0);
  }

  Serial.println();

  if (gLoopCount % 5 != 0) { return; }

  // Only print our status every 5th cycle, so every 1s.

  Serial.print(F("time "));
  Serial.print(gNextSendMillis);

  auto print_moteus = [](const Moteus::Query::Result& query) {
    Serial.print(static_cast<int>(query.mode));
    Serial.print(F(" "));
    Serial.print(query.position);
    Serial.print(F("  velocity "));
    Serial.print(query.velocity);
  };

  print_moteus(moteus1.last_result().values);
  Serial.print(F(" / "));
  print_moteus(moteus2.last_result().values);
  Serial.print(F(" / "));
  print_moteus(moteus3.last_result().values);
  Serial.print(F(" / "));
  print_moteus(moteus4.last_result().values);
  Serial.print(F(" / "));
  print_moteus(moteus5.last_result().values);
  Serial.print(F(" / "));
  print_moteus(moteus6.last_result().values);
  Serial.print(F(" / "));
  print_moteus(moteus7.last_result().values);
  Serial.print(F(" / "));
  print_moteus(moteus8.last_result().values);
  Serial.print(F(" / "));
  print_moteus(moteus9.last_result().values);
  Serial.print(F(" / "));
  print_moteus(moteus10.last_result().values);
  Serial.print(F(" / "));
  print_moteus(moteus11.last_result().values);
  Serial.print(F(" / "));
  print_moteus(moteus12.last_result().values);
  Serial.println();
}