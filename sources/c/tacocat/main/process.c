#include "tacocat.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_tacocat_process_main_
  void kt_tacocat_process_main(kt_tacocat_main_t * const main) {

    if (!main) return;

    if (main->setting.socket_receives.used != main->setting.file_receives.used && main->setting.socket_receives.used != main->setting.receives.used && main->setting.socket_receives.used != main->setting.status_receives.used) {
      main->setting.state.status = F_status_set_error(F_parameter);

      kt_tacocat_print_error_setting_socket_lengths_must_match(&main->program.error, kt_tacocat_long_receive_s, main->setting.receives.used, main->setting.file_receives.used, main->setting.socket_receives.used, main->setting.status_receives.used);

      return;
    }

    if (main->setting.socket_sends.used != main->setting.file_sends.used && main->setting.socket_sends.used != main->setting.sends.used && main->setting.socket_sends.used != main->setting.status_sends.used) {
      main->setting.state.status = F_status_set_error(F_parameter);

      kt_tacocat_print_error_setting_socket_lengths_must_match(&main->program.error, kt_tacocat_long_send_s, main->setting.sends.used, main->setting.file_sends.used, main->setting.socket_sends.used, main->setting.status_sends.used);

      return;
    }

    f_number_unsigned_t i = 0;

    // @todo Make this threaded, if threading is enabled (if threading is disabled then fork).
    //       TacocaT is intended to be simple, so be lazy and create a thread/fork for every single receive and send.

    // Create, bind, and listen to the socket.
    for (; i < main->setting.socket_receives.used; ++i) {

      if (kt_tacocat_signal_check(main)) return;

      main->setting.status_receives.array[i] = f_socket_create(&main->setting.socket_receives.array[i]);

      if (F_status_is_error(main->setting.status_receives.array[i])) {
        main->setting.state.status = main->setting.status_receives.array[i];

        kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(f_socket_create));

        continue;
      }

      if (main->setting.socket_receives.array[i].domain == f_socket_protocol_family_inet4_e) {
        main->setting.status_receives.array[i] = f_socket_bind_inet4(&main->setting.socket_receives.array[i]);
      }
      else if (main->setting.socket_receives.array[i].domain == f_socket_protocol_family_inet6_e) {
        main->setting.status_receives.array[i] = f_socket_bind_inet6(&main->setting.socket_receives.array[i]);
      }
      else if (main->setting.socket_receives.array[i].domain == f_socket_protocol_family_local_e) {
        main->setting.status_receives.array[i] = f_socket_bind_local(&main->setting.socket_receives.array[i]);
      }
      else {
        // @todo error, not supported.
      }

      if (F_status_is_error(main->setting.status_receives.array[i])) {
        main->setting.state.status = main->setting.status_receives.array[i];

        kt_tacocat_print_error(&main->program.error, main->setting.socket_receives.array[i].domain == f_socket_protocol_family_inet4_e
          ? macro_kt_tacocat_f(f_socket_bind_inet4)
          : main->setting.socket_receives.array[i].domain == f_socket_protocol_family_inet6_e
            ? macro_kt_tacocat_f(f_socket_bind_inet6)
            : macro_kt_tacocat_f(f_socket_bind_local)
        );

        continue;
      }

      main->setting.status_receives.array[i] = f_socket_listen(&main->setting.socket_receives.array[i], kt_tacocat_backlog_max_d);

      if (F_status_is_error(main->setting.status_receives.array[i])) {
        main->setting.state.status = main->setting.status_receives.array[i];

        kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(f_socket_listen));

        continue;
      }
    } // for

    for (i = 0; i < main->setting.socket_sends.used; ++i) {

      if (kt_tacocat_signal_check(main)) return;

      // @todo check to see if connection is one of "local", "inet" (ipv4), or "inet6" (ipv6) and configure socket appropriately.

      main->setting.status_sends.array[i] = f_socket_create(&main->setting.socket_sends.array[i]);

      if (F_status_is_error(main->setting.status_sends.array[i])) {
        main->setting.state.status = main->setting.status_sends.array[i];

        kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(f_socket_create));

        continue;
      }

      // @todo f_socket_bind().
    } // for

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

    // Disconnect.
    for (; i < main->setting.socket_receives.used; ++i) {

      if (kt_tacocat_signal_check(main)) return;

      main->setting.status_receives.array[i] = f_socket_disconnect(&main->setting.socket_receives.array[i], f_socket_close_read_write_e);

      if (F_status_is_error(main->setting.status_receives.array[i])) {
        main->setting.state.status = main->setting.status_receives.array[i];

        kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(f_socket_disconnect));
      }
    } // for

    for (i = 0; i < main->setting.socket_sends.used; ++i) {

      if (kt_tacocat_signal_check(main)) return;

      main->setting.status_sends.array[i] = f_socket_disconnect(&main->setting.socket_sends.array[i], f_socket_close_read_write_e);

      if (F_status_is_error(main->setting.status_sends.array[i])) {
        main->setting.state.status = main->setting.status_sends.array[i];

        kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(f_socket_disconnect));
      }
    } // for

    // Handle returning errors.
    if (F_status_is_error_not(main->setting.state.status)) {
      main->setting.state.status = F_none;

      for (i = 0; i < main->setting.socket_receives.used; ++i) {

        if (kt_tacocat_signal_check(main)) return;

        if (F_status_is_error(main->setting.status_receives.array[i])) {
          main->setting.state.status = main->setting.status_receives.array[i];
        }
      } // for

      for (i = 0; i < main->setting.socket_sends.used; ++i) {

        if (kt_tacocat_signal_check(main)) return;

        if (F_status_is_error(main->setting.status_sends.array[i])) {
          main->setting.state.status = main->setting.status_sends.array[i];
        }
      } // for
    }
  }
#endif // _di_kt_tacocat_process_main_

#ifdef __cplusplus
} // extern "C"
#endif
