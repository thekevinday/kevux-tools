#include "remove.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_remove_dates_resize_
  f_status_t kt_remove_dates_resize(const f_array_length_t length, kt_remove_dates_t * const dates) {

    if (!dates) return F_status_set_error(F_parameter);

    if (dates->used + length > F_array_length_t_size_d) return F_status_set_error(F_array_too_large);

    const f_status_t status = f_memory_resize(dates->size, length, sizeof(kt_remove_date_t), (void **) & dates->array);
    if (F_status_is_error(status)) return status;

    dates->size = length;

    if (dates->used > dates->size) {
      dates->used = length;
    }

    return F_none;
  }
#endif // _di_kt_remove_dates_resize_

#ifndef _di_kt_remove_modes_resize_
  f_status_t kt_remove_modes_resize(const f_array_length_t length, kt_remove_modes_t * const modes) {

    if (!modes) return F_status_set_error(F_parameter);

    if (modes->used + length > F_array_length_t_size_d) return F_status_set_error(F_array_too_large);

    const f_status_t status = f_memory_resize(modes->size, length, sizeof(kt_remove_mode_t), (void **) & modes->array);
    if (F_status_is_error(status)) return status;

    modes->size = length;

    if (modes->used > modes->size) {
      modes->used = length;
    }

    return F_none;
  }
#endif // _di_kt_remove_modes_resize_

#ifndef _di_kt_remove_setting_delete_
  f_status_t kt_remove_setting_delete(kt_remove_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    f_string_dynamic_resize(0, &setting->buffer);
    f_string_dynamics_resize(0, &setting->files);

    kt_remove_dates_resize(0, &setting->accessed);
    kt_remove_dates_resize(0, &setting->created);
    kt_remove_dates_resize(0, &setting->updated);
    kt_remove_modes_resize(0, &setting->modes);

    f_uint32s_resize(0, &setting->groups);
    f_uint32s_resize(0, &setting->users);

    return F_none;
  }
#endif // _di_kt_remove_setting_delete_

#ifndef _di_kt_remove_setting_load_
  void kt_remove_setting_load(const f_console_arguments_t arguments, kt_remove_main_t * const main) {

    if (!main) return;

    main->setting.flag -= main->setting.flag & kt_remove_main_flag_option_used_e;

    main->setting.state.step_small = kt_remove_allocation_console_d;

    f_console_parameter_process(arguments, &main->program.parameters, &main->setting.state, 0);

    main->setting.state.step_small = kt_remove_allocation_small_d;


    // Identify and pocess first/last parameters.
    if (main->program.parameters.array[kt_remove_parameter_line_first_no_e].result & f_console_result_found_e) {
      main->setting.flag -= main->setting.flag & kt_remove_main_flag_print_first_e;
    }
    else {
      main->setting.flag |= kt_remove_main_flag_print_first_e;
    }

    if (main->program.parameters.array[kt_remove_parameter_line_last_no_e].result & f_console_result_found_e) {
      main->setting.flag -= main->setting.flag & kt_remove_main_flag_print_last_e;
    }
    else {
      main->setting.flag |= kt_remove_main_flag_print_last_e;
    }

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & kt_remove_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      kt_remove_print_error(&main->program.error, macro_kt_remove_f(f_console_parameter_process));

      return;
    }

   {
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { kt_remove_parameter_no_color_e, kt_remove_parameter_light_e, kt_remove_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        main->setting.state.status = fll_program_parameter_process_context(choices, modes, F_true, &main->program);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & kt_remove_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          kt_remove_print_error(&main->program.error, macro_kt_remove_f(fll_program_parameter_process_context));

          return;
        }
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { kt_remove_parameter_verbosity_quiet_e, kt_remove_parameter_verbosity_error_e, kt_remove_parameter_verbosity_verbose_e, kt_remove_parameter_verbosity_debug_e, kt_remove_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        main->setting.state.status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, &main->program);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & kt_remove_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          kt_remove_print_error(&main->program.error, macro_kt_remove_f(fll_program_parameter_process_verbosity));

          return;
        }
      }
    }

    f_array_length_t i = 0;
    f_array_length_t index = 0;
    f_array_length_t index2 = 0;
    f_array_length_t total_locations = 0;
    f_array_length_t total_arguments = 0;

    uint8_t j = 0;

    if (main->program.parameters.array[kt_remove_parameter_help_e].result & f_console_result_found_e) {
      main->setting.flag |= kt_remove_main_flag_help_e;
    }

    if (main->program.parameters.array[kt_remove_parameter_version_e].result & f_console_result_found_e) {
      main->setting.flag |= kt_remove_main_flag_version_e;
    }

    if (main->program.parameters.array[kt_remove_parameter_copyright_e].result & f_console_result_found_e) {
      main->setting.flag |= kt_remove_main_flag_copyright_e;
    }

    if (main->program.parameters.array[kt_remove_parameter_block_e].result & f_console_result_found_e) {
      main->setting.flag |= kt_remove_main_flag_block_e;
      main->setting.flag |= kt_remove_main_flag_option_used_e;
    }

    if (main->program.parameters.array[kt_remove_parameter_character_e].result & f_console_result_found_e) {
      main->setting.flag |= kt_remove_main_flag_character_e;
      main->setting.flag |= kt_remove_main_flag_option_used_e;
    }

    if (main->program.parameters.array[kt_remove_parameter_different_e].result & f_console_result_found_e) {
      if (main->program.parameters.array[kt_remove_parameter_same_e].result & f_console_result_found_e) {
        index = main->program.parameters.array[kt_remove_parameter_different_e].locations.used;
        index2 = main->program.parameters.array[kt_remove_parameter_same_e].locations.used;

        if (main->program.parameters.array[kt_remove_parameter_different_e].locations.array[index] > main->program.parameters.array[kt_remove_parameter_same_e].locations.array[index2]) {
          main->setting.flag |= kt_remove_main_flag_different_e;

          if (main->setting.flag & kt_remove_main_flag_same_e) {
            main->setting.flag -= kt_remove_main_flag_same_e;
          }
        }
        else {
          main->setting.flag |= kt_remove_main_flag_same_e;

          if (main->setting.flag & kt_remove_main_flag_different_e) {
            main->setting.flag -= kt_remove_main_flag_different_e;
          }
        }
      }
      else {
        main->setting.flag |= kt_remove_main_flag_different_e;

        if (main->setting.flag & kt_remove_main_flag_same_e) {
          main->setting.flag -= kt_remove_main_flag_same_e;
        }
      }

      main->setting.flag |= kt_remove_main_flag_option_used_e;
    }
    else if (main->program.parameters.array[kt_remove_parameter_same_e].result & f_console_result_found_e) {
      main->setting.flag |= kt_remove_main_flag_same_e;

      if (main->setting.flag & kt_remove_main_flag_different_e) {
        main->setting.flag -= kt_remove_main_flag_different_e;
      }

      main->setting.flag |= kt_remove_main_flag_option_used_e;
    }

    if (main->program.parameters.array[kt_remove_parameter_fifo_e].result & f_console_result_found_e) {
      main->setting.flag |= kt_remove_main_flag_fifo_e;
      main->setting.flag |= kt_remove_main_flag_option_used_e;
    }

    if (main->program.parameters.array[kt_remove_parameter_follow_e].result & f_console_result_found_e) {
      if (main->program.parameters.array[kt_remove_parameter_stay_e].result & f_console_result_found_e) {
        index = main->program.parameters.array[kt_remove_parameter_follow_e].locations.used;
        index2 = main->program.parameters.array[kt_remove_parameter_stay_e].locations.used;

        if (main->program.parameters.array[kt_remove_parameter_follow_e].locations.array[index] > main->program.parameters.array[kt_remove_parameter_stay_e].locations.array[index2]) {
          main->setting.flag |= kt_remove_main_flag_follow_e;
        }
        else {
          if (main->setting.flag & kt_remove_main_flag_follow_e) {
            main->setting.flag -= kt_remove_main_flag_follow_e;
          }
        }
      }
      else {
        main->setting.flag |= kt_remove_main_flag_follow_e;
      }
    }
    else if (main->program.parameters.array[kt_remove_parameter_stay_e].result & f_console_result_found_e) {
      if (main->setting.flag & kt_remove_main_flag_follow_e) {
        main->setting.flag -= kt_remove_main_flag_follow_e;
      }
    }

    if (main->program.parameters.array[kt_remove_parameter_force_e].result & f_console_result_found_e) {
      main->setting.flag |= kt_remove_main_flag_force_e;
    }

    if (main->program.parameters.array[kt_remove_parameter_link_e].result & f_console_result_found_e) {
      main->setting.flag |= kt_remove_main_flag_link_e;
      main->setting.flag |= kt_remove_main_flag_option_used_e;
    }

    if (main->program.parameters.array[kt_remove_parameter_recurse_e].result & f_console_result_found_e) {
      main->setting.flag |= kt_remove_main_flag_recurse_e;
    }

    if (main->program.parameters.array[kt_remove_parameter_regular_e].result & f_console_result_found_e) {
      main->setting.flag |= kt_remove_main_flag_regular_e;
      main->setting.flag |= kt_remove_main_flag_option_used_e;
    }

    if (main->program.parameters.array[kt_remove_parameter_simulate_e].result & f_console_result_found_e) {
      main->setting.flag |= kt_remove_main_flag_simulate_e;
    }

    if (main->program.parameters.array[kt_remove_parameter_socket_e].result & f_console_result_found_e) {
      main->setting.flag |= kt_remove_main_flag_socket_e;
      main->setting.flag |= kt_remove_main_flag_option_used_e;
    }

    if (main->program.parameters.array[kt_remove_parameter_tree_e].result & f_console_result_found_e) {
      main->setting.flag |= kt_remove_main_flag_tree_e;
    }

    {
      f_console_parameter_t * const parameters[] = {
        &main->program.parameters.array[kt_remove_parameter_accessed_e],
        &main->program.parameters.array[kt_remove_parameter_created_e],
        &main->program.parameters.array[kt_remove_parameter_updated_e],
      };

      kt_remove_dates_t * const dates[] = {
        &main->setting.accessed,
        &main->setting.created,
        &main->setting.updated,
      };

      const f_string_static_t longs[] = {
        kt_remove_long_accessed_s,
        kt_remove_long_created_s,
        kt_remove_long_updated_s,
      };

      for (uint8_t p = 0; p < 3; ++p) {

        // kt_remove_parameter_accessed_e, kt_remove_parameter_created_e, kt_remove_parameter_updated_e, needs additional parameters, ==, <, <=, >, >=, <>.
        if (parameters[p]->result & f_console_result_found_e) {
          main->setting.state.status = F_status_set_error(F_parameter);

          kt_remove_print_error_parameter_missing_value_requires_amount(&main->program.error, f_console_symbol_long_normal_s, longs[p], 2);

          return;
        }

        if (parameters[p]->result & f_console_result_value_e) {
          total_locations = parameters[p]->locations.used;
          total_arguments = parameters[p]->values.used;

          if (total_locations * 2 != total_arguments) {
            main->setting.state.status = F_status_set_error(F_parameter);

            kt_remove_print_error_parameter_missing_value_requires_amount(&main->program.error, f_console_symbol_long_normal_s, longs[p], 2);

            return;
          }

          if (dates[p]->used + total_locations > dates[p]->size) {
            main->setting.state.status = kt_remove_dates_resize(dates[p]->size + (total_locations - dates[p]->size), dates[p]);

            if (F_status_is_error(main->setting.state.status)) {
              kt_remove_print_error(&main->program.error, macro_kt_remove_f(kt_remove_dates_resize));

              return;
            }
          }

          uint8_t enumerations[] = {
            kt_remove_flag_date_equal_e,
            kt_remove_flag_date_less_e,
            kt_remove_flag_date_less_equal_e,
            kt_remove_flag_date_more_e,
            kt_remove_flag_date_more_equal_e,
            kt_remove_flag_date_not_e,
            kt_remove_flag_date_equal_e,
            kt_remove_flag_date_less_e,
            kt_remove_flag_date_less_equal_e,
            kt_remove_flag_date_more_e,
            kt_remove_flag_date_more_equal_e,
            kt_remove_flag_date_not_e,
          };

          f_string_static_t strings[] = {
            kt_remove_date_symbol_equal_s,
            kt_remove_date_symbol_less_s,
            kt_remove_date_symbol_less_equal_s,
            kt_remove_date_symbol_more_s,
            kt_remove_date_symbol_more_equal_s,
            kt_remove_date_symbol_not_s,
            kt_remove_date_word_equal_s,
            kt_remove_date_word_less_s,
            kt_remove_date_word_less_equal_s,
            kt_remove_date_word_more_s,
            kt_remove_date_word_more_equal_s,
            kt_remove_date_word_not_s,
          };

          main->setting.state.status = F_known_not;

          {
            for (i = 0; i < total_arguments; i += 2) {

              index = parameters[p]->values.array[i];
              dates[p]->array[dates[p]->used].operation = 0;
              dates[p]->array[dates[p]->used].type = 0;

              for (j = 0; j < 12; ++j) {

                if (fl_string_dynamic_compare(main->program.parameters.arguments.array[index], strings[j]) == F_equal_to) {
                  dates[p]->array[dates[p]->used].operation = enumerations[j];

                  index2 = parameters[p]->values.array[i + 1];

                  kt_remove_convert_date(main, main->program.parameters.arguments.array[index2], &dates[p]->array[dates[p]->used]);
                  if (F_status_is_error(main->setting.state.status)) return;

                  ++dates[p]->used;

                  break;
                }

                if (kt_remove_signal_check(main)) return;
              } // for

              if (j == 12) {
                main->setting.state.status = F_status_set_error(F_parameter);

                kt_remove_print_error_parameter_unknown_value(&main->program.error, f_console_symbol_long_normal_s, longs[p], main->program.parameters.arguments.array[index]);

                return;
              }
            } // for
          }

          main->setting.flag |= kt_remove_main_flag_option_used_e;
        } // for
      }
    }

    // kt_remove_parameter_group_e, needs additional parameters (group).
    if (main->program.parameters.array[kt_remove_parameter_empty_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      kt_remove_print_error_parameter_missing_value_requires_amount(&main->program.error, f_console_symbol_long_normal_s, kt_remove_long_empty_s, 1);

      return;
    }

    if (main->program.parameters.array[kt_remove_parameter_empty_e].result & f_console_result_value_e) {
      total_arguments = main->program.parameters.array[kt_remove_parameter_empty_e].values.used;

      if (main->program.parameters.array[kt_remove_parameter_empty_e].locations.used != total_arguments) {
        main->setting.state.status = F_status_set_error(F_parameter);

        kt_remove_print_error_parameter_missing_value_requires_amount(&main->program.error, f_console_symbol_long_normal_s, kt_remove_long_empty_s, 1);

        return;
      }

      index = main->program.parameters.array[kt_remove_parameter_empty_e].values.array[total_arguments - 1];

      if (fl_string_dynamic_compare(kt_remove_not_s, main->program.parameters.arguments.array[index]) == F_equal_to) {
        main->setting.flag |= kt_remove_main_flag_empty_not_e;

        if (main->setting.flag & kt_remove_main_flag_empty_not_fail_e) {
          main->setting.flag -= kt_remove_main_flag_empty_not_fail_e;
        }

        if (main->setting.flag & kt_remove_main_flag_empty_only_e) {
          main->setting.flag -= kt_remove_main_flag_empty_only_e;
        }

        if (main->setting.flag & kt_remove_main_flag_empty_only_fail_e) {
          main->setting.flag -= kt_remove_main_flag_empty_only_fail_e;
        }
      }
      else if (fl_string_dynamic_compare(kt_remove_not_fail_s, main->program.parameters.arguments.array[index]) == F_equal_to) {
        main->setting.flag |= kt_remove_main_flag_empty_not_fail_e;

        if (main->setting.flag & kt_remove_main_flag_empty_not_e) {
          main->setting.flag -= kt_remove_main_flag_empty_not_e;
        }

        if (main->setting.flag & kt_remove_main_flag_empty_only_e) {
          main->setting.flag -= kt_remove_main_flag_empty_only_e;
        }

        if (main->setting.flag & kt_remove_main_flag_empty_only_fail_e) {
          main->setting.flag -= kt_remove_main_flag_empty_only_fail_e;
        }
      }
      else if (fl_string_dynamic_compare(kt_remove_only_s, main->program.parameters.arguments.array[index]) == F_equal_to) {
        main->setting.flag |= kt_remove_main_flag_empty_only_e;

        if (main->setting.flag & kt_remove_main_flag_empty_not_e) {
          main->setting.flag -= kt_remove_main_flag_empty_not_e;
        }

        if (main->setting.flag & kt_remove_main_flag_empty_not_fail_e) {
          main->setting.flag -= kt_remove_main_flag_empty_not_fail_e;
        }

        if (main->setting.flag & kt_remove_main_flag_empty_only_fail_e) {
          main->setting.flag -= kt_remove_main_flag_empty_only_fail_e;
        }
      }
      else if (fl_string_dynamic_compare(kt_remove_only_fail_s, main->program.parameters.arguments.array[index]) == F_equal_to) {
        main->setting.flag |= kt_remove_main_flag_empty_only_fail_e;

        if (main->setting.flag & kt_remove_main_flag_empty_not_e) {
          main->setting.flag -= kt_remove_main_flag_empty_not_e;
        }

        if (main->setting.flag & kt_remove_main_flag_empty_not_fail_e) {
          main->setting.flag -= kt_remove_main_flag_empty_not_fail_e;
        }

        if (main->setting.flag & kt_remove_main_flag_empty_only_e) {
          main->setting.flag -= kt_remove_main_flag_empty_only_e;
        }
      }
      else {
        main->setting.state.status = F_status_set_error(F_parameter);

        kt_remove_print_error_parameter_unknown_value(&main->program.error, f_console_symbol_long_normal_s, kt_remove_long_empty_s, main->program.parameters.arguments.array[index]);

        return;
      }

      main->setting.flag |= kt_remove_main_flag_option_used_e;
    }

    // kt_remove_parameter_group_e, needs additional parameters (gid).
    if (main->program.parameters.array[kt_remove_parameter_group_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      kt_remove_print_error_parameter_missing_value_requires_amount(&main->program.error, f_console_symbol_long_normal_s, kt_remove_long_group_s, 1);

      return;
    }

    if (main->program.parameters.array[kt_remove_parameter_group_e].result & f_console_result_value_e) {
      total_arguments = main->program.parameters.array[kt_remove_parameter_group_e].values.used;

      if (main->program.parameters.array[kt_remove_parameter_group_e].locations.used != total_arguments) {
        main->setting.state.status = F_status_set_error(F_parameter);

        kt_remove_print_error_parameter_missing_value_requires_amount(&main->program.error, f_console_symbol_long_normal_s, kt_remove_long_group_s, 1);

        return;
      }

      main->setting.state.status = f_uint32s_increase_by(total_arguments, &main->setting.groups);

      if (F_status_is_error(main->setting.state.status)) {
        kt_remove_print_error(&main->program.error, macro_kt_remove_f(f_uint32s_increase_by));

        return;
      }

      for (i = 0; i < total_arguments; ++i) {

        index = main->program.parameters.array[kt_remove_parameter_group_e].values.array[i];

        main->setting.groups.array[main->setting.groups.used] = kt_remove_get_id_group(main, main->program.parameters.arguments.array[index]);

        if (F_status_is_error(main->setting.state.status)) {
          kt_remove_print_error(&main->program.error, macro_kt_remove_f(kt_remove_get_id_group));

          return;
        }

        ++main->setting.groups.used;
      } // for

      main->setting.flag |= kt_remove_main_flag_group_e;
      main->setting.flag |= kt_remove_main_flag_option_used_e;
    }

    // kt_remove_parameter_isolate_e, needs additional parameters (all, ignore, or root).
    // Currently not supported, requires /proc support.
    //if (main->program.parameters.array[kt_remove_parameter_isolate_e].result & f_console_result_found_e) {
    //  main->setting.state.status = F_status_set_error(F_parameter);
    //
    //  kt_remove_print_error_parameter_missing_value_requires_amount(&main->program.error, f_console_symbol_long_normal_s, kt_remove_long_isolate_s, 1);
    //
    //  return;
    //}
    //
    //if (main->program.parameters.array[kt_remove_parameter_isolate_e].result & f_console_result_value_e) {
    //  total_arguments = main->program.parameters.array[kt_remove_parameter_isolate_e].values.used;
    //
    //  if (main->program.parameters.array[kt_remove_parameter_isolate_e].locations.used != total_arguments) {
    //    main->setting.state.status = F_status_set_error(F_parameter);
    //
    //    kt_remove_print_error_parameter_missing_value_requires_amount(&main->program.error, f_console_symbol_long_normal_s, kt_remove_long_isolate_s, 1);
    //
    //    return;
    //  }
    //
    //  index = main->program.parameters.array[kt_remove_parameter_isolate_e].values.array[total_arguments - 1];
    //
    //  if (fl_string_dynamic_compare(kt_remove_all_s, main->program.parameters.arguments.array[index]) == F_equal_to) {
    //    main->setting.flag |= kt_remove_main_flag_isolate_all_e;
    //
    //    if (main->setting.flag & kt_remove_main_flag_isolate_ignore_e) {
    //      main->setting.flag -= kt_remove_main_flag_isolate_ignore_e;
    //    }
    //
    //    if (main->setting.flag & kt_remove_main_flag_isolate_root_e) {
    //      main->setting.flag -= kt_remove_main_flag_isolate_root_e;
    //    }
    //  }
    //  else if (fl_string_dynamic_compare(kt_remove_ignore_s, main->program.parameters.arguments.array[index]) == F_equal_to) {
    //    main->setting.flag |= kt_remove_main_flag_isolate_ignore_e;
    //
    //    if (main->setting.flag & kt_remove_main_flag_isolate_all_e) {
    //      main->setting.flag -= kt_remove_main_flag_isolate_all_e;
    //    }
    //
    //    if (main->setting.flag & kt_remove_main_flag_isolate_root_e) {
    //      main->setting.flag -= kt_remove_main_flag_isolate_root_e;
    //    }
    //  }
    //  else if (fl_string_dynamic_compare(kt_remove_root_s, main->program.parameters.arguments.array[index]) == F_equal_to) {
    //    main->setting.flag |= kt_remove_main_flag_isolate_root_e;
    //
    //    if (main->setting.flag & kt_remove_main_flag_isolate_all_e) {
    //      main->setting.flag -= kt_remove_main_flag_isolate_all_e;
    //    }
    //
    //    if (main->setting.flag & kt_remove_main_flag_isolate_ignore_e) {
    //      main->setting.flag -= kt_remove_main_flag_isolate_ignore_e;
    //    }
    //  }
    //  else {
    //    main->setting.state.status = F_status_set_error(F_parameter);
    //
    //    kt_remove_print_error_parameter_unknown_value(&main->program.error, f_console_symbol_long_normal_s, kt_remove_long_isolate_s, main->program.parameters.arguments.array[index]);
    //
    //    return;
    //  }
    //}

    // kt_remove_parameter_mode_e, needs additional parameters (modes, match parameters).
    if (main->program.parameters.array[kt_remove_parameter_mode_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      kt_remove_print_error_parameter_missing_value_requires_amount(&main->program.error, f_console_symbol_long_normal_s, kt_remove_long_mode_s, 2);

      return;
    }

    if (main->program.parameters.array[kt_remove_parameter_mode_e].result & f_console_result_value_e) {
      total_locations = main->program.parameters.array[kt_remove_parameter_mode_e].locations.used;
      total_arguments = main->program.parameters.array[kt_remove_parameter_mode_e].values.used;

      if (total_locations * 2 != total_arguments) {
        main->setting.state.status = F_status_set_error(F_parameter);

        kt_remove_print_error_parameter_missing_value_requires_amount(&main->program.error, f_console_symbol_long_normal_s, kt_remove_long_mode_s, 2);

        return;
      }

      if (main->setting.modes.used + total_locations > main->setting.modes.size) {
        main->setting.state.status = kt_remove_modes_resize(main->setting.modes.size + (total_locations - main->setting.modes.size), &main->setting.modes);

        if (F_status_is_error(main->setting.state.status)) {
          kt_remove_print_error(&main->program.error, macro_kt_remove_f(kt_remove_modes_resize));

          return;
        }
      }

      uint8_t enumerations[] = {
        kt_remove_flag_mode_different_e,
        kt_remove_flag_mode_same_e,
        kt_remove_flag_mode_similar_e,
        kt_remove_flag_mode_not_e,
        kt_remove_flag_mode_different_e,
        kt_remove_flag_mode_same_e,
        kt_remove_flag_mode_similar_e,
        kt_remove_flag_mode_not_e,
      };

      f_string_static_t strings[] = {
        kt_remove_mode_symbol_different_s,
        kt_remove_mode_symbol_same_s,
        kt_remove_mode_symbol_similar_s,
        kt_remove_mode_symbol_not_s,
        kt_remove_mode_word_different_s,
        kt_remove_mode_word_same_s,
        kt_remove_mode_word_similar_s,
        kt_remove_mode_word_not_s,
      };

      for (i = 0; i < total_locations; i += 2) {

        index = main->program.parameters.array[kt_remove_parameter_mode_e].values.array[i];

        main->setting.modes.array[main->setting.modes.used].type = 0;

        for (j = 0; j < 8; ++j) {

          if (fl_string_dynamic_compare(main->program.parameters.arguments.array[index], strings[j]) == F_equal_to) {
            main->setting.modes.array[main->setting.modes.used].type = enumerations[j];

            index2 = main->program.parameters.array[kt_remove_parameter_mode_e].values.array[i + 1];

            main->setting.modes.array[main->setting.modes.used].mode = kt_remove_get_mode(main, main->program.parameters.arguments.array[index2]);
            if (F_status_is_error(main->setting.state.status)) return;

            ++main->setting.modes.used;

            break;
          }
        } // for

        if (j == 8) {
          main->setting.state.status = F_status_set_error(F_parameter);

          kt_remove_print_error_parameter_unknown_value(&main->program.error, f_console_symbol_long_normal_s, kt_remove_long_mode_s, main->program.parameters.arguments.array[index]);

          return;
        }
      } // for

      main->setting.flag |= kt_remove_main_flag_mode_e;
      main->setting.flag |= kt_remove_main_flag_option_used_e;
    }

    // kt_remove_parameter_user_e, needs additional parameters.
    if (main->program.parameters.array[kt_remove_parameter_user_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      kt_remove_print_error_parameter_missing_value_requires_amount(&main->program.error, f_console_symbol_long_normal_s, kt_remove_long_user_s, 1);

      return;
    }

    if (main->program.parameters.array[kt_remove_parameter_user_e].result & f_console_result_value_e) {
      total_arguments = main->program.parameters.array[kt_remove_parameter_user_e].values.used;

      if (main->program.parameters.array[kt_remove_parameter_user_e].locations.used != total_arguments) {
        main->setting.state.status = F_status_set_error(F_parameter);

        kt_remove_print_error_parameter_missing_value_requires_amount(&main->program.error, f_console_symbol_long_normal_s, kt_remove_long_user_s, 1);

        return;
      }

      main->setting.state.status = f_uint32s_increase_by(total_arguments, &main->setting.users);

      if (F_status_is_error(main->setting.state.status)) {
        kt_remove_print_error(&main->program.error, macro_kt_remove_f(f_uint32s_increase_by));

        return;
      }

      for (i = 0; i < total_arguments; ++i) {

        index = main->program.parameters.array[kt_remove_parameter_user_e].values.array[i];

        main->setting.users.array[main->setting.users.used] = kt_remove_get_id_user(main, main->program.parameters.arguments.array[index]);

        if (F_status_is_error(main->setting.state.status)) {
          kt_remove_print_error(&main->program.error, macro_kt_remove_f(kt_remove_get_id_user));

          return;
        }

        ++main->setting.users.used;
      } // for

      main->setting.flag |= kt_remove_main_flag_user_e;
      main->setting.flag |= kt_remove_main_flag_option_used_e;
    }

    // kt_remove_parameter_prompt_e, needs additional parameters (all, follow, once).
    if (main->program.parameters.array[kt_remove_parameter_prompt_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      kt_remove_print_error_parameter_missing_value_requires_amount(&main->program.error, f_console_symbol_long_normal_s, kt_remove_long_prompt_s, 1);

      return;
    }

    if (main->program.parameters.array[kt_remove_parameter_prompt_e].result & f_console_result_value_e) {
      total_arguments = main->program.parameters.array[kt_remove_parameter_prompt_e].values.used;

      if (main->program.parameters.array[kt_remove_parameter_prompt_e].locations.used != total_arguments) {
        main->setting.state.status = F_status_set_error(F_parameter);

        kt_remove_print_error_parameter_missing_value_requires_amount(&main->program.error, f_console_symbol_long_normal_s, kt_remove_long_prompt_s, 1);

        return;
      }

      index = main->program.parameters.array[kt_remove_parameter_prompt_e].values.array[total_arguments - 1];

      if (fl_string_dynamic_compare(kt_remove_all_s, main->program.parameters.arguments.array[index]) == F_equal_to) {
        main->setting.flag |= kt_remove_main_flag_prompt_all_e;

        if (main->setting.flag & kt_remove_main_flag_prompt_follow_e) {
          main->setting.flag -= kt_remove_main_flag_prompt_follow_e;
        }

        if (main->setting.flag & kt_remove_main_flag_prompt_once_e) {
          main->setting.flag -= kt_remove_main_flag_prompt_once_e;
        }

        if (main->setting.flag & kt_remove_main_flag_prompt_never_e) {
          main->setting.flag -= kt_remove_main_flag_prompt_never_e;
        }
      }
      else if (fl_string_dynamic_compare(kt_remove_follow_s, main->program.parameters.arguments.array[index]) == F_equal_to) {
        main->setting.flag |= kt_remove_main_flag_prompt_follow_e;

        if (main->setting.flag & kt_remove_main_flag_prompt_all_e) {
          main->setting.flag -= kt_remove_main_flag_prompt_all_e;
        }

        if (main->setting.flag & kt_remove_main_flag_prompt_once_e) {
          main->setting.flag -= kt_remove_main_flag_prompt_once_e;
        }

        if (main->setting.flag & kt_remove_main_flag_prompt_never_e) {
          main->setting.flag -= kt_remove_main_flag_prompt_never_e;
        }
      }
      else if (fl_string_dynamic_compare(kt_remove_once_s, main->program.parameters.arguments.array[index]) == F_equal_to) {
        main->setting.flag |= kt_remove_main_flag_prompt_once_e;

        if (main->setting.flag & kt_remove_main_flag_prompt_all_e) {
          main->setting.flag -= kt_remove_main_flag_prompt_all_e;
        }

        if (main->setting.flag & kt_remove_main_flag_prompt_follow_e) {
          main->setting.flag -= kt_remove_main_flag_prompt_follow_e;
        }

        if (main->setting.flag & kt_remove_main_flag_prompt_never_e) {
          main->setting.flag -= kt_remove_main_flag_prompt_never_e;
        }
      }
      else if (fl_string_dynamic_compare(kt_remove_never_s, main->program.parameters.arguments.array[index]) == F_equal_to) {
        main->setting.flag |= kt_remove_main_flag_prompt_never_e;

        if (main->setting.flag & kt_remove_main_flag_prompt_all_e) {
          main->setting.flag -= kt_remove_main_flag_prompt_all_e;
        }

        if (main->setting.flag & kt_remove_main_flag_prompt_follow_e) {
          main->setting.flag -= kt_remove_main_flag_prompt_follow_e;
        }

        if (main->setting.flag & kt_remove_main_flag_prompt_once_e) {
          main->setting.flag -= kt_remove_main_flag_prompt_once_e;
        }
      }
      else {
        main->setting.state.status = F_status_set_error(F_parameter);

        kt_remove_print_error_parameter_unknown_value(&main->program.error, f_console_symbol_long_normal_s, kt_remove_long_prompt_s, main->program.parameters.arguments.array[index]);

        return;
      }
    }

    if (main->program.parameters.array[kt_remove_parameter_utc_e].result & f_console_result_found_e) {

      // Use the right most parameter when both --utc and --local are passed.
      if (main->program.parameters.array[kt_remove_parameter_local_e].result & f_console_result_found_e) {
        const f_array_length_t last_local = main->program.parameters.array[kt_remove_parameter_local_e].locations.array[main->program.parameters.array[kt_remove_parameter_local_e].locations.used];
        const f_array_length_t last_utc = main->program.parameters.array[kt_remove_parameter_utc_e].locations.array[main->program.parameters.array[kt_remove_parameter_utc_e].locations.used];

        if (last_local > kt_remove_parameter_utc_e) {
          if (main->setting.flag & kt_remove_main_flag_utc_e) {
            main->setting.flag -= kt_remove_main_flag_utc_e;
          }
        }
        else {
          main->setting.flag |= kt_remove_main_flag_utc_e;
        }
      }
      else {
        main->setting.flag |= kt_remove_main_flag_utc_e;
      }
    }
    else if (main->program.parameters.array[kt_remove_parameter_local_e].result & f_console_result_found_e) {
      if (main->setting.flag & kt_remove_main_flag_utc_e) {
        main->setting.flag -= kt_remove_main_flag_utc_e;
      }
    }

    // Load all remaining files as static strings (setting size to 0).
    if (main->program.parameters.remaining.used) {
      main->setting.state.status = f_string_dynamics_increase_by(main->program.parameters.remaining.used, &main->setting.files);

      if (F_status_is_error(main->setting.state.status)) {
        kt_remove_print_error(&main->program.error, macro_kt_remove_f(f_string_dynamics_increase_by));

        return;
      }

      for (i = 0; i < main->program.parameters.remaining.used; ++i) {

        index = main->program.parameters.remaining.array[i];

        main->setting.files.array[main->setting.files.used].string = main->program.parameters.arguments.array[index].string;
        main->setting.files.array[main->setting.files.used].used = main->program.parameters.arguments.array[index].used;
        main->setting.files.array[main->setting.files.used++].size = 0;
      } // for
    }
  }
#endif // _di_kt_remove_setting_load_

#ifndef _di_kt_remove_setting_unload_
  f_status_t kt_remove_setting_unload(kt_remove_main_t * const main) {

    if (!main) return F_status_set_error(F_parameter);

    kt_remove_setting_delete(&main->setting);

    return F_none;
  }
#endif // _di_kt_remove_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif
