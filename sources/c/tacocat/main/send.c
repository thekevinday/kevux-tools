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
    bool poll = F_false;

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

              if (main->setting.send.array[i].step == kt_tacocat_socket_step_send_wait_e) {
                poll = F_true;
              }

              ready = F_done_not;
            }
          }
        } // for

        if (F_status_is_error_not(main->setting.status_send) && poll) {
          main->setting.status_send = f_file_poll(main->setting.send_polls, main->setting.active_send ? main->setting.interval_fast : main->setting.interval);

          if (main->program.signal_received) {
            main->setting.status_receive = F_status_set_error(F_interrupt);

            return 0;
          }

          poll = F_false;
        }

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

    if (!set->step) {
      kt_tacocat_send_process_initialize(main, set);

      if (F_status_is_error(set->status)) {
        macro_kt_send_process_handle_error_exit_1(main, kt_tacocat_send_process_initialize, kt_tacocat_send_s, set->network, set->status, set->name, set->step);
      }

      set->step = kt_tacocat_socket_step_send_size_e;
    }

    if (set->retry >= kt_tacocat_startup_retry_max_d) {
      f_file_close(&set->file);
      f_socket_disconnect(&set->socket, f_socket_close_fast_e);

      set->step = 0;
      set->socket.id_data = -1;

      // Keep error bit but set state to done to designate that nothing else is to be done.
      set->status = F_status_set_error(F_done);

      kt_tacocat_print_error_on_max_retries_send(&main->program.error, set);

      return F_done;
    }

    // @todo when total > 1, then this needs to build each part, incrementing part each time (every time this needs to be done, the entire header structure needs to be rebuilt until part == total - 1) (the receive code needs to also be sure to handle multiple parts).
    if (set->step == kt_tacocat_socket_step_send_size_e) {
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

      set->status = f_memory_array_increase_by(set->abstruses.array[4].value.is.a_unsigned, sizeof(f_number_unsigned_t), (void **) &set->parts.array, &set->parts.used, &set->parts.size);

      if (F_status_is_error(set->status)) {
        // @todo out of memory, send abort packet with F_memory as a status.
        // @todo pre-build an out of memory packet as a static string, with reserved space for the salt.
        // @todo packets like this need to be sent
        f_file_close(&set->file);
        f_socket_disconnect(&set->socket, f_socket_close_fast_e);

        set->step = 0;
        set->socket.id_data = -1;

        // Keep error bit but set state to done to designate that nothing else is to be done.
        set->status = F_status_set_error(F_done);

        kt_tacocat_print_error_on(&main->program.error, macro_kt_tacocat_f(f_memory_array_increase_by), kt_tacocat_send_size_s, set->network, set->status, set->name);

        return F_done_not;
      }

      set->step = kt_tacocat_socket_step_send_build_e;
    }

    if (set->step == kt_tacocat_socket_step_send_build_e) {
      f_state_t state_local = main->setting.state;
      state_local.data = &set->write_state;

      fl_fss_payload_header_map(set->abstruses, &set->headers, &state_local);

      set->status = state_local.status;

      macro_kt_send_process_handle_error_exit_1(main, fl_fss_payload_header_map, kt_tacocat_send_build_s, set->network, set->status, set->name, set->step);

      set->write_state.cache->used = 0;

      set->status = f_random_array_shuffle(0, set->headers.used, sizeof(f_string_map_t), set->write_state.cache, (void *) set->headers.array);

      macro_kt_send_process_handle_error_exit_1(main, f_random_array_shuffle, kt_tacocat_send_build_s, set->network, set->status, set->name, set->step);

      set->step = kt_tacocat_socket_step_send_header_e;
    }

    if (set->step == kt_tacocat_socket_step_send_header_e) {
      // @todo this needs to check the current status, accordingly (for when multiple blocks are being sent).

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

          set->status = f_string_dynamic_append_nulless(set->headers.array[i].key, &set->buffer);

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

      macro_kt_send_process_handle_error_exit_1(main, f_string_dynamic_append_nulless, kt_tacocat_send_combine_s, set->network, set->status, set->name, set->step);

      set->step = kt_tacocat_socket_step_send_file_e;
    }

    if (set->step == kt_tacocat_socket_step_send_file_e) {
      const f_number_unsigned_t size_header = set->buffer.used;

      set->status = f_string_dynamic_append(f_fss_payload_object_payload_s, &set->buffer);

      if (F_status_is_error_not(set->status)) {
        set->status = f_string_dynamic_append(f_fss_payload_object_end_s, &set->buffer);
      }

      macro_kt_send_process_handle_error_exit_1(main, f_string_dynamic_append, kt_tacocat_send_file_s, set->network, set->status, set->name, set->step);

      // Always reset the seek position in case a retry happened after the file block is read.
      {
        off_t seeked = 0;

        set->status = f_file_seek(set->file, SEEK_SET, set->size_done, &seeked);
        macro_kt_send_process_handle_error_exit_1(main, f_file_seek, kt_tacocat_send_file_s, set->network, set->status, set->name, set->step);
      }

      set->status = f_file_read_block(set->file, &set->buffer);
      macro_kt_send_process_handle_error_exit_1(main, f_file_read_block, kt_tacocat_send_file_s, set->network, set->status, set->name, set->step);

      set->status = f_string_dynamic_terminate_after(&set->buffer);
      macro_kt_send_process_handle_error_exit_1(main, f_string_dynamic_terminate_after, kt_tacocat_send_combine_s, set->network, set->status, set->name, set->step);

      set->retry = 0;
      set->step = kt_tacocat_socket_step_send_check_e;
    }

    if (set->step == kt_tacocat_socket_step_send_check_e) {
      // @todo this needs to check if the size read has changed and then re-build the header (swap the buffer read block into the cache then rebuild the header with th new size).
      //if (set->abstruses.array[2].value.is.a_unsigned < set->file.size_read) {
      //}

      set->step = kt_tacocat_socket_step_send_encode_e;
    }

    if (set->step == kt_tacocat_socket_step_send_encode_e) {
      const f_number_unsigned_t original = set->buffer.used;

      set->buffer.used = 0;

      // @todo there will need to be checks for max-size and the payload size, shrinking the payload if the header + payload is too large.
      // @todo if the header file is so large that the payload is smaller than a reasonable minumum (say 32 bytes), then this is a problem and throw a too large/small error.
      set->status = f_fss_simple_packet_encode(F_fss_simple_packet_endian_d, original, &set->buffer);

      set->buffer.used = original;

      macro_kt_send_process_handle_error_exit_1(main, f_fss_simple_packet_encode, kt_tacocat_send_payload_s, set->network, set->status, set->name, set->step);

      set->step = kt_tacocat_socket_step_send_packet_e;
    }

    if (set->step == kt_tacocat_socket_step_send_packet_e) {
      size_t written = 0;

      {
        const size_t original = set->socket.size_write;

        set->socket.size_write = set->buffer.used;

        set->status = f_socket_write_stream(&set->socket, f_socket_flag_signal_not_e, (void *) set->buffer.string, &written);

        set->socket.size_write = original;

        macro_kt_send_process_handle_error_exit_1(main, f_socket_write_stream, kt_tacocat_send_payload_s, set->network, set->status, set->name, set->step);
      }

      // @todo handle case when written < set->buffer.used, of which each pass. The entire buffer must be sent. May need another variable for say, set->size_process.

      set->size_done += written;

      set->status = F_okay;
      set->step = kt_tacocat_socket_step_send_wait_e;

      // Wait for packet received confirmation.
      return F_done_not;
    }

    if (set->step == kt_tacocat_socket_step_send_wait_e) {
      // @todo process/validate the received response.

      // When the buffer is smaller than the read block size, then the entire file should be completely sent.
      if (set->size_done >= set->buffer.used) {
        set->step = kt_tacocat_socket_step_send_done_e;
      }
      else {
        set->status = F_okay;
        set->step = kt_tacocat_socket_step_send_wait_e;

        return F_done_not;
      }
    }

    if (set->step == kt_tacocat_socket_step_send_done_e) {
      //@todo send done packet.
      set->status = f_file_close(&set->file);

      if (F_status_is_error(set->status)) {
        kt_tacocat_print_warning_on_file(&main->program.warning, macro_kt_tacocat_f(f_file_close), kt_tacocat_send_done_s, set->network, set->status, set->name, f_file_operation_close_s);
      }

      set->status = f_socket_disconnect(&set->socket, f_socket_close_fast_e);

      if (F_status_is_error(set->status)) {
        kt_tacocat_print_warning_on_file(&main->program.warning, macro_kt_tacocat_f(f_socket_disconnect), kt_tacocat_send_done_s, set->network, set->status, set->name, f_file_operation_close_s);
      }

      set->step = 0;
      set->socket.id_data = -1;
      set->status = F_okay;

      return F_done;
    }

    return F_done_not;
  }
#endif // _di_kt_tacocat_send_process_

#ifndef _di_kt_tacocat_send_process_initialize_
  void kt_tacocat_send_process_initialize(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set) {

    if (!main || !set) return;

    set->abstruses.used = 0;
    set->buffer.used = 0;
    set->id.used = 0;
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
    set->socket.id_data = -1;
    set->range.start = 1;
    set->range.stop = 0;
    set->state.status = F_none;
    set->status = F_none;
    set->time.used = 0;
    set->packet.control = 0;
    set->packet.size = 0;
    set->packet.payload.start = 1;
    set->packet.payload.stop = 0;
    set->part = 0;
    set->parts.used = 0;
    set->flag = 0;

    // For writes, the id_data is the same as the id.
    set->socket.id_data = set->socket.id;

    // Initialize the default file payload.
    set->status = f_memory_array_increase_by(kt_tacocat_packet_headers_d, sizeof(f_string_map_t), (void **) &set->headers.array, &set->headers.used, &set->headers.size);

    if (F_status_is_error_not(set->status)) {
      set->status = f_memory_array_increase_by(kt_tacocat_packet_prebuffer_d, sizeof(f_char_t), (void **) &set->buffer.string, &set->buffer.used, &set->buffer.size);
    }

    if (F_status_is_error_not(set->status)) {
      set->status = f_memory_array_increase_by(kt_tacocat_packet_id_length_d, sizeof(f_char_t), (void **) &set->id.string, &set->id.used, &set->id.size);
    }

    if (F_status_is_error_not(set->status)) {
      f_char_t id[kt_tacocat_packet_id_length_d];
      f_string_static_t id_buffer = macro_f_string_static_t_initialize_2(id, 0);
      uint8_t modded = 0;

      memset(id, 0, kt_tacocat_packet_id_length_d);

      if (F_status_is_error_not(f_random_read(0, kt_tacocat_packet_id_length_d, &id_buffer.string, &id_buffer.used))) {
        for (uint8_t i = 0; i < id_buffer.used; i += macro_f_utf_byte_width(id[i])) {

          if (f_utf_is_alphabetic_digit(id + i, kt_tacocat_packet_id_length_d - i, 0) == F_true) {
            set->id.string[set->id.used++] = id[i];

            if (macro_f_utf_byte_width(id[i]) > 1) {
              set->id.string[set->id.used++] = id[i + 1];

              if (macro_f_utf_byte_width(id[i]) > 2) {
                set->id.string[set->id.used++] = id[i + 2];

                if (macro_f_utf_byte_width(id[i]) > 3) {
                  set->id.string[set->id.used++] = id[i + 3];
                }
              }
            }
          }
          else {
            modded = ((uint8_t) id[i]) % 36;

            // Fallback to ASCII based on current index position.
            if (modded < 10) {
              set->id.string[set->id.used++] = (modded) + 48;
            }
            else if (modded < 36) {
              set->id.string[set->id.used++] = (modded) + 55; // ASCII 65 - 10 = 55.
            }
            else {
              set->id.string[set->id.used++] = (modded) + 61; // ASCII 97 - 36 = 61.
            }
          }
        } // for
      }
      else {
        // @todo manually generate something, probably use the file name and the port number.
      }
    }

    if (F_status_is_error_not(set->status)) {
      kt_tacocat_send_process_time_now(set);
    }

    if (F_status_is_error_not(set->status)) {
      kt_tacocat_process_abstruse_initialize(main, set);
    }

    if (F_status_is_error_not(set->status)) {
      set->status = F_okay;
    }
  }
#endif // _di_kt_tacocat_send_process_initialize_

#ifndef _di_kt_tacocat_send_process_time_now_
  void kt_tacocat_send_process_time_now(kt_tacocat_socket_set_t * const set) {

    if (!set) return;

    set->time.used = 0;

    f_string_t string = f_string_t_initialize;

    {
      time_t t = time(NULL);

      string = asctime(gmtime(&t));
    }

    if (string) {
      f_number_unsigned_t total = strnlen(string, kt_tacocat_max_asctime_d);

      // Do not count the NULL (some strnlen() implementations, like glibc, appear to incorrectly include the terminating NULL in the count.
      if (total && !string[total]) {
        --total;
      }

      set->status = f_memory_array_increase_by(total + kt_tacocat_time_utc_s.used + 1, sizeof(f_char_t), (void **) &set->time.string, &set->time.used, &set->time.size);
      if (F_status_is_error(set->status)) return;

      set->status = f_string_append(string, total, &set->time);
      if (F_status_is_error(set->status)) return;

      set->status = f_string_dynamic_append(kt_tacocat_time_utc_s, &set->time);
      if (F_status_is_error(set->status)) return;

      set->status = f_string_dynamic_terminate_after(&set->time);
      if (F_status_is_error(set->status)) return;

      set->status = F_okay;
    }
    else {
      set->status = F_status_set_error(F_time);
    }
  }
#endif // _di_kt_tacocat_send_process_time_now_

#ifdef __cplusplus
} // extern "C"
#endif
