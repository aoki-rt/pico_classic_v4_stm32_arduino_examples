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

#include "run.h"
#include "sensor.h"
#include "SPI.h"
#include "TMC5240.h"


HardwareTimer *Timer6 = new HardwareTimer(TIM6);
HardwareTimer *Timer7 = new HardwareTimer(TIM7);
SPIClass SPI_2(PB15,PB14,PB13);//MOSI,MISO,SCLK,CS(option)

#define LED0 PB10
#define LED1 PB1
#define LED2 PA6
#define LED3 PA4

#define SW_L PC8
#define SW_C PC9
#define SW_R PA8

#define MOTOR_EN PA15

#define AD_RIGHT_S PA0
#define AD_LEFT_F PA1
#define AD_RIGHT_F PA2
#define AD_VDD PA3
#define AD_LEFT_S PC3

#define SLED_FR PC14
#define SLED_FL PC15
#define SLED_R PF0
#define SLED_L PF1

#define SPI_CLK PB13
#define SPI_MOSI PB15
#define SPI_MISO PB14
#define SPI_CS_L PB12   //左モータ
#define SPI_CS_R PB7   //右モータ
#define SPI_CS_J PB9  //ジャイロ

#define TIRE_DIAMETER (48.00)
#define PULSE TMC5240_PULSE
#define TREAD_WIDTH (65.00)

#define MIN_SPEED 30


//環境に合わせて変更する
//ここから
#define REF_SEN_R 352
#define REF_SEN_L 327

#define TH_SEN_R 173
#define TH_SEN_L 169
#define TH_SEN_FR 145
#define TH_SEN_FL 134

#define CONTH_SEN_R TH_SEN_R
#define CONTH_SEN_L TH_SEN_L

#define CON_WALL_KP (0.5)
//ここまで


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

  pinMode(SLED_FR, OUTPUT);
  pinMode(SLED_FL, OUTPUT);
  pinMode(SLED_R, OUTPUT);
  pinMode(SLED_L, OUTPUT);
  digitalWrite(SLED_FR, LOW);
  digitalWrite(SLED_FL, LOW);
  digitalWrite(SLED_R, LOW);
  digitalWrite(SLED_L, LOW);

  Serial.begin(115200);

  Timer6->pause();
  Timer6->setOverflow(1000, MICROSEC_FORMAT);
  Timer6->attachInterrupt(controlInterrupt);
  Timer6->refresh();
  Timer6->resume();  //Timter Start

  Timer7->pause();
  Timer7->setOverflow(250, MICROSEC_FORMAT);
  Timer7->attachInterrupt(sensorInterrupt);
  Timer7->refresh();
  Timer7->resume();  //Timter Start

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
  if (digitalRead(SW_L) == 0) {
    while (1) {
      Serial.printf("r_sen  is %d\n\r", g_sensor.sen_r.value);
      Serial.printf("fr_sen is %d\n\r", g_sensor.sen_fr.value);
      Serial.printf("fl_sen is %d\n\r", g_sensor.sen_fl.value);
      Serial.printf("l_sen  is %d\n\r", g_sensor.sen_l.value);
      Serial.printf("VDD    is %d\n\r", g_sensor.battery_value);
      delay(100);
    }
  }
  digitalWrite(MOTOR_EN, LOW);
  delay(1000);
  g_run.accelerate(90, 350);
  g_run.oneStep(180 * 3, 350);
  g_run.decelerate(90, 350);
  delay(1000);
  digitalWrite(MOTOR_EN, HIGH);
}
