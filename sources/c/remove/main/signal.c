#include "remove.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_kt_remove_signal_check_) && defined(_di_thread_support_)
  f_status_t kt_remove_signal_check(fll_program_data_t * const main) {

    if (main->signal.id == -1) return F_false;

    if (!((++main->signal_check) % kt_remove_signal_check_d)) {
      if (fll_program_standard_signal_received(main)) return F_true;

      data->main->signal_check = 0;
    }

    return F_false;
  }
#endif // !defined(_di_kt_remove_signal_check_) && defined(_di_thread_support_)

#if !defined(_di_kt_remove_signal_check_) && !defined(_di_thread_support_)
  f_status_t kt_remove_signal_check(fll_program_data_t * const main) {

    if (main->signal.id == -1) return F_false;
    if (main->signal_received) return F_true;

    return F_false;
  }
#endif // !defined(_di_kt_remove_signal_check_) && !defined(_di_thread_support_)

#if !defined(_di_kt_remove_signal_handler_) && !defined(_di_thread_support_)
  void kt_remove_signal_handler(fll_program_data_t * const main, kt_remove_setting_t * const setting) {

    if (!main || !setting) return;

    siginfo_t information;
    f_array_length_t failsafe = 0;

    memset(&information, 0, sizeof(siginfo_t));

    main->signal_received = 0;

    f_signal_set_empty(&main->signal.set);
    f_signal_set_add(F_signal_abort, &main->signal.set);
    f_signal_set_add(F_signal_broken_pipe, &main->signal.set);
    f_signal_set_add(F_signal_hangup, &main->signal.set);
    f_signal_set_add(F_signal_interrupt, &main->signal.set);
    f_signal_set_add(F_signal_quit, &main->signal.set);
    f_signal_set_add(F_signal_termination, &main->signal.set);

    if (main->signal.id == -1) {
      setting->status_thread = f_signal_open(&main->signal);

      if (F_status_is_error(setting->status_thread)) {
        main->signal_received = F_signal_abort;

        return;
      }
    }

    do {
      memset(&information, 0, sizeof(siginfo_t));

      setting->status_thread = f_signal_wait(&main->signal.set, &information);

      if (F_status_is_error(setting->status_thread) && F_status_set_fine(setting->status_thread) != F_interrupt) {
        if (++failsafe >= kt_remove_signal_check_failsafe_d) break;
      }

      switch (information.si_signo) {
        case F_signal_abort:
        case F_signal_broken_pipe:
        case F_signal_hangup:
        case F_signal_interrupt:
        case F_signal_quit:
        case F_signal_termination:
          main->signal_received = information.si_signo;

          break;
      }

      failsafe = 0;
      setting->status_thread = F_none;

    } while (!main->signal_received);

    f_signal_close(&main->signal);

    if (F_status_is_error(setting->status_thread)) {
      main->signal_received = F_signal_abort;
    }
  }
#endif // !defined(_di_kt_remove_signal_handler_) && !defined(_di_thread_support_)

#ifdef __cplusplus
} // extern "C"
#endif
