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
              set->flag = kt_tacocat_socket_flag_receive_extract_e;
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
            set->flag = kt_tacocat_socket_flag_receive_extract_e;

            break;

          default:
            ++set->retry;

            break;
        }
      }
    }

    if (set->flag & kt_tacocat_socket_flag_receive_extract_e) {
      kt_tacocat_receive_process_extract(main, set);
      if (F_status_is_error(set->status)) return F_data_not;

      set->flag = kt_tacocat_socket_flag_receive_write_e;
    }

    if (set->flag & kt_tacocat_socket_flag_receive_check_e) {
      // @todo

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

#ifndef _di_kt_tacocat_receive_process_extract_
  void kt_tacocat_receive_process_extract(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set) {

    if (!main || !set) return;

    set->status = f_memory_array_increase_by(kt_tacocat_packet_headers_d, sizeof(f_abstruse_map_t), (void **) &set->abstruses.array, &set->abstruses.used, &set->abstruses.size);

    if (F_status_is_error(set->status)) {
      macro_kt_receive_process_handle_error_exit_2(main, f_memory_array_increase_by, set->network, set->status, set->name, set->flag, &set->socket.id_data);
    }

    // 0x1 = did not find payload, 0x2 = did not find header.
    uint8_t found_not = 0x3;

    for (f_number_unsigned_t i = 0; i < set->objects.used; ++i) {

      if (f_compare_dynamic_partial_string(f_fss_payload_object_header_s.string, set->buffer, f_fss_payload_object_header_s.used, set->objects.array[i]) == F_equal_to) {
        kt_tacocat_receive_process_extract_header(main, set, i);

        if (F_status_is_error(set->status)) {
          // @todo handle F_packet error, setup the sending of an invalid packet response (things similar to this needs to be done in multiple places).
          ++set->retry;

          return;
        }

        found_not &= ~0x2;
      }
      else if (f_compare_dynamic_partial_string(f_fss_payload_object_signature_s.string, set->buffer, f_fss_payload_object_signature_s.used, set->objects.array[i]) == F_equal_to) {
        kt_tacocat_receive_process_extract_signature(main, set, i);

        if (F_status_is_error(set->status)) {
          ++set->retry;

          return;
        }
      }
      else if (f_compare_dynamic_partial_string(f_fss_payload_object_payload_s.string, set->buffer, f_fss_payload_object_payload_s.used, set->objects.array[i]) == F_equal_to) {
        if (found_not & 0x1) {
          set->packet.payload = set->contents.array[i].array[0];
          found_not &= ~0x1;
        }
      }
    } // for

    set->status = F_okay;
  }
#endif // _di_kt_tacocat_receive_process_extract_

#ifndef _di_kt_tacocat_receive_process_extract_header_
  void kt_tacocat_receive_process_extract_header(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set, const f_number_unsigned_t at) {

    if (!main || !set) return;

    if (set->objects.array[at].start > set->objects.array[at].stop || !set->contents.array[at].used) {
      set->status = F_data_not;

      return;
    }

    set->range = set->contents.array[at].array[0];

    fll_fss_extended_read(set->buffer, &set->range, &set->objects_header, &set->contents_header, &set->objects_quoted_header, &set->contents_quoted_header, &set->objects_delimits_header, &set->contents_delimits_header, &set->state);

    if (F_status_is_error(set->state.status)) {
      kt_tacocat_print_error_on(&main->program.error, macro_kt_tacocat_f(fll_fss_extended_read), kt_tacocat_receive_s, set->network, set->status, set->name);

      set->status = set->state.status;

      return;
    }

    switch (set->state.status) {
      case F_okay:
      case F_okay_stop:
      case F_okay_eos:
        break;

      default:
        set->status = F_data_not;

        return;
    }

    f_number_unsigned_t i = 0;

    for (; i < set->objects_header.used; ++i) {

      // Index 0 is the status.
      if (f_compare_dynamic_partial_string(f_fss_payload_object_status_s.string, set->buffer, f_fss_payload_object_status_s.used, set->objects_header.array[i]) == F_equal_to) {

        // Require Content to exist.
        if (!set->contents_header.array[i].used) {
          set->abstruses.array[0].value.type = f_abstruse_none_e;

          continue;
        }

        set->abstruses.array[0].key = f_fss_payload_object_status_s;
        set->abstruses.array[0].value.type = f_abstruse_range_e;
        set->abstruses.array[0].value.is.a_range = set->contents_header.array[i].array[0];
      }

      // Index 1 is the type.
      else if (f_compare_dynamic_partial_string(f_fss_payload_object_type_s.string, set->buffer, f_fss_payload_object_type_s.used, set->objects_header.array[i]) == F_equal_to) {

        // Require Content to exist.
        if (!set->contents_header.array[i].used) {
         set->abstruses.array[1].value.type = f_abstruse_none_e;

          continue;
        }

        set->abstruses.array[1].key = f_fss_payload_object_type_s;
        set->abstruses.array[1].value.type = f_abstruse_range_e;
        set->abstruses.array[1].value.is.a_range = set->contents_header.array[i].array[0];
      }

      // Index 2 is the length.
      else if (f_compare_dynamic_partial_string(f_fss_payload_object_length_s.string, set->buffer, f_fss_payload_object_length_s.used, set->objects_header.array[i]) == F_equal_to) {

        // Require Content to exist.
        if (!set->contents_header.array[i].used) {
         set->abstruses.array[2].value.type = f_abstruse_none_e;

          continue;
        }

        set->abstruses.array[2].key = f_fss_payload_object_length_s;
        set->abstruses.array[2].value.type = f_abstruse_range_e;
        set->abstruses.array[2].value.is.a_range = set->contents_header.array[i].array[0];
      }

      // Index 3 is the part.
      else if (f_compare_dynamic_partial_string(f_fss_payload_object_part_s.string, set->buffer, f_fss_payload_object_part_s.used, set->objects_header.array[i]) == F_equal_to) {

        // Require Content to exist.
        if (!set->contents_header.array[i].used) {
         set->abstruses.array[3].value.type = f_abstruse_none_e;

          continue;
        }

        set->abstruses.array[3].key = f_fss_payload_object_part_s;
        set->abstruses.array[3].value.type = f_abstruse_range_e;
        set->abstruses.array[3].value.is.a_range = set->contents_header.array[i].array[0];
      }

      // Index 4 is the total number of packets (based on block size).
      else if (f_compare_dynamic_partial_string(f_fss_payload_object_total_s.string, set->buffer, f_fss_payload_object_total_s.used, set->objects_header.array[i]) == F_equal_to) {

        // Require Content to exist.
        if (!set->contents_header.array[i].used) {
         set->abstruses.array[4].value.type = f_abstruse_none_e;

          continue;
        }

        set->abstruses.array[4].key = f_fss_payload_object_total_s;
        set->abstruses.array[4].value.type = f_abstruse_range_e;
        set->abstruses.array[4].value.is.a_range = set->contents_header.array[i].array[0];
      }

      // Index 5 is the name (file name).
      else if (f_compare_dynamic_partial_string(f_fss_payload_object_name_s.string, set->buffer, f_fss_payload_object_name_s.used, set->objects_header.array[i]) == F_equal_to) {

        // Require Content to exist.
        if (!set->contents_header.array[i].used) {
         set->abstruses.array[5].value.type = f_abstruse_none_e;

          continue;
        }

        set->abstruses.array[5].key = f_fss_payload_object_name_s;
        set->abstruses.array[5].value.type = f_abstruse_range_e;
        set->abstruses.array[5].value.is.a_range = set->contents_header.array[i].array[0];
      }

      // Index 6 is the salt.
      else if (f_compare_dynamic_partial_string(kt_tacocat_salt_s.string, set->buffer, kt_tacocat_salt_s.used, set->objects_header.array[i]) == F_equal_to) {

        // Require Content to exist.
        if (!set->contents_header.array[i].used) {
          set->abstruses.array[6].value.type = f_abstruse_none_e;

          continue;
        }

        set->abstruses.array[6].key = kt_tacocat_salt_s;
        set->abstruses.array[6].value.type = f_abstruse_range_e;
        set->abstruses.array[6].value.is.a_range = set->contents_header.array[i].array[0];
      }
    } // for

    // Convert the status code.
    if (set->abstruses.array[0].value.type) {
      const f_number_unsigned_t length = set->abstruses.array[0].value.is.a_range.stop - set->abstruses.array[0].value.is.a_range.start + 1;
      char buffer[length];
      f_status_t status = F_false;

      memcpy(buffer, set->buffer.string + set->abstruses.array[0].value.is.a_range.start, length);

      const f_string_static_t status_string = macro_f_string_static_t_initialize_1(buffer, 0, length);

      set->status = fl_status_string_from(status_string, &status);

      if (set->status == F_okay) {
        set->abstruses.array[0].value.type = f_abstruse_unsigned_e;
        set->abstruses.array[0].value.is.a_unsigned = (f_number_unsigned_t) status;
      }
      else {
        kt_tacocat_print_error_on_packet_header_value_invalid(&main->program.error, kt_tacocat_receive_s, set->network, set->status, set->name, set->buffer, set->objects.array[at], set->abstruses.array[6].value.is.a_range);

        set->abstruses.array[0].value.type = f_abstruse_none_e;
        set->abstruses.array[0].value.is.a_unsigned = 0;

        set->status = F_status_set_error(F_packet);
      }
    }

    // Convert the type.
    if (set->abstruses.array[1].value.type) {
      if (f_compare_dynamic_partial_string(kt_tacocat_file_s.string, set->buffer, kt_tacocat_file_s.used, set->abstruses.array[1].value.is.a_range) == F_equal_to) {
        set->abstruses.array[1].value.type = f_abstruse_unsigned_e;
        set->abstruses.array[1].value.is.a_unsigned = (f_number_unsigned_t) kt_tacocat_packet_type_file_e;
      }
      else if (f_compare_dynamic_partial_string(kt_tacocat_done_s.string, set->buffer, kt_tacocat_done_s.used, set->abstruses.array[1].value.is.a_range) == F_equal_to) {
        set->abstruses.array[1].value.type = f_abstruse_unsigned_e;
        set->abstruses.array[1].value.is.a_unsigned = (f_number_unsigned_t) kt_tacocat_packet_type_done_e;
      }
      else if (f_compare_dynamic_partial_string(kt_tacocat_next_s.string, set->buffer, kt_tacocat_next_s.used, set->abstruses.array[1].value.is.a_range) == F_equal_to) {
        set->abstruses.array[1].value.type = f_abstruse_unsigned_e;
        set->abstruses.array[1].value.is.a_unsigned = (f_number_unsigned_t) kt_tacocat_packet_type_next_e;
      }
      else if (f_compare_dynamic_partial_string(kt_tacocat_resend_s.string, set->buffer, kt_tacocat_resend_s.used, set->abstruses.array[1].value.is.a_range) == F_equal_to) {
        set->abstruses.array[1].value.type = f_abstruse_unsigned_e;
        set->abstruses.array[1].value.is.a_unsigned = (f_number_unsigned_t) kt_tacocat_packet_type_resend_e;
      }
      else {
        set->status = F_status_set_error(F_found_not);

        kt_tacocat_print_error_on_packet_header_value_invalid(&main->program.error, kt_tacocat_receive_s, set->network, set->status, set->name, set->buffer, set->objects.array[at], set->abstruses.array[6].value.is.a_range);

        set->abstruses.array[1].value.type = f_abstruse_none_e;
        set->abstruses.array[1].value.is.a_unsigned = 0;

        set->status = F_status_set_error(F_packet);

        return;
      }
    }

    // Convert the length, part, and total.
    {
      f_number_unsigned_t number = 0;

      for (i = 2; i < 5; ++i) {

        if (!set->abstruses.array[i].value.type) continue;

        set->status = fl_conversion_dynamic_partial_to_unsigned(fl_conversion_data_base_10_c, set->buffer, set->abstruses.array[i].value.is.a_range, &number);

        if (set->status == F_okay) {
          set->abstruses.array[i].value.type = f_abstruse_unsigned_e;
          set->abstruses.array[i].value.is.a_unsigned = number;
        }
        else {
          kt_tacocat_print_error_on_packet_header_value_invalid(&main->program.error, kt_tacocat_receive_s, set->network, set->status, set->name, set->buffer, set->objects.array[at], set->abstruses.array[6].value.is.a_range);

          set->abstruses.array[i].value.type = f_abstruse_none_e;
          set->abstruses.array[i].value.is.a_unsigned = 0;

          set->status = F_status_set_error(F_packet);
        }
      } // for
    }

    set->abstruses.used = 6;
    set->status = F_okay;
  }
#endif // _di_kt_tacocat_receive_process_extract_header_

#ifndef _di_kt_tacocat_receive_process_extract_signature_
  void kt_tacocat_receive_process_extract_signature(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set, const f_number_unsigned_t at) {

    if (!main || !set) return;

    if (set->objects.array[at].start > set->objects.array[at].stop || !set->contents.array[at].used) {
      set->status = F_data_not;

      return;
    }

    set->range = set->contents.array[at].array[0];

    fll_fss_extended_read(set->buffer, &set->range, &set->objects_signature, &set->contents_signature, &set->objects_quoted_header, &set->contents_quoted_header, &set->objects_delimits_signature, &set->contents_delimits_signature, &set->state);

    if (F_status_is_error(set->state.status)) {
      kt_tacocat_print_error_on(&main->program.error, macro_kt_tacocat_f(fll_fss_extended_read), kt_tacocat_receive_s, set->network, set->status, set->name);

      set->status = set->state.status;

      return;
    }

    // @todo maybe 7 and beyond in the abstruse shall represent signatures?

    set->status = F_okay;
  }
#endif // _di_kt_tacocat_receive_process_extract_signature_

#ifdef __cplusplus
} // extern "C"
#endif
