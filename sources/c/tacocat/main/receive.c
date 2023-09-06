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

    if (F_status_is_error_not(main->setting.status_receive)) {
      do {
        main->setting.status_receive = f_file_poll(main->setting.receive_polls, main->setting.interval);

        if (main->program.signal_received) {
          main->setting.status_receive = F_status_set_error(F_interrupt);

          return 0;
        }

        // Skip if status is an error or is F_time_out.
        if (main->setting.status_receive == F_okay) {
          for (i = 0; i < main->setting.receive_polls.used; ++i) {

            if (main->setting.receive_polls.array[i].fd == -1) continue;

            if (main->setting.receive_polls.array[i].revents & (f_poll_read_e)) {
              kt_tacocat_receive_process(main, i);

              main->setting.receive_polls.array[i].revents = 0;

              if (F_status_is_error(main->setting.state.status)) continue;
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
  void kt_tacocat_receive_process(kt_tacocat_main_t * const main, const f_number_unsigned_t index) {

    if (!main) return;

    kt_tacocat_socket_set_t * const set = &main->setting.receive.array[index];

    // This is a new packet (kt_tacocat_socket_flag_none_e).
    if (!(main->setting.receive.array[index].flag)) {
      main->setting.receive.array[index].flag = kt_tacocat_socket_flag_block_control_e;
      main->setting.receive.array[index].retry = 0;
      set->buffer.used = 0;
      set->socket.size_read = kt_tacocat_packet_read_d;
    }

    // Load the header of the new packet.
    if (main->setting.receive.array[index].flag & kt_tacocat_socket_flag_block_control_e) {
      kt_tacocat_receive_process_control(main, index);

      if (F_status_is_error(set->status) || set->buffer.used < kt_tacocat_packet_peek_d) {
        f_file_close_id(&set->socket.id_data);

        return;
      }

      // Reset the buffer to allow for reusing and writing to the file in blocks.
      set->buffer.used = 0;
      set->socket.size_read = kt_tacocat_packet_read_d;

      // Make sure the buffer is large enough for payload processing block reads.
      set->status = f_memory_array_increase_by(set->socket.size_read, sizeof(f_char_t), (void **) &set->buffer.string, &set->buffer.used, &set->buffer.size);
      macro_kt_receive_process_handle_error_exit_1(main, f_memory_array_increase_by, set->network, set->status, main->setting.receive.array[index].flag, &set->socket.id_data);
    }

    if (main->setting.receive.array[index].flag & kt_tacocat_socket_flag_block_payload_e) {
      size_t length_read = 0;

      set->status = f_socket_read_stream(&set->socket, 0, (void *) set->buffer.string, &length_read);
      macro_kt_receive_process_handle_error_exit_1(main, f_socket_read_stream, set->network, set->status, main->setting.receive.array[index].flag, &set->socket.id_data);

      if (length_read) {
        set->buffer.used = length_read;

        set->status = f_file_write(main->setting.receive.array[index].file, set->buffer, 0);

        // Keep going on error, but in the future more advanced error handling/recovery is needed to make this more robust.
        if (F_status_is_error(set->status)) {
          // @fixme The file name is not being saved, need to add the file name. For now just adding "set->socket.name" as a placeholder.
          kt_tacocat_print_error_on_file(&main->program.error, macro_kt_tacocat_f(f_file_write), kt_tacocat_receive_s, set->network, set->status, set->socket.name);
        }

        // Reset buffer used and increment counter.
        set->packet.payload.stop += set->buffer.used;
        set->buffer.used = 0;

        f_file_close_id(&set->socket.id_data);

        if (set->packet.payload.stop < set->packet.size) return;
      }

      main->setting.receive.array[index].flag -= kt_tacocat_socket_flag_block_payload_e;
    }

    // Done processing the Packet.
    f_file_close_id(&set->socket.id_data);
    main->setting.receive.array[index].flag = 0;

    if (set->buffer.size > kt_tacocat_max_maintain_d) {
      set->buffer.used = 0;

      set->status = f_memory_array_resize(kt_tacocat_max_maintain_d, sizeof(f_char_t), (void **) &set->buffer.string, &set->buffer.used, &set->buffer.size);

      // Report the resize error but do not fail.
      if (F_status_is_error(set->status)) {
        kt_tacocat_print_error_on(&main->program.error, macro_kt_tacocat_f(f_memory_array_resize), kt_tacocat_receive_s, set->network, set->status);
      }
    }
  }
#endif // _di_kt_tacocat_receive_process_

#ifndef _di_kt_tacocat_receive_process_control_
  void kt_tacocat_receive_process_control(kt_tacocat_main_t * const main, const f_number_unsigned_t index) {

    if (!main) return;

    kt_tacocat_socket_set_t * const set = &main->setting.receive.array[index];

    const size_t size_read = set->socket.size_read;
    size_t length_read = 0;

    set->status = f_socket_accept(&set->socket);

    // The socket failed to accept and so there is no data socket id to close.
    macro_kt_receive_process_begin_handle_error_exit_1(main, f_socket_accept, set->network, set->status, set->flag);

    set->status = f_memory_array_increase_by(kt_tacocat_packet_peek_d + 1, sizeof(f_char_t), (void **) &set->buffer.string, &set->buffer.used, &set->buffer.size);
    macro_kt_receive_process_begin_handle_error_exit_1(main, f_memory_array_increase_by, set->network, set->status, set->flag);

    set->socket.size_read = kt_tacocat_packet_peek_d;

    set->status = f_socket_read_stream(&set->socket, 0, (void *) (set->buffer.string + set->buffer.used), &length_read);

    set->socket.size_read = size_read;

    macro_kt_receive_process_begin_handle_error_exit_1(main, f_socket_read_stream, set->network, set->status, set->flag);

    set->buffer.used += length_read;

    // Continue if the packet header is not fully ready.
    if (set->buffer.used < kt_tacocat_packet_peek_d) {

      // Peek ahead to see if the client has closed the connection (all the intended data should have been transmitted).
      if (length_read) {
        memset(main->cache.peek, 0, kt_tacocat_cache_size_peek_d);

        set->socket.size_read = kt_tacocat_cache_size_peek_d - 1;
        length_read = 0;

        set->status = f_socket_read_stream(&set->socket, f_socket_flag_peek_e | f_socket_flag_wait_not_e, (void *) main->cache.peek, &length_read);

        set->socket.size_read = size_read;
      }

      // Connection is closed when length is 0, which means the packet is too small.
      if (!length_read) {
        kt_tacocat_print_error_on_packet_too_small(&main->program.error, kt_tacocat_receive_s, set->network, kt_tacocat_packet_peek_d, set->buffer.used);

        set->buffer.used = 0;
        main->setting.receive.array[index].retry = 0;
        set->status = F_status_set_error(F_packet_too_small);
        set->flag = 0;

        return;
      }

      ++main->setting.receive.array[index].retry;

      return;
    }

    set->status = f_fss_simple_packet_extract_range(set->buffer, &set->packet);
    macro_kt_receive_process_begin_handle_error_exit_1(main, f_fss_simple_packet_extract_range, set->network, set->status, set->flag);

    if (set->status == F_packet_too_small) {
      set->packet.control = 0;
      set->packet.size = 0;
    }

    if (set->packet.size < F_fss_simple_packet_block_header_size_d) {
      set->flag = 0;

      return;
    }

    if (main->setting.flag & kt_tacocat_main_flag_max_buffer_e) {
      if (set->packet.size > main->setting.max_buffer) {
        set->buffer.used = 0;

        if (set->buffer.size > kt_tacocat_max_maintain_d) {
          set->status = f_memory_array_resize(kt_tacocat_max_maintain_d, sizeof(f_char_t), (void **) &set->buffer.string, &set->buffer.used, &set->buffer.size);

          // Report the resize error but do not fail.
          if (F_status_is_error(set->status)) {
            kt_tacocat_print_error_on(&main->program.error, macro_kt_tacocat_f(f_memory_array_resize), kt_tacocat_receive_s, set->network, set->status);
          }
        }

        set->status = F_status_set_error(F_packet_too_large);
        set->flag = 0;

        kt_tacocat_print_error_on_buffer_too_large(&main->program.error, kt_tacocat_receive_s, set->network, main->setting.max_buffer, set->packet.size);

        return;
      }
    }

    set->flag |= kt_tacocat_socket_flag_block_payload_e;
    set->flag -= kt_tacocat_socket_flag_block_control_e;

    // The payload range "stop" is used to represent the total amount of bytes processed so far (uncluding the header).
    set->packet.payload.start = 0;
    set->packet.payload.stop = set->buffer.used - 1;
  }
#endif // _di_kt_tacocat_receive_process_control_

#ifdef __cplusplus
} // extern "C"
#endif
