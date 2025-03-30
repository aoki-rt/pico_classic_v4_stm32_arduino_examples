// Copyright 2025 RT Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "SPI.h"
#include "TMC5240.h"
#include "run.h"

HardwareTimer *Timer6 = new HardwareTimer(TIM6);
SPIClass SPI_2(PB15,PB14,PB13);//MOSI,MISO,SCLK,CS(option)

#define LED0 PB10
#define LED1 PB1
#define LED2 PA6
#define LED3 PA4

#define SW_L PC8
#define SW_C PC9
#define SW_R PA8

#define MOTOR_EN PA15

#define SPI_CLK PB13
#define SPI_MOSI PB15
#define SPI_MISO PB14
#define SPI_CS_L PB12   //左モータ
#define SPI_CS_R PB7   //右モータ
#define SPI_CS_J PB9  //ジャイロ

#define TIRE_DIAMETER (48.00)
#define PULSE TMC5240_PULSE

#define MIN_SPEED 30

void setup() {
  // put your setup code here, to run once:
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  pinMode(SW_L, INPUT_PULLUP);
  pinMode(SW_C, INPUT_PULLUP);
  pinMode(SW_R, INPUT_PULLUP);

  //motor disable
  pinMode(MOTOR_EN, OUTPUT);
  digitalWrite(MOTOR_EN, HIGH);

  Timer6->pause();
  Timer6->setOverflow(1000, MICROSEC_FORMAT);
  Timer6->attachInterrupt(controlInterrupt);
  Timer6->refresh();
  Timer6->resume();  //Timter Start

  digitalWrite(MOTOR_EN, LOW);
  delay(1);
  g_tmc5240.init();
  digitalWrite(MOTOR_EN, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  while (digitalRead(SW_L) & digitalRead(SW_C) & digitalRead(SW_R)) {
    continue;
  }
  digitalWrite(MOTOR_EN, LOW);
  delay(1000);
  digitalWrite(LED0, HIGH);
  g_run.accelerate(90, 350);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  g_run.oneStep(180, 350);
  digitalWrite(LED3, HIGH);
  g_run.decelerate(90, 350);
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  delay(1000);
  digitalWrite(MOTOR_EN, HIGH);
}
