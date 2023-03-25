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
 *
 *     F_parameter (with error bit) if main is NULL or setting is NULL.
 * @param path
 *   The path to the file to operate on.
 */
#ifndef _di_kt_remove_operate_file_
  extern void kt_remove_operate_file(kt_remove_main_t * const main, const f_string_static_t path);
#endif // _di_kt_remove_operate_file_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_remove_operate_h
