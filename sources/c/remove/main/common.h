/**
 * Kevux Tools - Remove
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _kt_remove_common_h
#define _kt_remove_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_kt_remove_program_version_s_
  #define KT_REMOVE_program_version_major_s F_string_ascii_0_s
  #define KT_REMOVE_program_version_minor_s F_string_ascii_5_s
  #define KT_REMOVE_program_version_micro_s F_string_ascii_0_s

  #define KT_REMOVE_program_version_major_s_length F_string_ascii_0_s_length
  #define KT_REMOVE_program_version_minor_s_length F_string_ascii_5_s_length
  #define KT_REMOVE_program_version_micro_s_length F_string_ascii_0_s_length

  #if !(defined(KT_REMOVE_program_version_nano_prefix_s) && defined(KT_REMOVE_program_version_nano_prefix_s_length))
    #define KT_REMOVE_program_version_nano_prefix_s
    #define KT_REMOVE_program_version_nano_prefix_s_length 0
  #endif // !(defined(KT_REMOVE_program_version_nano_prefix_s) && defined(KT_REMOVE_program_version_nano_prefix_s_length))

  #if !(defined(KT_REMOVE_program_version_nano_s) && defined(KT_REMOVE_program_version_nano_s_length))
    #define KT_REMOVE_program_version_nano_s
    #define KT_REMOVE_program_version_nano_s_length 0
  #endif // !(defined(KT_REMOVE_program_version_nano_s) && defined(KT_REMOVE_program_version_nano_s_length))

  #define KT_REMOVE_program_version_s KT_REMOVE_program_version_major_s F_string_ascii_period_s KT_REMOVE_program_version_minor_s F_string_ascii_period_s KT_REMOVE_program_version_micro_s KT_REMOVE_program_version_nano_prefix_s KT_REMOVE_program_version_nano_s

  #define KT_REMOVE_program_version_s_length KT_REMOVE_program_version_major_s_length + F_string_ascii_period_s_length + KT_REMOVE_program_version_minor_s_length + F_string_ascii_period_s_length + KT_REMOVE_program_version_micro_s_length + KT_REMOVE_program_version_nano_prefix_s_length + KT_REMOVE_program_version_nano_s_length

  extern const f_string_static_t kt_remove_program_version_s;
#endif // _di_kt_remove_program_version_s_

/**
 * The program name.
 */
#ifndef _di_kt_remove_program_name_s_
  #define KT_REMOVE_program_name_s      "remove"
  #define KT_REMOVE_program_name_long_s "Remove"

  #define KT_REMOVE_program_name_s_length      6
  #define KT_REMOVE_program_name_long_s_length 6

  extern const f_string_static_t kt_remove_program_name_s;
  extern const f_string_static_t kt_remove_program_name_long_s;
#endif // _di_kt_remove_program_name_s_

/**
 * The program help related data.
 */
#ifndef kt_remove_program_help_parameters_s_
  #define KT_REMOVE_program_help_parameters_s "file(s)"
  #define KT_REMOVE_program_help_parameters_s_length 7

  extern const f_string_static_t kt_remove_program_help_parameters_s;
#endif // _di_utf8_program_help_parameters_s_

/**
 * The program default defines.
 *
 * kt_remove_default_allocation_*:
 *   - large: An allocation step used for buffers that are anticipated to have large buffers.
 *   - small: An allocation step used for buffers that are anticipated to have small buffers.
 */
#ifndef _di_kt_remove_default_d_
  #define kt_remove_default_allocation_large_d 2048
  #define kt_remove_default_allocation_small_d 128
#endif // _di_kt_remove_default_d_

/**
 * The program defines.
 *
 * Leap Year:
 *   - If can be evenly divided by 4, then this is a leap year.
 *
 * kt_remove_signal_*_d:
 *   - check:          When not using threads, this is how often to perform the check (lower numbers incur more kernel I/O).
 *   - check_failsafe: When using threads, how many consecutive failures to check signal before aborting (as a recursion failsafe).
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

/**
 * Strings associated with the date parameters.
 *
 * kt_remove_date_format_*_s:
 * - 00: The string "YYYY/MM/DD hh:ii:ss a +0000".
 * - 01: The string "YYYY/MM/DD HH:ii:ss +0000".
 * - 02: The string "YYYY/MM/DD hh:ii a +0000".
 * - 03: The string "YYYY/MM/DD HH:ii +0000".
 * - 04: The string "YYYY/MM/DD hh a +0000".
 * - 05: The string "YYYY/MM/DD HH +0000".
 * - 06: The string "YYYY/MM/DD hh:ii:ss a".
 * - 07: The string "YYYY/MM/DD HH:ii:ss".
 * - 08: The string "YYYY/MM/DD hh:ii a".
 * - 09: The string "YYYY/MM/DD HH:ii".
 * - 10: The string "YYYY/MM/DD hh a".
 * - 11: The string "YYYY/MM/DD HH".
 * - 12: The string "YYYY/MM/DD".
 * - 13: The string "YYYY/MM".
 * - 14: The string "YYYY/".
 *
 * kt_remove_date_symbol_*_s:
 * - equal:      Equal to operator.
 * - less:       Less than operator.
 * - less_equal: Less than or equal to operator.
 * - more:       Greater than operator.
 * - more_equal: Greater than or equal to operator.
 * - not:        Not equal to operator.
 *
 * kt_remove_date_word_*_s:
 * - equal:      Equal to words.
 * - less:       Less than words.
 * - less_equal: Less than or equal to words.
 * - more:       Greater than words.
 * - more_equal: Greater than or equal to words.
 * - not:        Not equal to words.
 */
#ifndef _di_kt_remove_date_s_
  #define KT_REMOVE_date_format_00_s "%Y/%m/%d %I:%M:%S %p %z"
  #define KT_REMOVE_date_format_01_s "%Y/%m/%d %H:%M:%S %z"
  #define KT_REMOVE_date_format_02_s "%Y/%m/%d %I:%M %p %z"
  #define KT_REMOVE_date_format_03_s "%Y/%m/%d %H:%M %z"
  #define KT_REMOVE_date_format_04_s "%Y/%m/%d %I %p %z"
  #define KT_REMOVE_date_format_05_s "%Y/%m/%d %H %z"
  #define KT_REMOVE_date_format_06_s "%Y/%m/%d %I:%M:%S %p"
  #define KT_REMOVE_date_format_07_s "%Y/%m/%d %H:%M:%S"
  #define KT_REMOVE_date_format_08_s "%Y/%m/%d %I:%M %p"
  #define KT_REMOVE_date_format_09_s "%Y/%m/%d %H:%M"
  #define KT_REMOVE_date_format_10_s "%Y/%m/%d %I %p"
  #define KT_REMOVE_date_format_11_s "%Y/%m/%d %H"
  #define KT_REMOVE_date_format_12_s "%Y/%m/%d"
  #define KT_REMOVE_date_format_13_s "%Y/%m"
  #define KT_REMOVE_date_format_14_s "%Y/"

  #define KT_REMOVE_date_format_00_s_length 23
  #define KT_REMOVE_date_format_01_s_length 20
  #define KT_REMOVE_date_format_02_s_length 20
  #define KT_REMOVE_date_format_03_s_length 17
  #define KT_REMOVE_date_format_04_s_length 17
  #define KT_REMOVE_date_format_05_s_length 14
  #define KT_REMOVE_date_format_06_s_length 20
  #define KT_REMOVE_date_format_07_s_length 17
  #define KT_REMOVE_date_format_08_s_length 17
  #define KT_REMOVE_date_format_09_s_length 14
  #define KT_REMOVE_date_format_10_s_length 14
  #define KT_REMOVE_date_format_11_s_length 11
  #define KT_REMOVE_date_format_12_s_length 8
  #define KT_REMOVE_date_format_13_s_length 5
  #define KT_REMOVE_date_format_14_s_length 3

  extern const f_string_static_t kt_remove_date_format_00_s;
  extern const f_string_static_t kt_remove_date_format_01_s;
  extern const f_string_static_t kt_remove_date_format_02_s;
  extern const f_string_static_t kt_remove_date_format_03_s;
  extern const f_string_static_t kt_remove_date_format_04_s;
  extern const f_string_static_t kt_remove_date_format_05_s;
  extern const f_string_static_t kt_remove_date_format_06_s;
  extern const f_string_static_t kt_remove_date_format_07_s;
  extern const f_string_static_t kt_remove_date_format_08_s;
  extern const f_string_static_t kt_remove_date_format_09_s;
  extern const f_string_static_t kt_remove_date_format_10_s;
  extern const f_string_static_t kt_remove_date_format_11_s;
  extern const f_string_static_t kt_remove_date_format_12_s;
  extern const f_string_static_t kt_remove_date_format_13_s;
  extern const f_string_static_t kt_remove_date_format_14_s;

  #define KT_REMOVE_date_format_example_00_s "2022/12/30 1:45:02 pm +0600"
  #define KT_REMOVE_date_format_example_01_s "2022/12/30 13:45:02 +0600"
  #define KT_REMOVE_date_format_example_02_s "2022/12/30 1:45 pm +0600"
  #define KT_REMOVE_date_format_example_03_s "2022/12/30 13:45 +0600"
  #define KT_REMOVE_date_format_example_04_s "2022/12/30 1 pm +0600"
  #define KT_REMOVE_date_format_example_05_s "2022/12/30 13 +0600"
  #define KT_REMOVE_date_format_example_06_s "2022/12/30 1:45:02 pm"
  #define KT_REMOVE_date_format_example_07_s "2022/12/30 13:45:02"
  #define KT_REMOVE_date_format_example_08_s "2022/12/30 1:45 pm"
  #define KT_REMOVE_date_format_example_09_s "2022/12/30 13:45"
  #define KT_REMOVE_date_format_example_10_s "2022/12/30 1 pm"
  #define KT_REMOVE_date_format_example_11_s "2022/12/30 13"
  #define KT_REMOVE_date_format_example_12_s "2022/12/30"
  #define KT_REMOVE_date_format_example_13_s "2022/12"
  #define KT_REMOVE_date_format_example_14_s "2022/"

  #define KT_REMOVE_date_format_example_00_s_length 27
  #define KT_REMOVE_date_format_example_01_s_length 25
  #define KT_REMOVE_date_format_example_02_s_length 24
  #define KT_REMOVE_date_format_example_03_s_length 22
  #define KT_REMOVE_date_format_example_04_s_length 21
  #define KT_REMOVE_date_format_example_05_s_length 19
  #define KT_REMOVE_date_format_example_06_s_length 21
  #define KT_REMOVE_date_format_example_07_s_length 19
  #define KT_REMOVE_date_format_example_08_s_length 18
  #define KT_REMOVE_date_format_example_09_s_length 16
  #define KT_REMOVE_date_format_example_10_s_length 15
  #define KT_REMOVE_date_format_example_11_s_length 13
  #define KT_REMOVE_date_format_example_12_s_length 10
  #define KT_REMOVE_date_format_example_13_s_length 9
  #define KT_REMOVE_date_format_example_14_s_length 5

  extern const f_string_static_t kt_remove_date_format_example_00_s;
  extern const f_string_static_t kt_remove_date_format_example_01_s;
  extern const f_string_static_t kt_remove_date_format_example_02_s;
  extern const f_string_static_t kt_remove_date_format_example_03_s;
  extern const f_string_static_t kt_remove_date_format_example_04_s;
  extern const f_string_static_t kt_remove_date_format_example_05_s;
  extern const f_string_static_t kt_remove_date_format_example_06_s;
  extern const f_string_static_t kt_remove_date_format_example_07_s;
  extern const f_string_static_t kt_remove_date_format_example_08_s;
  extern const f_string_static_t kt_remove_date_format_example_09_s;
  extern const f_string_static_t kt_remove_date_format_example_10_s;
  extern const f_string_static_t kt_remove_date_format_example_11_s;
  extern const f_string_static_t kt_remove_date_format_example_12_s;
  extern const f_string_static_t kt_remove_date_format_example_13_s;
  extern const f_string_static_t kt_remove_date_format_example_14_s;

  #define KT_REMOVE_date_symbol_equal_s      "=="
  #define KT_REMOVE_date_symbol_less_s       "<"
  #define KT_REMOVE_date_symbol_less_equal_s "<="
  #define KT_REMOVE_date_symbol_more_s       ">"
  #define KT_REMOVE_date_symbol_more_equal_s ">="
  #define KT_REMOVE_date_symbol_not_s        "<>"

  #define KT_REMOVE_date_symbol_equal_s_length      2
  #define KT_REMOVE_date_symbol_less_s_length       1
  #define KT_REMOVE_date_symbol_less_equal_s_length 2
  #define KT_REMOVE_date_symbol_more_s_length       1
  #define KT_REMOVE_date_symbol_more_equal_s_length 2
  #define KT_REMOVE_date_symbol_not_s_length        2

  extern const f_string_static_t kt_remove_date_symbol_equal_s;
  extern const f_string_static_t kt_remove_date_symbol_less_s;
  extern const f_string_static_t kt_remove_date_symbol_less_equal_s;
  extern const f_string_static_t kt_remove_date_symbol_more_s;
  extern const f_string_static_t kt_remove_date_symbol_more_equal_s;
  extern const f_string_static_t kt_remove_date_symbol_not_s;

  #define KT_REMOVE_date_word_equal_s      "equal"
  #define KT_REMOVE_date_word_less_s       "less"
  #define KT_REMOVE_date_word_less_equal_s "less_equal"
  #define KT_REMOVE_date_word_more_s       "more"
  #define KT_REMOVE_date_word_more_equal_s "more_equal"
  #define KT_REMOVE_date_word_not_s        "not"

  #define KT_REMOVE_date_word_equal_s_length      5
  #define KT_REMOVE_date_word_less_s_length       4
  #define KT_REMOVE_date_word_less_equal_s_length 10
  #define KT_REMOVE_date_word_more_s_length       4
  #define KT_REMOVE_date_word_more_equal_s_length 10
  #define KT_REMOVE_date_word_not_s_length        3

  extern const f_string_static_t kt_remove_date_word_equal_s;
  extern const f_string_static_t kt_remove_date_word_less_s;
  extern const f_string_static_t kt_remove_date_word_less_equal_s;
  extern const f_string_static_t kt_remove_date_word_more_s;
  extern const f_string_static_t kt_remove_date_word_more_equal_s;
  extern const f_string_static_t kt_remove_date_word_not_s;
#endif // _di_kt_remove_date_s_

/**
 * Strings associated with the mode parameters.
 *
 * kt_remove_mode_symbol_*_s:
 * - different: The not similar to operator.
 * - same:      The same as operator.
 * - similar:   The similar to operator.
 * - not:       The not same as operator.
 *
 * kt_remove_mode_word_*_s:
 * - different: The not similar to words.
 * - same:      The same as words.
 * - similar:   The similar to words.
 * - not:       The not same as words.
 */
#ifndef _di_kt_remove_mode_s_
  #define KT_REMOVE_mode_symbol_different_s "~~"
  #define KT_REMOVE_mode_symbol_same_s      "=="
  #define KT_REMOVE_mode_symbol_similar_s   "~="
  #define KT_REMOVE_mode_symbol_not_s       "<>"

  #define KT_REMOVE_mode_symbol_different_s_length 2
  #define KT_REMOVE_mode_symbol_same_s_length      2
  #define KT_REMOVE_mode_symbol_similar_s_length   2
  #define KT_REMOVE_mode_symbol_not_s_length       2

  extern const f_string_static_t kt_remove_mode_symbol_different_s;
  extern const f_string_static_t kt_remove_mode_symbol_same_s;
  extern const f_string_static_t kt_remove_mode_symbol_similar_s;
  extern const f_string_static_t kt_remove_mode_symbol_not_s;

  #define KT_REMOVE_mode_word_different_s "different"
  #define KT_REMOVE_mode_word_same_s      "same"
  #define KT_REMOVE_mode_word_similar_s   "similar"
  #define KT_REMOVE_mode_word_not_s       "not"

  #define KT_REMOVE_mode_word_different_s_length 9
  #define KT_REMOVE_mode_word_same_s_length      4
  #define KT_REMOVE_mode_word_similar_s_length   7
  #define KT_REMOVE_mode_word_not_s_length       3

  extern const f_string_static_t kt_remove_mode_word_different_s;
  extern const f_string_static_t kt_remove_mode_word_same_s;
  extern const f_string_static_t kt_remove_mode_word_similar_s;
  extern const f_string_static_t kt_remove_mode_word_not_s;
#endif // _di_kt_remove_mode_s_

/**
 * Additional strings used for various purposes.
 *
 * kt_remove_*_s: Arbitrary strings.
 */
#ifndef _di_kt_remove_s_
  #define KT_REMOVE_all_s       "all"
  #define KT_REMOVE_follow_s    "follow"
  #define KT_REMOVE_ignore_s    "ignore"
  #define KT_REMOVE_never_s     "never"
  #define KT_REMOVE_no_s        "no"
  #define KT_REMOVE_not_s       "not"
  #define KT_REMOVE_not_fail_s  "not_fail"
  #define KT_REMOVE_now_s       "now"
  #define KT_REMOVE_once_s      "once"
  #define KT_REMOVE_only_s      "only"
  #define KT_REMOVE_only_fail_s "only_fail"
  #define KT_REMOVE_root_s      "root"
  #define KT_REMOVE_today_s     "today"
  #define KT_REMOVE_tomorrow_s  "tomorrow"
  #define KT_REMOVE_yes_s       "yes"
  #define KT_REMOVE_yesterday_s "yesterday"

  #define KT_REMOVE_all_s_length       3
  #define KT_REMOVE_follow_s_length    6
  #define KT_REMOVE_ignore_s_length    6
  #define KT_REMOVE_never_s_length     5
  #define KT_REMOVE_no_s_length        2
  #define KT_REMOVE_not_s_length       3
  #define KT_REMOVE_not_fail_s_length  8
  #define KT_REMOVE_now_s_length       3
  #define KT_REMOVE_once_s_length      4
  #define KT_REMOVE_only_s_length      4
  #define KT_REMOVE_only_fail_s_length 9
  #define KT_REMOVE_root_s_length      4
  #define KT_REMOVE_today_s_length     5
  #define KT_REMOVE_tomorrow_s_length  8
  #define KT_REMOVE_yes_s_length       3
  #define KT_REMOVE_yesterday_s_length 9

  extern const f_string_static_t kt_remove_all_s;
  extern const f_string_static_t kt_remove_follow_s;
  extern const f_string_static_t kt_remove_ignore_s;
  extern const f_string_static_t kt_remove_never_s;
  extern const f_string_static_t kt_remove_no_s;
  extern const f_string_static_t kt_remove_not_s;
  extern const f_string_static_t kt_remove_not_fail_s;
  extern const f_string_static_t kt_remove_now_s;
  extern const f_string_static_t kt_remove_once_s;
  extern const f_string_static_t kt_remove_only_s;
  extern const f_string_static_t kt_remove_only_fail_s;
  extern const f_string_static_t kt_remove_root_s;
  extern const f_string_static_t kt_remove_today_s;
  extern const f_string_static_t kt_remove_tomorrow_s;
  extern const f_string_static_t kt_remove_yes_s;
  extern const f_string_static_t kt_remove_yesterday_s;
#endif // _di_kt_remove_s_

/**
 * A processed Date parameter.
 *
 * The start is inclusive and the stop is exclusive just like with f_string_range_t.
 *
 * operation: The comparison operation.
 * type:      The date type.
 *
 * start_year:       The year in which the seconds is relative to (is only processed when
 * start_second:     The entire date value in seconds for the date or the start of a date range.
 * start_nanosecond: The remaining nanosecond not represented in the seconds for the date or the start of a date range.
 * stop_second:      The entire date value in seconds for the stop of a date range (not used for non-range dates).
 * stop_nanosecond:  The remaining nanosecond not represented in the seconds for the stop of a date range (not used for non-range dates).
 */
#ifndef _di_kt_remove_date_t_
  typedef struct {
    uint8_t operation;
    uint8_t type;

    f_number_unsigned_t start_year;
    f_number_unsigned_t start_second;
    f_number_unsigned_t start_nanosecond;

    f_number_unsigned_t stop_year;
    f_number_unsigned_t stop_second;
    f_number_unsigned_t stop_nanosecond;
  } kt_remove_date_t;

  #define kt_remove_date_t_initialize { \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
  }
#endif // _di_kt_remove_date_t_

/**
 * Date parameters.
 *
 * array: An array of data parameters.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_kt_remove_dates_t_
  typedef struct {
    kt_remove_date_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } kt_remove_dates_t;

  #define kt_remove_dates_t_initialize { \
    0, \
    0, \
    0, \
  }

  #define macro_kt_remove_dates_t_clear(dates) \
    dates.array = 0; \
    dates.size = 0; \
    dates.used = 0;
#endif // _di_kt_remove_dates_t_

/**
 * A processed mode parameter.
 *
 * type: The mode type.
 * mode: The right side date value.
 */
#ifndef _di_kt_remove_mode_t_
  typedef struct {
    uint8_t type;
    mode_t mode;
  } kt_remove_mode_t;

  #define kt_remove_mode_t_initialize { \
    0, \
    0, \
  }
#endif // _di_kt_remove_mode_t_

/**
 * Mode parameters.
 *
 * array: An array of mode parameters.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_kt_remove_modes_t_
  typedef struct {
    kt_remove_mode_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } kt_remove_modes_t;

  #define kt_remove_modes_t_initialize { \
    0, \
    0, \
    0, \
  }

  #define macro_kt_remove_modes_t_clear(dates) \
    dates.array = 0; \
    dates.size = 0; \
    dates.used = 0;
#endif // _di_kt_remove_modes_t_

/**
 * Flags passed to the main function or program.
 *
 * @todo /proc needs to be implemented, but before that try to understand how --one-file-system, --no-preserve-root, and --preserve-root work in coreutils rm command.
 *
 * kt_remove_flag_*_e:
 *   - none:            No flags set.
 *   - block:           Remove by file type: block.
 *   - character:       Remove by file type: character.
 *   - date:            Remove by date (separate flag for <, <=, ==, >=, and >).
 *   - different:       Remove by user different from caller.
 *   - directory:       Remove by file type: directory.
 *   - empty_only:      Remove empty directories.
 *   - empty_only_fail: Fail on empty directories.
 *   - empty_not:       Remove not empty directories.
 *   - empty_not_fail:  Fail on not empty directories.
 *   - fifo:            Remove by file type: FIFO.
 *   - follow:          Follow symbolic links deleting the file being pointed to rather than the link itself (when not set the link itself is deleted).
 *   - force:           Forcibly delete.
 *   - group:           Remove by GID.
 *   - help:            Print help.
 *   - isolate_all:     Isolate to a single file system, error on all outside file system files (@todo requires /proc support).
 *   - isolate_ignore:  Ignore rather than fail for anything on a different file system (@todo requires /proc support).
 *   - isolate_root:    Isolate to a single file system, error on remove on '/' (@todo requires /proc support).
 *   - link:            Remove by file type: link.
 *   - mode:            Remove by mode.
 *   - option_used:     This gets set when when certain options are specified to toggle the default match detection boolean during removal of each file.
 *   - print_warning:   When specified, warnings are still printed even when verbosity is less than verbose.
 *   - prompt_all:      Operate in interactive mode, prompting for every file.
 *   - prompt_follow:   Operate in interactive mode: prompting for every link that is being followed.
 *   - prompt_never:    Do not operate in interactive mode.
 *   - prompt_once:     Operate in interactive mode: prompting if removing 3 or more files.
 *   - recurse:         Recurse directories.
 *   - regular:         Remove by file type: regular.
 *   - same:            Remove by same user as caller.
 *   - simulate:        Do not actually perform deletes, instead print messages (when silent, should still return 0 or 1).
 *   - socket:          Remove by file type: socket.
 *   - tree:            Remove directory tree (parent directories) (remove a/b/c, removes a/b/c, then a/b/, then a).
 *   - user:            Remove by UID.
 *   - utc:             Process dates in UTC mode.
 *   - version:         Print version.
 */
#ifndef _di_kt_remove_flag_e_
  enum {
    kt_remove_flag_none_e            = 0x0,
    kt_remove_flag_accessed_e        = 0x1,
    kt_remove_flag_block_e           = 0x2,
    kt_remove_flag_character_e       = 0x4,
    kt_remove_flag_created_e         = 0x8,
    kt_remove_flag_different_e       = 0x10,
    kt_remove_flag_directory_e       = 0x20,
    kt_remove_flag_empty_only_e      = 0x40,
    kt_remove_flag_empty_only_fail_e = 0x80,
    kt_remove_flag_empty_not_e       = 0x100,
    kt_remove_flag_empty_not_fail_e  = 0x200,
    kt_remove_flag_fifo_e            = 0x400,
    kt_remove_flag_follow_e          = 0x800,
    kt_remove_flag_force_e           = 0x1000,
    kt_remove_flag_group_e           = 0x2000,
    kt_remove_flag_help_e            = 0x4000,
    kt_remove_flag_isolate_all_e     = 0x8000,
    kt_remove_flag_isolate_ignore_e  = 0x10000,
    kt_remove_flag_isolate_root_e    = 0x20000,
    kt_remove_flag_link_e            = 0x40000,
    kt_remove_flag_mode_e            = 0x80000,
    kt_remove_flag_option_used_e     = 0x100000,
    kt_remove_flag_print_warning_e   = 0x200000,
    kt_remove_flag_prompt_all_e      = 0x400000,
    kt_remove_flag_prompt_follow_e   = 0x800000,
    kt_remove_flag_prompt_never_e    = 0x1000000,
    kt_remove_flag_prompt_once_e     = 0x2000000,
    kt_remove_flag_recurse_e         = 0x4000000,
    kt_remove_flag_regular_e         = 0x8000000,
    kt_remove_flag_same_e            = 0x10000000,
    kt_remove_flag_simulate_e        = 0x20000000,
    kt_remove_flag_socket_e          = 0x40000000,
    kt_remove_flag_tree_e            = 0x80000000,
    kt_remove_flag_updated_e         = 0x100000000,
    kt_remove_flag_user_e            = 0x200000000,
    kt_remove_flag_utc_e             = 0x400000000,
    kt_remove_flag_version_e         = 0x800000000,
  }; // enum
#endif // _di_kt_remove_flag_e_

/**
 * A set of flags used internally in the convert process.
 *
 * These are generally used during parsing of Time and EpochTime strings.
 *
 * kt_remove_flag_convert_*_e:
 * - colon:             Either single or double colon.
 * - colon_single:      Single colon detected.
 * - colon_double:      Double colon detected.
 * - match:             Matched either part.
 * - match_first:       Matched first (left) part.
 * - match_second:      Matched second (right) part.
 */
#ifndef _di_kt_remove_flag_convert_e_
  enum {
    kt_remove_flag_convert_none_e         = 0x0,
    kt_remove_flag_convert_colon_e        = 0x3,
    kt_remove_flag_convert_colon_single_e = 0x1,
    kt_remove_flag_convert_colon_double_e = 0x2,
    kt_remove_flag_convert_match_e        = 0xc,
    kt_remove_flag_convert_match_first_e  = 0x4,
    kt_remove_flag_convert_match_second_e = 0x8,
  }; // enum
#endif // _di_kt_remove_flag_convert_e_

/**
 * Flags associated with a date.
 *
 * kt_remove_flag_date_*_e:
 *   - none:       No flags set.
 *   - equal:      Perform equal to on date, '==' or 'equal'.
 *   - less:       Perform less than on date, '<' or 'less'.
 *   - less_equal: Perform less than or equal to on date, '<=' or 'less_equal'.
 *   - more:       Perform greater than on date, '>' or 'more'.
 *   - more_equal: Perform greater than or equal to on date, '>=' or 'more_equal'.
 *   - not:        Perform not equal to on date. '<>' or 'not'
 *
 *   - year:       Date has a year.
 *   - now:        Date is relative to 'now'.
 *   - string:     Date is processed via the string date functions (such as via strftime_r() or getdate_r()).
 *   - time:       Date is based off of Time format.
 *   - time_epoch: Date is based off of EpochTime format.
 *   - today:      Date is relative to 'today'.
 *   - tomorrow:   Date is relative to 'tomorrow'.
 *   - unix:       Date is based off of Unix Epoch format.
 *   - yesterday:  Date is relative to 'yesterday'.
 */
#ifndef _di_kt_remove_flag_date_e_
  enum {
    kt_remove_flag_date_none_e       = 0x0,

    // Used for comparisons.
    kt_remove_flag_date_equal_e      = 0x1,
    kt_remove_flag_date_less_e       = 0x2,
    kt_remove_flag_date_less_equal_e = 0x4,
    kt_remove_flag_date_more_e       = 0x8,
    kt_remove_flag_date_more_equal_e = 0x10,
    kt_remove_flag_date_not_e        = 0x20,

    // Used for processing and converting.
    kt_remove_flag_date_now_e        = 0x1,
    kt_remove_flag_date_string_e     = 0x2,
    kt_remove_flag_date_time_e       = 0x4,
    kt_remove_flag_date_time_epoch_e = 0x8,
    kt_remove_flag_date_today_e      = 0x10,
    kt_remove_flag_date_tomorrow_e   = 0x20,
    kt_remove_flag_date_unix_e       = 0x40,
    kt_remove_flag_date_yesterday_e  = 0x80,
  }; // enum
#endif // _di_kt_remove_flag_date_e_

/**
 * Flags associated with a mode.
 *
 * kt_remove_flag_mode_*_e:
 *   - none:      No flags set.
 *   - different: Remove by mode matching different parts.
 *   - same:      Remove by exact mode match.
 *   - similar:   Remove by mode matching same parts.
 *   - not:       Remove by not exact mode match.
 */
#ifndef _di_kt_remove_flag_mode_e_
  enum {
    kt_remove_flag_mode_none_e      = 0x0,
    kt_remove_flag_mode_different_e = 0x1, // '~~' or 'different'
    kt_remove_flag_mode_same_e      = 0x2, // '==' or 'same'
    kt_remove_flag_mode_similar_e   = 0x4, // '~=' or 'similar'
    kt_remove_flag_mode_not_e       = 0x8, // '<>' or 'not'
  }; // enum
#endif // _di_kt_remove_flag_mode_e_

/**
 * The main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * flag: Flags passed to the main function.
 *
 * status:        The main status code, generally used by the load settings and main functions.
 * status_thread: A status used eclusively by the threaded signal handler.
 * state:         The state data used when processing data.
 *
 * program_name:      The short name of the program.
 * program_name_long: The human friendly name of the program.
 *
 * buffer: A string buffer used for caching purposes.
 * files:  An array of file names (full paths to the files) to remove.
 *
 * accessed: An array of last accessed dates used for comparison.
 * created:  An array of created on dates used for comparison.
 * updated:  An array of last updated dates used for comparison.
 * modes:    An array of modes used for comparison.
 * groups:   An array of Group IDs (gid_t) represented via an unsigned 32-bit integer.
 * users:    An array of Group IDs (uid_t) represented via an unsigned 32-bit integer.
 *
 * process_help:   Process help (generally printing help).
 * process_normal: Process normally (data from parameters and files).
 *
 * macro_kt_remove_setting:
 *   - Used to represent a cast to ((kt_remove_setting_t *) setting).
 *   - Simplifies the number of parenthesis used to make code slightly cleaner.
 *   - Is wrapped in a parenthesis and not a block.
 */
#ifndef _di_kt_remove_setting_t_
  typedef struct {
    uint64_t flag;

    f_status_t status;
    f_status_t status_thread;
    f_state_t state;

    f_string_dynamic_t buffer;
    f_string_dynamics_t files;

    kt_remove_dates_t accessed;
    kt_remove_dates_t created;
    kt_remove_dates_t updated;
    kt_remove_modes_t modes;
    f_uint32s_t groups;
    f_uint32s_t users;

    const f_string_static_t *program_name;
    const f_string_static_t *program_name_long;

    f_status_t (*process_help)(fll_program_data_t * const main, void * const setting);
    void (*process_normal)(fll_program_data_t * const main, void * const setting);
  } kt_remove_setting_t;

  #define kt_remove_setting_t_initialize \
    { \
      kt_remove_flag_none_e, \
      F_none, \
      F_none, \
      macro_f_state_t_initialize(kt_remove_default_allocation_large_d, kt_remove_default_allocation_small_d, 0, 0, &fll_program_standard_signal_state, 0, 0, 0), \
      f_string_dynamic_t_initialize, \
      f_string_dynamics_t_initialize, \
      kt_remove_dates_t_initialize, \
      kt_remove_dates_t_initialize, \
      kt_remove_dates_t_initialize, \
      kt_remove_modes_t_initialize, \
      f_uint32s_t_initialize, \
      f_uint32s_t_initialize, \
      0, \
      0, \
      0, \
      0, \
    }

  #define macro_kt_remove_setting(setting) ((kt_remove_setting_t *) setting)
#endif // _di_kt_remove_setting_t_
/**
 * An arguments array for passing the standard variables to a thread callback.
 *
 * main:    The main program data.
 * setting: The main program settings.
 *
 * macro_kt_remove_arguments:
 *   - Used to represent a cast to ((kt_remove_setting_t *) setting).
 *   - Simplifies the number of parenthesis used to make code slightly cleaner.
 *   - Is wrapped in a parenthesis and not a block.
 */
#ifndef _di_kt_remove_arguments_t_
  typedef struct {
    fll_program_data_t *main;
    kt_remove_setting_t *setting;
  } kt_remove_arguments_t;

  #define kt_remove_arguments_t_initialize { \
    0, \
    0, \
  }

  #define macro_kt_remove_arguments_t_initialize(main, setting) { \
    main, \
    setting, \
  }

  #define macro_kt_remove_arguments(arguments) ((kt_remove_arguments_t *) arguments)
#endif // _di_kt_remove_arguments_t_

/**
 * The main program parameters.
 */
#ifndef _di_kt_remove_parameter_d_
  #define KT_REMOVE_short_accessed_s  "A"
  #define KT_REMOVE_short_block_s     "b"
  #define KT_REMOVE_short_character_s "c"
  #define KT_REMOVE_short_created_s   "C"
  #define KT_REMOVE_short_different_s "O"
  #define KT_REMOVE_short_directory_s "d"
  #define KT_REMOVE_short_empty_s     "e"
  #define KT_REMOVE_short_fifo_s      "o"
  #define KT_REMOVE_short_follow_s    "F"
  #define KT_REMOVE_short_force_s     "f"
  #define KT_REMOVE_short_group_s     "g"
  #define KT_REMOVE_short_isolate_s   "i"
  #define KT_REMOVE_short_link_s      "l"
  #define KT_REMOVE_short_mode_s      "m"
  #define KT_REMOVE_short_prompt_s    "p"
  #define KT_REMOVE_short_recurse_s   "r"
  #define KT_REMOVE_short_regular_s   "R"
  #define KT_REMOVE_short_same_s      "s"
  #define KT_REMOVE_short_simulate_s  "S"
  #define KT_REMOVE_short_socket_s    "k"
  #define KT_REMOVE_short_stay_s      "Y"
  #define KT_REMOVE_short_tree_s      "t"
  #define KT_REMOVE_short_updated_s   "U"
  #define KT_REMOVE_short_user_s      "u"

  #define KT_REMOVE_long_accessed_s  "accessed"
  #define KT_REMOVE_long_block_s     "block"
  #define KT_REMOVE_long_character_s "character"
  #define KT_REMOVE_long_created_s   "created"
  #define KT_REMOVE_long_different_s "different"
  #define KT_REMOVE_long_directory_s "directory"
  #define KT_REMOVE_long_empty_s     "empty"
  #define KT_REMOVE_long_fifo_s      "fifo"
  #define KT_REMOVE_long_follow_s    "follow"
  #define KT_REMOVE_long_force_s     "force"
  #define KT_REMOVE_long_group_s     "group"
  #define KT_REMOVE_long_isolate_s   "isolate"
  #define KT_REMOVE_long_link_s      "link"
  #define KT_REMOVE_long_local_s     "local"
  #define KT_REMOVE_long_mode_s      "mode"
  #define KT_REMOVE_long_prompt_s    "prompt"
  #define KT_REMOVE_long_recurse_s   "recurse"
  #define KT_REMOVE_long_regular_s   "regular"
  #define KT_REMOVE_long_same_s      "same"
  #define KT_REMOVE_long_simulate_s  "simulate"
  #define KT_REMOVE_long_socket_s    "socket"
  #define KT_REMOVE_long_stay_s      "stay"
  #define KT_REMOVE_long_tree_s      "tree"
  #define KT_REMOVE_long_updated_s   "updated"
  #define KT_REMOVE_long_user_s      "user"
  #define KT_REMOVE_long_utc_s       "utc"

  #define KT_REMOVE_short_accessed_s_length  1
  #define KT_REMOVE_short_block_s_length     1
  #define KT_REMOVE_short_character_s_length 1
  #define KT_REMOVE_short_created_s_length   1
  #define KT_REMOVE_short_different_s_length 1
  #define KT_REMOVE_short_directory_s_length 1
  #define KT_REMOVE_short_empty_s_length     1
  #define KT_REMOVE_short_fifo_s_length      1
  #define KT_REMOVE_short_follow_s_length    1
  #define KT_REMOVE_short_force_s_length     1
  #define KT_REMOVE_short_group_s_length     1
  #define KT_REMOVE_short_isolate_s_length   1
  #define KT_REMOVE_short_link_s_length      1
  #define KT_REMOVE_short_mode_s_length      1
  #define KT_REMOVE_short_prompt_s_length    1
  #define KT_REMOVE_short_recurse_s_length   1
  #define KT_REMOVE_short_regular_s_length   1
  #define KT_REMOVE_short_same_s_length      1
  #define KT_REMOVE_short_simulate_s_length  1
  #define KT_REMOVE_short_socket_s_length    1
  #define KT_REMOVE_short_stay_s_length      1
  #define KT_REMOVE_short_tree_s_length      1
  #define KT_REMOVE_short_updated_s_length   1
  #define KT_REMOVE_short_user_s_length      1

  #define KT_REMOVE_long_accessed_s_length  8
  #define KT_REMOVE_long_block_s_length     6
  #define KT_REMOVE_long_character_s_length 9
  #define KT_REMOVE_long_created_s_length   7
  #define KT_REMOVE_long_different_s_length 9
  #define KT_REMOVE_long_directory_s_length 9
  #define KT_REMOVE_long_empty_s_length     5
  #define KT_REMOVE_long_fifo_s_length      4
  #define KT_REMOVE_long_follow_s_length    6
  #define KT_REMOVE_long_force_s_length     5
  #define KT_REMOVE_long_group_s_length     5
  #define KT_REMOVE_long_isolate_s_length   7
  #define KT_REMOVE_long_link_s_length      4
  #define KT_REMOVE_long_local_s_length     5
  #define KT_REMOVE_long_mode_s_length      4
  #define KT_REMOVE_long_prompt_s_length    6
  #define KT_REMOVE_long_recurse_s_length   7
  #define KT_REMOVE_long_regular_s_length   7
  #define KT_REMOVE_long_same_s_length      4
  #define KT_REMOVE_long_simulate_s_length  8
  #define KT_REMOVE_long_socket_s_length    6
  #define KT_REMOVE_long_stay_s_length      4
  #define KT_REMOVE_long_tree_s_length      4
  #define KT_REMOVE_long_updated_s_length   7
  #define KT_REMOVE_long_user_s_length      4
  #define KT_REMOVE_long_utc_s_length       3

  extern const f_string_static_t kt_remove_short_accessed_s;
  extern const f_string_static_t kt_remove_short_block_s;
  extern const f_string_static_t kt_remove_short_character_s;
  extern const f_string_static_t kt_remove_short_created_s;
  extern const f_string_static_t kt_remove_short_different_s;
  extern const f_string_static_t kt_remove_short_directory_s;
  extern const f_string_static_t kt_remove_short_empty_s;
  extern const f_string_static_t kt_remove_short_fifo_s;
  extern const f_string_static_t kt_remove_short_follow_s;
  extern const f_string_static_t kt_remove_short_force_s;
  extern const f_string_static_t kt_remove_short_group_s;
  extern const f_string_static_t kt_remove_short_isolate_s;
  extern const f_string_static_t kt_remove_short_link_s;
  extern const f_string_static_t kt_remove_short_mode_s;
  extern const f_string_static_t kt_remove_short_prompt_s;
  extern const f_string_static_t kt_remove_short_recurse_s;
  extern const f_string_static_t kt_remove_short_regular_s;
  extern const f_string_static_t kt_remove_short_same_s;
  extern const f_string_static_t kt_remove_short_simulate_s;
  extern const f_string_static_t kt_remove_short_socket_s;
  extern const f_string_static_t kt_remove_short_stay_s;
  extern const f_string_static_t kt_remove_short_tree_s;
  extern const f_string_static_t kt_remove_short_updated_s;
  extern const f_string_static_t kt_remove_short_user_s;

  extern const f_string_static_t kt_remove_long_accessed_s;
  extern const f_string_static_t kt_remove_long_block_s;
  extern const f_string_static_t kt_remove_long_character_s;
  extern const f_string_static_t kt_remove_long_created_s;
  extern const f_string_static_t kt_remove_long_different_s;
  extern const f_string_static_t kt_remove_long_directory_s;
  extern const f_string_static_t kt_remove_long_empty_s;
  extern const f_string_static_t kt_remove_long_fifo_s;
  extern const f_string_static_t kt_remove_long_follow_s;
  extern const f_string_static_t kt_remove_long_force_s;
  extern const f_string_static_t kt_remove_long_group_s;
  extern const f_string_static_t kt_remove_long_isolate_s;
  extern const f_string_static_t kt_remove_long_link_s;
  extern const f_string_static_t kt_remove_long_local_s;
  extern const f_string_static_t kt_remove_long_mode_s;
  extern const f_string_static_t kt_remove_long_prompt_s;
  extern const f_string_static_t kt_remove_long_recurse_s;
  extern const f_string_static_t kt_remove_long_regular_s;
  extern const f_string_static_t kt_remove_long_same_s;
  extern const f_string_static_t kt_remove_long_simulate_s;
  extern const f_string_static_t kt_remove_long_socket_s;
  extern const f_string_static_t kt_remove_long_stay_s;
  extern const f_string_static_t kt_remove_long_tree_s;
  extern const f_string_static_t kt_remove_long_updated_s;
  extern const f_string_static_t kt_remove_long_user_s;
  extern const f_string_static_t kt_remove_long_utc_s;

  enum {
    kt_remove_parameter_help_e,
    kt_remove_parameter_light_e,
    kt_remove_parameter_dark_e,
    kt_remove_parameter_no_color_e,
    kt_remove_parameter_verbosity_quiet_e,
    kt_remove_parameter_verbosity_error_e,
    kt_remove_parameter_verbosity_normal_e,
    kt_remove_parameter_verbosity_verbose_e,
    kt_remove_parameter_verbosity_debug_e,
    kt_remove_parameter_version_e,
    kt_remove_parameter_accessed_e,
    kt_remove_parameter_block_e,
    kt_remove_parameter_character_e,
    kt_remove_parameter_created_e,
    kt_remove_parameter_different_e,
    kt_remove_parameter_directory_e,
    kt_remove_parameter_empty_e,
    kt_remove_parameter_fifo_e,
    kt_remove_parameter_follow_e,
    kt_remove_parameter_force_e,
    kt_remove_parameter_group_e,
    kt_remove_parameter_isolate_e,
    kt_remove_parameter_link_e,
    kt_remove_parameter_local_e,
    kt_remove_parameter_mode_e,
    kt_remove_parameter_prompt_e,
    kt_remove_parameter_recurse_e,
    kt_remove_parameter_regular_e,
    kt_remove_parameter_same_e,
    kt_remove_parameter_simulate_e,
    kt_remove_parameter_socket_e,
    kt_remove_parameter_stay_e,
    kt_remove_parameter_tree_e,
    kt_remove_parameter_updated_e,
    kt_remove_parameter_user_e,
    kt_remove_parameter_utc_e,
  }; // enum

  #define kt_remove_console_parameter_t_initialize \
    { \
      macro_f_console_parameter_t_initialize(f_console_standard_short_help_s.string,     f_console_standard_long_help_s.string,     0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_light_s.string,    f_console_standard_long_light_s.string,    0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_dark_s.string,     f_console_standard_long_dark_s.string,     0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_no_color_s.string, f_console_standard_long_no_color_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_quiet_s.string,    f_console_standard_long_quiet_s.string,    0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_error_s.string,    f_console_standard_long_error_s.string,    0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_normal_s.string,   f_console_standard_long_normal_s.string,   0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_verbose_s.string,  f_console_standard_long_verbose_s.string,  0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_debug_s.string,    f_console_standard_long_debug_s.string,    0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_version_s.string,  f_console_standard_long_version_s.string,  0, 0, f_console_type_inverse_e), \
      \
      macro_f_console_parameter_t_initialize(kt_remove_short_accessed_s.string,       kt_remove_long_accessed_s.string,       0, 2, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(kt_remove_short_block_s.string,          kt_remove_long_block_s.string,          0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(kt_remove_short_character_s.string,      kt_remove_long_character_s.string,      0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(kt_remove_short_created_s.string,        kt_remove_long_created_s.string,        0, 2, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(kt_remove_short_different_s.string,      kt_remove_long_different_s.string,      0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(kt_remove_short_directory_s.string,      kt_remove_long_directory_s.string,      0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(kt_remove_short_empty_s.string,          kt_remove_long_empty_s.string,          0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(kt_remove_short_fifo_s.string,           kt_remove_long_fifo_s.string,           0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(kt_remove_short_follow_s.string,         kt_remove_long_follow_s.string,         0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(kt_remove_short_force_s.string,          kt_remove_long_force_s.string,          0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(kt_remove_short_group_s.string,          kt_remove_long_group_s.string,          0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(kt_remove_short_isolate_s.string,        kt_remove_long_isolate_s.string,        0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(kt_remove_short_link_s.string,           kt_remove_long_link_s.string,           0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(0,                                       kt_remove_long_local_s.string,          0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(kt_remove_short_mode_s.string,           kt_remove_long_mode_s.string,           0, 2, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(kt_remove_short_prompt_s.string,         kt_remove_long_prompt_s.string,         0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(kt_remove_short_recurse_s.string,        kt_remove_long_recurse_s.string,        0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(kt_remove_short_regular_s.string,        kt_remove_long_regular_s.string,        0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(kt_remove_short_same_s.string,           kt_remove_long_same_s.string,           0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(kt_remove_short_simulate_s.string,       kt_remove_long_simulate_s.string,       0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(kt_remove_short_socket_s.string,         kt_remove_long_socket_s.string,         0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(kt_remove_short_stay_s.string,           kt_remove_long_stay_s.string,           0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(kt_remove_short_tree_s.string,           kt_remove_long_tree_s.string,           0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(kt_remove_short_updated_s.string,        kt_remove_long_updated_s.string,        0, 2, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(kt_remove_short_user_s.string,           kt_remove_long_user_s.string,           0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(0,                                       kt_remove_long_utc_s.string,            0, 0, f_console_type_normal_e), \
    }

  #define kt_remove_total_parameters_d 36
#endif // _di_kt_remove_parameter_d_

/**
 * Resize a date array.
 *
 * @param length
 *   The new size to use.
 * @param ranges
 *   The Date Comparison array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_kt_remove_dates_resize_
  extern f_status_t kt_remove_dates_resize(const f_array_length_t length, kt_remove_dates_t * const dates);
#endif // _di_kt_remove_dates_resize_

/**
 * Resize a mode array.
 *
 * @param length
 *   The new size to use.
 * @param ranges
 *   The Date Comparison array to resize.
 *
 * @return
 *   F_none on success.
 *
 *   F_array_too_large (with error bit) if the combined array is too large.
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_kt_remove_modes_resize_
  extern f_status_t kt_remove_modes_resize(const f_array_length_t length, kt_remove_modes_t * const modes);
#endif // _di_kt_remove_modes_resize_

/**
 * Delete the program main setting data.
 *
 * @param setting
 *   The program main setting data.
 *
 *   This does not alter setting.status.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_kt_remove_setting_delete_
  extern f_status_t kt_remove_setting_delete(kt_remove_setting_t * const setting);
#endif // _di_kt_remove_setting_delete_

/**
 * Perform the standard program setting load process.
 *
 * This prints error messages as appropriate.
 *
 * If either main or setting is NULL, then this immediately returns without doing anything.
 *
 * @param arguments
 *   The parameters passed to the process (often referred to as command line arguments).
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   The setting.flag has kt_remove_flag_option_used_e forcibly cleared on the start of this function.
 *
 *   This alters setting.status:
 *     F_none on success.
 *     F_data_not on success but nothing was provided to operate with.
 *
 *     F_parameter (with error bit) on parameter error.
 *
 *     Errors (with error bit) from: f_console_parameter_process().
 *     Errors (with error bit) from: f_file_stream_open().
 *     Errors (with error bit) from: f_string_dynamics_resize().
 *
 * @see f_console_parameter_process()
 * @see f_file_stream_open()
 * @see f_string_dynamics_resize()
 */
#ifndef _di_kt_remove_setting_load_
  extern void kt_remove_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, kt_remove_setting_t * const setting);
#endif // _di_kt_remove_setting_load_

/**
 * Perform the standard program setting unload process.
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   All buffers are deallocated.
 *
 *   This does not alter setting.status.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: utf8_setting_delete().
 *
 * @see utf8_setting_delete()
 */
#ifndef _di_kt_remove_setting_unload_
  extern f_status_t kt_remove_setting_unload(fll_program_data_t * const main, kt_remove_setting_t * const setting);
#endif // _di_kt_remove_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_remove_common_h
