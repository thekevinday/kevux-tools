#include "../remove.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_remove_main_delete_
  void kt_remove_main_delete(kt_remove_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);
    kt_remove_setting_delete(&main->setting);
  }
#endif // _di_kt_remove_main_delete_

#ifndef _di_kt_remove_setting_delete_
  f_status_t kt_remove_setting_delete(kt_remove_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    f_string_dynamic_resize(0, &setting->buffer);
    f_string_dynamics_resize(0, &setting->files);

    kt_remove_dates_resize(0, &setting->accessed);
    kt_remove_dates_resize(0, &setting->changed);
    kt_remove_dates_resize(0, &setting->updated);
    kt_remove_modes_resize(0, &setting->modes);

    f_uint32s_resize(0, &setting->groups);
    f_uint32s_resize(0, &setting->users);

    f_directory_recurse_do_delete(&setting->recurse);

    return F_none;
  }
#endif // _di_kt_remove_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif
