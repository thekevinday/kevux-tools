/**
 * Kevux Tools - TacocaT
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _kt_tacocat_common_h
#define _kt_tacocat_common_h

#ifdef __cplusplus
extern "C" {
#endif

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
 *   This alters setting.status:
 *     F_none on success.
 *
 *     F_parameter (with error bit) on parameter error.
 *
 *     Errors (with error bit) from: f_console_parameter_process().
 *     Errors (with error bit) from: f_string_dynamic_append_nulless().
 *     Errors (with error bit) from: fll_program_parameter_process_context().
 *     Errors (with error bit) from: fll_program_parameter_process_verbosity().
 *
 *     Errors (with error bit) from: kt_tacocat_setting_load_send_receive().
 *
 * @see f_console_parameter_process()
 * @see f_string_dynamic_append_nulless()
 * @see fll_program_parameter_process_context()
 * @see fll_program_parameter_process_verbosity()
 *
 * @see kt_tacocat_setting_load_send_receive()
 */
#ifndef _di_kt_tacocat_setting_load_
  extern void kt_tacocat_setting_load(const f_console_arguments_t arguments, kt_tacocat_main_t * const main);
#endif // _di_kt_tacocat_setting_load_

/**
 * Perform the standard program setting load process for the send and receive parameters.
 *
 * This will perform any DNS resolutions as necessary and open any appropriate files.
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
 *   This must be of type kt_tacocat_main_t.
 *
 *   This alters setting.status:
 *     F_none on success.
 *
 *     F_parameter (with error bit) on parameter error.
 *
 *     Errors (with error bit) from: f_file_exists().
 *     Errors (with error bit) from: f_file_open().
 *     Errors (with error bit) from: f_files_increase_by().
 *     Errors (with error bit) from: f_network_from_ip_name().
 *     Errors (with error bit) from: f_string_dynamic_append_nulless().
 *     Errors (with error bit) from: f_string_dynamic_increase_by().
 *     Errors (with error bit) from: f_string_dynamics_increase_by().
 *
 *     Errors (with error bit) from: main.callback.setting_load_send_receive().
 *
 * @see f_file_exists()
 * @see f_file_open()
 * @see f_files_increase_by()
 * @see f_network_from_ip_name()
 * @see f_string_dynamic_append_nulless()
 * @see f_string_dynamic_increase_by()
 * @see f_string_dynamics_increase_by()
 */
#ifndef _di_kt_tacocat_setting_load_send_receive_
  extern void kt_tacocat_setting_load_send_receive(const f_console_arguments_t arguments, void * const main);
#endif // _di_kt_tacocat_setting_load_send_receive_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_common_h
