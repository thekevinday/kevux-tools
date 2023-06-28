/**
 * Kevux Tools - TacocaT
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _kt_tacocat_thread_h
#define _kt_tacocat_thread_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Thread handler for signals/interrupts.
 *
 * If main.signal is non-zero, then this handles the following signals:
 *   - F_signal_abort
 *   - F_signal_broken_pipe
 *   - F_signal_hangup
 *   - F_signal_interrupt
 *   - F_signal_quit
 *   - F_signal_termination
 *
 * @param main
 *   The program and settings data.
 *
 *   Must be of type kt_tacocat_main_t.
 *
 * @return
 *   0, always.
 *
 * @see f_thread_cancel_state_set()
 *
 * @see kt_tacocat_signal_handler()
 */
#if !defined(_di_kt_tacocat_thread_signal_) && !defined(_di_thread_support_)
  extern void * kt_tacocat_thread_signal(void * const main);
#endif // !defined(_di_kt_tacocat_thread_signal_) && !defined(_di_thread_support_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_thread_h
