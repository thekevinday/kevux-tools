/**
 * Kevux Tools - Remove
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _kt_remove_thread_h
#define _kt_remove_thread_h

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
 * @param arguments
 *   The thread arguments.
 *   Must be of type kt_remove_arguments_t.
 *
 * @return
 *   0, always.
 *
 * @see f_signal_mask()
 * @see f_signal_wait()
 */
#if !defined(_di_kt_remove_thread_signal_) && !defined(_di_thread_support_)
  extern void * kt_remove_thread_signal(void * const arguments);
#endif // !defined(_di_kt_remove_thread_signal_) && !defined(_di_thread_support_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_remove_thread_h
