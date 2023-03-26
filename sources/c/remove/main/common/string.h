/**
 * Kevux Tools - Remove
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common string structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _kt_remove_common_string_h
#define _kt_remove_common_string_h

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
 * Additional strings used for various purposes.
 *
 * kt_remove_*_s: Arbitrary strings.
 */
#ifndef _di_kt_remove_s_
  #define KT_REMOVE_all_s       "all"
  #define KT_REMOVE_follow_s    "follow"
  #define KT_REMOVE_force_s     "force"
  #define KT_REMOVE_ignore_s    "ignore"
  #define KT_REMOVE_never_s     "never"
  #define KT_REMOVE_no_s        "no"
  #define KT_REMOVE_not_s       "not"
  #define KT_REMOVE_not_fail_s  "not_fail"
  #define KT_REMOVE_now_s       "now"
  #define KT_REMOVE_once_s      "once"
  #define KT_REMOVE_only_s      "only"
  #define KT_REMOVE_only_fail_s "only_fail"
  #define KT_REMOVE_recurse_s   "recurse"
  #define KT_REMOVE_remove_s    "remove"
  #define KT_REMOVE_root_s      "root"
  #define KT_REMOVE_today_s     "today"
  #define KT_REMOVE_tomorrow_s  "tomorrow"
  #define KT_REMOVE_yes_s       "yes"
  #define KT_REMOVE_yesterday_s "yesterday"

  #define KT_REMOVE_all_s_length       3
  #define KT_REMOVE_follow_s_length    6
  #define KT_REMOVE_force_s_length     5
  #define KT_REMOVE_ignore_s_length    6
  #define KT_REMOVE_never_s_length     5
  #define KT_REMOVE_no_s_length        2
  #define KT_REMOVE_not_s_length       3
  #define KT_REMOVE_not_fail_s_length  8
  #define KT_REMOVE_now_s_length       3
  #define KT_REMOVE_once_s_length      4
  #define KT_REMOVE_only_s_length      4
  #define KT_REMOVE_only_fail_s_length 9
  #define KT_REMOVE_recurse_s_length   7
  #define KT_REMOVE_remove_s_length    6
  #define KT_REMOVE_root_s_length      4
  #define KT_REMOVE_today_s_length     5
  #define KT_REMOVE_tomorrow_s_length  8
  #define KT_REMOVE_yes_s_length       3
  #define KT_REMOVE_yesterday_s_length 9

  extern const f_string_static_t kt_remove_all_s;
  extern const f_string_static_t kt_remove_follow_s;
  extern const f_string_static_t kt_remove_force_s;
  extern const f_string_static_t kt_remove_ignore_s;
  extern const f_string_static_t kt_remove_never_s;
  extern const f_string_static_t kt_remove_no_s;
  extern const f_string_static_t kt_remove_not_s;
  extern const f_string_static_t kt_remove_not_fail_s;
  extern const f_string_static_t kt_remove_now_s;
  extern const f_string_static_t kt_remove_once_s;
  extern const f_string_static_t kt_remove_only_s;
  extern const f_string_static_t kt_remove_only_fail_s;
  extern const f_string_static_t kt_remove_recurse_s;
  extern const f_string_static_t kt_remove_remove_s;
  extern const f_string_static_t kt_remove_root_s;
  extern const f_string_static_t kt_remove_today_s;
  extern const f_string_static_t kt_remove_tomorrow_s;
  extern const f_string_static_t kt_remove_yes_s;
  extern const f_string_static_t kt_remove_yesterday_s;
#endif // _di_kt_remove_s_

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
 * The main program parameters.
 */
#ifndef _di_kt_remove_parameter_s_
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
#endif // _di_kt_remove_parameter_s_

/**
 * Strings used printing the reason why a removal failed.
 */
#ifndef _di_kt_remove_print_reason_s_
  #define KT_REMOVE_print_reason_no_access_s "file be accessed"
  #define KT_REMOVE_print_reason_not_found_s "file cannot be found"
  #define KT_REMOVE_print_reason_stat_fail_s "cannot read file statistics"

  #define KT_REMOVE_print_reason_no_access_s_length 16
  #define KT_REMOVE_print_reason_not_found_s_length 20
  #define KT_REMOVE_print_reason_stat_fail_s_length 27

  extern const f_string_static_t kt_remove_print_reason_no_access_s;
  extern const f_string_static_t kt_remove_print_reason_not_found_s;
  extern const f_string_static_t kt_remove_print_reason_stat_fail_s;
#endif // _di_kt_remove_print_reason_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_remove_common_string_h
