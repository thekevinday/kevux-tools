/**
 * Kevux Tools - Remove
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _kt_remove_common_type_h
#define _kt_remove_common_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A processed Date parameter.
 *
 * The start is inclusive and the stop is exclusive just like with f_string_range_t.
 *
 * operation: The comparison operation.
 * type:      The date type.
 *
 * start_year:       The year in which the seconds is relative to (is only processed when
 * start_second:     The entire date value in seconds for the date or the start of a date range.
 * start_nanosecond: The remaining nanosecond not represented in the seconds for the date or the start of a date range.
 * stop_second:      The entire date value in seconds for the stop of a date range (not used for non-range dates).
 * stop_nanosecond:  The remaining nanosecond not represented in the seconds for the stop of a date range (not used for non-range dates).
 */
#ifndef _di_kt_remove_date_t_
  typedef struct {
    uint8_t operation;
    uint8_t type;

    f_number_unsigned_t start_year;
    f_number_unsigned_t start_second;
    f_number_unsigned_t start_nanosecond;

    f_number_unsigned_t stop_year;
    f_number_unsigned_t stop_second;
    f_number_unsigned_t stop_nanosecond;
  } kt_remove_date_t;

  #define kt_remove_date_t_initialize { \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
  }
#endif // _di_kt_remove_date_t_

/**
 * Date parameters.
 *
 * array: An array of data parameters.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_kt_remove_dates_t_
  typedef struct {
    kt_remove_date_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } kt_remove_dates_t;

  #define kt_remove_dates_t_initialize { \
    0, \
    0, \
    0, \
  }

  #define macro_kt_remove_dates_t_clear(dates) \
    dates.array = 0; \
    dates.size = 0; \
    dates.used = 0;
#endif // _di_kt_remove_dates_t_

/**
 * A processed mode parameter.
 *
 * type: The mode type.
 * mode: The right side date value.
 */
#ifndef _di_kt_remove_mode_t_
  typedef struct {
    uint8_t type;
    mode_t mode;
  } kt_remove_mode_t;

  #define kt_remove_mode_t_initialize { \
    0, \
    0, \
  }
#endif // _di_kt_remove_mode_t_

/**
 * Mode parameters.
 *
 * array: An array of mode parameters.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_kt_remove_modes_t_
  typedef struct {
    kt_remove_mode_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } kt_remove_modes_t;

  #define kt_remove_modes_t_initialize { \
    0, \
    0, \
    0, \
  }

  #define macro_kt_remove_modes_t_clear(dates) \
    dates.array = 0; \
    dates.size = 0; \
    dates.used = 0;
#endif // _di_kt_remove_modes_t_

/**
 * The main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * flag: Flags passed to the main function.
 *
 * status_thread: A status used eclusively by the threaded signal handler.
 * state:         The state data used when processing data.
 *
 * program_name:      The short name of the program.
 * program_name_long: The human friendly name of the program.
 *
 * buffer: A string buffer used for caching purposes.
 * files:  An array of file names (full paths to the files) to remove.
 *
 * accessed: An array of last accessed dates used for comparison.
 * changed:  An array of changed on dates used for comparison.
 * updated:  An array of last updated dates used for comparison.
 * modes:    An array of modes used for comparison.
 * groups:   An array of Group IDs (gid_t) represented via an unsigned 32-bit integer.
 * users:    An array of Group IDs (uid_t) represented via an unsigned 32-bit integer.
 *
 * process_help:         Process help (generally printing help).
 * process_normal:       Process normally (data from parameters and files).
 * process_operate_file: Process an individual file, returning F_done to designate handled, and F_none for letting parent continue handling.
 */
#ifndef _di_kt_remove_setting_t_
  typedef struct {
    uint64_t flag;

    f_status_t status_thread;
    f_state_t state;

    f_string_dynamic_t buffer;
    f_string_dynamics_t files;

    kt_remove_dates_t accessed;
    kt_remove_dates_t changed;
    kt_remove_dates_t updated;
    kt_remove_modes_t modes;
    f_uint32s_t groups;
    f_uint32s_t users;

    f_directory_recurse_do_t recurse;

    const f_string_static_t *program_name;
    const f_string_static_t *program_name_long;

    f_status_t (*process_help)(void * const main);
    void (*process_normal)(void * const main);
    void (*process_operate_file)(void * const main, const f_string_static_t path, const struct stat statistics, uint8_t * const flag);
  } kt_remove_setting_t;

  #define kt_remove_setting_t_initialize \
    { \
      kt_remove_main_flag_none_e, \
      F_none, \
      macro_f_state_t_initialize_1(kt_remove_allocation_large_d, kt_remove_allocation_small_d, F_none, 0, 0, &fll_program_standard_signal_handle, 0, 0, 0, 0), \
      f_string_dynamic_t_initialize, \
      f_string_dynamics_t_initialize, \
      kt_remove_dates_t_initialize, \
      kt_remove_dates_t_initialize, \
      kt_remove_dates_t_initialize, \
      kt_remove_modes_t_initialize, \
      f_uint32s_t_initialize, \
      f_uint32s_t_initialize, \
      f_directory_recurse_do_t_initialize, \
      0, \
      0, \
      0, \
      0, \
      0, \
    }
#endif // _di_kt_remove_setting_t_

/**
 * The main program data as a single structure.
 *
 * program: The main program data.
 * setting: The settings data.
 */
#ifndef _di_kt_remove_main_t_
  typedef struct {
    fll_program_data_t program;
    kt_remove_setting_t setting;
  } kt_remove_main_t;

  #define kt_remove_main_t_initialize \
    { \
      fll_program_data_t_initialize, \
      kt_remove_setting_t_initialize, \
    }
#endif // _di_kt_remove_main_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_remove_common_type_h
