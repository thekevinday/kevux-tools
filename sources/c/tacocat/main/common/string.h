/**
 * Kevux Tools - TacocaT
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common string structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _kt_tacocat_common_string_h
#define _kt_tacocat_common_string_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The program version.
 */
#ifndef _di_kt_tacocat_program_version_s_
  #define KT_TACOCAT_program_version_major_s F_string_ascii_0_s
  #define KT_TACOCAT_program_version_minor_s F_string_ascii_5_s
  #define KT_TACOCAT_program_version_micro_s F_string_ascii_0_s

  #define KT_TACOCAT_program_version_major_s_length F_string_ascii_0_s_length
  #define KT_TACOCAT_program_version_minor_s_length F_string_ascii_5_s_length
  #define KT_TACOCAT_program_version_micro_s_length F_string_ascii_0_s_length

  #if !(defined(KT_TACOCAT_program_version_nano_prefix_s) && defined(KT_TACOCAT_program_version_nano_prefix_s_length))
    #define KT_TACOCAT_program_version_nano_prefix_s
    #define KT_TACOCAT_program_version_nano_prefix_s_length 0
  #endif // !(defined(KT_TACOCAT_program_version_nano_prefix_s) && defined(KT_TACOCAT_program_version_nano_prefix_s_length))

  #if !(defined(KT_TACOCAT_program_version_nano_s) && defined(KT_TACOCAT_program_version_nano_s_length))
    #define KT_TACOCAT_program_version_nano_s
    #define KT_TACOCAT_program_version_nano_s_length 0
  #endif // !(defined(KT_TACOCAT_program_version_nano_s) && defined(KT_TACOCAT_program_version_nano_s_length))

  #define KT_TACOCAT_program_version_s KT_TACOCAT_program_version_major_s F_string_ascii_period_s KT_TACOCAT_program_version_minor_s F_string_ascii_period_s KT_TACOCAT_program_version_micro_s KT_TACOCAT_program_version_nano_prefix_s KT_TACOCAT_program_version_nano_s

  #define KT_TACOCAT_program_version_s_length KT_TACOCAT_program_version_major_s_length + F_string_ascii_period_s_length + KT_TACOCAT_program_version_minor_s_length + F_string_ascii_period_s_length + KT_TACOCAT_program_version_micro_s_length + KT_TACOCAT_program_version_nano_prefix_s_length + KT_TACOCAT_program_version_nano_s_length

  extern const f_string_static_t kt_tacocat_program_version_s;
#endif // _di_kt_tacocat_program_version_s_

/**
 * The program name.
 */
#ifndef _di_kt_tacocat_program_name_s_
  #define KT_TACOCAT_program_name_s      "tacocat"
  #define KT_TACOCAT_program_name_long_s "TacocaT"

  #define KT_TACOCAT_program_name_s_length      7
  #define KT_TACOCAT_program_name_long_s_length 7

  extern const f_string_static_t kt_tacocat_program_name_s;
  extern const f_string_static_t kt_tacocat_program_name_long_s;
#endif // _di_kt_tacocat_program_name_s_

/**
 * The program help related data.
 */
#ifndef kt_tacocat_program_help_parameters_s_
  // Not used.
#endif // _di_utf8_program_help_parameters_s_

/**
 * Additional strings used for various purposes.
 *
 * kt_tacocat_*_s: Arbitrary strings.
 */
#ifndef _di_kt_tacocat_s_
  #define KT_TACOCAT_classic_s           "classic"
  #define KT_TACOCAT_kevux_s             "kevux"
  #define KT_TACOCAT_file_s              "file"
  #define KT_TACOCAT_network_s           "network"
  #define KT_TACOCAT_network_or_socket_s "network / socket"
  #define KT_TACOCAT_receive_s           "receive"
  #define KT_TACOCAT_send_s              "send"
  #define KT_TACOCAT_socket_s            "socket"
  #define KT_TACOCAT_tacocat_s           "tacocat"
  #define KT_TACOCAT_two_s               "two"

  #define KT_TACOCAT_classic_s_length           7
  #define KT_TACOCAT_kevux_s_length             5
  #define KT_TACOCAT_file_s_length              4
  #define KT_TACOCAT_network_s_length           7
  #define KT_TACOCAT_network_or_socket_s_length 16
  #define KT_TACOCAT_receive_s_length           7
  #define KT_TACOCAT_send_s_length              4
  #define KT_TACOCAT_socket_s_length            6
  #define KT_TACOCAT_tacocat_s_length           7
  #define KT_TACOCAT_two_s_length               3

  extern const f_string_static_t kt_tacocat_classic_s;
  extern const f_string_static_t kt_tacocat_kevux_s;
  extern const f_string_static_t kt_tacocat_file_s;
  extern const f_string_static_t kt_tacocat_network_s;
  extern const f_string_static_t kt_tacocat_network_or_socket_s;
  extern const f_string_static_t kt_tacocat_receive_s;
  extern const f_string_static_t kt_tacocat_send_s;
  extern const f_string_static_t kt_tacocat_socket_s;
  extern const f_string_static_t kt_tacocat_tacocat_s;
  extern const f_string_static_t kt_tacocat_two_s;
#endif // _di_kt_tacocat_s_

/**
 * The main program parameters.
 */
#ifndef _di_kt_tacocat_parameter_s_
  #define KT_TACOCAT_short_interval_s "I"
  #define KT_TACOCAT_short_receive_s  "r"
  #define KT_TACOCAT_short_resolve_s  "R"
  #define KT_TACOCAT_short_send_s     "s"

  #define KT_TACOCAT_long_interval_s "interval"
  #define KT_TACOCAT_long_receive_s  "receive"
  #define KT_TACOCAT_long_resolve_s  "resolve"
  #define KT_TACOCAT_long_send_s     "send"

  #define KT_TACOCAT_short_interval_s_length 1
  #define KT_TACOCAT_short_receive_s_length  1
  #define KT_TACOCAT_short_resolve_s_length  1
  #define KT_TACOCAT_short_send_s_length     1

  #define KT_TACOCAT_long_interval_s_length 8
  #define KT_TACOCAT_long_receive_s_length  7
  #define KT_TACOCAT_long_resolve_s_length  7
  #define KT_TACOCAT_long_send_s_length     4

  extern const f_string_static_t kt_tacocat_short_interval_s;
  extern const f_string_static_t kt_tacocat_short_receive_s;
  extern const f_string_static_t kt_tacocat_short_resolve_s;
  extern const f_string_static_t kt_tacocat_short_send_s;

  extern const f_string_static_t kt_tacocat_long_interval_s;
  extern const f_string_static_t kt_tacocat_long_receive_s;
  extern const f_string_static_t kt_tacocat_long_resolve_s;
  extern const f_string_static_t kt_tacocat_long_send_s;
#endif // _di_kt_tacocat_parameter_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_common_string_h
