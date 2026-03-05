# Traffic Light Controller (Arduino Nano)

This project drives a **4‑way traffic intersection** with:
- **4 traffic lights** (A, B, C, D) — each one has **Green / Yellow / Red**
- **2 pedestrian light groups** (A3/A4 and B3/B4) — each one has **Green / Red**
- A **“CROSSWALK” indicator output** that **blinks continuously**

The code is written to be **non‑blocking** (no `delay()` in the control logic): it uses `millis()` + internal state variables to handle timing and phase switching.

---

## Repository structure

### `V2.ino`
Main Arduino sketch:
- Configures all pins in `setup()`
- Continuously blinks the crosswalk output
- Runs the current **sequence** `seq` inside a `switch(seq)` state machine
- Advances to the next sequence after a configured duration (`TIME_SEQ`, `TIME_TO_BLINK`, `TIME_BTW_SEQ`, `TIME_TO_BLINK_YELLOW`)
- When `seq` changes, `RESET_SEQ()` is called to restart internal phase/blink state cleanly

### `const.h`
Constants and global variables:
- **Arduino Nano pin mapping**
- Arrays describing each light group:
  - `TRAFFIC_LIGHT_A/B/C/D` (3 pins each: G/Y/R)
  - `PEDESTRIANS_A3_A4`, `PEDESTRIANS_B3_B4` (2 pins each: G/R)
- Timing constants (sequence durations, blinking periods, multiplexing interval, etc.)
- Global state variables used by the sequencer (e.g., `seq`, `last_seq`, `timer_btw_sq`, `phase`, `time_phase`, blink state variables)

### `basic_routines.h`
Low‑level helpers used by all sequences:
- **Crosswalk blinking**
  - `INIT_CROSSWALK()`
  - `BLINK_CROSSWALK(pin)` toggles the crosswalk output every `CROSSWALK_DELAY`
- **Traffic lights**
  - `GREEN_LIGHT(lightPins)`, `YELLOW_LIGHT(lightPins)`, `RED_LIGHT(lightPins)`
- **Pedestrian lights**
  - `GREEN_LIGHT_PED(...)`, `RED_LIGHT_PED(...)` (special handling for the 3‑wire pedestrian hardware logic)
  - `GREEN_LIGHT_PED_O(pedPins)`, `RED_LIGHT_PED_O(pedPins)` (simple 2‑wire output logic)
- **Generic blinking**
  - `BLINK_LIGHT_2PHASE(wire, lightPins, onMs, offMs)`
- `RESET_SEQ()` resets the phase/blink state so a new sequence starts consistently

> Note: some routines deliberately change pin modes to emulate **high‑impedance** states (setting a channel to `INPUT`) when required by the hardware wiring logic.

### `sequences.h`
All “scenario” functions `SEQ_*`:
- Sequences implement the intersection logic using:
  - **2‑phase** state machines (`phase = (phase + 1) % 2`)
  - **3‑phase** state machines (`phase = (phase + 1) % 3`)
- Phase switching is done with:
  - `if (now - time_phase >= INTERVAL_MULTEPLEXING) { ... }`
- Some sequences use `BLINK_LIGHT_2PHASE()` to create a **blinking green** or **blinking yellow** behavior.

---

## Pin mapping (Arduino Nano)

The pin assignment is defined in `const.h`. Summary:

- **Crosswalk output**
  - `D2` → `CROSSWALK_IO_E1_E2`

- **Traffic lights**
  - A: `D3` (G), `D4` (Y), `D5` (R)
  - B: `D6` (G), `D7` (Y), `D8` (R)
  - C: `D9` (G), `D10` (Y), `D11` (R)
  - D: `A0` (G), `A1` (Y), `A2` (R)

- **Pedestrian lights**
  - A3/A4: `A4` (G), `A3` (R)
  - B3/B4: `D12` (G), `A5` (R)

---

## Timing model

Main durations (defined in `const.h`):
- `TIME_SEQ` — duration of a “normal” sequence (type `_1`)
- `TIME_TO_BLINK` — duration of a “blink” sequence (type `_2`)
- `TIME_BTW_SEQ` — duration of a “transition” sequence (type `_3`)
- `TIME_TO_BLINK_YELLOW` — duration of `SEQ_7` (blinking yellow emergency mode)
- `INTERVAL_MULTEPLEXING` — very short interval used to alternate internal phases quickly

Blink periods:
- `BLINK_GREEN_ON_MS` / `BLINK_GREEN_OFF_MS`
- `BLINK_YELLOW_ON_MS` / `BLINK_YELLOW_OFF_MS`
- `CROSSWALK_DELAY`

---

## Sequence flow (state machine)

`V2.ino` runs sequences in this order:

1.  `SEQ_1_1` → normal state (2 phases)
2.  `SEQ_1_2` → includes blinking (2 phases)
3.  `SEQ_1_3` → transition (3 phases)
4.  `SEQ_2_1`
5.  `SEQ_2_2`
6.  `SEQ_2_3`
7.  `SEQ_3_1`
8.  `SEQ_3_2`
9.  `SEQ_3_3`
10. `SEQ_4_1`
11. `SEQ_4_2`
12. `SEQ_4_3`
13. `SEQ_5_1`
14. `SEQ_5_2`
15. `SEQ_5_3`
16. `SEQ_6_1`
17. `SEQ_7` → all traffic lights blinking yellow, then loops back to `seq = 1`

Each `case` runs the sequence function and checks if the time budget for that sequence has elapsed. When it is time to move on:
- `seq` is incremented (or reset to 1 after `SEQ_7`)
- `timer_btw_sq` is reset to `millis()`
- On the next loop iteration, `RESET_SEQ()` is triggered because `seq != last_seq`

---

## How the phases work (2‑phase and 3‑phase)

A sequence typically looks like this:
1. Check if enough time passed to advance `phase`
2. Apply outputs according to the current `phase` with a `switch(phase)`
3. Optionally keep some outputs always active (“always on” section)

This allows you to create complex behaviors (including multiplexing/high‑impedance patterns) while keeping the main loop responsive.

---

## How to customize

- **Change durations**: edit constants in `const.h`
- **Change behaviors**: edit the `SEQ_*` functions in `sequences.h`
- **Add a new scenario**:
  1. Create a new `SEQ_X_Y()` in `sequences.h`
  2. Add a new `case` in `V2.ino` and decide which duration constant to use
  3. Ensure `RESET_SEQ()` runs when switching into your new sequence (already handled via `seq != last_seq` logic)

---

## Quick troubleshooting

- If a new sequence starts in the “wrong phase”, make sure you are resetting the state on sequence change.
  - This project already does it via `RESET_SEQ()` when `seq` changes.
- If a light does not behave as expected, verify:
  - pin mapping in `const.h`
  - the correct light array (A/B/C/D) is used in each sequence
  - whether a routine switches the pin to `INPUT` (high‑impedance) on purpose for your hardware

---

## Wire-by-wire sequence recap table (G/Y/R)

Legend for **traffic lights** (A/B/C/D):
- `1` = pin driven **HIGH** (OUTPUT)
- `0` = pin driven **LOW** (OUTPUT)
- `Z` = **high‑impedance** (pin set to `INPUT`, pullup disabled)
- `B` = **blinking** on that color wire (driven HIGH/LOW according to the blink timer)
- `—` = **not updated** in that phase (keeps the previous state)

Legend for **pedestrian outputs** (`PEDESTRIANS_A3_A4`, `PEDESTRIANS_B3_B4`):
- `G:1 R:0` = pedestrian green ON, red OFF
- `G:0 R:1` = pedestrian red ON, green OFF
- `—` = not set in that sequence

> Notes  
- In **2‑phase sequences**: **Phase 0** = **pedestrian-style driving on the traffic-light groups** (calls to `GREEN_LIGHT_PED(...)` / `RED_LIGHT_PED(...)`), **Phase 1** = **normal traffic-light driving** (calls to `GREEN_LIGHT(...)` / `RED_LIGHT(...)` / `YELLOW_LIGHT(...)`).
- In **3‑phase sequences**: **Phase 0** = **pedestrian-style driving on the traffic-light groups**, then **Phase 1 → Phase 2** implement the **traffic transition** (typically red / all-stop → yellow clearance), using normal traffic-light routines.
> 1) Some sequences drive “pedestrian logic” on the **traffic-light 3-wire groups** using `GREEN_LIGHT_PED(...)` / `RED_LIGHT_PED(...)` (these set `Y` to `Z`).  
> 2) `BLINK_LIGHT_2PHASE(YELLOW_WIRE, ...)` makes `Y` blink while forcing `R=0` and `G=Z`.  
> 3) The table is extracted directly from the sequence functions in `sequences.h`.


| SEQ     |   Phase | TRAFFIC_LIGHT_A   | TRAFFIC_LIGHT_B   | TRAFFIC_LIGHT_C   | TRAFFIC_LIGHT_D   | PEDESTRIANS_A3_A4   | PEDESTRIANS_B3_B4   |
|:--------|--------:|:------------------|:------------------|:------------------|:------------------|:--------------------|:--------------------|
| SEQ_1_1 |       0 | G:1 Y:Z R:0       | G:0 Y:Z R:1       | G:1 Y:Z R:0       | G:0 Y:Z R:1       | G:0 R:1             | G:1 R:0             |
| SEQ_1_1 |       1 | G:Z Y:0 R:1       | G:1 Y:0 R:Z       | G:Z Y:0 R:1       | G:Z Y:0 R:1       | G:0 R:1             | G:1 R:0             |
| SEQ_1_2 |       0 | G:0 Y:Z R:1       | G:0 Y:Z R:1       | G:0 Y:Z R:1       | G:0 Y:Z R:1       | —                   | —                   |
| SEQ_1_2 |       1 | G:Z Y:0 R:1       | G:B Y:0 R:Z       | G:Z Y:0 R:1       | G:Z Y:0 R:1       | —                   | —                   |
| SEQ_1_3 |       0 | G:0 Y:Z R:1       | G:0 Y:Z R:1       | G:0 Y:Z R:1       | G:0 Y:Z R:1       | —                   | —                   |
| SEQ_1_3 |       1 | G:Z Y:0 R:1       | —                 | G:Z Y:0 R:1       | G:Z Y:0 R:1       | —                   | —                   |
| SEQ_1_3 |       2 | G:Z Y:1 R:0       | G:Z Y:1 R:0       | G:Z Y:1 R:0       | —                 | —                   | —                   |
| SEQ_2_1 |       0 | G:0 Y:Z R:1       | G:1 Y:Z R:0       | G:0 Y:Z R:1       | G:0 Y:Z R:1       | G:0 R:1             | G:0 R:1             |
| SEQ_2_1 |       1 | G:1 Y:0 R:Z       | G:Z Y:0 R:1       | G:1 Y:0 R:Z       | G:Z Y:0 R:1       | G:0 R:1             | G:0 R:1             |
| SEQ_2_2 |       0 | G:0 Y:Z R:1       | G:1 Y:Z R:0       | G:0 Y:Z R:1       | G:0 Y:Z R:1       | —                   | —                   |
| SEQ_2_2 |       1 | G:B Y:0 R:Z       | G:Z Y:0 R:1       | G:1 Y:0 R:Z       | G:Z Y:0 R:1       | —                   | —                   |
| SEQ_2_3 |       0 | G:0 Y:Z R:1       | G:1 Y:Z R:0       | G:0 Y:Z R:1       | G:0 Y:Z R:1       | —                   | —                   |
| SEQ_2_3 |       1 | —                 | G:Z Y:0 R:1       | G:1 Y:0 R:Z       | G:Z Y:0 R:1       | —                   | —                   |
| SEQ_2_3 |       2 | G:Z Y:1 R:0       | —                 | —                 | G:Z Y:1 R:0       | —                   | —                   |
| SEQ_3_1 |       0 | G:1 Y:Z R:0       | G:1 Y:Z R:0       | G:0 Y:Z R:1       | G:1 Y:Z R:0       | —                   | —                   |
| SEQ_3_1 |       1 | G:Z Y:0 R:1       | G:Z Y:0 R:1       | G:1 Y:0 R:Z       | G:1 Y:0 R:Z       | —                   | —                   |
| SEQ_3_2 |       0 | G:1 Y:Z R:0       | G:1 Y:Z R:0       | G:0 Y:Z R:1       | G:1 Y:Z R:0       | —                   | —                   |
| SEQ_3_2 |       1 | G:Z Y:0 R:1       | G:Z Y:0 R:1       | G:B Y:0 R:Z       | G:1 Y:0 R:Z       | —                   | —                   |
| SEQ_3_3 |       0 | G:1 Y:Z R:0       | G:1 Y:Z R:0       | G:0 Y:Z R:1       | G:1 Y:Z R:0       | —                   | —                   |
| SEQ_3_3 |       1 | G:Z Y:0 R:1       | G:Z Y:0 R:1       | —                 | G:1 Y:0 R:Z       | —                   | —                   |
| SEQ_3_3 |       2 | —                 | —                 | G:Z Y:1 R:0       | —                 | —                   | —                   |
| SEQ_4_1 |       0 | G:1 Y:Z R:0       | G:1 Y:Z R:0       | G:0 Y:Z R:1       | G:1 Y:Z R:0       | G:1 R:0             | G:0 R:1             |
| SEQ_4_1 |       1 | G:Z Y:0 R:1       | G:Z Y:0 R:1       | G:Z Y:0 R:1       | G:1 Y:0 R:Z       | G:1 R:0             | G:0 R:1             |
| SEQ_4_2 |       0 | G:1 Y:Z R:0       | G:1 Y:Z R:0       | G:0 Y:Z R:1       | G:1 Y:Z R:0       | —                   | —                   |
| SEQ_4_2 |       1 | G:Z Y:0 R:1       | G:Z Y:0 R:1       | G:Z Y:0 R:1       | G:B Y:0 R:Z       | —                   | —                   |
| SEQ_4_3 |       0 | G:1 Y:Z R:0       | G:1 Y:Z R:0       | G:0 Y:Z R:1       | G:1 Y:Z R:0       | —                   | —                   |
| SEQ_4_3 |       1 | G:Z Y:0 R:1       | G:Z Y:0 R:1       | G:Z Y:0 R:1       | —                 | —                   | —                   |
| SEQ_4_3 |       2 | —                 | —                 | G:Z Y:1 R:0       | G:Z Y:1 R:0       | —                   | —                   |
| SEQ_5_1 |       0 | G:1 Y:Z R:0       | G:1 Y:Z R:0       | G:0 Y:Z R:1       | G:1 Y:Z R:0       | G:1 R:0             | G:1 R:0             |
| SEQ_5_1 |       1 | G:Z Y:0 R:1       | G:Z Y:0 R:1       | G:1 Y:0 R:Z       | G:Z Y:0 R:1       | G:1 R:0             | G:1 R:0             |
| SEQ_5_2 |       0 | G:0 Y:Z R:1       | G:1 Y:Z R:0       | G:0 Y:Z R:1       | G:0 Y:Z R:1       | —                   | —                   |
| SEQ_5_2 |       1 | G:Z Y:0 R:1       | G:Z Y:0 R:1       | G:B Y:0 R:Z       | G:Z Y:0 R:1       | —                   | —                   |
| SEQ_5_3 |       0 | G:0 Y:Z R:1       | G:1 Y:Z R:0       | G:0 Y:Z R:1       | G:0 Y:Z R:1       | —                   | —                   |
| SEQ_5_3 |       1 | G:Z Y:0 R:1       | G:Z Y:0 R:1       | —                 | G:Z Y:0 R:1       | —                   | —                   |
| SEQ_5_3 |       2 | G:Z Y:1 R:0       | —                 | G:Z Y:1 R:0       | —                 | —                   | —                   |
| SEQ_6_1 |       0 | G:0 Y:Z R:1       | G:1 Y:Z R:0       | G:1 Y:Z R:0       | G:0 Y:Z R:1       | G:1 R:0             | G:0 R:1             |
| SEQ_6_1 |       1 | G:1 Y:0 R:Z       | G:Z Y:0 R:1       | G:Z Y:0 R:1       | G:Z Y:0 R:1       | G:1 R:0             | G:0 R:1             |
| SEQ_7   |       0 | G:Z Y:B R:0       | G:Z Y:B R:0       | G:Z Y:B R:0       | G:Z Y:B R:0       | —                   | —                   |
