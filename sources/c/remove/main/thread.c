#include "remove.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_remove_thread_signal_
  void * kt_remove_thread_signal(void * const arguments) {

    f_thread_cancel_state_set(PTHREAD_CANCEL_DEFERRED, 0);

    kt_remove_signal_handler(macro_kt_remove_arguments(arguments)->main, macro_kt_remove_arguments(arguments)->setting);

    return 0;
  }
#endif // _di_kt_remove_thread_signal_

#ifdef __cplusplus
} // extern "C"
#endif
