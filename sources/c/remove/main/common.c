#include "remove.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_remove_program_version_s_
  const f_string_static_t kt_remove_program_version_s = macro_f_string_static_t_initialize(KT_REMOVE_program_version_s, 0, KT_REMOVE_program_version_s_length);
#endif // _di_kt_remove_program_version_s_

#ifndef _di_kt_remove_program_name_s_
  const f_string_static_t kt_remove_program_name_s = macro_f_string_static_t_initialize(KT_REMOVE_program_name_s, 0, KT_REMOVE_program_name_s_length);
  const f_string_static_t kt_remove_program_name_long_s = macro_f_string_static_t_initialize(KT_REMOVE_program_name_long_s, 0, KT_REMOVE_program_name_long_s_length);
#endif // _di_kt_remove_program_name_s_

#ifndef kt_remove_program_help_parameters_s_
  const f_string_static_t kt_remove_program_help_parameters_s = macro_f_string_static_t_initialize(KT_REMOVE_program_help_parameters_s, 0, KT_REMOVE_program_help_parameters_s_length);
#endif // _di_utf8_program_help_parameters_s_

#ifndef _di_kt_remove_date_s_
  const f_string_static_t kt_remove_date_symbol_equal_s = macro_f_string_static_t_initialize(KT_REMOVE_date_symbol_equal_s, 0, KT_REMOVE_date_symbol_equal_s_length);
  const f_string_static_t kt_remove_date_symbol_less_s = macro_f_string_static_t_initialize(KT_REMOVE_date_symbol_less_s, 0, KT_REMOVE_date_symbol_less_s_length);
  const f_string_static_t kt_remove_date_symbol_less_equal_s = macro_f_string_static_t_initialize(KT_REMOVE_date_symbol_less_equal_s, 0, KT_REMOVE_date_symbol_less_equal_s_length);
  const f_string_static_t kt_remove_date_symbol_more_s = macro_f_string_static_t_initialize(KT_REMOVE_date_symbol_more_s, 0, KT_REMOVE_date_symbol_more_s_length);
  const f_string_static_t kt_remove_date_symbol_more_equal_s = macro_f_string_static_t_initialize(KT_REMOVE_date_symbol_more_equal_s, 0, KT_REMOVE_date_symbol_more_equal_s_length);
  const f_string_static_t kt_remove_date_symbol_not_s = macro_f_string_static_t_initialize(KT_REMOVE_date_symbol_not_s, 0, KT_REMOVE_date_symbol_not_s_length);

  const f_string_static_t kt_remove_date_word_equal_s = macro_f_string_static_t_initialize(KT_REMOVE_date_word_equal_s, 0, KT_REMOVE_date_word_equal_s_length);
  const f_string_static_t kt_remove_date_word_less_s = macro_f_string_static_t_initialize(KT_REMOVE_date_word_less_s, 0, KT_REMOVE_date_word_less_s_length);
  const f_string_static_t kt_remove_date_word_less_equal_s = macro_f_string_static_t_initialize(KT_REMOVE_date_word_less_equal_s, 0, KT_REMOVE_date_word_less_equal_s_length);
  const f_string_static_t kt_remove_date_word_more_s = macro_f_string_static_t_initialize(KT_REMOVE_date_word_more_s, 0, KT_REMOVE_date_word_more_s_length);
  const f_string_static_t kt_remove_date_word_more_equal_s = macro_f_string_static_t_initialize(KT_REMOVE_date_word_more_equal_s, 0, KT_REMOVE_date_word_more_equal_s_length);
  const f_string_static_t kt_remove_date_word_not_s = macro_f_string_static_t_initialize(KT_REMOVE_date_word_not_s, 0, KT_REMOVE_date_word_not_s_length);
#endif // _di_kt_remove_date_s_

/**
 * Strings associated with the mode parameters.
 */
#ifndef _di_kt_remove_mode_s_
  const f_string_static_t kt_remove_mode_symbol_different_s = macro_f_string_static_t_initialize(KT_REMOVE_mode_symbol_different_s, 0, KT_REMOVE_mode_symbol_different_s_length);
  const f_string_static_t kt_remove_mode_symbol_same_s = macro_f_string_static_t_initialize(KT_REMOVE_mode_symbol_same_s, 0, KT_REMOVE_mode_symbol_same_s_length);
  const f_string_static_t kt_remove_mode_symbol_similar_s = macro_f_string_static_t_initialize(KT_REMOVE_mode_symbol_similar_s, 0, KT_REMOVE_mode_symbol_similar_s_length);
  const f_string_static_t kt_remove_mode_symbol_not_s = macro_f_string_static_t_initialize(KT_REMOVE_mode_symbol_not_s, 0, KT_REMOVE_mode_symbol_not_s_length);

  const f_string_static_t kt_remove_mode_word_different_s = macro_f_string_static_t_initialize(KT_REMOVE_mode_word_different_s, 0, KT_REMOVE_mode_word_different_s_length);
  const f_string_static_t kt_remove_mode_word_same_s = macro_f_string_static_t_initialize(KT_REMOVE_mode_word_same_s, 0, KT_REMOVE_mode_word_same_s_length);
  const f_string_static_t kt_remove_mode_word_similar_s = macro_f_string_static_t_initialize(KT_REMOVE_mode_word_similar_s, 0, KT_REMOVE_mode_word_similar_s_length);
  const f_string_static_t kt_remove_mode_word_not_s = macro_f_string_static_t_initialize(KT_REMOVE_mode_word_not_s, 0, KT_REMOVE_mode_word_not_s_length);
#endif // _di_kt_remove_mode_s_

#ifndef _di_kt_remove_s_
  const f_string_static_t kt_remove_all_s = macro_f_string_static_t_initialize(KT_REMOVE_all_s, 0, KT_REMOVE_all_s_length);
  const f_string_static_t kt_remove_follow_s = macro_f_string_static_t_initialize(KT_REMOVE_follow_s, 0, KT_REMOVE_follow_s_length);
  const f_string_static_t kt_remove_ignore_s = macro_f_string_static_t_initialize(KT_REMOVE_ignore_s, 0, KT_REMOVE_ignore_s_length);
  const f_string_static_t kt_remove_never_s = macro_f_string_static_t_initialize(KT_REMOVE_never_s, 0, KT_REMOVE_never_s_length);
  const f_string_static_t kt_remove_no_s = macro_f_string_static_t_initialize(KT_REMOVE_no_s, 0, KT_REMOVE_no_s_length);
  const f_string_static_t kt_remove_not_s = macro_f_string_static_t_initialize(KT_REMOVE_not_s, 0, KT_REMOVE_not_s_length);
  const f_string_static_t kt_remove_not_fail_s = macro_f_string_static_t_initialize(KT_REMOVE_not_fail_s, 0, KT_REMOVE_not_fail_s_length);
  const f_string_static_t kt_remove_now_s = macro_f_string_static_t_initialize(KT_REMOVE_now_s, 0, KT_REMOVE_now_s_length);
  const f_string_static_t kt_remove_once_s = macro_f_string_static_t_initialize(KT_REMOVE_once_s, 0, KT_REMOVE_once_s_length);
  const f_string_static_t kt_remove_only_s = macro_f_string_static_t_initialize(KT_REMOVE_only_s, 0, KT_REMOVE_only_s_length);
  const f_string_static_t kt_remove_only_fail_s = macro_f_string_static_t_initialize(KT_REMOVE_only_fail_s, 0, KT_REMOVE_only_fail_s_length);
  const f_string_static_t kt_remove_root_s = macro_f_string_static_t_initialize(KT_REMOVE_root_s, 0, KT_REMOVE_root_s_length);
  const f_string_static_t kt_remove_today_s = macro_f_string_static_t_initialize(KT_REMOVE_today_s, 0, KT_REMOVE_today_s_length);
  const f_string_static_t kt_remove_tomorrow_s = macro_f_string_static_t_initialize(KT_REMOVE_tomorrow_s, 0, KT_REMOVE_tomorrow_s_length);
  const f_string_static_t kt_remove_yes_s = macro_f_string_static_t_initialize(KT_REMOVE_yes_s, 0, KT_REMOVE_yes_s_length);
  const f_string_static_t kt_remove_yesterday_s = macro_f_string_static_t_initialize(KT_REMOVE_yesterday_s, 0, KT_REMOVE_yesterday_s_length);
#endif // _di_kt_remove_s_

#ifndef _di_kt_remove_parameter_d_
  const f_string_static_t kt_remove_short_accessed_s = macro_f_string_static_t_initialize(KT_REMOVE_short_accessed_s, 0, KT_REMOVE_short_accessed_s_length);
  const f_string_static_t kt_remove_short_block_s = macro_f_string_static_t_initialize(KT_REMOVE_short_block_s, 0, KT_REMOVE_short_block_s_length);
  const f_string_static_t kt_remove_short_character_s = macro_f_string_static_t_initialize(KT_REMOVE_short_character_s, 0, KT_REMOVE_short_character_s_length);
  const f_string_static_t kt_remove_short_created_s = macro_f_string_static_t_initialize(KT_REMOVE_short_created_s, 0, KT_REMOVE_short_created_s_length);
  const f_string_static_t kt_remove_short_different_s = macro_f_string_static_t_initialize(KT_REMOVE_short_different_s, 0, KT_REMOVE_short_different_s_length);
  const f_string_static_t kt_remove_short_directory_s = macro_f_string_static_t_initialize(KT_REMOVE_short_directory_s, 0, KT_REMOVE_short_directory_s_length);
  const f_string_static_t kt_remove_short_empty_s = macro_f_string_static_t_initialize(KT_REMOVE_short_empty_s, 0, KT_REMOVE_short_empty_s_length);
  const f_string_static_t kt_remove_short_fifo_s = macro_f_string_static_t_initialize(KT_REMOVE_short_fifo_s, 0, KT_REMOVE_short_fifo_s_length);
  const f_string_static_t kt_remove_short_follow_s = macro_f_string_static_t_initialize(KT_REMOVE_short_follow_s, 0, KT_REMOVE_short_follow_s_length);
  const f_string_static_t kt_remove_short_force_s = macro_f_string_static_t_initialize(KT_REMOVE_short_force_s, 0, KT_REMOVE_short_force_s_length);
  const f_string_static_t kt_remove_short_group_s = macro_f_string_static_t_initialize(KT_REMOVE_short_group_s, 0, KT_REMOVE_short_group_s_length);
  const f_string_static_t kt_remove_short_isolate_s = macro_f_string_static_t_initialize(KT_REMOVE_short_isolate_s, 0, KT_REMOVE_short_isolate_s_length);
  const f_string_static_t kt_remove_short_link_s = macro_f_string_static_t_initialize(KT_REMOVE_short_link_s, 0, KT_REMOVE_short_link_s_length);
  const f_string_static_t kt_remove_short_mode_s = macro_f_string_static_t_initialize(KT_REMOVE_short_mode_s, 0, KT_REMOVE_short_mode_s_length);
  const f_string_static_t kt_remove_short_prompt_s = macro_f_string_static_t_initialize(KT_REMOVE_short_prompt_s, 0, KT_REMOVE_short_prompt_s_length);
  const f_string_static_t kt_remove_short_recurse_s = macro_f_string_static_t_initialize(KT_REMOVE_short_recurse_s, 0, KT_REMOVE_short_recurse_s_length);
  const f_string_static_t kt_remove_short_regular_s = macro_f_string_static_t_initialize(KT_REMOVE_short_regular_s, 0, KT_REMOVE_short_regular_s_length);
  const f_string_static_t kt_remove_short_same_s = macro_f_string_static_t_initialize(KT_REMOVE_short_same_s, 0, KT_REMOVE_short_same_s_length);
  const f_string_static_t kt_remove_short_simulate_s = macro_f_string_static_t_initialize(KT_REMOVE_short_simulate_s, 0, KT_REMOVE_short_simulate_s_length);
  const f_string_static_t kt_remove_short_socket_s = macro_f_string_static_t_initialize(KT_REMOVE_short_socket_s, 0, KT_REMOVE_short_socket_s_length);
  const f_string_static_t kt_remove_short_stay_s = macro_f_string_static_t_initialize(KT_REMOVE_short_stay_s, 0, KT_REMOVE_short_stay_s_length);
  const f_string_static_t kt_remove_short_tree_s = macro_f_string_static_t_initialize(KT_REMOVE_short_tree_s, 0, KT_REMOVE_short_tree_s_length);
  const f_string_static_t kt_remove_short_updated_s = macro_f_string_static_t_initialize(KT_REMOVE_short_updated_s, 0, KT_REMOVE_short_updated_s_length);
  const f_string_static_t kt_remove_short_user_s = macro_f_string_static_t_initialize(KT_REMOVE_short_user_s, 0, KT_REMOVE_short_user_s_length);

  const f_string_static_t kt_remove_long_accessed_s = macro_f_string_static_t_initialize(KT_REMOVE_long_accessed_s, 0, KT_REMOVE_long_accessed_s_length);
  const f_string_static_t kt_remove_long_block_s = macro_f_string_static_t_initialize(KT_REMOVE_long_block_s, 0, KT_REMOVE_long_block_s_length);
  const f_string_static_t kt_remove_long_character_s = macro_f_string_static_t_initialize(KT_REMOVE_long_character_s, 0, KT_REMOVE_long_character_s_length);
  const f_string_static_t kt_remove_long_created_s = macro_f_string_static_t_initialize(KT_REMOVE_long_created_s, 0, KT_REMOVE_long_created_s_length);
  const f_string_static_t kt_remove_long_different_s = macro_f_string_static_t_initialize(KT_REMOVE_long_different_s, 0, KT_REMOVE_long_different_s_length);
  const f_string_static_t kt_remove_long_directory_s = macro_f_string_static_t_initialize(KT_REMOVE_long_directory_s, 0, KT_REMOVE_long_directory_s_length);
  const f_string_static_t kt_remove_long_empty_s = macro_f_string_static_t_initialize(KT_REMOVE_long_empty_s, 0, KT_REMOVE_long_empty_s_length);
  const f_string_static_t kt_remove_long_fifo_s = macro_f_string_static_t_initialize(KT_REMOVE_long_fifo_s, 0, KT_REMOVE_long_fifo_s_length);
  const f_string_static_t kt_remove_long_follow_s = macro_f_string_static_t_initialize(KT_REMOVE_long_follow_s, 0, KT_REMOVE_long_follow_s_length);
  const f_string_static_t kt_remove_long_force_s = macro_f_string_static_t_initialize(KT_REMOVE_long_force_s, 0, KT_REMOVE_long_force_s_length);
  const f_string_static_t kt_remove_long_group_s = macro_f_string_static_t_initialize(KT_REMOVE_long_group_s, 0, KT_REMOVE_long_group_s_length);
  const f_string_static_t kt_remove_long_isolate_s = macro_f_string_static_t_initialize(KT_REMOVE_long_isolate_s, 0, KT_REMOVE_long_isolate_s_length);
  const f_string_static_t kt_remove_long_link_s = macro_f_string_static_t_initialize(KT_REMOVE_long_link_s, 0, KT_REMOVE_long_link_s_length);
  const f_string_static_t kt_remove_long_local_s = macro_f_string_static_t_initialize(KT_REMOVE_long_local_s, 0, KT_REMOVE_long_local_s_length);
  const f_string_static_t kt_remove_long_mode_s = macro_f_string_static_t_initialize(KT_REMOVE_long_mode_s, 0, KT_REMOVE_long_mode_s_length);
  const f_string_static_t kt_remove_long_prompt_s = macro_f_string_static_t_initialize(KT_REMOVE_long_prompt_s, 0, KT_REMOVE_long_prompt_s_length);
  const f_string_static_t kt_remove_long_recurse_s = macro_f_string_static_t_initialize(KT_REMOVE_long_recurse_s, 0, KT_REMOVE_long_recurse_s_length);
  const f_string_static_t kt_remove_long_regular_s = macro_f_string_static_t_initialize(KT_REMOVE_long_regular_s, 0, KT_REMOVE_long_regular_s_length);
  const f_string_static_t kt_remove_long_same_s = macro_f_string_static_t_initialize(KT_REMOVE_long_same_s, 0, KT_REMOVE_long_same_s_length);
  const f_string_static_t kt_remove_long_simulate_s = macro_f_string_static_t_initialize(KT_REMOVE_long_simulate_s, 0, KT_REMOVE_long_simulate_s_length);
  const f_string_static_t kt_remove_long_socket_s = macro_f_string_static_t_initialize(KT_REMOVE_long_socket_s, 0, KT_REMOVE_long_socket_s_length);
  const f_string_static_t kt_remove_long_stay_s = macro_f_string_static_t_initialize(KT_REMOVE_long_stay_s, 0, KT_REMOVE_long_stay_s_length);
  const f_string_static_t kt_remove_long_tree_s = macro_f_string_static_t_initialize(KT_REMOVE_long_tree_s, 0, KT_REMOVE_long_tree_s_length);
  const f_string_static_t kt_remove_long_updated_s = macro_f_string_static_t_initialize(KT_REMOVE_long_updated_s, 0, KT_REMOVE_long_updated_s_length);
  const f_string_static_t kt_remove_long_user_s = macro_f_string_static_t_initialize(KT_REMOVE_long_user_s, 0, KT_REMOVE_long_user_s_length);
  const f_string_static_t kt_remove_long_utc_s = macro_f_string_static_t_initialize(KT_REMOVE_long_utc_s, 0, KT_REMOVE_long_utc_s_length);
#endif // _di_kt_remove_parameter_d_

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
  void kt_remove_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, kt_remove_setting_t * const setting) {

    if (!main || !setting) return;

    setting->flag -= setting->flag & kt_remove_flag_option_used_e;

    // Identify priority of color parameters.
    {
      f_console_parameter_id_t ids[3] = { kt_remove_parameter_no_color_e, kt_remove_parameter_light_e, kt_remove_parameter_dark_e };
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 3);

      setting->status = fll_program_parameter_process(arguments, &main->parameters, choices, F_true, &main->context);

      main->output.set = &main->context.set;
      main->error.set = &main->context.set;
      main->warning.set = &main->context.set;

      if (main->context.set.error.before) {
        main->output.context = f_color_set_empty_s;
        main->output.notable = main->context.set.notable;

        main->error.context = main->context.set.error;
        main->error.notable = main->context.set.notable;

        main->warning.context = main->context.set.warning;
        main->warning.notable = main->context.set.notable;
      }
      else {
        f_color_set_t *sets[] = { &main->output.context, &main->output.notable, &main->error.context, &main->error.notable, &main->warning.context, &main->warning.notable, 0 };

        fll_program_parameter_process_empty(&main->context, sets);
      }

      if (F_status_is_error(setting->status)) {
        kt_remove_print_error(setting, main->error, macro_kt_remove_f(fll_program_parameter_process_empty));

        return;
      }
    }

    // Identify priority of verbosity related parameters.
    {
      f_console_parameter_id_t ids[5] = { kt_remove_parameter_verbosity_quiet_e, kt_remove_parameter_verbosity_error_e, kt_remove_parameter_verbosity_normal_e, kt_remove_parameter_verbosity_verbose_e, kt_remove_parameter_verbosity_debug_e };
      f_console_parameter_id_t choice = 0;
      const f_console_parameter_ids_t choices = macro_f_console_parameter_ids_t_initialize(ids, 5);

      setting->status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

      if (F_status_is_error(setting->status)) {
        kt_remove_print_error(setting, main->error, macro_kt_remove_f(f_console_parameter_prioritize_right));

        return;
      }

      if (choice == kt_remove_parameter_verbosity_quiet_e) {
        main->output.verbosity = f_console_verbosity_quiet_e;
        main->error.verbosity = f_console_verbosity_quiet_e;
        main->warning.verbosity = f_console_verbosity_quiet_e;
      }
      else if (choice == kt_remove_parameter_verbosity_error_e) {
        main->output.verbosity = f_console_verbosity_error_e;
        main->error.verbosity = f_console_verbosity_error_e;
        main->warning.verbosity = f_console_verbosity_error_e;
      }
      else if (choice == kt_remove_parameter_verbosity_normal_e) {
        main->output.verbosity = f_console_verbosity_normal_e;
        main->error.verbosity = f_console_verbosity_normal_e;
        main->warning.verbosity = f_console_verbosity_normal_e;
      }
      else if (choice == kt_remove_parameter_verbosity_verbose_e) {
        main->output.verbosity = f_console_verbosity_verbose_e;
        main->error.verbosity = f_console_verbosity_verbose_e;
        main->warning.verbosity = f_console_verbosity_verbose_e;
      }
      else if (choice == kt_remove_parameter_verbosity_debug_e) {
        main->output.verbosity = f_console_verbosity_debug_e;
        main->error.verbosity = f_console_verbosity_debug_e;
        main->warning.verbosity = f_console_verbosity_debug_e;
      }
    }

    main->output.to.id = F_type_descriptor_output_d;
    main->output.to.stream = F_type_output_d;
    main->output.to.flag = F_file_flag_create_d | F_file_flag_write_only_d | F_file_flag_append_d;

    f_array_length_t i = 0;
    f_array_length_t index = 0;
    f_array_length_t index2 = 0;
    f_array_length_t total_locations = 0;
    f_array_length_t total_arguments = 0;

    uint8_t j = 0;

    if (main->parameters.array[kt_remove_parameter_help_e].result == f_console_result_found_e) {
      setting->flag |= kt_remove_flag_help_e;
    }

    if (main->parameters.array[kt_remove_parameter_version_e].result == f_console_result_found_e) {
      setting->flag |= kt_remove_flag_version_e;
    }

    if (main->parameters.array[kt_remove_parameter_block_e].result == f_console_result_found_e) {
      setting->flag |= kt_remove_flag_block_e;
      setting->flag |= kt_remove_flag_option_used_e;
    }

    if (main->parameters.array[kt_remove_parameter_character_e].result == f_console_result_found_e) {
      setting->flag |= kt_remove_flag_character_e;
      setting->flag |= kt_remove_flag_option_used_e;
    }

    if (main->parameters.array[kt_remove_parameter_different_e].result == f_console_result_found_e) {
      if (main->parameters.array[kt_remove_parameter_same_e].result == f_console_result_found_e) {
        index = main->parameters.array[kt_remove_parameter_different_e].locations.used;
        index2 = main->parameters.array[kt_remove_parameter_same_e].locations.used;

        if (main->parameters.array[kt_remove_parameter_different_e].locations.array[index] > main->parameters.array[kt_remove_parameter_same_e].locations.array[index2]) {
          setting->flag |= kt_remove_flag_different_e;

          if (setting->flag & kt_remove_flag_same_e) {
            setting->flag -= kt_remove_flag_same_e;
          }
        }
        else {
          setting->flag |= kt_remove_flag_same_e;

          if (setting->flag & kt_remove_flag_different_e) {
            setting->flag -= kt_remove_flag_different_e;
          }
        }
      }
      else {
        setting->flag |= kt_remove_flag_different_e;

        if (setting->flag & kt_remove_flag_same_e) {
          setting->flag -= kt_remove_flag_same_e;
        }
      }

      setting->flag |= kt_remove_flag_option_used_e;
    }
    else if (main->parameters.array[kt_remove_parameter_same_e].result == f_console_result_found_e) {
      setting->flag |= kt_remove_flag_same_e;

      if (setting->flag & kt_remove_flag_different_e) {
        setting->flag -= kt_remove_flag_different_e;
      }

      setting->flag |= kt_remove_flag_option_used_e;
    }

    if (main->parameters.array[kt_remove_parameter_fifo_e].result == f_console_result_found_e) {
      setting->flag |= kt_remove_flag_fifo_e;
      setting->flag |= kt_remove_flag_option_used_e;
    }

    if (main->parameters.array[kt_remove_parameter_follow_e].result == f_console_result_found_e) {
      if (main->parameters.array[kt_remove_parameter_stay_e].result == f_console_result_found_e) {
        index = main->parameters.array[kt_remove_parameter_follow_e].locations.used;
        index2 = main->parameters.array[kt_remove_parameter_stay_e].locations.used;

        if (main->parameters.array[kt_remove_parameter_follow_e].locations.array[index] > main->parameters.array[kt_remove_parameter_stay_e].locations.array[index2]) {
          setting->flag |= kt_remove_flag_follow_e;
        }
        else {
          if (setting->flag & kt_remove_flag_follow_e) {
            setting->flag -= kt_remove_flag_follow_e;
          }
        }
      }
      else {
        setting->flag |= kt_remove_flag_follow_e;
      }
    }
    else if (main->parameters.array[kt_remove_parameter_stay_e].result == f_console_result_found_e) {
      if (setting->flag & kt_remove_flag_follow_e) {
        setting->flag -= kt_remove_flag_follow_e;
      }
    }

    if (main->parameters.array[kt_remove_parameter_force_e].result == f_console_result_found_e) {
      setting->flag |= kt_remove_flag_force_e;
    }

    if (main->parameters.array[kt_remove_parameter_link_e].result == f_console_result_found_e) {
      setting->flag |= kt_remove_flag_link_e;
      setting->flag |= kt_remove_flag_option_used_e;
    }

    if (main->parameters.array[kt_remove_parameter_recurse_e].result == f_console_result_found_e) {
      setting->flag |= kt_remove_flag_recurse_e;
    }

    if (main->parameters.array[kt_remove_parameter_regular_e].result == f_console_result_found_e) {
      setting->flag |= kt_remove_flag_regular_e;
      setting->flag |= kt_remove_flag_option_used_e;
    }

    if (main->parameters.array[kt_remove_parameter_simulate_e].result == f_console_result_found_e) {
      setting->flag |= kt_remove_flag_simulate_e;
    }

    if (main->parameters.array[kt_remove_parameter_socket_e].result == f_console_result_found_e) {
      setting->flag |= kt_remove_flag_socket_e;
      setting->flag |= kt_remove_flag_option_used_e;
    }

    if (main->parameters.array[kt_remove_parameter_tree_e].result == f_console_result_found_e) {
      setting->flag |= kt_remove_flag_tree_e;
    }

    {
      f_console_parameter_t * const parameters[] = {
        &main->parameters.array[kt_remove_parameter_accessed_e],
        &main->parameters.array[kt_remove_parameter_created_e],
        &main->parameters.array[kt_remove_parameter_updated_e],
      };

      kt_remove_dates_t * const dates[] = {
        &setting->accessed,
        &setting->created,
        &setting->updated,
      };

      const f_string_static_t longs[] = {
        kt_remove_long_accessed_s,
        kt_remove_long_created_s,
        kt_remove_long_updated_s,
      };

      for (uint8_t p = 0; p < 3; ++p) {

        // kt_remove_parameter_accessed_e, kt_remove_parameter_created_e, kt_remove_parameter_updated_e, needs additional parameters, ==, <, <=, >, >=, <>.
        if (parameters[p]->result == f_console_result_found_e) {
          setting->status = F_status_set_error(F_parameter);

          kt_remove_print_error_parameter_missing_value_requires_amount(main->error, f_console_symbol_long_enable_s, longs[p], 2);

          return;
        }

        if (parameters[p]->result == f_console_result_additional_e) {
          total_locations = parameters[p]->locations.used;
          total_arguments = parameters[p]->values.used;

          if (total_locations * 2 != total_arguments) {
            setting->status = F_status_set_error(F_parameter);

            kt_remove_print_error_parameter_missing_value_requires_amount(main->error, f_console_symbol_long_enable_s, longs[p], 2);

            return;
          }

          if (dates[p]->used + total_locations > dates[p]->size) {
            setting->status = kt_remove_dates_resize(dates[p]->size + (total_locations - dates[p]->size), dates[p]);

            if (F_status_is_error(setting->status)) {
              kt_remove_print_error(setting, main->error, macro_kt_remove_f(kt_remove_dates_resize));

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

          setting->status = F_known_not;

          {
            for (i = 0; i < total_arguments; i += 2) {

              index = parameters[p]->values.array[i];
              dates[p]->array[dates[p]->used].operation = 0;
              dates[p]->array[dates[p]->used].type = 0;

              for (j = 0; j < 12; ++j) {

                if (fl_string_dynamic_compare(main->parameters.arguments.array[index], strings[j]) == F_equal_to) {
                  dates[p]->array[dates[p]->used].operation = enumerations[j];

                  index2 = parameters[p]->values.array[i + 1];

                  kt_remove_get_date(main, setting, main->parameters.arguments.array[index2], &dates[p]->array[dates[p]->used].type);
                  if (F_status_is_error(setting->status)) return;

                  ++dates[p]->used;

                  break;
                }
              } // for

              if (j == 12) {
                setting->status = F_status_set_error(F_parameter);

                kt_remove_print_error_parameter_unknown_value(main->error, f_console_symbol_long_enable_s, longs[p], main->parameters.arguments.array[index]);

                return;
              }
            } // for
          }

          setting->flag |= kt_remove_flag_option_used_e;
        } // for
      }
    }

    // kt_remove_parameter_group_e, needs additional parameters (group).
    if (main->parameters.array[kt_remove_parameter_empty_e].result == f_console_result_found_e) {
      setting->status = F_status_set_error(F_parameter);

      kt_remove_print_error_parameter_missing_value_requires_amount(main->error, f_console_symbol_long_enable_s, kt_remove_long_empty_s, 1);

      return;
    }

    if (main->parameters.array[kt_remove_parameter_empty_e].result == f_console_result_additional_e) {
      total_arguments = main->parameters.array[kt_remove_parameter_empty_e].values.used;

      if (main->parameters.array[kt_remove_parameter_empty_e].locations.used != total_arguments) {
        setting->status = F_status_set_error(F_parameter);

        kt_remove_print_error_parameter_missing_value_requires_amount(main->error, f_console_symbol_long_enable_s, kt_remove_long_empty_s, 1);

        return;
      }

      index = main->parameters.array[kt_remove_parameter_empty_e].values.array[total_arguments - 1];

      if (fl_string_dynamic_compare(kt_remove_not_s, main->parameters.arguments.array[index]) == F_equal_to) {
        setting->flag |= kt_remove_flag_empty_not_e;

        if (setting->flag & kt_remove_flag_empty_not_fail_e) {
          setting->flag -= kt_remove_flag_empty_not_fail_e;
        }

        if (setting->flag & kt_remove_flag_empty_only_e) {
          setting->flag -= kt_remove_flag_empty_only_e;
        }

        if (setting->flag & kt_remove_flag_empty_only_fail_e) {
          setting->flag -= kt_remove_flag_empty_only_fail_e;
        }
      }
      else if (fl_string_dynamic_compare(kt_remove_not_fail_s, main->parameters.arguments.array[index]) == F_equal_to) {
        setting->flag |= kt_remove_flag_empty_not_fail_e;

        if (setting->flag & kt_remove_flag_empty_not_e) {
          setting->flag -= kt_remove_flag_empty_not_e;
        }

        if (setting->flag & kt_remove_flag_empty_only_e) {
          setting->flag -= kt_remove_flag_empty_only_e;
        }

        if (setting->flag & kt_remove_flag_empty_only_fail_e) {
          setting->flag -= kt_remove_flag_empty_only_fail_e;
        }
      }
      else if (fl_string_dynamic_compare(kt_remove_only_s, main->parameters.arguments.array[index]) == F_equal_to) {
        setting->flag |= kt_remove_flag_empty_only_e;

        if (setting->flag & kt_remove_flag_empty_not_e) {
          setting->flag -= kt_remove_flag_empty_not_e;
        }

        if (setting->flag & kt_remove_flag_empty_not_fail_e) {
          setting->flag -= kt_remove_flag_empty_not_fail_e;
        }

        if (setting->flag & kt_remove_flag_empty_only_fail_e) {
          setting->flag -= kt_remove_flag_empty_only_fail_e;
        }
      }
      else if (fl_string_dynamic_compare(kt_remove_only_fail_s, main->parameters.arguments.array[index]) == F_equal_to) {
        setting->flag |= kt_remove_flag_empty_only_fail_e;

        if (setting->flag & kt_remove_flag_empty_not_e) {
          setting->flag -= kt_remove_flag_empty_not_e;
        }

        if (setting->flag & kt_remove_flag_empty_not_fail_e) {
          setting->flag -= kt_remove_flag_empty_not_fail_e;
        }

        if (setting->flag & kt_remove_flag_empty_only_e) {
          setting->flag -= kt_remove_flag_empty_only_e;
        }
      }
      else {
        setting->status = F_status_set_error(F_parameter);

        kt_remove_print_error_parameter_unknown_value(main->error, f_console_symbol_long_enable_s, kt_remove_long_empty_s, main->parameters.arguments.array[index]);

        return;
      }

      setting->flag |= kt_remove_flag_option_used_e;
    }

    // kt_remove_parameter_group_e, needs additional parameters (gid).
    if (main->parameters.array[kt_remove_parameter_group_e].result == f_console_result_found_e) {
      setting->status = F_status_set_error(F_parameter);

      kt_remove_print_error_parameter_missing_value_requires_amount(main->error, f_console_symbol_long_enable_s, kt_remove_long_group_s, 1);

      return;
    }

    if (main->parameters.array[kt_remove_parameter_group_e].result == f_console_result_additional_e) {
      total_arguments = main->parameters.array[kt_remove_parameter_group_e].values.used;

      if (main->parameters.array[kt_remove_parameter_group_e].locations.used != total_arguments) {
        setting->status = F_status_set_error(F_parameter);

        kt_remove_print_error_parameter_missing_value_requires_amount(main->error, f_console_symbol_long_enable_s, kt_remove_long_group_s, 1);

        return;
      }

      setting->status = f_uint32s_increase_by(total_arguments, &setting->groups);

      if (F_status_is_error(setting->status)) {
        kt_remove_print_error(setting, main->error, macro_kt_remove_f(f_uint32s_increase_by));

        return;
      }

      for (i = 0; i < total_arguments; ++i) {

        index = main->parameters.array[kt_remove_parameter_group_e].values.array[i];

        setting->groups.array[setting->groups.used] = kt_remove_get_id_group(setting, main->parameters.arguments.array[index]);

        if (F_status_is_error(setting->status)) {
          kt_remove_print_error(setting, main->error, macro_kt_remove_f(kt_remove_get_id_group));

          return;
        }

        ++setting->groups.used;
      } // for

      setting->flag |= kt_remove_flag_group_e;
      setting->flag |= kt_remove_flag_option_used_e;
    }

    // kt_remove_parameter_isolate_e, needs additional parameters (all, ignore, or root).
    if (main->parameters.array[kt_remove_parameter_isolate_e].result == f_console_result_found_e) {
      setting->status = F_status_set_error(F_parameter);

      kt_remove_print_error_parameter_missing_value_requires_amount(main->error, f_console_symbol_long_enable_s, kt_remove_long_isolate_s, 1);

      return;
    }

    if (main->parameters.array[kt_remove_parameter_isolate_e].result == f_console_result_additional_e) {
      total_arguments = main->parameters.array[kt_remove_parameter_isolate_e].values.used;

      if (main->parameters.array[kt_remove_parameter_isolate_e].locations.used != total_arguments) {
        setting->status = F_status_set_error(F_parameter);

        kt_remove_print_error_parameter_missing_value_requires_amount(main->error, f_console_symbol_long_enable_s, kt_remove_long_isolate_s, 1);

        return;
      }

      index = main->parameters.array[kt_remove_parameter_isolate_e].values.array[total_arguments - 1];

      if (fl_string_dynamic_compare(kt_remove_all_s, main->parameters.arguments.array[index]) == F_equal_to) {
        setting->flag |= kt_remove_flag_isolate_all_e;

        if (setting->flag & kt_remove_flag_isolate_ignore_e) {
          setting->flag -= kt_remove_flag_isolate_ignore_e;
        }

        if (setting->flag & kt_remove_flag_isolate_root_e) {
          setting->flag -= kt_remove_flag_isolate_root_e;
        }
      }
      else if (fl_string_dynamic_compare(kt_remove_ignore_s, main->parameters.arguments.array[index]) == F_equal_to) {
        setting->flag |= kt_remove_flag_isolate_ignore_e;

        if (setting->flag & kt_remove_flag_isolate_all_e) {
          setting->flag -= kt_remove_flag_isolate_all_e;
        }

        if (setting->flag & kt_remove_flag_isolate_root_e) {
          setting->flag -= kt_remove_flag_isolate_root_e;
        }
      }
      else if (fl_string_dynamic_compare(kt_remove_root_s, main->parameters.arguments.array[index]) == F_equal_to) {
        setting->flag |= kt_remove_flag_isolate_root_e;

        if (setting->flag & kt_remove_flag_isolate_all_e) {
          setting->flag -= kt_remove_flag_isolate_all_e;
        }

        if (setting->flag & kt_remove_flag_isolate_ignore_e) {
          setting->flag -= kt_remove_flag_isolate_ignore_e;
        }
      }
      else {
        setting->status = F_status_set_error(F_parameter);

        kt_remove_print_error_parameter_unknown_value(main->error, f_console_symbol_long_enable_s, kt_remove_long_isolate_s, main->parameters.arguments.array[index]);

        return;
      }
    }

    // kt_remove_parameter_mode_e, needs additional parameters (modes, match parameters).
    if (main->parameters.array[kt_remove_parameter_mode_e].result == f_console_result_found_e) {
      setting->status = F_status_set_error(F_parameter);

      kt_remove_print_error_parameter_missing_value_requires_amount(main->error, f_console_symbol_long_enable_s, kt_remove_long_mode_s, 2);

      return;
    }

    if (main->parameters.array[kt_remove_parameter_mode_e].result == f_console_result_additional_e) {
      total_locations = main->parameters.array[kt_remove_parameter_mode_e].locations.used;
      total_arguments = main->parameters.array[kt_remove_parameter_mode_e].values.used;

      if (total_locations * 2 != total_arguments) {
        setting->status = F_status_set_error(F_parameter);

        kt_remove_print_error_parameter_missing_value_requires_amount(main->error, f_console_symbol_long_enable_s, kt_remove_long_mode_s, 2);

        return;
      }

      if (setting->modes.used + total_locations > setting->modes.size) {
        setting->status = kt_remove_modes_resize(setting->modes.size + (total_locations - setting->modes.size), &setting->modes);

        if (F_status_is_error(setting->status)) {
          kt_remove_print_error(setting, main->error, macro_kt_remove_f(kt_remove_modes_resize));

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

        index = main->parameters.array[kt_remove_parameter_mode_e].values.array[i];

        setting->modes.array[setting->modes.used].type = 0;

        for (j = 0; j < 8; ++j) {

          if (fl_string_dynamic_compare(main->parameters.arguments.array[index], strings[j]) == F_equal_to) {
            setting->modes.array[setting->modes.used].type = enumerations[j];

            index2 = main->parameters.array[kt_remove_parameter_mode_e].values.array[i + 1];

            setting->modes.array[setting->modes.used].mode = kt_remove_get_mode(main, setting, main->parameters.arguments.array[index2]);
            if (F_status_is_error(setting->status)) return;

            ++setting->modes.used;

            break;
          }
        } // for

        if (j == 8) {
          setting->status = F_status_set_error(F_parameter);

          kt_remove_print_error_parameter_unknown_value(main->error, f_console_symbol_long_enable_s, kt_remove_long_mode_s, main->parameters.arguments.array[index]);

          return;
        }
      } // for

      setting->flag |= kt_remove_flag_mode_e;
      setting->flag |= kt_remove_flag_option_used_e;
    }

    // kt_remove_parameter_user_e, needs additional parameters.
    if (main->parameters.array[kt_remove_parameter_user_e].result == f_console_result_found_e) {
      setting->status = F_status_set_error(F_parameter);

      kt_remove_print_error_parameter_missing_value_requires_amount(main->error, f_console_symbol_long_enable_s, kt_remove_long_user_s, 1);

      return;
    }

    if (main->parameters.array[kt_remove_parameter_user_e].result == f_console_result_additional_e) {
      total_arguments = main->parameters.array[kt_remove_parameter_user_e].values.used;

      if (main->parameters.array[kt_remove_parameter_user_e].locations.used != total_arguments) {
        setting->status = F_status_set_error(F_parameter);

        kt_remove_print_error_parameter_missing_value_requires_amount(main->error, f_console_symbol_long_enable_s, kt_remove_long_user_s, 1);

        return;
      }

      setting->status = f_uint32s_increase_by(total_arguments, &setting->users);

      if (F_status_is_error(setting->status)) {
        kt_remove_print_error(setting, main->error, macro_kt_remove_f(f_uint32s_increase_by));

        return;
      }

      for (i = 0; i < total_arguments; ++i) {

        index = main->parameters.array[kt_remove_parameter_user_e].values.array[i];

        setting->users.array[setting->users.used] = kt_remove_get_id_user(setting, main->parameters.arguments.array[index]);

        if (F_status_is_error(setting->status)) {
          kt_remove_print_error(setting, main->error, macro_kt_remove_f(kt_remove_get_id_user));

          return;
        }

        ++setting->users.used;
      } // for

      setting->flag |= kt_remove_flag_user_e;
      setting->flag |= kt_remove_flag_option_used_e;
    }

    // kt_remove_parameter_prompt_e, needs additional parameters (all, follow, once).
    if (main->parameters.array[kt_remove_parameter_prompt_e].result == f_console_result_found_e) {
      setting->status = F_status_set_error(F_parameter);

      kt_remove_print_error_parameter_missing_value_requires_amount(main->error, f_console_symbol_long_enable_s, kt_remove_long_prompt_s, 1);

      return;
    }

    if (main->parameters.array[kt_remove_parameter_prompt_e].result == f_console_result_additional_e) {
      total_arguments = main->parameters.array[kt_remove_parameter_prompt_e].values.used;

      if (main->parameters.array[kt_remove_parameter_prompt_e].locations.used != total_arguments) {
        setting->status = F_status_set_error(F_parameter);

        kt_remove_print_error_parameter_missing_value_requires_amount(main->error, f_console_symbol_long_enable_s, kt_remove_long_prompt_s, 1);

        return;
      }

      index = main->parameters.array[kt_remove_parameter_prompt_e].values.array[total_arguments - 1];

      if (fl_string_dynamic_compare(kt_remove_all_s, main->parameters.arguments.array[index]) == F_equal_to) {
        setting->flag |= kt_remove_flag_prompt_all_e;

        if (setting->flag & kt_remove_flag_prompt_follow_e) {
          setting->flag -= kt_remove_flag_prompt_follow_e;
        }

        if (setting->flag & kt_remove_flag_prompt_once_e) {
          setting->flag -= kt_remove_flag_prompt_once_e;
        }

        if (setting->flag & kt_remove_flag_prompt_never_e) {
          setting->flag -= kt_remove_flag_prompt_never_e;
        }
      }
      else if (fl_string_dynamic_compare(kt_remove_follow_s, main->parameters.arguments.array[index]) == F_equal_to) {
        setting->flag |= kt_remove_flag_prompt_follow_e;

        if (setting->flag & kt_remove_flag_prompt_all_e) {
          setting->flag -= kt_remove_flag_prompt_all_e;
        }

        if (setting->flag & kt_remove_flag_prompt_once_e) {
          setting->flag -= kt_remove_flag_prompt_once_e;
        }

        if (setting->flag & kt_remove_flag_prompt_never_e) {
          setting->flag -= kt_remove_flag_prompt_never_e;
        }
      }
      else if (fl_string_dynamic_compare(kt_remove_once_s, main->parameters.arguments.array[index]) == F_equal_to) {
        setting->flag |= kt_remove_flag_prompt_once_e;

        if (setting->flag & kt_remove_flag_prompt_all_e) {
          setting->flag -= kt_remove_flag_prompt_all_e;
        }

        if (setting->flag & kt_remove_flag_prompt_follow_e) {
          setting->flag -= kt_remove_flag_prompt_follow_e;
        }

        if (setting->flag & kt_remove_flag_prompt_never_e) {
          setting->flag -= kt_remove_flag_prompt_never_e;
        }
      }
      else if (fl_string_dynamic_compare(kt_remove_never_s, main->parameters.arguments.array[index]) == F_equal_to) {
        setting->flag |= kt_remove_flag_prompt_never_e;

        if (setting->flag & kt_remove_flag_prompt_all_e) {
          setting->flag -= kt_remove_flag_prompt_all_e;
        }

        if (setting->flag & kt_remove_flag_prompt_follow_e) {
          setting->flag -= kt_remove_flag_prompt_follow_e;
        }

        if (setting->flag & kt_remove_flag_prompt_once_e) {
          setting->flag -= kt_remove_flag_prompt_once_e;
        }
      }
      else {
        setting->status = F_status_set_error(F_parameter);

        kt_remove_print_error_parameter_unknown_value(main->error, f_console_symbol_long_enable_s, kt_remove_long_prompt_s, main->parameters.arguments.array[index]);

        return;
      }
    }

    if (main->parameters.array[kt_remove_parameter_utc_e].result == f_console_result_found_e) {

      // Use the right most parameter when both --utc and --local are passed.
      if (main->parameters.array[kt_remove_parameter_local_e].result == f_console_result_found_e) {
        const f_array_length_t last_local = main->parameters.array[kt_remove_parameter_local_e].locations.array[main->parameters.array[kt_remove_parameter_local_e].locations.used];
        const f_array_length_t last_utc = main->parameters.array[kt_remove_parameter_utc_e].locations.array[main->parameters.array[kt_remove_parameter_utc_e].locations.used];

        if (last_local > kt_remove_parameter_utc_e) {
          if (setting->flag & kt_remove_flag_utc_e) {
            setting->flag -= kt_remove_flag_utc_e;
          }
        }
        else {
          setting->flag |= kt_remove_flag_utc_e;
        }
      }
      else {
        setting->flag |= kt_remove_flag_utc_e;
      }
    }
    else if (main->parameters.array[kt_remove_parameter_local_e].result == f_console_result_found_e) {
      if (setting->flag & kt_remove_flag_utc_e) {
        setting->flag -= kt_remove_flag_utc_e;
      }
    }

    // Load all remaining files as static strings (setting size to 0).
    if (main->parameters.remaining.used) {
      setting->status = f_string_dynamics_increase_by(main->parameters.remaining.used, &setting->files);

      if (F_status_is_error(setting->status)) {
        kt_remove_print_error(setting, main->error, macro_kt_remove_f(f_string_dynamics_increase_by));

        return;
      }

      for (i = 0; i < main->parameters.remaining.used; ++i) {

        index = main->parameters.remaining.array[i];

        setting->files.array[setting->files.used].string = main->parameters.arguments.array[index].string;
        setting->files.array[setting->files.used].used = main->parameters.arguments.array[index].used;
        setting->files.array[setting->files.used++].size = 0;
      } // for
    }
  }
#endif // _di_kt_remove_setting_load_

#ifndef _di_kt_remove_setting_unload_
  f_status_t kt_remove_setting_unload(fll_program_data_t * const main, kt_remove_setting_t * const setting) {

    if (!main || !setting) return F_status_set_error(F_parameter);

    kt_remove_setting_delete(setting);

    return F_none;
  }
#endif // _di_kt_remove_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif
