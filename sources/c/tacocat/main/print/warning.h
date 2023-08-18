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
 *   This requires print.custom to be fake_main_t.
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
