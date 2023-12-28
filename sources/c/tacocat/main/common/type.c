#include "../tacocat.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_tacocat_cache_delete_
  void kt_tacocat_cache_delete(kt_tacocat_cache_t * const cache) {

    if (!cache) return;

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &cache->buffer.string, &cache->buffer.used, &cache->buffer.size);
  }
#endif // _di_kt_tacocat_cache_delete_

#ifndef _di_kt_tacocat_main_delete_
  void kt_tacocat_main_delete(kt_tacocat_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);
    kt_tacocat_cache_delete(&main->cache);
    kt_tacocat_setting_delete(&main->setting);
  }
#endif // _di_kt_tacocat_main_delete_

#ifndef _di_kt_tacocat_setting_delete_
  void kt_tacocat_setting_delete(kt_tacocat_setting_t * const setting) {

    if (!setting) return;

    f_memory_array_resize(0, sizeof(f_poll_t), (void **) &setting->receive_polls.array, &setting->receive_polls.used, &setting->receive_polls.size);
    f_memory_array_resize(0, sizeof(f_poll_t), (void **) &setting->send_polls.array, &setting->send_polls.used, &setting->send_polls.size);

    f_memory_arrays_resize(0, sizeof(kt_tacocat_socket_set_t), (void **) &setting->receive.array, &setting->receive.used, &setting->receive.size, &kt_tacocat_socket_sets_delete_callback);
    f_memory_arrays_resize(0, sizeof(kt_tacocat_socket_set_t), (void **) &setting->send.array, &setting->send.used, &setting->send.size, &kt_tacocat_socket_sets_delete_callback);
  }
#endif // _di_kt_tacocat_setting_delete_

#ifndef _di_kt_tacocat_socket_sets_delete_callback_
  f_status_t kt_tacocat_socket_sets_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      kt_tacocat_socket_set_t * const array = (kt_tacocat_socket_set_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        f_file_close(&array[i].file);
        f_file_close_id(&array[i].socket.id_data);
        f_socket_disconnect(&array[i].socket, f_socket_close_fast_e);

        if (array[i].objects.size) {
          f_memory_array_resize(0, sizeof(f_range_t), (void **) &array[i].objects.array, &array[i].objects.used, &array[i].objects.size);
        }

        if (array[i].contents.size) {
          f_memory_arrays_resize(0, sizeof(f_range_t), (void **) &array[i].contents.array, &array[i].contents.used, &array[i].contents.size, &f_rangess_delete_callback);
        }

        if (array[i].objects_delimits.size) {
          f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &array[i].objects_delimits.array, &array[i].objects_delimits.used, &array[i].objects_delimits.size);
        }

        if (array[i].objects_delimits.size) {
          f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &array[i].contents_delimits.array, &array[i].contents_delimits.used, &array[i].contents_delimits.size);
        }

        if (array[i].comments.size) {
          f_memory_array_resize(0, sizeof(f_range_t), (void **) &array[i].comments.array, &array[i].comments.used, &array[i].comments.size);
        }

        if (array[i].buffer.size) {
          f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].buffer.string, &array[i].buffer.used, &array[i].buffer.size);
        }

        if (array[i].cache.size) {
          f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].cache.string, &array[i].cache.used, &array[i].cache.size);
        }

        if (array[i].client.size) {
          f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].client.string, &array[i].client.used, &array[i].client.size);
        }

        if (array[i].header.size) {
          f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].header.string, &array[i].header.used, &array[i].header.size);
        }

        if (array[i].name.size) {
          f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].name.string, &array[i].name.used, &array[i].name.size);
        }

        if (array[i].network.size) {
          f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].network.string, &array[i].network.used, &array[i].network.size);
        }

        if (array[i].abstruses.size) {
          f_memory_arrays_resize(0, sizeof(f_abstruse_map_t), (void **) &array[i].abstruses.array, &array[i].abstruses.used, &array[i].abstruses.size, &f_abstruse_maps_delete_callback);
        }

        if (array[i].headers.size) {
          f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &array[i].headers.array, &array[i].headers.used, &array[i].headers.size, &f_string_maps_delete_callback);
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_kt_tacocat_socket_sets_delete_callback_

#ifdef __cplusplus
} // extern "C"
#endif
