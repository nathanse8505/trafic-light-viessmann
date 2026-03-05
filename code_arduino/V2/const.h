#ifndef CONST
#define CONST
/*      *==========Arduino Nano pinout======
 *                         _______
 *                    TXD-|       |-Vin
 *                    RXD-|       |-Gnd
 *                    RST-|       |-RST
 *                    GND-|       |-+5V
 * CROSSWALK_IO_E1_E2  D2-|       |-A7  
 *     TRAFFIC_G_IO_A  D3-|       |-A6  
 *     TRAFFIC_Y_IO_A  D4-|       |-A5, PED_R_IO_B3_B4
 *     TRAFFIC_R_IO_A  D5-|       |-A4, PED_G_IO_A3_A4
 *     TRAFFIC_G_IO_B  D6-|       |-A3, PED_R_IO_A3_A4 
 *     TRAFFIC_Y_IO_B  D7-|       |-A2, TRAFFIC_R_IO_D 
 *     TRAFFIC_R_IO_B  D8-|       |-A1, TRAFFIC_Y_IO_D 
 *     TRAFFIC_G_IO_C  D9-|       |-A0, TRAFFIC_G_IO_D 
 *     TRAFFIC_Y_IO_C D10-|       |-Ref
 *     TRAFFIC_R_IO_C D11-|       |-3.3V
 *     PED_G_IO_B3_B4 D12-|       |-D13 
 *                         --USB--
 */

#define CROSSWALK_IO_E1_E2 2 
#define TRAFFIC_G_IO_A 3
#define TRAFFIC_Y_IO_A 4
#define TRAFFIC_R_IO_A 5

#define TRAFFIC_G_IO_B 6
#define TRAFFIC_Y_IO_B 7
#define TRAFFIC_R_IO_B 8

#define TRAFFIC_G_IO_C 9
#define TRAFFIC_Y_IO_C 10
#define TRAFFIC_R_IO_C 11

#define TRAFFIC_G_IO_D A0
#define TRAFFIC_Y_IO_D A1
#define TRAFFIC_R_IO_D A2

#define PED_R_IO_A3_A4 A3
#define PED_G_IO_A3_A4 A4


#define PED_R_IO_B3_B4 A5
#define PED_G_IO_B3_B4 12



const uint8_t TRAFFIC_LIGHT_A[3] = {TRAFFIC_G_IO_A,TRAFFIC_Y_IO_A,TRAFFIC_R_IO_A};// pedestrian A1 connected to pedestrian A2
const uint8_t TRAFFIC_LIGHT_B[3] = {TRAFFIC_G_IO_B,TRAFFIC_Y_IO_B,TRAFFIC_R_IO_B};// pedestrian A1 connected to pedestrian A2
const uint8_t TRAFFIC_LIGHT_C[3] = {TRAFFIC_G_IO_C,TRAFFIC_Y_IO_C,TRAFFIC_R_IO_C};// pedestrian A1 connected to pedestrian A2
const uint8_t TRAFFIC_LIGHT_D[3] = {TRAFFIC_G_IO_D,TRAFFIC_Y_IO_D,TRAFFIC_R_IO_D};// pedestrian A1 connected to pedestrian A2
const uint8_t PEDESTRIANS_A3_A4[2] = {PED_G_IO_A3_A4,PED_R_IO_A3_A4};
const uint8_t PEDESTRIANS_B3_B4[2] = {PED_G_IO_B3_B4,PED_R_IO_B3_B4};




const uint8_t GREEN_WIRE = 0;
const uint8_t YELLOW_WIRE = 1;
const uint8_t RED_WIRE = 2;
const uint8_t GREEN_WIRE_PED = 0;
const uint8_t RED_WIRE_PED = 1;


int8_t last_seq = -1;
int8_t seq = 1;
unsigned long timer_btw_sq = 0;


//////////// CROSSWALK signspot/////////////
const uint16_t CROSSWALK_DELAY = 1000;
unsigned long crosswalk_timer = 0;
bool crosswalk_state = false; // false=LOW, true=HIGH
/////////////////// SEQUENCE ////////////////
const uint32_t TIME_SEQ        = 5000; // for sequence SEQ_X_1
const uint32_t TIME_TO_BLINK   = 2000; // for sequence SEQ_X_2
const uint32_t TIME_BTW_SEQ    = 1500; // for sequence SEQ_X_3
const int TIME_TO_BLINK_YELLOW = 20000;// for sequence SEQ_7
const int INTERVAL_MULTEPLEXING = 6;//in ms
////////////////BLINK //////////////
const unsigned long BLINK_GREEN_ON_MS  = 300;  // durée phase ON
const unsigned long BLINK_GREEN_OFF_MS = 300;  // durée phase OFF

const unsigned long BLINK_YELLOW_ON_MS  = 500;  // durée phase ON
const unsigned long BLINK_YELLOW_OFF_MS = 500;  // durée phase OFF

bool blink_phase_on = true;          // true=phase ON, false=phase OFF
unsigned long time_blink_phase = 0;  // début de la phase actuelle

// ---- Globals (à mettre en haut) ----
uint8_t phase = 0;                 // 0,1,2
unsigned long time_phase = 0;       // timestamp du début de phase


#endif