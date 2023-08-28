/**
 * Kevux Tools - Remove
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _kt_remove_common_print_h
#define _kt_remove_common_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A special array of strings intended for representing funciton names.
 *
 * These are primarily used for printing errors with the function names.
 *
 * The macro macro_kt_remove_f() is used to reference the array index by the enum name.
 *
 * macro_kt_remove_f():
 *   - name: The name of the function.
 */
#ifndef _di_kt_remove_f_a_
  extern const f_string_t kt_remove_f_a[];

  #define macro_kt_remove_f(name) kt_remove_f_a[kt_remove_f_##name##_e]
#endif // _di_kt_remove_f_a_

/**
 * An enum representing specific indexes within the above array.
 *
 * This is a convenience enum used to make code slightly more readable.
 */
#ifndef _di_kt_remove_f_e_
  enum {
    kt_remove_f_f_console_parameter_prioritize_right_e,
    kt_remove_f_f_console_parameter_process_e,
    kt_remove_f_f_file_mode_from_string_e,
    kt_remove_f_f_file_mode_to_mode_e,
    kt_remove_f_f_file_remove_e,
    kt_remove_f_f_memory_array_increase_by_e,
    kt_remove_f_f_memory_array_resize_e,
    kt_remove_f_f_thread_create_e,
    kt_remove_f_f_utf_is_digit_e,
    kt_remove_f_f_utf_is_whitespace_e,
    kt_remove_f_fl_conversion_dynamic_partial_to_unsigned_detect_e,
    kt_remove_f_fl_conversion_dynamic_to_unsigned_detect_e,
    kt_remove_f_fll_program_parameter_process_context_e,
    kt_remove_f_fll_program_parameter_process_empty_e,
    kt_remove_f_fll_program_parameter_process_verbosity_e,
    kt_remove_f_kt_remove_convert_date_relative_e,
    kt_remove_f_kt_remove_convert_timezone_e,
    kt_remove_f_kt_remove_dates_resize_e,
    kt_remove_f_kt_remove_get_id_group_e,
    kt_remove_f_kt_remove_get_id_user_e,
    kt_remove_f_kt_remove_modes_resize_e,
  }; // enum
#endif // _di_kt_remove_f_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_remove_common_print_h
