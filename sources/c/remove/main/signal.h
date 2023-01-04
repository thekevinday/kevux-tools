/**
 * Kevux Tools - Remove
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _kt_remove_signal_h
#define _kt_remove_signal_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Check to see if a signal is received.
 *
 * If main.signal is non-zero, then this handles the following signals:
 *   - F_signal_abort
 *   - F_signal_broken_pipe
 *   - F_signal_hangup
 *   - F_signal_interrupt
 *   - F_signal_quit
 *   - F_signal_termination
 *
 * There is a threaded and a non-threaded version of this.
 * The non-threaded version checks periodically using kt_remove_signal_check_d and updates main->signal_check as needed.
 * The threaded version checks the flag state which is set by a separate thread that is blocking until signal is received.
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_true on signal received.
 *   F_false otherwise.
 *
 * @see kt_remove_signal_handler()
 *
 * @see fll_program_standard_signal_received()
 */
#ifndef _di_kt_remove_signal_check_
  extern f_status_t kt_remove_signal_check(fll_program_data_t * const main);
#endif // _di_kt_remove_signal_check_

/**
 * Signal handler for signals/interrupts.
 *
 * This blocks until an expected signal is recieved.
 * When an expected signal is received it then sets the
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
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.signal_received, setting it to a received signal.
 *
 *   This alters setting.status:
 *     Errors with (error bit set) from: f_signal_open()
 *     Errors with (error bit set) from: f_signal_wait()
 *
 * @see f_signal_close()
 * @see f_signal_open()
 * @see f_signal_wait()
 */
#if !defined(_di_kt_remove_signal_handler_) && !defined(_di_thread_support_)
  extern void kt_remove_signal_handler(fll_program_data_t * const main, kt_remove_setting_t * const setting);
#endif // !defined(_di_kt_remove_signal_handler_) && !defined(_di_thread_support_)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_remove_signal_h
