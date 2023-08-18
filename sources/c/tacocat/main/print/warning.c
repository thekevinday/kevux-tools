#include "../tacocat.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_print_warning_setting_boolean_may_only_be_
  f_status_t kt_tacocat_print_warning_port_number_overflow(fl_print_t * const print, const f_string_static_t address, const f_number_unsigned_t port) {

    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe port number '%]", print->to, print->context, print->prefix, print->context);
    fl_print_format("%[%ul%]", print->to, print->notable, port, print->notable);
    fl_print_format("%[' from the address '%]", print->to, print->context, print->context);
    fl_print_format("%[%Q%]", print->to, print->notable, address, print->notable);
    fl_print_format("%['is too large for this system and so the port is being autodetermined.%]%r", print->to, print->context, print->context, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fake_build_print_warning_setting_boolean_may_only_be_

#ifdef __cplusplus
} // extern "C"
#endif
