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

#define TRAFFIC_G_IO_D 12
#define TRAFFIC_Y_IO_D A0
#define TRAFFIC_R_IO_D A1

#define PED_G_IO_A3_A4 A2
#define PED_R_IO_A3_A4 A3

#define PED_G_IO_B3_B4 A4
#define PED_R_IO_B3_B4 A5


const uint8_t TRAFFIC_LIGHT_A[3] = {TRAFFIC_G_IO_A,TRAFFIC_Y_IO_A,TRAFFIC_R_IO_A};// pedestrian A1 connected to pedestrian A2
const uint8_t TRAFFIC_LIGHT_B[3] = {TRAFFIC_G_IO_B,TRAFFIC_Y_IO_B,TRAFFIC_R_IO_B};// pedestrian A1 connected to pedestrian A2
const uint8_t TRAFFIC_LIGHT_C[3] = {TRAFFIC_G_IO_C,TRAFFIC_Y_IO_C,TRAFFIC_R_IO_C};// pedestrian A1 connected to pedestrian A2
const uint8_t TRAFFIC_LIGHT_D[3] = {TRAFFIC_G_IO_D,TRAFFIC_Y_IO_D,TRAFFIC_R_IO_D};// pedestrian A1 connected to pedestrian A2
const uint8_t PEDESTRIANS_A3_A4[2] = {PED_G_IO_A3_A4,PED_R_IO_A3_A4};
const uint8_t PEDESTRIANS_B3_B4[2] = {PED_G_IO_B3_B4,PED_R_IO_B3_B4};





const uint16_t PWM_MAX = 4095;     // 12-bit: 0..4095
const uint16_t DELAY_MS = 2;       // pause entre steps
const uint16_t NUMBER_OF_OUTPUT = 16;
const uint8_t GREEN_WIRE = 0;
const uint8_t YELLOW_WIRE = 1;
const uint8_t RED_WIRE = 2;
const uint8_t GREEN_WIRE_PED = 0;
const uint8_t RED_WIRE_PED = 1;

int8_t seq = 1;
long timer_btw_sq = 0;
const uint32_t TIME_SEQ = 5000;
const uint32_t TIME_BTW_SEQ = 1000;

const unsigned long CROSSWALK_DELAY = 1000;
unsigned long crosswalk_timer = 0;
bool crosswalk_state = false; // false=LOW, true=HIGH


void INIT_CROSSWALK(){
  crosswalk_timer = millis();
  crosswalk_state = false;
  digitalWrite(CROSSWALK_IO_E1_E2, LOW);
}
void INIT_G_pinmode(uint8_t* ch_traffic_light){
  pinMode(ch_traffic_light[GREEN_WIRE],OUTPUT);
  pinMode(ch_traffic_light[YELLOW_WIRE],OUTPUT);
  pinMode(ch_traffic_light[RED_WIRE],INPUT);
}

void INIT_Y_pinmode(uint8_t* ch_traffic_light){
  pinMode(ch_traffic_light[GREEN_WIRE],INPUT);
  pinMode(ch_traffic_light[YELLOW_WIRE],OUTPUT);
  pinMode(ch_traffic_light[RED_WIRE],OUTPUT);
}

void INIT_R_pinmode(uint8_t* ch_traffic_light){
  pinMode(ch_traffic_light[GREEN_WIRE],INPUT);
  pinMode(ch_traffic_light[YELLOW_WIRE],OUTPUT);
  pinMode(ch_traffic_light[RED_WIRE],OUTPUT);
}

void INIT_PED_pinmode(uint8_t* ch_traffic_light){
  pinMode(ch_traffic_light[GREEN_WIRE],OUTPUT);
  pinMode(ch_traffic_light[YELLOW_WIRE],INPUT);
  pinMode(ch_traffic_light[RED_WIRE],OUTPUT);
}



void BLINK_CROSSWALK(const uint8_t *crosswalk_io) {

  if (millis() - crosswalk_timer >= CROSSWALK_DELAY) {
    crosswalk_timer = millis();
    crosswalk_state = !crosswalk_state;
    digitalWrite(CROSSWALK_IO_E1_E2, crosswalk_state ? HIGH : LOW);
  }
}



void RED_LIGHT(uint8_t* ch_traffic_light){
  INIT_R_pinmode(ch_traffic_light);
  digitalWrite(ch_traffic_light[YELLOW_WIRE], LOW);
  digitalWrite(ch_traffic_light[RED_WIRE], HIGH);
   
}

void YELLOW_LIGHT(uint8_t* ch_traffic_light){
  INIT_Y_pinmode(ch_traffic_light);
  digitalWrite(ch_traffic_light[GREEN_WIRE], LOW);
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
  digitalWrite(ch_traffic_light[GREEN_WIRE], LOW);
  digitalWrite(ch_traffic_light[RED_WIRE], HIGH);
}

void GREEN_LIGHT_PED_O(uint8_t* ch_traffic_light){
  digitalWrite(ch_traffic_light[GREEN_WIRE], HIGH);
  digitalWrite(ch_traffic_light[RED_WIRE], LOW);
}
/*



void SEQ_1_1(){
   RED_LIGHT_GREEN_PEDESTRIAN(TRAFFIC_LIGHT_A);
   RED_LIGHT_PEDESTRIAN(PEDESTRIANS_A3_A4);

   GREEN_LIGHT_RED_PEDESTRIAN(TRAFFIC_LIGHT_B);
   GREEN_LIGHT_PEDESTRIAN(PEDESTRIANS_B3_B4);

   RED_LIGHT_GREEN_PEDESTRIAN(TRAFFIC_LIGHT_C);

   RED_LIGHT_RED_PEDESTRIAN(TRAFFIC_LIGHT_D);

}

void SEQ_1_2(){
   RED_LIGHT_RED_PEDESTRIAN(TRAFFIC_LIGHT_A);
   YELLOW_LIGHT(TRAFFIC_LIGHT_A);

   YELLOW_LIGHT_RED_PEDESTRIAN(TRAFFIC_LIGHT_B);
   
   RED_LIGHT_RED_PEDESTRIAN(TRAFFIC_LIGHT_C);
   YELLOW_LIGHT(TRAFFIC_LIGHT_C);

}
*/

void setup() {
  Serial.begin(115200);
  pinMode(CROSSWALK_IO_E1_E2,OUTPUT);

  pinMode(TRAFFIC_G_IO_A,OUTPUT);
  pinMode(TRAFFIC_Y_IO_A,OUTPUT);
  pinMode(TRAFFIC_R_IO_A,OUTPUT);

  pinMode(TRAFFIC_G_IO_B,OUTPUT);
  pinMode(TRAFFIC_Y_IO_B,OUTPUT);
  pinMode(TRAFFIC_R_IO_B,OUTPUT);

  pinMode(TRAFFIC_G_IO_C,OUTPUT);
  pinMode(TRAFFIC_Y_IO_C,OUTPUT);
  pinMode(TRAFFIC_R_IO_C,OUTPUT);

  pinMode(TRAFFIC_G_IO_D,OUTPUT);
  pinMode(TRAFFIC_Y_IO_D,OUTPUT);
  pinMode(TRAFFIC_R_IO_D,OUTPUT);

  pinMode(PED_G_IO_A3_A4,OUTPUT);
  pinMode(PED_R_IO_A3_A4,OUTPUT);

  pinMode(PED_G_IO_B3_B4,OUTPUT);
  pinMode(PED_R_IO_B3_B4,OUTPUT);

  INIT_CROSSWALK();
  Serial.println("init");
  
}


void loop() {
  BLINK_CROSSWALK(CROSSWALK_IO_E1_E2);
  //RED_LIGHT(TRAFFIC_LIGHT_A);
  //delay(5);
  //YELLOW_LIGHT(TRAFFIC_LIGHT_A);
  //delay(5);
  //GREEN_LIGHT_PED(TRAFFIC_LIGHT_A);

  RED_LIGHT(TRAFFIC_LIGHT_B);
  delay(5);
  YELLOW_LIGHT(TRAFFIC_LIGHT_B);
  delay(5);
  GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
  delay(5);
 
  /*
  if(seq == 1 && (millis() - timer_btw_sq >= TIME_SEQ)){
    SEQ_1_1();
    seq++;
    timer_btw_sq = millis();

  }

  if(seq == 2 && (millis() - timer_btw_sq <= TIME_BTW_SEQ)){
    SEQ_1_2();
  }
  else{
    seq++;
    timer_btw_sq = millis();
  }

  /*if(seq == 3 && (millis() - timer_btw_sq <= TIME_SEQ)){
    SEQ_2_1();
    eq++;
    timer_btw_sq = millis();
  }
  */


}