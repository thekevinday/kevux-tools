/**
 * Kevux Tools - TacocaT
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common enumeration types.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _kt_tacocat_common_enumeration_h
#define _kt_tacocat_common_enumeration_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Flags passed to the main function or program.
 *
 * kt_tacocat_main_flag_*_e:
 *   - none:            No flags set.
 *   - copyright:       Print copyright.
 *   - print_first:     When set, print new line to message output on program begin after loading settings.
 *   - print_last:      When set, print new line to message output on program end.
 *   - max_buffer:      When set, a maximum buffer on receive is enforced.
 *   - receive:         The address or socket to receive from is specified.
 *   - resolve_classic: Follow the classic Domain Name Resolution method.
 *   - resolve_kevux:   Follow the Kevux Domain Name Resolution method.
 *   - send:            The address or socket send to is specified.
 *   - help:            Print help.
 *   - version:         Print version.
 *
 * For resolve_classic and resolve_kevux flags:
 *   The classic method utilizes the /etc/resolv.conf traditional method.
 *   Under classic, the http://, https://, etc.. act as normal.
 *
 *   The Kevux method utilizes /etc/resolution/ method.
 *   Under Kevux, the web:// represents the traditional DNS, but kevux:// might represent Kevux network.
 *   For example web://www.google.com:443/ would be the same as https://www.google.com/, following DNS via /etc/resolution/dns/web.conf or /etc/resolution/host/web.conf.
 *   For example kevux://www.google.com:443/ would be a different server than google, following DNS via /etc/resolution/dns/kevux.conf or /etc/resolution/host/kevux.conf.
 *   The Kevux method also supports local DNS entries ie (~/.resolution/dns/kevux.conf or ~/.resolution/host/kevux.conf).
 *   @todo The Kevux method will be implemented in a library (project resolution and libresolution), re-introducing and expanding on the Turtle Kevux resolv.conf extensions that Kevin hacked into uClibc several years back.
 */
#ifndef _di_kt_tacocat_main_flag_e_
  enum {
    kt_tacocat_main_flag_none_e            = 0x0,
    kt_tacocat_main_flag_copyright_e       = 0x1,
    kt_tacocat_main_flag_help_e            = 0x2,
    kt_tacocat_main_flag_max_buffer_e      = 0x4,
    kt_tacocat_main_flag_print_first_e     = 0x8,
    kt_tacocat_main_flag_print_last_e      = 0x10,
    kt_tacocat_main_flag_receive_e         = 0x20,
    kt_tacocat_main_flag_resolve_classic_e = 0x40,
    kt_tacocat_main_flag_resolve_kevux_e   = 0x80,
    kt_tacocat_main_flag_resolve_e         = 0x100,
    kt_tacocat_main_flag_send_e            = 0x200,
    kt_tacocat_main_flag_version_e         = 0x400,
  }; // enum
#endif // _di_kt_tacocat_main_flag_e_

/**
 * The main program parameters.
 */
#ifndef _di_kt_tacocat_parameter_e_
  enum {
    kt_tacocat_parameter_help_e,
    kt_tacocat_parameter_copyright_e,
    kt_tacocat_parameter_light_e,
    kt_tacocat_parameter_dark_e,
    kt_tacocat_parameter_no_color_e,
    kt_tacocat_parameter_verbosity_quiet_e,
    kt_tacocat_parameter_verbosity_error_e,
    kt_tacocat_parameter_verbosity_normal_e,
    kt_tacocat_parameter_verbosity_verbose_e,
    kt_tacocat_parameter_verbosity_debug_e,
    kt_tacocat_parameter_version_e,
    kt_tacocat_parameter_line_first_no_e,
    kt_tacocat_parameter_line_last_no_e,

    kt_tacocat_parameter_interval_e,
    kt_tacocat_parameter_max_buffer_e,
    kt_tacocat_parameter_receive_e,
    kt_tacocat_parameter_resolve_e,
    kt_tacocat_parameter_send_e,
  }; // enum

  #define kt_tacocat_console_parameter_t_initialize \
    { \
      macro_fll_program_console_parameter_standard_initialize, \
      \
      macro_f_console_parameter_t_initialize_3(kt_tacocat_short_interval_s, kt_tacocat_long_interval_s, 1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_tacocat_short_max_buffer_s, kt_tacocat_long_max_buffer_s, 1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_tacocat_short_receive_s, kt_tacocat_long_receive_s, 2, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_tacocat_short_resolve_s, kt_tacocat_long_resolve_s, 1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_tacocat_short_send_s, kt_tacocat_long_send_s, 2, f_console_flag_normal_e), \
    }

  #define kt_tacocat_parameter_total_d 18
#endif // _di_kt_tacocat_parameter_e_

/**
 * Flags for fine-tuned print control.
 *
 * kt_tacocat_print_flag_*_e:
 *   - none:    No flags set.
 *   - debug:   Stream is for debug printing.
 *   - error:   Stream is for error printing.
 *   - file:    Stream is associated with a file.
 *   - in:      Stream is a source file.
 *   - message: Stream is for message printing.
 *   - out:     Stream is a destination file.
 *   - warning: Stream is for warning printing.
 */
#ifndef _di_kt_tacocat_print_flag_e_
  enum {
    kt_tacocat_print_flag_none_e    = 0x0,
    kt_tacocat_print_flag_debug_e   = 0x1,
    kt_tacocat_print_flag_error_e   = 0x2,
    kt_tacocat_print_flag_file_e    = 0x4,
    kt_tacocat_print_flag_in_e      = 0x8,
    kt_tacocat_print_flag_message_e = 0x10,
    kt_tacocat_print_flag_out_e     = 0x20,
    kt_tacocat_print_flag_warning_e = 0x40,
  }; // enum
#endif // _di_kt_tacocat_print_flag_e_

/**
 * Individual socket-specific flags for receiving.
 *
 * kt_tacocat_socket_flag_receive_*_e:
 *   - none:          No flags set.
 *   - block_control: Reading and processing the Control block and Size block.
 *   - block_payload: Reading and processing the Payload block.
 */
#ifndef _di_kt_tacocat_socket_flag_receive_e_
  enum {
    kt_tacocat_socket_flag_receive_none_e          = 0x0,
    kt_tacocat_socket_flag_receive_block_control_e = 0x1,
    kt_tacocat_socket_flag_receive_block_payload_e = 0x2,
  }; // enum
#endif // _di_kt_tacocat_socket_flag_receive_e_

/**
 * Individual socket-specific flags for receiving.
 *
 * kt_tacocat_socket_flag_send_*_e:
 *   - none:        No flags set.
 *   - file_open:   File is open.
 *   - file_buffer: File is buffered.
 *   - connect:     The remote address is connected.
 *   - buffer:      Send the buffer.
 *   - buffer_sent: Buffer has been sent.
 */
#ifndef _di_kt_tacocat_socket_flag_send_e_
  enum {
    kt_tacocat_socket_flag_send_none_e        = 0x0,
    kt_tacocat_socket_flag_send_file_open_e   = 0x1,
    kt_tacocat_socket_flag_send_file_buffer_e = 0x2,
    kt_tacocat_socket_flag_send_connect_e     = 0x4,
    kt_tacocat_socket_flag_send_buffer_e      = 0x8,
    kt_tacocat_socket_flag_send_buffer_sent_e = 0x10,
  }; // enum
#endif // _di_kt_tacocat_socket_flag_send_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_common_enumeration_h
