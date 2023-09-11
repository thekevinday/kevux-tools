#include "../tacocat.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_tacocat_print_message_help_
  f_status_t kt_tacocat_print_message_help(fl_print_t * const print, const f_color_context_t context) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    kt_tacocat_main_t * const main = (kt_tacocat_main_t *) print->custom;

    f_file_stream_lock(print->to);

    fll_program_print_help_header(print, kt_tacocat_program_name_long_s, kt_tacocat_program_version_s);

    fll_program_print_help_option_standard(print);

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_option(print, kt_tacocat_short_interval_s, kt_tacocat_long_interval_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "  Specify a custom poll interval in milliseconds to use.");
    fll_program_print_help_option(print, kt_tacocat_short_max_buffer_s, kt_tacocat_long_max_buffer_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "Specify a maximum buffer size to allow (in bytes) when receiving packets.");
    fll_program_print_help_option(print, kt_tacocat_short_receive_s, kt_tacocat_long_receive_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "   Specify an address or socket file to listen to and a file to write to.");
    fll_program_print_help_option(print, kt_tacocat_short_resolve_s, kt_tacocat_long_resolve_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "   Specify a custom DNS resolution methodology.");
    fll_program_print_help_option(print, kt_tacocat_short_send_s, kt_tacocat_long_send_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "      Specify an address or socket file send transmit to and a file to read from.");

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_usage(print, kt_tacocat_program_name_s, f_string_empty_s);

    fl_print_format("%r  The parameter '%[%r%r%]' may be set to ", print->to, f_string_eol_s, context.set.notable, f_console_symbol_long_normal_s, kt_tacocat_long_max_buffer_s, context.set.notable);
    fl_print_format("%[-1%] to disable the maximum buffer size limit on receive.%r%r", print->to, context.set.notable, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("%r  The parameters '%[%r%r%]', ", print->to, f_string_eol_s, context.set.notable, f_console_symbol_long_normal_s, kt_tacocat_long_receive_s, context.set.notable);
    fl_print_format("'%[%r%r%]' ", print->to, context.set.notable, f_console_symbol_long_normal_s, kt_tacocat_long_send_s, context.set.notable);
    fl_print_format("may either represent a network address or a local socket file.%r%r", print->to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The %[%r%r%] and the ", print->to, print->set->notable, f_console_symbol_long_normal_s, kt_tacocat_long_receive_s, print->set->notable);
    fl_print_format("%[%r%r%] options require 2 additional parameters:", print->to, print->set->notable, f_console_symbol_long_normal_s, kt_tacocat_long_send_s, print->set->notable);
    fl_print_format(" %[<%]%r%[>%]", print->to, print->set->notable, print->set->notable, kt_tacocat_network_or_socket_s, print->set->notable, print->set->notable);
    fl_print_format(" %[<%]%r%[>%].%r", print->to, print->set->notable, print->set->notable, kt_tacocat_file_s, print->set->notable, print->set->notable, f_string_eol_s);

    fl_print_format("    %[%r%]: The network address or the socket file to use.%r", print->to, print->set->notable, kt_tacocat_network_or_socket_s, print->set->notable, f_string_eol_s);
    fl_print_format("    %[%r%]: The local file to use to read from or to write to.%r%r", print->to, print->set->notable, kt_tacocat_file_s, print->set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  A local socket file must begin with an absolute path like '%[/var/www.example.com%]' and ", print->to, context.set.notable, context.set.notable);
    fl_print_format("'%[/var/example.socket%]', or it must begin with a relative absolute path, like ", print->to, context.set.notable, context.set.notable);
    fl_print_format("'%[./www.example.com%]' and %[./example.socket%].%r%r", print->to, context.set.notable, context.set.notable, context.set.notable, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  Any address that does not begin with either a single slash '%[/%]' (%[U+002F%])' or ", print->to, context.set.notable, context.set.notable, context.set.notable, context.set.notable);
    fl_print_format("a dot and a single slash '%[./%]' and (%[U+002E%]) ", print->to, context.set.notable, context.set.notable, context.set.notable, context.set.notable);
    fl_print_format("(%[U+002F%]) is considered a network address.%r", print->to, context.set.notable, context.set.notable, f_string_eol_s);

    f_file_stream_flush(print->to);
    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_kt_tacocat_print_message_help_

#ifndef _di_kt_tacocat_print_message_receive_operation_complete_
  f_status_t kt_tacocat_print_message_receive_operation_complete(fl_print_t * const print, const kt_tacocat_socket_set_t set) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("Packet from ", print->to);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->notable, set.network, print->set->notable);
    fl_print_format(" is complete.%r", print->to, f_string_eol_s);

    f_file_stream_unlock(print->to);
  }
#endif // _di_kt_tacocat_print_message_receive_operation_complete_

#ifndef _di_kt_tacocat_print_message_receive_operation_control_size_
  f_status_t kt_tacocat_print_message_receive_operation_control_size(fl_print_t * const print, const kt_tacocat_socket_set_t set) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("Packet from ", print->to);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->notable, set.network, print->set->notable);
    fl_print_format(" is %[%ul%] Bytes.%r", print->to, print->set->notable, set.packet.size, print->set->notable, f_string_eol_s);

    f_file_stream_unlock(print->to);
  }
#endif // _di_kt_tacocat_print_message_receive_operation_control_size_

#ifndef _di_kt_tacocat_print_message_receive_operation_received_
  f_status_t kt_tacocat_print_message_receive_operation_received(fl_print_t * const print, const kt_tacocat_socket_set_t set) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%rReceived packet from ", print->to, f_string_eol_s);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->notable, set.network, print->set->notable);

    if (print->verbosity > f_console_verbosity_normal_e) {
      fl_print_format(" (appending to file '", print->to);
      fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->notable, set.name, print->set->notable);
      fl_print_format("')", print->to);
    }

    fl_print_format(".%r", print->to, f_string_eol_s);

    f_file_stream_unlock(print->to);
  }
#endif // _di_kt_tacocat_print_message_receive_operation_received_

#ifdef __cplusplus
} // extern "C"
#endif
