#include "tacocat.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_tacocat_process_main_
  void kt_tacocat_process_main(kt_tacocat_main_t * const main) {

    if (!main) return;
    if (F_status_is_error(kt_tacocat_process_socket_set_error_has(main, kt_tacocat_long_receive_s, main->setting.receive))) return;
    if (F_status_is_error(kt_tacocat_process_socket_set_error_has(main, kt_tacocat_long_send_s, main->setting.send))) return;

    // @todo Make this threaded, if threading is enabled (if threading is disabled then fork).
    //       TacocaT is intended to be simple, so be lazy and create a thread/fork for every single receive and send.

    kt_tacocat_process_socket_set_receive(main);
    kt_tacocat_process_socket_set_send(main);

    // domain
    // PF_INET = ipv4
    // PF_INET6 = ipv6
    // type
    // SOCK_STREAM
    // SOCK_DGRAM
    // "struct sockaddr", "struct sockaddr_un", or "struct sockaddr_in"
    // protocol
    // f_socket_protocol_tcp
    // f_socket_protocol_udp

    //f_socket_connect

    // @todo:
    //   1: Establish connections.
    //   2: read / write from files.
    //   3: work or wait until told to terminate.
    //   4: terminate.

    kt_tacocat_process_socket_set_disconnect(main, &main->setting.receive);
    kt_tacocat_process_socket_set_disconnect(main, &main->setting.send);

    kt_tacocat_process_socket_set_error_handle(main, main->setting.receive);
    kt_tacocat_process_socket_set_error_handle(main, main->setting.send);
  }
#endif // _di_kt_tacocat_process_main_

#ifndef _di_kt_tacocat_process_socket_set_disconnect_
  void kt_tacocat_process_socket_set_disconnect(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set) {

    if (!main) return;

    if (!set) {
      main->setting.state.status = F_status_set_error(F_parameter);

      return;
    }

    f_status_t status = F_none;

    for (f_number_unsigned_t i = 0; i < set->sockets.used; ++i) {

      if (kt_tacocat_signal_check(main)) return;

      status = f_socket_disconnect(&set->sockets.array[i], f_socket_close_read_write_e);

      if (F_status_is_error_not(set->statuss.array[i]) && F_status_is_error(main->setting.state.status)) {
        set->statuss.array[i] = status;

        kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(f_socket_disconnect));
      }
    } // for
  }
#endif // _di_kt_tacocat_process_socket_set_disconnect_

#ifndef _di_kt_tacocat_process_socket_set_error_handle_
  void kt_tacocat_process_socket_set_error_handle(kt_tacocat_main_t * const main, const kt_tacocat_socket_set_t set) {

    if (!main) return;
    if (F_status_is_error(main->setting.state.status)) return;

    main->setting.state.status = F_none;

    for (f_number_unsigned_t i = 0; i < set.statuss.used; ++i) {

      if (kt_tacocat_signal_check(main)) return;

      if (F_status_is_error(set.statuss.array[i])) {
        main->setting.state.status = set.statuss.array[i];

        return;
      }
    } // for
  }
#endif // _di_kt_tacocat_process_socket_set_error_handle_

#ifndef _di_kt_tacocat_process_socket_set_error_has_
  f_status_t kt_tacocat_process_socket_set_error_has(kt_tacocat_main_t * const main, const f_string_static_t parameter, const kt_tacocat_socket_set_t set) {

    if (!main) {
      main->setting.state.status = F_status_set_error(F_parameter);

      kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(kt_tacocat_process_socket_set_error_has));

      return main->setting.state.status;
    }

    if (set.sockets.used != set.files.used || set.sockets.used != set.files.used || set.sockets.used != set.statuss.used || set.sockets.used != set.names.used || set.sockets.used != set.buffers.used) {
      main->setting.state.status = F_status_set_error(F_parameter);

      kt_tacocat_print_error_setting_socket_lengths_must_match(&main->program.error, parameter, set);

      return main->setting.state.status;
    }

    return F_none;
  }
#endif // _di_kt_tacocat_process_socket_set_error_has_

#ifndef _di_kt_tacocat_process_socket_set_receive_
  void kt_tacocat_process_socket_set_receive(kt_tacocat_main_t * const main) {

    if (!main) return;

    // Create, bind, and listen to the socket.
    for (f_number_unsigned_t i = 0; i < main->setting.receive.sockets.used; ++i) {

      if (kt_tacocat_signal_check(main)) return;
      if (F_status_is_error(main->setting.receive.statuss.array[i])) continue;

      main->setting.receive.statuss.array[i] = f_socket_create(&main->setting.receive.sockets.array[i]);

      if (F_status_is_error(main->setting.receive.statuss.array[i])) {
        main->setting.state.status = main->setting.receive.statuss.array[i];

        kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(f_socket_create));

        continue;
      }

      if (main->setting.receive.sockets.array[i].domain == f_socket_protocol_family_inet4_e) {
        main->setting.receive.statuss.array[i] = f_socket_bind_inet4(&main->setting.receive.sockets.array[i]);
      }
      else if (main->setting.receive.sockets.array[i].domain == f_socket_protocol_family_inet6_e) {
        main->setting.receive.statuss.array[i] = f_socket_bind_inet6(&main->setting.receive.sockets.array[i]);
      }
      else if (main->setting.receive.sockets.array[i].domain == f_socket_protocol_family_local_e) {
        main->setting.receive.statuss.array[i] = f_socket_bind_local(&main->setting.receive.sockets.array[i]);
      }
      else {
        main->setting.state.status = F_status_set_error(F_parameter);

        kt_tacocat_print_error_socket_protocol_unsupported(&main->program.error, main->setting.receive.names.array[i], main->setting.receive.sockets.array[i].domain);

        return;
      }

      if (F_status_is_error(main->setting.receive.statuss.array[i])) {
        main->setting.state.status = main->setting.receive.statuss.array[i];

        kt_tacocat_print_error(&main->program.error, main->setting.receive.sockets.array[i].domain == f_socket_protocol_family_inet4_e
          ? macro_kt_tacocat_f(f_socket_bind_inet4)
          : main->setting.receive.sockets.array[i].domain == f_socket_protocol_family_inet6_e
            ? macro_kt_tacocat_f(f_socket_bind_inet6)
            : macro_kt_tacocat_f(f_socket_bind_local)
        );

        continue;
      }

      main->setting.receive.statuss.array[i] = f_socket_listen(&main->setting.receive.sockets.array[i], kt_tacocat_backlog_max_d);

      if (F_status_is_error(main->setting.receive.statuss.array[i])) {
        main->setting.state.status = main->setting.receive.statuss.array[i];

        kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(f_socket_listen));

        continue;
      }

      if (main->setting.receive.sockets.array[i].id == -1) {
        main->setting.receive.polls.array[i].fd = -1;
        main->setting.receive.polls.array[i].events = 0;
        main->setting.receive.polls.array[i].revents = 0;
      }
      else {
        main->setting.receive.polls.array[i].fd = main->setting.receive.sockets.array[i].id;
        main->setting.receive.polls.array[i].events = f_poll_read_e | f_poll_urgent_e;
        main->setting.receive.polls.array[i].revents = 0;
      }
    } // for

    if (F_status_is_error_not(main->setting.state.status)) {
      // @todo this is where another process should poll/wait for connections and such (in another thread/fork).
      main->setting.state.status = f_file_poll(main->setting.receive.polls, 9000); // @todo temporarily set to 9 second(s).

      // @todo handle errors, but this will be in a fork/thread.

      main->setting.state.status = F_none;
    }
  }
#endif // _di_kt_tacocat_process_socket_set_receive_

#ifndef _di_kt_tacocat_process_socket_set_send_
  void kt_tacocat_process_socket_set_send(kt_tacocat_main_t * const main) {

    if (!main) return;

    for (f_number_unsigned_t i = 0; i < main->setting.send.sockets.used; ++i) {

      if (kt_tacocat_signal_check(main)) return;
      if (F_status_is_error(main->setting.send.statuss.array[i])) continue;

      main->setting.send.statuss.array[i] = f_socket_create(&main->setting.send.sockets.array[i]);

      if (F_status_is_error(main->setting.send.statuss.array[i])) {
        main->setting.state.status = main->setting.send.statuss.array[i];

        kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(f_socket_create));

        continue;
      }

      // @todo f_socket_bind().
    } // for

    if (F_status_is_error_not(main->setting.state.status)) {
      main->setting.state.status = F_none;
    }
  }
#endif // _di_kt_tacocat_process_socket_set_send_

#ifdef __cplusplus
} // extern "C"
#endif
