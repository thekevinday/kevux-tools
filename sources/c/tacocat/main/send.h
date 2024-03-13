/**
 * Kevux Tools - TacocaT
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _kt_tacocat_send_h
#define _kt_tacocat_send_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform the send operation for the send sockets.
 *
 * @param main
 *   The main program and settings data.
 *
 *   Must be of type kt_tacocat_main_t.
 *
 *   This does not alter main.setting.state.status, except on interrupt signal.
 *
 *   This alters main.setting.status_send:
 *     F_okay on success.
 *
 *     F_interrupt (with error bit set) on interrupt received.
 *
 * @return
 *   0, always.
 */
#ifndef _di_kt_tacocat_send_
  extern void * kt_tacocat_send(void * const main);
#endif // _di_kt_tacocat_send_

/**
 * Process the network socket, retrieving the data and writing to the file.
 *
 * This sends an FSS-000F (Simple Packet) using FSS-000E (Payload) such that the "payload" Object contains the file being transferred.
 * The file being transferred is transferred as-is.
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
 *     F_okay on success.
 *
 *     F_packet_too_large (with error bit) on total packet size is too large.
 *     F_payload_too_large (with error bit) on total payload size is too large.
 *     F_too_large (with error bit) on file too large.
 *
 *     Errors (with error bit) from: kt_tacocat_process_abstruse_initialize()
 *
 * @return
 *   F_done on success and done processing.
 *   F_done_not on success but not done processing.
 *
 *   F_parameter (with error bit) on invalid parameter.
 *
 * @see f_socket_read_stream()
 * @see kt_tacocat_send_process_initialize()
 */
#ifndef _di_kt_tacocat_send_process_
  extern f_status_t kt_tacocat_send_process(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set);
#endif // _di_kt_tacocat_send_process_

/**
 * Process the network socket, performing the initialization step such as when step == 0.
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
 *     F_okay on success.
 *
 *     F_packet_too_large (with error bit) on total packet size is too large.
 *     F_payload_too_large (with error bit) on total payload size is too large.
 *     F_too_large (with error bit) on file too large.
 *
 *     Errors (with error bit) from: f_memory_array_increase_by()
 *     Errors (with error bit) from: kt_tacocat_process_abstruse_initialize()
 *     Errors (with error bit) from: kt_tacocat_send_process_time_now()
 *
 * @see f_memory_array_increase_by()
 * @see kt_tacocat_process_abstruse_initialize()
 * @see kt_tacocat_send_process_time_now()
 */
#ifndef _di_kt_tacocat_send_process_initialize_
  extern void kt_tacocat_send_process_initialize(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set);
#endif // _di_kt_tacocat_send_process_initialize_

/**
 * Build a string containing the current time.
 *
 * @param set
 *   The socket set to process.
 *   Must not be NULL.
 *
 *   The set.time is updated with the generated time string.
 *
 *   This alters set.status:
 *     F_okay on success.
 *
 *     F_time (with error bit) on failure to get the time.
 *
 *     Errors (with error bit) from: f_memory_array_increase_by().
 *     Errors (with error bit) from: f_string_append().
 *     Errors (with error bit) from: f_string_dynamic_append().
 *     Errors (with error bit) from: f_string_dynamic_terminate_after().
 *
 * @see f_memory_array_increase_by()
 * @see f_string_append()
 * @see f_string_dynamic_append()
 * @see f_string_dynamic_terminate_after()
 *
 * @see asctime()
 * @see gmtime()
 * @see strnlen()
 */
#ifndef _di_kt_tacocat_send_process_time_now_
  extern void kt_tacocat_send_process_time_now(kt_tacocat_socket_set_t * const set);
#endif // _di_kt_tacocat_send_process_time_now_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_send_h
