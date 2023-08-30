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

        for (j = 0; j < sets[i]->files.used ; ++j) {
          f_file_close(&sets[i]->files.array[j]);
        } // for

        for (j = 0; j < sets[i]->sockets.used ; ++j) {
          f_socket_disconnect(&sets[i]->sockets.array[j], program.signal_received ? f_socket_close_fast_e : f_socket_close_read_write_e);
        } // for

        f_memory_array_resize(0, sizeof(uint16_t), (void **) &sets[i]->flags.array, &sets[i]->flags.used, &sets[i]->flags.size);
        f_memory_array_resize(0, sizeof(f_file_t), (void **) &sets[i]->files.array, &sets[i]->files.used, &sets[i]->files.size);
        f_memory_array_resize(0, sizeof(f_poll_t), (void **) &sets[i]->polls.array, &sets[i]->polls.used, &sets[i]->polls.size);
        f_memory_array_resize(0, sizeof(f_socket_t), (void **) &sets[i]->sockets.array, &sets[i]->sockets.used, &sets[i]->sockets.size);
        f_memory_array_resize(0, sizeof(f_status_t), (void **) &sets[i]->statuss.array, &sets[i]->statuss.used, &sets[i]->statuss.size);
        f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &sets[i]->names.array, &sets[i]->names.used, &sets[i]->names.size, &f_string_dynamics_delete_callback);
        f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &sets[i]->buffers.array, &sets[i]->buffers.used, &sets[i]->buffers.size, &f_string_dynamics_delete_callback);
        f_memory_array_resize(0, sizeof(f_fss_simple_packet_range_t), (void **) &sets[i]->packets.array, &sets[i]->packets.used, &sets[i]->packets.size);
      } // for
    }

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->buffer.string, &setting->buffer.used, &setting->buffer.size);

    return F_okay;
  }
#endif // _di_kt_tacocat_setting_delete_

#ifndef _di_kt_tacocat_thread_delete_
  f_status_t kt_tacocat_thread_delete(const fll_program_data_t program, kt_tacocat_thread_t * const thread) {

    if (!thread) return F_status_set_error(F_parameter);

    return F_okay;
  }
#endif // _di_kt_tacocat_thread_delete_

#ifdef __cplusplus
} // extern "C"
#endif
