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
 * A set containing all socket related data sets.
 *
 * block_size: The size in bytes to used to represent a block when sending or receiving packets.
 *
 * flags:   An array of flags for each socket.
 * files:   An array of files for each socket.
 * polls:   An array of sockets to poll, specifically for passing to f_file_poll().
 * sockets: An array of the network sockets.
 * statuss: An array of statuses for each socket.
 *
 * names:   An array of names for each socket.
 * buffers: An array of buffers for sending or receiving data between clients for each socket.
 * packets: An array of simple packet ranges representing the parts of the packet for each socket for use during processing.
 */
#ifndef _di_kt_tacocat_socket_set_t_
  typedef struct {
    f_number_unsigned_t block_size;

    f_uint16s_t flags;
    f_files_t files;
    f_polls_t polls;
    f_sockets_t sockets;
    f_statuss_t statuss;

    f_string_dynamics_t names;
    f_string_dynamics_t buffers;
    f_fss_simple_packet_ranges_t packets;
  } kt_tacocat_socket_set_t;

  #define kt_tacocat_socket_set_t_initialize \
    { \
      kt_tacocat_block_size_d, \
      f_uint16s_t_initialize, \
      f_files_t_initialize, \
      f_polls_t_initialize, \
      f_sockets_t_initialize, \
      f_statuss_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_fss_simple_packet_ranges_t_initialize, \
    }

  #define macro_kt_tacocat_setting_t_initialize_1(block_size) \
    { \
      block_size, \
      f_uint16s_t_initialize, \
      f_files_t_initialize, \
      f_polls_t_initialize, \
      f_sockets_t_initialize, \
      f_statuss_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_fss_simple_packet_ranges_t_initialize, \
    }
#endif // _di_kt_tacocat_socket_set_t_

/**
 * The main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * flag:     Flags passed to the main function.
 * interval: The poll interval to use.
 *
 * status_receive: A status used exclusively by the receive thread.
 * status_send:    A status used exclusively by the send thread.
 * status_signal:  A status used exclusively by the threaded signal handler.
 *
 * state: The state data used when processing data.
 *
 * receive: The socket set for receiving data receive clients.
 * send:    The socket set for sending data send clients.
 *
 * buffer: A string buffer used for caching purposes.
 */
#ifndef _di_kt_tacocat_setting_t_
  typedef struct {
    uint64_t flag;
    uint64_t interval;

    f_status_t status_receive;
    f_status_t status_send;
    f_status_t status_signal;

    f_state_t state;

    kt_tacocat_socket_set_t receive;
    kt_tacocat_socket_set_t send;

    f_string_dynamic_t buffer;
  } kt_tacocat_setting_t;

  #define kt_tacocat_setting_t_initialize \
    { \
      kt_tacocat_main_flag_none_e, \
      kt_tacocat_interval_poll_d, \
      F_okay, \
      F_okay, \
      F_okay, \
      macro_f_state_t_initialize_1(kt_tacocat_allocation_large_d, kt_tacocat_allocation_small_d, F_okay, 0, 0, &fll_program_standard_signal_handle, 0, 0, 0, 0), \
      macro_kt_tacocat_setting_t_initialize_1(kt_tacocat_block_size_receive_d), \
      macro_kt_tacocat_setting_t_initialize_1(kt_tacocat_block_size_send_d), \
      f_string_dynamic_t_initialize, \
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
 * The main thread settings.
 */
#ifndef _di_kt_tacocat_thread_t_
  typedef struct {
    f_thread_id_t id_receive;
    f_thread_id_t id_send;
  } kt_tacocat_thread_t;

  #define kt_tacocat_thread_t_initialize \
    { \
      f_thread_id_t_initialize, \
      f_thread_id_t_initialize, \
    }
#endif // _di_kt_tacocat_thread_t_

/**
 * The main program data as a single structure.
 *
 * program:  The main program data.
 * setting:  The settings data.
 * callback: The program callbacks.
 * thread:   The program thread data.
 */
#ifndef _di_kt_tacocat_main_t_
  typedef struct {
    fll_program_data_t program;
    kt_tacocat_setting_t setting;
    kt_tacocat_callback_t callback;
    kt_tacocat_thread_t thread;
  } kt_tacocat_main_t;

  #define kt_tacocat_main_t_initialize \
    { \
      fll_program_data_t_initialize, \
      kt_tacocat_setting_t_initialize, \
      kt_tacocat_callback_t_initialize, \
      kt_tacocat_thread_t_initialize, \
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
 * @param program
 *   The main program data.
 * @param setting
 *   The program main setting data.
 *
 *   This does not alter setting.state.status.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_kt_tacocat_setting_delete_
  extern f_status_t kt_tacocat_setting_delete(const fll_program_data_t program, kt_tacocat_setting_t * const setting);
#endif // _di_kt_tacocat_setting_delete_

/**
 * Delete the program main thread data.
 *
 * @param program
 *   The main program data.
 * @param thread
 *   The program main thread data.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 */
#ifndef _di_kt_tacocat_thread_delete_
  extern f_status_t kt_tacocat_thread_delete(const fll_program_data_t program, kt_tacocat_thread_t * const thread);
#endif // _di_kt_tacocat_thread_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_common_type_h
