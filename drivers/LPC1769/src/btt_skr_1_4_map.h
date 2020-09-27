/*
  btt_skr_1.4_map.h - driver code for LPC176x processor, pin mappings compatible with BIGTREETECH SKR 1.4 board


  Part of GrblHAL

  Copyright (c) 2019-2020 Terje Io, denkijin

  Mappings experimental

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#define BOARD_NAME "BTT SKR 1.4"
//
// Steppers
//  commented defines are imported from Marlin for pins
//  Quite unsure how the defined variables in GrblHAL relate to
//  those as defined in Marlin
//  maybe OP has insight?

// Define step pulse output pins.

// #define X_STEP_PIN                         P2_02 port 2 pin 2???
// #define X_DIR_PIN                          P2_06
// #define X_ENABLE_PIN                       P2_01 <-- move to ena/dis
// grammar below imported from ramps_1.6_map.h
// #define X_STEP_PIN       P2.02
#define X_STEP_PN           2
#define X_STEP_PORT         port(X_STEP_PN) //what
#define X_STEP_PIN          2
#define X_STEP_BIT          (1<<X_STEP_PIN)


// #define Y_STEP_PIN                         P0_19
// #define Y_DIR_PIN                          P0_20
// #define Y_ENABLE_PIN                       P2_08 <<--move to ena/dis
// imported from ramps_1.6_map.h
// #define Y_STEP_PIN       P0.19
#define Y_STEP_PN           0
#define Y_STEP_PORT         port(Y_STEP_PN)
#define Y_STEP_PIN          19
#define Y_STEP_BIT          (1<<Y_STEP_PIN)

// #define Z_ENABLE_PIN                       P0_21
// #define Z_DIR_PIN
// #define Z_ENABLE_PIN
// imported from ramps_1.6_map.h
// #define Z_STEP_PIN       P0.22
#define Z_STEP_PN           0
#define Z_STEP_PORT         port(Z_STEP_PN)
#define Z_STEP_PIN          22
#define Z_STEP_BIT          (1<<Z_STEP_PIN)

// E0/E1 = A_AXIS/B_AXIS
// #define E0_STEP_PIN                        P2_13
// #define E0_DIR_PIN                         P0_11
// #define EO_ENABLE_PIN
// #define E0_STEP_PIN      P2.13
#ifdef A_AXIS
#define A_STEP_PN           2
#define A_STEP_PORT         port(A_STEP_PN)
#define A_STEP_PIN          13
#define A_STEP_BIT          (1<<A_STEP_PIN)
#endif

// #define E1_STEP_PIN                        P1_15
// #define E1_DIR_PIN                         P1_14
// #define E1_ENABLE_PIN                      P1_16
// #define E1_STEP_PIN      P1.15
#ifdef B_AXIS
#define B_STEP_PN           1
#define B_STEP_PORT         port(B_STEP_PN)
#define B_STEP_PIN          15
#define B_STEP_BIT          (1<<B_STEP_PIN)
#endif

// from ramps_1.6
#define STEP_OUTMODE GPIO_BITBAND

// from ramps_1.6
// Define step direction output pins.
// #define X_DIR_PIN        P2.06
#define X_DIRECTION_PN      2
#define X_DIRECTION_PORT    port(X_DIRECTION_PN)
#define X_DIRECTION_PIN     6
#define X_DIRECTION_BIT     (1<<X_DIRECTION_PIN)

// ##define Y_DIR_PIN       P0.20
#define Y_DIRECTION_PN      0
#define Y_DIRECTION_PORT    port(Y_DIRECTION_PN)
#define Y_DIRECTION_PIN     20  // Due Analog Pin 7
#define Y_DIRECTION_BIT     (1<<Y_DIRECTION_PIN)

//  #define Z_DIR_PIN       P2.11
#define Z_DIRECTION_PN      2
#define Z_DIRECTION_PORT    port(Z_DIRECTION_PN)
#define Z_DIRECTION_PIN     11  // Due Digital Pin 48
#define Z_DIRECTION_BIT     (1<<Z_STEP_PIN)

// #define E0_DIR_PIN       P0.11
#ifdef A_AXIS
#define A_DIRECTION_PN      0
#define A_DIRECTION_PORT    port(A_DIRECTION_PN)
#define A_DIRECTION_PIN     11   // Due Digital Pin 28
#define A_DIRECTION_BIT     (1<<A_DIRECTION_PIN)
#endif

// #define E1_DIR_PIN       P1.14
#ifdef B_AXIS
#define B_DIRECTION_PN      1
#define B_DIRECTION_PORT    port(B_DIRECTION_PN)
#define B_DIRECTION_PIN     14  // Due Digital Pin 34
#define B_DIRECTION_BIT     (1<<B_DIRECTION_PIN)
#endif

#define DIRECTION_OUTMODE GPIO_BITBAND

// from ramps_1.6
// Define stepper driver enable/disable output pin(s).
// here I thought to use X_STOP_PIN but the correct choice is X_ENABLE_PIN
//  #define X_ENABLE_PIN    P2.01
#define X_DISABLE_PN        2
#define X_DISABLE_PORT      port(X_DISABLE_PN)
#define X_DISABLE_PIN       1
#define X_DISABLE_BIT       (1<<X_DISABLE_PIN)

// #define Y_ENABLE_PIN     P2.08
#define Y_DISABLE_PN        2
#define Y_DISABLE_PORT      port(Y_DISABLE_PN)
#define Y_DISABLE_PIN       8
#define Y_DISABLE_BIT       (1<<Y_DISABLE_PIN)

// #define Z_ENABLE_PIN     P0.21
#define Z_DISABLE_PN        0
#define Z_DISABLE_PORT      port(Z_DISABLE_PN)
#define Z_DISABLE_PIN       21
#define Z_DISABLE_BIT       (1<<Z_DISABLE_PIN)

// #define E0_ENABLE_PIN    P2.12
#ifdef A_AXIS
#define A_DISABLE_PN        2
#define A_DISABLE_PORT      port(A_DISABLE_PN)
#define A_DISABLE_PIN       12
#define A_DISABLE_BIT       (1<<A_DISABLE_PIN)
#endif

// #define E1_ENABLE_PIN    P1.16
#ifdef B_AXIS
#define B_DISABLE_PN        1
#define B_DISABLE_PORT      port(B_DISABLE_PN)
#define B_DISABLE_PIN       16
#define B_DISABLE_BIT       (1<<B_DISABLE_PIN)
#endif

#define DISABLE_OUTMODE GPIO_BITBAND

// Define homing/hard limit switch input pins.
// here, we need config for with and without trinamic
// using
// NOTE: Port 1 is not interrupt capable!
//  #define X_MIN_PIN       P1.29
#define X_LIMIT_PN          1
#define X_LIMIT_PORT        port(X_LIMIT_PN)
#define X_LIMIT_PIN         29
#define X_LIMIT_BIT         (1<<X_LIMIT_PIN)

// #define Y_MIN_PIN        P1.28
#define Y_LIMIT_PN          1
#define Y_LIMIT_PORT        port(Y_LIMIT_PN)
#define Y_LIMIT_PIN         28
#define Y_LIMIT_BIT         (1<<Y_LIMIT_PIN)

//  #define Z_MIN_PIN       P0.21
#define Z_LIMIT_PN          0
#define Z_LIMIT_PORT        port(Z_LIMIT_PN)
#define Z_LIMIT_PIN         21
#define Z_LIMIT_BIT         (1<<Z_LIMIT_PIN)

// Define homing/hard limit switch input pins.
// using E0DET, E1DET, PWRDET
// #define E0DET            P1.26
// #define E1DET            P1.25
//  #define PWRDET          P1.0
#define X_LIMIT_PN_MAX      1
#define X_LIMIT_PORT_MAX    port(X_LIMIT_PN_MAX)
#define X_LIMIT_PIN_MAX     26
#define X_LIMIT_BIT_MAX     (1<<X_LIMIT_PIN_MAX)

#define Y_LIMIT_PN_MAX      1
#define Y_LIMIT_PORT_MAX    port(Y_LIMIT_PN_MAX)
#define Y_LIMIT_PIN_MAX     25
#define Y_LIMIT_BIT_MAX     (1<<Y_LIMIT_PIN_MAX)

#define Z_LIMIT_PN_MAX      1
#define Z_LIMIT_PORT_MAX    port(Z_LIMIT_PN_MAX)
#define Z_LIMIT_PIN_MAX     0
#define Z_LIMIT_BIT_MAX     (1<<Z_LIMIT_PIN_MAX)

#define LIMIT_MASK (X_LIMIT_BIT|X_LIMIT_BIT_MAX|Y_LIMIT_BIT|Y_LIMIT_BIT_MAX|Z_LIMIT_BIT|Z_LIMIT_BIT_MAX) // All limit bits (needs to be on same port)
#define LIMIT_INMODE GPIO_BITBAND

// Define probe switch input pin.
// #define PROBE       P0.10
#define PROBE_PN    0
#define PROBE_PORT  port(PROBE_PN)
#define PROBE_PIN   10
#define PROBE_BIT   (1<<PROBE_PIN)

// Define spindle enable and spindle direction output pins.
/*
    here, we must utilise pins dedcated to the heated bed for spindle control
*/
//
// what to use for spindle enable? hotbed enable?
//
// listed as [04] on  ramps.md
// this seems to be on AUX-3 
#define SPINDLE_ENABLE_PN       1
#define SPINDLE_ENABLE_PORT     port(SPINDLE_ENABLE_PN)
#define SPINDLE_ENABLE_PIN      18
#define SPINDLE_ENABLE_BIT      (1<<SPINDLE_ENABLE_PIN)

// listed as [05] on ramps.md
#define SPINDLE_DIRECTION_PN    1
#define SPINDLE_DIRECTION_PORT  port(SPINDLE_DIRECTION_PN)
#define SPINDLE_DIRECTION_PIN   19
#define SPINDLE_DIRECTION_BIT   (1<<SPINDLE_DIRECTION_PIN)

// Start of PWM & Stepper Enabled Spindle

// Define flood and mist coolant enable output pins.
#define COOLANT_FLOOD_PN    0
#define COOLANT_FLOOD_PORT  port(COOLANT_FLOOD_PN)
#define COOLANT_FLOOD_PIN   26
#define COOLANT_FLOOD_BIT   (1<<COOLANT_FLOOD_PIN)

// Define user-control CONTROLs (cycle start, reset, feed hold) input pins.
#define RESET_PORT_PN       0
#define RESET_PORT          port(RESET_PORT_PN)
#define RESET_PIN           27
#define RESET_BIT           (1<<RESET_PIN)

#define FEED_HOLD_PN        0
#define FEED_HOLD_PORT      port(FEED_HOLD_PN)
#define FEED_HOLD_PIN       28
#define FEED_HOLD_BIT       (1<<FEED_HOLD_PIN)

#define CYCLE_START_PN      2
#define CYCLE_START_PORT    port(CYCLE_START_PN)
#define CYCLE_START_PIN     6   // DUE Analog Pin 5
#define CYCLE_START_BIT     (1<<CYCLE_START_PIN)

#define CONTROL_INMODE GPIO_BITBAND

#ifdef SPINDLE_PWM_PIN_2_4
#define SPINDLE_PWM_CHANNEL         PWM1_CH5    // MOSFET3 (P2.4)
#else
#define SPINDLE_PWM_CHANNEL         PWM1_CH6    // BED MOSFET (P2.5)
#endif
#define SPINDLE_PWM_USE_PRIMARY_PIN   false
#define SPINDLE_PWM_USE_SECONDARY_PIN true

#define SD_SPI_PORT 1
#define SD_CS_PN    0
#define SD_CS_PORT  port(SD_CS_PN)
#define SD_CS_PIN   6

/**/

// imported from Marlin
#define TEMP_1_PIN                      P0_23_A0  // A2 (T2) - (69) - TEMP_1_PIN
#define TEMP_BED_PIN                    P0_25_A2  // A0 (T0) - (67) - TEMP_BED_PIN
