/**
 * Kevux Tools - Remove
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _kt_remove_simulate_h
#define _kt_remove_simulate_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Simulate operate.
 *
 * This does nothing if the simulate flag (kt_remove_flag_simulate_e) is not set.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 */
#ifndef _di_kt_remove_simulate_operate_
  extern void kt_remove_simulate_operate(fll_program_data_t * const main, kt_remove_setting_t * const setting);
#endif // _di_kt_remove_simulate_operate_

/**
 * Simulate operate on a single file.
 *
 * This does nothing if the simulate flag (kt_remove_flag_simulate_e) is not set.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param path
 *   The path to the file to operate on.
 */
#ifndef _di_kt_remove_simulate_operate_file_
  extern void kt_remove_simulate_operate_file(fll_program_data_t * const main, kt_remove_setting_t * const setting, const f_string_static_t path);
#endif // _di_kt_remove_simulate_operate_file_

/**
 * Simulate operate on a single file, processing file existence.
 *
 * This does nothing if the simulate flag (kt_remove_flag_simulate_e) is not set.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param path
 *   The path to the file to operate on.
 */
#ifndef _di_kt_remove_simulate_operate_file_exists_
  extern void kt_remove_simulate_operate_file_exists(fll_program_data_t * const main, kt_remove_setting_t * const setting, const f_string_static_t path);
#endif // _di_kt_remove_simulate_operate_file_exists_

/**
 * Simulate operate on a single file, processing file statistics.
 *
 * This does nothing if the simulate flag (kt_remove_flag_simulate_e) is not set.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param statistics
 *   The file statistics.
 */
#ifndef _di_kt_remove_simulate_operate_file_stat_
  extern void kt_remove_simulate_operate_file_stat(fll_program_data_t * const main, kt_remove_setting_t * const setting, struct stat statistics);
#endif // _di_kt_remove_simulate_operate_file_stat_

/**
 * Simulate operate on a single file, designate that file is forcibly to be removed.
 *
 * This does nothing if the simulate flag (kt_remove_flag_simulate_e) is not set.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 */
#ifndef _di_kt_remove_simulate_operate_remove_force_yes_
  extern void kt_remove_simulate_operate_remove_force_yes(fll_program_data_t * const main, kt_remove_setting_t * const setting);
#endif // _di_kt_remove_simulate_operate_remove_force_yes_

/**
 * Simulate operate on a single file, designate that file is not forcibly to be removed.
 *
 * This does nothing if the simulate flag (kt_remove_flag_simulate_e) is not set.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 */
#ifndef _di_kt_remove_simulate_operate_remove_force_no_
  extern void kt_remove_simulate_operate_remove_force_no(fll_program_data_t * const main, kt_remove_setting_t * const setting);
#endif // _di_kt_remove_simulate_operate_remove_force_no_

/**
 * Simulate operate on a single file, designate that file is to be removed.
 *
 * This does nothing if the simulate flag (kt_remove_flag_simulate_e) is not set.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 */
#ifndef _di_kt_remove_simulate_operate_remove_yes_
  extern void kt_remove_simulate_operate_remove_yes(fll_program_data_t * const main, kt_remove_setting_t * const setting);
#endif // _di_kt_remove_simulate_operate_remove_yes_

/**
 * Simulate operate on a single file, designate that file is not to be removed.
 *
 * This does nothing if the simulate flag (kt_remove_flag_simulate_e) is not set.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 */
#ifndef _di_kt_remove_simulate_operate_remove_no_
  extern void kt_remove_simulate_operate_remove_no(fll_program_data_t * const main, kt_remove_setting_t * const setting);
#endif // _di_kt_remove_simulate_operate_remove_no_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_remove_simulate_h
