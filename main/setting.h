#ifndef _SETTING_H_
#define _SETTING_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "define_type.h"

// Axis array index values. Must start with 0 and be continuous.
#define N_AXIS 3 // Number of axes
#define X_AXIS 0 // Axis indexing value.
#define Y_AXIS 1
#define Z_AXIS 2
// #define A_AXIS 3


// Bit field and masking macros
#define bit(n) (1 << n)

// Define settings restore bitflags.
#define SETTINGS_RESTORE_ALL 0xFF // All bitflags
#define SETTINGS_RESTORE_DEFAULTS bit(0)
#define SETTINGS_RESTORE_PARAMETERS bit(1)
#define SETTINGS_RESTORE_STARTUP_LINES bit(2)
#define SETTINGS_RESTORE_BUILD_INFO bit(3)

// Define bit flag masks for the boolean settings in settings.flag.
#define BITFLAG_REPORT_INCHES      bit(0)
// #define BITFLAG_AUTO_START         bit(1) // Obsolete. Don't alter to keep back compatibility.
#define BITFLAG_INVERT_ST_ENABLE   bit(2)
#define BITFLAG_HARD_LIMIT_ENABLE  bit(3)
#define BITFLAG_HOMING_ENABLE      bit(4)
#define BITFLAG_SOFT_LIMIT_ENABLE  bit(5)
#define BITFLAG_INVERT_LIMIT_PINS  bit(6)
#define BITFLAG_INVERT_PROBE_PIN   bit(7)

// Define status reporting boolean enable bit flags in settings.status_report_mask
#define BITFLAG_RT_STATUS_MACHINE_POSITION  bit(0)
#define BITFLAG_RT_STATUS_WORK_POSITION     bit(1)
#define BITFLAG_RT_STATUS_PLANNER_BUFFER    bit(2)
#define BITFLAG_RT_STATUS_SERIAL_RX         bit(3)
#define BITFLAG_RT_STATUS_LIMIT_PINS        bit(4)

// Global persistent settings (Stored from byte)
typedef struct {
  // Axis settings
  float steps_per_mm[N_AXIS];
  float max_rate[N_AXIS];
  float acceleration[N_AXIS];
  float max_travel[N_AXIS];

  // Remaining Grbl settings
  uint8_t pulse_microseconds;
  uint8_t step_invert_mask;
  uint8_t dir_invert_mask;
  uint8_t stepper_idle_lock_time; // If max value 255, steppers do not disable.
  uint8_t status_report_mask; // Mask to indicate desired report data.
  float junction_deviation;
  float arc_tolerance;

  uint8_t flags;  // Contains default boolean settings

  uint8_t homing_dir_mask;
  float homing_feed_rate;
  float homing_seek_rate;
  uint16_t homing_debounce_delay;
  float homing_pulloff;
} settings_t;
extern settings_t settings;

#ifdef __cplusplus
}
#endif

#endif /*_SETTING_H_*/

