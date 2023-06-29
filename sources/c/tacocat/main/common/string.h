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
  #define KT_TACOCAT_program_help_parameters_s "socket(s)/address(s)"
  #define KT_TACOCAT_program_help_parameters_s_length 20

  extern const f_string_static_t kt_tacocat_program_help_parameters_s;
#endif // _di_utf8_program_help_parameters_s_

/**
 * Additional strings used for various purposes.
 *
 * kt_tacocat_*_s: Arbitrary strings.
 */
#ifndef _di_kt_tacocat_s_
  #define KT_TACOCAT_network_s "network"
  #define KT_TACOCAT_pid_s     "pid"
  #define KT_TACOCAT_socket_s  "socket"
  #define KT_TACOCAT_tacocat_s "tacocat"

  #define KT_TACOCAT_network_s_length 7
  #define KT_TACOCAT_pid_s_length     3
  #define KT_TACOCAT_socket_s_length  6
  #define KT_TACOCAT_tacocat_s_length 7

  extern const f_string_static_t kt_tacocat_network_s;
  extern const f_string_static_t kt_tacocat_pid_s;
  extern const f_string_static_t kt_tacocat_socket_s;
  extern const f_string_static_t kt_tacocat_tacocat_s;
#endif // _di_kt_tacocat_s_

/**
 * Additional strings directly associated with PID file and path.
 *
 * kt_tacocat_pid_*_s: Pid Path specific strings.
 */
#ifndef _di_kt_tacocat_pid_s_
  #ifndef KT_TACOCAT_pid_path_s
    #define KT_TACOCAT_pid_path_s "/var/run/tacocat/"
  #endif // KT_TACOCAT_pid_path_s

  #ifndef KT_TACOCAT_pid_path_s_length
    #define KT_TACOCAT_pid_path_s_length 17
  #endif // KT_TACOCAT_pid_path_s_length

  extern const f_string_static_t kt_tacocat_pid_path_s;
#endif // _di_kt_tacocat_pid_s_

/**
 * The main program parameters.
 */
#ifndef _di_kt_tacocat_parameter_s_
  #define KT_TACOCAT_short_background_s "b"
  #define KT_TACOCAT_short_from_s       "f"
  #define KT_TACOCAT_short_pid_s        "p"
  #define KT_TACOCAT_short_pid_name_s   "N"
  #define KT_TACOCAT_short_pid_path_s   "P"
  #define KT_TACOCAT_short_resolve_s    "R"
  #define KT_TACOCAT_short_to_s         "t"

  #define KT_TACOCAT_long_background_s "background"
  #define KT_TACOCAT_long_from_s       "from"
  #define KT_TACOCAT_long_pid_s        "pid"
  #define KT_TACOCAT_long_pid_name_s   "pid_name"
  #define KT_TACOCAT_long_pid_path_s   "pid_path"
  #define KT_TACOCAT_long_resolve_s    "resolve"
  #define KT_TACOCAT_long_to_s         "to"

  #define KT_TACOCAT_short_background_s_length 1
  #define KT_TACOCAT_short_from_s_length       1
  #define KT_TACOCAT_short_pid_s_length        1
  #define KT_TACOCAT_short_pid_name_s_length   1
  #define KT_TACOCAT_short_pid_path_s_length   1
  #define KT_TACOCAT_short_resolve_s_length    1
  #define KT_TACOCAT_short_to_s_length         1

  #define KT_TACOCAT_long_background_s_length 10
  #define KT_TACOCAT_long_from_s_length       4
  #define KT_TACOCAT_long_pid_s_length        3
  #define KT_TACOCAT_long_pid_name_s_length   8
  #define KT_TACOCAT_long_pid_path_s_length   8
  #define KT_TACOCAT_long_resolve_s_length    7
  #define KT_TACOCAT_long_to_s_length         2

  extern const f_string_static_t kt_tacocat_short_background_s;
  extern const f_string_static_t kt_tacocat_short_from_s;
  extern const f_string_static_t kt_tacocat_short_pid_s;
  extern const f_string_static_t kt_tacocat_short_pid_name_s;
  extern const f_string_static_t kt_tacocat_short_pid_path_s;
  extern const f_string_static_t kt_tacocat_short_resolve_s;
  extern const f_string_static_t kt_tacocat_short_to_s;

  extern const f_string_static_t kt_tacocat_long_background_s;
  extern const f_string_static_t kt_tacocat_long_from_s;
  extern const f_string_static_t kt_tacocat_long_pid_s;
  extern const f_string_static_t kt_tacocat_long_pid_name_s;
  extern const f_string_static_t kt_tacocat_long_pid_path_s;
  extern const f_string_static_t kt_tacocat_long_resolve_s;
  extern const f_string_static_t kt_tacocat_long_to_s;
#endif // _di_kt_tacocat_parameter_s_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_common_string_h
