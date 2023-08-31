#include "../tacocat.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_tacocat_print_warning_parameter_integer_is_
  f_status_t kt_tacocat_print_warning_parameter_integer_is(fl_print_t * const print, const f_string_static_t symbol, const f_string_static_t name, const f_string_static_t is) {

    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe value for the parameter '%]", print->to, print->set->error, print->set->error);
    fl_print_format(f_string_format_QQ_single_s.string, print->to, print->set->notable, symbol, name, print->set->notable);
    fl_print_format("%[' is %]", print->to, print->set->error, print->set->error);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->notable, is, print->set->notable);
    fl_print_format(f_string_format_sentence_end_s.string, print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_kt_tacocat_print_warning_parameter_integer_is_

#ifndef _di_kt_tacocat_print_warning_port_number_overflow_
  f_status_t kt_tacocat_print_warning_port_number_overflow(fl_print_t * const print, const f_string_static_t address, const f_number_unsigned_t port) {

    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe port number '%]", print->to, print->context, print->prefix, print->context);
    fl_print_format("%[%ul%]", print->to, print->notable, port, print->notable);
    fl_print_format("%[' from the address '%]", print->to, print->context, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->notable, address, print->notable);
    fl_print_format("%['is too large for this system and so the port is being autodetermined.%]%r", print->to, print->context, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_kt_tacocat_print_warning_port_number_overflow_

#ifdef __cplusplus
} // extern "C"
#endif
