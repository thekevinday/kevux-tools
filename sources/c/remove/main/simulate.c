#include "remove.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_remove_simulate_operate_
  void kt_remove_simulate_operate(fll_program_data_t * const main, kt_remove_setting_t * const setting) {

    if (!main || !setting) return;
    if (!(setting->flag & kt_remove_flag_simulate_e)) return;

    flockfile(main->output.to.stream);

    fl_print_format("%r%[Files to Remove%]:%r", main->output.to.stream, f_string_eol_s, main->output.set->title, main->output.set->title, f_string_eol_s);

    for (f_array_length_t i = 0; i < setting->files.used; ++i) {
      fl_print_format("  %Q%r", main->output.to.stream, setting->files.array[i], f_string_eol_s);
    } // for

    f_print_dynamic(f_string_eol_s, main->output.to.stream);

    funlockfile(main->output.to.stream);
  }
#endif // _di_kt_remove_simulate_operate_

#ifndef _di_kt_remove_simulate_operate_file_
  void kt_remove_simulate_operate_file(fll_program_data_t * const main, kt_remove_setting_t * const setting, const f_string_static_t path) {

    if (!main || !setting) return;
    if (!(setting->flag & kt_remove_flag_simulate_e)) return;

    fll_print_format("%[Remove '%Q'%]:%r", main->output.to.stream, main->output.set->notable, path, main->output.set->notable, f_string_eol_s);
  }
#endif // _di_kt_remove_simulate_operate_file_

#ifndef _di_kt_remove_simulate_operate_file_exists_
  void kt_remove_simulate_operate_file_exists(fll_program_data_t * const main, kt_remove_setting_t * const setting, const f_string_static_t path) {

    if (!main || !setting) return;
    if (!(setting->flag & kt_remove_flag_simulate_e)) return;

    if (F_status_is_error(setting->status)) {
      fl_print_format("  file_access_failure %un%r", main->output.to.stream, (f_number_unsigned_t) F_status_set_fine(setting->status), f_string_eol_s);

      return;
    }

    if (setting->status == F_true) {
      f_status_t status = f_file_is(path, F_file_type_link_d, F_false);

      if (F_status_is_error(status)) {
        fl_print_format("  file_read_failure %un%r", main->output.to.stream, (f_number_unsigned_t) F_status_set_fine(status), f_string_eol_s);

        return;
      }

      if (status == F_true) {
        setting->buffer.used = 0;

        status = f_file_link_read(path, F_false, &setting->buffer);

        if (F_status_is_error(status)) {
          fl_print_format("  link_read_failure %un%r", main->output.to.stream, (f_number_unsigned_t) F_status_set_fine(status), f_string_eol_s);

          return;
        }

        flockfile(main->output.to.stream);

        fl_print_format("  follow %Q%r", main->output.to.stream, (setting->flag & kt_remove_flag_follow_e) ? kt_remove_yes_s : kt_remove_no_s, f_string_eol_s);
        fl_print_format("  to '%Q'%r", main->output.to.stream, setting->buffer, f_string_eol_s);

        funlockfile(main->output.to.stream);
      }
    }

    fll_print_format("  exists %Q%r", main->output.to.stream, setting->status == F_true ? kt_remove_yes_s : kt_remove_no_s, f_string_eol_s);
  }
#endif // _di_kt_remove_simulate_operate_file_exists_

#ifndef _di_kt_remove_simulate_operate_file_stat_
  void kt_remove_simulate_operate_file_stat(fll_program_data_t * const main, kt_remove_setting_t * const setting, struct stat statistics) {

    if (!main || !setting) return;
    if (!(setting->flag & kt_remove_flag_simulate_e)) return;

    if (setting->flag & kt_remove_flag_block_e) {
      fll_print_format("  block %Q%r", main->output.to.stream, (macro_f_file_type_get(statistics.st_mode) == F_file_type_block_d) ? kt_remove_yes_s : kt_remove_no_s, f_string_eol_s);
    }

    if (setting->flag & kt_remove_flag_character_e) {
      fll_print_format("  character %Q%r", main->output.to.stream, (macro_f_file_type_get(statistics.st_mode) == F_file_type_character_d) ? kt_remove_yes_s : kt_remove_no_s, f_string_eol_s);
    }

    if (setting->flag & kt_remove_flag_directory_e) {
      fll_print_format("  directory %Q%r", main->output.to.stream, (macro_f_file_type_get(statistics.st_mode) == F_file_type_directory_d) ? kt_remove_yes_s : kt_remove_no_s, f_string_eol_s);
    }

    if (setting->flag & kt_remove_flag_fifo_e) {
      fll_print_format("  fifo %Q%r", main->output.to.stream, (macro_f_file_type_get(statistics.st_mode) == F_file_type_fifo_d) ? kt_remove_yes_s : kt_remove_no_s, f_string_eol_s);
    }

    if (setting->flag & kt_remove_flag_link_e) {
      fll_print_format("  link %Q%r", main->output.to.stream, (macro_f_file_type_get(statistics.st_mode) == F_file_type_link_d) ? kt_remove_yes_s : kt_remove_no_s, f_string_eol_s);
    }

    if (setting->flag & kt_remove_flag_regular_e) {
      fll_print_format("  regular %Q%r", main->output.to.stream, (macro_f_file_type_get(statistics.st_mode) == F_file_type_regular_d) ? kt_remove_yes_s : kt_remove_no_s, f_string_eol_s);
    }

    if (setting->flag & kt_remove_flag_socket_e) {
      fll_print_format("  socket %Q%r", main->output.to.stream, (macro_f_file_type_get(statistics.st_mode) == F_file_type_socket_d) ? kt_remove_yes_s : kt_remove_no_s, f_string_eol_s);
    }

    f_array_length_t i = 0;

    if (setting->flag & kt_remove_flag_user_e) {
      for (; i < setting->users.used; ++i) {
        if (statistics.st_uid == (uid_t) setting->users.array[i]) break;
      } // for

      if (i == setting->users.used) {
        fll_print_format("  user%r", main->output.to.stream, f_string_eol_s);
      }
      else {
        fll_print_format("  user %un%r", main->output.to.stream, (f_number_unsigned_t) statistics.st_uid, f_string_eol_s);
      }
    }

    if (setting->flag & kt_remove_flag_same_e) {
      fll_print_format("  same %Q%r", main->output.to.stream, (statistics.st_uid == geteuid()) ? kt_remove_yes_s : kt_remove_no_s, f_string_eol_s);
    }

    if (setting->flag & kt_remove_flag_different_e) {
      fll_print_format("  different %Q%r", main->output.to.stream, (statistics.st_uid == geteuid()) ? kt_remove_no_s : kt_remove_yes_s, f_string_eol_s);
    }

    if (setting->flag & kt_remove_flag_group_e) {
      for (i = 0; i < setting->groups.used; ++i) {
        if (statistics.st_gid == (gid_t) setting->groups.array[i]) break;
      } // for

      if (i == setting->groups.used) {
        fll_print_format("  group%r", main->output.to.stream, f_string_eol_s);
      }
      else {
        fll_print_format("  group %un%r", main->output.to.stream, (f_number_unsigned_t) statistics.st_gid, f_string_eol_s);
      }
    }

    if (setting->flag & kt_remove_flag_mode_e) {
      const mode_t mode = statistics.st_mode & F_file_mode_all_d;

      fll_print_format("  mode %@un%r", main->output.to.stream, (f_number_unsigned_t) mode, f_string_eol_s);

      for (i = 0; i < setting->modes.used; ++i) {

        if (setting->modes.array[i].type == kt_remove_flag_mode_different_e) {
          if (setting->modes.array[i].mode & ~mode) break;
        }
        else if (setting->modes.array[i].type == kt_remove_flag_mode_same_e) {
          if (setting->modes.array[i].mode == mode) break;
        }
        else if (setting->modes.array[i].type == kt_remove_flag_mode_similar_e) {
          if (setting->modes.array[i].mode & mode) break;
        }
        else if (setting->modes.array[i].type == kt_remove_flag_mode_not_e) {
          if (setting->modes.array[i].mode != mode) break;
        }
      } // for

      if (i < setting->modes.used) {
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

          if (setting->modes.array[i].type == types[j]) {
            fll_print_format("  mode_matched %Q %@un%r", main->output.to.stream, strings[j], (f_number_unsigned_t) setting->modes.array[i].mode, f_string_eol_s);

            break;
          }
        } // for
      }
    }

    {
      kt_remove_dates_t * const dates[] = {
        &setting->accessed,
        &setting->created,
        &setting->updated,
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

      f_string_static_t name_type = f_string_empty_s;
      uint8_t p = 0;
      f_status_t result = F_none;

      // @todo: these are put drafted implementations, what needs to be done is consider the type as well (for example 'today' would allow anything at all in the day, this requires more complicated logic than what is below (break this into separte functions to simplify).
      for (; p < 3; ++p) {

        for (i = 0; i < dates[p]->used; ++i) {

          name_type = f_string_empty_s;
          result = F_none;

          if (dates[p]->array[i].operation == kt_remove_flag_date_equal_e) {
            if (times[p].tv_sec == dates[p]->array[i].seconds && times[p].tv_nsec == dates[p]->array[i].nanoseconds) {
              name_type = kt_remove_date_symbol_equal_s;
              result = F_true;
            }
            else {
              result = F_false;
            }
          }
          else if (dates[p]->array[i].operation == kt_remove_flag_date_less_e) {
            if (times[p].tv_sec < dates[p]->array[i].seconds) {
              name_type = kt_remove_date_symbol_less_s;
              result = F_true;
            }
            else if (times[p].tv_sec == dates[p]->array[i].seconds && times[p].tv_nsec < dates[p]->array[i].nanoseconds) {
              name_type = kt_remove_date_symbol_less_s;
              result = F_true;
            }
            else {
              result = F_false;
            }
          }
          else if (dates[p]->array[i].operation == kt_remove_flag_date_less_equal_e) {
            if (times[p].tv_sec < dates[p]->array[i].seconds) {
              name_type = kt_remove_date_symbol_less_equal_s;
              result = F_true;
            }
            else if (times[p].tv_sec == dates[p]->array[i].seconds && times[p].tv_nsec <= dates[p]->array[i].nanoseconds) {
              name_type = kt_remove_date_symbol_less_equal_s;
              result = F_true;
            }
            else {
              result = F_false;
            }
          }
          else if (dates[p]->array[i].operation == kt_remove_flag_date_more_e) {
            if (times[p].tv_sec > dates[p]->array[i].seconds) {
              name_type = kt_remove_date_symbol_more_s;
              result = F_true;
            }
            else if (times[p].tv_sec == dates[p]->array[i].seconds && times[p].tv_nsec > dates[p]->array[i].nanoseconds) {
              name_type = kt_remove_date_symbol_more_s;
              result = F_true;
            }
            else {
              result = F_false;
            }
          }
          else if (dates[p]->array[i].operation == kt_remove_flag_date_more_equal_e) {
            if (times[p].tv_sec > dates[p]->array[i].seconds) {
              name_type = kt_remove_date_symbol_more_equal_s;
              result = F_true;
            }
            else if (times[p].tv_sec == dates[p]->array[i].seconds && times[p].tv_nsec >= dates[p]->array[i].nanoseconds) {
              name_type = kt_remove_date_symbol_more_equal_s;
              result = F_true;
            }
            else {
              result = F_false;
            }
          }
          else if (dates[p]->array[i].operation == kt_remove_flag_date_not_e) {
            if (times[p].tv_sec != dates[p]->array[i].seconds || times[p].tv_nsec != dates[p]->array[i].nanoseconds) {
              name_type = kt_remove_date_symbol_not_s;
              result = F_true;
            }
            else {
              result = F_false;
            }
          }

          if (name_type.used) {
            fll_print_format("  %Q %Q ", main->output.to.stream, *names[p], result ? kt_remove_yes_s : kt_remove_no_s);
            fll_print_format("%u::%un 0:%un %Q ", main->output.to.stream, kt_remove_time_year_unix_epoch_d, (f_number_unsigned_t) times[p].tv_sec, (f_number_unsigned_t) times[p].tv_nsec, name_type);
            fll_print_format("%u::%un 0:%un%r", main->output.to.stream, kt_remove_time_year_unix_epoch_d, dates[p]->array[i].seconds, dates[p]->array[i].nanoseconds, f_string_eol_s);

            break;
          }
        } // for
      } // for
    }
  }
#endif // _di_kt_remove_simulate_operate_file_stat_

#ifndef _di_kt_remove_simulate_operate_remove_force_yes_
  void kt_remove_simulate_operate_remove_force_yes(fll_program_data_t * const main, kt_remove_setting_t * const setting) {

    if (!(setting->flag & kt_remove_flag_simulate_e)) return;

    fll_print_format("  force yes%r", main->output.to.stream, f_string_eol_s);
  }
#endif // _di_kt_remove_simulate_operate_remove_force_yes_

#ifndef _di_kt_remove_simulate_operate_remove_force_no_
  void kt_remove_simulate_operate_remove_force_no(fll_program_data_t * const main, kt_remove_setting_t * const setting) {

    if (!(setting->flag & kt_remove_flag_simulate_e)) return;

    fll_print_format("  force no%r", main->output.to.stream, f_string_eol_s);
  }
#endif // _di_kt_remove_simulate_operate_remove_force_no_

#ifndef _di_kt_remove_simulate_operate_remove_yes_
  void kt_remove_simulate_operate_remove_yes(fll_program_data_t * const main, kt_remove_setting_t * const setting) {

    if (!(setting->flag & kt_remove_flag_simulate_e)) return;

    fll_print_format("  remove yes%r", main->output.to.stream, f_string_eol_s);
  }
#endif // _di_kt_remove_simulate_operate_remove_yes_

#ifndef _di_kt_remove_simulate_operate_remove_no_
  void kt_remove_simulate_operate_remove_no(fll_program_data_t * const main, kt_remove_setting_t * const setting) {

    if (!(setting->flag & kt_remove_flag_simulate_e)) return;

    fll_print_format("  remove no%r", main->output.to.stream, f_string_eol_s);
  }
#endif // _di_kt_remove_simulate_operate_remove_no_

#ifdef __cplusplus
} // extern "C"
#endif
