/**
 * Kevux Tools - TacocaT
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _kt_tacocat_process_h
#define _kt_tacocat_process_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform the main TacocaT processing.
 *
 * @param main
 *   The main program and settings data.
 *
 *   This alters main.setting.state.status:
 *     F_okay on success.
 */
#ifndef _di_kt_tacocat_process_main_
  extern void kt_tacocat_process_main(kt_tacocat_main_t * const main);
#endif // _di_kt_tacocat_process_main_

/**
 * Initialize the abstruse for the send or receive process.
 *
 * This initializes the abstruse to the standard packet abstruse structure.
 *
 * Standard abstruse packet index positions:
 *   0: status.
 *   1: type.
 *   2: length.
 *   3: part.
 *   4: total.
 *   5: name.
 *   6: salt.
 *
 * @param main
 *   The main program and settings data.
 *
 *   This does not alter main.setting.state.status, except on interrupt signal.
 * @param set
 *   The socket set to process.
 *   Must not be NULL.
 *
 *   This alters set.status:
 *     Success from: f_memory_array_increase_by().
 *
 *     Errors (with error bit) from: f_memory_array_increase_by().
 *
 * @see f_memory_array_increase_by()
 */
#ifndef _di_kt_tacocat_process_abstruse_initialize_
  extern void kt_tacocat_process_abstruse_initialize(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set);
#endif // _di_kt_tacocat_process_abstruse_initialize_

/**
 * Disconnect the socket set and close open file.
 *
 * @param main
 *   The main program and settings data.
 *
 *   This alters main.setting.state.status:
 *     F_parameter (with error bit) on invalid parameter.
 *
 *     This does not set parameter error on success or any socket disconnect error.
 * @param set
 *   The socket set to disconnect all parts of.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) on invalid parameter.
 */
#ifndef _di_kt_tacocat_process_socket_sets_disconnect_
  extern f_status_t kt_tacocat_process_socket_sets_disconnect(kt_tacocat_main_t * const main, kt_tacocat_socket_sets_t * const sets);
#endif // _di_kt_tacocat_process_socket_sets_disconnect_

/**
 * Traverse the sockets, grabbing the first error and setting the main.setting.state.status appropriately.
 *
 * This does not print messages.
 *
 * @param main
 *   The main program and settings data.
 *
 *   This alters main.setting.state.status:
 *     F_okay on success and no error is found.
 *
 *     An status with error bit set from any socket that has a status failure.
 *
 *     If this already has the error bit set, then no changes are performed.
 * @param sets
 *   The socket sets to handle the errors of.
 * @param status
 *   The status to update with the status code from the given set.
 */
#ifndef _di_kt_tacocat_process_socket_sets_error_handle_
  extern void kt_tacocat_process_socket_sets_error_handle(kt_tacocat_main_t * const main, const kt_tacocat_socket_sets_t sets, f_status_t * const status);
#endif // _di_kt_tacocat_process_socket_sets_error_handle_

/**
 * Check the socket set and handle and print error if the array lengths do not match.
 *
 * @param main
 *   The main program and settings data.
 *
 *   This alters main.setting.state.status:
 *     F_parameter (with error bit) if a parameter is invalid.
 *
 *     This is not altered on success.
 * @param parameter
 *   The parameter long name to use when printing errors.
 * @param set
 *   The socket set to handle the errors of.
 * @param status
 *   The status to update with the status code from the given set.
 *
 * @return
 *   F_okay on no error.
 *
 *   F_interrupt (with error bit) if interrupt was received.
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_kt_tacocat_process_socket_set_error_has_
  extern f_status_t kt_tacocat_process_socket_set_error_has(kt_tacocat_main_t * const main, const f_string_static_t parameter, const kt_tacocat_socket_sets_t set, f_status_t * const status);
#endif // _di_kt_tacocat_process_socket_set_error_has_

/**
 * Process the receive socket set.
 *
 * @param main
 *   The main program and settings data.
 *
 *   This alters main.setting.state.status:
 *     F_okay on success.
 */
#ifndef _di_kt_tacocat_process_socket_set_receive_
  extern void kt_tacocat_process_socket_set_receive(kt_tacocat_main_t * const main);
#endif // _di_kt_tacocat_process_socket_set_receive_

/**
 * Process the send socket set.
 *
 * @param main
 *   The main program and settings data.
 *
 *   This alters main.setting.state.status:
 *     F_okay on success.
 */
#ifndef _di_kt_tacocat_process_socket_set_send_
  extern void kt_tacocat_process_socket_set_send(kt_tacocat_main_t * const main);
#endif // _di_kt_tacocat_process_socket_set_send_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_process_h
