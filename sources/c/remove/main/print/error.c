#include "../remove.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_remove_print_error_
  f_status_t kt_remove_print_error(fl_print_t * const print, const f_string_t function) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_error_print(print, F_status_set_fine(((kt_remove_main_t *) print->custom)->setting.state.status), function, F_true);

    return F_okay;
  }
#endif // _di_kt_remove_print_error_

#ifndef _di_kt_remove_print_error_file_
  f_status_t kt_remove_print_error_file(fl_print_t * const print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_error_file_print(print, F_status_set_fine(((kt_remove_main_t *) print->custom)->setting.state.status), function, F_true, name, operation, type);

    return F_okay;
  }
#endif // _di_kt_remove_print_error_file_

#ifndef _di_kt_remove_print_error_parameter_missing_value_requires_amount_
  f_status_t kt_remove_print_error_parameter_missing_value_requires_amount(fl_print_t * const print, const f_string_static_t symbol, const f_string_static_t parameter, const f_number_unsigned_t amount) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe parameter%] ", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%Q%Q%]", print->to, print->set->notable, symbol, parameter, print->set->notable);
    fl_print_format("%[ is specified, but%] ", print->to, print->set->error, print->set->error);
    fl_print_format("%[%un%]", print->to, print->set->notable, amount, print->set->notable);
    fl_print_format(" %[values are not given.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_kt_remove_print_error_parameter_missing_value_requires_amount_

#ifndef _di_kt_remove_print_error_parameter_no_files_
  f_status_t kt_remove_print_error_parameter_no_files(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_print_format("%[%QNo files have been specified to be removed.%]%r", print->to, print->set->error, print->prefix, print->set->error, f_string_eol_s);

    return F_okay;
  }
#endif // _di_kt_remove_print_error_parameter_no_files_

#ifndef _di_kt_remove_print_error_recursion_max_
  f_status_t kt_remove_print_error_recursion_max(fl_print_t * const print, const f_string_static_t path) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    kt_remove_main_t *main = (kt_remove_main_t *) print->custom;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QMax recursion of", print->to, print->set->error, print->prefix, print->set->error, f_string_eol_s);
    fl_print_format("%[%ul%]", print->to, print->set->notable, main->setting.recurse.depth_max, print->set->notable);
    fl_print_format(" at '%[%Q%]'.%]%r", print->to, print->set->notable, path, print->set->notable, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_kt_remove_print_error_recursion_max_

#ifndef _di_kt_remove_print_error_parameter_unknown_value_
  f_status_t kt_remove_print_error_parameter_unknown_value(fl_print_t * const print, const f_string_static_t symbol, const f_string_static_t parameter, const f_string_static_t value) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe parameter%] ", print->to, print->set->error, print->prefix, print->set->error);
    fl_print_format("%[%Q%Q%]", print->to, print->set->notable, symbol, parameter, print->set->notable);
    fl_print_format("%[ is passed an unknown value '%]", print->to, print->set->error, print->set->error);
    fl_print_format("%[%Q%]", print->to, print->set->notable, value, print->set->notable);
    fl_print_format("%['.%]%r", print->to, print->set->error, print->set->error, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_kt_remove_print_error_parameter_unknown_value_

#ifdef __cplusplus
} // extern "C"
#endif
