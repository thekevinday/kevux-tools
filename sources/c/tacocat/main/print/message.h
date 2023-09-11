/**
 * Kevux Tools - TacocaT
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the print message functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _kt_tacocat_print_message_h
#define _kt_tacocat_print_message_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print help.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This requires print.custom to be fake_main_t.
 *
 *   This locks, uses, and unlocks the file stream.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param context
 *   The color context settings.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_kt_tacocat_print_message_help_
  extern f_status_t kt_tacocat_print_message_help(fl_print_t * const print, const f_color_context_t context);
#endif // _di_kt_tacocat_print_message_help_

/**
 * Print message about receive operation packet being complete.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This locks, uses, and unlocks the file stream.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param set
 *   The socket set relating to the message.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_kt_tacocat_print_message_receive_operation_complete_
  extern f_status_t kt_tacocat_print_message_receive_operation_complete(fl_print_t * const print, const kt_tacocat_socket_set_t set);
#endif // _di_kt_tacocat_print_message_receive_operation_complete_

/**
 * Print message about receive operation packet control size.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This locks, uses, and unlocks the file stream.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param set
 *   The socket set relating to the message.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_kt_tacocat_print_message_receive_operation_control_size_
  extern f_status_t kt_tacocat_print_message_receive_operation_control_size(fl_print_t * const print, const kt_tacocat_socket_set_t set);
#endif // _di_kt_tacocat_print_message_receive_operation_control_size_

/**
 * Print message about receive operation packet received.
 *
 * @param print
 *   The output structure to print to.
 *
 *   This locks, uses, and unlocks the file stream.
 *
 *   This does not alter print.custom.setting.state.status.
 * @param set
 *   The socket set relating to the message.
 *
 * @return
 *   F_okay on success.
 *   F_output_not on success, but no printing is performed.
 *
 *   F_output_not (with error bit) if setting is NULL.
 */
#ifndef _di_kt_tacocat_print_message_receive_operation_received_
  extern f_status_t kt_tacocat_print_message_receive_operation_received(fl_print_t * const print, const kt_tacocat_socket_set_t set);
#endif // _di_kt_tacocat_print_message_receive_operation_received_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_print_message_h
