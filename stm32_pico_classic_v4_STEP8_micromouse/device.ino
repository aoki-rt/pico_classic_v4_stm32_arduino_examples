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

void controlInterruptStart(void) {
  Timer6->resume();
}
void controlInterruptStop(void) {
  Timer6->pause();
}

void sensorInterruptStart(void) {
  Timer7->resume();
}
void sensorInterruptStop(void) {
  Timer7->pause();
}

void deviceInit(void) {
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  pinMode(BLED0, OUTPUT);
  pinMode(BLED1, OUTPUT);

  pinMode(SW_L, INPUT_PULLUP);
  pinMode(SW_C, INPUT_PULLUP);
  pinMode(SW_R, INPUT_PULLUP);

  pinMode(SLED_FR, OUTPUT);
  pinMode(SLED_FL, OUTPUT);
  pinMode(SLED_R, OUTPUT);
  pinMode(SLED_L, OUTPUT);
  digitalWrite(SLED_FR, LOW);
  digitalWrite(SLED_FL, LOW);
  digitalWrite(SLED_R, LOW);
  digitalWrite(SLED_L, LOW);

  pinMode(MOTOR_EN, OUTPUT);
  digitalWrite(MOTOR_EN, LOW);

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

  Serial.begin(115200);
}

//LED
void ledSet(unsigned char data) {
  digitalWrite(LED0, data & 0x01);
  digitalWrite(LED1, (data >> 1) & 0x01);
  digitalWrite(LED2, (data >> 2) & 0x01);
  digitalWrite(LED3, (data >> 3) & 0x01);
}

void bledSet(char data) {
  if (data & 0x01) {
    digitalWrite(BLED0, HIGH);
  } else {
    digitalWrite(BLED0, LOW);
  }
  if (data & 0x02) {
    digitalWrite(BLED1, HIGH);
  } else {
    digitalWrite(BLED1, LOW);
  }
}

//Buzzer
void buzzerEnable(short f) {
  analogWriteFrequency(f);
  analogWrite(BUZZER, 127);
}

void buzzerDisable(void) {
  analogWrite(BUZZER, 255);
}

//motor
void motorEnable(void) {
  digitalWrite(MOTOR_EN, LOW);  //Power ON
}
void motorDisable(void) {
  digitalWrite(MOTOR_EN, HIGH);  //Power OFF
}

//SWITCH
unsigned char switchGet(void) {
  unsigned char ret = 0;
  if (digitalRead(SW_R) == LOW) {
    do {
      delay(20);
    } while (digitalRead(SW_R) == LOW);
    ret |= SW_RM;
  }
  if (digitalRead(SW_C) == LOW) {
    do {
      delay(20);
    } while (digitalRead(SW_C) == LOW);
    ret |= SW_CM;
  }
  if (digitalRead(SW_L) == LOW) {
    do {
      delay(20);
    } while (digitalRead(SW_L) == LOW);
    ret |= SW_LM;
  }
  return ret;
}

//sensor
unsigned short sensorGetR(void) {
  digitalWrite(SLED_R, HIGH);
  unsigned short tmp = RTanalogRead(AD_RIGHT_S);
  digitalWrite(SLED_R, LOW);
  return tmp;
}
unsigned short sensorGetL(void) {
  digitalWrite(SLED_L, HIGH);
  unsigned short tmp = RTanalogRead(AD_LEFT_S);
  digitalWrite(SLED_L, LOW);
  return tmp;
}
unsigned short sensorGetFL(void) {
  digitalWrite(SLED_FL, HIGH);  //LED点灯
  unsigned short tmp = RTanalogRead(AD_LEFT_F);
  digitalWrite(SLED_FL, LOW);  //LED消灯
  return tmp;
}
unsigned short sensorGetFR(void) {
  digitalWrite(SLED_FR, HIGH);
  unsigned short tmp = RTanalogRead(AD_RIGHT_F);
  digitalWrite(SLED_FR, LOW);
  return tmp;
}
short batteryVoltGet(void) {
  return (float)RTanalogRead(AD_VDD) / 4095.0 * 3300.0 / 10.0 * (10.0 + 51.0);
}


uint16_t RTanalogRead(uint32_t ulPin){
  ADC_HandleTypeDef AdcHandle = {};
  ADC_ChannelConfTypeDef AdcChannelConf = {};
  __IO uint16_t uhADCxConvertedValue = 0;
  uint32_t bank = 0;

  PinName pin = analogInputToPinName(ulPin);

  AdcHandle.Instance = (ADC_TypeDef *)pinmap_peripheral(pin, PinMap_ADC);
  AdcHandle.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  AdcHandle.Init.Resolution = ADC_RESOLUTION_12B;
  AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  AdcHandle.Init.GainCompensation = 0;
  AdcHandle.Init.ScanConvMode = DISABLE;
  AdcHandle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  AdcHandle.Init.LowPowerAutoWait = DISABLE;
  AdcHandle.Init.ContinuousConvMode = DISABLE;
  AdcHandle.Init.NbrOfConversion = 1;
  AdcHandle.Init.DiscontinuousConvMode = DISABLE;
  AdcHandle.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  AdcHandle.Init.DMAContinuousRequests = DISABLE;
  AdcHandle.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  AdcHandle.Init.OversamplingMode = DISABLE;

  AdcHandle.State = HAL_ADC_STATE_RESET;
  AdcHandle.DMA_Handle = NULL;
  AdcHandle.Lock = HAL_UNLOCKED;

  if (HAL_ADC_Init(&AdcHandle) != HAL_OK) {
    return 0;
  }

  pinmap_pinout(pin, PinMap_ADC);

  AdcChannelConf.Channel = get_adc_channel(pin, &bank);
  AdcChannelConf.Rank = ADC_REGULAR_RANK_1;
  AdcChannelConf.SamplingTime = ADC_SAMPLETIME_47CYCLES_5;
  AdcChannelConf.SingleDiff = ADC_SINGLE_ENDED;
  AdcChannelConf.OffsetNumber = ADC_OFFSET_NONE;
  AdcChannelConf.Offset = 0;
  if (HAL_ADC_ConfigChannel(&AdcHandle, &AdcChannelConf) != HAL_OK) {
    return 0;
  }

  if (HAL_ADC_Start(&AdcHandle) != HAL_OK) {
    return 0;
  }

  if (HAL_ADC_PollForConversion(&AdcHandle, 10) != HAL_OK) {
    return 0;
  }

  if ((HAL_ADC_GetState(&AdcHandle) & HAL_ADC_STATE_REG_EOC) == HAL_ADC_STATE_REG_EOC) {
    uhADCxConvertedValue = HAL_ADC_GetValue(&AdcHandle);
  }

  if (HAL_ADC_Stop(&AdcHandle) != HAL_OK) {
    return 0;
  }

  return uhADCxConvertedValue;
}
