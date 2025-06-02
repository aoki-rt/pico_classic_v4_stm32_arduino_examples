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
#ifndef PARAMETER_H_
#define PARAMETER_H_

//初期パラメータ
#define TIRE_DIAMETER (48.21)
#define TREAD_WIDTH (69.5)

#define REF_SEN_R 380
#define REF_SEN_L 459

#define TH_SEN_R 69
#define TH_SEN_L 184
#define TH_SEN_FR 80
#define TH_SEN_FL 60

#define CONTH_SEN_R (TH_SEN_R+10)
#define CONTH_SEN_L (TH_SEN_L+10)

#define GOAL_X 7
#define GOAL_Y 7

#define WAITLOOP_SLED 300

#define CON_WALL_KP 0.3
#define SEARCH_ACCEL 1.5
#define TURN_ACCEL 0.3

#define SEARCH_SPEED 350
#define MAX_SPEED 1000
#define MIN_SPEED 30

#define INC_FREQ 3000
#define DEC_FREQ 2000

#define BATT_MAX 12000
#define BATT_MIN 10000

#define HALF_SECTION 90
#define SECTION 180

#endif  // PARAMETER_H_