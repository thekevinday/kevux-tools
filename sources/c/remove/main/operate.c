#include "remove.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_remove_operate_file_
  void kt_remove_operate_file(kt_remove_main_t * const main, const f_string_static_t path) {

    if (!main) return;

    if (!path.used) {
      main->setting.state.status = F_data_not;

      return;
    }

    if (main->program.signal_received) return;

    kt_remove_print_simulate_operate_file(&main->program.output, path);

    main->setting.state.status = f_file_exists(path, main->setting.flag & kt_remove_main_flag_follow_e);

    kt_remove_print_simulate_operate_file_exists(&main->program.output, path);

    if (main->setting.state.status == F_false) {
      if (!(main->setting.flag & kt_remove_main_flag_simulate_e)) {
        remove_print_warning_file_reason(&main->program.warning, path, kt_remove_print_reason_not_found_s);
      }

      return;
    }

    if (F_status_is_error(main->setting.state.status)) {
      if (!(main->setting.flag & kt_remove_main_flag_simulate_e)) {
        remove_print_warning_file_reason(&main->program.warning, path, kt_remove_print_reason_no_access_s);
      }

      return;
    }

    if (main->setting.state.status == F_false) {
      kt_remove_print_simulate_operate_boolean(&main->program.output, kt_remove_remove_s, F_false);

      return;
    }

    if (main->program.signal_received) return;

    f_number_unsigned_t i = 0;
    uint8_t flag = (main->setting.flag & kt_remove_main_flag_option_used_e) ? 0 : kt_remove_flag_file_operate_remove_e;

    struct stat statistics;

    memset(&statistics, 0, sizeof(struct stat));

    main->setting.state.status = f_file_stat(path, main->setting.flag & kt_remove_main_flag_follow_e, &statistics);

    kt_remove_print_simulate_operate_file_stat(&main->program.output, statistics);

    if (F_status_is_error(main->setting.state.status)) {
      if (!(main->setting.flag & kt_remove_main_flag_simulate_e)) {
        remove_print_warning_file_reason(&main->program.warning, path, kt_remove_print_reason_stat_fail_s);
      }

      return;
    }

    if (main->setting.flag & kt_remove_main_flag_block_e) {
      if (macro_f_file_type_get(statistics.st_mode) == F_file_type_block_d) {
        flag |= kt_remove_flag_file_operate_remove_e;
      }
    }

    if (main->setting.flag & kt_remove_main_flag_character_e) {
      if (macro_f_file_type_get(statistics.st_mode) == F_file_type_character_d) {
        flag |= kt_remove_flag_file_operate_remove_e;
      }
    }

    if (macro_f_file_type_get(statistics.st_mode) == F_file_type_directory_d) {
      flag |= kt_remove_flag_file_operate_directory_e;

      if (main->setting.flag & kt_remove_main_flag_directory_e) {
        flag |= kt_remove_flag_file_operate_remove_e;
      }
    }

    if (main->setting.flag & kt_remove_main_flag_fifo_e) {
      if (macro_f_file_type_get(statistics.st_mode) == F_file_type_fifo_d) {
        flag |= kt_remove_flag_file_operate_remove_e;
      }
    }

    if (main->setting.flag & kt_remove_main_flag_link_e) {
      if (macro_f_file_type_get(statistics.st_mode) == F_file_type_link_d) {
        flag |= kt_remove_flag_file_operate_remove_e;
      }
    }

    if (main->setting.flag & kt_remove_main_flag_regular_e) {
      if (macro_f_file_type_get(statistics.st_mode) == F_file_type_regular_d) {
        flag |= kt_remove_flag_file_operate_remove_e;
      }
    }

    if (main->setting.flag & kt_remove_main_flag_socket_e) {
      if (macro_f_file_type_get(statistics.st_mode) == F_file_type_socket_d) {
        flag |= kt_remove_flag_file_operate_remove_e;
      }
    }

    if (main->setting.flag & kt_remove_main_flag_user_e) {
      for (i = 0; i < main->setting.users.used; ++i) {

        if (main->program.signal_received) return;
        if (statistics.st_uid == (uid_t) main->setting.users.array[i]) break;
      } // for

      if (i < main->setting.users.used) {
        flag |= kt_remove_flag_file_operate_remove_e;
      }
    }

    if (main->setting.flag & kt_remove_main_flag_same_e) {
      if (statistics.st_uid != geteuid()) {
        flag |= kt_remove_flag_file_operate_remove_e;
      }
    }

    if (main->setting.flag & kt_remove_main_flag_different_e) {
      if (statistics.st_uid == geteuid()) {
        flag |= kt_remove_flag_file_operate_remove_e;
      }
    }

    if (main->setting.flag & kt_remove_main_flag_group_e) {
      for (i = 0; i < main->setting.groups.used; ++i) {

        if (main->program.signal_received) return;
        if (statistics.st_gid == (gid_t) main->setting.groups.array[i]) break;
      } // for

      if (i < main->setting.groups.used) {
        flag |= kt_remove_flag_file_operate_remove_e;
      }
    }

    if (main->setting.flag & kt_remove_main_flag_mode_e) {
      const mode_t mode = statistics.st_mode & F_file_mode_all_d;

      for (i = 0; i < main->setting.modes.used; ++i) {

        if (main->program.signal_received) return;

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
        flag |= kt_remove_flag_file_operate_remove_e;
      }

      if (main->setting.flag & kt_remove_main_flag_recurse_e) {
        flag |= kt_remove_flag_file_operate_recurse_e;
      }

      if (main->setting.flag & kt_remove_main_flag_force_e) {
        flag |= kt_remove_flag_file_operate_remove_e;
      }

      // Trigger the callback to make any modifications before simulating or performing the removal.
      if (main->setting.process_operate_file) {
        main->setting.state.status = F_none;

        main->setting.process_operate_file((void *) main, path, statistics, &flag);
        if (F_status_is_error(main->setting.state.status)) return;

        if (main->setting.state.status == F_done) {
          main->setting.state.status = F_none;

          return;
        }
      }

      main->setting.state.status = F_none;
    }

    if (main->setting.flag & kt_remove_main_flag_force_e) {
      kt_remove_print_simulate_operate_boolean(&main->program.output, kt_remove_force_s, F_true);
    }

    if (flag & kt_remove_flag_file_operate_directory_e) {
      kt_remove_print_simulate_operate_boolean(&main->program.output, kt_remove_recurse_s, flag & kt_remove_flag_file_operate_recurse_e);
    }

    // @todo add check here to see if file is a directory, apply any appropriate restrictions (such as not removing non-empty directories without force or recursive).
    // @todo be sure too handle all of the remaining flags, such as tree, force, recurse, etc...:
    //   - kt_remove_main_flag_accessed_e
    //   - kt_remove_main_flag_created_e
    //   - kt_remove_main_flag_empty_only_e
    //   - kt_remove_main_flag_empty_only_fail_e
    //   - kt_remove_main_flag_empty_not_e
    //   - kt_remove_main_flag_empty_not_fail_e
    //   - kt_remove_main_flag_prompt_all_e
    //   - kt_remove_main_flag_prompt_follow_e
    //   - kt_remove_main_flag_prompt_never_e
    //   - kt_remove_main_flag_prompt_once_e
    //   - kt_remove_main_flag_recurse_e
    //   - kt_remove_main_flag_tree_e
    //   - kt_remove_main_flag_updated_e

    kt_remove_print_simulate_operate_boolean(&main->program.output, kt_remove_remove_s, flag & kt_remove_flag_file_operate_remove_e);

    // @todo do actual removal.
  }
#endif // _di_kt_remove_operate_file_

#ifdef __cplusplus
} // extern "C"
#endif
