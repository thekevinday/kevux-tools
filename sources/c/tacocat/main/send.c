#include "tacocat.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_tacocat_send_
  void * kt_tacocat_send(void * const void_main) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    if (!void_main) return 0;

    kt_tacocat_main_t * const main = (kt_tacocat_main_t *) void_main;

    kt_tacocat_process_socket_set_send(main);

    if (F_status_is_error_not(main->setting.status_send)) {
      // @todo
    }

    kt_tacocat_process_socket_sets_disconnect(main, &main->setting.send);

    kt_tacocat_process_socket_sets_error_handle(main, main->setting.send, &main->setting.status_send);

    if (F_status_is_error_not(main->setting.status_send)) {
      main->setting.status_send = F_okay;
    }

    return 0;
  }
#endif // _di_kt_tacocat_send_

#ifdef __cplusplus
} // extern "C"
#endif
