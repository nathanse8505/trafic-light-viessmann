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




const uint8_t GREEN_WIRE = 0;
const uint8_t YELLOW_WIRE = 1;
const uint8_t RED_WIRE = 2;
const uint8_t GREEN_WIRE_PED = 0;
const uint8_t RED_WIRE_PED = 1;

int8_t seq = 1;
long timer_btw_sq = 0;
const uint32_t TIME_SEQ = 5000;
const uint32_t TIME_BTW_SEQ = 1500;

//////////// CROSSWALK signspot/////////////
const uint16_t CROSSWALK_DELAY = 1000;
unsigned long crosswalk_timer = 0;
bool crosswalk_state = false; // false=LOW, true=HIGH
///////////////////////////////////

long time_multiplexing = 0;
const int INTERVAL_MULTEPLEXING = 5;//in ms


long time_blink_green = 0;
long time_blink = 0;
const int TIME_TO_BLINK = 2000;
const int BLINK_GREEN = 200;
bool light_green_state = true;
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


void INIT_R_OR_Y_pinmode(uint8_t* ch_traffic_light){
  pinMode(ch_traffic_light[GREEN_WIRE],INPUT);
  pinMode(ch_traffic_light[YELLOW_WIRE],OUTPUT);
  pinMode(ch_traffic_light[RED_WIRE],OUTPUT);
}

void INIT_PED_pinmode(uint8_t* ch_traffic_light){
  pinMode(ch_traffic_light[GREEN_WIRE],OUTPUT);
  pinMode(ch_traffic_light[YELLOW_WIRE],INPUT);
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

void BLINK_GREEN_LIGHT(uint8_t* ch_traffic_light){
  INIT_G_pinmode(ch_traffic_light);
  if (millis() - time_blink >= BLINK_GREEN) {
    time_blink = millis();
    light_green_state = !light_green_state;
    digitalWrite(ch_traffic_light[GREEN_WIRE], light_green_state ? HIGH : LOW);
  }
}


void SEQ_1_1(){
  
  if(millis() - time_multiplexing > INTERVAL_MULTEPLEXING){
    GREEN_LIGHT_PED(TRAFFIC_LIGHT_A);
    RED_LIGHT_PED(TRAFFIC_LIGHT_B);
    GREEN_LIGHT_PED(TRAFFIC_LIGHT_C);
    RED_LIGHT_PED(TRAFFIC_LIGHT_D);
    time_multiplexing = millis();
  }
  else{
    RED_LIGHT(TRAFFIC_LIGHT_A);
    GREEN_LIGHT(TRAFFIC_LIGHT_B);
    RED_LIGHT(TRAFFIC_LIGHT_C);
    RED_LIGHT(TRAFFIC_LIGHT_D);
  }

  RED_LIGHT_PED_O(PEDESTRIANS_A3_A4);
  GREEN_LIGHT_PED_O(PEDESTRIANS_B3_B4);
}


void SEQ_1_2(){
  if(millis() - time_multiplexing > INTERVAL_MULTEPLEXING){
    RED_LIGHT_RED_PED(TRAFFIC_LIGHT_A);
    RED_LIGHT_PED(TRAFFIC_LIGHT_B);
    RED_LIGHT_RED_PED(TRAFFIC_LIGHT_C);
  }
  else{
    YELLOW_LIGHT(TRAFFIC_LIGHT_A);
    YELLOW_LIGHT(TRAFFIC_LIGHT_B);
    YELLOW_LIGHT(TRAFFIC_LIGHT_C);
  }
   
}

void SEQ_2_1(){
  
  if(millis() - time_multiplexing > INTERVAL_MULTEPLEXING){
    RED_LIGHT_PED(TRAFFIC_LIGHT_A);
    GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
    RED_LIGHT_PED(TRAFFIC_LIGHT_C);
    RED_LIGHT_PED(TRAFFIC_LIGHT_D);
    time_multiplexing = millis();
  }
  else{
    GREEN_LIGHT(TRAFFIC_LIGHT_A);
    RED_LIGHT(TRAFFIC_LIGHT_B);
    GREEN_LIGHT(TRAFFIC_LIGHT_C);
    RED_LIGHT(TRAFFIC_LIGHT_D);
  }

  RED_LIGHT_PED_O(PEDESTRIANS_A3_A4);
  RED_LIGHT_PED_O(PEDESTRIANS_B3_B4);
}





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

  timer_btw_sq = millis();
}


void loop() {
  BLINK_CROSSWALK(CROSSWALK_IO_E1_E2);

  if(seq == 1){
    if(millis() - timer_btw_sq >= TIME_SEQ){
      
      if (millis() - time_blink_green <= TIME_TO_BLINK){
        BLINK_GREEN_LIGHT(TRAFFIC_LIGHT_B);
      }
      else{
        seq++;
        timer_btw_sq = millis();
      }
    }
    else{
      SEQ_1_1();
      time_blink_green = millis();
    }
  }

  if(seq == 2){
    SEQ_1_2();
    if(millis() - timer_btw_sq >= TIME_BTW_SEQ){
      seq++;
      timer_btw_sq = millis();
    }
  }

  if(seq == 3){
      if(millis() - timer_btw_sq >= TIME_SEQ){
        
        if (millis() - time_blink_green <= TIME_TO_BLINK){
          BLINK_GREEN_LIGHT(TRAFFIC_LIGHT_A);
          BLINK_GREEN_LIGHT(TRAFFIC_LIGHT_C);
        }
        else{
          seq++;
          timer_btw_sq = millis();
        }
      }
      else{
        SEQ_2_1();
        time_blink_green = millis();
      }
    }


}