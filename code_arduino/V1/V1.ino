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
const uint32_t TIME_SEQ = 5000;
const uint32_t TIME_BTW_SEQ = 1500;

//////////// CROSSWALK signspot/////////////
const uint16_t CROSSWALK_DELAY = 1000;
unsigned long crosswalk_timer = 0;
bool crosswalk_state = false; // false=LOW, true=HIGH
///////////////////////////////////
const int INTERVAL_MULTEPLEXING = 6;//in ms
unsigned long time_multiplexing_1 = 0;
unsigned long time_multiplexing_2 = INTERVAL_MULTEPLEXING;
bool M = true;

const unsigned long BLINK_GREEN_ON_MS  = 300;  // durée phase ON
const unsigned long BLINK_GREEN_OFF_MS = 300;  // durée phase OFF

const unsigned long BLINK_YELLOW_ON_MS  = 500;  // durée phase ON
const unsigned long BLINK_YELLOW_OFF_MS = 500;  // durée phase OFF
bool blink_phase_on = true;          // true=phase ON, false=phase OFF
unsigned long time_blink_phase = 0;  // début de la phase actuelle
const int TIME_TO_BLINK = 2000;
const int TIME_TO_BLINK_YELLOW = 20000;

// ---- Globals (à mettre en haut) ----
uint8_t phase = 0;                 // 0,1,2
unsigned long time_phase = 0;       // timestamp du début de phase


void RESET_SEQ(){
  // Reset multiplexing state
  time_multiplexing_1 = millis();
  time_multiplexing_2 = millis();
  M = true;

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


void SEQ_1_1() {
  unsigned long now = millis();

  if (M == true) {
    if (now - time_multiplexing_1 < INTERVAL_MULTEPLEXING) {
      //Serial.println("enter1");

      // ===== PHASE 1 =====
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_A);
      RED_LIGHT_PED(TRAFFIC_LIGHT_B);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_C);
      RED_LIGHT_PED(TRAFFIC_LIGHT_D);

    } else {
      // Fin phase 1 -> start phase 2
      M = false;
      time_multiplexing_2 = now;
      return; // IMPORTANT: évite d'exécuter la phase 2 dans le même loop()
    }

  } else { // M == false
    if (now - time_multiplexing_2 < INTERVAL_MULTEPLEXING) {
      //Serial.println("enter2");

      // ===== PHASE 2 =====
      RED_LIGHT(TRAFFIC_LIGHT_A);
      GREEN_LIGHT(TRAFFIC_LIGHT_B);
      RED_LIGHT(TRAFFIC_LIGHT_C);
      RED_LIGHT(TRAFFIC_LIGHT_D);

    } else {
      // Fin phase 2 -> start phase 1
      M = true;
      time_multiplexing_1 = now;
      return; // IMPORTANT
    }
  }

  // ===== Toujours actifs (dans les 2 phases) =====
  RED_LIGHT_PED_O(PEDESTRIANS_A3_A4);
  GREEN_LIGHT_PED_O(PEDESTRIANS_B3_B4);
}

void SEQ_1_2(){
   unsigned long now = millis();

  if (M == true) {
    if (now - time_multiplexing_1 < INTERVAL_MULTEPLEXING) {
      //Serial.println("enter1");

      // ===== PHASE 1 =====
      RED_LIGHT_PED(TRAFFIC_LIGHT_A);
      RED_LIGHT_PED(TRAFFIC_LIGHT_B);
      RED_LIGHT_PED(TRAFFIC_LIGHT_C);
      RED_LIGHT_PED(TRAFFIC_LIGHT_D);

    } else {
      // Fin phase 1 -> start phase 2
      M = false;
      time_multiplexing_2 = now;
      return; // IMPORTANT: évite d'exécuter la phase 2 dans le même loop()
    }

  } else { // M == false
    if (now - time_multiplexing_2 < INTERVAL_MULTEPLEXING) {
      //Serial.println("enter2");

      // ===== PHASE 2 =====
      RED_LIGHT(TRAFFIC_LIGHT_A);
      BLINK_LIGHT_2PHASE(GREEN_WIRE,TRAFFIC_LIGHT_B,BLINK_GREEN_ON_MS,BLINK_GREEN_OFF_MS);
      RED_LIGHT(TRAFFIC_LIGHT_C);
      RED_LIGHT(TRAFFIC_LIGHT_D);

    } else {
      // Fin phase 2 -> start phase 1
      M = true;
      time_multiplexing_1 = now;
      return; // IMPORTANT
    }
  }

  // ===== Toujours actifs (dans les 2 phases) =====
  RED_LIGHT_PED_O(PEDESTRIANS_A3_A4);
  GREEN_LIGHT_PED_O(PEDESTRIANS_B3_B4);
    
}



// ---- Fonction 3 phases ----
void SEQ_1_3() {
  unsigned long now = millis();

  // Switch de phase si durée écoulée
  if (now - time_phase >= INTERVAL_MULTEPLEXING) {
    phase = (phase + 1) % 3;
    time_phase = now;
    return; // IMPORTANT: évite d'exécuter la nouvelle phase dans le même loop()
  }

  // ===== PHASES =====
  switch (phase) {

    case 0: // ===== PHASE 1 =====
      RED_LIGHT_PED(TRAFFIC_LIGHT_A);
      RED_LIGHT_PED(TRAFFIC_LIGHT_B);
      RED_LIGHT_PED(TRAFFIC_LIGHT_C);
      RED_LIGHT_PED(TRAFFIC_LIGHT_D);
      break;

    case 1: // ===== PHASE 2 =====
      RED_LIGHT(TRAFFIC_LIGHT_A);
      RED_LIGHT(TRAFFIC_LIGHT_C);
      RED_LIGHT(TRAFFIC_LIGHT_D);
      break;

    case 2: // ===== PHASE 3 ===== (à adapter selon ta logique)
      // Exemple: l'inverse de la phase 2 (ou ce que tu veux)
      YELLOW_LIGHT(TRAFFIC_LIGHT_A);
      YELLOW_LIGHT(TRAFFIC_LIGHT_B);
      YELLOW_LIGHT(TRAFFIC_LIGHT_C);
      break;
  }

}


void SEQ_2_1() {
  unsigned long now = millis();

  if (M == true) {
    if (now - time_multiplexing_1 < INTERVAL_MULTEPLEXING) {
      //Serial.println("enter1");

      // ===== PHASE 1 =====
      RED_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      RED_LIGHT_PED(TRAFFIC_LIGHT_C);
      RED_LIGHT_PED(TRAFFIC_LIGHT_D);

    } else {
      // Fin phase 1 -> start phase 2
      M = false;
      time_multiplexing_2 = now;
      return; // IMPORTANT: évite d'exécuter la phase 2 dans le même loop()
    }

  } else { // M == false
    if (now - time_multiplexing_2 < INTERVAL_MULTEPLEXING) {
      //Serial.println("enter2");

      // ===== PHASE 2 =====
      GREEN_LIGHT(TRAFFIC_LIGHT_A);
      RED_LIGHT(TRAFFIC_LIGHT_B);
      GREEN_LIGHT(TRAFFIC_LIGHT_C);
      RED_LIGHT(TRAFFIC_LIGHT_D);

    } else {
      // Fin phase 2 -> start phase 1
      M = true;
      time_multiplexing_1 = now;
      return; // IMPORTANT
    }
  }

  // ===== Toujours actifs (dans les 2 phases) =====
  RED_LIGHT_PED_O(PEDESTRIANS_A3_A4);
  RED_LIGHT_PED_O(PEDESTRIANS_B3_B4);
}


void SEQ_2_2(){
   unsigned long now = millis();

  if (M == true) {
    if (now - time_multiplexing_1 < INTERVAL_MULTEPLEXING) {
      //Serial.println("enter1");

      // ===== PHASE 1 =====
      RED_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      RED_LIGHT_PED(TRAFFIC_LIGHT_C);
      RED_LIGHT_PED(TRAFFIC_LIGHT_D);

    } else {
      // Fin phase 1 -> start phase 2
      M = false;
      time_multiplexing_2 = now;
      return; // IMPORTANT: évite d'exécuter la phase 2 dans le même loop()
    }

  } else { // M == false
    if (now - time_multiplexing_2 < INTERVAL_MULTEPLEXING) {
      //Serial.println("enter2");

      // ===== PHASE 2 =====

      BLINK_LIGHT_2PHASE(GREEN_WIRE,TRAFFIC_LIGHT_A,BLINK_GREEN_ON_MS,BLINK_GREEN_OFF_MS);
      RED_LIGHT(TRAFFIC_LIGHT_B);
      GREEN_LIGHT(TRAFFIC_LIGHT_C);
      RED_LIGHT(TRAFFIC_LIGHT_D);

    } else {
      // Fin phase 2 -> start phase 1
      M = true;
      time_multiplexing_1 = now;
      return; // IMPORTANT
    }
  }
}

// ---- Fonction 3 phases ----
void SEQ_2_3() {
  unsigned long now = millis();

  // Switch de phase si durée écoulée
  if (now - time_phase >= INTERVAL_MULTEPLEXING) {
    phase = (phase + 1) % 3;
    time_phase = now;
    return; // IMPORTANT: évite d'exécuter la nouvelle phase dans le même loop()
  }

  // ===== PHASES =====
  switch (phase) {

    case 0: // ===== PHASE 1 =====
      RED_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      RED_LIGHT_PED(TRAFFIC_LIGHT_C);
      RED_LIGHT_PED(TRAFFIC_LIGHT_D);
      break;

    case 1: // ===== PHASE 2 =====
      RED_LIGHT(TRAFFIC_LIGHT_B);
      GREEN_LIGHT(TRAFFIC_LIGHT_C);
      RED_LIGHT(TRAFFIC_LIGHT_D);
      break;

    case 2: // ===== PHASE 3 ===== (à adapter selon ta logique)
      // Exemple: l'inverse de la phase 2 (ou ce que tu veux)
      YELLOW_LIGHT(TRAFFIC_LIGHT_A);
      YELLOW_LIGHT(TRAFFIC_LIGHT_D);
      break;
  }

}


void SEQ_3_1() {
  unsigned long now = millis();

  if (M == true) {
    if (now - time_multiplexing_1 < INTERVAL_MULTEPLEXING) {
      //Serial.println("enter1");

      // ===== PHASE 1 =====
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      RED_LIGHT_PED(TRAFFIC_LIGHT_C);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_D);

    } else {
      // Fin phase 1 -> start phase 2
      M = false;
      time_multiplexing_2 = now;
      return; // IMPORTANT: évite d'exécuter la phase 2 dans le même loop()
    }

  } else { // M == false
    if (now - time_multiplexing_2 < INTERVAL_MULTEPLEXING) {
      //Serial.println("enter2");

      // ===== PHASE 2 =====
      RED_LIGHT(TRAFFIC_LIGHT_A);
      RED_LIGHT(TRAFFIC_LIGHT_B);
      GREEN_LIGHT(TRAFFIC_LIGHT_C);
      GREEN_LIGHT(TRAFFIC_LIGHT_D);

    } else {
      // Fin phase 2 -> start phase 1
      M = true;
      time_multiplexing_1 = now;
      return; // IMPORTANT
    }
  }

  // ===== Toujours actifs (dans les 2 phases) =====
  RED_LIGHT_PED_O(PEDESTRIANS_A3_A4);
  RED_LIGHT_PED_O(PEDESTRIANS_B3_B4);
}

void SEQ_3_2(){
   unsigned long now = millis();

  if (M == true) {
    if (now - time_multiplexing_1 < INTERVAL_MULTEPLEXING) {
      //Serial.println("enter1");

      // ===== PHASE 1 =====
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      RED_LIGHT_PED(TRAFFIC_LIGHT_C);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_D);

    } else {
      // Fin phase 1 -> start phase 2
      M = false;
      time_multiplexing_2 = now;
      return; // IMPORTANT: évite d'exécuter la phase 2 dans le même loop()
    }

  } else { // M == false
    if (now - time_multiplexing_2 < INTERVAL_MULTEPLEXING) {
      //Serial.println("enter2");

      // ===== PHASE 2 =====

      RED_LIGHT(TRAFFIC_LIGHT_A);
      RED_LIGHT(TRAFFIC_LIGHT_B);
      BLINK_LIGHT_2PHASE(GREEN_WIRE,TRAFFIC_LIGHT_C,BLINK_GREEN_ON_MS,BLINK_GREEN_OFF_MS);
      GREEN_LIGHT(TRAFFIC_LIGHT_D);

    } else {
      // Fin phase 2 -> start phase 1
      M = true;
      time_multiplexing_1 = now;
      return; // IMPORTANT
    }
  }
}

// ---- Fonction 3 phases ----
void SEQ_3_3() {
  unsigned long now = millis();

  // Switch de phase si durée écoulée
  if (now - time_phase >= INTERVAL_MULTEPLEXING) {
    phase = (phase + 1) % 3;
    time_phase = now;
    return; // IMPORTANT: évite d'exécuter la nouvelle phase dans le même loop()
  }

  // ===== PHASES =====
  switch (phase) {

    case 0: // ===== PHASE 1 =====
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      RED_LIGHT_PED(TRAFFIC_LIGHT_C);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_D);
      break;

    case 1: // ===== PHASE 2 =====
      RED_LIGHT(TRAFFIC_LIGHT_A);
      RED_LIGHT(TRAFFIC_LIGHT_B);
      GREEN_LIGHT(TRAFFIC_LIGHT_D);
      break;

    case 2: // ===== PHASE 3 ===== (à adapter selon ta logique)
      // Exemple: l'inverse de la phase 2 (ou ce que tu veux)
      
      YELLOW_LIGHT(TRAFFIC_LIGHT_C);
      break;
  }

}



void SEQ_4_1() {
  unsigned long now = millis();

  if (M == true) {
    if (now - time_multiplexing_1 < INTERVAL_MULTEPLEXING) {
      //Serial.println("enter1");

      // ===== PHASE 1 =====
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      RED_LIGHT_PED(TRAFFIC_LIGHT_C);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_D);

    } else {
      // Fin phase 1 -> start phase 2
      M = false;
      time_multiplexing_2 = now;
      return; // IMPORTANT: évite d'exécuter la phase 2 dans le même loop()
    }

  } else { // M == false
    if (now - time_multiplexing_2 < INTERVAL_MULTEPLEXING) {
      //Serial.println("enter2");

      // ===== PHASE 2 =====
      RED_LIGHT(TRAFFIC_LIGHT_A);
      RED_LIGHT(TRAFFIC_LIGHT_B);
      RED_LIGHT(TRAFFIC_LIGHT_C);
      GREEN_LIGHT(TRAFFIC_LIGHT_D);

    } else {
      // Fin phase 2 -> start phase 1
      M = true;
      time_multiplexing_1 = now;
      return; // IMPORTANT
    }
  }

  // ===== Toujours actifs (dans les 2 phases) =====
  GREEN_LIGHT_PED_O(PEDESTRIANS_A3_A4);
  RED_LIGHT_PED_O(PEDESTRIANS_B3_B4);
}

void SEQ_4_2(){
   unsigned long now = millis();

  if (M == true) {
    if (now - time_multiplexing_1 < INTERVAL_MULTEPLEXING) {
      //Serial.println("enter1");

      // ===== PHASE 1 =====
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      RED_LIGHT_PED(TRAFFIC_LIGHT_C);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_D);

    } else {
      // Fin phase 1 -> start phase 2
      M = false;
      time_multiplexing_2 = now;
      return; // IMPORTANT: évite d'exécuter la phase 2 dans le même loop()
    }

  } else { // M == false
    if (now - time_multiplexing_2 < INTERVAL_MULTEPLEXING) {
      //Serial.println("enter2");

      // ===== PHASE 2 =====

      RED_LIGHT(TRAFFIC_LIGHT_A);
      RED_LIGHT(TRAFFIC_LIGHT_B);
      RED_LIGHT(TRAFFIC_LIGHT_C);
      BLINK_LIGHT_2PHASE(GREEN_WIRE,TRAFFIC_LIGHT_D,BLINK_GREEN_ON_MS, BLINK_GREEN_OFF_MS);

    } else {
      // Fin phase 2 -> start phase 1
      M = true;
      time_multiplexing_1 = now;
      return; // IMPORTANT
    }
  }
}

// ---- Fonction 3 phases ----
void SEQ_4_3() {
  unsigned long now = millis();

  // Switch de phase si durée écoulée
  if (now - time_phase >= INTERVAL_MULTEPLEXING) {
    phase = (phase + 1) % 3;
    time_phase = now;
    return; // IMPORTANT: évite d'exécuter la nouvelle phase dans le même loop()
  }

  // ===== PHASES =====
  switch (phase) {

    case 0: // ===== PHASE 1 =====
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      RED_LIGHT_PED(TRAFFIC_LIGHT_C);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_D);
      break;

    case 1: // ===== PHASE 2 =====
      RED_LIGHT(TRAFFIC_LIGHT_A);
      RED_LIGHT(TRAFFIC_LIGHT_B);
      RED_LIGHT(TRAFFIC_LIGHT_C);
      break;

    case 2: // ===== PHASE 3 ===== (à adapter selon ta logique)
      // Exemple: l'inverse de la phase 2 (ou ce que tu veux)
      YELLOW_LIGHT(TRAFFIC_LIGHT_C);
      YELLOW_LIGHT(TRAFFIC_LIGHT_D);
      break;
  }

}



void SEQ_5_1() {
  unsigned long now = millis();

  if (M == true) {
    if (now - time_multiplexing_1 < INTERVAL_MULTEPLEXING) {
      //Serial.println("enter1");

      // ===== PHASE 1 =====
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      RED_LIGHT_PED(TRAFFIC_LIGHT_C);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_D);

    } else {
      // Fin phase 1 -> start phase 2
      M = false;
      time_multiplexing_2 = now;
      return; // IMPORTANT: évite d'exécuter la phase 2 dans le même loop()
    }

  } else { // M == false
    if (now - time_multiplexing_2 < INTERVAL_MULTEPLEXING) {
      //Serial.println("enter2");

      // ===== PHASE 2 =====
      RED_LIGHT(TRAFFIC_LIGHT_A);
      RED_LIGHT(TRAFFIC_LIGHT_B);
      GREEN_LIGHT(TRAFFIC_LIGHT_C);
      RED_LIGHT(TRAFFIC_LIGHT_D);

    } else {
      // Fin phase 2 -> start phase 1
      M = true;
      time_multiplexing_1 = now;
      return; // IMPORTANT
    }
  }

  // ===== Toujours actifs (dans les 2 phases) =====
  GREEN_LIGHT_PED_O(PEDESTRIANS_A3_A4);
  GREEN_LIGHT_PED_O(PEDESTRIANS_B3_B4);
}

void SEQ_5_2(){
   unsigned long now = millis();

  if (M == true) {
    if (now - time_multiplexing_1 < INTERVAL_MULTEPLEXING) {
      //Serial.println("enter1");

      // ===== PHASE 1 =====
      RED_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      RED_LIGHT_PED(TRAFFIC_LIGHT_C);
      RED_LIGHT_PED(TRAFFIC_LIGHT_D);

    } else {
      // Fin phase 1 -> start phase 2
      M = false;
      time_multiplexing_2 = now;
      return; // IMPORTANT: évite d'exécuter la phase 2 dans le même loop()
    }

  } else { // M == false
    if (now - time_multiplexing_2 < INTERVAL_MULTEPLEXING) {
      //Serial.println("enter2");

      // ===== PHASE 2 =====

      RED_LIGHT(TRAFFIC_LIGHT_A);
      RED_LIGHT(TRAFFIC_LIGHT_B);
      BLINK_LIGHT_2PHASE(GREEN_WIRE,TRAFFIC_LIGHT_C,BLINK_GREEN_ON_MS,BLINK_GREEN_OFF_MS);
      RED_LIGHT(TRAFFIC_LIGHT_D);

    } else {
      // Fin phase 2 -> start phase 1
      M = true;
      time_multiplexing_1 = now;
      return; // IMPORTANT
    }
  }
}

// ---- Fonction 3 phases ----
void SEQ_5_3() {
  unsigned long now = millis();

  // Switch de phase si durée écoulée
  if (now - time_phase >= INTERVAL_MULTEPLEXING) {
    phase = (phase + 1) % 3;
    time_phase = now;
    return; // IMPORTANT: évite d'exécuter la nouvelle phase dans le même loop()
  }

  // ===== PHASES =====
  switch (phase) {

    case 0: // ===== PHASE 1 =====
      RED_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      RED_LIGHT_PED(TRAFFIC_LIGHT_C);
      RED_LIGHT_PED(TRAFFIC_LIGHT_D);
      break;

    case 1: // ===== PHASE 2 =====
      RED_LIGHT(TRAFFIC_LIGHT_A);
      RED_LIGHT(TRAFFIC_LIGHT_B);
      RED_LIGHT(TRAFFIC_LIGHT_D);
      break;

    case 2: // ===== PHASE 3 ===== (à adapter selon ta logique)
      // Exemple: l'inverse de la phase 2 (ou ce que tu veux)
      YELLOW_LIGHT(TRAFFIC_LIGHT_A);
      YELLOW_LIGHT(TRAFFIC_LIGHT_C);
      break;
  }

}

void SEQ_6_1() {
  unsigned long now = millis();

  if (M == true) {
    if (now - time_multiplexing_1 < INTERVAL_MULTEPLEXING) {
      //Serial.println("enter1");

      // ===== PHASE 1 =====
      RED_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_C);
      RED_LIGHT_PED(TRAFFIC_LIGHT_D);

    } else {
      // Fin phase 1 -> start phase 2
      M = false;
      time_multiplexing_2 = now;
      return; // IMPORTANT: évite d'exécuter la phase 2 dans le même loop()
    }

  } else { // M == false
    if (now - time_multiplexing_2 < INTERVAL_MULTEPLEXING) {
      //Serial.println("enter2");

      // ===== PHASE 2 =====
      GREEN_LIGHT(TRAFFIC_LIGHT_A);
      RED_LIGHT(TRAFFIC_LIGHT_B);
      RED_LIGHT(TRAFFIC_LIGHT_C);
      RED_LIGHT(TRAFFIC_LIGHT_D);

    } else {
      // Fin phase 2 -> start phase 1
      M = true;
      time_multiplexing_1 = now;
      return; // IMPORTANT
    }
  }
  // ===== Toujours actifs (dans les 2 phases) =====
  GREEN_LIGHT_PED_O(PEDESTRIANS_A3_A4);
  RED_LIGHT_PED_O(PEDESTRIANS_B3_B4);
}

void SEQ_7() {

     BLINK_LIGHT_2PHASE(YELLOW_WIRE,TRAFFIC_LIGHT_A, BLINK_YELLOW_ON_MS, BLINK_YELLOW_OFF_MS);
     BLINK_LIGHT_2PHASE(YELLOW_WIRE,TRAFFIC_LIGHT_B, BLINK_YELLOW_ON_MS, BLINK_YELLOW_OFF_MS);
     BLINK_LIGHT_2PHASE(YELLOW_WIRE,TRAFFIC_LIGHT_C, BLINK_YELLOW_ON_MS, BLINK_YELLOW_OFF_MS);
     BLINK_LIGHT_2PHASE(YELLOW_WIRE,TRAFFIC_LIGHT_D, BLINK_YELLOW_ON_MS, BLINK_YELLOW_OFF_MS);
   
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
  if (seq != last_seq) {
    RESET_SEQ();          // très important avec M/phase/blink partagés
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