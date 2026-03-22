#ifndef SEQ
#define SEQ

#include "basic_routines.h"

// ============================================================================
// SEQ 1
// ============================================================================

void SEQ_1_1() {
  unsigned long now = millis();

  if (now - time_phase >= INTERVAL_MULTEPLEXING) {
    phase = (phase + 1) % 2;
    time_phase = now;
    return; // IMPORTANT: évite d'exécuter la nouvelle phase dans le même loop()
  }

  switch (phase) {
    case 0: // ===== PHASE 1 =====
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_A);
      RED_LIGHT_PED(TRAFFIC_LIGHT_B);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_C);
      RED_LIGHT_PED(TRAFFIC_LIGHT_D);
      break;

    case 1: // ===== PHASE 2 =====
      RED_LIGHT(TRAFFIC_LIGHT_A);
      GREEN_LIGHT(TRAFFIC_LIGHT_B);
      RED_LIGHT(TRAFFIC_LIGHT_C);
      RED_LIGHT(TRAFFIC_LIGHT_D);
      break;
  }

  // ===== Toujours actifs (dans les 2 phases) =====
  RED_LIGHT_PED_O(PEDESTRIANS_A3_A4);
  GREEN_LIGHT_PED_O(PEDESTRIANS_B3_B4);
}

void SEQ_1_2() {
  unsigned long now = millis();

  if (now - time_phase >= INTERVAL_MULTEPLEXING) {
    phase = (phase + 1) % 2;
    time_phase = now;
    return;
  }

  switch (phase) {
    case 0: // ===== PHASE 1 =====
      RED_LIGHT_PED(TRAFFIC_LIGHT_A);
      RED_LIGHT_PED(TRAFFIC_LIGHT_B);
      RED_LIGHT_PED(TRAFFIC_LIGHT_C);
      RED_LIGHT_PED(TRAFFIC_LIGHT_D);
      break;

    case 1: // ===== PHASE 2 =====
      RED_LIGHT(TRAFFIC_LIGHT_A);
      BLINK_LIGHT_2PHASE(GREEN_WIRE, TRAFFIC_LIGHT_B, BLINK_GREEN_ON_MS, BLINK_GREEN_OFF_MS);
      RED_LIGHT(TRAFFIC_LIGHT_C);
      RED_LIGHT(TRAFFIC_LIGHT_D);
      break;
  }

  
}

// ---- Fonction 3 phases ----
void SEQ_1_3() {
  unsigned long now = millis();

  if (now - time_phase >= INTERVAL_MULTEPLEXING) {
    phase = (phase + 1) % 3;
    time_phase = now;
    return;
  }

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

    case 2: // ===== PHASE 3 =====
      YELLOW_LIGHT(TRAFFIC_LIGHT_A);
      YELLOW_LIGHT(TRAFFIC_LIGHT_B);
      YELLOW_LIGHT(TRAFFIC_LIGHT_C);
      break;
  }
}

// ============================================================================
// SEQ 2 
// ============================================================================

void SEQ_2_1() {
  unsigned long now = millis();

  if (now - time_phase >= INTERVAL_MULTEPLEXING) {
    phase = (phase + 1) % 2;
    time_phase = now;
    return;
  }

  switch (phase) {
    case 0: // PHASE 1
      RED_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      RED_LIGHT_PED(TRAFFIC_LIGHT_C);
      RED_LIGHT_PED(TRAFFIC_LIGHT_D);
      break;

    case 1: // PHASE 2
      GREEN_LIGHT(TRAFFIC_LIGHT_A);
      RED_LIGHT(TRAFFIC_LIGHT_B);
      GREEN_LIGHT(TRAFFIC_LIGHT_C);
      RED_LIGHT(TRAFFIC_LIGHT_D);
      break;
  }

  // Toujours actifs
  RED_LIGHT_PED_O(PEDESTRIANS_A3_A4);
  RED_LIGHT_PED_O(PEDESTRIANS_B3_B4);
}

void SEQ_2_2() {
  unsigned long now = millis();

  if (now - time_phase >= INTERVAL_MULTEPLEXING) {
    phase = (phase + 1) % 2;
    time_phase = now;
    return;
  }

  switch (phase) {
    case 0: // PHASE 1
      RED_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      RED_LIGHT_PED(TRAFFIC_LIGHT_C);
      RED_LIGHT_PED(TRAFFIC_LIGHT_D);
      break;

    case 1: // PHASE 2
      BLINK_LIGHT_2PHASE(GREEN_WIRE, TRAFFIC_LIGHT_A, BLINK_GREEN_ON_MS, BLINK_GREEN_OFF_MS);
      RED_LIGHT(TRAFFIC_LIGHT_B);
      GREEN_LIGHT(TRAFFIC_LIGHT_C);
      RED_LIGHT(TRAFFIC_LIGHT_D);
      break;
  }

}

// ---- Fonction 3 phases ----
void SEQ_2_3() {
  unsigned long now = millis();

  if (now - time_phase >= INTERVAL_MULTEPLEXING) {
    phase = (phase + 1) % 3;
    time_phase = now;
    return;
  }

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

    case 2: // ===== PHASE 3 =====
      YELLOW_LIGHT(TRAFFIC_LIGHT_A);
      YELLOW_LIGHT(TRAFFIC_LIGHT_D);
      break;
  }
}

// ============================================================================
// SEQ 3
// ============================================================================

void SEQ_3_1() {
  unsigned long now = millis();

  if (now - time_phase >= INTERVAL_MULTEPLEXING) {
    phase = (phase + 1) % 2;
    time_phase = now;
    return;
  }

  switch (phase) {
    case 0: // PHASE 1
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      RED_LIGHT_PED(TRAFFIC_LIGHT_C);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_D);
      break;

    case 1: // PHASE 2
      RED_LIGHT(TRAFFIC_LIGHT_A);
      RED_LIGHT(TRAFFIC_LIGHT_B);
      GREEN_LIGHT(TRAFFIC_LIGHT_C);
      GREEN_LIGHT(TRAFFIC_LIGHT_D);
      break;
  }
  // Toujours actifs
  //RED_LIGHT_PED_O(PEDESTRIANS_A3_A4);
  //RED_LIGHT_PED_O(PEDESTRIANS_B3_B4);

}

void SEQ_3_2() {
  unsigned long now = millis();

  if (now - time_phase >= INTERVAL_MULTEPLEXING) {
    phase = (phase + 1) % 2;
    time_phase = now;
    return;
  }

  switch (phase) {
    case 0: // PHASE 1
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      RED_LIGHT_PED(TRAFFIC_LIGHT_C);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_D);
      break;

    case 1: // PHASE 2
      RED_LIGHT(TRAFFIC_LIGHT_A);
      RED_LIGHT(TRAFFIC_LIGHT_B);
      BLINK_LIGHT_2PHASE(GREEN_WIRE, TRAFFIC_LIGHT_C, BLINK_GREEN_ON_MS, BLINK_GREEN_OFF_MS);
      GREEN_LIGHT(TRAFFIC_LIGHT_D);
      break;
  }
}

// ---- Fonction 3 phases ----
void SEQ_3_3() {
  unsigned long now = millis();

  if (now - time_phase >= INTERVAL_MULTEPLEXING) {
    phase = (phase + 1) % 3;
    time_phase = now;
    return;
  }

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

    case 2: // ===== PHASE 3 =====
      YELLOW_LIGHT(TRAFFIC_LIGHT_C);
      break;
  }
}

// ============================================================================
// SEQ 4
// ============================================================================

void SEQ_4_1() {
  unsigned long now = millis();

  if (now - time_phase >= INTERVAL_MULTEPLEXING) {
    phase = (phase + 1) % 2;
    time_phase = now;
    return;
  }

  switch (phase) {
    case 0: // PHASE 1
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      RED_LIGHT_PED(TRAFFIC_LIGHT_C);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_D);
      break;

    case 1: // PHASE 2
      RED_LIGHT(TRAFFIC_LIGHT_A);
      RED_LIGHT(TRAFFIC_LIGHT_B);
      RED_LIGHT(TRAFFIC_LIGHT_C);
      GREEN_LIGHT(TRAFFIC_LIGHT_D);
      break;
  }

  GREEN_LIGHT_PED_O(PEDESTRIANS_A3_A4);
  RED_LIGHT_PED_O(PEDESTRIANS_B3_B4);
}

void SEQ_4_2() {
  unsigned long now = millis();

  if (now - time_phase >= INTERVAL_MULTEPLEXING) {
    phase = (phase + 1) % 2;
    time_phase = now;
    return;
  }

  switch (phase) {
    case 0: // PHASE 1
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      RED_LIGHT_PED(TRAFFIC_LIGHT_C);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_D);
      break;

    case 1: // PHASE 2
      RED_LIGHT(TRAFFIC_LIGHT_A);
      RED_LIGHT(TRAFFIC_LIGHT_B);
      RED_LIGHT(TRAFFIC_LIGHT_C);
      BLINK_LIGHT_2PHASE(GREEN_WIRE, TRAFFIC_LIGHT_D, BLINK_GREEN_ON_MS, BLINK_GREEN_OFF_MS);
      break;
  }
}

// ---- Fonction 3 phases ----
void SEQ_4_3() {
  unsigned long now = millis();

  if (now - time_phase >= INTERVAL_MULTEPLEXING) {
    phase = (phase + 1) % 3;
    time_phase = now;
    return;
  }

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

    case 2: // ===== PHASE 3 =====
      YELLOW_LIGHT(TRAFFIC_LIGHT_C);
      YELLOW_LIGHT(TRAFFIC_LIGHT_D);
      break;
  }
}

// ============================================================================
// SEQ 5
// ============================================================================

void SEQ_5_1() {
  unsigned long now = millis();

  if (now - time_phase >= INTERVAL_MULTEPLEXING) {
    phase = (phase + 1) % 2;
    time_phase = now;
    return;
  }

  switch (phase) {
    case 0: // PHASE 1
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      RED_LIGHT_PED(TRAFFIC_LIGHT_C);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_D);
      break;

    case 1: // PHASE 2
      RED_LIGHT(TRAFFIC_LIGHT_A);
      RED_LIGHT(TRAFFIC_LIGHT_B);
      GREEN_LIGHT(TRAFFIC_LIGHT_C);
      RED_LIGHT(TRAFFIC_LIGHT_D);
      break;
  }

  GREEN_LIGHT_PED_O(PEDESTRIANS_A3_A4);
  GREEN_LIGHT_PED_O(PEDESTRIANS_B3_B4);
}

void SEQ_5_2() {
  unsigned long now = millis();

  if (now - time_phase >= INTERVAL_MULTEPLEXING) {
    phase = (phase + 1) % 2;
    time_phase = now;
    return;
  }

  switch (phase) {
    case 0: // PHASE 1
      RED_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      RED_LIGHT_PED(TRAFFIC_LIGHT_C);
      RED_LIGHT_PED(TRAFFIC_LIGHT_D);
      break;

    case 1: // PHASE 2
      RED_LIGHT(TRAFFIC_LIGHT_A);
      RED_LIGHT(TRAFFIC_LIGHT_B);
      BLINK_LIGHT_2PHASE(GREEN_WIRE, TRAFFIC_LIGHT_C, BLINK_GREEN_ON_MS, BLINK_GREEN_OFF_MS);
      RED_LIGHT(TRAFFIC_LIGHT_D);
      break;
  }
}

// ---- Fonction 3 phases ----
void SEQ_5_3() {
  unsigned long now = millis();

  if (now - time_phase >= INTERVAL_MULTEPLEXING) {
    phase = (phase + 1) % 3;
    time_phase = now;
    return;
  }

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

    case 2: // ===== PHASE 3 =====
      YELLOW_LIGHT(TRAFFIC_LIGHT_A);
      YELLOW_LIGHT(TRAFFIC_LIGHT_C);
      break;
  }
}

// ============================================================================
// SEQ 6
// ============================================================================

void SEQ_6_1() {
  unsigned long now = millis();

  if (now - time_phase >= INTERVAL_MULTEPLEXING) {
    phase = (phase + 1) % 2;
    time_phase = now;
    return;
  }

  switch (phase) {
    case 0: // PHASE 1
      RED_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_C);
      RED_LIGHT_PED(TRAFFIC_LIGHT_D);
      break;

    case 1: // PHASE 2
      GREEN_LIGHT(TRAFFIC_LIGHT_A);
      RED_LIGHT(TRAFFIC_LIGHT_B);
      RED_LIGHT(TRAFFIC_LIGHT_C);
      RED_LIGHT(TRAFFIC_LIGHT_D);
      break;
  }

  GREEN_LIGHT_PED_O(PEDESTRIANS_A3_A4);
  RED_LIGHT_PED_O(PEDESTRIANS_B3_B4);
}

void SEQ_6_2() {
  unsigned long now = millis();

  if (now - time_phase >= INTERVAL_MULTEPLEXING) {
    phase = (phase + 1) % 2;
    time_phase = now;
    return;
  }

  switch (phase) {
    case 0: // PHASE 1
      RED_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_C);
      RED_LIGHT_PED(TRAFFIC_LIGHT_D);
      break;

    case 1: // PHASE 2
      BLINK_LIGHT_2PHASE(GREEN_WIRE, TRAFFIC_LIGHT_A, BLINK_GREEN_ON_MS, BLINK_GREEN_OFF_MS);
      RED_LIGHT(TRAFFIC_LIGHT_B);
      RED_LIGHT(TRAFFIC_LIGHT_C);
      RED_LIGHT(TRAFFIC_LIGHT_D);
      
      break;
  }
}

void SEQ_6_3() {
  unsigned long now = millis();

  if (now - time_phase >= INTERVAL_MULTEPLEXING) {
    phase = (phase + 1) % 3;
    time_phase = now;
    return;
  }

  switch (phase) {
    case 0: // ===== PHASE 1 =====
      RED_LIGHT_PED(TRAFFIC_LIGHT_A);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_B);
      GREEN_LIGHT_PED(TRAFFIC_LIGHT_C);
      RED_LIGHT_PED(TRAFFIC_LIGHT_D);
      break;

    case 1: // ===== PHASE 2 =====
      RED_LIGHT(TRAFFIC_LIGHT_B);
      RED_LIGHT(TRAFFIC_LIGHT_C);
      RED_LIGHT(TRAFFIC_LIGHT_D);
      break;

    case 2: // ===== PHASE 3 =====
      YELLOW_LIGHT(TRAFFIC_LIGHT_A);
      YELLOW_LIGHT(TRAFFIC_LIGHT_B);
      break;
  }
}


// ============================================================================
// SEQ 7
// ============================================================================

void SEQ_7() {
  BLINK_LIGHT_2PHASE(YELLOW_WIRE, TRAFFIC_LIGHT_A, BLINK_YELLOW_ON_MS, BLINK_YELLOW_OFF_MS);
  BLINK_LIGHT_2PHASE(YELLOW_WIRE, TRAFFIC_LIGHT_B, BLINK_YELLOW_ON_MS, BLINK_YELLOW_OFF_MS);
  BLINK_LIGHT_2PHASE(YELLOW_WIRE, TRAFFIC_LIGHT_C, BLINK_YELLOW_ON_MS, BLINK_YELLOW_OFF_MS);
  BLINK_LIGHT_2PHASE(YELLOW_WIRE, TRAFFIC_LIGHT_D, BLINK_YELLOW_ON_MS, BLINK_YELLOW_OFF_MS);

  BLANK_LIGHT_PED_O(PEDESTRIANS_A3_A4);
  BLANK_LIGHT_PED_O(PEDESTRIANS_B3_B4);
}

#endif