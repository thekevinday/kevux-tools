#include "remove.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_remove_thread_signal_
  void * kt_remove_thread_signal(void * const main) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    if (main) {
      kt_remove_signal_handler((kt_remove_main_t *) main);
    }

    return 0;
  }
#endif // _di_kt_remove_thread_signal_

#ifdef __cplusplus
} // extern "C"
#endif
