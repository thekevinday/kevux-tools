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

#ifdef __cplusplus
} // extern "C"
#endif
