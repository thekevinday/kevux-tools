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

          // @todo handle errors
          //if (F_status_is_error(main->setting.receive.statuss.array[i])) ... // @todo more work needed to clear error bit when a new read is ready.
        }
        else {
          // @todo handle error or F_time_out on main->setting.status_receive.
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

    uint16_t * const flag = &main->setting.receive.flags.array[index];
    uint16_t * const retry = &main->setting.receive.retrys.array[index];
    uint32_t * const total = &main->setting.receive.totals.array[index];
    f_poll_t * const poll = &main->setting.receive.polls.array[index];
    f_socket_t * const socket = &main->setting.receive.sockets.array[index];
    f_status_t * const status = &main->setting.receive.statuss.array[index];
    f_string_dynamic_t * const name = &main->setting.receive.names.array[index];
    f_string_dynamic_t * const buffer = &main->setting.receive.buffers.array[index];
    f_fss_simple_packet_range_t * const packet = &main->setting.receive.packets.array[index];

    size_t length_read = 0;

    // This is a new packet (kt_tacocat_socket_flag_none_e).
    if (!(*flag)) {
      *flag = kt_tacocat_socket_flag_block_begin_e;
      *retry = 0;
      *total = 0;
      buffer->used = 0;
      socket->size_read = kt_tacocat_packet_read_d;
    }

    const size_t size_read = socket->size_read;

    // @todo move this section into its own function call.
    // Load the header of the new packet.
    if ((*flag) & kt_tacocat_socket_flag_block_begin_e) {
      *status = f_socket_accept(socket);

      // The socket failed to accept and so there is no data socket id to close.
      macro_kt_receive_process_handle_error_exit_1(main, f_socket_accept, name, status, flag, 0);

      *status = f_memory_array_increase_by(kt_tacocat_packet_peek_d + 1, sizeof(f_char_t), (void **) &buffer->string, &buffer->used, &buffer->size);
      macro_kt_receive_process_handle_error_exit_1(main, f_memory_array_increase_by, name, status, flag, &socket->id_data);

      socket->size_read = kt_tacocat_packet_peek_d;

      *status = f_socket_read_stream(socket, 0, (void *) (buffer->string + buffer->used), &length_read);

      socket->size_read = size_read;

      macro_kt_receive_process_handle_error_exit_1(main, f_socket_read_stream, name, status, flag, &socket->id_data);

      buffer->used += length_read;

      // Continue if the packet header is not fully ready (@todo, implement a counter with a max length thaat prevents infinite loop waits, "retry" is intended for this).
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
          kt_tacocat_print_error_on_packet_too_small(&main->program.error, kt_tacocat_receive_s, *name, kt_tacocat_packet_peek_d, buffer->used);

          buffer->used = 0;
          *retry = 0;
          *status = F_status_set_error(F_packet_too_small);
          *flag -= kt_tacocat_socket_flag_block_begin_e;

          f_file_close_id(&socket->id_data);

          return;
        }

        ++(*retry);

        f_file_close_id(&socket->id_data);

        return;
      }

      packet->control.start = 1;
      packet->control.stop = 0;
      packet->size.start = 1;
      packet->size.stop = 0;
      packet->payload.start = 1;
      packet->payload.stop = 0;

      // @todo need to check/handle if all of the parts exists (want F_okay, but check F_partial, F_data_not, and F_valid_not (F_valid_not has error bit set).
      *status = f_fss_simple_packet_identify(*buffer, packet);
      macro_kt_receive_process_handle_error_exit_1(main, f_fss_simple_packet_identify, name, status, flag, &socket->id_data);

      // @todo this needs to be wrapped in big/little endian checks, but for now just use ntohl.
      *total = ntohl(*((uint32_t *) (buffer->string + 1)));

      if (*total <= F_fss_simple_packet_block_header_size_d) {
        // @todo handle error, perform memory clearing and possibly send try again message to client but for now, just close the connection gracefully.
        f_file_close_id(&socket->id_data);

        *flag -= kt_tacocat_socket_flag_block_begin_e;

        return;
      }

      if (main->setting.flag & kt_tacocat_main_flag_max_buffer_e) {
        if (*total > main->setting.max_buffer) {
          buffer->used = 0;

          if (buffer->size > kt_tacocat_max_maintain_d) {
            *status = f_memory_array_resize(kt_tacocat_max_maintain_d, sizeof(f_char_t), (void **) &buffer->string, &buffer->used, &buffer->size);

            // Report the resize error but do not fail.
            if (F_status_is_error(*status)) {
              kt_tacocat_print_error_on(&main->program.error, macro_kt_tacocat_f(f_memory_array_resize), kt_tacocat_receive_s, *name, *status);
            }
          }

          // @todo for all unrecoverable errors, make sure to drop/flush the packet to prevent processing and then reset the status code (otherwise an infinite error loop will occur, which is the current behavior).
          *status = F_status_set_error(F_packet_too_large);

          kt_tacocat_print_error_on_buffer_too_large(&main->program.error, kt_tacocat_receive_s, *name); // @todo pass total parameter to print requested packet size.

          // @todo send message to client that the packet is too large but for now, just close the connection gracefully.
          f_file_close_id(&socket->id_data);

          return;
        }
      }

      *flag -= kt_tacocat_socket_flag_block_begin_e;
      *flag |= kt_tacocat_socket_flag_block_control_e;
    }

    *status = f_memory_array_increase_by(socket->size_read, sizeof(f_char_t), (void **) &buffer->string, &buffer->used, &buffer->size);
    macro_kt_receive_process_handle_error_exit_2(main, f_memory_array_increase_by, name, status, flag, &socket->id_data);

    *status = f_socket_read_stream(socket, f_socket_flag_wait_not_e, (void *) buffer->string, &length_read);
    macro_kt_receive_process_handle_error_exit_2(main, f_socket_read_stream, name, status, flag, &socket->id_data);

    //kt_tacocat_socket_flag_none_e          = 0x0,
    //kt_tacocat_socket_flag_block_control_e = 0x1,
    //kt_tacocat_socket_flag_block_payload_e = 0x2,

    // f_socket_flag_peek_e,
    //f_socket_read_stream

    // For now just close the socket until the appropriate code gets written here.
    f_file_close_id(&socket->id_data);

    // @todo perform this check only when fully finished processing all of the packet parts (expected *total is reached).
    if (buffer->size > kt_tacocat_max_maintain_d) {
      buffer->used = 0;

      *status = f_memory_array_resize(kt_tacocat_max_maintain_d, sizeof(f_char_t), (void **) &buffer->string, &buffer->used, &buffer->size);

      // Report the resize error but do not fail.
      if (F_status_is_error(*status)) {
        kt_tacocat_print_error_on(&main->program.error, macro_kt_tacocat_f(f_memory_array_resize), kt_tacocat_receive_s, *name, *status);
      }
    }
  }
#endif // _di_kt_tacocat_receive_process_

#ifdef __cplusplus
} // extern "C"
#endif
