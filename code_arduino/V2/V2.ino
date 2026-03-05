#include "sequences.h"

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

  if (seq != last_seq) {
    RESET_SEQ();         
    last_seq = seq;
  }
  

  switch (seq){
 
    case 1:
      SEQ_1_1();
      if(millis() - timer_btw_sq >= TIME_SEQ){
        seq++;
        timer_btw_sq = millis();
      }
      break;
    

    case 2:
      SEQ_1_2();
      if(millis() - timer_btw_sq > TIME_TO_BLINK){
        seq++;
        timer_btw_sq = millis();
      }
      break;
  

    case 3:
      SEQ_1_3();
      if(millis() - timer_btw_sq >= TIME_BTW_SEQ){
        seq++;
        timer_btw_sq = millis();
      }
      break;
    

    case 4:
      SEQ_2_1();
      if(millis() - timer_btw_sq > TIME_SEQ){
        seq++;
        timer_btw_sq = millis();
      }
      break;
    

    case 5:
      SEQ_2_2();
      if(millis() - timer_btw_sq >= TIME_TO_BLINK){
        seq++;
        timer_btw_sq = millis();
      }
      break;
    

    case 6:
      SEQ_2_3();
      if(millis() - timer_btw_sq > TIME_BTW_SEQ){
        seq++;
        timer_btw_sq = millis();
      }
      break;
    

    case 7:
      SEQ_3_1();
      if(millis() - timer_btw_sq >= TIME_SEQ){
        seq++;
        timer_btw_sq = millis(); 
      }
      break;
    

    case 8:
      SEQ_3_2();
      if(millis() - timer_btw_sq > TIME_TO_BLINK){
        seq++;
        timer_btw_sq = millis();
      }
      break;
    

    case 9:
      SEQ_3_3();
      if(millis() - timer_btw_sq >= TIME_BTW_SEQ){
        seq++;
        timer_btw_sq = millis();
      }
      break;
    

    case 10:
      SEQ_4_1();
      if(millis() - timer_btw_sq > TIME_SEQ){
        seq++;
        timer_btw_sq = millis();
      }
      break;
    

    case 11:
      SEQ_4_2();
      if(millis() - timer_btw_sq >= TIME_TO_BLINK){
        seq++;
        timer_btw_sq = millis();
      }
      break;
    

    case 12:
      SEQ_4_3();
      if(millis() - timer_btw_sq > TIME_BTW_SEQ){
        seq++;
        timer_btw_sq = millis();
      }
      break;
    

    case 13:
      SEQ_5_1();
      if(millis() - timer_btw_sq >= TIME_SEQ){
        seq++;
        timer_btw_sq = millis();
      }
      break;
  

    case 14:
      SEQ_5_2();
      if(millis() - timer_btw_sq > TIME_TO_BLINK){
        seq++;
        timer_btw_sq = millis();
      }
      break;
    

    case 15:
      SEQ_5_3();
      if(millis() - timer_btw_sq >= TIME_BTW_SEQ){
        seq++;
        timer_btw_sq = millis();
      }
      break;
    


    case 16:
      SEQ_6_1();
      if(millis() - timer_btw_sq >= TIME_SEQ){
        seq++;
        timer_btw_sq = millis();
      }
      break;
    

    case 17:
      SEQ_7();
      if(millis() - timer_btw_sq > TIME_TO_BLINK_YELLOW){
        seq = 1;
        timer_btw_sq = millis();
      }
      break;
      
  }

}