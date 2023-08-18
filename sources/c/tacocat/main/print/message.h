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
 *
 * @see f_file_stream_flush()
 * @see f_file_stream_lock()
 * @see f_file_stream_unlock()
 * @see f_print_dynamic_raw()
 * @see fl_print_format()
 * @see fll_program_print_help_header()
 * @see fll_program_print_help_option()
 * @see fll_program_print_help_option_long()
 */
#ifndef _di_kt_tacocat_print_message_help_
  extern f_status_t kt_tacocat_print_message_help(fl_print_t * const print, const f_color_context_t context);
#endif // _di_kt_tacocat_print_message_help_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_print_message_h
