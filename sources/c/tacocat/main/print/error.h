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
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param function
 *   A string representing the function that has an error.
 *
 * @return
 *   F_okay on success.
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
 * Print generic error message regarding a function failing in some way using the given status.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param function
 *   A string representing the function that has an error.
 * @param status
 *   The status code representing the error being reported.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_print()
 */
#ifndef _di_kt_tacocat_print_error_status_
  extern f_status_t kt_tacocat_print_error_status(fl_print_t * const print, const f_string_t function, const f_status_t status);
#endif // _di_kt_tacocat_print_error_status_

/**
 * Print file related error messages.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
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
 *   F_okay on success.
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
 * Print network-related error message regarding a function failing in some way using the given status.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param on
 *   The network connection direction, which should either be "receive" or "send".
 * @param network
 *   The name of the network in which the error is related.
 * @param status
 *   The status code representing the error.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_kt_tacocat_print_error_on_
  extern f_status_t kt_tacocat_print_error_on(fl_print_t * const print, const f_string_t function, f_string_static_t on, const f_string_static_t network, const f_status_t status);
#endif // _di_kt_tacocat_print_error_on_

/**
 * Print network-related error message for when buffer is too large to accept additional packet blocks.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param on
 *   The network connection direction, which should either be "receive" or "send".
 * @param network
 *   The name of the network in which the error is related.
 * @param size_max
 *   The maximum buffer size.
 * @param size_got
 *   The provided buffer size.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_kt_tacocat_print_error_on_buffer_too_large_
  extern f_status_t kt_tacocat_print_error_on_buffer_too_large(fl_print_t * const print, f_string_static_t on, const f_string_static_t network, const f_number_unsigned_t size_expect, const f_number_unsigned_t size_got);
#endif // _di_kt_tacocat_print_error_on_buffer_too_large_

/**
 * Print network-related error message for when the connection is busy.
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
#ifndef _di_kt_tacocat_print_error_on_busy_
  extern f_status_t kt_tacocat_print_error_on_busy(fl_print_t * const print, f_string_static_t on, const f_string_static_t network);
#endif // _di_kt_tacocat_print_error_on_busy_
/**
 * Print network-related error message regarding the writing the network data to a file.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param function
 *   The name of the function where the error happened.
 *   Set to 0 to disable.
 * @param on
 *   The network connection direction, which should either be "receive" or "send".
 * @param network
 *   The name of the network in which the error is related.
 * @param status
 *   The status code representing the error.
 * @param name
 *   The name of the file or directory.
 * @param operation
 *   The file operation that fails, such as 'open' or 'write'.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_kt_tacocat_print_error_on_file_
  extern f_status_t kt_tacocat_print_error_on_file(fl_print_t * const print, const f_string_t function, f_string_static_t on, const f_string_static_t network, const f_status_t status, const f_string_static_t name, const f_string_static_t operation);
#endif // _di_kt_tacocat_print_error_on_file_

/**
 * Print network-related error message for when the connection is busy.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param on
 *   The network connection direction, which should either be "receive" or "send".
 * @param network
 *   The name of the network in which the error is related.
 * @param size_expect
 *   The expected buffer size.
 * @param size_got
 *   The provided buffer size.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_kt_tacocat_print_error_on_packet_too_small_
  extern f_status_t kt_tacocat_print_error_on_packet_too_small(fl_print_t * const print, f_string_static_t on, const f_string_static_t network, const f_number_unsigned_t size_expect, const f_number_unsigned_t size_got);
#endif // _di_kt_tacocat_print_error_on_packet_too_small_

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
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_kt_tacocat_print_error_parameter_value_resolve_unknown_
  extern f_status_t kt_tacocat_print_error_parameter_value_resolve_unknown(fl_print_t * const print, const f_string_dynamic_t unknown);
#endif // _di_kt_tacocat_print_error_parameter_value_resolve_unknown_

/**
 * Print error about invalid port number in address.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param address
 *   The entire address string, including the port number.
 * @param port_range
 *   The range within the address string representing the port.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_kt_tacocat_print_error_port_number_invalid_
  extern f_status_t kt_tacocat_print_error_port_number_invalid(fl_print_t * const print, const f_string_static_t address, const f_string_range_t port_range);
#endif // _di_kt_tacocat_print_error_port_number_invalid_

/**
 * Print error message for when an unsupported protocol is used.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param name
 *   The file or network name associated with the unsupported protocol.
 * @param protocol
 *   The protocol number representing the unsupported protocol
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 *
 * @see fll_error_file_print()
 */
#ifndef _di_kt_tacocat_print_error_socket_protocol_unsupported_
  extern f_status_t kt_tacocat_print_error_socket_protocol_unsupported(fl_print_t * const print, const f_string_dynamic_t name, const f_number_unsigned_t protocol);
#endif // _di_kt_tacocat_print_error_socket_protocol_unsupported_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_print_error_h
