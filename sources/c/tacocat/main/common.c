#include "tacocat.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_tacocat_setting_load_
  void kt_tacocat_setting_load(const f_console_arguments_t arguments, kt_tacocat_main_t * const main) {

    if (!main) return;

    main->setting.state.step_small = kt_tacocat_allocation_console_d;

    f_console_parameter_process(arguments, &main->program.parameters, &main->setting.state, 0);

    main->setting.state.step_small = kt_tacocat_allocation_small_d;


    // Identify and pocess first/last parameters.
    if (main->program.parameters.array[kt_tacocat_parameter_line_first_no_e].result & f_console_result_found_e) {
      main->setting.flag -= main->setting.flag & kt_tacocat_main_flag_print_first_e;
    }
    else {
      main->setting.flag |= kt_tacocat_main_flag_print_first_e;
    }

    if (main->program.parameters.array[kt_tacocat_parameter_line_last_no_e].result & f_console_result_found_e) {
      main->setting.flag -= main->setting.flag & kt_tacocat_main_flag_print_last_e;
    }
    else {
      main->setting.flag |= kt_tacocat_main_flag_print_last_e;
    }

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & kt_tacocat_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(f_console_parameter_process));

      return;
    }

   {
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { kt_tacocat_parameter_no_color_e, kt_tacocat_parameter_light_e, kt_tacocat_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        main->setting.state.status = fll_program_parameter_process_context(choices, modes, F_true, &main->program);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & kt_tacocat_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(fll_program_parameter_process_context));

          return;
        }
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { kt_tacocat_parameter_verbosity_quiet_e, kt_tacocat_parameter_verbosity_error_e, kt_tacocat_parameter_verbosity_verbose_e, kt_tacocat_parameter_verbosity_debug_e, kt_tacocat_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        main->setting.state.status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, &main->program);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & kt_tacocat_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(fll_program_parameter_process_verbosity));

          return;
        }
      }
    }

    if (main->program.parameters.array[kt_tacocat_parameter_help_e].result & f_console_result_found_e) {
      main->setting.flag |= kt_tacocat_main_flag_help_e;
    }
    else {
      main->setting.flag -= main->setting.flag & kt_tacocat_main_flag_help_e;
    }

    if (main->program.parameters.array[kt_tacocat_parameter_version_e].result & f_console_result_found_e) {
      main->setting.flag |= kt_tacocat_main_flag_version_e;
    }
    else {
      main->setting.flag -= main->setting.flag & kt_tacocat_main_flag_version_e;
    }

    if (main->program.parameters.array[kt_tacocat_parameter_copyright_e].result & f_console_result_found_e) {
      main->setting.flag |= kt_tacocat_main_flag_copyright_e;
    }
    else {
      main->setting.flag -= main->setting.flag & kt_tacocat_main_flag_copyright_e;
    }

    if (main->program.parameters.array[kt_tacocat_parameter_background_e].result & f_console_result_found_e) {
      main->setting.flag |= kt_tacocat_main_flag_background_e;
    }
    else {
      main->setting.flag -= main->setting.flag & kt_tacocat_main_flag_background_e;
    }

    if (main->program.parameters.array[kt_tacocat_parameter_pid_e].result & f_console_result_found_e) {
      main->setting.flag |= kt_tacocat_main_flag_pid_e;
    }
    else {
      main->setting.flag -= main->setting.flag & kt_tacocat_main_flag_pid_e;
    }

    uint8_t i = 0;
    f_number_unsigned_t index = 0;

    {
      const uint8_t parameters[] = {
        kt_tacocat_parameter_pid_name_e,
        kt_tacocat_parameter_pid_path_e,
      };

      const f_string_static_t longs[] = {
        kt_tacocat_long_pid_name_s,
        kt_tacocat_long_pid_path_s,
      };

      f_string_dynamic_t * const strings[] = {
        &main->setting.pid_name,
        &main->setting.pid_path,
      };

      for (; i < 2; ++i) {

        if (main->program.parameters.array[parameters[i]].result & f_console_result_value_e) {
          index = main->program.parameters.array[parameters[i]].values.array[main->program.parameters.array[parameters[i]].values.used - 1];

          if (main->program.parameters.arguments.array[index].used) {
            strings[i]->used = 0;

            main->setting.state.status = f_string_dynamic_append_nulless(main->program.parameters.arguments.array[index], strings[i]);

            if (F_status_is_error(main->setting.state.status)) {
              if ((main->setting.flag & kt_tacocat_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
                fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
              }

              kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(f_string_dynamic_append_nulless));

              return;
            }
          }
          else {
            main->setting.state.status = F_status_set_error(F_parameter);

            if ((main->setting.flag & kt_tacocat_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            fll_program_print_error_parameter_empty_value(&main->program.error, f_console_symbol_long_normal_s, longs[i]);

            return;
          }
        }
        else if (main->program.parameters.array[parameters[i]].result & f_console_result_found_e) {
          main->setting.state.status = F_status_set_error(F_parameter);

          if ((main->setting.flag & kt_tacocat_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, longs[i]);

          return;
        }
      } // for
    }

    {
      const uint8_t parameters[] = {
        kt_tacocat_parameter_from_e,
        kt_tacocat_parameter_to_e,
      };

      const f_string_static_t longs[] = {
        kt_tacocat_long_from_s,
        kt_tacocat_long_to_s,
      };

      f_string_dynamics_t * const strings[] = {
        &main->setting.froms,
        &main->setting.tos,
      };

      f_number_unsigned_t j = 0;

      for (i = 0; i < 2; ++i) {

        if (main->program.parameters.array[parameters[i]].result & f_console_result_value_e) {
          strings[i]->used = 0;

          main->setting.state.status = f_string_dynamics_increase_by(main->program.parameters.array[parameters[i]].values.used, strings[i]);

          if (F_status_is_error(main->setting.state.status)) {
            if ((main->setting.flag & kt_tacocat_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(f_string_dynamics_increase_by));

            return;
          }

          for (j = 0; j < main->program.parameters.array[parameters[i]].values.used; ++j) {

            index = main->program.parameters.array[parameters[i]].values.array[j];

            if (main->program.parameters.arguments.array[index].used) {
              strings[i]->array[j].used = 0;

              main->setting.state.status = f_string_dynamic_append_nulless(main->program.parameters.arguments.array[index], &strings[i]->array[j]);

              if (F_status_is_error(main->setting.state.status)) {
                if ((main->setting.flag & kt_tacocat_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
                  fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
                }

                kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(f_string_dynamic_append_nulless));

                return;
              }
            }
            else {
              main->setting.state.status = F_status_set_error(F_parameter);

              if ((main->setting.flag & kt_tacocat_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
                fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
              }

              fll_program_print_error_parameter_empty_value(&main->program.error, f_console_symbol_long_normal_s, longs[i]);

              return;
            }
          } // for
        }
        else if (main->program.parameters.array[parameters[i]].result & f_console_result_found_e) {
          main->setting.state.status = F_status_set_error(F_parameter);

          if ((main->setting.flag & kt_tacocat_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, longs[i]);

          return;
        }
      } // for
    }
  }
#endif // _di_kt_tacocat_setting_load_

#ifdef __cplusplus
} // extern "C"
#endif
