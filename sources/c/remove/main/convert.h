/**
 * Kevux Tools - Remove
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _kt_remove_convert_h
#define _kt_remove_convert_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Convert the string from a string representation of date into the numeric representation of that date.
 *
 * This accepts the following formats:
 * - Time, with or without year (2022:1234, :1234).
 * - EpochTime, with or without year (2022::1234, ::1234).
 * - Relative strings: 'now', 'today', 'tomorrow', 'yesterday'.
 *
 * Note that 'today', 'tomorrow', and 'yesterday' represent whole days.
 * Any greater than like values starts at the end of the day.
 * Any lesser than like values start at the beginning of the day.
 *
 * Note that the 'now' is the current moment in time down to the lowest supported unit of time.
 *
 * Only a limited set of 'time' string values are implemented in this project.
 * More 'time' string values will likely be implemented in a not yet existent 'f_time' project in FLL 0.7 or greater (possibly including fl_time and fll_time).
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.status:
 *     F_none on success.
 *     F_data_not on success, but buffer is empty and there is no data to process.
 *
 *     F_buffer (with error bit) if the buffer is invalid.
 *     F_parameter (with error bit) if a parameter is invalid.
 *     F_prohibited (with error bit) if the system does not permit accessing the system clock.
 *     F_failure (with error bit) for any other failure.
 *
 *     @todo review codes below.
 *     F_number_too_large (with error bit) if the given ID is too large.
 *     F_number_too_small (with error bit) if the given ID is too small.
 *     F_known_not (with error bit) if the given string is not of a known format
 *
 *     Errors (with error bit) from: fl_conversion_dynamic_partial_to_unsigned_detect().
 *     Errors (with error bit) from: fl_string_dynamic_partial_rip_nulless().
 *
 *     Errors (with error bit) from: kt_remove_get_date_relative().
 * @param buffer
 *   A string containing group name or ID.
 * @param date
 *   The converted date.
 *
 * @see fl_conversion_dynamic_partial_to_unsigned_detect()
 * @see fl_string_dynamic_partial_rip_nulless()
 *
 * @see kt_remove_get_date_relative()
 */
#ifndef _di_kt_remove_convert_date_
  extern void kt_remove_convert_date(fll_program_data_t * const main, kt_remove_setting_t * const setting, const f_string_static_t buffer, kt_remove_date_t * const date);
#endif // _di_kt_remove_convert_date_

/**
 * Convert the string from a string representation of date into the numeric representation of that date in seconds since epoch.
 *
 * This accepts the following formats:
 * - Relative strings: 'now', 'today', 'tomorrow', and 'yesterday'.
 *
 * For 'now', the current time in seconds is returned.
 * For 'today', the start of the day is returned.
 * For 'tomorrow', the start of the day after 'today' is returned.
 * For 'yesterday', the start of the day before 'today' is returned.
 *
 * Only a limited set of 'time' string values are implemented in this project.
 * More 'time' string values will likely be implemented in a not yet existent 'f_time' project in FLL 0.7 or greater (possibly including fl_time and fll_time).
 *
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.status:
 *     F_none on success.
 *     F_data_not on success, but buffer is empty or there is no data to process.
 *
 *     F_buffer (with error bit) if the buffer is invalid.
 *     F_parameter (with error bit) if a parameter is invalid.
 *     F_prohibited (with error bit) if the system does not permit accessing the system clock.
 *     F_failure (with error bit) for any other failure.
 * @param date
 *   The converted date.
 *
 * @see clock_gettime()
 *
 * @see f_utf_is_digit()
 * @see f_utf_is_whitespace()
 * @see fl_conversion_dynamic_partial_to_unsigned_detect()
 *
 * @see kt_remove_get_date_relative()
 */
#ifndef _di_kt_remove_convert_date_relative_
  extern void kt_remove_convert_date_relative(kt_remove_setting_t * const setting, kt_remove_date_t * const date);
#endif // _di_kt_remove_convert_date_relative_

/**
 * Convert the string from a string representation of an ID or a group name into the numeric representation of that ID or group name.
 *
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.status:
 *     F_none on success.
 *
 *     F_number_too_large (with error bit) if the given ID is too large.
 *
 *     Errors (with error bit) from: f_account_group_id_by_name().
 *     Errors (with error bit) from: fl_conversion_dynamic_to_unsigned_detect().
 *     Errors (with error bit) from: fl_string_dynamic_rip_nulless().
 * @param buffer
 *   A string containing group name or ID.
 *
 * @see f_account_group_id_by_name()
 * @see fl_conversion_dynamic_to_unsigned_detect()
 * @see fl_string_dynamic_rip_nulless()
 */
#ifndef _di_kt_remove_get_id_group_
  extern uint32_t kt_remove_get_id_group(kt_remove_setting_t * const setting, const f_string_static_t buffer);
#endif // _di_kt_remove_get_id_group_

/**
 * Convert the string from a string representation of an ID or a user name into the numeric representation of that ID or user name.
 *
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.status:
 *     F_none on success.
 *
 *     F_number_too_large (with error bit) if the given ID is too large.
 *
 *     Errors (with error bit) from: f_account_group_id_by_name().
 *     Errors (with error bit) from: fl_conversion_dynamic_to_unsigned_detect().
 *     Errors (with error bit) from: fl_string_dynamic_rip_nulless().
 * @param buffer
 *   A string containing group name or ID.
 *
 * @see f_account_id_by_name()
 * @see fl_conversion_dynamic_to_unsigned_detect()
 * @see fl_string_dynamic_rip_nulless()
 */
#ifndef _di_kt_remove_get_id_user_
  extern uint32_t kt_remove_get_id_user(kt_remove_setting_t * const setting, const f_string_static_t buffer);
#endif // _di_kt_remove_get_id_user_

/**
 * Convert the string from a string representation of a mode into the numeric representation of that mode.
 *
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_file_mode_from_string().
 *     Errors (with error bit) from: f_file_mode_to_mode().
 * @param buffer
 *   A string containing group name or ID.
 *
 * @see f_file_mode_from_string()
 * @see f_file_mode_to_mode()
 */
#ifndef _di_kt_remove_get_mode_
  extern mode_t kt_remove_get_mode(fll_program_data_t * const main, kt_remove_setting_t * const setting, const f_string_static_t buffer);
#endif // _di_kt_remove_get_mode_

/**
 * Convert the given date to the local time zone.
 *
 * This does not check the flags to see if UTC is in used.
 * The caller must assure this is appropriate.
 *
 * @param setting
 *   The main program settings.
 *
 *   This alters setting.status:
 *     F_none on success.
 *
 *     F_number_overflow (with error bit) if the date after applying the timezone is too large.
 *     F_number_underflow (with error bit) if the date after applying the timezone is too small.
 *     F_parameter (with error bit) if a parameter is invalid.
 * @param year
 *   The year value.
 *   This is commonly set to UNIX Epoch.
 *   This is only updated if the timezone would result in a year change.
 * @param seconds
 *   The seconds since the start of the year.
 *   This is updated based on the global timezone variable.
 */
#ifndef _di_kt_remove_convert_timezone_
  extern void kt_remove_convert_timezone(kt_remove_setting_t * const setting, f_number_unsigned_t * const year, f_number_unsigned_t * const seconds);
#endif // _di_kt_remove_convert_timezone_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_remove_convert_h
