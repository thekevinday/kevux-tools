/**
 * Kevux Tools - TacocaT
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print warning functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _kt_tacocat_print_warning_h
#define _kt_tacocat_print_warning_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print warning message about given port number being out of range for this system.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param on
 *   The network connection direction, which should either be "receive" or "send".
 * @param network
 *   The name of the network in which the error is related.
 * @param retry
 *   The current retry attempt.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_kt_tacocat_print_warning_on_busy_
  extern f_status_t kt_tacocat_print_warning_on_busy(fl_print_t * const print, f_string_static_t on, const f_string_static_t network, const f_number_unsigned_t retry);
#endif // _di_kt_tacocat_print_warning_on_busy_

/**
 * Print warning message about client closing the connection unexpectedly.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param on
 *   The network connection direction, which should either be "receive" or "send".
 * @param network
 *   The name of the network in which the error is related.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_kt_tacocat_print_warning_on_client_closed_
  extern f_status_t kt_tacocat_print_warning_on_client_closed(fl_print_t * const print, f_string_static_t on, const f_string_static_t network);
#endif // _di_kt_tacocat_print_warning_on_client_closed_

/**
 * Print network-related warning message regarding the writing the network data to a file.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param function
 *   The name of the function where the warning happened.
 *   Set to 0 to disable.
 * @param on
 *   The network connection direction, which should either be "receive" or "send".
 * @param network
 *   The name of the network in which the warning is related.
 * @param status
 *   The status code representing the warning.
 * @param name
 *   The name of the file or directory.
 * @param operation
 *   The file operation that fails, such as 'open' or 'write'.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with warning bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_kt_tacocat_print_warning_on_file_
  extern f_status_t kt_tacocat_print_warning_on_file(fl_print_t * const print, const f_string_t function, f_string_static_t on, const f_string_static_t network, const f_status_t status, const f_string_static_t name, const f_string_static_t operation);
#endif // _di_kt_tacocat_print_warning_on_file_

/**
 * Print warning message about given parameter being a specific integer value.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param symbol
 *   The symbol string prepended to both parameters.
 *   This locks, uses, and unlocks the file stream.
 *   This is usually f_console_symbol_long_normal_s.
 * @param name
 *   The parameter name.
 * @param is
 *   The string representing the number that is being warned about.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_kt_tacocat_print_warning_parameter_integer_less_than_
  extern f_status_t kt_tacocat_print_warning_parameter_integer_less_than(fl_print_t * const print, const f_string_static_t symbol, const f_string_static_t name, const f_string_static_t than);
#endif // _di_kt_tacocat_print_warning_parameter_integer_less_than_

/**
 * Print warning message about given port number being out of range for this system.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param address
 *   The original address string.
 * @param port
 *   The out of range port.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see fl_print_format()
 */
#ifndef _di_kt_tacocat_print_warning_port_number_overflow_
  extern f_status_t kt_tacocat_print_warning_port_number_overflow(fl_print_t * const print, const f_string_static_t address, const f_number_unsigned_t port);
#endif // _di_kt_tacocat_print_warning_port_number_overflow_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_print_warning_h
