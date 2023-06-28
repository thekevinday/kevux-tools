/**
 * Kevux Tools - Remove
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _kt_remove_common_h
#define _kt_remove_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Resize a date array.
 *
 * @param length
 *   The new size to use.
 * @param ranges
 *   The Date Comparison array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_kt_remove_dates_resize_
  extern f_status_t kt_remove_dates_resize(const f_number_unsigned_t length, kt_remove_dates_t * const dates);
#endif // _di_kt_remove_dates_resize_

/**
 * Resize a mode array.
 *
 * @param length
 *   The new size to use.
 * @param ranges
 *   The Date Comparison array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_kt_remove_modes_resize_
  extern f_status_t kt_remove_modes_resize(const f_number_unsigned_t length, kt_remove_modes_t * const modes);
#endif // _di_kt_remove_modes_resize_

/**
 * Perform the standard program setting load process.
 *
 * This prints error messages as appropriate.
 *
 * If either main or setting is NULL, then this immediately returns without doing anything.
 *
 * @param arguments
 *   The parameters passed to the process (often referred to as command line arguments).
 * @param main
 *   The main program and settings data.
 *
 *   The setting.flag has kt_remove_flag_option_used_e forcibly cleared on the start of this function.
 *
 *   This alters setting.status:
 *     F_none on success.
 *     F_data_not on success but nothing was provided to operate with.
 *
 *     F_parameter (with error bit) on parameter error.
 *
 *     Errors (with error bit) from: f_console_parameter_process().
 *     Errors (with error bit) from: f_file_stream_open().
 *     Errors (with error bit) from: f_string_dynamics_resize().
 *
 * @see f_console_parameter_process()
 * @see f_file_stream_open()
 * @see f_string_dynamics_resize()
 */
#ifndef _di_kt_remove_setting_load_
  extern void kt_remove_setting_load(const f_console_arguments_t arguments, kt_remove_main_t * const main);
#endif // _di_kt_remove_setting_load_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_remove_common_h
