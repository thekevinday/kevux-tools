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
 * kt_tacocat_block_*_d:
 *   - size:         The block size in bytes to use for either sending or receiving.
 *   - size_receive: The block size in bytes to use when sending packets.
 *   - size_send:    The block size in bytes to use when receiving packets.
 *
 * kt_tacocat_cache_*_d:
 *   - peek: The size in bytes representing the size of the peek cache (should be set to at least "kt_tacocat_block_size_receive_d + 1" and must be greater than zero).
 *
 * kt_tacocat_interval_*_d:
 *   - poll: The time in milliseconds to poll for before returning (this is the amount of time poll() blocks).
 *
 * kt_tacocat_max_*_d:
 *   - backlog:  The max backlog in bytes size to use.
 *   - buffer:   The max buffer in bytes size to use when receiving packets.
 *   - maintain: The max size in bytes to maintain a particular buffer.
 *
 * kt_tacocat_packet_*_d:
 *   - peek: The size to peek into the packet to get the initial information.
 *   - read: The size to read at a time when processing the packet.
 *
 * kt_tacocat_signal_*_d:
 *   - check:          When not using threads, this is how often to perform the check (lower numbers incur more kernel I/O).
 *   - check_failsafe: When using threads, how many consecutive failures to check signal before aborting (as a recursion failsafe).
 *
 * kt_tacocat_startup_*_d:
 *   - retry_delay_second:      The delay in seconds to wait between each retry.
 *   - retry_delay_millisecond: The delay in milliseconds to wait between each retry.
 *   - retry_max:               During start up, the maximum number of retries to perform when trying to establish the initial connection before giving up.
 */
#ifndef _di_kt_tacocat_d_
  #define kt_tacocat_allocation_console_d 0x4
  #define kt_tacocat_allocation_large_d   0x800
  #define kt_tacocat_allocation_small_d   0x80

  #define kt_tacocat_block_size_d          0xffff
  #define kt_tacocat_block_size_receive_d  kt_tacocat_block_size_d
  #define kt_tacocat_block_size_send_d     kt_tacocat_block_size_d

  #define kt_tacocat_cache_size_peek_d (kt_tacocat_block_size_receive_d + 1)

  #define kt_tacocat_interval_poll_d 1400 // 1.4 second.

  #define kt_tacocat_max_backlog_d  0x400
  #define kt_tacocat_max_buffer_d   0x10000000 // 0x10^0x5 * 0x100 (Which is 256 Megabytes (0x10^0x5 where the base unit is 16 rather than 10 or 2 (maybe call this xytes? Megaxytes?)).
  #define kt_tacocat_max_maintain_d 0x100000   // 0x10^5 (Which is 1 Megabyte in base 16 (1 Megaxyte (MX)).

  #define kt_tacocat_packet_peek_d F_fss_simple_packet_block_header_size_d
  #define kt_tacocat_packet_read_d 0x2000

  #define kt_tacocat_signal_check_d          0x4e20
  #define kt_tacocat_signal_check_failsafe_d 0x4e20

  #define kt_tacocat_startup_retry_delay_second_d      3
  #define kt_tacocat_startup_retry_delay_millisecond_d 0
  #define kt_tacocat_startup_retry_max_d               24
#endif // _di_kt_tacocat_d_

/**
 * The program macros.
 *
 * macro_setting_load_print_first:
 *   Intended to be used to simplify the code in kt_tacocat_setting_load() and make it more readable.
 *
 * macro_setting_load_handle_send_receive_error_continue_1:
 *   Intended to be used to simplify the code in kt_tacocat_setting_load_send_receive() and make it more readable.
 *   This is for the basic error that calls kt_tacocat_print_error() when printing.
 *
 * macro_setting_load_handle_send_receive_error_file_continue_1:
 *   The same as macro_setting_load_handle_send_receive_error_continue_1() but intended for file errors.
 *
 * macro_kt_receive_process_handle_error_exit_1:
 *   Intended to be used for handling an error during the receive process while not processing within flag kt_tacocat_socket_flag_block_control_e.
 *   The parameter id_data and is set to 0 to disable and is otherwise an address pointer.
 *
 * macro_kt_receive_process_begin_handle_error_exit_1:
 *   Intended to be used for handling an error during the receive process while processing within flag kt_tacocat_socket_flag_block_control_e.
 */
#ifndef _di_kt_tacocat_macros_d_
  #define macro_setting_load_print_first() \
    if ((main->setting.flag & kt_tacocat_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) { \
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to); \
    }

  #define macro_setting_load_handle_send_receive_error_continue_1(method) \
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

  #define macro_setting_load_handle_send_receive_error_continue_2(method) \
    if (F_status_is_error(main->setting.state.status)) { \
      macro_setting_load_print_first(); \
      \
      kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(method)); \
      \
      if (F_status_is_error_not(failed)) { \
        failed = main->setting.state.status; \
      } \
      \
      sets[i]->array[j].status = main->setting.state.status; \
      \
      continue; \
    }

  #define macro_setting_load_handle_send_receive_error_file_continue_1(method, name, operation, type) \
    if (F_status_is_error(main->setting.state.status)) { \
      macro_setting_load_print_first(); \
      \
      kt_tacocat_print_error_file(&main->program.error, macro_kt_tacocat_f(method), name, operation, type); \
      \
      if (F_status_is_error_not(failed)) { \
        failed = main->setting.state.status; \
      } \
      \
      sets[i]->array[j].status = main->setting.state.status; \
      \
      continue; \
    }

  #define macro_kt_receive_process_handle_error_exit_1(main, method, name, status, flag, id_data) \
    if (F_status_is_error(status)) { \
      kt_tacocat_print_error_on(&main->program.error, macro_kt_tacocat_f(method), kt_tacocat_receive_s, name, status); \
      \
      if (id_data) { \
        f_file_close_id(id_data); \
      } \
      \
      flag = 0; \
      \
      return; \
    }

  #define macro_kt_receive_process_begin_handle_error_exit_1(main, method, name, status, flag) \
    if (F_status_is_error(status)) { \
      kt_tacocat_print_error_on(&main->program.error, macro_kt_tacocat_f(method), kt_tacocat_receive_s, name, status); \
      \
      flag = 0; \
      \
      return; \
    }
#endif // _di_kt_tacocat_macro_d_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_common_define_h
