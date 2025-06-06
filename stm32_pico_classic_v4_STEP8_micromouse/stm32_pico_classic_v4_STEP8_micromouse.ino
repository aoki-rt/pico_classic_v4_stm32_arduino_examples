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

#include "adjust.h"
#include "device.h"
#include "fast.h"
#include "Flash.h"
#include "map_manager.h"
#include "misc.h"
#include "parameter.h"
#include "run.h"
#include "search.h"
#include "sensor.h"
#include <SPI.h>
#include "TMC5240.h"

HardwareTimer *Timer6 = new HardwareTimer(TIM6);  //control
HardwareTimer *Timer7 = new HardwareTimer(TIM7);  //sensor
SPIClass SPI_2(PB15, PB14, PB13);                 //MOSI,MISO,SCLK,CS(option)

void setup() {
  // put your setup code here, to run once:
  deviceInit();
  g_tmc5240.init();
	g_map.goal_mx = GOAL_X;
	g_map.goal_my = GOAL_Y;
  
  motorDisable();
  buzzerEnable(INC_FREQ);
  delay(80);
  buzzerDisable();

  g_misc.mode_select = 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  ledSet(g_misc.mode_select);
  switch (switchGet()) {
    case SW_RM:
      g_misc.mode_select = g_misc.buttonInc(g_misc.mode_select, 15, 1);
      break;
    case SW_LM:
      g_misc.mode_select = g_misc.buttonDec(g_misc.mode_select, 1, 15);
      break;
    case SW_CM:
      g_misc.buttonOk();
      g_misc.modeExec(g_misc.mode_select);
      break;
  }
  delay(1);
}
