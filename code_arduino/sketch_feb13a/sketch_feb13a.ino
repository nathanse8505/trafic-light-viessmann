#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


const uint8_t TRAFFIC_LIGHT_A[3] = {0,1,2};// pedestrian A1 connected to pedestrian A2
const uint8_t TRAFFIC_LIGHT_B[3] = {3,4,5}; //pedestrian B1 connected to pedestrian B2
const uint8_t TRAFFIC_LIGHT_C[3] = {6,7,8}; // pedestrian C1 connected to pedestrian C2
const uint8_t TRAFFIC_LIGHT_D[3] = {9,10,11};// pedestrian D1 connected to pedestrian D2
const uint8_t PEDESTRIANS_A3_A4[2] = {12,13};
const uint8_t PEDESTRIANS_B3_B4[2] = {14,15};

#define CROSSWALK_IO_E1 3 
#define CROSSWALK_IO_E2 4 


// Adresse I2C du PCA9685 (souvent 0x40)
Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver(0x40);


const uint16_t PWM_MAX = 4095;     // 12-bit: 0..4095
const uint16_t DELAY_MS = 2;       // pause entre steps
const uint16_t NUMBER_OF_OUTPUT = 16;
const uint8_t GREEN_WIRE = 0;
const uint8_t YELLOW_WIRE = 1;
const uint8_t RED_WIRE = 2;
const uint8_t GREEN_WIRE_PED = 0;
const uint8_t RED_WIRE_PED = 1;


const int8_t NUMBER_OF_CROSSWALK = 2;
uint8_t CROSSWALKS[NUMBER_OF_CROSSWALK] = {CROSSWALK_IO_E1,CROSSWALK_IO_E2};
const unsigned long CROSSWALK_DELAY = 1500;
unsigned long crosswalk_timer = 0;
bool crosswalk_state = false; // false=LOW, true=HIGH


void INIT_CROSSWALK(){
  crosswalk_timer = millis();
  crosswalk_state = false;
  for (uint8_t i = 0; i < NUMBER_OF_CROSSWALK; i++) digitalWrite(CROSSWALKS[i], LOW);
}

void BLINK_CROSSWALK(const uint8_t *crosswalk_io, uint8_t count) {

  if (millis(); - crosswalk_timer >= CROSSWALK_DELAY) {
    crosswalk_timer = millis();
    crosswalk_state = !crosswalk_state;

    for (uint8_t i = 0; i < count; i++) {
      digitalWrite(crosswalk_io[i], crosswalk_state ? HIGH : LOW);
    }
  }
}



void RED_LIGHT_GREEN_PEDESTRIAN(uint8_t ch_traffic_light[]){
   pca.setPWM(ch_traffic_light[GREEN_WIRE], 0, 0);   // ON à 0, OFF à v => duty proportionnel
   pca.setPWM(ch_traffic_light[YELLOW_WIRE], 0, 0);   // ON à 0, OFF à v => duty proportionnel
   pca.setPWM(ch_traffic_light[RED_WIRE], 0,  PWM_MAX);   // ON à 0, OFF à v => duty proportionnel

}

void RED_LIGHT_RED_PEDESTRIAN(uint8_t ch_traffic_light[]){
   pca.setPWM(ch_traffic_light[GREEN_WIRE], 0, 0);   // ON à 0, OFF à v => duty proportionnel
   pca.setPWM(ch_traffic_light[YELLOW_WIRE], 0, 0);   // ON à 0, OFF à v => duty proportionnel
   pca.setPWM(ch_traffic_light[RED_WIRE], 0,  PWM_MAX);   // ON à 0, OFF à v => duty proportionnel

}

void YELLOW_LIGHT_RED_PEDESTRIAN(uint8_t ch_traffic_light[]){
   pca.setPWM(ch_traffic_light[GREEN_WIRE], 0,  0);   // ON à 0, OFF à v => duty proportionnel
   pca.setPWM(ch_traffic_light[YELLOW_WIRE], 0, PWM_MAX);   // ON à 0, OFF à v => duty proportionnel
   pca.setPWM(ch_traffic_light[RED_WIRE], 0, 0);   // ON à 0, OFF à v => duty proportionnel
  
}

void YELLOW_LIGHT(uint8_t ch_traffic_light[]){
   pca.setPWM(ch_traffic_light[GREEN_WIRE], 0, 0);   // ON à 0, OFF à v => duty proportionnel
   pca.setPWM(ch_traffic_light[YELLOW_WIRE], 0, PWM_MAX);   // ON à 0, OFF à v => duty proportionnel
   pca.setPWM(ch_traffic_light[RED_WIRE], 0, 0);   // ON à 0, OFF à v => duty proportionnel
  
}


void GREEN_LIGHT_GREEN_PEDESTRIAN(uint8_t ch_traffic_light[]){
  pca.setPWM(ch_traffic_light[GREEN_WIRE], 0, PWM_MAX);   // ON à 0, OFF à v => duty proportionnel
  pca.setPWM(ch_traffic_light[YELLOW_WIRE], 0,0);   // ON à 0, OFF à v => duty proportionnel
  pca.setPWM(ch_traffic_light[RED_WIRE], 0, 0);   // ON à 0, OFF à v => duty proportionnel
}

void GREEN_LIGHT_RED_PEDESTRIAN(uint8_t ch_traffic_light[]){
  pca.setPWM(ch_traffic_light[GREEN_WIRE], 0, PWM_MAX);   // ON à 0, OFF à v => duty proportionnel
  pca.setPWM(ch_traffic_light[YELLOW_WIRE], 0, 0);   // ON à 0, OFF à v => duty proportionnel
  pca.setPWM(ch_traffic_light[RED_WIRE], 0, 0);   // ON à 0, OFF à v => duty proportionnel
}


void BLANK_LIGHT(uint8_t ch_traffic_light[]){
  pca.setPWM(ch_traffic_light[GREEN_WIRE], 0, 0);   // ON à 0, OFF à v => duty proportionnel
  pca.setPWM(ch_traffic_light[YELLOW_WIRE], 0, 0);   // ON à 0, OFF à v => duty proportionnel
  pca.setPWM(ch_traffic_light[RED_WIRE], 0, 0);   // ON à 0, OFF à v => duty proportionnel
}

void GREEN_LIGHT_PEDESTRIAN(uint8_t ch_pedestrian[]){
  pca.setPWM(ch_pedestrian[GREEN_WIRE_PED], 0, PWM_MAX);   // ON à 0, OFF à v => duty proportionnel
  pca.setPWM(ch_pedestrian[RED_WIRE_PED], 0, 0);   // ON à 0, OFF à v => duty proportionnel
}

void RED_LIGHT_PEDESTRIAN(uint8_t ch_pedestrian[]){
  pca.setPWM(ch_pedestrian[GREEN_WIRE_PED], 0, 0);   // ON à 0, OFF à v => duty proportionnel
  pca.setPWM(ch_pedestrian[RED_WIRE_PED], 0, PWM_MAX);   // ON à 0, OFF à v => duty proportionnel
}



void SEQ_1(){
   RED_LIGHT_GREEN_PEDESTRIAN(TRAFFIC_LIGHT_A);
   RED_LIGHT_PEDESTRIAN(PEDESTRIANS_A3_A4);

   GREEN_LIGHT_RED_PEDESTRIAN(TRAFFIC_LIGHT_B);
   GREEN_LIGHT_PEDESTRIAN(PEDESTRIANS_B3_B4);

   RED_LIGHT_GREEN_PEDESTRIAN(TRAFFIC_LIGHT_C);

   RED_LIGHT_RED_PEDESTRIAN(TRAFFIC_LIGHT_D);

}


void setup() {
  pinMode(CROSSWALK_IO_E1,OUTPUT);
  pinMode( CROSSWALK_IO_E2,OUTPUT);

  Wire.begin();
  pca.begin();
  // Fréquence PWM (LED : 500-1000 Hz marche bien)
  pca.setPWMFreq(1000);

  // LED éteinte au départ
  for(int i = 0;i < NUMBER_OF_OUTPUT;i++){
      pca.setPWM(i, 0, 0);
  }
  INIT_CROSSWALK();
  
}


void loop() {
BLINK_CROSSWALK(CROSSWALKS, NUMBER_OF_CROSSWALK);
}