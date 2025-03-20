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

//#include "HardwareTimer.h"
HardwareTimer *Timer7 = new HardwareTimer(TIM7);
HardwareSerial Serial1(PA10,PA9);//STm32G4のdefaultのSerialはLP1になっている

#define SLED_FR PC14
#define SLED_FL PC15
#define SLED_R PF0
#define SLED_L PF1

#define AD_RIGHT_S PA0
#define AD_LEFT_F PA1
#define AD_RIGHT_F PA2
#define AD_VDD PA3
#define AD_LEFT_S PC3

volatile short g_sensor_value_fr;
volatile short g_sensor_value_fl;
volatile short g_sensor_value_r;
volatile short g_sensor_value_l;
volatile short g_battery_value;

void sensorInterrupt(void) {
  static char cnt = 0;
  switch (cnt) {
    case 0:
      digitalWrite(SLED_FR, HIGH);  //LED点灯
      for (int i = 0; i < 300; i++) {
        asm("nop \n");
      }
      g_sensor_value_fr = analogRead(AD_RIGHT_F);
      digitalWrite(SLED_FR, LOW);  //LED消灯
      break;
    case 1:
      digitalWrite(SLED_FL, HIGH);  //LED点灯
      for (int i = 0; i < 300; i++) {
        asm("nop \n");
      }
      g_sensor_value_fl = analogRead(AD_LEFT_F);
      digitalWrite(SLED_FL, LOW);  //LED消灯
      break;
    case 2:
      digitalWrite(SLED_R, HIGH);  //LED点灯
      for (int i = 0; i < 300; i++) {
        asm("nop \n");
      }
      g_sensor_value_r = analogRead(AD_RIGHT_S);
      digitalWrite(SLED_R, LOW);  //LED消灯
      break;
    case 3:
      digitalWrite(SLED_L, HIGH);  //LED点灯
      for (int i = 0; i < 300; i++) {
        asm("nop \n");
      }
      g_sensor_value_l = analogRead(AD_LEFT_S);
      digitalWrite(SLED_L, LOW);  //LED消灯
      g_battery_value = (double)analogReadMilliVolts(AD_VDD) / 10.0 * (10.0 + 51.0);
      break;
    default:
      Serial1.printf("error¥n¥r");
      break;
  }
  cnt++;
  if (cnt >= 4) cnt = 0;
}

void setup() {
  // put your setup code here, to run once:
  //Sensor 発光off
  pinMode(SLED_FR, OUTPUT);
  pinMode(SLED_FL, OUTPUT);
  pinMode(SLED_R, OUTPUT);
  pinMode(SLED_L, OUTPUT);
  digitalWrite(SLED_FR, LOW);
  digitalWrite(SLED_FL, LOW);
  digitalWrite(SLED_R, LOW);
  digitalWrite(SLED_L, LOW);

  Serial1.begin(115200);

  Timer7->pause();
  Timer7->setOverflow(250,MICROSEC_FORMAT);
  Timer7->attachInterrupt(sensorInterrupt);
  Timer7->refresh();
  Timer7->resume();  //Timter Start
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial1.printf("r_sen  is %d\n\r", g_sensor_value_r);
  Serial1.printf("fr_sen is %d\n\r", g_sensor_value_fr);
  Serial1.printf("fl_sen is %d\n\r", g_sensor_value_fl);
  Serial1.printf("l_sen  is %d\n\r", g_sensor_value_l);
  Serial1.printf("VDD    is %d\n\r", g_battery_value);
  delay(100);
}
