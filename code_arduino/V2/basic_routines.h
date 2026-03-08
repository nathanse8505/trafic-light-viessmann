#ifndef FUNCTION
#define FUNCTION

#include "const.h"


void RESET_SEQ(){
  // Reset 3-phase state (si utilisé)
  phase = 0;
  time_phase = millis();

  // Reset blink state (partagé)
  blink_phase_on = true;
  time_blink_phase = millis();
}

void INIT_CROSSWALK(){
  crosswalk_timer = millis();
  crosswalk_state = false;
  digitalWrite(CROSSWALK_IO_E1_E2, LOW);
}

void INIT_G_pinmode(const uint8_t* ch_traffic_light){
  pinMode(ch_traffic_light[GREEN_WIRE],OUTPUT);
  pinMode(ch_traffic_light[YELLOW_WIRE],OUTPUT);
  pinMode(ch_traffic_light[RED_WIRE],INPUT);
  digitalWrite(ch_traffic_light[RED_WIRE], LOW); // disable pullup on INPUT
}


void INIT_R_OR_Y_pinmode(const uint8_t* ch_traffic_light){
  pinMode(ch_traffic_light[GREEN_WIRE], INPUT);
  digitalWrite(ch_traffic_light[GREEN_WIRE], LOW); // disable pullup on INPUT
  pinMode(ch_traffic_light[YELLOW_WIRE], OUTPUT);
  pinMode(ch_traffic_light[RED_WIRE], OUTPUT);
}

void INIT_PED_pinmode(const uint8_t* ch_traffic_light){
  pinMode(ch_traffic_light[GREEN_WIRE],OUTPUT);
  pinMode(ch_traffic_light[YELLOW_WIRE],INPUT);
  digitalWrite(ch_traffic_light[YELLOW_WIRE], LOW); // disable pullup on INPUT
  pinMode(ch_traffic_light[RED_WIRE],OUTPUT);
}




void BLINK_CROSSWALK(const uint8_t crosswalk_io) {

  if (millis() - crosswalk_timer >= CROSSWALK_DELAY) {
    crosswalk_timer = millis();
    crosswalk_state = !crosswalk_state;
    digitalWrite(crosswalk_io, crosswalk_state ? HIGH : LOW);
  }
}


void RED_LIGHT(uint8_t* ch_traffic_light){
  INIT_R_OR_Y_pinmode(ch_traffic_light);
  digitalWrite(ch_traffic_light[YELLOW_WIRE], LOW);
  digitalWrite(ch_traffic_light[RED_WIRE], HIGH);
}

void RED_LIGHT_RED_PED(uint8_t* ch_traffic_light){
  pinMode(ch_traffic_light[GREEN_WIRE],OUTPUT);
  pinMode(ch_traffic_light[YELLOW_WIRE],OUTPUT);
  pinMode(ch_traffic_light[RED_WIRE],OUTPUT);
  digitalWrite(ch_traffic_light[GREEN_WIRE], LOW);
  digitalWrite(ch_traffic_light[YELLOW_WIRE], LOW);
  digitalWrite(ch_traffic_light[RED_WIRE], HIGH);

}

void YELLOW_LIGHT(uint8_t* ch_traffic_light){
  INIT_R_OR_Y_pinmode(ch_traffic_light);
  digitalWrite(ch_traffic_light[YELLOW_WIRE], HIGH);
  digitalWrite(ch_traffic_light[RED_WIRE], LOW);
   
}

void GREEN_LIGHT(uint8_t* ch_traffic_light){
  INIT_G_pinmode(ch_traffic_light);
  digitalWrite(ch_traffic_light[GREEN_WIRE], HIGH);
  digitalWrite(ch_traffic_light[YELLOW_WIRE], LOW);
}

void RED_LIGHT_PED(uint8_t* ch_traffic_light){
  INIT_PED_pinmode(ch_traffic_light);
  digitalWrite(ch_traffic_light[GREEN_WIRE], LOW);
  digitalWrite(ch_traffic_light[RED_WIRE], HIGH);
}

void GREEN_LIGHT_PED(uint8_t* ch_traffic_light){
  INIT_PED_pinmode(ch_traffic_light);
  digitalWrite(ch_traffic_light[GREEN_WIRE], HIGH);
  digitalWrite(ch_traffic_light[RED_WIRE], LOW);
}

void RED_LIGHT_PED_O(uint8_t* ch_traffic_light){
  digitalWrite(ch_traffic_light[GREEN_WIRE_PED], LOW);
  digitalWrite(ch_traffic_light[RED_WIRE_PED], HIGH);
}

void GREEN_LIGHT_PED_O(uint8_t* ch_traffic_light){
  digitalWrite(ch_traffic_light[GREEN_WIRE_PED], HIGH);
  digitalWrite(ch_traffic_light[RED_WIRE_PED], LOW);
}

void BLANK_LIGHT_PED_O(uint8_t* ch_traffic_light){
  digitalWrite(ch_traffic_light[GREEN_WIRE_PED], LOW);
  digitalWrite(ch_traffic_light[RED_WIRE_PED], LOW);
}



void BLINK_LIGHT_2PHASE(int wire,uint8_t* ch_traffic_light,int delay_on,int delay_off) {
  if (wire == GREEN_WIRE){
    INIT_G_pinmode(ch_traffic_light);
    digitalWrite(ch_traffic_light[YELLOW_WIRE],LOW);
  }
  else{
    INIT_R_OR_Y_pinmode(ch_traffic_light);
    digitalWrite(ch_traffic_light[RED_WIRE],LOW);
  }
  
  unsigned long now = millis();
  unsigned long phase_duration = blink_phase_on ? delay_on : delay_off;

  // Changement de phase
  if (now - time_blink_phase >= phase_duration) {
    time_blink_phase = now;
    blink_phase_on = !blink_phase_on;
  }

  // Appliquer l’état correspondant à la phase
  digitalWrite(ch_traffic_light[wire], blink_phase_on ? HIGH : LOW);
}

#endif