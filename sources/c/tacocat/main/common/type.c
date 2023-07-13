#include "../tacocat.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_tacocat_main_delete_
  void kt_tacocat_main_delete(kt_tacocat_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);
    kt_tacocat_setting_delete(main->program, &main->setting);
    kt_tacocat_thread_delete(main->program, &main->thread);
  }
#endif // _di_kt_tacocat_main_delete_

#ifndef _di_kt_tacocat_setting_delete_
  f_status_t kt_tacocat_setting_delete(const fll_program_data_t program, kt_tacocat_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    {
      f_number_unsigned_t j = 0;

      kt_tacocat_socket_set_t * const sets[] = {
        &setting->receive,
        &setting->send,
      };

      for (uint8_t i = 0; i < 2; ++i) {

        for (; j < sets[i]->files.used ; ++j) {
          f_file_close(&sets[i]->files.array[j]);
        } // for

        for (; j < sets[i]->sockets.used ; ++j) {
          f_socket_disconnect(&sets[i]->sockets.array[j], program.signal_received ? f_socket_close_fast_e : f_socket_close_read_write_e);
        } // for

        f_files_resize(0, &sets[i]->files);
        f_polls_resize(0, &sets[i]->polls);
        f_sockets_resize(0, &sets[i]->sockets);
        f_statuss_resize(0, &sets[i]->statuss);

        f_string_dynamics_resize(0, &sets[i]->names);
        f_string_dynamics_resize(0, &sets[i]->buffers);
      } // for
    }

    f_string_dynamic_resize(0, &setting->buffer);

    return F_none;
  }
#endif // _di_kt_tacocat_setting_delete_

#ifndef _di_kt_tacocat_thread_delete_
  f_status_t kt_tacocat_thread_delete(const fll_program_data_t program, kt_tacocat_thread_t * const thread) {

    if (!thread) return F_status_set_error(F_parameter);

    return F_none;
  }
#endif // _di_kt_tacocat_thread_delete_

#ifdef __cplusplus
} // extern "C"
#endif
