/**
 * Kevux Tools - TacocaT
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common data structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _kt_tacocat_common_h
#define _kt_tacocat_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform the standard program setting load process.
 *
 * This prints error messages as appropriate.
 *
 * If either main or setting is NULL, then this immediately returns without doing anything.
 *
 * @param arguments
 *   The parameters passed to the process (often referred to as command line arguments).
 * @param main
 *   The main program and settings data.
 *
 *   This alters setting.state.status:
 *     F_okay on success.
 *
 *     F_parameter (with error bit) if a parameter is invalid.
 *
 *     Errors (with error bit) from: f_console_parameter_process().
 *     Errors (with error bit) from: f_string_dynamic_append_nulless().
 *     Errors (with error bit) from: fll_program_parameter_process_context().
 *     Errors (with error bit) from: fll_program_parameter_process_verbosity().
 *
 *     Errors (with error bit) from: kt_tacocat_setting_load_send_receive().
 *
 * @see f_console_parameter_process()
 * @see f_string_dynamic_append_nulless()
 * @see fll_program_parameter_process_context()
 * @see fll_program_parameter_process_verbosity()
 *
 * @see kt_tacocat_setting_load_send_receive()
 */
#ifndef _di_kt_tacocat_setting_load_
  extern void kt_tacocat_setting_load(const f_console_arguments_t arguments, kt_tacocat_main_t * const main);
#endif // _di_kt_tacocat_setting_load_

/**
 * Perform the standard program setting load process for the send and receive parameters.
 *
 * This will perform any DNS resolutions as necessary and open any appropriate files.
 *
 * This prints error messages as appropriate.
 *
 * If either main or setting is NULL, then this immediately returns without doing anything.
 *
 * @param arguments
 *   The parameters passed to the process (often referred to as command line arguments).
 * @param main
 *   The main program and settings data.
 *
 *   This must be of type kt_tacocat_main_t.
 *
 *   This alters main.setting.state.status:
 *     F_okay on success.
 *
 *     F_parameter (with error bit) if a parameter is invalid.
 *
 *     Errors (with error bit) from: f_file_exists().
 *     Errors (with error bit) from: f_file_open().
 *     Errors (with error bit) from: f_memory_array_increase_by().
 *     Errors (with error bit) from: f_network_from_ip_name().
 *     Errors (with error bit) from: f_string_dynamic_append_nulless().
 *
 *     Errors (with error bit) from: main.callback.setting_load_send_receive().
 *
 * @see f_file_exists()
 * @see f_file_open()
 * @see f_memory_array_increase_by()
 * @see f_network_from_ip_name()
 * @see f_string_dynamic_append_nulless()
 */
#ifndef _di_kt_tacocat_setting_load_send_receive_
  extern void kt_tacocat_setting_load_send_receive(const f_console_arguments_t arguments, void * const main);
#endif // _di_kt_tacocat_setting_load_send_receive_

/**
 * Process the string and extract any potential port numbers.
 *
 * A port number is expected to be a digit following the last ':' at the end of the string.
 *
 * This does not print error messages.
 *
 * @param main
 *   The main program and settings data.
 *
 *   The main.setting.state.status can be set to either F_network_version_four or F_network_version_six when calling this function to bypass IP type detection.
 *
 *   This alters main.setting.state.status:
 *     F_okay on success.
 *     F_data_not on success but there is nothing in the address string (address.used is 0).
 *     F_number_not on success but there is no port number.
 *
 *     F_parameter (with error bit) if a parameter is invalid.
 *
 *     Errors (with error bit) from: fl_conversion_dynamic_to_unsigned_detect().
 * @param range_ip
 *   The range in the string representing the extracted address and port number.
 * @param address
 *   The string representing the address to extract the port number from.
 *   If a valid number is found, then this is updated to truncate the length at the colon and a NULL termination is inserted at the colon.
 *   For IPv6, only bracket wrapped addresses are supported when using port number (like [2001:db8::1]:80).
 *   Base notations for port numbers are supported (such as specifying hexidecimal like [2001:db8::1]:0x50 or specifying octal like 127.0.0.1:0o120)
 *
 *   Supported base notations:
 *   - Hexidecimals (base 16) begin with either '0x' or '0X'.
 *   - Duodecimals (base 12) begin with either '0d' or '0D'.
 *   - Octals (base 8) begin with either '0o' or '0O'.
 *   - Binaries (base 2) begin with either '0b' or '0B'.
 *   - Decimal (base 10) is used for all other cases.
 * @param port
 *   The extracted port number.
 *
 *   When main.setting.state.status is set to either F_network_version_four or F_network_version_six when calling this function, the port represents the location within the address string that the port number begins.
 *
 * @see fl_conversion_dynamic_to_unsigned_detect()
 */
#ifndef _di_kt_tacocat_setting_load_address_port_extract_
  extern void kt_tacocat_setting_load_address_port_extract(kt_tacocat_main_t * const main, const f_range_double_t range_ip, f_string_static_t * const address, f_number_unsigned_t * const port);
#endif // _di_kt_tacocat_setting_load_address_port_extract_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_common_h
