/**
 * Kevux Tools - TacocaT
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common print functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _kt_tacocat_common_print_h
#define _kt_tacocat_common_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A special array of strings intended for representing funciton names.
 *
 * These are primarily used for printing errors with the function names.
 *
 * The macro macro_kt_tacocat_f() is used to reference the array index by the enum name.
 *
 * macro_kt_tacocat_f():
 *   - name: The name of the function.
 */
#ifndef _di_kt_tacocat_f_a_
  extern const f_string_t kt_tacocat_f_a[];

  #define macro_kt_tacocat_f(name) kt_tacocat_f_a[kt_tacocat_f_##name##_e]
#endif // _di_kt_tacocat_f_a_

/**
 * An enum representing specific indexes within the above array.
 *
 * This is a convenience enum used to make code slightly more readable.
 */
#ifndef _di_kt_tacocat_f_e_
  enum {
    kt_tacocat_f_f_console_parameter_process_e = 0,
    kt_tacocat_f_f_file_close_e,
    kt_tacocat_f_f_file_close_id_e,
    kt_tacocat_f_f_file_open_e,
    kt_tacocat_f_f_file_read_block_e,
    kt_tacocat_f_f_file_size_by_id_e,
    kt_tacocat_f_f_file_write_e,
    kt_tacocat_f_f_fss_simple_packet_extract_range_e,
    kt_tacocat_f_f_memory_array_increase_by_e,
    kt_tacocat_f_f_memory_array_resize_e,
    kt_tacocat_f_f_network_from_ip_name_e,
    kt_tacocat_f_f_network_from_ip_string_e,
    kt_tacocat_f_f_network_is_ip_address_e,
    kt_tacocat_f_f_socket_accept_e,
    kt_tacocat_f_f_socket_bind_inet4_e,
    kt_tacocat_f_f_socket_bind_inet6_e,
    kt_tacocat_f_f_socket_bind_local_e,
    kt_tacocat_f_f_socket_close_e,
    kt_tacocat_f_f_socket_connect_e,
    kt_tacocat_f_f_socket_create_e,
    kt_tacocat_f_f_socket_disconnect_e,
    kt_tacocat_f_f_socket_listen_e,
    kt_tacocat_f_f_socket_option_set_e,
    kt_tacocat_f_f_socket_read_stream_e,
    kt_tacocat_f_f_socket_write_stream_e,
    kt_tacocat_f_f_string_append_nulless_e,
    kt_tacocat_f_f_string_dynamic_append_e,
    kt_tacocat_f_f_string_dynamic_append_nulless_e,
    kt_tacocat_f_f_string_dynamic_terminate_after_e,
    kt_tacocat_f_f_thread_create_e,
    kt_tacocat_f_fl_conversion_dynamic_partial_to_unsigned_detect_e,
    kt_tacocat_f_fl_conversion_dynamic_to_unsigned_detect_e,
    kt_tacocat_f_fl_fss_payload_header_map_e,
    kt_tacocat_f_fll_program_parameter_process_context_e,
    kt_tacocat_f_fll_program_parameter_process_verbosity_e,
    kt_tacocat_f_kt_tacocat_process_socket_set_error_has_e,
    kt_tacocat_f_kt_tacocat_setting_load_address_port_extract_e,
    kt_tacocat_f_kt_tacocat_setting_load_send_receive_allocate_e,
  }; // enum
#endif // _di_kt_tacocat_f_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_common_print_h
