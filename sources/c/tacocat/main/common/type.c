#include "../tacocat.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_tacocat_main_delete_
  void kt_tacocat_main_delete(kt_tacocat_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);
    kt_tacocat_setting_delete(main->program, &main->setting);
  }
#endif // _di_kt_tacocat_main_delete_

#ifndef _di_kt_tacocat_setting_delete_
  f_status_t kt_tacocat_setting_delete(const fll_program_data_t program, kt_tacocat_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    f_number_unsigned_t i = 0;

    for (; i < setting->file_receives.used ; ++i) {
      f_file_close(&setting->file_receives.array[i]);
    } // for

    for (; i < setting->file_sends.used ; ++i) {
      f_file_close(&setting->file_sends.array[i]);
    } // for

    for (; i < setting->socket_receives.used ; ++i) {
      f_socket_disconnect(&setting->socket_receives.array[i], program.signal_received ? f_socket_close_fast_e : f_socket_close_read_write_e);
    } // for

    for (; i < setting->socket_sends.used ; ++i) {
      f_socket_disconnect(&setting->socket_sends.array[i], program.signal_received ? f_socket_close_fast_e : f_socket_close_read_write_e);
    } // for

    f_files_resize(0, &setting->file_receives);
    f_files_resize(0, &setting->file_sends);

    f_sockets_resize(0, &setting->socket_receives);
    f_sockets_resize(0, &setting->socket_sends);

    f_statuss_resize(0, &setting->status_receives);
    f_statuss_resize(0, &setting->status_sends);

    f_string_dynamics_resize(0, &setting->receives);
    f_string_dynamics_resize(0, &setting->sends);

    f_string_dynamic_resize(0, &setting->buffer);

    return F_none;
  }
#endif // _di_kt_tacocat_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif
