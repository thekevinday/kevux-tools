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

    if (main->program.parameters.array[kt_tacocat_parameter_max_buffer_e].result & f_console_result_value_e) {
      index = main->program.parameters.array[kt_tacocat_parameter_max_buffer_e].values.array[main->program.parameters.array[kt_tacocat_parameter_max_buffer_e].values.used - 1];

      f_number_unsigned_t number = 0;

      main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, main->program.parameters.arguments.array[index], &number);

      if (F_status_is_error(main->setting.state.status)) {
        macro_setting_load_print_first();
        kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(fl_conversion_dynamic_to_unsigned_detect));

        return;
      }

      if (number == 0) {
        kt_tacocat_print_warning_parameter_integer_less_than(&main->program.warning, f_console_symbol_long_normal_s, kt_tacocat_long_max_buffer_s, main->program.parameters.arguments.array[index]);

        main->setting.max_buffer = 0;
        main->setting.flag |= kt_tacocat_main_flag_max_buffer_e;
      }
      else if (main->setting.state.status == F_number_negative) {
        if (number == 1) {
          main->setting.max_buffer = 0;
          main->setting.flag -= main->setting.flag & kt_tacocat_main_flag_max_buffer_e;
        }
        else {
          main->setting.state.status = F_status_set_error(F_parameter);

          fll_program_print_error_parameter_integer_less_than(&main->program.error, f_console_symbol_long_normal_s, kt_tacocat_long_max_buffer_s, main->program.parameters.arguments.array[index], kt_tacocat_digit_negative_one_s);

          return;
        }
      }
      else {
        main->setting.max_buffer = number;
        main->setting.flag |= kt_tacocat_main_flag_max_buffer_e;
      }
    }
    else if (main->program.parameters.array[kt_tacocat_parameter_max_buffer_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      macro_setting_load_print_first();

      fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, kt_tacocat_long_max_buffer_s);

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

    kt_tacocat_socket_sets_t * const sets[] = {
      &main->setting.receive,
      &main->setting.send,
    };

    f_polls_t * const polls[] = {
      &main->setting.receive_polls,
      &main->setting.send_polls,
    };

    const bool is_receive[] = {
      F_true,
      F_false,
    };

    const f_number_unsigned_t default_block_size[] = {
      kt_tacocat_block_size_receive_d,
      kt_tacocat_block_size_send_d,
    };

    f_number_unsigned_t j = 0;
    f_number_unsigned_t k = 0;
    f_number_unsigned_t p = 0;
    f_number_unsigned_t index = 0;
    f_number_unsigned_t length = 0;
    f_number_unsigned_t total = 0;
    f_status_t failed = F_okay;
    struct hostent host;
    f_network_family_ip_t family = f_network_family_ip_t_initialize;
    f_number_unsigned_t port = 0;
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

        total = main->program.parameters.array[parameters[i]].values.used / 2;

        main->setting.state.status = f_memory_array_increase_by(total, sizeof(f_poll_t), (void **) &polls[i]->array, &polls[i]->used, &polls[i]->size);
        macro_setting_load_handle_send_receive_error_continue_1(f_memory_array_increase_by);

        main->setting.state.status = f_memory_array_increase_by(total, sizeof(kt_tacocat_socket_set_t), (void **) &sets[i]->array, &sets[i]->used, &sets[i]->size);
        macro_setting_load_handle_send_receive_error_continue_1(f_memory_array_increase_by);

        if (F_status_is_error_not(main->setting.state.status)) {
          main->setting.state.status = F_okay;
        }

        for (p = 0; p < main->program.parameters.array[parameters[i]].values.used; p += 2) {

          // First parameter value represents the network address or the socket file path.
          index = main->program.parameters.array[parameters[i]].values.array[p];

          j = sets[i]->used;

          sets[i]->array[j].size_block = default_block_size[i];
          sets[i]->array[j].buffer.used = 0;
          sets[i]->array[j].client.used = 0;
          sets[i]->array[j].flag = kt_tacocat_socket_flag_none_e;
          sets[i]->array[j].name.used = 0;
          sets[i]->array[j].network.used = 0;
          sets[i]->array[j].packet.control = 0;
          sets[i]->array[j].packet.size = 0;
          sets[i]->array[j].packet.payload.start = 1;
          sets[i]->array[j].packet.payload.stop = 0;
          sets[i]->array[j].retry = 0;
          sets[i]->array[j].status = F_okay;

          if (main->program.parameters.arguments.array[index].used) {
            if (f_path_is_absolute(main->program.parameters.arguments.array[index]) == F_true || f_path_is_relative_current(main->program.parameters.arguments.array[index]) == F_true) {

              main->setting.state.status = f_memory_array_increase_by(main->program.parameters.arguments.array[index].used + 2, sizeof(f_char_t), (void **) &sets[i]->array[j].network.string, &sets[i]->array[j].network.used, &sets[i]->array[j].network.size);

              macro_setting_load_handle_send_receive_error_continue_2(f_memory_array_increase_by);

              main->setting.state.status = f_string_dynamic_append_nulless(main->program.parameters.arguments.array[index], &sets[i]->array[j].network);

              macro_setting_load_handle_send_receive_error_continue_2(f_string_dynamic_append_nulless);

              // Designate this as a socket file by appending after the terminating NULL, past the used length.
              sets[i]->array[j].network.string[sets[i]->array[j].network.used] = 0;
              sets[i]->array[j].network.string[sets[i]->array[j].network.used + 1] = f_string_ascii_slash_forward_s.string[0];

              if (is_receive[i]) {
                main->setting.state.status = f_file_exists(sets[i]->array[j].network, F_true);

                macro_setting_load_handle_send_receive_error_continue_2(f_string_dynamic_append_nulless);
              }

              sets[i]->array[j].network.string[sets[i]->array[j].network.used] = 0;
              sets[i]->array[j].socket.domain = f_socket_protocol_family_local_e;
              sets[i]->array[j].socket.protocol = f_socket_protocol_tcp_e;
              sets[i]->array[j].socket.type = f_socket_type_stream_e;
              sets[i]->array[j].socket.name = sets[i]->array[j].network;
            }
            else if (main->setting.flag & kt_tacocat_main_flag_resolve_classic_e) {
              memset(&host, 0, sizeof(struct hostent));

              port = 0;
              address = main->program.parameters.arguments.array[index];
              f_char_t address_string[address.used];
              f_string_range_t port_range = f_string_range_t_initialize;

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

              kt_tacocat_setting_load_address_port_extract(main, &address, &port, &port_range);

              if (F_status_is_error(main->setting.state.status)) {
                macro_setting_load_print_first();

                if (port_range.start > port_range.stop) {
                  kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(kt_tacocat_setting_load_address_port_extract));
                }
                else {
                  kt_tacocat_print_error_port_number_invalid(&main->program.error, address, port_range);
                }

                if (F_status_is_error_not(failed)) {
                  failed = main->setting.state.status;
                }

                sets[i]->array[j].status = main->setting.state.status;

                continue;
              }

              // Fail forward if port number is not supported by the system.
              if (port != (in_port_t) port) {
                kt_tacocat_print_warning_port_number_overflow(&main->program.warning, main->program.parameters.arguments.array[index], port);

                port = 0;
              }

              if (host.h_addrtype) {
                main->setting.state.status = f_string_dynamic_append(address, &sets[i]->array[j].network);

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

                  sets[i]->array[j].status = main->setting.state.status;

                  continue;
                }

                main->setting.state.status = f_memory_array_increase_by(INET6_ADDRSTRLEN + 1, sizeof(f_char_t), (void **) &sets[i]->array[j].network.string, &sets[i]->array[j].network.used, &sets[i]->array[j].network.size);

                macro_setting_load_handle_send_receive_error_continue_2(f_memory_array_increase_by);

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

                main->setting.state.status = f_memory_array_increase_by(INET6_ADDRSTRLEN + 1, sizeof(f_char_t), (void **) &sets[i]->array[j].network.string, &sets[i]->array[j].network.used, &sets[i]->array[j].network.size);

                macro_setting_load_handle_send_receive_error_continue_2(f_memory_array_increase_by);

                if (host.h_addrtype == f_socket_address_family_inet4_e) {
                  family.type = f_network_family_ip_4_e;
                  family.address.v4 = *((struct in_addr *) host.h_addr_list[k]);
                }
                else {
                  family.type = f_network_family_ip_6_e;
                  family.address.v6 = *((struct in6_addr *) host.h_addr_list[k]);
                }

                main->setting.state.status = f_network_to_ip_string(family, &sets[i]->array[j].network);

                if (main->setting.state.status == F_data_not || !host.h_addr_list || !host.h_addr_list[0]) {
                  main->setting.state.status = F_status_set_error(F_parameter);

                  macro_setting_load_print_first();

                  // @todo provide network-specific error messages for when no hosts are returned.
                  kt_tacocat_print_error(&main->program.error, macro_kt_tacocat_f(f_network_from_ip_name));

                  if (F_status_is_error_not(failed)) {
                    failed = main->setting.state.status;
                  }

                  sets[i]->array[j].status = main->setting.state.status;

                  continue;
                }

                sets[i]->array[j].network.string[sets[i]->array[j].network.used] = 0;
              }

              sets[i]->array[j].socket.protocol = f_socket_protocol_tcp_e;
              sets[i]->array[j].socket.type = f_socket_type_stream_e;

              if (host.h_addrtype == f_socket_address_family_inet4_e) {
                sets[i]->array[j].socket.domain = f_socket_protocol_family_inet4_e;
                sets[i]->array[j].socket.address.inet4.sin_port = htons((in_port_t) port);
                sets[i]->array[j].socket.address.inet4.sin_addr.s_addr = INADDR_ANY;
              }
              else if (host.h_addrtype == f_socket_address_family_inet6_e) {
                sets[i]->array[j].socket.domain = f_socket_protocol_family_inet6_e;
                sets[i]->array[j].socket.address.inet6.sin6_port = htons((in_port_t) port);
                sets[i]->array[j].socket.address.inet6.sin6_addr = in6addr_any;
              }
            }
            else {
              // @todo Kevux DNS resolution.
            }

            ++polls[i]->used;
            ++sets[i]->used;
          }
          else {
            main->setting.state.status = F_status_set_error(F_parameter);

            macro_setting_load_print_first();

            fll_program_print_error_parameter_empty_value(&main->program.error, f_console_symbol_long_normal_s, longs[i]);

            if (F_status_is_error_not(failed)) {
              failed = main->setting.state.status;
            }

            sets[i]->array[j].status = main->setting.state.status;

            continue;
          }

          // The second parameter value represents the local file to read from or write to.
          index = main->program.parameters.array[parameters[i]].values.array[p + 1];

          if (main->program.parameters.arguments.array[index].used) {

            // Make sure the current file is closed.
            f_file_close(&sets[i]->array[j].file);

            sets[i]->array[j].file.flag = is_receive[i] ? F_file_flag_append_wo_d : F_file_flag_read_only_d;
            sets[i]->array[j].file.size_read = sets[i]->array[j].size_block;
            sets[i]->array[j].file.size_write = sets[i]->array[j].size_block;

            // Associate file name via a static string.
            sets[i]->array[j].name.string = main->program.parameters.arguments.array[index].string;
            sets[i]->array[j].name.used = main->program.parameters.arguments.array[index].used;
            sets[i]->array[j].name.size = 0;

            // @fixme only open the file when reading/writing and then close it at the end. This open is fine if it is used as a check on startup, but in this case immediately close it.
            main->setting.state.status = f_file_open(sets[i]->array[j].name, F_file_mode_all_rw_d, &sets[i]->array[j].file);

            if (F_status_is_error(main->setting.state.status)) {
              macro_setting_load_handle_send_receive_error_file_continue_1(f_file_open, sets[i]->array[j].name, f_file_operation_open_s, fll_error_file_type_file_e);

              if (F_status_is_error_not(failed)) {
                failed = main->setting.state.status;
              }

              sets[i]->array[j].status = main->setting.state.status;
            }
          }
          else {
            main->setting.state.status = F_status_set_error(F_parameter);

            macro_setting_load_print_first();

            fll_program_print_error_parameter_empty_value(&main->program.error, f_console_symbol_long_normal_s, longs[i]);

            if (F_status_is_error_not(failed)) {
              failed = main->setting.state.status;
            }

            sets[i]->array[j].status = main->setting.state.status;

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

    main->setting.state.status = F_status_is_error(failed) ? failed : F_okay;
  }
#endif // _di_kt_tacocat_setting_load_send_receive_

#ifndef _di_kt_tacocat_setting_load_address_port_extract_
  void kt_tacocat_setting_load_address_port_extract(kt_tacocat_main_t * const main, f_string_static_t * const address, f_number_unsigned_t * const port, f_string_range_t * const port_range) {

    if (!main) return;

    if (!address || !port || !port_range) {
      main->setting.state.status = F_status_set_error(F_parameter);

      return;
    }

    if (!address->used) {
      main->setting.state.status = F_data_not;

      return;
    }

    port_range->stop = address->used;

    if (main->setting.state.status == F_network_version_four || main->setting.state.status == F_network_version_six) {
      port_range->start = 0;

      if (*port) {
        port_range->start = *port;
        *port = 0;

        const f_string_static_t adjusted = macro_f_string_static_t_initialize_1(address->string + port_range->start, 0, address->used - port_range->start);

        main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, adjusted, port);
        if (F_status_is_error(main->setting.state.status)) return;

        address->string[port_range->start] = 0;
        address->used = port_range->start;

        while (address->used && address->string[address->used] != f_string_ascii_colon_s.string[0]) --address->used;
      }

      main->setting.state.status = F_okay;

      return;
    }

    *port = 0;
    port_range->start = address->used;

    while (--port_range->start) {
      if (address->string[port_range->start] == f_string_ascii_colon_s.string[0]) break;
    } // while

    if (port_range->start && ++port_range->start < address->used) {
      const f_string_static_t adjusted = macro_f_string_static_t_initialize_1(address->string + port_range->start, 0, address->used - port_range->start);

      main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, adjusted, port);
      if (F_status_is_error(main->setting.state.status)) return;

      address->string[--port_range->start] = 0;
      address->used = port_range->start;
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
