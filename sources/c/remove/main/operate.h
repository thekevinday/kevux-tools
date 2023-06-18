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
 *     F_none on success.
 *     F_data_not on success but file is an empty string.
 * @param path
 *   The path to the file to operate on.
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
 *     Errors (with error bit) from: f_file_remove().
 * @param path
 *   The path to the file to operate on.
 * @param flag
 *   The operate file specific flags from kt_remove_flag_file_operate_*_e.
 */
#ifndef _di_kt_remove_operate_file_directory_
  extern void kt_remove_operate_file_directory(kt_remove_main_t * const main, const f_string_static_t path, const uint8_t flag);
#endif // _di_kt_remove_operate_file_directory_

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
 *     Errors (with error bit) from: f_file_remove().
 * @param path
 *   The path to the file to operate on.
 * @param flag
 *   The operate file specific flags from kt_remove_flag_file_operate_*_e.
 *
 * @see f_file_remove()
 */
#ifndef _di_kt_remove_operate_file_normal_
  extern void kt_remove_operate_file_normal(kt_remove_main_t * const main, const f_string_static_t path, const uint8_t flag);
#endif // _di_kt_remove_operate_file_normal_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_remove_operate_h
