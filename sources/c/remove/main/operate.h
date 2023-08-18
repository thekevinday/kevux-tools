/**
 * Kevux Tools - Remove
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _kt_remove_operate_h
#define _kt_remove_operate_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Operate on a single file.
 *
 * @param main
 *   The main program and settings data.
 *
 *   This alters main.setting.state.status:
 *     F_okay on success.
 *     F_data_not on success but file is an empty string.
 *
 *     Errors (with error bit) from: f_string_dynamic_append().
 *
 *     Errors (with error bit) from: kt_remove_operate_file_directory().
 *     Errors (with error bit) from: kt_remove_operate_file_normal().
 *     Errors (with error bit) from: kt_remove_operate_file_simulate().
 * @param path
 *   The path to the file to operate on.
 *
 *   This should always be TRUE when calling from the top level.
 *   This should always be FALSE if calling from within a fl_directory_do() callback.
 *   This is because fl_directory_do() handles directory traversal and processing.
 *
 * @see f_string_dynamic_append()
 *
 * @see kt_remove_operate_file_directory()
 * @see kt_remove_operate_file_normal()
 * @see kt_remove_operate_file_simulate()
 */
#ifndef _di_kt_remove_operate_file_
  extern void kt_remove_operate_file(kt_remove_main_t * const main, const f_string_static_t path);
#endif // _di_kt_remove_operate_file_

/**
 * Perform actual file removal for directory files.
 *
 * @param main
 *   The main program and settings data.
 *
 *   This alters main.setting.state.status:
 *     F_no on success but file is not to be removed.
 *     F_yes on success and file is removed.
 *
 *     F_recurse (with error bit) on max recursion depth reached.
 *
 *     Errors (with error bit) from: f_file_remove().
 * @param path
 *   The path to the file to operate on.
 * @param flag
 *   The operate file specific flags from kt_remove_flag_file_operate_*_e.
 *
 * @see f_file_remove()
 */
#ifndef _di_kt_remove_operate_file_directory_
  extern void kt_remove_operate_file_directory(kt_remove_main_t * const main, const f_string_static_t path, const uint8_t flag);
#endif // _di_kt_remove_operate_file_directory_

/**
 * Perform directory recurse file operation action.
 *
 * @param recurse
 *   Must not be NULL.
 *   Must be of type f_directory_recurse_do_t.
 * @param name
 *   The name of the file or directory the action is being performed on.
 *   Does not have the parent directory path.
 *   May be empty at the top level.
 * @param flag
 *   A flag representing the particular action being performed.
 *
 * @see f_directory_remove()
 * @see fl_directory_do()
 */
#ifndef _di_kt_remove_operate_file_directory_recurse_action_
  extern void kt_remove_operate_file_directory_recurse_action(void * const recurse, const f_string_static_t name, const uint16_t flag);
#endif // _di_kt_remove_operate_file_directory_recurse_action_

/**
 * Handle errors while performing directory recurse file operation action.
 *
 * @param recurse
 *   Must not be NULL.
 *   Must be of type f_directory_recurse_do_t.
 * @param name
 *   The name of the file or directory the action is being performed on.
 *   Does not have the parent directory path.
 *   May be empty at the top level.
 * @param flag
 *   A flag representing the particular action being performed.
 *
 * @see fl_directory_do()
 */
#ifndef _di_kt_remove_operate_file_directory_recurse_handle_
  extern void kt_remove_operate_file_directory_recurse_handle(void * const recurse, const f_string_static_t name, const uint16_t flag);
#endif // _di_kt_remove_operate_file_directory_recurse_handle_

/**
 * Perform actual file removal for non-directory files.
 *
 * @param main
 *   The main program and settings data.
 *
 *   This alters main.setting.state.status:
 *     F_no on success but file is not to be removed.
 *     F_yes on success and file is removed.
 *
 *     Errors (with error bit) from: f_file_link_read().
 *     Errors (with error bit) from: f_file_remove().
 * @param path
 *   The path to the file to operate on.
 * @param flag
 *   The operate file specific flags from kt_remove_flag_file_operate_*_e.
 *
 * @see f_file_link_read()
 * @see f_file_remove()
 */
#ifndef _di_kt_remove_operate_file_normal_
  extern void kt_remove_operate_file_normal(kt_remove_main_t * const main, const f_string_static_t path, const uint8_t flag);
#endif // _di_kt_remove_operate_file_normal_

/**
 * Perform simulation of the file operation.
 *
 * The simulation process is also intended to be used to determine what to do with the actual file.
 * A flag is populated based on the results of the simulation analysis.
 *
 * @param main
 *   The main program and settings data.
 *
 *   This alters main.setting.state.status:
 *     F_okay on success.
 *     F_data_not on success but file is an empty string.
 *
 *     Errors (with error bit) from: f_file_link_read().
 *     Errors (with error bit) from: f_file_remove().
 * @param path
 *   The path to the file to operate on.
 *
 * @return
 *   The flags determined by the simulation.
 *
 * @see f_file_link_read()
 * @see f_file_remove()
 */
#ifndef _di_kt_remove_operate_file_simulate_
  extern uint8_t kt_remove_operate_file_simulate(kt_remove_main_t * const main, const f_string_static_t path);
#endif // _di_kt_remove_operate_file_simulate_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_remove_operate_h
