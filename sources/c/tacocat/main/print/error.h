/**
 * Kevux Tools - TacocaT
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print error functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _kt_tacocat_print_error_h
#define _kt_tacocat_print_error_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print generic error message regarding a function failing in some way.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_print()
 */
#ifndef _di_kt_tacocat_print_error_
  extern f_status_t kt_tacocat_print_error(fl_print_t * const print, const f_string_t function);
#endif // _di_kt_tacocat_print_error_

/**
 * Print file related error or warning messages.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param name
 *   The name of the file or directory.
 * @param operation
 *   The operation that fails, such as 'create' or 'access'.
 * @param type
 *   A valid file type code from the fll_error_file_type enum.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_kt_tacocat_print_error_file_
  extern f_status_t kt_tacocat_print_error_file(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_kt_tacocat_print_error_file_

/**
 * Print error message for when an unknown value for the resolve parameter is provided.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param unknown
 *   The string representing the unknown value passed to the resolve parameter.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_kt_tacocat_print_error_parameter_value_resolve_unknown_
  extern f_status_t kt_tacocat_print_error_parameter_value_resolve_unknown(fl_print_t * const print, const f_string_dynamic_t unknown);
#endif // _di_kt_tacocat_print_error_parameter_value_resolve_unknown_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_print_error_h
