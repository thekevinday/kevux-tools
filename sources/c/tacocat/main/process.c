#include "tacocat.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_tacocat_process_main_
  void kt_tacocat_process_main(kt_tacocat_main_t * const main) {

    if (!main) return;
    if (F_status_is_error(kt_tacocat_process_socket_set_error_has(main, kt_tacocat_long_receive_s, main->setting.receive, &main->setting.status_receive))) return;
    if (F_status_is_error(kt_tacocat_process_socket_set_error_has(main, kt_tacocat_long_send_s, main->setting.send, &main->setting.status_send))) return;

    #ifdef _di_thread_support_
      // @todo implement fork and wait for both receive and send.
    #else
      {
        if (main->setting.flag & kt_tacocat_main_flag_receive_e) {
          memset(&main->thread.id_receive, 0, sizeof(f_thread_id_t));

          main->setting.state.status = f_thread_create(0, &main->thread.id_receive, kt_tacocat_receive, (void *) main);
        }

        if (F_status_is_error_not(main->setting.state.status)) {
          if (main->setting.flag & kt_tacocat_main_flag_send_e) {
            memset(&main->thread.id_send, 0, sizeof(f_thread_id_t));

            main->setting.state.status = f_thread_create(0, &main->thread.id_send, kt_tacocat_send, (void *) main);

            if (F_status_is_error(main->setting.state.status) && (main->setting.flag & kt_tacocat_main_flag_receive_e)) {
              f_thread_cancel(main->thread.id_receive);
            }
          }
        }

        if (F_status_is_error(main->setting.state.status)) {
          kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(f_thread_create));
        }
      }

      if (main->setting.flag & kt_tacocat_main_flag_receive_e) {
        f_thread_join(main->thread.id_receive, 0);

        if (F_status_is_error(main->setting.status_receive)) {
          main->setting.state.status = main->setting.status_receive;
        }
      }

      if (main->setting.flag & kt_tacocat_main_flag_send_e) {
        f_thread_join(main->thread.id_send, 0);

        if (F_status_is_error(main->setting.status_send) && F_status_is_error_not(main->setting.state.status)) {
          main->setting.state.status = main->setting.status_send;
        }
      }
    #endif // _di_thread_support_

    if (F_status_is_error_not(main->setting.state.status)) {
      main->setting.state.status = F_okay;
    }
  }
#endif // _di_kt_tacocat_process_main_

#ifndef _di_kt_tacocat_process_socket_set_error_has_
  f_status_t kt_tacocat_process_socket_set_error_has(kt_tacocat_main_t * const main, const f_string_static_t parameter, const kt_tacocat_socket_sets_t set, f_status_t * const status) {

    if (!main || !status) {
      if (status) {
        *status = F_status_set_error(F_parameter);
      }

      kt_tacocat_print_error_status(&main->program.error, macro_kt_tacocat_f(kt_tacocat_process_socket_set_error_has), *status);

      return F_status_set_error(F_parameter);
    }

    return F_okay;
  }
#endif // _di_kt_tacocat_process_socket_set_error_has_

#ifndef _di_kt_tacocat_process_socket_set_receive_
  void kt_tacocat_process_socket_set_receive(kt_tacocat_main_t * const main) {

    if (!main || F_status_is_error(main->setting.status_receive)) return;

    int value_socket = 0;

    for (f_number_unsigned_t i = 0; i < main->setting.receive.used; ++i) {

      if (kt_tacocat_signal_check(main)) return;
      if (F_status_is_error(main->setting.receive.array[i].status)) continue;

      main->setting.receive.array[i].socket.id = -1;
      main->setting.receive.array[i].socket.id_data = -1;

      main->setting.receive.array[i].status = f_socket_create(&main->setting.receive.array[i].socket);

      if (F_status_is_error(main->setting.receive.array[i].status)) {
        main->setting.status_receive = main->setting.receive.array[i].status;

        kt_tacocat_print_error_status(&main->program.error, macro_kt_tacocat_f(f_socket_create), main->setting.status_receive);

        continue;
      }

      // Make the socket re-usable.
      {
        value_socket = 1;

        main->setting.receive.array[i].status = f_socket_option_set(&main->setting.receive.array[i].socket, SOL_SOCKET, f_socket_option_address_reuse_e | f_socket_option_port_reuse_e, &value_socket, sizeof(int));

        if (F_status_is_error(main->setting.receive.array[i].status)) {
          main->setting.status_receive = main->setting.receive.array[i].status;

          kt_tacocat_print_error_status(&main->program.error, macro_kt_tacocat_f(f_socket_option_set), main->setting.status_receive);

          continue;
        }
      }

      for (main->setting.receive.array[i].retry = 0; main->setting.receive.array[i].retry < kt_tacocat_startup_retry_max_d; ++main->setting.receive.array[i].retry) {

        if (main->setting.receive.array[i].socket.domain == f_socket_protocol_family_inet4_e) {
          main->setting.receive.array[i].status = f_socket_bind_inet4(&main->setting.receive.array[i].socket);
        }
        else if (main->setting.receive.array[i].socket.domain == f_socket_protocol_family_inet6_e) {
          main->setting.receive.array[i].status = f_socket_bind_inet6(&main->setting.receive.array[i].socket);
        }
        else if (main->setting.receive.array[i].socket.domain == f_socket_protocol_family_local_e) {
          main->setting.receive.array[i].status = f_socket_bind_local(&main->setting.receive.array[i].socket);
        }
        else {
          main->setting.status_receive = F_status_set_error(F_parameter);

          kt_tacocat_print_error_socket_protocol_unsupported(&main->program.error, main->setting.receive.array[i].network, main->setting.receive.array[i].socket.domain);

          return;
        }

        if (F_status_set_fine(main->setting.receive.array[i].status) == F_busy_address) {
          if (main->setting.receive.array[i].retry < kt_tacocat_startup_retry_max_d) {
            kt_tacocat_print_warning_on_busy(&main->program.warning, kt_tacocat_receive_s, main->setting.receive.array[i].network, main->setting.receive.array[i].retry + 1);

            struct timespec time = { 0 };

            main->setting.receive.array[i].status = f_time_spec_millisecond(kt_tacocat_startup_retry_delay_second_d, kt_tacocat_startup_retry_delay_millisecond_d, &time);

            if (F_status_is_error_not(main->setting.receive.array[i].status)) {
              nanosleep(&time, 0);
            }

            if (main->program.signal_received) {
              main->setting.status_receive = F_status_set_error(F_interrupt);

              return;
            }

            main->setting.receive.array[i].status = F_status_set_error(F_busy_address);

            continue;
          }
        }

        break;
      } // for

      if (F_status_is_error_not(main->setting.receive.array[i].status) && main->setting.receive.array[i].retry < kt_tacocat_startup_retry_max_d) {
        main->setting.receive.array[i].status = F_okay;
      }

      main->setting.receive.array[i].retry = 0;

      if (F_status_is_error(main->setting.receive.array[i].status)) {
        main->setting.status_receive = main->setting.receive.array[i].status;

        if (F_status_set_fine(main->setting.status_receive) == F_busy_address) {
          kt_tacocat_print_error_on_busy(&main->program.error, kt_tacocat_receive_s, main->setting.receive.array[i].network);
        }
        else {
          kt_tacocat_print_error_status(&main->program.error, main->setting.receive.array[i].socket.domain == f_socket_protocol_family_inet4_e
            ? macro_kt_tacocat_f(f_socket_bind_inet4)
            : main->setting.receive.array[i].socket.domain == f_socket_protocol_family_inet6_e
              ? macro_kt_tacocat_f(f_socket_bind_inet6)
              : macro_kt_tacocat_f(f_socket_bind_local),
            main->setting.status_receive
          );
        }

        continue;
      }

      main->setting.receive.array[i].status = f_socket_listen(&main->setting.receive.array[i].socket, kt_tacocat_max_backlog_d);

      if (F_status_is_error(main->setting.receive.array[i].status)) {
        main->setting.status_receive = main->setting.receive.array[i].status;

        kt_tacocat_print_error_status(&main->program.error, macro_kt_tacocat_f(f_socket_listen), main->setting.status_receive);

        continue;
      }

      if (main->setting.receive.array[i].socket.id == -1) {
        main->setting.receive_polls.array[i].fd = -1;
        main->setting.receive_polls.array[i].events = 0;
        main->setting.receive_polls.array[i].revents = 0;
      }
      else {
        main->setting.receive_polls.array[i].fd = main->setting.receive.array[i].socket.id;
        main->setting.receive_polls.array[i].events = f_poll_read_e;
        main->setting.receive_polls.array[i].revents = 0;
      }
    } // for

    if (F_status_is_error_not(main->setting.status_receive)) {
      main->setting.status_receive = F_okay;
    }
  }
#endif // _di_kt_tacocat_process_socket_set_receive_

#ifndef _di_kt_tacocat_process_socket_set_send_
  void kt_tacocat_process_socket_set_send(kt_tacocat_main_t * const main) {

    if (!main || F_status_is_error(main->setting.status_send)) return;

    int value_socket = 0;

    for (f_number_unsigned_t i = 0; i < main->setting.send.used; ++i) {

      if (kt_tacocat_signal_check(main)) return;
      if (F_status_is_error(main->setting.send.array[i].status)) continue;

      main->setting.send.array[i].status = f_socket_create(&main->setting.send.array[i].socket);

      if (F_status_is_error(main->setting.send.array[i].status)) {
        main->setting.status_send = main->setting.send.array[i].status;

        kt_tacocat_print_error_status(&main->program.error, macro_kt_tacocat_f(f_socket_create), main->setting.status_send);

        continue;
      }

      // Make the socket re-usable.
      {
        value_socket = 1;

        main->setting.send.array[i].status = f_socket_option_set(&main->setting.send.array[i].socket, SOL_SOCKET, f_socket_option_address_reuse_e | f_socket_option_port_reuse_e, &value_socket, sizeof(int));

        if (F_status_is_error(main->setting.send.array[i].status)) {
          main->setting.status_send = main->setting.send.array[i].status;

          kt_tacocat_print_error_status(&main->program.error, macro_kt_tacocat_f(f_socket_option_set), main->setting.status_send);

          continue;
        }
      }

      for (main->setting.send.array[i].retry = 0; main->setting.send.array[i].retry < kt_tacocat_startup_retry_max_d; ++main->setting.send.array[i].retry) {

        if (main->setting.send.array[i].socket.domain == f_socket_protocol_family_inet4_e || main->setting.send.array[i].socket.domain == f_socket_protocol_family_inet6_e || main->setting.send.array[i].socket.domain == f_socket_protocol_family_local_e) {
          main->setting.send.array[i].status = f_socket_connect(main->setting.send.array[i].socket); // @fixme this is currently failing because part of the parameters is invalid (figure out why).

          // The id_data socket ID is the same when sending (writing) to the socket.
          if (F_status_is_error_not(main->setting.send.array[i].status)) {
            main->setting.send.array[i].socket.id_data = main->setting.send.array[i].socket.id;
          }

          // Treat invalid file descriptor as an error as the descriptor should be valid at this point in time.
          if (main->setting.send.array[i].status == F_file_descriptor) {
            main->setting.send.array[i].status = F_status_set_error(F_file_descriptor);
          }
        }
        else {
          main->setting.status_send = F_status_set_error(F_parameter);

          kt_tacocat_print_error_socket_protocol_unsupported(&main->program.error, main->setting.send.array[i].network, main->setting.send.array[i].socket.domain);

          return;
        }

        if (F_status_set_fine(main->setting.send.array[i].status) == F_busy_address) {
          if (main->setting.send.array[i].retry < kt_tacocat_startup_retry_max_d) {
            kt_tacocat_print_warning_on_busy(&main->program.warning, kt_tacocat_send_s, main->setting.send.array[i].network, main->setting.send.array[i].retry + 1);

            struct timespec time = { 0 };

            main->setting.send.array[i].status = f_time_spec_millisecond(kt_tacocat_startup_retry_delay_second_d, kt_tacocat_startup_retry_delay_millisecond_d, &time);

            if (F_status_is_error_not(main->setting.send.array[i].status)) {
              nanosleep(&time, 0);
            }

            if (main->program.signal_received) {
              main->setting.status_send = F_status_set_error(F_interrupt);

              return;
            }

            main->setting.send.array[i].status = F_status_set_error(F_busy_address);

            continue;
          }
        }

        break;
      } // for

      if (F_status_is_error_not(main->setting.send.array[i].status) && main->setting.send.array[i].retry < kt_tacocat_startup_retry_max_d) {
        main->setting.send.array[i].status = F_okay;
      }

      main->setting.send.array[i].retry = 0;

      if (F_status_is_error(main->setting.send.array[i].status)) {
        main->setting.status_send = main->setting.send.array[i].status;

        if (F_status_set_fine(main->setting.status_send) == F_busy_address) {
          kt_tacocat_print_error_on_busy(&main->program.error, kt_tacocat_send_s, main->setting.send.array[i].network);
        }
        else {
          kt_tacocat_print_error_status(&main->program.error, macro_kt_tacocat_f(f_socket_connect), main->setting.status_send);
        }

        continue;
      }

      if (main->setting.send.array[i].socket.id == -1) {
        main->setting.send_polls.array[i].fd = -1;
        main->setting.send_polls.array[i].events = 0;
        main->setting.send_polls.array[i].revents = 0;
      }
      else {
        // @todo do not forget to utilize the poll fd.
        main->setting.send_polls.array[i].fd = main->setting.send.array[i].socket.id;
        main->setting.send_polls.array[i].events = f_poll_write_e;
        main->setting.send_polls.array[i].revents = 0;
      }
    } // for

    if (F_status_is_error_not(main->setting.status_send)) {
      main->setting.status_send = F_okay;
    }
  }
#endif // _di_kt_tacocat_process_socket_set_send_

#ifndef _di_kt_tacocat_process_socket_sets_disconnect_
  f_status_t kt_tacocat_process_socket_sets_disconnect(kt_tacocat_main_t * const main, kt_tacocat_socket_sets_t * const sets) {

    if (!main || !sets) return F_status_set_error(F_parameter);

    {
      f_status_t status = F_none;

      for (f_number_unsigned_t i = 0; i < sets->used ; ++i) {

        f_file_close(&sets->array[i].file);
        f_file_close_id(&sets->array[i].socket.id_data);

        status = f_socket_disconnect(&sets->array[i].socket, main->program.signal_received ? f_socket_close_fast_e : f_socket_close_read_write_e);

        if (F_status_is_error(status)) {
          f_socket_disconnect(&sets->array[i].socket, f_socket_close_read_write_e);
        }

        sets->array[i].socket.id = -1;
        sets->array[i].socket.id_data = -1;
      } // for
    }

    return F_okay;
  }
#endif // _di_kt_tacocat_process_socket_sets_disconnect_

#ifndef _di_kt_tacocat_process_socket_sets_error_handle_
  void kt_tacocat_process_socket_sets_error_handle(kt_tacocat_main_t * const main, const kt_tacocat_socket_sets_t sets, f_status_t * const status) {

    if (!main || !status) return;
    if (F_status_is_error(*status)) return;

    *status = F_okay;

    for (f_number_unsigned_t i = 0; i < sets.used; ++i) {

      if (kt_tacocat_signal_check(main)) return;

      if (F_status_is_error(sets.array[i].status)) {
        *status = sets.array[i].status;

        return;
      }
    } // for
  }
#endif // _di_kt_tacocat_process_socket_sets_error_handle_

#ifdef __cplusplus
} // extern "C"
#endif
