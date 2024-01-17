/**
 * Kevux Tools - TacocaT
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _kt_tacocat_packet_h
#define _kt_tacocat_packet_h

#ifdef __cplusplus
extern "C" {
#endif


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
 *     Errors (with error bit) from: kt_tacocat_packet_extract_header().
 *     Errors (with error bit) from: kt_tacocat_packet_extract_signature().
 * @param direction
 *   The string representing the direction and is used for error handling.
 *   This is generally either kt_tacocat_receive_s or kt_tacocat_send_s.
 *
 * @see f_memory_array_increase_by()
 * @see kt_tacocat_packet_extract_header()
 * @see kt_tacocat_packet_extract_signature()
 */
#ifndef _di_kt_tacocat_packet_extract_
  extern void kt_tacocat_packet_extract(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set, const f_string_static_t direction);
#endif // _di_kt_tacocat_packet_extract_

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
 *   - 7: Transaction ID (Can be anything, generally unique or port number).
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
 *     F_packet (with error bit) on invalid packet header.
 *
 *     Errors (with error bit) from: fll_fss_extended_read().
 * @param at
 *   The index position representing which Object and Contents set to use.
 * @param direction
 *   The string representing the direction and is used for error handling.
 *   This is generally either kt_tacocat_receive_s or kt_tacocat_send_s.
 *
 * @see fll_fss_extended_read()
 */
#ifndef _di_kt_tacocat_packet_extract_header_
  extern void kt_tacocat_packet_extract_header(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set, const f_number_unsigned_t at, const f_string_static_t direction);
#endif // _di_kt_tacocat_packet_extract_header_

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
 * @param direction
 *   The string representing the direction and is used for error handling.
 *   This is generally either kt_tacocat_receive_s or kt_tacocat_send_s.
 * @param at
 *   The index position representing which Object and Contents set to use.
 */
#ifndef _di_kt_tacocat_packet_extract_signature_
  extern void kt_tacocat_packet_extract_signature(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set, const f_number_unsigned_t at, const f_string_static_t direction);
#endif // _di_kt_tacocat_packet_extract_signature_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_packet_h
