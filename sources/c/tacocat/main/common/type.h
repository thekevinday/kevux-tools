/**
 * Kevux Tools - TacocaT
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _kt_tacocat_common_type_h
#define _kt_tacocat_common_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * flag: Flags passed to the main function.
 *
 * status_thread: A status used eclusively by the threaded signal handler.
 * state:         The state data used when processing data.
 *
 * pid_file:   The PID file.
 * file_froms: An array of input files.
 * file_tos:   An array of output files.
 *
 * buffer:   A string buffer used for caching purposes.
 * pid_name: The name of the PID file without the path and without the file extension (.pid).
 * pid_path: A file path to the directory containing the PID file.
 *
 * froms: An array of buffers for receiving data from clients.
 * tos:   An array of buffers for sending data to clients.
 */
#ifndef _di_kt_tacocat_setting_t_
  typedef struct {
    uint64_t flag;

    f_status_t status_thread;
    f_state_t state;

    f_file_t pid_file;
    f_files_t file_froms;
    f_files_t file_tos;

    f_string_dynamic_t buffer;
    f_string_dynamic_t pid_path;
    f_string_dynamic_t pid_name;

    f_string_dynamics_t froms;
    f_string_dynamics_t tos;
  } kt_tacocat_setting_t;

  #define kt_tacocat_setting_t_initialize \
    { \
      kt_tacocat_main_flag_none_e, \
      F_none, \
      macro_f_state_t_initialize_1(kt_tacocat_allocation_large_d, kt_tacocat_allocation_small_d, F_none, 0, 0, &fll_program_standard_signal_handle, 0, 0, 0, 0), \
      f_file_t_initialize, \
      f_files_t_initialize, \
      f_files_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_dynamics_t_initialize, \
    }
#endif // _di_kt_tacocat_setting_t_

/**
 * The main program data as a single structure.
 *
 * program: The main program data.
 * setting: The settings data.
 */
#ifndef _di_kt_tacocat_main_t_
  typedef struct {
    fll_program_data_t program;
    kt_tacocat_setting_t setting;
  } kt_tacocat_main_t;

  #define kt_tacocat_main_t_initialize \
    { \
      fll_program_data_t_initialize, \
      kt_tacocat_setting_t_initialize, \
    }
#endif // _di_kt_tacocat_main_t_

/**
 * Deallocate main program data.
 *
 * @param setting_make
 *   The make setting data.
 *
 *   This does not alter main.setting.state.status.
 */
#ifndef _di_kt_tacocat_main_delete_
  extern void kt_tacocat_main_delete(kt_tacocat_main_t * const main);
#endif // _di_kt_tacocat_main_delete_

/**
 * Delete the program main setting data.
 *
 * @param setting
 *   The program main setting data.
 *
 *   This does not alter setting.state.status.
 *
 * @return
 *   F_none on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_kt_tacocat_setting_delete_
  extern f_status_t kt_tacocat_setting_delete(kt_tacocat_setting_t * const setting);
#endif // _di_kt_tacocat_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_common_type_h
