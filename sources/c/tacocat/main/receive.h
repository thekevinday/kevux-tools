/**
 * Kevux Tools - TacocaT
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _kt_tacocat_receive_h
#define _kt_tacocat_receive_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform the receive operation for the receive sockets.
 *
 * @param main
 *   The main program and settings data.
 *
 *   Must be of type kt_tacocat_main_t.
 *
 *   This does not alter main.setting.state.status, except on interrupt signal.
 *
 *   This alters main.setting.status_receive:
 *     F_okay on success.
 *
 *     F_interrupt (with error bit set) on interrupt received.
 *
 *     Errors (with error bit) from: f_file_close().
 *     Errors (with error bit) from: f_file_poll().
 *     Errors (with error bit) from: kt_tacocat_receive_process().
 *
 * @return
 *   0, always.
 *
 * @see f_file_close()
 * @see f_file_poll()
 * @see kt_tacocat_receive_process()
 */
#ifndef _di_kt_tacocat_receive_
  extern void * kt_tacocat_receive(void * const main);
#endif // _di_kt_tacocat_receive_

/**
 * Process the network socket, retrieving the data and writing to the file.
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
 *     F_done (with error bit) on too many retries.
 *     F_packet_too_small (with error bit) on total packet size is too small.
 *     F_packet_too_large (with error bit) on total packet size is too large.
 *     F_payload_too_large (with error bit) on total payload size is too large.
 *
 *     Errors (with error bit) from: f_file_open().
 *     Errors (with error bit) from: f_file_write().
 *     Errors (with error bit) from: f_memory_array_increase_by().
 *     Errors (with error bit) from: f_memory_array_resize().
 *     Errors (with error bit) from: f_socket_read_stream().
 *     Errors (with error bit) from: kt_tacocat_receive_process_control().
 *
 * @return
 *    F_done on success and done processing.
 *    F_done_not on success but not done processing.
 *
 *    F_parameter (with error bit) on invalid parameter.
 *
 * @see f_file_open()
 * @see f_file_write()
 * @see f_memory_array_increase_by()
 * @see f_memory_array_resize()
 * @see f_socket_read_stream()
 * @see kt_tacocat_receive_process_control()
 */
#ifndef _di_kt_tacocat_receive_process_
  extern f_status_t kt_tacocat_receive_process(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set);
#endif // _di_kt_tacocat_receive_process_

/**
 * Process the network socket, retrieving and processing the Control and Size header information.
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
 *
 *     Errors (with error bit) from: f_fss_simple_packet_decode_range().
 *     Errors (with error bit) from: f_memory_array_increase_by().
 *     Errors (with error bit) from: f_memory_array_resize().
 *     Errors (with error bit) from: f_socket_accept().
 *     Errors (with error bit) from: f_socket_read_stream().
 *
 * @see f_fss_simple_packet_decode_range()
 * @see f_memory_array_increase_by()
 * @see f_memory_array_resize()
 * @see f_socket_accept()
 * @see f_socket_read_stream()
 */
#ifndef _di_kt_tacocat_receive_process_control_
  extern void kt_tacocat_receive_process_control(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set);
#endif // _di_kt_tacocat_receive_process_control_

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
 *   This does not alter set.status.
 */
#ifndef _di_kt_tacocat_receive_process_initialize_
  extern void kt_tacocat_receive_process_initialize(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set);
#endif // _di_kt_tacocat_receive_process_initialize_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_receive_h
