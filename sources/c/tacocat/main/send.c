#include "tacocat.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_tacocat_send_
  void * kt_tacocat_send(void * const void_main) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    if (!void_main) return 0;

    kt_tacocat_main_t * const main = (kt_tacocat_main_t *) void_main;
    f_number_unsigned_t i = 0;
    f_status_t ready = F_okay;

    kt_tacocat_process_socket_set_send(main);

    if (F_status_is_error_not(main->setting.status_send) && main->setting.send.used) {
      do {
        ready = F_okay;

        for (i = 0; i < main->setting.send.used; ++i) {

          if (main->program.signal_received) {
            main->setting.status_send = F_status_set_error(F_interrupt);

            return 0;
          }

          if (main->setting.send.array[i].status == F_done) {
            if (ready != F_done_not) {
              ready = F_done;
            }
          }
          else {
            if (kt_tacocat_send_process(main, &main->setting.send.array[i]) == F_done) {
              if (ready != F_done_not) {
                ready = F_done;
              }
            }
            else {
              ready = F_done_not;
            }
          }
        } // for

      } while (F_status_is_error_not(main->setting.status_send) && ready == F_done_not);
    }

    kt_tacocat_process_socket_sets_disconnect(main, &main->setting.send);

    kt_tacocat_process_socket_sets_error_handle(main, main->setting.send, &main->setting.status_send);

    if (F_status_is_error_not(main->setting.status_send)) {
      main->setting.status_send = F_okay;
    }

    return 0;
  }
#endif // _di_kt_tacocat_send_

#ifndef _di_kt_tacocat_send_process_
  f_status_t kt_tacocat_send_process(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set) {

    if (!main || !set) return F_status_set_error(F_parameter);

    // @todo this needs a max retries for sending without error, possibly resetting depending on the part (flag).

    if (!set->flag) {
      set->size_done = 0;

      set->status = f_file_open(set->name, F_file_mode_all_r_d, &set->file);

      if (F_status_is_error(set->status)) {
        kt_tacocat_print_error_on_file(&main->program.error, macro_kt_tacocat_f(f_file_open), kt_tacocat_send_s, set->network, set->status, set->name, f_file_operation_open_s);

        return F_done_not;
      }

      set->flag = kt_tacocat_socket_flag_send_file_open_e;
    }

    if (set->flag == kt_tacocat_socket_flag_send_file_open_e) {
      set->buffer.used = 0;

      // Make sure the buffer is large enough for the file block reads (including a space for a terminating NULL).
      set->status = f_memory_array_increase_by(set->file.size_read + 1, sizeof(f_char_t), (void **) &set->buffer.string, &set->buffer.used, &set->buffer.size);
      macro_kt_send_process_handle_error_exit_1(main, f_memory_array_increase_by, set->network, set->status, set->flag);

      set->status = f_file_read_block(set->file, &set->buffer);
      macro_kt_send_process_handle_error_exit_1(main, f_file_read_block, set->network, set->status, set->flag);

      if (set->buffer.used) {
        set->status = f_string_dynamic_terminate_after(&set->buffer);
        macro_kt_send_process_handle_error_exit_1(main, f_string_dynamic_terminate_after, set->network, set->status, set->flag);

        set->flag = kt_tacocat_socket_flag_send_file_buffer_e;
      }
      else {

        // File is empty, nothing left to send.
        set->flag = kt_tacocat_socket_flag_send_buffer_sent_e;
      }
    }

    if (set->flag == kt_tacocat_socket_flag_send_file_buffer_e) {
      set->status = f_socket_connect(set->socket);
      macro_kt_send_process_handle_error_exit_1(main, f_socket_connect, set->network, set->status, set->flag);

      set->flag = kt_tacocat_socket_flag_send_connect_e;
    }

    if (set->flag == kt_tacocat_socket_flag_send_connect_e) {
      size_t written = 0;

      set->status = f_socket_write_stream(&set->socket, 0, (void *) (set->buffer.string + set->size_done), &written);
      macro_kt_send_process_handle_error_exit_1(main, f_socket_write_stream, set->network, set->status, set->flag);

      set->size_done += written;

      // When the buffer is smaller than the read block size, then the entire file should be completely sent.
      if (set->size_done == set->buffer.used && set->size_done < set->file.size_read) {
        set->flag = kt_tacocat_socket_flag_send_buffer_sent_e;
      }
    }

    if (set->flag == kt_tacocat_socket_flag_send_buffer_sent_e) {
      set->flag = 0;
      set->size_done = 0;

      set->status = f_file_close(&set->file);

      if (F_status_is_error(set->status)) {
        kt_tacocat_print_warning_on_file(&main->program.warning, macro_kt_tacocat_f(f_file_close), kt_tacocat_send_s, set->network, set->status, set->name, f_file_operation_close_s);
      }

      set->status = f_socket_disconnect(&set->socket, f_socket_close_write_e);

      if (F_status_is_error(set->status)) {
        kt_tacocat_print_warning_on_file(&main->program.warning, macro_kt_tacocat_f(f_socket_disconnect), kt_tacocat_send_s, set->network, set->status, set->name, f_file_operation_close_s);
      }

      set->status = F_okay;

      return F_done;
    }

    return F_done_not;
  }
#endif // _di_kt_tacocat_send_process_

#ifdef __cplusplus
} // extern "C"
#endif
