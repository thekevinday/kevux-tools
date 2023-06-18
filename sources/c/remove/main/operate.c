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

    if (main->setting.flag & kt_remove_main_flag_follow_e) {
      flag |= kt_remove_flag_file_operate_follow_e;
    }

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
      if (macro_f_file_type_is_block(statistics.st_mode)) {
        flag |= kt_remove_flag_file_operate_remove_e;
      }
    }

    if (main->setting.flag & kt_remove_main_flag_character_e) {
      if (macro_f_file_type_is_character(statistics.st_mode)) {
        flag |= kt_remove_flag_file_operate_remove_e;
      }
    }


    if (macro_f_file_type_is_directory(statistics.st_mode)) {
      flag |= kt_remove_flag_file_operate_directory_e;

      if (main->setting.flag & kt_remove_main_flag_directory_e) {
        flag |= kt_remove_flag_file_operate_remove_e;
      }
    }

    if (main->setting.flag & kt_remove_main_flag_fifo_e) {
      if (macro_f_file_type_is_fifo(statistics.st_mode)) {
        flag |= kt_remove_flag_file_operate_remove_e;
      }
    }

    if (main->setting.flag & kt_remove_main_flag_link_e) {
      if (macro_f_file_type_is_link(statistics.st_mode)) {
        flag |= kt_remove_flag_file_operate_remove_e;
      }
    }

    if (main->setting.flag & kt_remove_main_flag_regular_e) {
      if (macro_f_file_type_is_regular(statistics.st_mode)) {
        flag |= kt_remove_flag_file_operate_remove_e;
      }
    }

    if (main->setting.flag & kt_remove_main_flag_socket_e) {
      if (macro_f_file_type_is_socket(statistics.st_mode)) {
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

    if (flag & kt_remove_flag_file_operate_directory_e) {
      if (main->setting.flag & kt_remove_main_flag_empty_all_d) {
        // @todo handle simulate for this.
      }

      // Recurse effectively forces tree.
      if (main->setting.flag & kt_remove_main_flag_recurse_e) {
        // @todo handle simulate for this.
        // @todo consider not following "rm" and having recurse not act like "--force" is specified.
      }
      else if (main->setting.flag & kt_remove_main_flag_tree_e) {
        // @todo handle simulate for this.
      }
    }

    if (main->setting.flag & kt_remove_main_flag_prompt_all_d) {
      // @todo handle simulate for this.
    }

    kt_remove_print_simulate_operate_boolean(&main->program.output, kt_remove_remove_s, flag & kt_remove_flag_file_operate_remove_e);

    if (!(main->setting.flag & kt_remove_main_flag_simulate_e)) {
      if (flag & kt_remove_flag_file_operate_directory_e) {
        kt_remove_operate_file_directory(main, path, flag);
        if (F_status_is_error(main->setting.state.status)) return;
      }
      else {
        kt_remove_operate_file_normal(main, path, flag);
        if (F_status_is_error(main->setting.state.status)) return;
      }
    }

    main->setting.state.status = F_none;
  }
#endif // _di_kt_remove_operate_file_

#ifndef _di_kt_remove_operate_file_directory_
  void kt_remove_operate_file_directory(kt_remove_main_t * const main, const f_string_static_t path, const uint8_t flag) {

    if (!(flag & kt_remove_flag_file_operate_remove_e)) {
      main->setting.state.status = F_no;

      return;
    }

    main->setting.state.status = F_yes;
  }
#endif // _di_kt_remove_operate_file_directory_

#ifndef _di_kt_remove_operate_file_normal_
  void kt_remove_operate_file_normal(kt_remove_main_t * const main, const f_string_static_t path, const uint8_t flag) {

    if (!(flag & kt_remove_flag_file_operate_remove_e)) {
      main->setting.state.status = F_no;

      return;
    }

    // @todo consider providing a "follow deep" parameter for recursively following until a non-link is reached.
    if (flag & kt_remove_flag_file_operate_follow_e) {
      main->setting.buffer.used = 0;

      main->setting.state.status = f_file_link_read(path, F_false, &main->setting.buffer);

      if (F_status_is_error(main->setting.state.status)) {
        kt_remove_print_error_file(&main->program.error, macro_kt_remove_f(f_file_remove), path, f_file_operation_stat_s, fll_error_file_type_link_e);

        return;
      }

      main->setting.state.status = f_file_remove(main->setting.buffer);

      if (F_status_is_error(main->setting.state.status)) {
        kt_remove_print_error_file(&main->program.error, macro_kt_remove_f(f_file_remove), main->setting.buffer, f_file_operation_delete_s, fll_error_file_type_file_e);

        return;
      }
    }
    else {
      main->setting.state.status = f_file_remove(path);

      if (F_status_is_error(main->setting.state.status)) {
        kt_remove_print_error_file(&main->program.error, macro_kt_remove_f(f_file_remove), path, f_file_operation_delete_s, fll_error_file_type_file_e);

        return;
      }
    }

    main->setting.state.status = F_yes;
  }
#endif // _di_kt_remove_operate_file_normal_

#ifdef __cplusplus
} // extern "C"
#endif
