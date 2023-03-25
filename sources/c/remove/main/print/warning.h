/**
 * Kevux Tools - Remove
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print warning functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _kt_remove_print_warning_h
#define _kt_remove_print_warning_h

#ifdef __cplusplus
extern "C" {
#endif

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
 *   The output structure to print to.
 *
 *   This locks, uses, and unlocks the file stream.
 *
 *   This does not alter print.custom.setting.state.status.
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
  extern f_status_t remove_print_warning_file_reason(fl_print_t * const print, const f_string_static_t path, const f_string_static_t reason);
#endif // _di_kt_remove_print_warning_file_reason_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_remove_print_warning_h
