#include "../tacocat.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_tacocat_print_error_
  f_status_t kt_tacocat_print_error(fl_print_t * const print, const f_string_t function) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_error_print(print, F_status_set_fine(((kt_tacocat_main_t *) print->custom)->setting.state.status), function, F_true);

    return F_none;
  }
#endif // _di_kt_tacocat_print_error_

#ifndef _di_kt_tacocat_print_error_file_
  f_status_t kt_tacocat_print_error_file(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_error_file_print(print, F_status_set_fine(((kt_tacocat_main_t *) print->custom)->setting.state.status), function, F_true, name, operation, type);

    return F_none;
  }
#endif // _di_kt_tacocat_print_error_file_

#ifndef _di_kt_tacocat_print_error_parameter_value_resolve_unknown_
  f_status_t kt_tacocat_print_error_parameter_value_resolve_unknown(fl_print_t * const print, const f_string_dynamic_t unknown) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe parameter%] ", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%Q%Q%]", print->to, print->set->notable, f_console_symbol_long_normal_s, kt_tacocat_long_resolve_s, print->set->notable);
    fl_print_format(" %[may only be either '%]", print->to, print->set->error, print->set->error, f_string_eol_s);
    fl_print_format("%[%Q%]", print->to, print->set->notable, kt_tacocat_classic_s, print->set->notable);
    fl_print_format("%' or '%]", print->to, print->set->error, print->set->error, f_string_eol_s);
    fl_print_format("%[%Q%]", print->to, print->set->notable, kt_tacocat_kevux_s, print->set->notable);
    fl_print_format(" %[' but '%]", print->to, print->set->error, print->set->error, f_string_eol_s);
    fl_print_format("%[%Q%]", print->to, print->set->notable, unknown, print->set->notable);
    fl_print_format(" %[' is given.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_kt_tacocat_print_error_parameter_value_resolve_unknown_

#ifndef _di_kt_tacocat_print_error_setting_socket_lengths_must_match_
  f_status_t kt_tacocat_print_error_setting_socket_lengths_must_match(fl_print_t * const print, const f_string_dynamic_t name, const f_number_unsigned_t names, const f_number_unsigned_t files, const f_number_unsigned_t sockets, const f_number_unsigned_t statuss) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe lengths of all%] ", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%Q%]", print->to, print->set->notable, name, print->set->notable);
    fl_print_format(" %[arrays do not have the same length, name array length is '%]", print->to, print->set->error, print->set->error, f_string_eol_s);
    fl_print_format("%[%ul%]", print->to, print->set->notable, names, print->set->notable);
    fl_print_format("%', the file array length is '%]", print->to, print->set->error, print->set->error, f_string_eol_s);
    fl_print_format("%[%ul%]", print->to, print->set->notable, files, print->set->notable);
    fl_print_format(" %[', the socket array length is '%]", print->to, print->set->error, print->set->error, f_string_eol_s);
    fl_print_format("%[%ul%]", print->to, print->set->notable, sockets, print->set->notable);
    fl_print_format(" %[', and the status array length is '%]", print->to, print->set->error, print->set->error, f_string_eol_s);
    fl_print_format("%[%ul%]", print->to, print->set->notable, statuss, print->set->notable);
    fl_print_format(" %['.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_kt_tacocat_print_error_setting_socket_lengths_must_match_

#ifdef __cplusplus
} // extern "C"
#endif
