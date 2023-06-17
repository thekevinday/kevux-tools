#include "remove.h"
#include "main.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  kt_remove_main_t data = kt_remove_main_t_initialize;

  data.program.debug.flag |= kt_remove_print_flag_debug_e | kt_remove_print_flag_out_e;
  data.program.error.flag |= kt_remove_print_flag_error_e | kt_remove_print_flag_out_e;
  data.program.message.flag |= kt_remove_print_flag_message_e | kt_remove_print_flag_out_e;
  data.program.output.flag |= kt_remove_print_flag_out_e;
  data.program.warning.flag |= kt_remove_print_flag_warning_e | kt_remove_print_flag_out_e;
  data.program.message.custom = (void *) &data;
  data.program.output.custom = (void *) &data;
  data.program.error.custom = (void *) &data;
  data.program.warning.custom = (void *) &data;
  data.program.debug.custom = (void *) &data;

  data.setting.state.data = (void *) &data;
  data.setting.program_name = &kt_remove_program_name_s;
  data.setting.program_name_long = &kt_remove_program_name_long_s;
  data.setting.process_help = &kt_remove_process_help;
  data.setting.process_normal = &kt_remove_process_normal;

  #ifdef _en_kt_default_to_utc_
    data.setting.flag |= kt_remove_flag_utc_e;
  #endif // _en_kt_default_to_utc_

  f_console_parameter_t parameters[] = kt_remove_console_parameter_t_initialize;

  data.program.parameters.array = parameters;
  data.program.parameters.used = kt_remove_total_parameters_d;
  data.program.environment = envp;

  if (f_pipe_input_exists()) {
    data.program.pipe = fll_program_data_pipe_input_e;
  }

  fll_program_standard_set_up(&data.program);

  #ifdef _di_thread_support_
    {
      const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize_1(argc, argv, envp);

      kt_remove_setting_load(arguments, &data);
    }

    status_code_main(&data);
  #else
    {
      f_thread_id_t id_signal;

      memset(&id_signal, 0, sizeof(f_thread_id_t));

      data.setting.state.status = f_thread_create(0, &id_signal, &kt_remove_thread_signal, (void *) &data);

      if (F_status_is_error(data.setting.state.status)) {
        kt_remove_print_error(&data.program.error, macro_kt_remove_f(f_thread_create));
      }
      else {
        {
          const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize_1(argc, argv, envp);

          kt_remove_setting_load(arguments, &data);
        }

        if (!kt_remove_signal_check(&data)) {
          kt_remove_main(&data);
        }

        f_thread_cancel(id_signal);
        f_thread_join(id_signal, 0);
      }
    }
  #endif // _di_thread_support_

  kt_remove_setting_unload(&data);

  fll_program_data_delete(&data.program);

  fll_program_standard_set_down(&data.program);

  return (F_status_is_error(data.setting.state.status) || data.setting.state.status == F_false) ? 1 : 0;
}
