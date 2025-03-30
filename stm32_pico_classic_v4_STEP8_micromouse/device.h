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
#ifndef DEVICE_H_
#define DEVICE_H_

#define SW_LM 1
#define SW_CM 2
#define SW_RM 4

#define LED0 PB10
#define LED1 PB1
#define LED2 PA6
#define LED3 PA4

#define BLED0 PA7
#define BLED1 PC5

#define SW_L PC8
#define SW_C PC9
#define SW_R PA8

#define SLED_FR PC14
#define SLED_FL PC15
#define SLED_R PF0
#define SLED_L PF1

#define BUZZER PB2

#define AD_RIGHT_S PA0
#define AD_LEFT_F PA1
#define AD_RIGHT_F PA2
#define AD_VDD PA3
#define AD_LEFT_S PC3

#define MOTOR_EN PA15

#define SPI_CLK PB13
#define SPI_MOSI PB15
#define SPI_MISO PB14
#define SPI_CS_L PB12   //左モータ
#define SPI_CS_R PB7   //右モータ
#define SPI_CS_J PB9  //ジャイロ

#endif  // DEVICE_H_