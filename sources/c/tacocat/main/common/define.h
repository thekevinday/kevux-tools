/**
 * Kevux Tools - TacocaT
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common define types.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _kt_tacocat_common_define_h
#define _kt_tacocat_common_define_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program defines.
 *
 * kt_tacocat_allocation_*_d:
 *   - console: An allocation step used for small buffers specifically for console parameter.
 *   - large:   An allocation step used for buffers that are anticipated to have large buffers.
 *   - small:   An allocation step used for buffers that are anticipated to have small buffers.
 *
 * kt_tacocat_signal_*_d:
 *   - check:          When not using threads, this is how often to perform the check (lower numbers incur more kernel I/O).
 *   - check_failsafe: When using threads, how many consecutive failures to check signal before aborting (as a recursion failsafe).
 */
#ifndef _di_kt_tacocat_d_
  #define kt_tacocat_allocation_console_d 4
  #define kt_tacocat_allocation_large_d   2048
  #define kt_tacocat_allocation_small_d   128

  #define kt_tacocat_signal_check_d          20000
  #define kt_tacocat_signal_check_failsafe_d 20000
#endif // _di_kt_tacocat_d_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_common_define_h
