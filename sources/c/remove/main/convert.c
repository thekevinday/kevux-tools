#include "remove.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_remove_get_date_
  struct timespec kt_remove_get_date(fll_program_data_t * const main, kt_remove_setting_t * const setting, const f_string_static_t buffer, uint8_t * const type) {

    if (!setting || !buffer.used) {
      struct timespec result;

      memset(&result, 0, sizeof(struct timespec));

      if (setting) setting->status = F_data_not;

      return result;
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

        if (fl_string_dynamic_compare(buffer, strings[i]) == F_equal_to) {
          setting->status = F_none;

          if (type) {
            *type = enumerations[i];
          }

          return kt_remove_get_date_relative(setting, enumerations[i]);
        }
      } // for
    }

    // 0x1 = single colon, 0x2 = double colon, 0x4 = matched first, 0x8 = matched second, 0x10 = matched negative on first, 0x20 = matched negative on second, 0x40 = matched positive on first, 0x80 = matched positive on second.
    uint8_t matches = 0;
    uint64_t digit_first = 0;
    uint64_t digit_second = 0;
    f_string_range_t range_first = f_string_range_t_initialize;
    f_string_range_t range_second = f_string_range_t_initialize;

    struct timespec result;

    memset(&result, 0, sizeof(struct timespec));

    {
      uint8_t width = 0;
      f_string_range_t range = macro_f_string_range_t_initialize2(buffer.used);
      f_array_length_t width_max = (range.stop - range.start) + 1;

      for (; range.start <= range.stop; range.start += width, width_max -= width) {

        // Skip past NULL characters.
        if (!buffer.string[range.start]) {
          width = 1;

          continue;
        }

        width = macro_f_utf_byte_width_is(buffer.string[range.start]);

        if (matches & 0x8) {
          setting->status = f_utf_is_digit(buffer.string + range.start, width_max, 0);

          if (F_status_is_error(setting->status)) {
            kt_remove_print_error(setting, main->error, macro_kt_remove_f(f_utf_is_digit));

            return result;
          }

          if (setting->status == F_true) {
            range_second.stop = range.start;

            continue;
          }

          // Not digit matches at this point are invalid.
          matches = 0;

          break;
        }

        // @todo review this, this is 0x1, 0x2, and 0x20 (why match second negative?).
        if (matches & 0x23) {

          // Search until a colon, a digit, or a minus is found.
          if (fl_string_dynamic_compare_string(buffer.string + range.start, f_string_ascii_colon_s, width) == F_equal_to) {

            // A third colon is not valid.
            if (matches & 0x2) {
              matches = 0;

              break;
            }

            matches |= 0x2;

            continue;
          }

          if (fl_string_dynamic_compare_string(buffer.string + range.start, f_string_ascii_minus_s, width) == F_equal_to) {

            // An out of place minus sign is not valid.
            if (matches & 0x20) {
              matches = 0;

              break;
            }

            matches |= 0x20;

            continue;
          }

          setting->status = f_utf_is_digit(buffer.string + range.start, width_max, 0);

          if (F_status_is_error(setting->status)) {
            kt_remove_print_error(setting, main->error, macro_kt_remove_f(f_utf_is_digit));

            return result;
          }

          if (setting->status == F_true) {
            matches |= 0x8;
            range_second.start = range.start;
          }
        }
        else if (matches & 0x4) {

          // Only a colon is expected.
          if (fl_string_dynamic_compare_string(buffer.string + range.start, f_string_ascii_colon_s, width) == F_equal_to) {
            matches |= 0x1;
          }
          else {
            matches = 0;

            break;
          }
        }
        else {
          setting->status = f_utf_is_whitespace(buffer.string + range.start, width_max, F_false);

          if (F_status_is_error(setting->status)) {
            kt_remove_print_error(setting, main->error, macro_kt_remove_f(f_utf_is_whitespace));

            return result;
          }

          if (setting->status == F_true) continue;

          if (fl_string_dynamic_compare_string(buffer.string + range.start, f_string_ascii_colon_s, width) == F_equal_to) {
            matches |= 0x1;

            continue;
          }

          if (fl_string_dynamic_compare_string(buffer.string + range.start, f_string_ascii_minus_s, width) == F_equal_to) {

            // An out of place minus sign is not valid.
            if (matches & 0x50) {
              matches = 0;

              break;
            }

            matches |= 0x10;

            continue;
          }

          setting->status = f_utf_is_digit(buffer.string + range.start, width_max, 0);

          if (F_status_is_error(setting->status)) {
            kt_remove_print_error(setting, main->error, macro_kt_remove_f(f_utf_is_digit));

            return result;
          }

          if (setting->status == F_true) {
            if (matches & 0x4) {
              range_first.stop = range.start;
            }
            else {
              matches |= 0x4;
              range_first.start = range.start;

              // A digit is found before a leading minus, so assume this is a positive number.
              if (!(matches & 0x10)) {
                matches |= 0x40;
              }
            }
          }
          else if (!(matches & 0x50) && fl_string_dynamic_compare_string(buffer.string + range.start, f_string_ascii_minus_s, width) == F_equal_to) {
            matches |= 0x10;
          }
          else {
            matches = 0;

            break;
          }
        }
      } // for

      setting->status = F_none;
    }

    // If the first and possibly the second digit matches.
    if (matches & 0xc) {
      fl_conversion_data_t conversion_data = fl_conversion_data_base_10_c;

      // Process the first character.
      if (matches & 0x4) {
        if (matches & 0x10) {
          conversion_data.flag |= FL_conversion_data_flag_negative_d;
        }

        setting->status = fl_conversion_dynamic_partial_to_unsigned_detect(conversion_data, buffer, range_first, &digit_first);

        if (F_status_is_error(setting->status)) {
          kt_remove_print_error(setting, main->error, macro_kt_remove_f(fl_conversion_dynamic_partial_to_unsigned_detect));

          return result;
        }

        // Remove the negative bit for next use.
        conversion_data.flag -= conversion_data.flag & FL_conversion_data_flag_negative_d;
      }
      else {
        if (matches & 0x2) {

          // The Unix Epoch is used for double colons when no year is specified.
          digit_first = kt_remove_time_year_unix_epoch_d;

          if (type) {
            *type = kt_remove_flag_date_time_epoch_e;
          }
        }
        else {

          // The current year is used for single colon when no year is specified.
          digit_first = (time(0) / kt_remove_time_seconds_in_year_d) + kt_remove_time_year_unix_epoch_d;

          if (type) {
            *type = kt_remove_flag_date_time_e;
          }
        }
      }

      // Process the second character.
      if (matches & 0x8) {
        if (matches & 0x20) {
          conversion_data.flag |= FL_conversion_data_flag_negative_d;
        }

        setting->status = fl_conversion_dynamic_partial_to_unsigned_detect(conversion_data, buffer, range_second, &digit_second);

        if (F_status_is_error(setting->status)) {
          kt_remove_print_error(setting, main->error, macro_kt_remove_f(fl_conversion_dynamic_partial_to_unsigned_detect));

          return result;
        }

        if (matches & 0x2) {
          result.tv_sec = setting->flag & kt_remove_flag_utc_e ? digit_second : digit_second - timezone;

          // This is a double colon, so it is in UnixTime format.
          if (digit_first > kt_remove_time_year_unix_epoch_d) {
            result.tv_sec += (digit_first - kt_remove_time_year_unix_epoch_d) * kt_remove_time_seconds_in_year_d;
          }
          else if (digit_first < kt_remove_time_year_unix_epoch_d) {
            result.tv_sec -= (kt_remove_time_year_unix_epoch_d - digit_first) * kt_remove_time_seconds_in_year_d;
          }
        }
        else {
          result.tv_sec = (digit_second / kt_remove_time_seconds_in_nanosecond_d);
          result.tv_nsec = digit_second % kt_remove_time_seconds_in_nanosecond_d;

          if (setting->flag & kt_remove_flag_utc_e) {
            result.tv_sec -= timezone;
          }

          const uint64_t year_current = (time(0) / kt_remove_time_seconds_in_year_d) + kt_remove_time_year_unix_epoch_d;

          // This is a single colon, so it is in Time format.
          if (digit_first > kt_remove_time_year_unix_epoch_d) {
            result.tv_sec += (digit_first - kt_remove_time_year_unix_epoch_d) * kt_remove_time_seconds_in_year_d;
          }
          else if (digit_first < kt_remove_time_year_unix_epoch_d) {
            result.tv_sec -= (kt_remove_time_year_unix_epoch_d - digit_first) * kt_remove_time_seconds_in_year_d;
          }
        }
      }
      else {

        // A colon after the end without a digit following it is not valid (such as '1234:' or '1234::').
        if (matches & 0x3) {
          matches = 0;
        }
        else {

          // This is a UNIX timestamp by itself (has no colons).
          result.tv_sec = setting->flag & kt_remove_flag_utc_e ? digit_first : digit_first - timezone;
        }
      }
    }
    else {
      // @todo check to see if this is just a digit, and if so then it is UNIX Epoch time (kt_remove_flag_date_unix_e).
    }

    if (!matches) {
      // @todo attempt to process using the string date time conversion libc functions or return an error.
      // @todo formats:
      // - YYYY/MM/DD hh:ii:ss a +0000
      // - YYYY/MM/DD HH:ii:ss +0000
      // - YYYY/MM/DD hh:ii a +0000
      // - YYYY/MM/DD HH:ii +0000
      // - YYYY/MM/DD hh a +0000
      // - YYYY/MM/DD HH +0000
      // - YYYY/MM/DD hh:ii:ss a
      // - YYYY/MM/DD HH:ii:ss
      // - YYYY/MM/DD hh:ii a
      // - YYYY/MM/DD HH:ii
      // - YYYY/MM/DD hh a
      // - YYYY/MM/DD HH
      // - YYYY/MM/DD
      // - YYYY/MM
      // - YYYY/
      // (Note how the year by itselfs still has a trailing '/'. this is done to ensure it is not confused with the Unix timestamp.

      //if (type) {
      //  *type = kt_remove_flag_date_string_e;
      //}
    }

    setting->status = matches ? F_none : F_status_set_error(F_known_not);

    return result;
  }
#endif // _di_kt_remove_get_date_

#ifndef _di_kt_remove_get_date_relative_
  struct timespec kt_remove_get_date_relative(kt_remove_setting_t * const setting, const uint8_t type) {

    struct timespec result;

    memset(&result, 0, sizeof(struct timespec));

    if (!setting) return result;

    const time_t since_epoch = time(0);

    if (type == kt_remove_flag_date_now_e) {
      result.tv_sec = since_epoch;

      if (setting->flag & kt_remove_flag_utc_e) {
        result.tv_sec -= timezone;
      }

      return result;
    }

    // Determine start of day.
    const time_t today = since_epoch - ((setting->flag & kt_remove_flag_utc_e ? since_epoch : since_epoch - timezone) % kt_remove_time_seconds_in_day_d);

    if (type == kt_remove_flag_date_today_e) {
      result.tv_sec = today;
    }
    else if (type == kt_remove_flag_date_tomorrow_e) {
      result.tv_sec = today + kt_remove_time_seconds_in_day_d;
    }
    else {
      result.tv_sec = today - kt_remove_time_seconds_in_day_d;
    }

    return result;
  }
#endif // _di_kt_remove_get_date_relative_

#ifndef _di_kt_remove_get_id_group_
  uint32_t kt_remove_get_id_group(kt_remove_setting_t * const setting, const f_string_static_t buffer) {

    if (!setting) return 0;

    f_number_unsigned_t number = 0;

    setting->status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, buffer, &number);

    if (F_status_is_error(setting->status)) {
      if (F_status_set_fine(setting->status) == F_number) {
        setting->buffer.used = 0;

        setting->status = fl_string_dynamic_rip_nulless(buffer, &setting->buffer);
        if (F_status_is_error(setting->status)) return 0;

        gid_t gid = 0;

        setting->status = f_account_group_id_by_name(setting->buffer, &gid);
        if (F_status_is_error(setting->status)) return 0;

        if (setting->status == F_exist_not) {
          setting->status = F_status_set_error(F_exist_not);

          return 0;
        }

        setting->status = F_none;

        return (uint32_t) gid;
      }

      return 0;
    }

    if (number > F_type_size_32_unsigned_d) {
      setting->status = F_status_set_error(F_number_too_large);

      return 0;
    }

    setting->status = F_none;

    return (uint32_t) number;
  }
#endif // _di_kt_remove_get_id_group_

#ifndef _di_kt_remove_get_id_user_
  uint32_t kt_remove_get_id_user(kt_remove_setting_t * const setting, const f_string_static_t buffer) {

    if (!setting) return 0;

    f_number_unsigned_t number = 0;

    setting->status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, buffer, &number);

    if (F_status_is_error(setting->status)) {
      if (F_status_set_fine(setting->status) == F_number) {
        setting->buffer.used = 0;

        setting->status = fl_string_dynamic_rip_nulless(buffer, &setting->buffer);
        if (F_status_is_error(setting->status)) return 0;

        uid_t uid = 0;

        setting->status = f_account_id_by_name(setting->buffer, &uid);
        if (F_status_is_error(setting->status)) return 0;

        if (setting->status == F_exist_not) {
          setting->status = F_status_set_error(F_exist_not);

          return 0;
        }

        setting->status = F_none;

        return (uint32_t) uid;
      }

      return 0;
    }

    if (number > F_type_size_32_unsigned_d) {
      setting->status = F_status_set_error(F_number_too_large);

      return 0;
    }

    setting->status = F_none;

    return (uint32_t) number;
  }
#endif // _di_kt_remove_get_id_user_

#ifndef _di_kt_remove_get_mode_
  mode_t kt_remove_get_mode(fll_program_data_t * const main, kt_remove_setting_t * const setting, const f_string_static_t buffer) {

    if (!setting) return 0;

    f_file_mode_t mode_file = f_file_mode_t_initialize;
    uint8_t mode_replace = 0;

    setting->status = f_file_mode_from_string(buffer, main->umask, &mode_file, &mode_replace);

    if (F_status_is_error(setting->status)) {
      kt_remove_print_error(setting, main->error, macro_kt_remove_f(f_file_mode_from_string));

      return 0;
    }

    mode_t mode = 0;

    setting->status = f_file_mode_to_mode(mode_file, &mode);

    if (F_status_is_error(setting->status)) {
      kt_remove_print_error(setting, main->error, macro_kt_remove_f(f_file_mode_to_mode));

      return 0;
    }

    setting->status = F_none;

    return mode;
  }
#endif // _di_kt_remove_get_mode_

#ifdef __cplusplus
} // extern "C"
#endif
