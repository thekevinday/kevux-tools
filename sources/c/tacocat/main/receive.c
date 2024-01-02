#include "tacocat.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_tacocat_receive_
  void * kt_tacocat_receive(void * const void_main) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    if (!void_main) return 0;

    kt_tacocat_main_t * const main = (kt_tacocat_main_t *) void_main;
    f_number_unsigned_t i = 0;

    kt_tacocat_process_socket_set_receive(main);

    if (F_status_is_error_not(main->setting.status_receive) && main->setting.receive.used) {
      do {
        main->setting.status_receive = f_file_poll(main->setting.receive_polls, main->setting.active_receive ? main->setting.interval_fast : main->setting.interval);

        if (main->program.signal_received) {
          main->setting.status_receive = F_status_set_error(F_interrupt);

          return 0;
        }

        // @todo or check if there is any lingering in-progress process not waiting on receive.
        // @todo when there is a lingering iin-progress process, change the poll timeout to a shorter period to process the lingering process more.
        // Skip if status from poll is an error or is F_time_out.
        if (main->setting.status_receive == F_okay) {
          for (i = 0; i < main->setting.receive_polls.used; ++i) {

            if (main->setting.receive_polls.array[i].fd == -1) continue;

            if (main->setting.receive_polls.array[i].revents & (f_poll_read_e)) {
              if (kt_tacocat_receive_process(main, &main->setting.receive.array[i]) == F_done) {
                if (F_status_is_error(main->setting.receive.array[i].status)) {
                  // @todo there probably should be a timeout as well as a retry, which should be checked if the poll read condition above is false.
                  if (++main->setting.receive.array[i].retry >= kt_tacocat_startup_retry_max_d) {
                    f_file_close(&main->setting.receive.array[i].file);

                    // Keep error bit but set state to done to designate that nothing else is to be done.
                    main->setting.receive.array[i].status = F_status_set_error(F_done);

                    if (main->setting.receive.array[i].flag) {
                      main->setting.receive.array[i].flag = 0;

                      if (main->setting.active_receive) {
                        --main->setting.active_receive;
                      }
                    }

                    kt_tacocat_print_error_on_max_retries_receive(&main->program.error, &main->setting.receive.array[i]);
                  }

                  // @todo if flag is kt_tacocat_socket_flag_receive_control_e, check if error is either F_packet_too_small or F_packet_too_large. This is a non-retrying error.
                }
              }
              else {
                if (F_status_is_error(main->setting.receive.array[i].status)) {
                  if (++main->setting.receive.array[i].retry >= kt_tacocat_startup_retry_max_d) {
                    f_file_close(&main->setting.receive.array[i].file);

                    // Keep error bit but set state to done to designate that nothing else is to be done. @todo review and confirm if this assignment with error bit set is needed anymore or should be changed.
                    main->setting.receive.array[i].status = F_status_set_error(F_done);

                    if (main->setting.receive.array[i].flag) {
                      main->setting.receive.array[i].flag = 0;

                      if (main->setting.active_receive) {
                        --main->setting.active_receive;
                      }
                    }

                    kt_tacocat_print_error_on_max_retries_receive(&main->program.error, &main->setting.receive.array[i]);
                  }
                }
              }

              main->setting.receive_polls.array[i].revents = 0;
            }
          } // for
        }

      } while (F_status_is_error_not(main->setting.status_receive));
    }

    kt_tacocat_process_socket_sets_disconnect(main, &main->setting.receive);

    kt_tacocat_process_socket_sets_error_handle(main, main->setting.receive, &main->setting.status_receive);

    if (F_status_is_error_not(main->setting.status_receive)) {
      main->setting.status_receive = F_okay;
    }

    return 0;
  }
#endif // _di_kt_tacocat_receive_

#ifndef _di_kt_tacocat_receive_process_
  f_status_t kt_tacocat_receive_process(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set) {

    if (!main || !set) return F_status_set_error(F_parameter);

    // This is a new packet (kt_tacocat_socket_flag_receive_none_e).
    if (!(set->flag)) {
      kt_tacocat_print_message_receive_operation_received(&main->program.message, *set);

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
      set->socket.id_data = -1;
      set->range.start = 1;
      set->range.stop = 0;
      set->state.status = F_none;
      set->status = F_none;
      set->packet.control = 0;
      set->packet.size = 0;
      set->packet.payload.start = 1;
      set->packet.payload.stop = 0;
      set->flag = kt_tacocat_socket_flag_receive_control_e;

      ++main->setting.active_receive;
    }

    if (set->retry >= kt_tacocat_startup_retry_max_d) {
      f_file_close(&set->file);

      // Keep error bit but set state to done to designate that nothing else is to be done.
      set->status = F_status_set_error(F_done);
      set->flag = 0;

      if (main->setting.active_receive) {
        --main->setting.active_receive;
      }

      kt_tacocat_print_error_on_max_retries_receive(&main->program.error, set);

      return F_done;
    }

    // Load the header of the new packet.
    if (set->flag & kt_tacocat_socket_flag_receive_control_e) {
      kt_tacocat_receive_process_control(main, set);

      if (set->buffer.used < kt_tacocat_packet_peek_d || F_status_is_error(set->status)) {
        if (main->setting.active_receive) {
          --main->setting.active_receive;
        }

        return F_done;
      }

      // Reset the buffer to allow for reusing and writing to the file in blocks.
      set->buffer.used = 0;

      // Make sure the buffer is large enough for payload processing block reads.
      set->status = f_memory_array_increase_by(set->socket.size_read, sizeof(f_char_t), (void **) &set->buffer.string, &set->buffer.used, &set->buffer.size);
      macro_kt_receive_process_handle_error_exit_1(main, f_memory_array_increase_by, set->network, set->status, set->name, set->flag, &set->socket.id_data);

      set->retry = 0;
      set->buffer.used = 0;
      set->flag = kt_tacocat_socket_flag_receive_packet_e;
    }

    if (set->flag & kt_tacocat_socket_flag_receive_packet_e) {
      size_t length_read = 0;

      set->status = f_socket_read_stream(&set->socket, 0, (void *) (set->buffer.string + set->buffer.used), &length_read);
      macro_kt_receive_process_handle_error_exit_1(main, f_socket_read_stream, set->network, set->status, set->name, set->flag, &set->socket.id_data);

      if (length_read) {
        set->retry = 0;
        set->buffer.used += length_read;

        // This is not a valid packet if the actual size is greater than expected.
        if (set->buffer.used > set->packet.size) {
          kt_tacocat_print_error_on_packet_too_large(&main->program.error, kt_tacocat_receive_s, set->network, set->packet.size, set->buffer.used);

          set->status = F_status_set_error(F_packet_too_large);

          return F_done;
        }

        // Initialize the range to start reading after the Control and Size blocks.
        if (set->range.start > set->range.stop) {
          set->range.start = F_fss_simple_packet_block_header_size_d;
        }

        set->range.stop = set->buffer.used - 1;
        set->flag = kt_tacocat_socket_flag_receive_find_e;
      }
      else {
        ++set->retry;
      }
    }

    if (set->flag & kt_tacocat_socket_flag_receive_find_e) {
      set->state.status = F_none;

      fll_fss_payload_read(set->buffer, &set->range, &set->objects, &set->contents, &set->objects_delimits, &set->contents_delimits, &set->comments, &set->state);

      // Note that F_fss_found_object_content_not is not treated as an error because the "payload" section is optional.
      if (F_status_is_error(set->state.status) && F_status_set_fine(set->state.status) != F_fss_found_object_content_not) {
        switch (F_status_set_fine(set->state.status)) {
          case F_okay:
          case F_okay_eos:
          case F_okay_stop:

            if (set->buffer.used == set->packet.size) {

              // The packet is fully loaded and there is no "payload" section.
              set->flag = kt_tacocat_socket_flag_receive_check_e;
            }
            else {

              // Seek the left-most new line from the current position to ensure that the next pass potentially reads a complete line.
              while (set->range.start && set->buffer.string[set->range.start] != f_string_eol_s.string[0]) {

                --set->range.start;
              } // while

              // No packet is found and is not yet finished loading the data.
              set->flag = kt_tacocat_socket_flag_receive_packet_e;
            }

            break;

          default:

            // Seek the left-most new line from the current position to ensure that the next pass potentially reads a complete line.
            while (set->range.start && set->buffer.string[set->range.start] != f_string_eol_s.string[0]) {

              --set->range.start;
            } // while

            if (set->buffer.used != set->packet.size) {
              set->flag = kt_tacocat_socket_flag_receive_packet_e;
            }

            ++set->retry;

            break;
        }
      }
      else {
        switch (F_status_set_fine(set->state.status)) {
          case F_okay:
          case F_okay_eos:
          case F_okay_stop:
          case F_data_not:
          case F_data_not_eos:
          case F_data_not_stop:
          case F_fss_found_object_content_not:
            set->flag = kt_tacocat_socket_flag_receive_check_e;

            break;

          default:
            ++set->retry;

            break;
        }
      }
    }

    if (set->flag & kt_tacocat_socket_flag_receive_check_e) {

      // @todo this probably should be in a separate function, similar to how kt_tacocat_receive_process_control() is.
      {
        uint8_t found_not = F_true;

        for (f_number_unsigned_t i = 0; i < set->objects.used; ++i) {

          if (f_compare_dynamic_partial_string(f_fss_payload_object_header_s.string, set->buffer, f_fss_payload_object_header_s.used, set->objects.array[i]) == F_equal_to) {
            // @todo walk through header, mapping it.
          }
          else if (f_compare_dynamic_partial_string(f_fss_payload_object_signature_s.string, set->buffer, f_fss_payload_object_signature_s.used, set->objects.array[i]) == F_equal_to) {
            // @todo walk through signature, mapping it.
          }
          else if (f_compare_dynamic_partial_string(f_fss_payload_object_payload_s.string, set->buffer, f_fss_payload_object_payload_s.used, set->objects.array[i]) == F_equal_to) {
            if (found_not) {
              set->packet.payload = set->contents.array[i].array[0];
              found_not = F_false;
            }
          }
        } // for
      }

      // @todo walk through each set->objects and their respective set->contents, checking and processing the data.

      set->flag = kt_tacocat_socket_flag_receive_write_e;
    }

    if (set->flag & kt_tacocat_socket_flag_receive_write_e) {
      set->status = f_file_open(set->name, F_file_mode_all_rw_d, &set->file);

      if (F_status_is_error(set->status)) {
        kt_tacocat_print_error_on_file_receive(&main->program.error, macro_kt_tacocat_f(f_file_open), kt_tacocat_receive_s, set->network, set->status, set->name, f_file_operation_open_s);

        return F_done_not; // @todo consider sending a file error to caller. This should not infinitely attempt to open on failure.
      }

      set->status = f_file_write_range(set->file, set->buffer, set->packet.payload, 0);

      // Keep going on error, but in the future more advanced error handling/recovery is needed to make this more robust.
      if (F_status_is_error(set->status)) {
        f_file_close(&set->file);

        kt_tacocat_print_error_on_file_receive(&main->program.error, macro_kt_tacocat_f(f_file_write_range), kt_tacocat_receive_s, set->network, set->status, set->name, f_file_operation_write_s);
      }

      f_file_close(&set->file);

      set->buffer.used = 0;
      set->flag = kt_tacocat_socket_flag_receive_done_e;
    }

    // Done processing the Packet.
    if (set->flag & kt_tacocat_socket_flag_receive_done_e) {
      kt_tacocat_print_message_receive_operation_complete(&main->program.message, *set);

      f_file_close(&set->file);

      set->flag = 0;
      set->status = F_okay;

      if (main->setting.active_receive) {
        --main->setting.active_receive;
      }

      if (set->buffer.size > kt_tacocat_max_maintain_d) {
        set->buffer.used = 0;

        set->status = f_memory_array_resize(kt_tacocat_max_maintain_d, sizeof(f_char_t), (void **) &set->buffer.string, &set->buffer.used, &set->buffer.size);

        // Report the resize error but do not fail.
        if (F_status_is_error(set->status)) {
          kt_tacocat_print_error_on(&main->program.error, macro_kt_tacocat_f(f_memory_array_resize), kt_tacocat_receive_s, set->network, set->status, set->name);
        }
      }

      return F_done;
    }

    return F_done_not;
  }
#endif // _di_kt_tacocat_receive_process_

#ifndef _di_kt_tacocat_receive_process_control_
  void kt_tacocat_receive_process_control(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set) {

    if (!main || !set) return;

    const size_t size_read = set->socket.size_read;
    size_t length_read = 0;

    set->status = f_socket_accept(&set->socket);

    // The socket failed to accept and so there is no data socket id to close.
    macro_kt_receive_process_begin_handle_error_exit_1(main, f_socket_accept, set->network, set->status, set->name, set->flag);

    set->status = f_memory_array_increase_by(kt_tacocat_packet_peek_d + 1, sizeof(f_char_t), (void **) &set->buffer.string, &set->buffer.used, &set->buffer.size);
    macro_kt_receive_process_begin_handle_error_exit_1(main, f_memory_array_increase_by, set->network, set->status, set->name, set->flag);

    set->socket.size_read = kt_tacocat_packet_peek_d;

    set->status = f_socket_read_stream(&set->socket, f_socket_flag_peek_e, (void *) (set->buffer.string + set->buffer.used), &length_read);

    set->socket.size_read = size_read;

    macro_kt_receive_process_begin_handle_error_exit_1(main, f_socket_read_stream, set->network, set->status, set->name, set->flag);

    set->buffer.used += length_read;

    // Try peeking again if the packet header is not fully ready.
    if (set->buffer.used < kt_tacocat_packet_peek_d) {

      // Peek ahead to see if the client has closed the connection (all the intended data should have been transmitted).
      if (length_read) {
        memset(main->cache.peek, 0, kt_tacocat_cache_size_peek_d);

        set->socket.size_read = kt_tacocat_cache_size_peek_d - 1;
        length_read = 0;

        set->status = f_socket_read_stream(&set->socket, f_socket_flag_peek_e | f_socket_flag_wait_not_e, (void *) main->cache.peek, &length_read);

        set->socket.size_read = size_read;

        // Connection is closed when length is 0, which means the packet is too small.
        if (!length_read) {
          kt_tacocat_print_error_on_packet_too_small(&main->program.error, kt_tacocat_receive_s, set->network, kt_tacocat_packet_peek_d, set->buffer.used);

          set->status = F_status_set_error(F_packet_too_small);

          return;
        }
      }
      else {

        // Connection is closed when length is 0.
        kt_tacocat_print_warning_on_client_closed(&main->program.warning, kt_tacocat_receive_s, set->network);

        set->flag = 0;
        set->status = F_status_set_error(F_packet_too_small);

        return;
      }

      ++set->retry;

      return;
    }

    set->status = f_fss_simple_packet_decode_range(set->buffer, &set->packet);
    macro_kt_receive_process_begin_handle_error_exit_1(main, f_fss_simple_packet_decode_range, set->network, set->status, set->name, set->flag);

    if (set->status == F_packet_too_small || set->packet.size < kt_tacocat_packet_minimum_d || set->packet.size > main->setting.max_buffer) {
      set->buffer.used = 0;

      if (set->buffer.size > kt_tacocat_max_maintain_d) {
        set->status = f_memory_array_resize(kt_tacocat_max_maintain_d, sizeof(f_char_t), (void **) &set->buffer.string, &set->buffer.used, &set->buffer.size);

        // Report the resize error but do not fail.
        if (F_status_is_error(set->status)) {
          kt_tacocat_print_error_on(&main->program.error, macro_kt_tacocat_f(f_memory_array_resize), kt_tacocat_receive_s, set->network, set->status, set->name);
        }
      }

      set->flag = 0;

      if (set->status == F_packet_too_small || set->packet.size < kt_tacocat_packet_minimum_d) {
        set->status = F_status_set_error(F_packet_too_small);
      }
      else {
        set->status = F_status_set_error(F_packet_too_large);
      }

      kt_tacocat_print_error_on_packet_invalid(&main->program.error, kt_tacocat_receive_s, set->network);

      return;
    }

    kt_tacocat_print_message_receive_operation_control_size(&main->program.message, *set);
  }
#endif // _di_kt_tacocat_receive_process_control_

#ifdef __cplusplus
} // extern "C"
#endif
