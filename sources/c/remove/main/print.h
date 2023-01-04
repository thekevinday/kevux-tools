/**
 * Kevux Tools - Remove
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _kt_remove_print_h
#define _kt_remove_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print generic error message regarding a function failing in some way.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates the how and where to print.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 *
 * @see fll_error_print()
 */
#ifndef _di_kt_remove_print_error_
  extern f_status_t kt_remove_print_error(kt_remove_setting_t * const setting, const fl_print_t print, const f_string_t function);
#endif // _di_kt_remove_print_error_

/**
 * Print file related error or warning messages.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates how printing is to be performed.
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
 * @see fll_error_file_print()
 */
#ifndef _di_kt_remove_print_error_file_
  extern f_status_t kt_remove_print_error_file(kt_remove_setting_t * const setting, const fl_print_t print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type);
#endif // _di_kt_remove_print_error_file_

/**
 * Print message about parameter not have the required amount of values associated with this parameter.
 *
 * This is only printed when verbosity is not set to quiet.
 *
 * This uses the following:
 *   - print.set->error: For the error context.
 *   - print.set->strong: For the highlighting context
 *   - print.prefix: For the prefixing a string to the message (such as "ERROR:").
 *
 * @param print
 *   The output structure.
 *   This locks, uses, and unlocks the file stream.
 * @param symbol
 *   The symbol string prepended to both parameters.
 *   This locks, uses, and unlocks the file stream.
 *   This is usually f_console_symbol_long_enable_s.
 * @param parameter
 *   The parameter name.
 * @param amount
 *   The number representing the amount of missing parameters.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_kt_remove_print_error_parameter_missing_value_requires_amount_
  extern f_status_t kt_remove_print_error_parameter_missing_value_requires_amount(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t parameter, const f_number_unsigned_t amount);
#endif // _di_kt_remove_print_error_parameter_missing_value_requires_amount_

/**
 * Print message about no files being specified.
 *
 * This is only printed when verbosity is not set to quiet.
 *
 * This uses the following:
 *   - print.set->error: For the error context.
 *   - print.set->strong: For the highlighting context
 *   - print.prefix: For the prefixing a string to the message (such as "ERROR:").
 *
 * @param print
 *   The output structure.
 *   This locks, uses, and unlocks the file stream.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_kt_remove_print_error_parameter_no_files_
  extern f_status_t kt_remove_print_error_parameter_no_files(const fl_print_t print);
#endif // _di_kt_remove_print_error_parameter_no_files_

/**
 * Print message about parameter having an unknown value.
 *
 * This is only printed when verbosity is not set to quiet.
 *
 * This uses the following:
 *   - print.set->error: For the error context.
 *   - print.set->strong: For the highlighting context
 *   - print.prefix: For the prefixing a string to the message (such as "ERROR:").
 *
 * @param print
 *   The output structure.
 *   This locks, uses, and unlocks the file stream.
 * @param symbol
 *   The symbol string prepended to both parameters.
 *   This locks, uses, and unlocks the file stream.
 *   This is usually f_console_symbol_long_enable_s.
 * @param parameter
 *   The parameter name.
 * @param value
 *   The unknown value.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_kt_remove_print_error_parameter_unknown_value_
  extern f_status_t kt_remove_print_error_parameter_unknown_value(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t parameter, const f_string_static_t value);
#endif // _di_kt_remove_print_error_parameter_unknown_value_

/**
 * Print help.
 *
 * @param setting
 *   The main program settings.
 *
 *   This does not alter setting.status.
 * @param print
 *   Designates how printing is to be performed.
 * @param context
 *   The color context settings.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_kt_remove_print_help_
  extern f_status_t kt_remove_print_help(kt_remove_setting_t * const setting, const fl_print_t print, const f_color_context_t context);
#endif // _di_kt_remove_print_help_

/**
 * Print warning message about file not being found.
 *
 * This is only printed when verbosity is less than verbose and kt_remove_flag_print_warning_e is not set.
 * This is not printed when verbosity is set to quiet even when kt_remove_flag_print_warning_e is set.
 * This is not printed when kt_remove_flag_force_e is set.
 *
 * This uses the following:
 *   - print.set->warning: For the warning context.
 *   - print.set->strong: For the highlighting context
 *   - print.prefix: For the prefixing a string to the message (such as "WARNING:").
 *
 * @param print
 *   The output structure.
 *   This locks, uses, and unlocks the file stream.
 * @param path
 *   The path to the file.
 * @param reason
 *   The reason for the failure.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_kt_remove_print_warning_file_reason_
  extern f_status_t remove_print_warning_file_reason(kt_remove_setting_t * const setting, const fl_print_t print, const f_string_static_t path, const f_string_static_t reason);
#endif // _di_kt_remove_print_warning_file_reason_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_remove_print_h
