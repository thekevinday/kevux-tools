#include "../tacocat.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_tacocat_program_version_s_
  const f_string_static_t kt_tacocat_program_version_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_program_version_s, 0, KT_TACOCAT_program_version_s_length);
#endif // _di_kt_tacocat_program_version_s_

#ifndef _di_kt_tacocat_program_name_s_
  const f_string_static_t kt_tacocat_program_name_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_program_name_s, 0, KT_TACOCAT_program_name_s_length);
  const f_string_static_t kt_tacocat_program_name_long_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_program_name_long_s, 0, KT_TACOCAT_program_name_long_s_length);
#endif // _di_kt_tacocat_program_name_s_

#ifndef kt_tacocat_program_help_parameters_s_
  // Not used.
#endif // _di_utf8_program_help_parameters_s_

#ifndef _di_kt_tacocat_s_
  const f_string_static_t kt_tacocat_abort_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_abort_s, 0, KT_TACOCAT_abort_s_length);
  const f_string_static_t kt_tacocat_classic_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_classic_s, 0, KT_TACOCAT_classic_s_length);
  const f_string_static_t kt_tacocat_digit_negative_one_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_digit_negative_one_s, 0, KT_TACOCAT_digit_negative_one_s_length);
  const f_string_static_t kt_tacocat_done_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_done_s, 0, KT_TACOCAT_done_s_length);
  const f_string_static_t kt_tacocat_kevux_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_kevux_s, 0, KT_TACOCAT_kevux_s_length);
  const f_string_static_t kt_tacocat_file_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_file_s, 0, KT_TACOCAT_file_s_length);
  const f_string_static_t kt_tacocat_network_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_network_s, 0, KT_TACOCAT_network_s_length);
  const f_string_static_t kt_tacocat_network_or_socket_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_network_or_socket_s, 0, KT_TACOCAT_network_or_socket_s_length);
  const f_string_static_t kt_tacocat_next_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_next_s, 0, KT_TACOCAT_next_s_length);
  const f_string_static_t kt_tacocat_receive_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_receive_s, 0, KT_TACOCAT_receive_s_length);
  const f_string_static_t kt_tacocat_resend_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_resend_s, 0, KT_TACOCAT_resend_s_length);
  const f_string_static_t kt_tacocat_salt_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_salt_s, 0, KT_TACOCAT_salt_s_length);
  const f_string_static_t kt_tacocat_send_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_send_s, 0, KT_TACOCAT_send_s_length);
  const f_string_static_t kt_tacocat_send_build_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_send_build_s, 0, KT_TACOCAT_send_build_s_length);
  const f_string_static_t kt_tacocat_send_combine_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_send_combine_s, 0, KT_TACOCAT_send_combine_s_length);
  const f_string_static_t kt_tacocat_send_connect_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_send_connect_s, 0, KT_TACOCAT_send_connect_s_length);
  const f_string_static_t kt_tacocat_send_done_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_send_done_s, 0, KT_TACOCAT_send_done_s_length);
  const f_string_static_t kt_tacocat_send_file_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_send_file_s, 0, KT_TACOCAT_send_file_s_length);
  const f_string_static_t kt_tacocat_send_header_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_send_header_s, 0, KT_TACOCAT_send_header_s_length);
  const f_string_static_t kt_tacocat_send_payload_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_send_payload_s, 0, KT_TACOCAT_send_payload_s_length);
  const f_string_static_t kt_tacocat_send_size_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_send_size_s, 0, KT_TACOCAT_send_size_s_length);
  const f_string_static_t kt_tacocat_socket_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_socket_s, 0, KT_TACOCAT_socket_s_length);
  const f_string_static_t kt_tacocat_tacocat_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_tacocat_s, 0, KT_TACOCAT_tacocat_s_length);
  const f_string_static_t kt_tacocat_two_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_two_s, 0, KT_TACOCAT_two_s_length);
#endif // _di_kt_tacocat_s_

#ifndef _di_kt_tacocat_parameter_s_
  const f_string_static_t kt_tacocat_short_interval_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_short_interval_s, 0, KT_TACOCAT_short_interval_s_length);
  const f_string_static_t kt_tacocat_short_max_buffer_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_short_max_buffer_s, 0, KT_TACOCAT_short_max_buffer_s_length);
  const f_string_static_t kt_tacocat_short_receive_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_short_receive_s, 0, KT_TACOCAT_short_receive_s_length);
  const f_string_static_t kt_tacocat_short_resolve_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_short_resolve_s, 0, KT_TACOCAT_short_resolve_s_length);
  const f_string_static_t kt_tacocat_short_send_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_short_send_s, 0, KT_TACOCAT_short_send_s_length);

  const f_string_static_t kt_tacocat_long_interval_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_long_interval_s, 0, KT_TACOCAT_long_interval_s_length);
  const f_string_static_t kt_tacocat_long_max_buffer_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_long_max_buffer_s, 0, KT_TACOCAT_long_max_buffer_s_length);
  const f_string_static_t kt_tacocat_long_receive_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_long_receive_s, 0, KT_TACOCAT_long_receive_s_length);
  const f_string_static_t kt_tacocat_long_resolve_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_long_resolve_s, 0, KT_TACOCAT_long_resolve_s_length);
  const f_string_static_t kt_tacocat_long_send_s = macro_f_string_static_t_initialize_1(KT_TACOCAT_long_send_s, 0, KT_TACOCAT_long_send_s_length);
#endif // _di_kt_tacocat_parameter_s_

#ifdef __cplusplus
} // extern "C"
#endif
