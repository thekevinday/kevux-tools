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
        main->setting.status_receive = f_file_poll(main->setting.receive.polls, main->setting.interval);

        if (main->program.signal_received) {
          main->setting.status_receive = F_status_set_error(F_interrupt);

          return 0;
        }

        // Skip if status is an error or is F_time_out.
        if (main->setting.status_receive == F_okay) {
          for (i = 0; i < main->setting.receive.polls.used; ++i) {

            if (main->setting.receive.polls.array[i].fd == -1) continue;

            if (main->setting.receive.polls.array[i].revents & (f_poll_read_e)) {
              kt_tacocat_receive_process(main, i);

              main->setting.receive.polls.array[i].revents = 0;

              if (F_status_is_error(main->setting.state.status)) continue;
            }
          } // for
        }

      } while (F_status_is_error_not(main->setting.status_receive));
    }

    kt_tacocat_process_socket_set_disconnect(main, &main->setting.receive);

    kt_tacocat_process_socket_set_error_handle(main, main->setting.receive, &main->setting.status_receive);

    if (F_status_is_error_not(main->setting.status_receive)) {
      main->setting.status_receive = F_okay;
    }

    return 0;
  }
#endif // _di_kt_tacocat_receive_

#ifndef _di_kt_tacocat_receive_process_
  void kt_tacocat_receive_process(kt_tacocat_main_t * const main, const f_number_unsigned_t index) {

    if (!main) return;

    f_socket_t * const socket = &main->setting.receive.sockets.array[index];
    f_status_t * const status = &main->setting.receive.statuss.array[index];
    f_string_dynamic_t * const network = &main->setting.receive.networks.array[index];
    f_string_dynamic_t * const buffer = &main->setting.receive.buffers.array[index];
    f_fss_simple_packet_range_t * const packet = &main->setting.receive.packets.array[index];

    // This is a new packet (kt_tacocat_socket_flag_none_e).
    if (!(main->setting.receive.flags.array[index])) {
      main->setting.receive.flags.array[index] = kt_tacocat_socket_flag_block_control_e;
      main->setting.receive.retrys.array[index] = 0;
      buffer->used = 0;
      socket->size_read = kt_tacocat_packet_read_d;
    }

    // Load the header of the new packet.
    if (main->setting.receive.flags.array[index] & kt_tacocat_socket_flag_block_control_e) {
      kt_tacocat_receive_process_control(main, index);

      if (F_status_is_error(*status) || buffer->used < kt_tacocat_packet_peek_d) {
        f_file_close_id(&socket->id_data);

        return;
      }

      // Reset the buffer to allow for reusing and writing to the file in blocks.
      buffer->used = 0;
      socket->size_read = kt_tacocat_packet_read_d;

      // Make sure the buffer is large enough for payload processing block reads.
      *status = f_memory_array_increase_by(socket->size_read, sizeof(f_char_t), (void **) &buffer->string, &buffer->used, &buffer->size);
      macro_kt_receive_process_handle_error_exit_1(main, f_memory_array_increase_by, network, status, main->setting.receive.flags.array[index], &socket->id_data);
    }

    if (main->setting.receive.flags.array[index] & kt_tacocat_socket_flag_block_payload_e) {
      size_t length_read = 0;

      *status = f_socket_read_stream(socket, 0, (void *) buffer->string, &length_read);
      macro_kt_receive_process_handle_error_exit_1(main, f_socket_read_stream, network, status, main->setting.receive.flags.array[index], &socket->id_data);

      if (length_read) {
        buffer->used = length_read;

        *status = f_file_write(main->setting.receive.files.array[index], *buffer, 0);

        // Keep going on error, but in the future more advanced error handling/recovery is needed to make this more robust.
        if (F_status_is_error(*status)) {
          // @fixme The file name is not being saved, need to add the file name. For now just adding "socket->name" as a placeholder.
          kt_tacocat_print_error_on_file(&main->program.error, macro_kt_tacocat_f(f_file_write), kt_tacocat_receive_s, *network, *status, socket->name);
        }

        // Reset buffer used and increment counter.
        main->setting.receive.packets.array[index].payload.stop += buffer->used;
        buffer->used = 0;

        f_file_close_id(&socket->id_data);

        if (main->setting.receive.packets.array[index].payload.stop < main->setting.receive.packets.array[index].size) return;
      }

      main->setting.receive.flags.array[index] -= kt_tacocat_socket_flag_block_payload_e;
    }

    // Done processing the Packet.
    f_file_close_id(&socket->id_data);
    main->setting.receive.flags.array[index] = 0;

    if (buffer->size > kt_tacocat_max_maintain_d) {
      buffer->used = 0;

      *status = f_memory_array_resize(kt_tacocat_max_maintain_d, sizeof(f_char_t), (void **) &buffer->string, &buffer->used, &buffer->size);

      // Report the resize error but do not fail.
      if (F_status_is_error(*status)) {
        kt_tacocat_print_error_on(&main->program.error, macro_kt_tacocat_f(f_memory_array_resize), kt_tacocat_receive_s, *network, *status);
      }
    }
  }
#endif // _di_kt_tacocat_receive_process_

#ifndef _di_kt_tacocat_receive_process_control_
  void kt_tacocat_receive_process_control(kt_tacocat_main_t * const main, const f_number_unsigned_t index) {

    if (!main) return;

    uint16_t * const flag = &main->setting.receive.flags.array[index];
    f_socket_t * const socket = &main->setting.receive.sockets.array[index];
    f_status_t * const status = &main->setting.receive.statuss.array[index];
    f_string_dynamic_t * const network = &main->setting.receive.networks.array[index];
    f_string_dynamic_t * const buffer = &main->setting.receive.buffers.array[index];

    const size_t size_read = socket->size_read;
    size_t length_read = 0;

    *status = f_socket_accept(socket);

    // The socket failed to accept and so there is no data socket id to close.
    macro_kt_receive_process_begin_handle_error_exit_1(main, f_socket_accept, network, status, flag);

    *status = f_memory_array_increase_by(kt_tacocat_packet_peek_d + 1, sizeof(f_char_t), (void **) &buffer->string, &buffer->used, &buffer->size);
    macro_kt_receive_process_begin_handle_error_exit_1(main, f_memory_array_increase_by, network, status, flag);

    socket->size_read = kt_tacocat_packet_peek_d;

    *status = f_socket_read_stream(socket, 0, (void *) (buffer->string + buffer->used), &length_read);

    socket->size_read = size_read;

    macro_kt_receive_process_begin_handle_error_exit_1(main, f_socket_read_stream, network, status, flag);

    buffer->used += length_read;

    // Continue if the packet header is not fully ready.
    if (buffer->used < kt_tacocat_packet_peek_d) {

      // Peek ahead to see if the client has closed the connection (all the intended data should have been transmitted).
      if (length_read) {
        memset(main->cache.peek, 0, kt_tacocat_cache_size_peek_d);

        socket->size_read = kt_tacocat_cache_size_peek_d - 1;
        length_read = 0;

        *status = f_socket_read_stream(socket, f_socket_flag_peek_e | f_socket_flag_wait_not_e, (void *) main->cache.peek, &length_read);

        socket->size_read = size_read;
      }

      // Connection is closed when length is 0, which means the packet is too small.
      if (!length_read) {
        kt_tacocat_print_error_on_packet_too_small(&main->program.error, kt_tacocat_receive_s, *network, kt_tacocat_packet_peek_d, buffer->used);

        buffer->used = 0;
        main->setting.receive.retrys.array[index] = 0;
        *status = F_status_set_error(F_packet_too_small);
        *flag = 0;

        return;
      }

      ++main->setting.receive.retrys.array[index];

      return;
    }

    *status = f_fss_simple_packet_extract_range(*buffer, &main->setting.receive.packets.array[index]);
    macro_kt_receive_process_begin_handle_error_exit_1(main, f_fss_simple_packet_extract_range, network, status, flag);

    if (*status == F_packet_too_small) {
      main->setting.receive.packets.array[index].control = 0;
      main->setting.receive.packets.array[index].size = 0;
    }

    if (main->setting.receive.packets.array[index].size < F_fss_simple_packet_block_header_size_d) {
      *flag = 0;

      return;
    }

    if (main->setting.flag & kt_tacocat_main_flag_max_buffer_e) {
      if (main->setting.receive.packets.array[index].size > main->setting.max_buffer) {
        buffer->used = 0;

        if (buffer->size > kt_tacocat_max_maintain_d) {
          *status = f_memory_array_resize(kt_tacocat_max_maintain_d, sizeof(f_char_t), (void **) &buffer->string, &buffer->used, &buffer->size);

          // Report the resize error but do not fail.
          if (F_status_is_error(*status)) {
            kt_tacocat_print_error_on(&main->program.error, macro_kt_tacocat_f(f_memory_array_resize), kt_tacocat_receive_s, *network, *status);
          }
        }

        *status = F_status_set_error(F_packet_too_large);
        *flag = 0;

        kt_tacocat_print_error_on_buffer_too_large(&main->program.error, kt_tacocat_receive_s, *network, main->setting.max_buffer, main->setting.receive.packets.array[index].size);

        return;
      }
    }

    *flag |= kt_tacocat_socket_flag_block_payload_e;
    *flag -= kt_tacocat_socket_flag_block_control_e;

    // The payload range "stop" is used to represent the total amount of bytes processed so far (uncluding the header).
    main->setting.receive.packets.array[index].payload.start = 0;
    main->setting.receive.packets.array[index].payload.stop = buffer->used - 1;
  }
#endif // _di_kt_tacocat_receive_process_control_

#ifdef __cplusplus
} // extern "C"
#endif
