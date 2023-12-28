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
 * @see f_socket_read_stream()
 */
#ifndef _di_kt_tacocat_send_process_
  extern f_status_t kt_tacocat_send_process(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set);
#endif // _di_kt_tacocat_send_process_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_send_h
