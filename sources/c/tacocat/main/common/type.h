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
 * block_size_receive: The size in bytes to used to represent a block when receiving packets.
 * block_size_send:    The size in bytes to used to represent a block when sending packets.
 *
 * status_thread: A status used eclusively by the threaded signal handler.
 * state:         The state data used when processing data.
 *
 * file_receives: An array of input files.
 * file_sends:    An array of output files.
 *
 * socket_receives: An array of the network sockets for receiving.
 * socket_sends:    An array of the network sockets for sending.
 *
 * buffer:   A string buffer used for caching purposes.
 *
 * receives: An array of buffers for receiving data receive clients.
 * sends:    An array of buffers for sending data send clients.
 */
#ifndef _di_kt_tacocat_setting_t_
  typedef struct {
    uint64_t flag;

    f_number_unsigned_t block_size_receive;
    f_number_unsigned_t block_size_send;

    f_status_t status_thread;
    f_state_t state;

    f_files_t file_receives;
    f_files_t file_sends;

    f_sockets_t socket_receives;
    f_sockets_t socket_sends;

    f_string_dynamic_t buffer;

    f_string_dynamics_t receives;
    f_string_dynamics_t sends;
  } kt_tacocat_setting_t;

  #define kt_tacocat_setting_t_initialize \
    { \
      kt_tacocat_main_flag_none_e, \
      kt_tacocat_block_size_receive_d, \
      kt_tacocat_block_size_send_d, \
      F_none, \
      macro_f_state_t_initialize_1(kt_tacocat_allocation_large_d, kt_tacocat_allocation_small_d, F_none, 0, 0, &fll_program_standard_signal_handle, 0, 0, 0, 0), \
      f_files_t_initialize, \
      f_files_t_initialize, \
      f_sockets_t_initialize, \
      f_sockets_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_dynamics_t_initialize, \
    }
#endif // _di_kt_tacocat_setting_t_

/**
 * The TacocaT callbacks.
 *
 * setting_load_send_receive: Process loading the settings regarding send and receive, handling DNS resolution and file opening as needed.
 */
#ifndef _di_kt_tacocat_callback_t_
  typedef struct {
    void (*setting_load_send_receive)(const f_console_arguments_t arguments, void * const main);
  } kt_tacocat_callback_t;

  #define kt_tacocat_callback_t_initialize \
    { \
      0, \
    }
#endif // _di_kt_tacocat_callback_t_

/**
 * The main program data as a single structure.
 *
 * program:  The main program data.
 * setting:  The settings data.
 * callback: The program callbacks.
 */
#ifndef _di_kt_tacocat_main_t_
  typedef struct {
    fll_program_data_t program;
    kt_tacocat_setting_t setting;
    kt_tacocat_callback_t callback;
  } kt_tacocat_main_t;

  #define kt_tacocat_main_t_initialize \
    { \
      fll_program_data_t_initialize, \
      kt_tacocat_setting_t_initialize, \
      kt_tacocat_callback_t_initialize, \
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
