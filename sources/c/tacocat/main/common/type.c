#include "../tacocat.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_tacocat_main_delete_
  void kt_tacocat_main_delete(kt_tacocat_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);
    kt_tacocat_setting_delete(&main->setting);
  }
#endif // _di_kt_tacocat_main_delete_

#ifndef _di_kt_tacocat_setting_delete_
  f_status_t kt_tacocat_setting_delete(kt_tacocat_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    f_file_close(&setting->pid_file);

    f_number_unsigned_t i = 0;

    for (; i < setting->file_froms.used ; ++i) {
      f_file_close(&setting->file_froms.array[i]);
    } // for

    for (; i < setting->file_tos.used ; ++i) {
      f_file_close(&setting->file_tos.array[i]);
    } // for

    f_string_dynamic_resize(0, &setting->buffer);
    f_string_dynamic_resize(0, &setting->pid_path);
    f_string_dynamic_resize(0, &setting->pid_name);
    f_string_dynamics_resize(0, &setting->froms);
    f_string_dynamics_resize(0, &setting->tos);

    return F_none;
  }
#endif // _di_kt_tacocat_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif
