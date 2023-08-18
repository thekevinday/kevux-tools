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
      macro_setting_load_print_first();
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
          macro_setting_load_print_first();

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
          macro_setting_load_print_first();

          kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(fll_program_parameter_process_verbosity));

          return;
        }
      }
    }

    f_number_unsigned_t index = 0;

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

    if (main->program.parameters.array[kt_tacocat_parameter_resolve_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      macro_setting_load_print_first();

      fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, kt_tacocat_long_resolve_s);
    }
    else if (main->program.parameters.array[kt_tacocat_parameter_resolve_e].result & f_console_result_value_e) {
      index = main->program.parameters.array[kt_tacocat_parameter_resolve_e].values.array[main->program.parameters.array[kt_tacocat_parameter_resolve_e].values.used - 1];

      if (f_compare_dynamic(main->program.parameters.arguments.array[index], kt_tacocat_classic_s) == F_equal_to) {
        main->setting.flag -= main->setting.flag & kt_tacocat_main_flag_resolve_kevux_e;
        main->setting.flag |= kt_tacocat_main_flag_resolve_classic_e;
      }
      else if (f_compare_dynamic(main->program.parameters.arguments.array[index], kt_tacocat_kevux_s) == F_equal_to) {
        main->setting.flag -= main->setting.flag & kt_tacocat_main_flag_resolve_classic_e;
        main->setting.flag |= kt_tacocat_main_flag_resolve_kevux_e;
      }
      else {
        main->setting.state.status = F_status_set_error(F_parameter);

        macro_setting_load_print_first();

        kt_tacocat_print_error_parameter_value_resolve_unknown(&main->program.error, main->program.parameters.arguments.array[index]);
      }
    }
    else {
      #ifdef _kt_resolve_default_kevux_
        main->setting.flag -= main->setting.flag & kt_tacocat_main_flag_resolve_classic_e;
        main->setting.flag |= kt_tacocat_main_flag_resolve_kevux_e;
      #else
        main->setting.flag -= main->setting.flag & kt_tacocat_main_flag_resolve_kevux_e;
        main->setting.flag |= kt_tacocat_main_flag_resolve_classic_e;
      #endif // _kt_resolve_default_kevux_
    }

    if (main->program.parameters.array[kt_tacocat_parameter_interval_e].result & f_console_result_value_e) {
      index = main->program.parameters.array[kt_tacocat_parameter_interval_e].values.array[main->program.parameters.array[kt_tacocat_parameter_interval_e].values.used - 1];

      f_number_unsigned_t number = 0;

      main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, main->program.parameters.arguments.array[index], &number);

      if (F_status_is_error(main->setting.state.status)) {
        macro_setting_load_print_first();
        kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(fl_conversion_dynamic_to_unsigned_detect));

        return;
      }

      if (number == 0 || main->setting.state.status == F_number_negative) {
        main->setting.state.status = F_status_set_error(F_parameter);

        fll_program_print_error_parameter_integer_less_than(&main->program.error, f_console_symbol_long_normal_s, kt_tacocat_long_interval_s, main->program.parameters.arguments.array[index], f_string_ascii_1_s);

        return;
      }

      main->setting.interval = number;
    }
    else if (main->program.parameters.array[kt_tacocat_parameter_interval_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      macro_setting_load_print_first();

      fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, kt_tacocat_long_interval_s);

      return;
    }

    // Only process these when needed to avoid unnecessary operations.
    if (main->callback.setting_load_send_receive && !(main->setting.flag & (kt_tacocat_main_flag_copyright_e | kt_tacocat_main_flag_version_e |kt_tacocat_main_flag_help_e))) {
      main->callback.setting_load_send_receive(arguments, (void *) main);
    }

    if (F_status_is_error_not(main->setting.state.status)) {
      main->setting.state.status = F_okay;
    }
  }
#endif // _di_kt_tacocat_setting_load_

#ifndef _di_kt_tacocat_setting_load_send_receive_
  void kt_tacocat_setting_load_send_receive(const f_console_arguments_t arguments, void * const void_main) {

    if (!void_main) return;

    kt_tacocat_main_t * const main = (kt_tacocat_main_t *) void_main;

    const uint8_t parameters[] = {
      kt_tacocat_parameter_receive_e,
      kt_tacocat_parameter_send_e,
    };

    const uint64_t flags[] = {
      kt_tacocat_main_flag_receive_e,
      kt_tacocat_main_flag_send_e,
    };

    const f_string_static_t longs[] = {
      kt_tacocat_long_receive_s,
      kt_tacocat_long_send_s,
    };

    kt_tacocat_socket_set_t * const sets[] = {
      &main->setting.receive,
      &main->setting.send,
    };

    const bool is_receive[] = {
      F_true,
      F_false,
    };

    f_number_unsigned_t j = 0;
    f_number_unsigned_t k = 0;
    f_number_unsigned_t index = 0;
    f_number_unsigned_t length = 0;
    f_status_t failed = F_okay;
    struct hostent host;
    f_network_family_ip_t family = f_network_family_ip_t_initialize;
    f_number_unsigned_t port = 0;
    f_number_unsigned_t total = 0;
    f_string_static_t address = f_string_static_t_initialize;

    for (uint8_t i = 0; i < 2; ++i) {

      if (main->program.parameters.array[parameters[i]].result & f_console_result_value_e) {
        main->setting.flag |= flags[i];

        if (main->program.parameters.array[parameters[i]].values.used % 2) {
          main->setting.state.status = F_status_set_error(F_parameter);

          if ((main->setting.flag & kt_tacocat_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fll_program_print_error_parameter_missing_value_requires_amount(&main->program.error, f_console_symbol_long_normal_s, longs[i], kt_tacocat_two_s);

          if (F_status_is_error_not(failed)) {
            failed = main->setting.state.status;
          }

          continue;
        }

        sets[i]->flags.used = 0;
        sets[i]->names.used = 0;
        sets[i]->buffers.used = 0;
        sets[i]->packets.used = 0;
        sets[i]->files.used = 0;
        sets[i]->sockets.used = 0;
        sets[i]->statuss.used = 0;
        sets[i]->polls.used = 0;

        total = main->program.parameters.array[parameters[i]].values.used / 2;

        main->setting.state.status = f_memory_array_increase_by(total, sizeof(uint16_t), (void **) &sets[i]->flags.array, &sets[i]->flags.used, &sets[i]->flags.size);

        macro_setting_load_handle_send_receive_error_continue_1(f_memory_array_increase_by);

        main->setting.state.status = f_string_dynamics_increase_by(total, &sets[i]->names);

        macro_setting_load_handle_send_receive_error_continue_1(f_string_dynamics_increase_by);

        main->setting.state.status = f_string_dynamics_increase_by(total, &sets[i]->buffers);

        macro_setting_load_handle_send_receive_error_continue_1(f_string_dynamics_increase_by);

        main->setting.state.status = f_fss_simple_packet_ranges_increase_by(total, &sets[i]->packets);

        macro_setting_load_handle_send_receive_error_continue_1(f_fss_simple_packet_ranges_increase_by);

        main->setting.state.status = f_memory_array_increase_by(total, sizeof(f_file_t), (void **) &sets[i]->files.array, &sets[i]->files.used, &sets[i]->files.size);

        macro_setting_load_handle_send_receive_error_continue_1(f_memory_array_increase_by);

        main->setting.state.status = f_sockets_increase_by(total, &sets[i]->sockets);

        macro_setting_load_handle_send_receive_error_continue_1(f_sockets_increase_by);

        main->setting.state.status = f_statuss_increase_by(total, &sets[i]->statuss);

        macro_setting_load_handle_send_receive_error_continue_1(f_statuss_increase_by);

        main->setting.state.status = f_polls_increase_by(total, &sets[i]->polls);

        macro_setting_load_handle_send_receive_error_continue_1(f_polls_increase_by);

        for (j = 0; j < main->program.parameters.array[parameters[i]].values.used; j += 2) {

          // First parameter value represents the network address or the socket file path.
          index = main->program.parameters.array[parameters[i]].values.array[j];
          sets[i]->statuss.array[j] = F_okay;
          sets[i]->flags.array[j] = kt_tacocat_socket_flag_none_e;
          sets[i]->names.array[j].used = 0;
          sets[i]->buffers.array[j].used = 0;
          sets[i]->packets.array[j].control.start = 1;
          sets[i]->packets.array[j].control.stop = 0;
          sets[i]->packets.array[j].size.start = 1;
          sets[i]->packets.array[j].size.stop = 0;
          sets[i]->packets.array[j].payload.start = 1;
          sets[i]->packets.array[j].payload.stop = 0;

          if (main->program.parameters.arguments.array[index].used) {
            if (f_path_is_absolute(main->program.parameters.arguments.array[index]) == F_true || f_path_is_relative_current(main->program.parameters.arguments.array[index]) == F_true) {

              main->setting.state.status = f_string_dynamic_increase_by(main->program.parameters.arguments.array[index].used + 2, &sets[i]->names.array[j]);

              macro_setting_load_handle_send_receive_error_continue_2(f_string_dynamic_increase_by);

              main->setting.state.status = f_string_dynamic_append_nulless(main->program.parameters.arguments.array[index], &sets[i]->names.array[j]);

              macro_setting_load_handle_send_receive_error_continue_2(f_string_dynamic_append_nulless);

              // Designate this as a socket file by appending after the terminating NULL, past the used length.
              sets[i]->names.array[j].string[sets[i]->names.array[j].used] = 0;
              sets[i]->names.array[j].string[sets[i]->names.array[j].used + 1] = f_string_ascii_slash_forward_s.string[0];

              if (is_receive[i]) {
                main->setting.state.status = f_file_exists(sets[i]->names.array[j], F_true);

                macro_setting_load_handle_send_receive_error_continue_2(f_string_dynamic_append_nulless);
              }

              sets[i]->names.array[j].string[sets[i]->names.array[j].used] = 0;
              sets[i]->sockets.array[j].domain = f_socket_protocol_family_local_e;
              sets[i]->sockets.array[j].protocol = f_socket_protocol_tcp_e;
              sets[i]->sockets.array[j].type = f_socket_type_stream_e;
              sets[i]->sockets.array[j].name = sets[i]->names.array[j];
            }
            else if (main->setting.flag & kt_tacocat_main_flag_resolve_classic_e) {
              memset(&host, 0, sizeof(struct hostent));

              port = 0;
              address = main->program.parameters.arguments.array[index];
              f_char_t address_string[address.used];

              memcpy(address_string, address.string, address.used);
              address.string = address_string;

              f_network_is_ip_address(address, &port, &main->setting.state);

              if (F_status_is_error(main->setting.state.status)) {
                // @todo print error message about bad port number or similar.
                macro_setting_load_handle_send_receive_error_continue_2(f_network_is_ip_address);
              }

              if (main->setting.state.status == F_network_version_four) {
                host.h_addrtype = f_socket_address_family_inet4_e;
              }
              else if (main->setting.state.status == F_network_version_six) {
                host.h_addrtype = f_socket_address_family_inet6_e;
              }
              else {
                host.h_addrtype = 0;
              }

              kt_tacocat_setting_load_address_port_extract(main, &address, &port);

              if (F_status_is_error(main->setting.state.status)) {
                // @todo print error message about bad port number or similar.
                macro_setting_load_handle_send_receive_error_continue_2(kt_tacocat_setting_load_address_port_extract);
              }

              // Fail forward if port number is not supported by the system.
              if (port != (in_port_t) port) {
                kt_tacocat_print_warning_port_number_overflow(&main->program.warning, main->program.parameters.arguments.array[index], port);

                port = 0;
              }

              if (host.h_addrtype) {
                main->setting.state.status = f_string_dynamic_append(address, &sets[i]->names.array[j]);

                macro_setting_load_handle_send_receive_error_continue_2(f_string_dynamic_append);
              }
              else {
                // @todo move this block into its own function.
                main->setting.state.status = f_network_from_ip_name(address, &host);

                // @todo provide network-specific error messages.
                macro_setting_load_handle_send_receive_error_continue_2(f_network_from_ip_name);

                if (main->setting.state.status == F_data_not || !host.h_addr_list || !host.h_addr_list[0]) {
                  main->setting.state.status = F_status_set_error(F_parameter);

                  macro_setting_load_print_first();

                  // @todo provide network-specific error messages for when no hosts are returned.
                  kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(f_network_from_ip_name));

                  if (F_status_is_error_not(failed)) {
                    failed = main->setting.state.status;
                  }

                  sets[i]->statuss.array[j] = main->setting.state.status;

                  continue;
                }

                main->setting.state.status = f_string_dynamic_increase_by(INET6_ADDRSTRLEN + 1, &sets[i]->names.array[j]);

                macro_setting_load_handle_send_receive_error_continue_2(f_string_dynamic_increase_by);

                // Randomly select one of the addresses when there are more than one.
                if (host.h_addr_list[1]) {
                  k = 2;

                  while (host.h_addr_list[k++]);

                  // Real randomness or security is not needed here, so fiddle with predictable but somewhat dynamic numbers.
                  srand(main->program.pid + j + host.h_addr_list[0][0]);
                  k = rand() % (k - 1);
                }
                else {
                  k = 0;
                }

                main->setting.state.status = f_string_dynamic_increase_by(INET6_ADDRSTRLEN + 1, &sets[i]->names.array[j]);

                macro_setting_load_handle_send_receive_error_continue_2(f_string_dynamic_increase_by);

                if (host.h_addrtype == f_socket_address_family_inet4_e) {
                  family.type = f_network_family_ip_4_e;
                  family.address.v4 = *((struct in_addr *) host.h_addr_list[k]);
                }
                else {
                  family.type = f_network_family_ip_6_e;
                  family.address.v6 = *((struct in6_addr *) host.h_addr_list[k]);
                }

                main->setting.state.status = f_network_to_ip_string(family, &sets[i]->names.array[j]);

                if (main->setting.state.status == F_data_not || !host.h_addr_list || !host.h_addr_list[0]) {
                  main->setting.state.status = F_status_set_error(F_parameter);

                  macro_setting_load_print_first();

                  // @todo provide network-specific error messages for when no hosts are returned.
                  kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(f_network_from_ip_name));

                  if (F_status_is_error_not(failed)) {
                    failed = main->setting.state.status;
                  }

                  sets[i]->statuss.array[j] = main->setting.state.status;

                  continue;
                }

                sets[i]->names.array[j].string[sets[i]->names.array[j].used] = 0;
              }

              sets[i]->sockets.array[j].protocol = f_socket_protocol_tcp_e;
              sets[i]->sockets.array[j].type = f_socket_type_stream_e;

              if (host.h_addrtype == f_socket_address_family_inet4_e) {
                sets[i]->sockets.array[j].domain = f_socket_protocol_family_inet4_e;
                sets[i]->sockets.array[j].address.inet4.sin_port = (in_port_t) port;
                sets[i]->sockets.array[j].address.inet4.sin_addr.s_addr = INADDR_ANY;
              }
              else if (host.h_addrtype == f_socket_address_family_inet6_e) {
                sets[i]->sockets.array[j].domain = f_socket_protocol_family_inet6_e;
                sets[i]->sockets.array[j].address.inet6.sin6_port = (in_port_t) port;
                sets[i]->sockets.array[j].address.inet6.sin6_addr = in6addr_any;
              }
            }
            else {
              // @todo Kevux DNS resolution.
            }

            ++sets[i]->files.used;
            ++sets[i]->polls.used;
            ++sets[i]->sockets.used;
            ++sets[i]->statuss.used;
            ++sets[i]->names.used;
            ++sets[i]->buffers.used;
            ++sets[i]->packets.used;
          }
          else {
            main->setting.state.status = F_status_set_error(F_parameter);

            macro_setting_load_print_first();

            fll_program_print_error_parameter_empty_value(&main->program.error, f_console_symbol_long_normal_s, longs[i]);

            if (F_status_is_error_not(failed)) {
              failed = main->setting.state.status;
            }

            sets[i]->statuss.array[j] = main->setting.state.status;

            continue;
          }

          // The second parameter value represents the local file to read from or write to.
          index = main->program.parameters.array[parameters[i]].values.array[j + 1];

          if (main->program.parameters.arguments.array[index].used) {

            // Make sure the current file is closed.
            f_file_close(&sets[i]->files.array[j]);

            sets[i]->files.array[j].flag = is_receive[i] ? F_file_flag_append_wo_d : F_file_flag_read_only_d;
            sets[i]->files.array[j].size_read = sets[i]->block_size;
            sets[i]->files.array[j].size_write = sets[i]->block_size;

            main->setting.state.status = f_file_open(main->program.parameters.arguments.array[index], F_file_mode_all_rw_d, &sets[i]->files.array[j]);

            if (F_status_is_error(main->setting.state.status)) {
              macro_setting_load_handle_send_receive_error_file_continue_1(f_file_open, main->program.parameters.arguments.array[index], f_file_operation_open_s, fll_error_file_type_file_e);

              if (F_status_is_error_not(failed)) {
                failed = main->setting.state.status;
              }

              sets[i]->statuss.array[j] = main->setting.state.status;
            }
          }
          else {
            main->setting.state.status = F_status_set_error(F_parameter);

            macro_setting_load_print_first();

            fll_program_print_error_parameter_empty_value(&main->program.error, f_console_symbol_long_normal_s, longs[i]);

            if (F_status_is_error_not(failed)) {
              failed = main->setting.state.status;
            }

            sets[i]->statuss.array[j] = main->setting.state.status;

            continue;
          }
        } // for
      }
      else if (main->program.parameters.array[parameters[i]].result & f_console_result_found_e) {
        main->setting.flag -= main->setting.flag & flags[i];

        main->setting.state.status = F_status_set_error(F_parameter);

        macro_setting_load_print_first();

        fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, longs[i]);

        if (F_status_is_error_not(failed)) {
          failed = main->setting.state.status;
        }

        continue;
      }
      else {
        main->setting.flag -= main->setting.flag & flags[i];
      }
    } // for

    if (F_status_is_error(failed)) {
      main->setting.state.status = failed;
    }
  }
#endif // _di_kt_tacocat_setting_load_send_receive_

#ifndef _di_kt_tacocat_setting_load_address_port_extract_
  void kt_tacocat_setting_load_address_port_extract(kt_tacocat_main_t * const main, f_string_static_t * const address, f_number_unsigned_t * const port) {

    if (!main) return;

    if (!address || !port) {
      main->setting.state.status = F_status_set_error(F_parameter);

      return;
    }

    if (!address->used) {
      main->setting.state.status = F_data_not;

      return;
    }

    f_number_unsigned_t i = 0;

    if (main->setting.state.status == F_network_version_four || main->setting.state.status == F_network_version_six) {
      if (*port) {
        i = *port;
        *port = 0;

        const f_string_static_t adjusted = macro_f_string_static_t_initialize_1(address->string + i, 0, address->used - i);

        main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, adjusted, port);
        if (F_status_is_error(main->setting.state.status)) return;

        address->string[i] = 0;
        address->used = i;

        while (address->used && address->string[address->used] != f_string_ascii_colon_s.string[0]) --address->used;
      }

      main->setting.state.status = F_okay;

      return;
    }

    *port = 0;
    i = address->used;

    while (--i) {
      if (address->string[i] == f_string_ascii_colon_s.string[0]) break;
    } // while

    if (i && i + 1 < address->used) {
      const f_string_static_t adjusted = macro_f_string_static_t_initialize_1(address->string + i + 1, 0, address->used - i - 1);

      main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, adjusted, port);
      if (F_status_is_error(main->setting.state.status)) return;

      address->string[i] = 0;
      address->used = i;
      main->setting.state.status = F_okay;
    }
    else {
      main->setting.state.status = F_number_not;
    }
  }
#endif // _di_kt_tacocat_setting_load_address_port_extract_


#ifdef __cplusplus
} // extern "C"
#endif
