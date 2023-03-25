/**
 * Kevux Tools - Remove
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common define types.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _kt_remove_common_define_h
#define _kt_remove_common_define_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program defines.
 *
 * Leap Year:
 *   - If can be evenly divided by 4, then this is a leap year.
 *
 * kt_remove_signal_*_d:
 *
 * kt_remove_*_d:
 *   - allocation_console:    An allocation step used for small buffers specifically for console parameter.
 *   - allocation_large:      An allocation step used for buffers that are anticipated to have large buffers.
 *   - allocation_small:      An allocation step used for buffers that are anticipated to have small buffers.
 *   - signal_check:          When not using threads, this is how often to perform the check (lower numbers incur more kernel I/O).
 *   - signal_check_failsafe: When using threads, how many consecutive failures to check signal before aborting (as a recursion failsafe).
 *
 * kt_remove_time_seconds_in_*_d:
 *   - day:        Number of seconds in a day.
 *   - hour:       Number of seconds in a hour.
 *   - minute:     Number of seconds in a minute.
 *   - nanosecond: Number of seconds in a nanosecond.
 *   - week:       Number of seconds in a week.
 *   - year:       Number of seconds in a year (does not include leap years).
 *
 * kt_remove_time_year_*_d:
 *   - unix_epoch: The year in which the UNIX Epoch starts.
 */
#ifndef _di_kt_remove_d_
  #define kt_remove_allocation_console_d 4
  #define kt_remove_allocation_large_d   2048
  #define kt_remove_allocation_small_d   128

  #define kt_remove_signal_check_d          20000
  #define kt_remove_signal_check_failsafe_d 20000

  #define kt_remove_time_seconds_in_day_d        86400
  #define kt_remove_time_seconds_in_hour_d       3600
  #define kt_remove_time_seconds_in_minute_d     60
  #define kt_remove_time_seconds_in_nanosecond_d 1000000000
  #define kt_remove_time_seconds_in_week_d       604800
  #define kt_remove_time_seconds_in_year_d       31536000

  #define kt_remove_time_year_unix_epoch_d 1970
#endif // _di_kt_remove_d_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_remove_common_define_h
