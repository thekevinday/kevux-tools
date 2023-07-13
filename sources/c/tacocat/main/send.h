/**
 * Kevux Tools - TacocaT
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _kt_tacocat_send_h
#define _kt_tacocat_send_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform the send operation for the send sockets.
 *
 * @param main
 *   The main program and settings data.
 *
 *   Must be of type kt_tacocat_main_t.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *     F_child on child process exiting.
 *
 * @return
 *   0, always.
 */
#ifndef _di_kt_tacocat_send_
  extern void * kt_tacocat_send(void * const main);
#endif // _di_kt_tacocat_send_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_send_h
