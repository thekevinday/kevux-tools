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

    // @todo this needs to integrate send_polls, for checking responses to sent packets.
    if (F_status_is_error_not(main->setting.status_send) && main->setting.send.used) {
      do {
        ready = F_okay;

        for (i = 0; i < main->setting.send.used; ++i) {

          if (main->program.signal_received) {
            main->setting.status_send = F_status_set_error(F_interrupt);

            return 0;
          }

          if (F_status_set_fine(main->setting.send.array[i].status) == F_done) {
            if (F_status_is_error(main->setting.send.array[i].status) || ready != F_done_not) {
              ready = F_done;
            }
          }
          else {
            // @todo in all cases error or success, when done be sure set->file is closed.
            // @todo on error during partial transfer either attempt to resend, attempt to send failure packet, or abandon.
            if (kt_tacocat_send_process(main, &main->setting.send.array[i]) == F_done) {
              if (F_status_is_error(main->setting.send.array[i].status)) {
                ++main->setting.send.array[i].retry;
              }
              else if (ready != F_done_not) {
                ready = F_done;
              }
            }
            else {
              if (F_status_is_error(main->setting.send.array[i].status)) {
                ++main->setting.send.array[i].retry;
              }

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

    if (!set->flag) {
      set->abstruses.used = 0;
      set->buffer.used = 0;
      set->cache.used = 0;
      set->header.used = 0;
      set->headers.used = 0;
      set->objects.used = 0;
      set->contents.used = 0;
      set->objects_delimits.used = 0;
      set->contents_delimits.used = 0;
      set->comments.used = 0;
      set->retry = 0;
      set->size_done = 0;
      set->size_total = 0;
      set->file.size_read = set->size_block;
      set->socket.size_read = kt_tacocat_packet_read_d;
      set->range.start = -1;
      set->range.stop = 0;
      set->packet.control = 0;
      set->packet.size = 0;
      set->status = F_none;

      // For writes, the id_data is the same as the id.
      set->socket.id_data = set->socket.id;

      // Initialize the default file payload.
      set->status = f_memory_array_increase_by(kt_tacocat_packet_headers_d, sizeof(f_string_map_t), (void **) &set->headers.array, &set->headers.used, &set->headers.size);

      if (F_status_is_error_not(set->status)) {
        set->status = f_memory_array_increase_by(kt_tacocat_packet_prebuffer_d, sizeof(f_char_t), (void **) &set->buffer.string, &set->buffer.used, &set->buffer.size);
      }

      if (F_status_is_error_not(set->status)) {
        set->status = f_memory_array_increase_by(kt_tacocat_packet_headers_d, sizeof(f_abstruse_map_t), (void **) &set->abstruses.array, &set->abstruses.used, &set->abstruses.size);
      }

      if (F_status_is_error(set->status)) {
        macro_kt_send_process_handle_error_exit_1(main, f_memory_array_increase_by, kt_tacocat_send_s, set->network, set->status, set->name, set->flag);
      }

      // Index 0 is the status.
      set->abstruses.array[0].key = f_fss_payload_object_status_s;
      set->abstruses.array[0].value.type = f_abstruse_dynamic_e;
      set->abstruses.array[0].value.is.a_dynamic = f_status_okay_s;

      // Index 1 is the type.
      set->abstruses.array[1].key = f_fss_payload_object_type_s;
      set->abstruses.array[1].value.type = f_abstruse_dynamic_e;
      set->abstruses.array[1].value.is.a_dynamic = f_file_type_name_file_s;

      // Index 2 is the length.
      set->abstruses.array[2].key = f_fss_payload_object_length_s;
      set->abstruses.array[2].value.type = f_abstruse_unsigned_e;
      set->abstruses.array[2].value.is.a_unsigned = 0;

      // Index 3 is the part.
      set->abstruses.array[3].key = f_fss_payload_object_part_s;
      set->abstruses.array[3].value.type = f_abstruse_unsigned_e;
      set->abstruses.array[3].value.is.a_unsigned = 0;

      // Index 4 is the total number of packets (based on block size).
      set->abstruses.array[4].key = f_fss_payload_object_total_s;
      set->abstruses.array[4].value.type = f_abstruse_unsigned_e;
      set->abstruses.array[4].value.is.a_unsigned = 0;

      // Index 5 is the name.
      set->abstruses.array[5].key = f_fss_payload_object_name_s;
      set->abstruses.array[5].value.type = f_abstruse_dynamic_e;
      set->abstruses.array[5].value.is.a_dynamic = set->name;

      // Index 6 is the salt.
      set->abstruses.array[6].key = kt_tacocat_salt_s;
      set->abstruses.array[6].value.type = f_abstruse_unsigned_e;

      {
        long salt = 0;

        f_random_get(&salt);

        set->abstruses.array[6].value.is.a_unsigned = (f_number_unsigned_t) salt;
      }

      set->abstruses.used = 7;

      set->flag = kt_tacocat_socket_flag_send_size_e;
    }

    if (set->retry >= kt_tacocat_startup_retry_max_d) {
      f_file_close(&set->file);
      f_socket_disconnect(&set->socket, f_socket_close_fast_e);

      set->flag = 0;
      set->socket.id_data = -1;

      // Keep error bit but set state to done to designate that nothing else is to be done.
      set->status = F_status_set_error(F_done);

      kt_tacocat_print_error_on_max_retries_send(&main->program.error, set);

      return F_done;
    }

    if (set->flag & kt_tacocat_socket_flag_send_size_e) {
      if (set->file.id == -1) {
        set->status = f_file_open(set->name, F_file_mode_all_r_d, &set->file);

        if (F_status_is_error(set->status)) {
          kt_tacocat_print_error_on_file_receive(&main->program.error, macro_kt_tacocat_f(f_file_open), kt_tacocat_send_s, set->network, set->status, set->name, f_file_operation_open_s);

          return F_done_not;
        }
      }

      // Total is used here to explicitly pass a pointer of off_t rather than a pointer of size_t cast to an off_t.
      off_t total = 0;

      set->status = f_file_size_by_id(set->file, &total);

      if (F_status_is_error(set->status)) {
        kt_tacocat_print_error_on_file_receive(&main->program.error, macro_kt_tacocat_f(f_file_size_by_id), kt_tacocat_send_size_s, set->network, set->status, set->name, f_file_operation_open_s);

        return F_done_not;
      }

      if ((f_number_unsigned_t) total > F_number_t_size_unsigned_d) {
        set->status = F_status_set_error(F_too_large);

        kt_tacocat_print_error_on_file_too_large(&main->program.error, set->name, kt_tacocat_send_size_s, set->network, F_number_t_size_unsigned_d, set->abstruses.array[4].value.is.a_unsigned);

        return F_done_not;
      }

      set->abstruses.array[3].value.is.a_unsigned = 0;
      set->size_total = (f_number_unsigned_t) total;

      if (total) {
        if (set->size_total < set->file.size_read) {
          set->abstruses.array[2].value.is.a_unsigned = set->size_total;
          set->abstruses.array[4].value.is.a_unsigned = 1;
        }
        else {
          set->abstruses.array[2].value.is.a_unsigned = set->file.size_read;
          set->abstruses.array[4].value.is.a_unsigned = set->size_total / set->file.size_read;

          if (set->abstruses.array[4].value.is.a_unsigned % set->file.size_read) {
            ++set->abstruses.array[4].value.is.a_unsigned;
          }
        }
      }
      else {
        set->abstruses.array[2].value.is.a_unsigned = set->size_total;
        set->abstruses.array[4].value.is.a_unsigned = 1;
      }

      set->flag = kt_tacocat_socket_flag_send_build_e;
    }

    if (set->flag & kt_tacocat_socket_flag_send_build_e) {
      f_state_t state_local = main->setting.state;
      state_local.data = &set->write_state;

      fl_fss_payload_header_map(set->abstruses, &set->headers, &state_local);
      macro_kt_send_process_handle_error_exit_1(main, fl_fss_payload_header_map, kt_tacocat_send_build_s, set->network, state_local.status, set->name, set->flag);

      set->flag = kt_tacocat_socket_flag_send_header_e;
    }

    if (set->flag & kt_tacocat_socket_flag_send_header_e) {
      // @todo this needs to check the current status, accodingly (for when multiple blocks are being sent).

      // Reserve the FSS Packet header, which will be calculated just before sending.
      set->buffer.used = 5;
      memset(set->buffer.string, 0, 5);

      set->status = f_string_dynamic_append_nulless(f_fss_payload_comment_header_begin_s, &set->buffer);

      if (F_status_is_error_not(set->status)) {
        set->status = f_string_dynamic_append_nulless(f_fss_payload_comment_header_s, &set->buffer);
      }

      if (F_status_is_error_not(set->status)) {
        set->status = f_string_dynamic_append_nulless(f_fss_payload_comment_header_end_s, &set->buffer);
      }

      if (F_status_is_error_not(set->status)) {
        set->status = f_string_dynamic_append_nulless(f_fss_payload_object_header_s, &set->buffer);
      }

      if (F_status_is_error_not(set->status)) {
        set->status = f_string_dynamic_append_nulless(f_fss_payload_object_end_s, &set->buffer);
      }

      if (F_status_is_error_not(set->status)) {
        for (f_number_unsigned_t i = 0; i < set->headers.used; ++i) {

          set->status = f_string_dynamic_append_nulless(set->headers.array[i].name, &set->buffer);

          if (F_status_is_error_not(set->status)) {
            set->status = f_string_dynamic_append_nulless(f_fss_extended_open_s, &set->buffer);
          }

          if (F_status_is_error_not(set->status)) {
            set->status = f_string_dynamic_append_nulless(set->headers.array[i].value, &set->buffer);
          }

          if (F_status_is_error_not(set->status)) {
            set->status = f_string_dynamic_append_nulless(f_fss_extended_close_s, &set->buffer);
          }
          else {
            break;
          }
        } // for
      }

      macro_kt_send_process_handle_error_exit_1(main, f_string_dynamic_append_nulless, kt_tacocat_send_combine_s, set->network, set->status, set->name, set->flag);

      set->flag = kt_tacocat_socket_flag_send_file_e;
    }

    if (set->flag & kt_tacocat_socket_flag_send_file_e) {
      const f_number_unsigned_t size_header = set->buffer.used;

      set->status = f_string_dynamic_append(f_fss_payload_object_payload_s, &set->buffer);

      if (F_status_is_error_not(set->status)) {
        set->status = f_string_dynamic_append(f_fss_payload_object_end_s, &set->buffer);
      }

      macro_kt_send_process_handle_error_exit_1(main, f_string_dynamic_append, kt_tacocat_send_file_s, set->network, set->status, set->name, set->flag);

      // Always reset the seek position in case a retry happened after the file block is read.
      {
        off_t seeked = 0;

        set->status = f_file_seek(set->file, SEEK_SET, set->size_done, &seeked);
        macro_kt_send_process_handle_error_exit_1(main, f_file_seek, kt_tacocat_send_file_s, set->network, set->status, set->name, set->flag);
      }

      set->status = f_file_read_block(set->file, &set->buffer);
      macro_kt_send_process_handle_error_exit_1(main, f_file_read_block, kt_tacocat_send_file_s, set->network, set->status, set->name, set->flag);

      set->status = f_string_dynamic_terminate_after(&set->buffer);
      macro_kt_send_process_handle_error_exit_1(main, f_string_dynamic_terminate_after, kt_tacocat_send_combine_s, set->network, set->status, set->name, set->flag);

      set->retry = 0;
      set->flag = kt_tacocat_socket_flag_send_check_e;
    }

    if (set->flag & kt_tacocat_socket_flag_send_check_e) {
      // @todo this needs to check if the size read has changed and then re-build the header (swap the buffer read block into the cache then rebuild the header with th new size).
      //if (set->abstruses.array[2].value.is.a_unsigned < set->file.size_read) {
      //}

      set->flag = kt_tacocat_socket_flag_send_encode_e;
    }

    if (set->flag & kt_tacocat_socket_flag_send_encode_e) {
      const f_number_unsigned_t original = set->buffer.used;

      set->buffer.used = 0;

      // @todo there will need to be checks for max-size and the payload size, shrinking the payload if the header + payload is too large.
      // @todo if the header file is so large that the payload is smaller than a reasonable minumum (say 32 bytes), then this is a problem and throw a too large/small error.
      set->status = f_fss_simple_packet_encode(F_fss_simple_packet_endian_d, original, &set->buffer);

      set->buffer.used = original;

      macro_kt_send_process_handle_error_exit_1(main, f_fss_simple_packet_encode, kt_tacocat_send_payload_s, set->network, set->status, set->name, set->flag);

      set->flag = kt_tacocat_socket_flag_send_packet_e;
    }

    if (set->flag & kt_tacocat_socket_flag_send_packet_e) {
      size_t written = 0;

      {
        const size_t original = set->socket.size_write;

        set->socket.size_write = set->buffer.used;

        set->status = f_socket_write_stream(&set->socket, f_socket_flag_signal_not_e, (void *) set->buffer.string, &written);

        set->socket.size_write = original;

        macro_kt_send_process_handle_error_exit_1(main, f_socket_write_stream, kt_tacocat_send_payload_s, set->network, set->status, set->name, set->flag);
      }

      // @todo handle case when written < set->buffer.used, of which each pass. The entire buffer must be sent. May need another variable for say, set->size_process.

      set->size_done += written;

      // When the buffer is smaller than the read block size, then the entire file should be completely sent.
      if (set->size_done >= set->buffer.used) {
        set->flag = kt_tacocat_socket_flag_send_done_e;
      }
      else {
        set->status = F_okay;
        set->flag = kt_tacocat_socket_flag_send_header_e;

        return F_done_not;
      }
    }

    if (set->flag & kt_tacocat_socket_flag_send_done_e) {
      set->status = f_file_close(&set->file);

      if (F_status_is_error(set->status)) {
        kt_tacocat_print_warning_on_file(&main->program.warning, macro_kt_tacocat_f(f_file_close), kt_tacocat_send_done_s, set->network, set->status, set->name, f_file_operation_close_s);
      }

      set->status = f_socket_disconnect(&set->socket, f_socket_close_fast_e);

      if (F_status_is_error(set->status)) {
        kt_tacocat_print_warning_on_file(&main->program.warning, macro_kt_tacocat_f(f_socket_disconnect), kt_tacocat_send_done_s, set->network, set->status, set->name, f_file_operation_close_s);
      }

      set->flag = 0;
      set->socket.id_data = -1;
      set->status = F_okay;

      return F_done;
    }

    return F_done_not;
  }
#endif // _di_kt_tacocat_send_process_

#ifdef __cplusplus
} // extern "C"
#endif
