#include "remove.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_remove_print_error_
  f_status_t kt_remove_print_error(kt_remove_setting_t * const setting, const fl_print_t print, const f_string_t function) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    fll_error_print(print, F_status_set_fine(setting->status), function, F_true);

    return F_none;
  }
#endif // _di_kt_remove_print_error_

#ifndef _di_kt_remove_print_error_file_
  f_status_t kt_remove_print_error_file(kt_remove_setting_t * const setting, const fl_print_t print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    fll_error_file_print(print, F_status_set_fine(setting->status), function, F_true, name, operation, type);

    return F_none;
  }
#endif // _di_kt_remove_print_error_file_

#ifndef _di_kt_remove_print_error_parameter_missing_value_requires_amount_
  f_status_t kt_remove_print_error_parameter_missing_value_requires_amount(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t parameter, const f_number_unsigned_t amount) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    flockfile(print.to.stream);

    fl_print_format("%[%QThe parameter%] ", print.to.stream, print.set->error, print.prefix, print.set->error);
    fl_print_format("%[%Q%Q%]", print.to.stream, print.set->notable, symbol, parameter, print.set->notable);
    fl_print_format("%[ is specified, but%] ", print.to.stream, print.set->error, print.set->error);
    fl_print_format("%[%un%]", print.to.stream, print.set->notable, amount, print.set->notable);
    fl_print_format(" %[values are not given.%]%r", print.to.stream, print.set->error, print.set->error, f_string_eol_s);

    funlockfile(print.to.stream);

    return F_none;
  }
#endif // _di_kt_remove_print_error_parameter_missing_value_requires_amount_

#ifndef _di_kt_remove_print_error_parameter_no_files_
  f_status_t kt_remove_print_error_parameter_no_files(const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    fll_print_format("%[%QNo files have been specified to be removed.%]%r", print.to.stream, print.set->error, print.prefix, print.set->error, f_string_eol_s);

    return F_none;
  }
#endif // _di_kt_remove_print_error_parameter_no_files_

#ifndef _di_kt_remove_print_error_parameter_unknown_value_
  f_status_t kt_remove_print_error_parameter_unknown_value(const fl_print_t print, const f_string_static_t symbol, const f_string_static_t parameter, const f_string_static_t value) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    flockfile(print.to.stream);

    fl_print_format("%[%QThe parameter%] ", print.to.stream, print.set->error, print.prefix, print.set->error);
    fl_print_format("%[%Q%Q%]", print.to.stream, print.set->notable, symbol, parameter, print.set->notable);
    fl_print_format("%[ is passed an unknown value '%]", print.to.stream, print.set->error, print.set->error);
    fl_print_format("%[%Q%]", print.to.stream, print.set->notable, value, print.set->notable);
    fl_print_format("%['.%]%r", print.to.stream, print.set->error, print.set->error, f_string_eol_s);

    funlockfile(print.to.stream);

    return F_none;
  }
#endif // _di_kt_remove_print_error_parameter_unknown_value_

#ifndef _di_kt_remove_print_help_
  f_status_t kt_remove_print_help(kt_remove_setting_t * const setting, const fl_print_t print, const f_color_context_t context) {

    if (!setting) return F_output_not;

    flockfile(print.to.stream);

    fll_program_print_help_header(print.to, context, *setting->program_name_long, kt_remove_program_version_s);

    fll_program_print_help_option(print.to, context, f_console_standard_short_help_s, f_console_standard_long_help_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Print this help message.");
    fll_program_print_help_option(print.to, context, f_console_standard_short_dark_s, f_console_standard_long_dark_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(print.to, context, f_console_standard_short_light_s, f_console_standard_long_light_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(print.to, context, f_console_standard_short_no_color_s, f_console_standard_long_no_color_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "Do not print.to using color.");
    fll_program_print_help_option(print.to, context, f_console_standard_short_quiet_s, f_console_standard_long_quiet_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity, silencing most output.");
    fll_program_print_help_option(print.to, context, f_console_standard_short_error_s, f_console_standard_long_error_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Decrease verbosity, using only error output.");
    fll_program_print_help_option(print.to, context, f_console_standard_short_normal_s, f_console_standard_long_normal_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "  Set verbosity to normal.");
    fll_program_print_help_option(print.to, context, f_console_standard_short_verbose_s, f_console_standard_long_verbose_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Increase verbosity beyond normal output.");
    fll_program_print_help_option(print.to, context, f_console_standard_short_debug_s, f_console_standard_long_debug_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, "   Enable debugging, significantly increasing verbosity beyond normal output.");
    fll_program_print_help_option(print.to, context, f_console_standard_short_version_s, f_console_standard_long_version_s, f_console_symbol_short_disable_s, f_console_symbol_long_disable_s, " Print only the version number.");

    f_print_dynamic_raw(f_string_eol_s, print.to.stream);

    fll_program_print_help_option(print.to, context, kt_remove_short_accessed_s, kt_remove_long_accessed_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Remove by file last accessed date and time.");
    fll_program_print_help_option(print.to, context, kt_remove_short_block_s, kt_remove_long_block_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Remove by file type of block.");
    fll_program_print_help_option(print.to, context, kt_remove_short_character_s, kt_remove_long_character_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Remove by file type of character.");
    fll_program_print_help_option(print.to, context, kt_remove_short_created_s, kt_remove_long_created_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Remove by file created on date and time.");
    fll_program_print_help_option(print.to, context, kt_remove_short_different_s, kt_remove_long_different_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Remove by file owner by a user different from the current calling user.");
    fll_program_print_help_option(print.to, context, kt_remove_short_directory_s, kt_remove_long_directory_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Remove by file type of directory.");
    fll_program_print_help_option(print.to, context, kt_remove_short_empty_s, kt_remove_long_empty_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Remove directory by a specific empty or not empty state.");
    fll_program_print_help_option(print.to, context, kt_remove_short_fifo_s, kt_remove_long_fifo_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Remove by file type of FIFO.");
    fll_program_print_help_option(print.to, context, kt_remove_short_follow_s, kt_remove_long_follow_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Remove the file being pointed to rather than the symbolic link itself.");
    fll_program_print_help_option(print.to, context, kt_remove_short_force_s, kt_remove_long_force_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Forcibly perform remove.");
    fll_program_print_help_option(print.to, context, kt_remove_short_group_s, kt_remove_long_group_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Remove by file group ID or name.");
    fll_program_print_help_option(print.to, context, kt_remove_short_isolate_s, kt_remove_long_isolate_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Isolate remove based on filesystem.");
    fll_program_print_help_option(print.to, context, kt_remove_short_link_s, kt_remove_long_link_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Remove by file type of link.");
    fll_program_print_help_option(print.to, context, kt_remove_short_mode_s, kt_remove_long_mode_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Remove by file mode.");
    fll_program_print_help_option(print.to, context, kt_remove_short_prompt_s, kt_remove_long_prompt_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Prompt before removing.");
    fll_program_print_help_option(print.to, context, kt_remove_short_recurse_s, kt_remove_long_recurse_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Traverse into sub-directories when removing.");
    fll_program_print_help_option(print.to, context, kt_remove_short_regular_s, kt_remove_long_regular_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Remove by file type of regular.");
    fll_program_print_help_option(print.to, context, kt_remove_short_same_s, kt_remove_long_same_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Remove by file owner by the current calling user.");
    fll_program_print_help_option(print.to, context, kt_remove_short_simulate_s, kt_remove_long_simulate_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Simulate removal rather than actually removing.");
    fll_program_print_help_option(print.to, context, kt_remove_short_socket_s, kt_remove_long_socket_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Remove by file type of socket.");
    fll_program_print_help_option(print.to, context, kt_remove_short_stay_s, kt_remove_long_stay_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Remove the symbolic link itself rather than the file being pointed to.");
    fll_program_print_help_option(print.to, context, kt_remove_short_tree_s, kt_remove_long_tree_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Remove entire specified directory tree.");
    fll_program_print_help_option(print.to, context, kt_remove_short_updated_s, kt_remove_long_updated_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Remove by file last updated date and time.");
    fll_program_print_help_option(print.to, context, kt_remove_short_user_s, kt_remove_long_user_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "     Remove by file user ID or name.");

    f_print_dynamic_raw(f_string_eol_s, print.to.stream);

    fll_program_print_help_option_long(print.to, context, kt_remove_long_local_s, f_console_symbol_long_enable_s, "Designate dates are in local time, unless time zone is specified.");
    fll_program_print_help_option_long(print.to, context, kt_remove_long_utc_s, f_console_symbol_long_enable_s, "  Designate dates are in UTC, unless time zone is specified.");

    fll_program_print_help_usage(print.to, context, kt_remove_program_name_s, kt_remove_program_help_parameters_s);

    fl_print_format("  The parameters '%[%r%r%]', ", print.to.stream, context.set.notable, f_console_symbol_long_enable_s, kt_remove_long_accessed_s, context.set.notable);
    fl_print_format("'%[%r%r%]', ", print.to.stream, context.set.notable, f_console_symbol_long_enable_s, kt_remove_long_created_s, context.set.notable);
    fl_print_format("'%[%r%r%]', ", print.to.stream, context.set.notable, f_console_symbol_long_enable_s, kt_remove_long_group_s, context.set.notable);
    fl_print_format("'%[%r%r%]', ", print.to.stream, context.set.notable, f_console_symbol_long_enable_s, kt_remove_long_mode_s, context.set.notable);
    fl_print_format("'%[%r%r%]', and ", print.to.stream, context.set.notable, f_console_symbol_long_enable_s, kt_remove_long_updated_s, context.set.notable);
    fl_print_format("'%[%r%r%]' may be specified multiple times.%r%r", print.to.stream, context.set.notable, f_console_symbol_long_enable_s, kt_remove_long_user_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The value passed to the parameter '%[%r%r%]' may either be a ", print.to.stream, context.set.notable, f_console_symbol_long_enable_s, kt_remove_long_group_s, context.set.notable, f_string_eol_s);
    fl_print_format("%[GID%]", print.to.stream, context.set.notable, context.set.notable);
    fl_print_format(" or a %[group name%].%r%r", print.to.stream, context.set.notable, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The value passed to the parameter '%[%r%r%]' may either be a ", print.to.stream, context.set.notable, f_console_symbol_long_enable_s, kt_remove_long_user_s, context.set.notable, f_string_eol_s);
    fl_print_format("%[UID%]", print.to.stream, context.set.notable, context.set.notable);
    fl_print_format(" or a %[user name%].%r%r", print.to.stream, context.set.notable, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The parameter '%[%r%r%]' supports the following values:%r", print.to.stream, context.set.notable, f_console_symbol_long_enable_s, kt_remove_long_empty_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':       Remove directories that are not empty.%r", print.to.stream, context.set.notable, kt_remove_not_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':  Fail when attempting to remove directories that are not empty.%r", print.to.stream, context.set.notable, kt_remove_not_fail_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':      Remove directories that are empty.%r", print.to.stream, context.set.notable, kt_remove_only_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]': Fail when removing directoies that are empty.%r%r", print.to.stream, context.set.notable, kt_remove_only_fail_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The parameter '%[%r%r%]' supports the following values:%r", print.to.stream, context.set.notable, f_console_symbol_long_enable_s, kt_remove_long_isolate_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':    Isolate to a single file system, error on all files outside of the file system.%r", print.to.stream, context.set.notable, kt_remove_all_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]': Ignore rather than erroring on problems outside the file system.%r", print.to.stream, context.set.notable, kt_remove_ignore_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':   Isolate to a single file system, error on '/'.%r%r", print.to.stream, context.set.notable, kt_remove_root_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    // @todo "isolate" needs to optionally pass, ignoring when /proc is not available or fail when /proc is not available.
    // @todo "/proc" needs to be configurable define macro and use that string here.

    fl_print_format("  The parameter '%[%r%r%]' supports the following values:%r", print.to.stream, context.set.notable, f_console_symbol_long_enable_s, kt_remove_long_prompt_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':    Operate in interactive mode, prompting for every file.%r", print.to.stream, context.set.notable, kt_remove_all_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]': Operate in interactive mode, prompting for every link that is being followed.%r", print.to.stream, context.set.notable, kt_remove_follow_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':  Do not operate in interactive mode.%r", print.to.stream, context.set.notable, kt_remove_never_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':   Operate in interactive mode: prompting if removing 3 or more files.%r%r", print.to.stream, context.set.notable, kt_remove_once_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The first value to the parameter '%[%r%r%]' must be any of:%r", print.to.stream, context.set.notable, f_console_symbol_long_enable_s, kt_remove_long_mode_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]'", print.to.stream, context.set.notable, kt_remove_mode_symbol_different_s, context.set.notable);
    fl_print_format(" or '%[%r%]': Mode matches different parts.%r", print.to.stream, context.set.notable, kt_remove_mode_word_different_s, context.set.notable, f_string_eol_s);

    fl_print_format("  - '%[%r%]'", print.to.stream, context.set.notable, kt_remove_mode_symbol_same_s, context.set.notable);
    fl_print_format(" or '%[%r%]':      Mode matches exactly.%r", print.to.stream, context.set.notable, kt_remove_mode_word_same_s, context.set.notable, f_string_eol_s);

    fl_print_format("  - '%[%r%]'", print.to.stream, context.set.notable, kt_remove_mode_symbol_similar_s, context.set.notable);
    fl_print_format(" or '%[%r%]':   Mode matches the same parts.%r", print.to.stream, context.set.notable, kt_remove_mode_word_similar_s, context.set.notable, f_string_eol_s);

    fl_print_format("  - '%[%r%]'", print.to.stream, context.set.notable, kt_remove_mode_symbol_not_s, context.set.notable);
    fl_print_format(" or '%[%r%]':       Mode does not match exactly.%r%r", print.to.stream, context.set.notable, kt_remove_mode_word_not_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The second value to the parameter '%[%r%r%]' may be either a mode octal or a mode string, such as: ", print.to.stream, context.set.notable, f_console_symbol_long_enable_s, kt_remove_long_mode_s, context.set.notable);
    fl_print_format("'%[0751%]'", print.to.stream, context.set.notable, context.set.notable);
    fl_print_format(" or '%[u+rwX,g+r%]'.%r%r", print.to.stream, context.set.notable, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The date related parameters are: '%[%r%r%]', ", print.to.stream, context.set.notable, f_console_symbol_long_enable_s, kt_remove_long_accessed_s, context.set.notable);
    fl_print_format("'%[%r%r%]', and ", print.to.stream, context.set.notable, f_console_symbol_long_enable_s, kt_remove_long_created_s, context.set.notable);
    fl_print_format("'%[%r%r%]'.%r%r", print.to.stream, context.set.notable, f_console_symbol_long_enable_s, kt_remove_long_updated_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The first value to the date related parameters must be any of the following comparison operators:%r", print.to.stream, f_string_eol_s);
    fl_print_format("  - '%[%r%]'", print.to.stream, context.set.notable, kt_remove_date_symbol_equal_s, context.set.notable);
    fl_print_format(" or '%[%r%]':      Date match using an equal to operation.%r", print.to.stream, context.set.notable, kt_remove_date_word_equal_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]'", print.to.stream, context.set.notable, kt_remove_date_symbol_less_s, context.set.notable);
    fl_print_format(" or '%[%r%]':        Date match using a less than operation.%r", print.to.stream, context.set.notable, kt_remove_date_word_less_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]'", print.to.stream, context.set.notable, kt_remove_date_symbol_less_equal_s, context.set.notable);
    fl_print_format(" or '%[%r%]': Date match using a less than or equal to operation.%r", print.to.stream, context.set.notable, kt_remove_date_word_less_equal_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]'", print.to.stream, context.set.notable, kt_remove_date_symbol_more_s, context.set.notable);
    fl_print_format(" or '%[%r%]':        Date match using a more than operation.%r", print.to.stream, context.set.notable, kt_remove_date_word_more_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]'", print.to.stream, context.set.notable, kt_remove_date_symbol_more_equal_s, context.set.notable);
    fl_print_format(" or '%[%r%]': Date match using a more than or equal to operation.%r", print.to.stream, context.set.notable, kt_remove_date_word_more_equal_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]'", print.to.stream, context.set.notable, kt_remove_date_symbol_not_s, context.set.notable);
    fl_print_format(" or '%[%r%]':        Date match using a not equal to operation.%r%r", print.to.stream, context.set.notable, kt_remove_date_word_not_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When the second value to the date related parameters must be a date.%r%r", print.to.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  Valid dates for the date related parameters must be any of the following:%r", print.to.stream, f_string_eol_s);
    fl_print_format("  - '%[%r%]':        Use the current day and time.%r", print.to.stream, context.set.notable, kt_remove_now_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[Time%]':       Use the Time format, such as ", print.to.stream, context.set.notable, context.set.notable);
    fl_print_format("'%[1234:5678%]'.%r", print.to.stream, context.set.notable, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[EpochTime%]':  Use the EpochTime format, such as ", print.to.stream, context.set.notable, context.set.notable);
    fl_print_format("'%[1234::5678%]'.%r", print.to.stream, context.set.notable, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':      Use the current day.%r", print.to.stream, context.set.notable, kt_remove_today_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':   Use the next day.%r", print.to.stream, context.set.notable, kt_remove_tomorrow_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[Unix Epoch%]': Use the EpochTime format, such as ", print.to.stream, context.set.notable, context.set.notable);
    fl_print_format("'%[1672639985%]'.%r", print.to.stream, context.set.notable, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':  Use the previous day.%r%r", print.to.stream, context.set.notable, kt_remove_yesterday_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  Valid formats for the date related parameters must be any of the following:%r", print.to.stream, f_string_eol_s);
    fl_print_format("  - '%[%r%]': A date like '%[%r%]'.%r", print.to.stream, context.set.notable, kt_remove_date_format_00_s, context.set.notable, context.set.notable, kt_remove_date_format_example_00_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':    A date like '%[%r%]'.%r", print.to.stream, context.set.notable, kt_remove_date_format_01_s, context.set.notable, context.set.notable, kt_remove_date_format_example_01_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':    A date like '%[%r%]'.%r", print.to.stream, context.set.notable, kt_remove_date_format_02_s, context.set.notable, context.set.notable, kt_remove_date_format_example_02_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':       A date like '%[%r%]'.%r", print.to.stream, context.set.notable, kt_remove_date_format_03_s, context.set.notable, context.set.notable, kt_remove_date_format_example_03_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':       A date like '%[%r%]'.%r", print.to.stream, context.set.notable, kt_remove_date_format_04_s, context.set.notable, context.set.notable, kt_remove_date_format_example_04_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':          A date like '%[%r%]'.%r", print.to.stream, context.set.notable, kt_remove_date_format_05_s, context.set.notable, context.set.notable, kt_remove_date_format_example_05_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':    A date like '%[%r%]'.%r", print.to.stream, context.set.notable, kt_remove_date_format_06_s, context.set.notable, context.set.notable, kt_remove_date_format_example_06_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':       A date like '%[%r%]'.%r", print.to.stream, context.set.notable, kt_remove_date_format_07_s, context.set.notable, context.set.notable, kt_remove_date_format_example_07_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':       A date like '%[%r%]'.%r", print.to.stream, context.set.notable, kt_remove_date_format_08_s, context.set.notable, context.set.notable, kt_remove_date_format_example_08_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':          A date like '%[%r%]'.%r", print.to.stream, context.set.notable, kt_remove_date_format_09_s, context.set.notable, context.set.notable, kt_remove_date_format_example_09_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':          A date like '%[%r%]'.%r", print.to.stream, context.set.notable, kt_remove_date_format_10_s, context.set.notable, context.set.notable, kt_remove_date_format_example_10_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':             A date like '%[%r%]'.%r", print.to.stream, context.set.notable, kt_remove_date_format_11_s, context.set.notable, context.set.notable, kt_remove_date_format_example_11_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':                A date like '%[%r%]'.%r", print.to.stream, context.set.notable, kt_remove_date_format_12_s, context.set.notable, context.set.notable, kt_remove_date_format_example_12_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':                   A date like '%[%r%]'.%r", print.to.stream, context.set.notable, kt_remove_date_format_13_s, context.set.notable, context.set.notable, kt_remove_date_format_example_13_s, context.set.notable, f_string_eol_s);
    fl_print_format("  - '%[%r%]':                     A date like '%[%r%]'.%r%r", print.to.stream, context.set.notable, kt_remove_date_format_14_s, context.set.notable, context.set.notable, kt_remove_date_format_example_14_s, context.set.notable, f_string_eol_s, f_string_eol_s);

    fflush(print.to.stream);
    funlockfile(print.to.stream);

    return F_none;
  }
#endif // _di_kt_remove_print_help_

#ifndef _di_kt_remove_print_warning_file_reason_
  f_status_t remove_print_warning_file_reason(kt_remove_setting_t * const setting, const fl_print_t print, const f_string_static_t path, const f_string_static_t reason) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;
    if (print.verbosity < f_console_verbosity_verbose_e && !(setting->flag & kt_remove_flag_force_e)) {
      if (setting) {
        if (!(setting->flag & kt_remove_flag_print_warning_e)) return F_output_not;
      }
      else {
        return F_output_not;
      }
    }

    flockfile(print.to.stream);

    fl_print_format("%[%QUnable to remove file '%]", print.to.stream, print.set->warning, print.prefix, print.set->warning);
    fl_print_format("%[%Q%]", print.to.stream, print.set->notable, path, print.set->notable);
    fl_print_format("%[', %Q.%]%r", print.to.stream, print.set->warning, reason, print.set->warning, f_string_eol_s);

    funlockfile(print.to.stream);

    return F_none;
  }
#endif // _di_kt_remove_print_warning_file_reason_

#ifdef __cplusplus
} // extern "C"
#endif
