#include "tacocat.h"
#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  kt_tacocat_main_t data = kt_tacocat_main_t_initialize;

  data.program.debug.flag |= kt_tacocat_print_flag_debug_e | kt_tacocat_print_flag_out_e;
  data.program.error.flag |= kt_tacocat_print_flag_error_e | kt_tacocat_print_flag_out_e;
  data.program.message.flag |= kt_tacocat_print_flag_message_e | kt_tacocat_print_flag_out_e;
  data.program.output.flag |= kt_tacocat_print_flag_out_e;
  data.program.warning.flag |= kt_tacocat_print_flag_warning_e | kt_tacocat_print_flag_out_e;
  data.program.message.custom = (void *) &data;
  data.program.output.custom = (void *) &data;
  data.program.error.custom = (void *) &data;
  data.program.warning.custom = (void *) &data;
  data.program.debug.custom = (void *) &data;

  data.setting.state.data = (void *) &data;

  f_console_parameter_t parameters[] = kt_tacocat_console_parameter_t_initialize;

  data.program.parameters.array = parameters;
  data.program.parameters.used = kt_tacocat_parameter_total_d;
  data.program.environment = envp;

  if (f_pipe_input_exists()) {
    data.program.pipe = fll_program_data_pipe_input_e;
  }

  fll_program_standard_set_up(&data.program);

  #ifdef _di_thread_support_
    {
      const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize_1(argc, argv, envp);

      kt_tacocat_setting_load(arguments, &data);
    }

    status_code_main(&data);
  #else
    {
      f_thread_id_t id_signal;

      memset(&id_signal, 0, sizeof(f_thread_id_t));

      data.setting.state.status = f_thread_create(0, &id_signal, &kt_tacocat_thread_signal, (void *) &data);

      if (F_status_is_error(data.setting.state.status)) {
        kt_tacocat_print_error(&data.program.error, macro_kt_tacocat_f(f_thread_create));
      }
      else {
        {
          const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize_1(argc, argv, envp);

          kt_tacocat_setting_load(arguments, &data);
        }

        if (!kt_tacocat_signal_check(&data)) {
          kt_tacocat_main(&data);
        }

        f_thread_cancel(id_signal);
        f_thread_join(id_signal, 0);
      }
    }
  #endif // _di_thread_support_

  kt_tacocat_main_delete(&data);

  fll_program_standard_set_down(&data.program);

  return (F_status_is_error(data.setting.state.status) || data.setting.state.status == F_false) ? 1 : 0;
}

#ifdef __cplusplus
} // extern "C"
#endif
