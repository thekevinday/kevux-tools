#include "remove.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_remove_convert_date_
  void kt_remove_convert_date(kt_remove_main_t * const main, const f_string_static_t buffer, kt_remove_date_t * const date) {

    if (!main || !buffer.used || !date) {
      if (main) main->setting.state.status = F_data_not;

      return;
    }

    {
      f_string_static_t strings[] = {
        kt_remove_now_s,
        kt_remove_today_s,
        kt_remove_tomorrow_s,
        kt_remove_yesterday_s,
      };

      uint16_t enumerations[] = {
        kt_remove_flag_date_now_e,
        kt_remove_flag_date_today_e,
        kt_remove_flag_date_tomorrow_e,
        kt_remove_flag_date_yesterday_e,
      };

      for (uint8_t i = 0; i < 4; ++i) {

        if (f_compare_dynamic(buffer, strings[i]) == F_equal_to) {
          date->type = enumerations[i];

          kt_remove_convert_date_relative(main, date);

          if (F_status_is_error(main->setting.state.status)) {
            kt_remove_print_error(&main->program.error, macro_kt_remove_f(kt_remove_convert_date_relative));
          }

          return;
        }
      } // for
    }

    uint8_t matches = 0;
    f_string_range_t range_first = f_string_range_t_initialize;
    f_string_range_t range_second = f_string_range_t_initialize;

    {
      uint8_t width = 0;
      f_string_range_t range = macro_f_string_range_t_initialize2(buffer.used);
      f_array_length_t width_max = (range.stop - range.start) + 1;

      for (; range.start <= range.stop; range.start += width, width_max -= width) {

        if (kt_remove_signal_check(main)) return;

        // Skip past NULL characters.
        if (!buffer.string[range.start]) {
          width = 1;

          continue;
        }

        width = macro_f_utf_byte_width(buffer.string[range.start]);

        if (matches & kt_remove_flag_convert_match_second_e) {
          main->setting.state.status = f_utf_is_digit(buffer.string + range.start, width_max, 0);

          if (F_status_is_error(main->setting.state.status)) {
            kt_remove_print_error(&main->program.error, macro_kt_remove_f(f_utf_is_digit));

            return;
          }

          if (main->setting.state.status == F_true) {
            range_second.stop = range.start;

            continue;
          }

          // Not digit matches at this point are invalid.
          matches = 0;

          break;
        }

        if (matches & kt_remove_flag_convert_colon_e) {

          // Search until a colon or a digit is found.
          if (f_compare_dynamic_string(buffer.string + range.start, f_string_ascii_colon_s, width) == F_equal_to) {

            // A third colon is not valid.
            if (matches & kt_remove_flag_convert_colon_double_e) {
              matches = 0;

              break;
            }

            matches |= kt_remove_flag_convert_colon_double_e;

            continue;
          }

          main->setting.state.status = f_utf_is_digit(buffer.string + range.start, width_max, 0);

          if (F_status_is_error(main->setting.state.status)) {
            kt_remove_print_error(&main->program.error, macro_kt_remove_f(f_utf_is_digit));

            return;
          }

          if (main->setting.state.status == F_true) {
            matches |= kt_remove_flag_convert_match_second_e;
            range_second.start = range.start;
            range_second.stop = range.start;
          }

          continue;
        }

        if (matches & kt_remove_flag_convert_match_first_e) {

          if (f_compare_dynamic_string(buffer.string + range.start, f_string_ascii_colon_s, width) == F_equal_to) {
            matches |= kt_remove_flag_convert_colon_single_e;

            continue;
          }

          main->setting.state.status = f_utf_is_digit(buffer.string + range.start, width_max, 0);

          if (F_status_is_error(main->setting.state.status)) {
            kt_remove_print_error(&main->program.error, macro_kt_remove_f(f_utf_is_digit));

            return;
          }

          if (main->setting.state.status == F_true) {
            range_first.stop = range.start;
          }
          else {
            matches = 0;

            break;
          }

          continue;
        }

        main->setting.state.status = f_utf_is_whitespace(buffer.string + range.start, width_max, F_false);

        if (F_status_is_error(main->setting.state.status)) {
          kt_remove_print_error(&main->program.error, macro_kt_remove_f(f_utf_is_whitespace));

          return;
        }

        if (main->setting.state.status == F_true) continue;

        if (f_compare_dynamic_string(buffer.string + range.start, f_string_ascii_colon_s, width) == F_equal_to) {
          matches |= kt_remove_flag_convert_colon_single_e;

          continue;
        }

        main->setting.state.status = f_utf_is_digit(buffer.string + range.start, width_max, 0);

        if (F_status_is_error(main->setting.state.status)) {
          kt_remove_print_error(&main->program.error, macro_kt_remove_f(f_utf_is_digit));

          return;
        }

        if (main->setting.state.status == F_true) {
          matches |= kt_remove_flag_convert_match_first_e;
          range_first.start = range.start;
          range_first.stop = range.start;
        }
        else {
          matches = 0;

          break;
        }
      } // for

      main->setting.state.status = F_none;
    }

    // If the first and possibly the second digit matches.
    if (matches & kt_remove_flag_convert_match_e) {
      fl_conversion_data_t conversion_data = fl_conversion_data_base_10_c;

      date->start_year = 0;
      date->start_second = 0;
      date->start_nanosecond = 0;
      date->stop_second = 0;
      date->stop_nanosecond = 0;
      date->stop_year = 0;
      date->type = 0;

      // Process the first character.
      if (matches & kt_remove_flag_convert_match_first_e) {
        main->setting.state.status = fl_conversion_dynamic_partial_to_unsigned_detect(conversion_data, buffer, range_first, &date->start_year);

        if (F_status_is_error(main->setting.state.status)) {
          kt_remove_print_error(&main->program.error, macro_kt_remove_f(fl_conversion_dynamic_partial_to_unsigned_detect));

          return;
        }
      }
      else {
        if (matches & kt_remove_flag_convert_colon_double_e) {

          // The Unix Epoch is used for double colons when no year is specified.
          date->start_year = kt_remove_time_year_unix_epoch_d;
          date->type |= kt_remove_flag_date_time_epoch_e;
        }
        else {
          struct timespec now;
          int result = 0;

          memset(&now, 0, sizeof(struct timespec));

          // The current year is used for single colon when no year is specified.
          {
            result = clock_gettime(CLOCK_REALTIME, &now);

            if (!result) {
              if (result == EFAULT) {
                 main->setting.state.status = F_status_set_error(F_buffer);
              }
              else if (result == EINVAL) {
                main->setting.state.status = F_status_set_error(F_parameter);
              }
              else if (result == EPERM) {
                main->setting.state.status = F_status_set_error(F_prohibited);
              }
              else {
                main->setting.state.status = F_status_set_error(F_failure);
              }

              return;
            }
          }

          date->start_year = now.tv_sec / kt_remove_time_seconds_in_year_d;
          date->type |= kt_remove_flag_date_time_e;
        }
      }

      // Process the second character.
      if (matches & kt_remove_flag_convert_match_second_e) {
        main->setting.state.status = fl_conversion_dynamic_partial_to_unsigned_detect(conversion_data, buffer, range_second, &date->start_second);

        if (F_status_is_error(main->setting.state.status)) {
          kt_remove_print_error(&main->program.error, macro_kt_remove_f(fl_conversion_dynamic_partial_to_unsigned_detect));

          return;
        }

        if (matches & kt_remove_flag_convert_colon_double_e) {
          if (!(main->setting.flag & kt_remove_main_flag_utc_e)) {
            kt_remove_convert_timezone(main, &date->start_year, &date->start_second);

            if (F_status_is_error(main->setting.state.status)) {
              kt_remove_print_error(&main->program.error, macro_kt_remove_f(kt_remove_convert_timezone));

              return;
            }
          }
        }
        else {
          date->start_nanosecond = date->start_second % kt_remove_time_seconds_in_nanosecond_d;
          date->start_second = (date->start_second / kt_remove_time_seconds_in_nanosecond_d);

          if (!(main->setting.flag & kt_remove_main_flag_utc_e)) {
            kt_remove_convert_timezone(main, &date->start_year, &date->start_second);

            if (F_status_is_error(main->setting.state.status)) {
              kt_remove_print_error(&main->program.error, macro_kt_remove_f(kt_remove_convert_timezone));

              return;
            }
          }
        }
      }
      else {

        // A colon after the end without a digit following it is not valid (such as '1234:' or '1234::').
        if (matches & kt_remove_flag_convert_colon_e) {
          matches = 0;
        }
        else {

          // This is a UNIX timestamp by itself (has no colons).
          date->start_year = kt_remove_time_year_unix_epoch_d;
          date->type = kt_remove_flag_date_unix_e;

          main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(conversion_data, buffer, &date->start_second);

          if (F_status_is_error(main->setting.state.status)) {
            kt_remove_print_error(&main->program.error, macro_kt_remove_f(fl_conversion_dynamic_to_unsigned_detect));

            return;
          }

          kt_remove_convert_timezone(main, &date->start_year, &date->start_second);

          if (F_status_is_error(main->setting.state.status)) {
            kt_remove_print_error(&main->program.error, macro_kt_remove_f(kt_remove_convert_timezone));

            return;
          }
        }
      }
    }

    if (!matches) {
      const f_string_t formats[] = {
        kt_remove_date_format_00_s.string,
        kt_remove_date_format_01_s.string,
        kt_remove_date_format_02_s.string,
        kt_remove_date_format_03_s.string,
        kt_remove_date_format_04_s.string,
        kt_remove_date_format_05_s.string,
        kt_remove_date_format_06_s.string,
        kt_remove_date_format_07_s.string,
        kt_remove_date_format_08_s.string,
        kt_remove_date_format_09_s.string,
        kt_remove_date_format_10_s.string,
        kt_remove_date_format_11_s.string,
        kt_remove_date_format_12_s.string,
        kt_remove_date_format_13_s.string,
        kt_remove_date_format_14_s.string,
      };

      struct tm time;

      for (f_array_length_t i = 0; i < 15; ++i) {

        if (kt_remove_signal_check(main)) return;

        memset(&time, 0, sizeof(struct tm));

        if (strptime(buffer.string, formats[i], &time) != 0) {
          date->start_year = kt_remove_time_year_unix_epoch_d;
          date->start_nanosecond = 0;
          date->stop_second = 0;
          date->stop_nanosecond = 0;
          date->stop_year = 0;
          date->type = kt_remove_flag_date_string_e;

          date->start_second = time.tm_sec;
          date->start_second += time.tm_min * kt_remove_time_seconds_in_minute_d;
          date->start_second += time.tm_hour * kt_remove_time_seconds_in_hour_d;
          date->start_second += time.tm_yday * kt_remove_time_seconds_in_day_d;
          date->start_nanosecond = 0;

          // @todo investigate whether or not tm_isdst needs to be taken into consideration.
          matches = 1;

          break;
        }
      } // for
    }

    main->setting.state.status = matches ? F_none : F_status_set_error(F_known_not);
  }
#endif // _di_kt_remove_convert_date_

#ifndef _di_kt_remove_convert_date_relative_
  void kt_remove_convert_date_relative(kt_remove_main_t * const main, kt_remove_date_t * const date) {

    if (!main || !date) {
      if (main) main->setting.state.status = F_status_set_error(F_parameter);

      return;
    }

    struct timespec now;

    memset(&now, 0, sizeof(struct timespec));

    {
      const int result = clock_gettime(CLOCK_REALTIME, &now);

      if (result) {
        if (errno == EFAULT) {
           main->setting.state.status = F_status_set_error(F_buffer);
        }
        else if (errno == EINVAL) {
          main->setting.state.status = F_status_set_error(F_parameter);
        }
        else if (errno == EPERM) {
          main->setting.state.status = F_status_set_error(F_prohibited);
        }
        else {
          main->setting.state.status = F_status_set_error(F_failure);
        }

        return;
      }
    }

    date->start_year = kt_remove_time_year_unix_epoch_d;
    date->start_second = now.tv_sec;
    date->start_nanosecond = 0;
    date->stop_year = kt_remove_time_year_unix_epoch_d;
    date->stop_second = 0;
    date->stop_nanosecond = 0;

    if (date->type == kt_remove_flag_date_now_e) {
      date->start_nanosecond = now.tv_nsec;

      if (!(main->setting.flag & kt_remove_main_flag_utc_e)) {
        kt_remove_convert_timezone(main, &date->start_year, &date->start_second);
        if (F_status_is_error(main->setting.state.status)) return;
      }

      main->setting.state.status = F_none;

      return;
    }

    // Determine start of day.
    if (!(main->setting.flag & kt_remove_main_flag_utc_e)) {
      kt_remove_convert_timezone(main, &date->start_year, &date->start_second);
      if (F_status_is_error(main->setting.state.status)) return;
    }

    date->start_second -= date->start_second % kt_remove_time_seconds_in_day_d;

    if (date->type == kt_remove_flag_date_today_e) {
      date->stop_second = date->start_second + kt_remove_time_seconds_in_day_d; // @fixme, check to see if this would overflow and if so increment year.
    }
    else if (date->type == kt_remove_flag_date_tomorrow_e) {
      date->start_second += kt_remove_time_seconds_in_day_d;
      date->stop_second = date->start_second + kt_remove_time_seconds_in_day_d; // @fixme, check to see if this would overflow and if so increment year.
    }
    else if (date->type == kt_remove_flag_date_yesterday_e) {
      date->start_second -= kt_remove_time_seconds_in_day_d;
      date->stop_second = date->start_second;
    }

    main->setting.state.status = F_none;
  }
#endif // _di_kt_remove_convert_date_relative_

#ifndef _di_kt_remove_get_id_group_
  uint32_t kt_remove_get_id_group(kt_remove_main_t * const main, const f_string_static_t buffer) {

    if (!main) return 0;

    f_number_unsigned_t number = 0;

    main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, buffer, &number);

    if (F_status_is_error(main->setting.state.status)) {
      if (F_status_set_fine(main->setting.state.status) == F_number) {
        main->setting.buffer.used = 0;

        main->setting.state.status = f_rip_dynamic_nulless(buffer, &main->setting.buffer);
        if (F_status_is_error(main->setting.state.status)) return 0;

        gid_t gid = 0;

        main->setting.state.status = f_account_group_id_by_name(main->setting.buffer, &gid);
        if (F_status_is_error(main->setting.state.status)) return 0;

        if (main->setting.state.status == F_exist_not) {
          main->setting.state.status = F_status_set_error(F_exist_not);

          return 0;
        }

        main->setting.state.status = F_none;

        return (uint32_t) gid;
      }

      return 0;
    }

    if (number > F_type_size_32_unsigned_d) {
      main->setting.state.status = F_status_set_error(F_number_too_large);

      return 0;
    }

    main->setting.state.status = F_none;

    return (uint32_t) number;
  }
#endif // _di_kt_remove_get_id_group_

#ifndef _di_kt_remove_get_id_user_
  uint32_t kt_remove_get_id_user(kt_remove_main_t * const main, const f_string_static_t buffer) {

    if (!main) return 0;

    f_number_unsigned_t number = 0;

    main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, buffer, &number);

    if (F_status_is_error(main->setting.state.status)) {
      if (F_status_set_fine(main->setting.state.status) == F_number) {
        main->setting.buffer.used = 0;

        main->setting.state.status = f_rip_dynamic_nulless(buffer, &main->setting.buffer);
        if (F_status_is_error(main->setting.state.status)) return 0;

        uid_t uid = 0;

        main->setting.state.status = f_account_id_by_name(main->setting.buffer, &uid);
        if (F_status_is_error(main->setting.state.status)) return 0;

        if (main->setting.state.status == F_exist_not) {
          main->setting.state.status = F_status_set_error(F_exist_not);

          return 0;
        }

        main->setting.state.status = F_none;

        return (uint32_t) uid;
      }

      return 0;
    }

    if (number > F_type_size_32_unsigned_d) {
      main->setting.state.status = F_status_set_error(F_number_too_large);

      return 0;
    }

    main->setting.state.status = F_none;

    return (uint32_t) number;
  }
#endif // _di_kt_remove_get_id_user_

#ifndef _di_kt_remove_get_mode_
  mode_t kt_remove_get_mode(kt_remove_main_t * const main, const f_string_static_t buffer) {

    if (!main) return 0;

    f_file_mode_t mode_file = f_file_mode_t_initialize;
    uint8_t mode_replace = 0;

    main->setting.state.status = f_file_mode_from_string(buffer, main->program.umask, &mode_file, &mode_replace);

    if (F_status_is_error(main->setting.state.status)) {
      kt_remove_print_error(&main->program.error, macro_kt_remove_f(f_file_mode_from_string));

      return 0;
    }

    mode_t mode = 0;

    main->setting.state.status = f_file_mode_to_mode(mode_file, &mode);

    if (F_status_is_error(main->setting.state.status)) {
      kt_remove_print_error(&main->program.error, macro_kt_remove_f(f_file_mode_to_mode));

      return 0;
    }

    main->setting.state.status = F_none;

    return mode;
  }
#endif // _di_kt_remove_get_mode_

#ifndef _di_kt_remove_convert_timezone_
  void kt_remove_convert_timezone(kt_remove_main_t * const main, f_number_unsigned_t * const year, f_number_unsigned_t * const seconds) {

    if (!main || !year || !seconds) {
      if (main) main->setting.state.status = F_status_set_error(F_parameter);

      return;
    }

    if (timezone < 0) {
      if (*seconds > kt_remove_time_seconds_in_year_d + timezone) {
        if (*year < F_number_t_size_max_unsigned_d) {
          ++(*year);
          *seconds -= kt_remove_time_seconds_in_year_d + timezone;
        }
        else {
          main->setting.state.status = F_status_set_error(F_number_overflow);

          return;
        }
      }
      else {
        *seconds -= timezone;
      }
    }
    else {
      if (*seconds < timezone) {
        if (*year) {
          --(*year);
          *seconds = kt_remove_time_seconds_in_year_d - (timezone - *seconds);
        }
        else {
          main->setting.state.status = F_status_set_error(F_number_underflow);

          return;
        }
      }
      else {
        *seconds -= timezone;
      }
    }

    main->setting.state.status = F_none;
  }
#endif // _di_kt_remove_convert_timezone_

#ifdef __cplusplus
} // extern "C"
#endif
