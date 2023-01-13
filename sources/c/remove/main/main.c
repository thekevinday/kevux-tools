#include "remove.h"
#include "main.h"

int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  fll_program_data_t data = fll_program_data_t_initialize;
  kt_remove_setting_t setting = kt_remove_setting_t_initialize;
  setting.state.data = (void *) &data;
  setting.program_name = &kt_remove_program_name_s;
  setting.program_name_long = &kt_remove_program_name_long_s;
  setting.process_help = &kt_remove_process_help;
  setting.process_normal = &kt_remove_process_normal;

  #ifdef _en_kt_default_to_utc_
    setting.flag |= kt_remove_flag_utc_e;
  #endif // _en_kt_default_to_utc_

  f_console_parameter_t parameters[] = kt_remove_console_parameter_t_initialize;
  data.parameters.array = parameters;
  data.parameters.used = kt_remove_total_parameters_d;

  fll_program_standard_setup(&data.signal);

  {
    f_thread_id_t id_signal;
    kt_remove_arguments_t signal_arguments = macro_kt_remove_arguments_t_initialize(&data, &setting);

    memset(&id_signal, 0, sizeof(f_thread_id_t));

    setting.status = f_thread_create(0, &id_signal, &kt_remove_thread_signal, (void *) &signal_arguments);

    if (F_status_is_error(setting.status)) {
      kt_remove_print_error(&setting, data.error, macro_kt_remove_f(f_thread_create));
    }
    else {
      {
        const f_console_arguments_t arguments = macro_f_console_arguments_t_initialize(argc, argv, envp);

        kt_remove_setting_load(arguments, &data, &setting);
      }

      if (!kt_remove_signal_check(&data)) {
        kt_remove_main(&data, &setting);
      }

      f_thread_cancel(id_signal);
      f_thread_join(id_signal, 0);
    }
  }

  kt_remove_setting_unload(&data, &setting);

  fll_program_data_delete(&data);

  fll_program_standard_setdown(&data.signal);

  return F_status_is_error(setting.status) ? 1 : 0;
}
