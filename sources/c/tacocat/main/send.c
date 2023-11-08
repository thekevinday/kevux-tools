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

      set->flag = kt_tacocat_socket_flag_send_size_e;
    }

    if (set->flag == kt_tacocat_socket_flag_send_size_e) {

      // Total is used here to explicitly pass a pointer of off_t rather than a pointer of size_t cast to an off_t.
      off_t total = 0;

      set->status = f_file_size_by_id(set->file, &total);

      if (F_status_is_error(set->status)) {
        kt_tacocat_print_error_on_file(&main->program.error, macro_kt_tacocat_f(f_file_size_by_id), kt_tacocat_send_s, set->network, set->status, set->name, f_file_operation_open_s);

        return F_done_not;
      }

      set->size_total = (size_t) total; // @todo there is a size_total, but there is a total packet size and a total payload size. Find a way to distinguish both.
      set->flag = kt_tacocat_socket_flag_send_file_e;
    }

    if (set->flag == kt_tacocat_socket_flag_send_file_e) {
      set->buffer.used = 0;

      // Make sure the buffer is large enough for the file block reads (including a space for a terminating NULL).
      set->status = f_memory_array_increase_by(set->file.size_read + f_fss_payload_object_payload_s.used + f_fss_payload_object_end_s.used + 1, sizeof(f_char_t), (void **) &set->buffer.string, &set->buffer.used, &set->buffer.size);
      macro_kt_send_process_handle_error_exit_1(main, f_memory_array_increase_by, set->network, set->status, set->flag);

      set->status = f_string_dynamic_append(f_fss_payload_object_payload_s, &set->buffer);
      macro_kt_send_process_handle_error_exit_1(main, f_file_read_block, set->network, set->status, set->flag);

      set->status = f_string_dynamic_append(f_fss_payload_object_end_s, &set->buffer);
      macro_kt_send_process_handle_error_exit_1(main, f_file_read_block, set->network, set->status, set->flag);

      set->status = f_file_read_block(set->file, &set->buffer);
      macro_kt_send_process_handle_error_exit_1(main, f_file_read_block, set->network, set->status, set->flag);

      set->buffer.string[set->buffer.used] = 0;
      set->flag = kt_tacocat_socket_flag_send_build_e;
    }

    // @todo The build process needs to be broken up into multiple parts that can fit in a FSS Packet (2^32 - 6).
    if (set->flag == kt_tacocat_socket_flag_send_build_e) {
      set->header.used = 0;

      if (set->buffer.used) {
        set->status = f_memory_array_increase_by(kt_tacocat_packet_prebuffer_d, sizeof(f_char_t), (void **) &set->header.string, &set->header.used, &set->header.size);
        macro_kt_send_process_handle_error_exit_1(main, f_memory_array_increase_by, set->network, set->status, set->flag);

        f_state_t state_local = main->setting.state;
        state_local.data = &set->write_state;

        // @todo build the header and add to the header buffer and also add the "\npayload:\n". (resume programming here)
        // The entire structure:
        //   f_fss_payload_comment_header_begin_s.used + f_fss_payload_comment_header_s.used + f_fss_payload_comment_header_end_s.used
        //   f_fss_payload_object_header_s.used + f_fss_payload_object_end_s
        //   set->header.used
        //   f_fss_payload_object_payload_s.used + f_fss_payload_object_end_s
        //   set->buffer.used

        // @todo create the following headers:
        //       1) type file (or string, and if file, then name is filesize and size is filesize, otherwise name is unused and size is string length.)
        //       1) name "example.csv"
        //       2) size 1234
        //       3) status F_okay

        // @todo
        //       1) Build abstruse headers map of data.
        //       2) Call this: fl_fss_payload_header_map(set->headers, f_string_maps_t * const destinations, f_state_t * const state)
        //       3) append maps to buffer.

        // @todo needs to be kt_tacocat_socket_flag_send_build_e equivalent for sending the structures, like the header structure.

        set->header.string[set->header.used] = 0;
        set->flag = kt_tacocat_socket_flag_send_build_e;
      }
      else {

        // File is empty, nothing left to send.
        set->flag = kt_tacocat_socket_flag_send_done_e;
      }
    }

    // @todo all below is not updated to flag enumeration changes.

    // @todo don't send just yet, need to build the payload header (then send that first, followed by the payload itself)..
    // probably should send the header data separately first to avoid additional allocations of merging the buffer with the header.
    if (set->flag == kt_tacocat_socket_flag_send_build_e) {
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
        set->flag = kt_tacocat_socket_flag_send_done_e;
      }
    }

    if (set->flag == kt_tacocat_socket_flag_send_done_e) {
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
