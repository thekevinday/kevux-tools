#include "remove.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_remove_main_
  void kt_remove_main(fll_program_data_t * const main, kt_remove_setting_t * const setting) {

    if (!main || !setting || F_status_is_error(setting->status)) return;

    setting->status = F_none;

    if (setting->flag & kt_remove_flag_help_e) {
      if (setting->process_help) {
        setting->process_help(main, (void *) setting);
      }

      return;
    }

    if (setting->flag & kt_remove_flag_version_e) {
      fll_print_format("%r%r", main->output.to.stream, kt_remove_program_version_s, f_string_eol_s);

      return;
    }

    // This program ignores the input pipe.
    if (setting->process_normal) {
      setting->process_normal(main, (void *) setting);
      if (F_status_is_error(setting->status)) return;
    }

    // Ensure a new line is always put at the end of the program execution.
    f_print_dynamic_raw(f_string_eol_s, main->output.to.stream);

    if (main->signal_received) {
      setting->status = F_interrupt;
    }
  }
#endif // _di_kt_remove_main_

#ifndef _di_kt_remove_process_help_
  f_status_t kt_remove_process_help(fll_program_data_t * const main, void * const void_setting) {

    if (!main || !void_setting) return F_output_not;

    return kt_remove_print_help(macro_kt_remove_setting(void_setting), main->output, main->context);
  }
#endif // _di_kt_remove_process_help_

#ifndef _di_kt_remove_process_normal_
  void kt_remove_process_normal(fll_program_data_t * const main, void * const void_setting) {

    if (!main || !void_setting) return;

    kt_remove_arguments_t arguments = macro_kt_remove_arguments_t_initialize(main, macro_kt_remove_setting(void_setting));

    f_thread_id_t id_signal;

    memset(&id_signal, 0, sizeof(f_thread_id_t));

    kt_remove_process_normal_operate(main, macro_kt_remove_setting(void_setting));

    f_thread_cancel(id_signal);
    f_thread_join(id_signal, 0);
  }
#endif // _di_kt_remove_process_normal_

#ifndef _di_kt_remove_process_normal_operate_
  void kt_remove_process_normal_operate(fll_program_data_t * const main, kt_remove_setting_t * const setting) {

    if (!main || !setting) return;

    if (!setting->files.used) {
      kt_remove_print_error_parameter_no_files(main->error);

      return;
    }

    kt_remove_simulate_operate(main, setting);

    setting->status = F_none;

    for (f_array_length_t i = 0; i < setting->files.used; ++i) {

      kt_remove_operate_file(main, setting, setting->files.array[i]);
      if (F_status_is_error(setting->status)) break;

      if ((setting->flag & kt_remove_flag_simulate_e) && i + 1 < setting->files.used) {
        f_print_dynamic(f_string_eol_s, main->output.to.stream);
      }

      if (setting->status == F_interrupt) break;
    } // for
  }
#endif // _di_kt_remove_process_normal_operate_

#ifdef __cplusplus
} // extern "C"
#endif
