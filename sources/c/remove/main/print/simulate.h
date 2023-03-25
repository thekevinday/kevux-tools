/**
 * Kevux Tools - Remove
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print simulate functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _kt_remove_print_simulate_h
#define _kt_remove_print_simulate_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Simulate operate.
 *
 * This does nothing if the simulate flag (kt_remove_flag_simulate_e) is not set.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This locks, uses, and unlocks the file stream.
 *
 *   This does not alter print.custom.setting.state.status.
 */
#ifndef _di_kt_remove_print_simulate_operate_
  extern void kt_remove_print_simulate_operate(fl_print_t * const print);
#endif // _di_kt_remove_print_simulate_operate_

/**
 * Simulate operate on a single file.
 *
 * This does nothing if the simulate flag (kt_remove_flag_simulate_e) is not set.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This locks, uses, and unlocks the file stream.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param path
 *   The path to the file to operate on.
 */
#ifndef _di_kt_remove_print_simulate_operate_file_
  extern void kt_remove_print_simulate_operate_file(fl_print_t * const print, const f_string_static_t path);
#endif // _di_kt_remove_print_simulate_operate_file_

/**
 * Simulate operate on a single file, processing file existence.
 *
 * This does nothing if the simulate flag (kt_remove_flag_simulate_e) is not set.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This locks, uses, and unlocks the file stream.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param path
 *   The path to the file to operate on.
 */
#ifndef _di_kt_remove_print_simulate_operate_file_exists_
  extern void kt_remove_print_simulate_operate_file_exists(fl_print_t * const print, const f_string_static_t path);
#endif // _di_kt_remove_print_simulate_operate_file_exists_

/**
 * Simulate operate on a single file, processing file statistics.
 *
 * This does nothing if the simulate flag (kt_remove_flag_simulate_e) is not set.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This locks, uses, and unlocks the file stream.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param statistics
 *   The file statistics.
 */
#ifndef _di_kt_remove_print_simulate_operate_file_stat_
  extern void kt_remove_print_simulate_operate_file_stat(fl_print_t * const print, struct stat statistics);
#endif // _di_kt_remove_print_simulate_operate_file_stat_

/**
 * Simulate operate on a single file, designate that file is to be removed or not removed (forcibly or otherwise).
 *
 * This does nothing if the simulate flag (kt_remove_flag_simulate_e) is not set.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This locks, uses, and unlocks the file stream.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param yes
 *   If TRUE, then this is to be removed.
 *   If FALSE, then this is not to be removed.
 * @param force
 *   If TRUE, then this prints a message about being forced.
 *   If FALSE, then this prints a message about being removed.
 */
#ifndef _di_kt_remove_print_simulate_operate_remove_
  extern void kt_remove_print_simulate_operate_remove(fl_print_t * const print, const bool yes, const bool force);
#endif // _di_kt_remove_print_simulate_operate_remove_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_remove_print_simulate_h
