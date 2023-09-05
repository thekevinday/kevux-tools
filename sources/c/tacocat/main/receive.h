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
 *   This alters main.setting.state.status:
 *     F_okay on success.
 *     F_child on child process exiting.
 *
 * @return
 *   0, always.
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
 *   This alters main.setting.state.status:
 *     F_okay on success.
 *
 *     F_packet_too_large (with error bit) on total packet size is too large.
 *     F_payload_too_large (with error bit) on total payload size is too large.
 * @param index
 *   The position within the receive arrays to process.
 *
 * @see f_socket_read_stream()
 */
#ifndef _di_kt_tacocat_receive_process_
  extern void kt_tacocat_receive_process(kt_tacocat_main_t * const main, const f_number_unsigned_t index);
#endif // _di_kt_tacocat_receive_process_

/**
 * Process the network socket, retrieving and processing the Control and Size header information.
 *
 * @param main
 *   The main program and settings data.
 *
 *   This alters main.setting.state.status:
 *     F_okay on success.
 *
 *     F_packet_too_large (with error bit) on total packet size is too large.
 *     F_payload_too_large (with error bit) on total payload size is too large.
 * @param index
 *   The position within the receive arrays to process.
 *
 * @see f_socket_read_stream()
 */
#ifndef _di_kt_tacocat_receive_process_control_
  extern void kt_tacocat_receive_process_control(kt_tacocat_main_t * const main, const f_number_unsigned_t index);
#endif // _di_kt_tacocat_receive_process_control_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_receive_h
