/**
 * Kevux Tools - Remove
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common enumeration types.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _kt_remove_common_enumeration_h
#define _kt_remove_common_enumeration_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Flags passed to the main function or program.
 *
 * kt_remove_main_flag_*_e:
 *   - none:            No flags set.
 *   - accessed:        @todo
 *   - block:           Remove by file type: block.
 *   - character:       Remove by file type: character.
 *   - copyright:       Print copyright.
 *   - created:         @todo
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
 *   - print_first:     When set, print new line to message output on program begin after loading settings.
 *   - print_last:      When set, print new line to message output on program end.
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
    kt_remove_main_flag_none_e            = 0x0,
    kt_remove_main_flag_accessed_e        = 0x1,
    kt_remove_main_flag_block_e           = 0x2,
    kt_remove_main_flag_character_e       = 0x4,
    kt_remove_main_flag_copyright_e       = 0x8,
    kt_remove_main_flag_created_e         = 0x10,
    kt_remove_main_flag_different_e       = 0x20,
    kt_remove_main_flag_directory_e       = 0x40,
    kt_remove_main_flag_empty_only_e      = 0x80,
    kt_remove_main_flag_empty_only_fail_e = 0x100,
    kt_remove_main_flag_empty_not_e       = 0x200,
    kt_remove_main_flag_empty_not_fail_e  = 0x400,
    kt_remove_main_flag_fifo_e            = 0x800,
    kt_remove_main_flag_follow_e          = 0x1000,
    kt_remove_main_flag_force_e           = 0x2000,
    kt_remove_main_flag_group_e           = 0x4000,
    kt_remove_main_flag_help_e            = 0x8000,
    kt_remove_main_flag_isolate_all_e     = 0x10000,
    kt_remove_main_flag_isolate_ignore_e  = 0x20000,
    kt_remove_main_flag_isolate_root_e    = 0x40000,
    kt_remove_main_flag_link_e            = 0x80000,
    kt_remove_main_flag_mode_e            = 0x100000,
    kt_remove_main_flag_option_used_e     = 0x200000,
    kt_remove_main_flag_print_first_e     = 0x400000,
    kt_remove_main_flag_print_last_e      = 0x800000,
    kt_remove_main_flag_prompt_all_e      = 0x1000000,
    kt_remove_main_flag_prompt_follow_e   = 0x2000000,
    kt_remove_main_flag_prompt_never_e    = 0x4000000,
    kt_remove_main_flag_prompt_once_e     = 0x8000000,
    kt_remove_main_flag_recurse_e         = 0x10000000,
    kt_remove_main_flag_regular_e         = 0x20000000,
    kt_remove_main_flag_same_e            = 0x40000000,
    kt_remove_main_flag_simulate_e        = 0x80000000,
    kt_remove_main_flag_socket_e          = 0x100000000,
    kt_remove_main_flag_tree_e            = 0x200000000,
    kt_remove_main_flag_updated_e         = 0x400000000,
    kt_remove_main_flag_user_e            = 0x800000000,
    kt_remove_main_flag_utc_e             = 0x1000000000,
    kt_remove_main_flag_version_e         = 0x2000000000,
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
 * The main program parameters.
 */
#ifndef _di_kt_remove_parameter_e_
  enum {
    kt_remove_parameter_help_e,
    kt_remove_parameter_copyright_e,
    kt_remove_parameter_light_e,
    kt_remove_parameter_dark_e,
    kt_remove_parameter_no_color_e,
    kt_remove_parameter_verbosity_quiet_e,
    kt_remove_parameter_verbosity_error_e,
    kt_remove_parameter_verbosity_normal_e,
    kt_remove_parameter_verbosity_verbose_e,
    kt_remove_parameter_verbosity_debug_e,
    kt_remove_parameter_version_e,
    kt_remove_parameter_line_first_no_e,
    kt_remove_parameter_line_last_no_e,

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
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_help_s,          f_console_standard_long_help_s,          0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_copyright_s,     f_console_standard_long_copyright_s,     0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_light_s,         f_console_standard_long_light_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_dark_s,          f_console_standard_long_dark_s,          0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_no_color_s,      f_console_standard_long_no_color_s,      0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_quiet_s,         f_console_standard_long_quiet_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_error_s,         f_console_standard_long_error_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_normal_s,        f_console_standard_long_normal_s,        0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_verbose_s,       f_console_standard_long_verbose_s,       0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_debug_s,         f_console_standard_long_debug_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_version_s,       f_console_standard_long_version_s,       0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_line_first_no_s, f_console_standard_long_line_first_no_s, 0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_line_last_no_s,  f_console_standard_long_line_last_no_s,  0, f_console_flag_inverse_e), \
      \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_accessed_s,  kt_remove_long_accessed_s,  2, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_block_s,     kt_remove_long_block_s,     0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_character_s, kt_remove_long_character_s, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_created_s,   kt_remove_long_created_s,   2, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_different_s, kt_remove_long_different_s, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_directory_s, kt_remove_long_directory_s, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_empty_s,     kt_remove_long_empty_s,     1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_fifo_s,      kt_remove_long_fifo_s,      0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_follow_s,    kt_remove_long_follow_s,    0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_force_s,     kt_remove_long_force_s,     0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_group_s,     kt_remove_long_group_s,     1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_isolate_s,   kt_remove_long_isolate_s,   1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_link_s,      kt_remove_long_link_s,      0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_5(                             kt_remove_long_local_s,     0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_mode_s,      kt_remove_long_mode_s,      2, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_prompt_s,    kt_remove_long_prompt_s,    1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_recurse_s,   kt_remove_long_recurse_s,   0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_regular_s,   kt_remove_long_regular_s,   0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_same_s,      kt_remove_long_same_s,      0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_simulate_s,  kt_remove_long_simulate_s,  0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_socket_s,    kt_remove_long_socket_s,    0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_stay_s,      kt_remove_long_stay_s,      0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_tree_s,      kt_remove_long_tree_s,      0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_updated_s,   kt_remove_long_updated_s,   2, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(kt_remove_short_user_s,      kt_remove_long_user_s,      1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_5(                             kt_remove_long_utc_s,       0, f_console_flag_normal_e), \
    }

  #define kt_remove_total_parameters_d 39
#endif // _di_kt_remove_parameter_e_

/**
 * Flags for fine-tuned print control.
 *
 * kt_remove_print_flag_*_e:
 *   - none:    No flags set.
 *   - debug:   Stream is for debug printing.
 *   - error:   Stream is for error printing.
 *   - file:    Stream is associated with a file.
 *   - in:      Stream is a source file.
 *   - message: Stream is for message printing.
 *   - out:     Stream is a destination file.
 *   - warning: Stream is for warning printing.
 */
#ifndef _di_kt_remove_print_flag_e_
  enum {
    kt_remove_print_flag_none_e    = 0x0,
    kt_remove_print_flag_debug_e   = 0x1,
    kt_remove_print_flag_error_e   = 0x2,
    kt_remove_print_flag_file_e    = 0x4,
    kt_remove_print_flag_in_e      = 0x8,
    kt_remove_print_flag_message_e = 0x10,
    kt_remove_print_flag_out_e     = 0x20,
    kt_remove_print_flag_warning_e = 0x40,
  }; // enum
#endif // _di_kt_remove_print_flag_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_remove_common_enumeration_h
