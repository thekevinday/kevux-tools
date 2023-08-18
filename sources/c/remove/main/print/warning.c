#include "../remove.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_remove_print_warning_file_reason_
  f_status_t remove_print_warning_file_reason(fl_print_t * const print, const f_string_static_t path, const f_string_static_t reason) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);

    kt_remove_main_t * const main = (kt_remove_main_t *) print->custom;

    if (print->verbosity < f_console_verbosity_verbose_e && !(main->setting.flag & kt_remove_main_flag_force_e)) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QUnable to remove file '%]", print->to, print->set->warning, print->prefix, print->set->warning);
    fl_print_format("%[%Q%]", print->to, print->set->notable, path, print->set->notable);
    fl_print_format("%[', %Q.%]%r", print->to, print->set->warning, reason, print->set->warning, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_kt_remove_print_warning_file_reason_

#ifdef __cplusplus
} // extern "C"
#endif
