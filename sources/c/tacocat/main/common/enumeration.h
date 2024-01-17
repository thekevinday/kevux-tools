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
 * Types of packets.
 *
 * kt_tacocat_packet_type_*_e:
 *   - none:   No type is set.
 *   - abort:  The packet is designates that the connection is to be aborted.
 *   - done:   The package acknowledges the receipt of a packet.
 *   - file:   The packet is a file.
 *   - next:   The packet is a request for the next file.
 *   - resend: The packet is a request to resend the given part number.
 */
#ifndef _di_kt_tacocat_packet_type_e_
  enum {
    kt_tacocat_packet_type_none_e   = 0x0,
    kt_tacocat_packet_type_abort_e  = 0x1,
    kt_tacocat_packet_type_done_e   = 0x2,
    kt_tacocat_packet_type_file_e   = 0x4,
    kt_tacocat_packet_type_next_e   = 0x8,
    kt_tacocat_packet_type_resend_e = 0x10,
  }; // enum
#endif // _di_kt_tacocat_packet_type_e_

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
 * Socket related flags, such as designating handling of error packet.
 *
 * kt_tacocat_socket_flag_*_e:
 *   - none:   No flags set.
 *   - abort:  Abort connection.
 *   - done:   Send packet confirming that everything is done.
 *   - listen: Listen for a response to a previously sent connection.
 *   - next:   Request or Send next packet for existing connection.
 *   - resend: Send packet for requesting a re-send of the previous packet.
 */
#ifndef _di_kt_tacocat_socket_flag_e_
  enum {
    kt_tacocat_socket_flag_none_e   = 0,
    kt_tacocat_socket_flag_abort_e  = 0x1,
    kt_tacocat_socket_flag_done_e   = 0x2,
    kt_tacocat_socket_flag_listen_e = 0x4,
    kt_tacocat_socket_flag_next_e   = 0x8,
    kt_tacocat_socket_flag_resend_e = 0x10,
  }; // enum
#endif // _di_kt_tacocat_socket_flag_e_

/**
 * Individual socket-specific steps for receiving.
 *
 * kt_tacocat_socket_step_receive_*_e:
 *   - none:    No flags set.
 *   - control: Reading and processing the Control block and Size block.
 *   - packet:  Reading and processing the rest of the Packet block (the Header and Payload sections).
 *   - find:    Find the Header section and everything else up until the Payload section.
 *   - extract: Process the loaded data, extracting the Header and Signature sections.
 *   - check:   Check the loaded data, doing size checks, interpreting the status, and performing any signature checks.
 *   - write:   Save the loaded Payload block to the file (write to the file).
 *   - next:    Send "next" or "done" packet.
 *   - done:    Done processing file.
 */
#ifndef _di_kt_tacocat_socket_step_receive_e_
  enum {
    kt_tacocat_socket_step_receive_none_e = 0,
    kt_tacocat_socket_step_receive_control_e,
    kt_tacocat_socket_step_receive_packet_e,
    kt_tacocat_socket_step_receive_find_e,
    kt_tacocat_socket_step_receive_extract_e,
    kt_tacocat_socket_step_receive_check_e,
    kt_tacocat_socket_step_receive_write_e,
    kt_tacocat_socket_step_receive_next_e,
    kt_tacocat_socket_step_receive_done_e,
  }; // enum
#endif // _di_kt_tacocat_socket_step_receive_e_

/**
 * Individual socket-specific steps for receiving.
 *
 * kt_tacocat_socket_step_send_*_e:
 *   - none:     No flags set.
 *   - size:     Determine the file size.
 *   - header:   Build and buffer the header.
 *   - build:    Build the header information.
 *   - file:     Buffer the file.
 *   - check:    Additional checks before sending, such as re-checking header size.
 *   - encode:   Encode entire packet.
 *   - packet:   Send the packet.
 *   - response: Wait for a response packet from the opposite end.
 *   - done:     The entire Packet is sent.
 */
#ifndef _di_kt_tacocat_socket_step_send_e_
  enum {
    kt_tacocat_socket_step_send_none_e = 0,
    kt_tacocat_socket_step_send_size_e,
    kt_tacocat_socket_step_send_header_e,
    kt_tacocat_socket_step_send_build_e,
    kt_tacocat_socket_step_send_file_e,
    kt_tacocat_socket_step_send_check_e,
    kt_tacocat_socket_step_send_encode_e,
    kt_tacocat_socket_step_send_packet_e,
    kt_tacocat_socket_step_send_wait_e,
    kt_tacocat_socket_step_send_done_e,
  }; // enum
#endif // _di_kt_tacocat_socket_step_send_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_common_enumeration_h
