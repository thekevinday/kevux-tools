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

    fll_program_print_help_option(print, kt_tacocat_short_background_s, kt_tacocat_long_background_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "Run this program in the background.");
    fll_program_print_help_option(print, kt_tacocat_short_from_s, kt_tacocat_long_from_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "      Specify an address or socket file to listen to.");
    fll_program_print_help_option(print, kt_tacocat_short_pid_s, kt_tacocat_long_pid_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "       Enable the use of a PID file.");
    fll_program_print_help_option(print, kt_tacocat_short_pid_name_s, kt_tacocat_long_pid_name_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "  Specify a custom PID file name, without the '.pid' extension.");
    fll_program_print_help_option(print, kt_tacocat_short_pid_path_s, kt_tacocat_long_pid_path_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "  Specify a custom directory path where the PID file is located.");
    fll_program_print_help_option(print, kt_tacocat_short_resolve_s, kt_tacocat_long_resolve_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "   Specify a custom DNS resolution methodology.");
    fll_program_print_help_option(print, kt_tacocat_short_to_s, kt_tacocat_long_to_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "        Specify an address or socket file to transmit to.");

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_usage(print, kt_tacocat_program_name_s, kt_tacocat_program_help_parameters_s);

    fl_print_format("%r  The parameters '%[%r%r%]', ", print->to, f_string_eol_s, context.set.notable, f_console_symbol_long_normal_s, kt_tacocat_long_from_s, context.set.notable);
    fl_print_format("'%[%r%r%]' ", print->to, context.set.notable, f_console_symbol_long_normal_s, kt_tacocat_long_to_s, context.set.notable);
    fl_print_format("may either represent a network address or a local socket file.%r%r", print->to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  A local socket file must begin with an absolute path like '%[/var/www.example.com%]' and ", print->to, context.set.notable, context.set.notable);
    fl_print_format("'%[/var/example.socket%]', or it must begin with a relative absolute path, like ", print->to, context.set.notable, context.set.notable);
    fl_print_format("'%[./www.example.com%]' and %[./example.socket%].%r%r", print->to, context.set.notable, context.set.notable, context.set.notable, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  Any address that does not begin with either a single slash '%[/%]' (%[U+002F%])' or ", print->to, context.set.notable, context.set.notable, context.set.notable, context.set.notable);
    fl_print_format("a dot and a single slash '%[./%]' and (%[U+002E%]) ", print->to, context.set.notable, context.set.notable, context.set.notable, context.set.notable);
    fl_print_format("(%[U+002F%]) is considered a network address.%r%r", print->to, context.set.notable, context.set.notable, f_string_eol_s, f_string_eol_s);

    f_file_stream_flush(print->to);
    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_kt_tacocat_print_message_help_

#ifdef __cplusplus
} // extern "C"
#endif
