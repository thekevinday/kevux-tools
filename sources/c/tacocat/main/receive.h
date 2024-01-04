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
 * Process the header and signature strings, extracting the data.
 *
 * Another function should perform some of the validation on the header.
 * @todo This other function needs to return a status code such as F_continue to designate to continue to the next iteration.
 *       Ideally, the flag will be set to how to continue, such as "continue loading the entire payload".
 *       This situation would arise when the payload needs to be validated, such as the size.
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
 *     Errors (with error bit) from: f_memory_array_increase_by().
 *     Errors (with error bit) from: kt_tacocat_receive_process_extract_header().
 *     Errors (with error bit) from: kt_tacocat_receive_process_extract_signature().
 *
 * @see f_memory_array_increase_by()
 * @see kt_tacocat_receive_process_extract_header()
 * @see kt_tacocat_receive_process_extract_signature()
 */
#ifndef _di_kt_tacocat_receive_process_extract_
  extern void kt_tacocat_receive_process_extract(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set);
#endif // _di_kt_tacocat_receive_process_extract_

/**
 * Extract the header strings using the given index for an Object and Content.
 *
 * The positions in the abstruse are hard-coded with specific representations.
 *
 * Index Positions:
 *   - 0: Status string (such as F_okay).
 *   - 1: Type string (type of packet).
 *   - 2: Length number (the length of the Payload section).
 *   - 3: Packet part number.
 *   - 4: Total packet parts number.
 *   - 5: Name string (file name).
 *   - 6: Salt string (for making packet unique, if encrypted, signed, or something similar).
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
 *     F_data_not on success, but no data to process.
 *
 *     Errors (with error bit) from: fll_fss_extended_read().
 * @param at
 *   The index position representing which Object and Contents set to use.
 *
 * @see fll_fss_extended_read()
 */
#ifndef _di_kt_tacocat_receive_process_extract_header_
  extern void kt_tacocat_receive_process_extract_header(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set, const f_number_unsigned_t at);
#endif // _di_kt_tacocat_receive_process_extract_header_

/**
 * Extract the signature strings using the given index for an Object and Content.
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
 * @param at
 *   The index position representing which Object and Contents set to use.
 */
#ifndef _di_kt_tacocat_receive_process_extract_signature_
  extern void kt_tacocat_receive_process_extract_signature(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set, const f_number_unsigned_t at);
#endif // _di_kt_tacocat_receive_process_extract_signature_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_receive_h
