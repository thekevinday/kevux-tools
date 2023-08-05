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
        if (main->setting.status_receive == F_none) {

          for (i = 0; i < main->setting.receive.polls.used; ++i) {

            if (main->setting.receive.polls.array[i].fd == -1) continue;

            // @todo figure out what f_poll_urgent_e can be.
            if (main->setting.receive.polls.array[i].revents & (f_poll_read_e | f_poll_urgent_e)) {
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
      main->setting.status_receive = F_none;
    }

    return 0;
  }
#endif // _di_kt_tacocat_receive_

#ifndef _di_kt_tacocat_receive_process_
  void kt_tacocat_receive_process(kt_tacocat_main_t * const main, const f_number_unsigned_t index) {

    uint16_t * const flag = &main->setting.receive.flags.array[index];
    f_socket_t * const socket = &main->setting.receive.sockets.array[index];
    f_poll_t * const poll = &main->setting.receive.polls.array[index];
    f_status_t * const status = &main->setting.receive.statuss.array[index];
    f_string_dynamic_t * const name = &main->setting.receive.names.array[index];
    f_string_dynamic_t * const buffer = &main->setting.receive.buffers.array[index];
    f_fss_simple_packet_range_t * const packet = &main->setting.receive.packets.array[index];

    //if (poll->revents & f_poll_urgent_e) { // handle out of band, via f_socket_flag_out_of_band_e?

    *status = f_string_dynamic_increase_by(socket->size_read, buffer);

    if (F_status_is_error(*status)) {
      kt_tacocat_print_error_on(&main->program.error, macro_kt_tacocat_f(f_string_dynamic_increase_by), kt_tacocat_receive_s, *name, *status);

      return;
    }

    size_t length = 0;

    // This is a new packet (kt_tacocat_socket_flag_none_e).
    if (!(*flag)) {
      buffer->used = 0;
    }

    *status = f_string_dynamic_increase_by(socket->size_read, buffer);

    if (F_status_is_error(*status)) {
      kt_tacocat_print_error_on(&main->program.error, macro_kt_tacocat_f(f_string_dynamic_increase_by), kt_tacocat_receive_s, *name, *status);

      return;
    }

    // This is a new packet (kt_tacocat_socket_flag_none_e).
    if (!(*flag)) {
      *status = f_socket_accept(socket);

      if (F_status_is_error(*status)) {
        kt_tacocat_print_error_on(&main->program.error, macro_kt_tacocat_f(f_socket_accept), kt_tacocat_receive_s, *name, *status);

        return;
      }

      socket->size_read = kt_tacocat_packet_peek_d;
      *status = f_socket_read_stream(socket, f_socket_flag_peek_e, (void *) &buffer->string, &length);

      if (F_status_is_error(*status)) {
        kt_tacocat_print_error_on(&main->program.error, macro_kt_tacocat_f(f_socket_read_stream), kt_tacocat_receive_s, *name, *status);

        f_file_close_id(&socket->id_data);

        return;
      }

      packet->control.start = 1;
      packet->control.stop = 0;
      packet->size.start = 1;
      packet->size.stop = 0;
      packet->payload.start = 1;
      packet->payload.stop = 0;

      *status = f_fss_simple_packet_identify(*buffer, packet);

      return;
    }

    socket->size_read = kt_tacocat_packet_read_d;

    //kt_tacocat_socket_flag_none_e          = 0x0,
    //kt_tacocat_socket_flag_block_control_e = 0x1,
    //kt_tacocat_socket_flag_block_payload_e = 0x2,

    // f_socket_flag_peek_e,
    //f_socket_read_stream

    // For now just close the socket until the appropriate code gets written here.
    f_file_close_id(&socket->id_data);
  }
#endif // _di_kt_tacocat_receive_process_

#ifdef __cplusplus
} // extern "C"
#endif
