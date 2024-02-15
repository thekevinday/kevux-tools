#include "tacocat.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_tacocat_main_
  void kt_tacocat_main(kt_tacocat_main_t * const main) {

    if (!main) return;

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & kt_tacocat_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    macro_setting_load_print_first();

    main->setting.state.status = F_okay;

    if (main->setting.flag & kt_tacocat_main_flag_version_copyright_help_e) {
      if (main->setting.flag & kt_tacocat_main_flag_help_e) {
        kt_tacocat_print_message_help(&main->program.output, main->program.context);
      }
      else if (main->setting.flag & kt_tacocat_main_flag_version_e) {
        fll_program_print_version(&main->program.message, kt_tacocat_program_version_s);
      }
      else if (main->setting.flag & kt_tacocat_main_flag_copyright_e) {
        fll_program_print_copyright(&main->program.message);
      }

      if ((main->setting.flag & kt_tacocat_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      return;
    }

    main->setting.state.status = f_random_seed(F_random_seed_flag_block_not_d);

    // Try again, but only once if blocked.
    if (main->setting.state.status == F_status_set_error(F_again)) {
      {
        const struct timespec time = { .tv_sec = kt_tacocat_startup_seed_delay_second_d, .tv_nsec = kt_tacocat_startup_seed_delay_nanosecond_d };

        nanosleep(&time, 0);
      }

      main->setting.state.status = f_random_seed(F_random_seed_flag_block_not_d);
    }

    if (F_status_is_error(main->setting.state.status)) {

      // Fall back to the far less secure but better than nothing method of using time as the seed.
      f_random_seed_set((unsigned int) time(0));

      main->setting.state.status = F_okay;
    }

    kt_tacocat_process_main(main);

    if (main->program.signal_received) {
      main->setting.state.status = F_status_set_error(F_interrupt);
    }

    if (main->setting.state.status == F_status_set_error(F_interrupt)) {
      fll_program_print_signal_received(&main->program.warning, main->program.signal_received);
    }

    if ((main->setting.flag & kt_tacocat_main_flag_print_last_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
      fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
    }
  }
#endif // _di_kt_tacocat_main_

#ifdef __cplusplus
} // extern "C"
#endif
