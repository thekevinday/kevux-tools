#include "remove.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_remove_operate_file_
  void kt_remove_operate_file(fll_program_data_t * const main, kt_remove_setting_t * const setting, const f_string_static_t path) {

    if (!main || !setting) return;

    if (!path.used) {
      setting->status = F_data_not;

      return;
    }

    if (main->signal_received) return;

    kt_remove_simulate_operate_file(main, setting, path);

    setting->status = f_file_exists(path, setting->flag & kt_remove_flag_follow_e);

    kt_remove_simulate_operate_file_exists(main, setting, path);

    if (setting->status == F_false) {
      if (!(setting->flag & kt_remove_flag_simulate_e)) {
        remove_print_warning_file_reason(setting, main->warning, path, kt_remove_print_reason_not_found_s);
      }

      return;
    }

    if (F_status_is_error(setting->status)) {
      if (!(setting->flag & kt_remove_flag_simulate_e)) {
        remove_print_warning_file_reason(setting, main->warning, path, kt_remove_print_reason_no_access_s);
      }

      return;
    }

    if (setting->status == F_false) {
      kt_remove_simulate_operate_remove_no(main, setting);

      return;
    }

    if (main->signal_received) return;

    f_array_length_t i = 0;
    f_status_t remove = (setting->flag & kt_remove_flag_option_used_e) ? F_false : F_true;

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    setting->status = f_file_stat(path, setting->flag & kt_remove_flag_follow_e, &statistics);

    kt_remove_simulate_operate_file_stat(main, setting, statistics);

    if (F_status_is_error(setting->status)) {
      if (!(setting->flag & kt_remove_flag_simulate_e)) {
        remove_print_warning_file_reason(setting, main->warning, path, kt_remove_print_reason_stat_fail_s);
      }

      return;
    }

    if (setting->flag & kt_remove_flag_block_e) {
      if (macro_f_file_type_get(statistics.st_mode) == F_file_type_block_d) {
        remove = F_true;
      }
    }

    if (setting->flag & kt_remove_flag_character_e) {
      if (macro_f_file_type_get(statistics.st_mode) == F_file_type_character_d) {
        remove = F_true;
      }
    }

    if (setting->flag & kt_remove_flag_directory_e) {
      if (macro_f_file_type_get(statistics.st_mode) == F_file_type_directory_d) {
        remove = F_true;
      }
    }

    if (setting->flag & kt_remove_flag_fifo_e) {
      if (macro_f_file_type_get(statistics.st_mode) == F_file_type_fifo_d) {
        remove = F_true;
      }
    }

    if (setting->flag & kt_remove_flag_link_e) {
      if (macro_f_file_type_get(statistics.st_mode) == F_file_type_link_d) {
        remove = F_true;
      }
    }

    if (setting->flag & kt_remove_flag_regular_e) {
      if (macro_f_file_type_get(statistics.st_mode) == F_file_type_regular_d) {
        remove = F_true;
      }
    }

    if (setting->flag & kt_remove_flag_socket_e) {
      if (macro_f_file_type_get(statistics.st_mode) == F_file_type_socket_d) {
        remove = F_true;
      }
    }

    if (main->signal_received) return;

    if (setting->flag & kt_remove_flag_user_e) {
      for (i = 0; i < setting->users.used; ++i) {
        if (statistics.st_uid == (uid_t) setting->users.array[i]) break;
      } // for

      if (i < setting->users.used) {
        remove = F_true;
      }
    }

    if (setting->flag & kt_remove_flag_same_e) {
      if (statistics.st_uid != geteuid()) {
        remove = F_true;
      }
    }

    if (setting->flag & kt_remove_flag_different_e) {
      if (statistics.st_uid == geteuid()) {
        remove = F_true;
      }
    }

    if (setting->flag & kt_remove_flag_group_e) {
      for (i = 0; i < setting->groups.used; ++i) {
        if (statistics.st_gid == (gid_t) setting->groups.array[i]) break;
      } // for

      if (i < setting->groups.used) {
        remove = F_true;
      }
    }

    if (setting->flag & kt_remove_flag_mode_e) {
      const mode_t mode = statistics.st_mode & F_file_mode_all_d;

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
        remove = F_true;
      }
    }

    if (main->signal_received) return;

    setting->status = F_none;

    if (setting->flag & kt_remove_flag_force_e) {
      if (remove == F_false) {
        kt_remove_simulate_operate_remove_force_yes(main, setting);

        remove = F_true;
      }
      else {
        kt_remove_simulate_operate_remove_force_no(main, setting);
      }
    }

    // @todo add check here to see if file is a directory, apply any appropriate restrictions (such as not removing non-empty directories without force or recursive).

    // @todo

    if (remove == F_true) {
      kt_remove_simulate_operate_remove_yes(main, setting);
    }
    else {
      kt_remove_simulate_operate_remove_no(main, setting);
    }

    // @todo do actual removal.
    // @todo be sure too handle all of the remaining flags, such as tree, force, recurse, etc...
  }
#endif // _di_kt_remove_operate_file_

#ifdef __cplusplus
} // extern "C"
#endif
