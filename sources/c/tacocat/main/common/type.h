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
 * A set of all socket related properties.
 *
 * size_block: The size in bytes to used to represent a block when sending or receiving packets.
 * size_done:  The size in bytes that are done being processed (generally used by send/write).
 * size_total: The size in bytes tht represent the entire size to be processed (size_done should eventually equal this).
 *
 * flag:  A set of flags.
 * step:  The current step the socket set is operating under.
 * retry: The current number of retries performed.
 * part:  The current active part number.
 *
 * file:   The file structure.
 * socket: Socket structure.
 * status: The status of the socket operations.
 *
 * range:                       A generic range, often used for FSS processing.
 * objects:                     An array of FSS Objects.
 * objects_header:              An array of FSS Objects, for the Header section.
 * objects_signature:           An array of FSS Objects, for the Signature section.
 * contents:                    An array of FSS Contents.
 * contents_header:             An array of FSS Contents, for the Header section.
 * contents_signature:          An array of FSS Contents, for the Signature section.
 * objects_delimits:            An array of FSS Object delimits.
 * objects_delimits_header:     An array of FSS Object delimits, for the Header section.
 * objects_delimits_signature:  An array of FSS Object delimits, for the Signature section.
 * contents_delimits:           An array of FSS Content delimits.
 * contents_delimits_header:    An array of FSS Content delimits, for the Header section.
 * contents_delimits_signature: An array of FSS Content delimits, for the Signature section.
 * parts:                       An array of numbers where each index represents a part number.
 * objects_quoted_header:       An array of FSS Objects quoted flags, for the Header section.
 * objects_quoted_signature:    An array of FSS Objects quoted flags, for the Header section.
 * contents_quoted_header:      An array of FSS Content quoted flags, for the Header section.
 * contents_quoted_signature:   An array of FSS Content quoted flags, for the Header section.
 * comments:                    An array of FSS comments.
 * state:                       Basic state information, usually passed to the FSS functions.
 *
 * buffer:      A buffer for sending or receiving data between clients.
 * cache:       A cache used for various purposes, but primarily for the building of the send packet.
 * client:      A single client address for some network connection.
 * header:      A buffer used for the header part and possibly the reset of a packet, except for the actual payload.
 * name:        A file name for reading from or writing to.
 * network:     A network name for the socket.
 * packet:      The simple packet range representing the parts of the packet for use during processing.
 * write_state: State data for the packet write operation.
 *
 * abstruses: The abstruse header map array, used for building the headers when sending a response.
 * headers:   The map of the headers after being processed for use when buulding the headers when sending a response.
 */
#ifndef _di_kt_tacocat_socket_set_t_
  typedef struct {
    f_number_unsigned_t size_block;
    size_t size_done;
    size_t size_total;

    uint16_t flag;
    uint16_t step;
    uint16_t retry;
    f_number_unsigned_t part;

    f_file_t file;
    f_socket_t socket;
    f_status_t status;

    f_range_t range;
    f_ranges_t objects;
    f_ranges_t objects_header;
    f_ranges_t objects_signature;
    f_rangess_t contents;
    f_rangess_t contents_header;
    f_rangess_t contents_signature;
    f_number_unsigneds_t objects_delimits;
    f_number_unsigneds_t objects_delimits_header;
    f_number_unsigneds_t objects_delimits_signature;
    f_number_unsigneds_t contents_delimits;
    f_number_unsigneds_t contents_delimits_header;
    f_number_unsigneds_t contents_delimits_signature;
    f_number_unsigneds_t parts;
    f_uint8s_t objects_quoted_header;
    f_uint8s_t objects_quoted_signature;
    f_uint8ss_t contents_quoted_header;
    f_uint8ss_t contents_quoted_signature;
    f_ranges_t comments;
    f_state_t state;

    f_string_dynamic_t buffer;
    f_string_dynamic_t cache;
    f_string_dynamic_t client;
    f_string_dynamic_t header;
    f_string_dynamic_t id;
    f_string_dynamic_t name;
    f_string_dynamic_t network;
    f_fss_simple_packet_range_t packet;
    f_fss_payload_header_state_t write_state;

    f_abstruse_maps_t abstruses;
    f_string_maps_t headers;
  } kt_tacocat_socket_set_t;

  #define kt_tacocat_socket_set_t_initialize \
    { \
      kt_tacocat_block_size_d, \
      0, \
      0, \
      0, \
      0, \
      f_file_t_initialize, \
      f_socket_t_initialize, \
      f_status_t_initialize, \
      f_range_t_initialize, \
      f_ranges_t_initialize, \
      f_ranges_t_initialize, \
      f_ranges_t_initialize, \
      f_rangess_t_initialize, \
      f_rangess_t_initialize, \
      f_rangess_t_initialize, \
      f_number_unsigneds_t_initialize, \
      f_number_unsigneds_t_initialize, \
      f_number_unsigneds_t_initialize, \
      f_number_unsigneds_t_initialize, \
      f_number_unsigneds_t_initialize, \
      f_uint8s_t_initialize, \
      f_uint8s_t_initialize, \
      f_uint8ss_t_initialize, \
      f_uint8ss_t_initialize, \
      f_ranges_t_initialize, \
      f_state_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_fss_simple_packet_range_t_initialize, \
      f_fss_payload_header_state_t_initialize, \
      f_abstruse_maps_t_initialize, \
      f_string_maps_t_initialize, \
    }

  #define macro_kt_tacocat_socket_set_t_initialize_1(size_block) \
    { \
      size_block, \
      0, \
      0, \
      0, \
      0, \
      f_file_t_initialize, \
      f_poll_t_initialize, \
      f_socket_t_initialize, \
      f_status_t_initialize, \
      f_range_t_initialize, \
      f_ranges_t_initialize, \
      f_ranges_t_initialize, \
      f_ranges_t_initialize, \
      f_rangess_t_initialize, \
      f_rangess_t_initialize, \
      f_rangess_t_initialize, \
      f_number_unsigneds_t_initialize, \
      f_number_unsigneds_t_initialize, \
      f_number_unsigneds_t_initialize, \
      f_number_unsigneds_t_initialize, \
      f_number_unsigneds_t_initialize, \
      f_uint8s_t_initialize, \
      f_uint8s_t_initialize, \
      f_uint8ss_t_initialize, \
      f_uint8ss_t_initialize, \
      f_ranges_t_initialize, \
      f_state_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_fss_simple_packet_range_t_initialize, \
      f_fss_payload_header_state_t_initialize, \
      f_abstruse_maps_t_initialize, \
      f_string_maps_t_initialize, \
    }

  #define macro_kt_tacocat_socket_set_t_initialize_2(size_block, write_state) \
    { \
      size_block, \
      0, \
      0, \
      0, \
      0, \
      f_file_t_initialize, \
      f_poll_t_initialize, \
      f_socket_t_initialize, \
      f_status_t_initialize, \
      f_range_t_initialize, \
      f_ranges_t_initialize, \
      f_ranges_t_initialize, \
      f_ranges_t_initialize, \
      f_rangess_t_initialize, \
      f_rangess_t_initialize, \
      f_rangess_t_initialize, \
      f_number_unsigneds_t_initialize, \
      f_number_unsigneds_t_initialize, \
      f_number_unsigneds_t_initialize, \
      f_number_unsigneds_t_initialize, \
      f_number_unsigneds_t_initialize, \
      f_uint8s_t_initialize, \
      f_uint8s_t_initialize, \
      f_uint8ss_t_initialize, \
      f_uint8ss_t_initialize, \
      f_ranges_t_initialize, \
      f_state_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_fss_simple_packet_range_t_initialize, \
      write_state, \
      f_abstruse_maps_t_initialize, \
      f_string_maps_t_initialize, \
    }
#endif // _di_kt_tacocat_socket_set_t_

/**
 * An array of socket sets.
 *
 * array: The array of socket sets.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_kt_tacocat_socket_sets_t_
  typedef struct {
    kt_tacocat_socket_set_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } kt_tacocat_socket_sets_t;

  #define kt_tacocat_socket_sets_t_initialize { 0, 0, 0 }

  #define macro_kt_tacocat_socket_sets_t_initialize_1(array, size, used) { array, size, used }
  #define macro_kt_tacocat_socket_sets_t_initialize_2(array, length) { array, length, length }

  #define macro_kt_tacocat_socket_sets_t_clear(socket_set) macro_f_string_statics_t_clear(socket_set)
#endif // _di_kt_tacocat_socket_sets_t_

/**
 * The main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * flag:           Flags passed to the main function.
 * interval:       The poll interval to use.
 * interval_fast:  A poll interval to use when needing the interval to be short.
 * max_buffer:     The maximum buffer size to use on receive.
 * active_receive: The number of active receive processes, after initial connection is established.
 * active_send:    The number of active send processes, after initial connection is established.
 *
 * status_receive: A status used exclusively by the receive thread.
 * status_send:    A status used exclusively by the send thread.
 * status_signal:  A status used exclusively by the threaded signal handler.
 *
 * state: The state data used when processing data.
 *
 * receive_polls: An array of sockets to poll for receiving data, specifically for passing to f_file_poll().
 * send_polls:    An array of sockets to poll for sending data, specifically for passing to f_file_poll().
 *
 * receive: The socket set for receiving data receive clients.
 * send:    The socket set for sending data send clients.
 */
#ifndef _di_kt_tacocat_setting_t_
  typedef struct {
    uint64_t flag;
    uint64_t interval;
    uint64_t interval_fast;
    f_number_unsigned_t max_buffer;
    f_number_unsigned_t active_receive;
    f_number_unsigned_t active_send;

    f_status_t status_receive;
    f_status_t status_send;
    f_status_t status_signal;

    f_state_t state;

    f_polls_t receive_polls;
    f_polls_t send_polls;

    kt_tacocat_socket_sets_t receive;
    kt_tacocat_socket_sets_t send;
  } kt_tacocat_setting_t;

  #define kt_tacocat_setting_t_initialize \
    { \
      kt_tacocat_main_flag_max_buffer_e, \
      kt_tacocat_interval_poll_d, \
      kt_tacocat_interval_poll_fast_d, \
      kt_tacocat_max_buffer_d, \
      0, \
      0, \
      F_okay, \
      F_okay, \
      F_okay, \
      macro_f_state_t_initialize_1(kt_tacocat_allocation_large_d, kt_tacocat_allocation_small_d, F_okay, 0, 0, &fll_program_standard_signal_handle, 0, 0, 0, 0), \
      f_polls_t_initialize, \
      f_polls_t_initialize, \
      kt_tacocat_socket_sets_t_initialize, \
      kt_tacocat_socket_sets_t_initialize, \
    }
#endif // _di_kt_tacocat_setting_t_

/**
 * The TacocaT caches.
 *
 * peek: A static cache intended to be used for performing a peek on a given network stream.
 *
 * buffer: A string buffer used for caching purposes.
 */
#ifndef _di_kt_tacocat_cache_t_
  typedef struct {
    f_char_t peek[kt_tacocat_cache_size_peek_d];

    f_string_dynamic_t buffer;
  } kt_tacocat_cache_t;

  #define kt_tacocat_cache_t_initialize \
    { \
      { 0 }, \
      f_string_dynamic_t_initialize, \
    }
#endif // _di_kt_tacocat_cache_t_

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
    kt_tacocat_cache_t cache;
  } kt_tacocat_main_t;

  #define kt_tacocat_main_t_initialize \
    { \
      fll_program_data_t_initialize, \
      kt_tacocat_setting_t_initialize, \
      kt_tacocat_callback_t_initialize, \
      kt_tacocat_thread_t_initialize, \
      kt_tacocat_cache_t_initialize, \
    }
#endif // _di_kt_tacocat_main_t_

/**
 * Delete the program main cache data.
 *
 * @param cache
 *   The program main cache data.
 */
#ifndef _di_kt_tacocat_cache_delete_
  extern void kt_tacocat_cache_delete(kt_tacocat_cache_t * const cache);
#endif // _di_kt_tacocat_cache_delete_

/**
 * Deallocate main program data.
 *
 * @param main
 *   The program and settings data.
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
 */
#ifndef _di_kt_tacocat_setting_delete_
  extern void kt_tacocat_setting_delete(kt_tacocat_setting_t * const setting);
#endif // _di_kt_tacocat_setting_delete_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an kt_tacocat_socket_sets_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_kt_tacocat_socket_sets_delete_callback_
  extern f_status_t kt_tacocat_socket_sets_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_kt_tacocat_socket_sets_delete_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_common_type_h
