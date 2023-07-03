/**
 * Kevux Tools - TacocaT
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common define types.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _kt_tacocat_common_define_h
#define _kt_tacocat_common_define_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program defines.
 *
 * kt_tacocat_allocation_*_d:
 *   - console: An allocation step used for small buffers specifically for console parameter.
 *   - large:   An allocation step used for buffers that are anticipated to have large buffers.
 *   - small:   An allocation step used for buffers that are anticipated to have small buffers.
 *
 * kt_tacocat_signal_*_d:
 *   - check:          When not using threads, this is how often to perform the check (lower numbers incur more kernel I/O).
 *   - check_failsafe: When using threads, how many consecutive failures to check signal before aborting (as a recursion failsafe).
 *
 * kt_tacocat_block_size_*_d:
 *   - receive: The block size in bytes to use when sending packets.
 *   - send:    The block size in bytes to use when receiving packets.
 */
#ifndef _di_kt_tacocat_d_
  #define kt_tacocat_allocation_console_d 4
  #define kt_tacocat_allocation_large_d   2048
  #define kt_tacocat_allocation_small_d   128

  #define kt_tacocat_signal_check_d          20000
  #define kt_tacocat_signal_check_failsafe_d 20000

  #define kt_tacocat_block_size_receive_d 65535
  #define kt_tacocat_block_size_send_d    65535
#endif // _di_kt_tacocat_d_

/**
 * The program macros.
 *
 * macro_setting_load_print_first:
 *   Intended to be used to simplify the code in kt_tacocat_setting_load() and make it more readable.
 *
 * macro_setting_load_handle_send_receive_error_continue_basic:
 *   Intended to be used to simplify the code in kt_tacocat_setting_load_send_receive() and make it more readable.
 *   This is for the basic error that calls kt_tacocat_print_error() when printing.
 *
 * macro_setting_load_handle_send_receive_error_file_continue_basic:
 *   The same as macro_setting_load_handle_send_receive_error_continue_basic() but intended for file errors.
 */
#ifndef _di_kt_tacocat_macros_d_
  #define macro_setting_load_print_first() \
    if ((main->setting.flag & kt_tacocat_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) { \
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to); \
    }

  #define macro_setting_load_handle_send_receive_error_continue_basic(method) \
    if (F_status_is_error(main->setting.state.status)) { \
      macro_setting_load_print_first(); \
      \
      kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(method)); \
      \
      if (F_status_is_error_not(failed)) { \
        failed = main->setting.state.status; \
      } \
      \
      continue; \
    }

  #define macro_setting_load_handle_send_receive_error_file_continue_basic(method, name, operation, type) \
    if (F_status_is_error(main->setting.state.status)) { \
      macro_setting_load_print_first(); \
      \
      kt_tacocat_print_error_file(&main->program.error, macro_kt_tacocat_f(method), name, operation, type); \
      \
      if (F_status_is_error_not(failed)) { \
        failed = main->setting.state.status; \
      } \
      \
      continue; \
    }
#endif // _di_kt_tacocat_macro_d_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_common_define_h
