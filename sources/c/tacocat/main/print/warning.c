#include "../tacocat.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_tacocat_print_warning_on_busy_
  f_status_t kt_tacocat_print_warning_on_busy(fl_print_t * const print, f_string_static_t on, const f_string_static_t network, const f_number_unsigned_t retry) {

    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QNetwork on%] ", print->to, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->notable, on, print->set->notable);
    fl_print_format(" %[for '%]", print->to, print->context, print->context, f_string_eol_s);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->notable, network, print->set->notable);
    fl_print_format("%[' is busy, pausing and then retrying %ul/%ul.%]%r", print->to, print->context, retry, kt_tacocat_startup_retry_max_d, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_kt_tacocat_print_warning_on_busy_

#ifndef _di_kt_tacocat_print_warning_on_client_closed_
  f_status_t kt_tacocat_print_warning_on_client_closed(fl_print_t * const print, f_string_static_t on, const f_string_static_t network) {

    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QNetwork on%] ", print->to, print->context, print->prefix, print->context);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->notable, on, print->set->notable);
    fl_print_format(" %[for '%]", print->to, print->context, print->context, f_string_eol_s);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->notable, network, print->set->notable);
    fl_print_format("%[' closed by the client.%]%r", print->to, print->context, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_kt_tacocat_print_warning_on_client_closed_

#ifndef _di_kt_tacocat_print_warning_on_file_
  f_status_t kt_tacocat_print_warning_on_file(fl_print_t * const print, const f_string_t function, f_string_static_t on, const f_string_static_t network, const f_status_t status, const f_string_static_t name, const f_string_static_t operation) {

    if (!print || !print->custom) return F_status_set_warning(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QNetwork on%] ", print->to, print->set->warning, print->prefix, print->set->warning);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->notable, on, print->set->notable);
    fl_print_format(" %[for '%]", print->to, print->set->warning, print->set->warning, f_string_eol_s);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->notable, network, print->set->notable);
    fl_print_format("%[' failed to write to file '%]", print->to, print->set->warning, print->set->warning, f_string_eol_s);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->notable, name, print->set->notable);
    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->set->warning, print->set->warning, f_string_eol_s);

    f_file_stream_unlock(print->to);

    fll_error_file_print(print, F_status_set_fine(((kt_tacocat_main_t *) print->custom)->setting.state.status), function, F_true, name, operation, fll_error_file_type_file_e);
  }
#endif // _di_kt_tacocat_print_warning_on_file_

#ifndef _di_kt_tacocat_print_warning_parameter_integer_less_than_
  f_status_t kt_tacocat_print_warning_parameter_integer_less_than(fl_print_t * const print, const f_string_static_t symbol, const f_string_static_t name, const f_string_static_t is) {

    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe value '%]", print->to, print->context, print->context);
    fl_print_format(f_string_format_QQ_single_s.string, print->to, print->set->notable, is, print->set->notable);
    fl_print_format("%[' for the parameter '%]", print->to, print->context, print->context);
    fl_print_format(f_string_format_QQ_single_s.string, print->to, print->set->notable, symbol, name, print->set->notable);
    fl_print_format("%[' is less than %]", print->to, print->context, print->context);
    fl_print_format("%[%ul%]", print->to, print->notable, kt_tacocat_packet_peek_d, print->notable);
    fl_print_format(f_string_format_sentence_end_s.string, print->to, print->context, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_kt_tacocat_print_warning_parameter_integer_less_than_

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
