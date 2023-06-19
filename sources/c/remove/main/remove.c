#include "remove.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_remove_main_
  void kt_remove_main(kt_remove_main_t * const main) {

    if (!main) return;

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & kt_remove_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    if ((main->setting.flag & kt_remove_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }

    main->setting.state.status = F_none;

    if (main->setting.flag & (kt_remove_main_flag_help_e | kt_remove_main_flag_version_e | kt_remove_main_flag_copyright_e)) {
      if (main->setting.flag & kt_remove_main_flag_help_e) {
        if (main->setting.process_help) {
          main->setting.process_help((void *) main);
        }
      }
      else if (main->setting.flag & kt_remove_main_flag_version_e) {
        fll_program_print_version(&main->program.message, kt_remove_program_version_s);
      }
      else if (main->setting.flag & kt_remove_main_flag_copyright_e) {
        fll_program_print_copyright(&main->program.message);
      }

      if ((main->setting.flag & kt_remove_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    if (main->setting.process_normal) {
      main->setting.process_normal((void *) main);
      if (F_status_is_error(main->setting.state.status)) return;
    }

    if (main->program.signal_received) {
      main->setting.state.status = F_status_set_error(F_interrupt);
    }

    if (main->setting.state.status == F_status_set_error(F_interrupt)) {
      fll_program_print_signal_received(&main->program.warning, main->program.signal_received);
    }

    if ((main->setting.flag & kt_remove_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }
  }
#endif // _di_kt_remove_main_

#ifndef _di_kt_remove_process_help_
  f_status_t kt_remove_process_help(void * const main) {

    if (!main) return F_output_not;

    return kt_remove_print_message_help(&((kt_remove_main_t *) main)->program.output, ((kt_remove_main_t *) main)->program.context);
  }
#endif // _di_kt_remove_process_help_

#ifndef _di_kt_remove_process_normal_
  void kt_remove_process_normal(void * const main) {

    if (!main) return;

    f_thread_id_t id_signal;

    memset(&id_signal, 0, sizeof(f_thread_id_t));

    kt_remove_process_normal_operate(((kt_remove_main_t *) main));

    f_thread_cancel(id_signal);
    f_thread_join(id_signal, 0);
  }
#endif // _di_kt_remove_process_normal_

#ifndef _di_kt_remove_process_normal_operate_
  void kt_remove_process_normal_operate(kt_remove_main_t * const main) {

    if (!main) return;

    if (!main->setting.files.used) {
      kt_remove_print_error_parameter_no_files(&main->program.error);

      return;
    }

    kt_remove_print_simulate_operate(&main->program.output);

    main->setting.state.status = F_none;

    for (f_number_unsigned_t i = 0; i < main->setting.files.used; ++i) {

      kt_remove_operate_file(main, main->setting.files.array[i]);

      if ((main->setting.flag & kt_remove_main_flag_simulate_e) && i + 1 < main->setting.files.used && (F_status_is_error_not(main->setting.state.status) || F_status_set_fine(main->setting.state.status) == F_interrupt)) {
        f_print_dynamic(f_string_eol_s, main->program.output.to);
      }

      if (F_status_is_error(main->setting.state.status)) break;
    } // for
  }
#endif // _di_kt_remove_process_normal_operate_

#ifdef __cplusplus
} // extern "C"
#endif
