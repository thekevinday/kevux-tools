#include "../remove.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_remove_program_version_s_
  const f_string_static_t kt_remove_program_version_s = macro_f_string_static_t_initialize_1(KT_REMOVE_program_version_s, 0, KT_REMOVE_program_version_s_length);
#endif // _di_kt_remove_program_version_s_

#ifndef _di_kt_remove_program_name_s_
  const f_string_static_t kt_remove_program_name_s = macro_f_string_static_t_initialize_1(KT_REMOVE_program_name_s, 0, KT_REMOVE_program_name_s_length);
  const f_string_static_t kt_remove_program_name_long_s = macro_f_string_static_t_initialize_1(KT_REMOVE_program_name_long_s, 0, KT_REMOVE_program_name_long_s_length);
#endif // _di_kt_remove_program_name_s_

#ifndef kt_remove_program_help_parameters_s_
  const f_string_static_t kt_remove_program_help_parameters_s = macro_f_string_static_t_initialize_1(KT_REMOVE_program_help_parameters_s, 0, KT_REMOVE_program_help_parameters_s_length);
#endif // _di_utf8_program_help_parameters_s_

#ifndef _di_kt_remove_s_
  const f_string_static_t kt_remove_all_s = macro_f_string_static_t_initialize_1(KT_REMOVE_all_s, 0, KT_REMOVE_all_s_length);
  const f_string_static_t kt_remove_follow_s = macro_f_string_static_t_initialize_1(KT_REMOVE_follow_s, 0, KT_REMOVE_follow_s_length);
  const f_string_static_t kt_remove_force_s = macro_f_string_static_t_initialize_1(KT_REMOVE_force_s, 0, KT_REMOVE_force_s_length);
  const f_string_static_t kt_remove_ignore_s = macro_f_string_static_t_initialize_1(KT_REMOVE_ignore_s, 0, KT_REMOVE_ignore_s_length);
  const f_string_static_t kt_remove_never_s = macro_f_string_static_t_initialize_1(KT_REMOVE_never_s, 0, KT_REMOVE_never_s_length);
  const f_string_static_t kt_remove_no_s = macro_f_string_static_t_initialize_1(KT_REMOVE_no_s, 0, KT_REMOVE_no_s_length);
  const f_string_static_t kt_remove_not_s = macro_f_string_static_t_initialize_1(KT_REMOVE_not_s, 0, KT_REMOVE_not_s_length);
  const f_string_static_t kt_remove_not_fail_s = macro_f_string_static_t_initialize_1(KT_REMOVE_not_fail_s, 0, KT_REMOVE_not_fail_s_length);
  const f_string_static_t kt_remove_now_s = macro_f_string_static_t_initialize_1(KT_REMOVE_now_s, 0, KT_REMOVE_now_s_length);
  const f_string_static_t kt_remove_once_s = macro_f_string_static_t_initialize_1(KT_REMOVE_once_s, 0, KT_REMOVE_once_s_length);
  const f_string_static_t kt_remove_only_s = macro_f_string_static_t_initialize_1(KT_REMOVE_only_s, 0, KT_REMOVE_only_s_length);
  const f_string_static_t kt_remove_only_fail_s = macro_f_string_static_t_initialize_1(KT_REMOVE_only_fail_s, 0, KT_REMOVE_only_fail_s_length);
  const f_string_static_t kt_remove_recurse_s = macro_f_string_static_t_initialize_1(KT_REMOVE_recurse_s, 0, KT_REMOVE_recurse_s_length);
  const f_string_static_t kt_remove_remove_s = macro_f_string_static_t_initialize_1(KT_REMOVE_remove_s, 0, KT_REMOVE_remove_s_length);
  const f_string_static_t kt_remove_root_s = macro_f_string_static_t_initialize_1(KT_REMOVE_root_s, 0, KT_REMOVE_root_s_length);
  const f_string_static_t kt_remove_today_s = macro_f_string_static_t_initialize_1(KT_REMOVE_today_s, 0, KT_REMOVE_today_s_length);
  const f_string_static_t kt_remove_tomorrow_s = macro_f_string_static_t_initialize_1(KT_REMOVE_tomorrow_s, 0, KT_REMOVE_tomorrow_s_length);
  const f_string_static_t kt_remove_yes_s = macro_f_string_static_t_initialize_1(KT_REMOVE_yes_s, 0, KT_REMOVE_yes_s_length);
  const f_string_static_t kt_remove_yesterday_s = macro_f_string_static_t_initialize_1(KT_REMOVE_yesterday_s, 0, KT_REMOVE_yesterday_s_length);
#endif // _di_kt_remove_s_

#ifndef _di_kt_remove_date_s_
  const f_string_static_t kt_remove_date_format_00_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_00_s, 0, KT_REMOVE_date_format_00_s_length);
  const f_string_static_t kt_remove_date_format_01_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_01_s, 0, KT_REMOVE_date_format_01_s_length);
  const f_string_static_t kt_remove_date_format_02_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_02_s, 0, KT_REMOVE_date_format_02_s_length);
  const f_string_static_t kt_remove_date_format_03_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_03_s, 0, KT_REMOVE_date_format_03_s_length);
  const f_string_static_t kt_remove_date_format_04_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_04_s, 0, KT_REMOVE_date_format_04_s_length);
  const f_string_static_t kt_remove_date_format_05_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_05_s, 0, KT_REMOVE_date_format_05_s_length);
  const f_string_static_t kt_remove_date_format_06_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_06_s, 0, KT_REMOVE_date_format_06_s_length);
  const f_string_static_t kt_remove_date_format_07_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_07_s, 0, KT_REMOVE_date_format_07_s_length);
  const f_string_static_t kt_remove_date_format_08_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_08_s, 0, KT_REMOVE_date_format_08_s_length);
  const f_string_static_t kt_remove_date_format_09_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_09_s, 0, KT_REMOVE_date_format_09_s_length);
  const f_string_static_t kt_remove_date_format_10_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_10_s, 0, KT_REMOVE_date_format_10_s_length);
  const f_string_static_t kt_remove_date_format_11_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_11_s, 0, KT_REMOVE_date_format_11_s_length);
  const f_string_static_t kt_remove_date_format_12_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_12_s, 0, KT_REMOVE_date_format_12_s_length);
  const f_string_static_t kt_remove_date_format_13_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_13_s, 0, KT_REMOVE_date_format_13_s_length);
  const f_string_static_t kt_remove_date_format_14_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_14_s, 0, KT_REMOVE_date_format_14_s_length);

  const f_string_static_t kt_remove_date_format_example_00_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_example_00_s, 0, KT_REMOVE_date_format_example_00_s_length);
  const f_string_static_t kt_remove_date_format_example_01_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_example_01_s, 0, KT_REMOVE_date_format_example_01_s_length);
  const f_string_static_t kt_remove_date_format_example_02_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_example_02_s, 0, KT_REMOVE_date_format_example_02_s_length);
  const f_string_static_t kt_remove_date_format_example_03_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_example_03_s, 0, KT_REMOVE_date_format_example_03_s_length);
  const f_string_static_t kt_remove_date_format_example_04_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_example_04_s, 0, KT_REMOVE_date_format_example_04_s_length);
  const f_string_static_t kt_remove_date_format_example_05_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_example_05_s, 0, KT_REMOVE_date_format_example_05_s_length);
  const f_string_static_t kt_remove_date_format_example_06_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_example_06_s, 0, KT_REMOVE_date_format_example_06_s_length);
  const f_string_static_t kt_remove_date_format_example_07_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_example_07_s, 0, KT_REMOVE_date_format_example_07_s_length);
  const f_string_static_t kt_remove_date_format_example_08_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_example_08_s, 0, KT_REMOVE_date_format_example_08_s_length);
  const f_string_static_t kt_remove_date_format_example_09_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_example_09_s, 0, KT_REMOVE_date_format_example_09_s_length);
  const f_string_static_t kt_remove_date_format_example_10_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_example_10_s, 0, KT_REMOVE_date_format_example_10_s_length);
  const f_string_static_t kt_remove_date_format_example_11_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_example_11_s, 0, KT_REMOVE_date_format_example_11_s_length);
  const f_string_static_t kt_remove_date_format_example_12_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_example_12_s, 0, KT_REMOVE_date_format_example_12_s_length);
  const f_string_static_t kt_remove_date_format_example_13_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_example_13_s, 0, KT_REMOVE_date_format_example_13_s_length);
  const f_string_static_t kt_remove_date_format_example_14_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_format_example_14_s, 0, KT_REMOVE_date_format_example_14_s_length);

  const f_string_static_t kt_remove_date_symbol_equal_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_symbol_equal_s, 0, KT_REMOVE_date_symbol_equal_s_length);
  const f_string_static_t kt_remove_date_symbol_less_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_symbol_less_s, 0, KT_REMOVE_date_symbol_less_s_length);
  const f_string_static_t kt_remove_date_symbol_less_equal_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_symbol_less_equal_s, 0, KT_REMOVE_date_symbol_less_equal_s_length);
  const f_string_static_t kt_remove_date_symbol_more_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_symbol_more_s, 0, KT_REMOVE_date_symbol_more_s_length);
  const f_string_static_t kt_remove_date_symbol_more_equal_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_symbol_more_equal_s, 0, KT_REMOVE_date_symbol_more_equal_s_length);
  const f_string_static_t kt_remove_date_symbol_not_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_symbol_not_s, 0, KT_REMOVE_date_symbol_not_s_length);

  const f_string_static_t kt_remove_date_word_equal_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_word_equal_s, 0, KT_REMOVE_date_word_equal_s_length);
  const f_string_static_t kt_remove_date_word_less_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_word_less_s, 0, KT_REMOVE_date_word_less_s_length);
  const f_string_static_t kt_remove_date_word_less_equal_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_word_less_equal_s, 0, KT_REMOVE_date_word_less_equal_s_length);
  const f_string_static_t kt_remove_date_word_more_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_word_more_s, 0, KT_REMOVE_date_word_more_s_length);
  const f_string_static_t kt_remove_date_word_more_equal_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_word_more_equal_s, 0, KT_REMOVE_date_word_more_equal_s_length);
  const f_string_static_t kt_remove_date_word_not_s = macro_f_string_static_t_initialize_1(KT_REMOVE_date_word_not_s, 0, KT_REMOVE_date_word_not_s_length);
#endif // _di_kt_remove_date_s_

#ifndef _di_kt_remove_mode_s_
  const f_string_static_t kt_remove_mode_symbol_different_s = macro_f_string_static_t_initialize_1(KT_REMOVE_mode_symbol_different_s, 0, KT_REMOVE_mode_symbol_different_s_length);
  const f_string_static_t kt_remove_mode_symbol_same_s = macro_f_string_static_t_initialize_1(KT_REMOVE_mode_symbol_same_s, 0, KT_REMOVE_mode_symbol_same_s_length);
  const f_string_static_t kt_remove_mode_symbol_similar_s = macro_f_string_static_t_initialize_1(KT_REMOVE_mode_symbol_similar_s, 0, KT_REMOVE_mode_symbol_similar_s_length);
  const f_string_static_t kt_remove_mode_symbol_not_s = macro_f_string_static_t_initialize_1(KT_REMOVE_mode_symbol_not_s, 0, KT_REMOVE_mode_symbol_not_s_length);

  const f_string_static_t kt_remove_mode_word_different_s = macro_f_string_static_t_initialize_1(KT_REMOVE_mode_word_different_s, 0, KT_REMOVE_mode_word_different_s_length);
  const f_string_static_t kt_remove_mode_word_same_s = macro_f_string_static_t_initialize_1(KT_REMOVE_mode_word_same_s, 0, KT_REMOVE_mode_word_same_s_length);
  const f_string_static_t kt_remove_mode_word_similar_s = macro_f_string_static_t_initialize_1(KT_REMOVE_mode_word_similar_s, 0, KT_REMOVE_mode_word_similar_s_length);
  const f_string_static_t kt_remove_mode_word_not_s = macro_f_string_static_t_initialize_1(KT_REMOVE_mode_word_not_s, 0, KT_REMOVE_mode_word_not_s_length);
#endif // _di_kt_remove_mode_s_

#ifndef _di_kt_remove_parameter_s_
  const f_string_static_t kt_remove_short_accessed_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_accessed_s, 0, KT_REMOVE_short_accessed_s_length);
  const f_string_static_t kt_remove_short_block_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_block_s, 0, KT_REMOVE_short_block_s_length);
  const f_string_static_t kt_remove_short_character_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_character_s, 0, KT_REMOVE_short_character_s_length);
  const f_string_static_t kt_remove_short_created_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_created_s, 0, KT_REMOVE_short_created_s_length);
  const f_string_static_t kt_remove_short_different_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_different_s, 0, KT_REMOVE_short_different_s_length);
  const f_string_static_t kt_remove_short_directory_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_directory_s, 0, KT_REMOVE_short_directory_s_length);
  const f_string_static_t kt_remove_short_empty_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_empty_s, 0, KT_REMOVE_short_empty_s_length);
  const f_string_static_t kt_remove_short_fifo_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_fifo_s, 0, KT_REMOVE_short_fifo_s_length);
  const f_string_static_t kt_remove_short_follow_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_follow_s, 0, KT_REMOVE_short_follow_s_length);
  const f_string_static_t kt_remove_short_force_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_force_s, 0, KT_REMOVE_short_force_s_length);
  const f_string_static_t kt_remove_short_group_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_group_s, 0, KT_REMOVE_short_group_s_length);
  const f_string_static_t kt_remove_short_isolate_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_isolate_s, 0, KT_REMOVE_short_isolate_s_length);
  const f_string_static_t kt_remove_short_link_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_link_s, 0, KT_REMOVE_short_link_s_length);
  const f_string_static_t kt_remove_short_mode_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_mode_s, 0, KT_REMOVE_short_mode_s_length);
  const f_string_static_t kt_remove_short_prompt_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_prompt_s, 0, KT_REMOVE_short_prompt_s_length);
  const f_string_static_t kt_remove_short_recurse_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_recurse_s, 0, KT_REMOVE_short_recurse_s_length);
  const f_string_static_t kt_remove_short_regular_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_regular_s, 0, KT_REMOVE_short_regular_s_length);
  const f_string_static_t kt_remove_short_same_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_same_s, 0, KT_REMOVE_short_same_s_length);
  const f_string_static_t kt_remove_short_simulate_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_simulate_s, 0, KT_REMOVE_short_simulate_s_length);
  const f_string_static_t kt_remove_short_socket_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_socket_s, 0, KT_REMOVE_short_socket_s_length);
  const f_string_static_t kt_remove_short_stay_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_stay_s, 0, KT_REMOVE_short_stay_s_length);
  const f_string_static_t kt_remove_short_tree_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_tree_s, 0, KT_REMOVE_short_tree_s_length);
  const f_string_static_t kt_remove_short_updated_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_updated_s, 0, KT_REMOVE_short_updated_s_length);
  const f_string_static_t kt_remove_short_user_s = macro_f_string_static_t_initialize_1(KT_REMOVE_short_user_s, 0, KT_REMOVE_short_user_s_length);

  const f_string_static_t kt_remove_long_accessed_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_accessed_s, 0, KT_REMOVE_long_accessed_s_length);
  const f_string_static_t kt_remove_long_block_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_block_s, 0, KT_REMOVE_long_block_s_length);
  const f_string_static_t kt_remove_long_character_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_character_s, 0, KT_REMOVE_long_character_s_length);
  const f_string_static_t kt_remove_long_created_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_created_s, 0, KT_REMOVE_long_created_s_length);
  const f_string_static_t kt_remove_long_different_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_different_s, 0, KT_REMOVE_long_different_s_length);
  const f_string_static_t kt_remove_long_directory_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_directory_s, 0, KT_REMOVE_long_directory_s_length);
  const f_string_static_t kt_remove_long_empty_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_empty_s, 0, KT_REMOVE_long_empty_s_length);
  const f_string_static_t kt_remove_long_fifo_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_fifo_s, 0, KT_REMOVE_long_fifo_s_length);
  const f_string_static_t kt_remove_long_follow_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_follow_s, 0, KT_REMOVE_long_follow_s_length);
  const f_string_static_t kt_remove_long_force_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_force_s, 0, KT_REMOVE_long_force_s_length);
  const f_string_static_t kt_remove_long_group_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_group_s, 0, KT_REMOVE_long_group_s_length);
  const f_string_static_t kt_remove_long_isolate_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_isolate_s, 0, KT_REMOVE_long_isolate_s_length);
  const f_string_static_t kt_remove_long_link_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_link_s, 0, KT_REMOVE_long_link_s_length);
  const f_string_static_t kt_remove_long_local_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_local_s, 0, KT_REMOVE_long_local_s_length);
  const f_string_static_t kt_remove_long_mode_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_mode_s, 0, KT_REMOVE_long_mode_s_length);
  const f_string_static_t kt_remove_long_prompt_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_prompt_s, 0, KT_REMOVE_long_prompt_s_length);
  const f_string_static_t kt_remove_long_recurse_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_recurse_s, 0, KT_REMOVE_long_recurse_s_length);
  const f_string_static_t kt_remove_long_regular_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_regular_s, 0, KT_REMOVE_long_regular_s_length);
  const f_string_static_t kt_remove_long_same_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_same_s, 0, KT_REMOVE_long_same_s_length);
  const f_string_static_t kt_remove_long_simulate_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_simulate_s, 0, KT_REMOVE_long_simulate_s_length);
  const f_string_static_t kt_remove_long_socket_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_socket_s, 0, KT_REMOVE_long_socket_s_length);
  const f_string_static_t kt_remove_long_stay_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_stay_s, 0, KT_REMOVE_long_stay_s_length);
  const f_string_static_t kt_remove_long_tree_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_tree_s, 0, KT_REMOVE_long_tree_s_length);
  const f_string_static_t kt_remove_long_updated_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_updated_s, 0, KT_REMOVE_long_updated_s_length);
  const f_string_static_t kt_remove_long_user_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_user_s, 0, KT_REMOVE_long_user_s_length);
  const f_string_static_t kt_remove_long_utc_s = macro_f_string_static_t_initialize_1(KT_REMOVE_long_utc_s, 0, KT_REMOVE_long_utc_s_length);
#endif // _di_kt_remove_parameter_s_

#ifndef _di_kt_remove_print_reason_s_
  const f_string_static_t kt_remove_print_reason_no_access_s = macro_f_string_static_t_initialize_1(KT_REMOVE_print_reason_no_access_s, 0, KT_REMOVE_print_reason_no_access_s_length);
  const f_string_static_t kt_remove_print_reason_not_found_s = macro_f_string_static_t_initialize_1(KT_REMOVE_print_reason_not_found_s, 0, KT_REMOVE_print_reason_not_found_s_length);
  const f_string_static_t kt_remove_print_reason_stat_fail_s = macro_f_string_static_t_initialize_1(KT_REMOVE_print_reason_stat_fail_s, 0, KT_REMOVE_print_reason_stat_fail_s_length);
#endif // _di_kt_remove_print_reason_s_

#ifdef __cplusplus
} // extern "C"
#endif
