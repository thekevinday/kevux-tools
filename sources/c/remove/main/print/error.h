/**
 * Kevux Tools - Remove
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print error functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _kt_remove_print_error_h
#define _kt_remove_print_error_h

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
#ifndef _di_kt_remove_print_error_
  extern f_status_t kt_remove_print_error(fl_print_t * const print, const f_string_t function);
#endif // _di_kt_remove_print_error_

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
#ifndef _di_kt_remove_print_error_file_
  extern f_status_t kt_remove_print_error_file(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_kt_remove_print_error_file_

/**
 * Print message about parameter not have the required amount of values associated with this parameter.
 *
 * This is only printed when verbosity is not set to quiet.
 *
 * This uses the following:
 *   - print.set.error: For the error context.
 *   - print.set.strong: For the highlighting context
 *   - print.prefix: For the prefixing a string to the message (such as "ERROR:").
 *
 * @param print
 *   The output structure to print to.
 *
 *   This locks, uses, and unlocks the file stream.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param symbol
 *   The symbol string prepended to both parameters.
 *   This locks, uses, and unlocks the file stream.
 *   This is usually f_console_symbol_long_normal_s.
 * @param parameter
 *   The parameter name.
 * @param amount
 *   The number representing the amount of missing parameters.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_kt_remove_print_error_parameter_missing_value_requires_amount_
  extern f_status_t kt_remove_print_error_parameter_missing_value_requires_amount(fl_print_t * const print, const f_string_static_t symbol, const f_string_static_t parameter, const f_number_unsigned_t amount);
#endif // _di_kt_remove_print_error_parameter_missing_value_requires_amount_

/**
 * Print message about no files being specified.
 *
 * This is only printed when verbosity is not set to quiet.
 *
 * This uses the following:
 *   - print.set.error: For the error context.
 *   - print.set.strong: For the highlighting context
 *   - print.prefix: For the prefixing a string to the message (such as "ERROR:").
 *
 * @param print
 *   The output structure to print to.
 *
 *   This locks, uses, and unlocks the file stream.
 *
 *   This does not alter print.custom.setting.state.status.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_print_format()
 */
#ifndef _di_kt_remove_print_error_parameter_no_files_
  extern f_status_t kt_remove_print_error_parameter_no_files(fl_print_t * const print);
#endif // _di_kt_remove_print_error_parameter_no_files_

/**
 * Print message about parameter having an unknown value.
 *
 * This is only printed when verbosity is not set to quiet.
 *
 * This uses the following:
 *   - print.set.error: For the error context.
 *   - print.set.strong: For the highlighting context
 *   - print.prefix: For the prefixing a string to the message (such as "ERROR:").
 *
 * @param print
 *   The output structure to print to.
 *
 *   This locks, uses, and unlocks the file stream.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param symbol
 *   The symbol string prepended to both parameters.
 *   This locks, uses, and unlocks the file stream.
 *   This is usually f_console_symbol_long_normal_s.
 * @param parameter
 *   The parameter name.
 * @param value
 *   The unknown value.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_kt_remove_print_error_parameter_unknown_value_
  extern f_status_t kt_remove_print_error_parameter_unknown_value(fl_print_t * const print, const f_string_static_t symbol, const f_string_static_t parameter, const f_string_static_t value);
#endif // _di_kt_remove_print_error_parameter_unknown_value_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_remove_print_error_h
