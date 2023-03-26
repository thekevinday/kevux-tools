#include "../remove.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_remove_print_simulate_operate_
  void kt_remove_print_simulate_operate(fl_print_t * const print) {

    if (!print || !print->custom) return;

    kt_remove_main_t * const main = (kt_remove_main_t *) print->custom;

    if (!(main->setting.flag & kt_remove_main_flag_simulate_e)) return;

    f_file_stream_lock(print->to);

    fl_print_format("%[Files to Remove%]:%r", print->to, print->set->title, print->set->title, f_string_eol_s);

    for (f_array_length_t i = 0; i < main->setting.files.used; ++i) {
      fl_print_format("  %Q%r", print->to, main->setting.files.array[i], f_string_eol_s);
    } // for

    f_print_dynamic(f_string_eol_s, print->to);

    f_file_stream_unlock(main->program.output.to);
  }
#endif // _di_kt_remove_print_simulate_operate_

#ifndef _di_kt_remove_print_simulate_operate_file_
  void kt_remove_print_simulate_operate_file(fl_print_t * const print, const f_string_static_t path) {

    if (!print || !print->custom) return;

    kt_remove_main_t * const main = (kt_remove_main_t *) print->custom;

    if (!(main->setting.flag & kt_remove_main_flag_simulate_e)) return;

    fll_print_format("%[Remove '%Q'%]:%r", main->program.output.to, main->program.output.set->notable, path, main->program.output.set->notable, f_string_eol_s);
  }
#endif // _di_kt_remove_print_simulate_operate_file_

#ifndef _di_kt_remove_print_simulate_operate_file_exists_
  void kt_remove_print_simulate_operate_file_exists(fl_print_t * const print, const f_string_static_t path) {

    if (!print || !print->custom) return;

    kt_remove_main_t * const main = (kt_remove_main_t *) print->custom;

    if (!(main->setting.flag & kt_remove_main_flag_simulate_e)) return;

    if (F_status_is_error(main->setting.state.status)) {
      fl_print_format("  file_access_failure %ui%r", main->program.output.to, F_status_set_fine(main->setting.state.status), f_string_eol_s);

      return;
    }

    f_status_t status = f_file_is(path, F_file_type_link_d, F_false);


    if (F_status_is_error(status) && F_status_set_fine(status) != F_file_found_not) {
      fl_print_format("  file_read_failure %ui%r", main->program.output.to, F_status_set_fine(status), f_string_eol_s);

      return;
    }

    if (status == F_true) {
      main->setting.buffer.used = 0;

      status = f_file_link_read(path, F_false, &main->setting.buffer);

      if (F_status_is_error(status)) {
        fl_print_format("  link_read_failure %ui%r", main->program.output.to, F_status_set_fine(status), f_string_eol_s);

        return;
      }

      f_file_stream_lock(main->program.output.to);

      fl_print_format("  follow %r%r", main->program.output.to, (main->setting.flag & kt_remove_main_flag_follow_e) ? kt_remove_yes_s : kt_remove_no_s, f_string_eol_s);
      fl_print_format("  to '%Q'%r", main->program.output.to, main->setting.buffer, f_string_eol_s);

      f_file_stream_unlock(main->program.output.to);
    }

    fll_print_format("  exists %r%r", main->program.output.to, main->setting.state.status == F_true ? kt_remove_yes_s : kt_remove_no_s, f_string_eol_s);
  }
#endif // _di_kt_remove_print_simulate_operate_file_exists_

#ifndef _di_kt_remove_print_simulate_operate_file_stat_
  void kt_remove_print_simulate_operate_file_stat(fl_print_t * const print, struct stat statistics) {

    if (!print || !print->custom) return;

    kt_remove_main_t * const main = (kt_remove_main_t *) print->custom;

    if (!(main->setting.flag & kt_remove_main_flag_simulate_e)) return;

    if (main->setting.flag & kt_remove_main_flag_block_e) {
      fll_print_format("  block %r%r", main->program.output.to, (macro_f_file_type_get(statistics.st_mode) == F_file_type_block_d) ? kt_remove_yes_s : kt_remove_no_s, f_string_eol_s);
    }

    if (main->setting.flag & kt_remove_main_flag_character_e) {
      fll_print_format("  character %r%r", main->program.output.to, (macro_f_file_type_get(statistics.st_mode) == F_file_type_character_d) ? kt_remove_yes_s : kt_remove_no_s, f_string_eol_s);
    }

    if (main->setting.flag & kt_remove_main_flag_directory_e) {
      fll_print_format("  directory %r%r", main->program.output.to, (macro_f_file_type_get(statistics.st_mode) == F_file_type_directory_d) ? kt_remove_yes_s : kt_remove_no_s, f_string_eol_s);
    }

    if (main->setting.flag & kt_remove_main_flag_fifo_e) {
      fll_print_format("  fifo %r%r", main->program.output.to, (macro_f_file_type_get(statistics.st_mode) == F_file_type_fifo_d) ? kt_remove_yes_s : kt_remove_no_s, f_string_eol_s);
    }

    if (main->setting.flag & kt_remove_main_flag_link_e) {
      fll_print_format("  link %r%r", main->program.output.to, (macro_f_file_type_get(statistics.st_mode) == F_file_type_link_d) ? kt_remove_yes_s : kt_remove_no_s, f_string_eol_s);
    }

    if (main->setting.flag & kt_remove_main_flag_regular_e) {
      fll_print_format("  regular %r%r", main->program.output.to, (macro_f_file_type_get(statistics.st_mode) == F_file_type_regular_d) ? kt_remove_yes_s : kt_remove_no_s, f_string_eol_s);
    }

    if (main->setting.flag & kt_remove_main_flag_socket_e) {
      fll_print_format("  socket %r%r", main->program.output.to, (macro_f_file_type_get(statistics.st_mode) == F_file_type_socket_d) ? kt_remove_yes_s : kt_remove_no_s, f_string_eol_s);
    }

    f_array_length_t i = 0;

    if (main->setting.flag & kt_remove_main_flag_user_e) {
      for (; i < main->setting.users.used; ++i) {
        if (statistics.st_uid == (uid_t) main->setting.users.array[i]) break;
      } // for

      if (i == main->setting.users.used) {
        fll_print_format("  user%r", main->program.output.to, f_string_eol_s);
      }
      else {
        fll_print_format("  user %un%r", main->program.output.to, (f_number_unsigned_t) statistics.st_uid, f_string_eol_s);
      }
    }

    if (main->setting.flag & kt_remove_main_flag_same_e) {
      fll_print_format("  same %r%r", main->program.output.to, (statistics.st_uid == geteuid()) ? kt_remove_yes_s : kt_remove_no_s, f_string_eol_s);
    }

    if (main->setting.flag & kt_remove_main_flag_different_e) {
      fll_print_format("  different %r%r", main->program.output.to, (statistics.st_uid == geteuid()) ? kt_remove_no_s : kt_remove_yes_s, f_string_eol_s);
    }

    if (main->setting.flag & kt_remove_main_flag_group_e) {
      for (i = 0; i < main->setting.groups.used; ++i) {
        if (statistics.st_gid == (gid_t) main->setting.groups.array[i]) break;
      } // for

      if (i == main->setting.groups.used) {
        fll_print_format("  group%r", main->program.output.to, f_string_eol_s);
      }
      else {
        fll_print_format("  group %un%r", main->program.output.to, (f_number_unsigned_t) statistics.st_gid, f_string_eol_s);
      }
    }

    if (main->setting.flag & kt_remove_main_flag_mode_e) {
      const mode_t mode = statistics.st_mode & F_file_mode_all_d;

      fll_print_format("  mode %@03un%r", main->program.output.to, (f_number_unsigned_t) mode, f_string_eol_s);

      for (i = 0; i < main->setting.modes.used; ++i) {

        if (main->setting.modes.array[i].type == kt_remove_flag_mode_different_e) {
          if (main->setting.modes.array[i].mode & ~mode) break;
        }
        else if (main->setting.modes.array[i].type == kt_remove_flag_mode_same_e) {
          if (main->setting.modes.array[i].mode == mode) break;
        }
        else if (main->setting.modes.array[i].type == kt_remove_flag_mode_similar_e) {
          if (main->setting.modes.array[i].mode & mode) break;
        }
        else if (main->setting.modes.array[i].type == kt_remove_flag_mode_not_e) {
          if (main->setting.modes.array[i].mode != mode) break;
        }
      } // for

      if (i < main->setting.modes.used) {
        uint8_t types[] = {
          kt_remove_flag_mode_different_e,
          kt_remove_flag_mode_same_e,
          kt_remove_flag_mode_similar_e,
          kt_remove_flag_mode_not_e,
        };

        f_string_static_t strings[] = {
          kt_remove_mode_word_different_s,
          kt_remove_mode_word_same_s,
          kt_remove_mode_word_similar_s,
          kt_remove_mode_word_not_s,
        };

        for (uint8_t j = 0; j < 4; ++j) {

          if (main->setting.modes.array[i].type == types[j]) {
            fll_print_format("  mode_matched %Q %@03un%r", main->program.output.to, strings[j], (f_number_unsigned_t) main->setting.modes.array[i].mode, f_string_eol_s);

            break;
          }
        } // for
      }
    }

    {
      kt_remove_dates_t * const dates[] = {
        &main->setting.accessed,
        &main->setting.created,
        &main->setting.updated,
      };

      struct timespec times[] = {
        statistics.st_atim,
        statistics.st_ctim,
        statistics.st_mtim,
      };

      const f_string_static_t * const names[] = {
        &kt_remove_long_accessed_s,
        &kt_remove_long_created_s,
        &kt_remove_long_updated_s,
      };

      uint8_t p = 0;
      f_status_t result = F_none;
      f_string_static_t name_type = f_string_empty_s;
      f_number_unsigned_t match_year = 0;
      f_number_unsigned_t match_second = 0;
      f_number_unsigned_t start_year = 0;
      f_number_unsigned_t start_second = 0;
      f_number_unsigned_t stop_year = 0;
      f_number_unsigned_t stop_second = 0;

      for (; p < 3; ++p) {

        for (i = 0; i < dates[p]->used; ++i) {

          if (kt_remove_signal_check(main)) return;

          match_year = kt_remove_time_year_unix_epoch_d + (times[p].tv_sec / kt_remove_time_seconds_in_year_d);
          match_second = times[p].tv_sec % kt_remove_time_seconds_in_year_d;

          start_year = dates[p]->array[i].start_year + (dates[p]->array[i].start_second / kt_remove_time_seconds_in_year_d);
          start_second = dates[p]->array[i].start_second % kt_remove_time_seconds_in_year_d;

          name_type = f_string_empty_s;
          result = F_none;

          if (dates[p]->array[i].type == kt_remove_flag_date_today_e || dates[p]->array[i].type == kt_remove_flag_date_tomorrow_e || dates[p]->array[i].type == kt_remove_flag_date_yesterday_e) {
            stop_year = dates[p]->array[i].stop_year + (dates[p]->array[i].stop_second / kt_remove_time_seconds_in_year_d);
            stop_second = dates[p]->array[i].stop_second % kt_remove_time_seconds_in_year_d;

            if (dates[p]->array[i].operation == kt_remove_flag_date_equal_e) {
              name_type = kt_remove_date_symbol_equal_s;
              result = F_false;

              if (match_year == start_year) {
                if (match_second > start_second && match_second < stop_second) {
                  result = F_true;
                }
                else if (match_second == start_second && times[p].tv_nsec >= dates[p]->array[i].start_nanosecond && times[p].tv_nsec < dates[p]->array[i].stop_nanosecond) {
                  result = F_true;
                }
              }
            }
            else if (dates[p]->array[i].operation == kt_remove_flag_date_less_e) {
              name_type = kt_remove_date_symbol_less_s;
              result = F_false;

              if (match_year < start_year) {
                result = F_true;
              }
              else if (match_year == start_year) {
                if (match_second < start_second) {
                  result = F_true;
                }
                else if (match_second == start_second && times[p].tv_nsec < dates[p]->array[i].start_nanosecond) {
                  result = F_true;
                }
              }
            }
            else if (dates[p]->array[i].operation == kt_remove_flag_date_less_equal_e) {
              name_type = kt_remove_date_symbol_less_equal_s;
              result = F_false;

              if (match_year < start_year) {
                result = F_true;
              }
              else if (match_year == start_year) {
                if (match_second < stop_second) {
                  result = F_true;
                }
                else if (match_second == stop_second && times[p].tv_nsec < dates[p]->array[i].stop_nanosecond) {
                  result = F_true;
                }
              }
            }
            else if (dates[p]->array[i].operation == kt_remove_flag_date_more_e) {
              name_type = kt_remove_date_symbol_more_s;
              result = F_false;

              if (match_year > start_year) {
                result = F_true;
              }
              else if (match_year == start_year) {
                if (match_second > stop_second) {
                  result = F_true;
                }
                else if (match_second == stop_second && times[p].tv_nsec >= dates[p]->array[i].stop_nanosecond) {
                  result = F_true;
                }
              }
            }
            else if (dates[p]->array[i].operation == kt_remove_flag_date_more_equal_e) {
              name_type = kt_remove_date_symbol_more_equal_s;
              result = F_false;

              if (match_year > start_year) {
                result = F_true;
              }
              else if (match_year == start_year) {
                if (match_second > start_second) {
                  result = F_true;
                }
                else if (match_second == start_second && times[p].tv_nsec >= dates[p]->array[i].start_nanosecond) {
                  result = F_true;
                }
              }
            }
            else if (dates[p]->array[i].operation == kt_remove_flag_date_not_e) {
              name_type = kt_remove_date_symbol_not_s;
              result = F_true;

              if (match_year == start_year) {
                if (match_second > start_second && match_second < stop_second) {
                  result = F_false;
                }
                else if (match_second == start_second && times[p].tv_nsec >= dates[p]->array[i].start_nanosecond && times[p].tv_nsec < dates[p]->array[i].stop_nanosecond) {
                  result = F_false;
                }
              }
            }
          }
          else if (dates[p]->array[i].operation == kt_remove_flag_date_equal_e) {
            name_type = kt_remove_date_symbol_equal_s;

            if (match_year == start_year && match_second == start_second && times[p].tv_nsec == dates[p]->array[i].start_nanosecond) {
              result = F_true;
            }
            else {
              result = F_false;
            }
          }
          else if (dates[p]->array[i].operation == kt_remove_flag_date_less_e) {
            name_type = kt_remove_date_symbol_less_s;
            result = F_false;

            if (match_year < start_year) {
              result = F_true;
            }
            else if (match_year == start_year) {
              if (match_second < start_second) {
                result = F_true;
              }
              else if (match_second == start_second && times[p].tv_nsec < dates[p]->array[i].start_nanosecond) {
                result = F_true;
              }
            }
          }
          else if (dates[p]->array[i].operation == kt_remove_flag_date_less_equal_e) {
            name_type = kt_remove_date_symbol_less_equal_s;
            result = F_false;

            if (match_year < start_year) {
              result = F_true;
            }
            else if (match_year == start_year) {
              if (match_second < start_second) {
                result = F_true;
              }
              else if (match_second == start_second && times[p].tv_nsec <= dates[p]->array[i].start_nanosecond) {
                result = F_true;
              }
            }
          }
          else if (dates[p]->array[i].operation == kt_remove_flag_date_more_e) {
            name_type = kt_remove_date_symbol_more_s;
            result = F_false;

            if (match_year > start_year) {
              result = F_true;
            }
            else if (match_year == start_year) {
              if (match_second > start_second) {
                result = F_true;
              }
              else if (match_second == start_second && times[p].tv_nsec > dates[p]->array[i].start_nanosecond) {
                result = F_true;
              }
            }
          }
          else if (dates[p]->array[i].operation == kt_remove_flag_date_more_equal_e) {
            name_type = kt_remove_date_symbol_more_equal_s;
            result = F_false;

            if (match_year > start_year) {
              result = F_true;
            }
            else if (match_year == start_year) {
              if (match_second > start_second) {
                result = F_true;
              }
              else if (match_second == start_second && times[p].tv_nsec >= dates[p]->array[i].start_nanosecond) {
                result = F_true;
              }
            }
          }
          else if (dates[p]->array[i].operation == kt_remove_flag_date_not_e) {
            name_type = kt_remove_date_symbol_not_s;

            if (match_year != start_year || match_second != start_second || times[p].tv_nsec != dates[p]->array[i].start_nanosecond) {
              result = F_true;
            }
            else {
              result = F_false;
            }
          }

          if (name_type.used) {
            fll_print_format("  %Q %Q ", main->program.output.to, *names[p], result ? kt_remove_yes_s : kt_remove_no_s);
            fll_print_format("%u::%un 0:%un %Q ", main->program.output.to, match_year, (f_number_unsigned_t) times[p].tv_sec, (f_number_unsigned_t) times[p].tv_nsec, name_type);
            fll_print_format("%u::%un 0:%un%r", main->program.output.to, dates[p]->array[i].start_year, dates[p]->array[i].start_second, dates[p]->array[i].start_nanosecond, f_string_eol_s);

            break;
          }
        } // for
      } // for
    }
  }
#endif // _di_kt_remove_print_simulate_operate_file_stat_

#ifndef _di_kt_remove_print_simulate_operate_boolean_
  void kt_remove_print_simulate_operate_boolean(fl_print_t * const print, const f_string_static_t name, const bool yes) {

    if (!print || !print->custom) return;

    kt_remove_main_t * const main = (kt_remove_main_t *) print->custom;

    if (!(main->setting.flag & kt_remove_main_flag_simulate_e)) return;

    fll_print_format("  %r %r%r", main->program.output.to, name, yes ? kt_remove_yes_s : kt_remove_no_s, f_string_eol_s);
  }
#endif // _di_kt_remove_print_simulate_operate_boolean_

#ifdef __cplusplus
} // extern "C"
#endif
