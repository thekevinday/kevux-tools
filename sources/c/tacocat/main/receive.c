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

        for (i = 0; i < main->setting.receive.polls.used; ++i) {

          if (main->setting.receive.polls.array[i].fd == -1) continue;

          // @todo figure out what f_poll_urgent_e can be.
          if (main->setting.receive.polls.array[i].revents & (f_poll_read_e | f_poll_urgent_e)) {
            // @todo call receive
            kt_tacocat_receive_process(main, i);

            if (F_status_is_error(main->setting.state.status)) {
              // @todo print error.

              continue;
            }
          }
        } // for

        // @todo handle errors

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

    f_socket_t * const socket = &main->setting.receive.sockets.array[index];
    f_poll_t * const poll = &main->setting.receive.polls.array[index];

    if (poll->revents & f_poll_urgent_e) {
      // @todo then handle out of band, via f_socket_flag_out_of_band_e.
    }

    // f_socket_flag_peek_e,
    //f_socket_read_stream
  }
#endif // _di_kt_tacocat_receive_process_

#ifdef __cplusplus
} // extern "C"
#endif
