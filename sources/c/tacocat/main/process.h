/**
 * Kevux Tools - TacocaT
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _kt_tacocat_process_h
#define _kt_tacocat_process_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform the main TacocaT processing.
 *
 * @param main
 *   The main program and settings data.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 */
#ifndef _di_kt_tacocat_process_main_
  extern void kt_tacocat_process_main(kt_tacocat_main_t * const main);
#endif // _di_kt_tacocat_process_main_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_process_h
