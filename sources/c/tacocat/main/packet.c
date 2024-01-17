#include "tacocat.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_tacocat_packet_extract_
  void kt_tacocat_packet_extract(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set, const f_string_static_t direction) {

    if (!main || !set) return;

    kt_tacocat_process_abstruse_initialize(main, set);

    if (F_status_is_error(set->status)) {
      kt_tacocat_print_error_on(&main->program.error, macro_kt_tacocat_f(kt_tacocat_process_abstruse_initialize), direction, set->network, set->status, set->name);

      if (set->socket.id_data) {
        f_file_close_id(&set->socket.id_data);
      }

      set->step = 0;

      return;
    }

    // 0x1 = did not find payload, 0x2 = did not find header.
    uint8_t found_not = 0x3;

    for (f_number_unsigned_t i = 0; i < set->objects.used; ++i) {

      if (f_compare_dynamic_partial_string(f_fss_payload_object_header_s.string, set->buffer, f_fss_payload_object_header_s.used, set->objects.array[i]) == F_equal_to) {
        kt_tacocat_packet_extract_header(main, set, i, direction);

        if (F_status_is_error(set->status)) {
          // @todo handle F_packet error, setup the sending of an invalid packet response (things similar to this needs to be done in multiple places).
          ++set->retry;

          return;
        }

        found_not &= ~0x2;
      }
      else if (f_compare_dynamic_partial_string(f_fss_payload_object_signature_s.string, set->buffer, f_fss_payload_object_signature_s.used, set->objects.array[i]) == F_equal_to) {
        kt_tacocat_packet_extract_signature(main, set, i, direction);

        if (F_status_is_error(set->status)) {
          ++set->retry;

          return;
        }
      }
      else if (f_compare_dynamic_partial_string(f_fss_payload_object_payload_s.string, set->buffer, f_fss_payload_object_payload_s.used, set->objects.array[i]) == F_equal_to) {
        if (found_not & 0x1) {
          set->packet.payload = set->contents.array[i].array[0];
          found_not &= ~0x1;
        }
      }
    } // for

    set->status = F_okay;
  }
#endif // _di_kt_tacocat_packet_extract_

#ifndef _di_kt_tacocat_packet_extract_header_
  void kt_tacocat_packet_extract_header(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set, const f_number_unsigned_t at, const f_string_static_t direction) {

    if (!main || !set) return;

    if (set->objects.array[at].start > set->objects.array[at].stop || !set->contents.array[at].used) {
      set->status = F_data_not;

      return;
    }

    set->range = set->contents.array[at].array[0];

    fll_fss_extended_read(set->buffer, &set->range, &set->objects_header, &set->contents_header, &set->objects_quoted_header, &set->contents_quoted_header, &set->objects_delimits_header, &set->contents_delimits_header, &set->state);

    if (F_status_is_error(set->state.status)) {
      kt_tacocat_print_error_on(&main->program.error, macro_kt_tacocat_f(fll_fss_extended_read), direction, set->network, set->status, set->name);

      set->status = set->state.status;

      return;
    }

    switch (set->state.status) {
      case F_okay:
      case F_okay_stop:
      case F_okay_eos:
        break;

      default:
        set->status = F_data_not;

        return;
    }

    f_number_unsigned_t i = 0;

    for (; i < set->objects_header.used; ++i) {

      // Index 0 is the status.
      if (f_compare_dynamic_partial_string(f_fss_payload_object_status_s.string, set->buffer, f_fss_payload_object_status_s.used, set->objects_header.array[i]) == F_equal_to) {

        // Require Content to exist.
        if (!set->contents_header.array[i].used) {
          set->abstruses.array[0].value.type = f_abstruse_none_e;

          continue;
        }

        set->abstruses.array[0].value.type = f_abstruse_range_e;
        set->abstruses.array[0].value.is.a_range = set->contents_header.array[i].array[0];
      }

      // Index 1 is the type.
      else if (f_compare_dynamic_partial_string(f_fss_payload_object_type_s.string, set->buffer, f_fss_payload_object_type_s.used, set->objects_header.array[i]) == F_equal_to) {

        // Require Content to exist.
        if (!set->contents_header.array[i].used) {
         set->abstruses.array[1].value.type = f_abstruse_none_e;

          continue;
        }

        set->abstruses.array[1].value.type = f_abstruse_range_e;
        set->abstruses.array[1].value.is.a_range = set->contents_header.array[i].array[0];
      }

      // Index 2 is the length.
      else if (f_compare_dynamic_partial_string(f_fss_payload_object_length_s.string, set->buffer, f_fss_payload_object_length_s.used, set->objects_header.array[i]) == F_equal_to) {

        // Require Content to exist.
        if (!set->contents_header.array[i].used) {
         set->abstruses.array[2].value.type = f_abstruse_none_e;

          continue;
        }

        set->abstruses.array[2].value.type = f_abstruse_range_e;
        set->abstruses.array[2].value.is.a_range = set->contents_header.array[i].array[0];
      }

      // Index 3 is the part.
      else if (f_compare_dynamic_partial_string(f_fss_payload_object_part_s.string, set->buffer, f_fss_payload_object_part_s.used, set->objects_header.array[i]) == F_equal_to) {

        // Require Content to exist.
        if (!set->contents_header.array[i].used) {
         set->abstruses.array[3].value.type = f_abstruse_none_e;

          continue;
        }

        set->abstruses.array[3].value.type = f_abstruse_range_e;
        set->abstruses.array[3].value.is.a_range = set->contents_header.array[i].array[0];
      }

      // Index 4 is the total number of packets (based on block size).
      else if (f_compare_dynamic_partial_string(f_fss_payload_object_total_s.string, set->buffer, f_fss_payload_object_total_s.used, set->objects_header.array[i]) == F_equal_to) {

        // Require Content to exist.
        if (!set->contents_header.array[i].used) {
         set->abstruses.array[4].value.type = f_abstruse_none_e;

          continue;
        }

        set->abstruses.array[4].value.type = f_abstruse_range_e;
        set->abstruses.array[4].value.is.a_range = set->contents_header.array[i].array[0];
      }

      // Index 5 is the name (file name).
      else if (f_compare_dynamic_partial_string(f_fss_payload_object_name_s.string, set->buffer, f_fss_payload_object_name_s.used, set->objects_header.array[i]) == F_equal_to) {

        // Require Content to exist.
        if (!set->contents_header.array[i].used) {
         set->abstruses.array[5].value.type = f_abstruse_none_e;

          continue;
        }

        set->abstruses.array[5].value.type = f_abstruse_range_e;
        set->abstruses.array[5].value.is.a_range = set->contents_header.array[i].array[0];
      }

      // Index 6 is the salt.
      else if (f_compare_dynamic_partial_string(kt_tacocat_salt_s.string, set->buffer, kt_tacocat_salt_s.used, set->objects_header.array[i]) == F_equal_to) {

        // Require Content to exist.
        if (!set->contents_header.array[i].used) {
          set->abstruses.array[6].value.type = f_abstruse_none_e;

          continue;
        }

        set->abstruses.array[6].value.type = f_abstruse_range_e;
        set->abstruses.array[6].value.is.a_range = set->contents_header.array[i].array[0];
      }

      // Index 7 is the transaction id.
      else if (f_compare_dynamic_partial_string(f_fss_payload_object_id_s.string, set->buffer, f_fss_payload_object_id_s.used, set->objects_header.array[i]) == F_equal_to) {

        // Require Content to exist.
        if (!set->contents_header.array[i].used) {
          set->abstruses.array[7].value.type = f_abstruse_none_e;

          continue;
        }

        set->abstruses.array[7].value.type = f_abstruse_range_e;
        set->abstruses.array[7].value.is.a_range = set->contents_header.array[i].array[0];
      }
    } // for

    // Convert the status code.
    if (set->abstruses.array[0].value.type) {
      const f_number_unsigned_t length = set->abstruses.array[0].value.is.a_range.stop - set->abstruses.array[0].value.is.a_range.start + 1;
      char buffer[length];
      f_status_t status = F_false;

      memcpy(buffer, set->buffer.string + set->abstruses.array[0].value.is.a_range.start, length);

      const f_string_static_t status_string = macro_f_string_static_t_initialize_1(buffer, 0, length);

      set->status = fl_status_string_from(status_string, &status);

      if (set->status == F_okay) {
        set->abstruses.array[0].value.type = f_abstruse_unsigned_e;
        set->abstruses.array[0].value.is.a_unsigned = (f_number_unsigned_t) status;
      }
      else {
        kt_tacocat_print_error_on_packet_header_value_invalid(&main->program.error, direction, set->network, set->status, set->name, set->buffer, set->objects.array[at], set->abstruses.array[6].value.is.a_range);

        set->abstruses.array[0].value.type = f_abstruse_none_e;
        set->abstruses.array[0].value.is.a_unsigned = 0;

        set->status = F_status_set_error(F_packet);
      }
    }

    // Convert the type.
    if (set->abstruses.array[1].value.type) {
      if (f_compare_dynamic_partial_string(kt_tacocat_file_s.string, set->buffer, kt_tacocat_file_s.used, set->abstruses.array[1].value.is.a_range) == F_equal_to) {
        set->abstruses.array[1].value.type = f_abstruse_unsigned_e;
        set->abstruses.array[1].value.is.a_unsigned = (f_number_unsigned_t) kt_tacocat_packet_type_file_e;
      }
      else if (f_compare_dynamic_partial_string(kt_tacocat_done_s.string, set->buffer, kt_tacocat_done_s.used, set->abstruses.array[1].value.is.a_range) == F_equal_to) {
        set->abstruses.array[1].value.type = f_abstruse_unsigned_e;
        set->abstruses.array[1].value.is.a_unsigned = (f_number_unsigned_t) kt_tacocat_packet_type_done_e;
      }
      else if (f_compare_dynamic_partial_string(kt_tacocat_next_s.string, set->buffer, kt_tacocat_next_s.used, set->abstruses.array[1].value.is.a_range) == F_equal_to) {
        set->abstruses.array[1].value.type = f_abstruse_unsigned_e;
        set->abstruses.array[1].value.is.a_unsigned = (f_number_unsigned_t) kt_tacocat_packet_type_next_e;
      }
      else if (f_compare_dynamic_partial_string(kt_tacocat_resend_s.string, set->buffer, kt_tacocat_resend_s.used, set->abstruses.array[1].value.is.a_range) == F_equal_to) {
        set->abstruses.array[1].value.type = f_abstruse_unsigned_e;
        set->abstruses.array[1].value.is.a_unsigned = (f_number_unsigned_t) kt_tacocat_packet_type_resend_e;
      }
      else {
        set->status = F_status_set_error(F_found_not);

        kt_tacocat_print_error_on_packet_header_value_invalid(&main->program.error, direction, set->network, set->status, set->name, set->buffer, set->objects.array[at], set->abstruses.array[6].value.is.a_range);

        set->abstruses.array[1].value.type = f_abstruse_none_e;
        set->abstruses.array[1].value.is.a_unsigned = 0;

        set->status = F_status_set_error(F_packet);

        return;
      }
    }

    // Convert the length, part, and total.
    {
      f_number_unsigned_t number = 0;

      for (i = 2; i < 5; ++i) {

        if (!set->abstruses.array[i].value.type) continue;

        set->status = fl_conversion_dynamic_partial_to_unsigned(fl_conversion_data_base_10_c, set->buffer, set->abstruses.array[i].value.is.a_range, &number);

        if (set->status == F_okay) {
          set->abstruses.array[i].value.type = f_abstruse_unsigned_e;
          set->abstruses.array[i].value.is.a_unsigned = number;
        }
        else {
          kt_tacocat_print_error_on_packet_header_value_invalid(&main->program.error, direction, set->network, set->status, set->name, set->buffer, set->objects.array[at], set->abstruses.array[6].value.is.a_range);

          set->abstruses.array[i].value.type = f_abstruse_none_e;
          set->abstruses.array[i].value.is.a_unsigned = 0;

          set->status = F_status_set_error(F_packet);
        }
      } // for
    }

    set->abstruses.used = kt_tacocat_packet_headers_d;
    set->status = F_okay;
  }
#endif // _di_kt_tacocat_packet_extract_header_

#ifndef _di_kt_tacocat_packet_extract_signature_
  void kt_tacocat_packet_extract_signature(kt_tacocat_main_t * const main, kt_tacocat_socket_set_t * const set, const f_number_unsigned_t at, const f_string_static_t direction) {

    if (!main || !set) return;

    if (set->objects.array[at].start > set->objects.array[at].stop || !set->contents.array[at].used) {
      set->status = F_data_not;

      return;
    }

    set->range = set->contents.array[at].array[0];

    fll_fss_extended_read(set->buffer, &set->range, &set->objects_signature, &set->contents_signature, &set->objects_quoted_header, &set->contents_quoted_header, &set->objects_delimits_signature, &set->contents_delimits_signature, &set->state);

    if (F_status_is_error(set->state.status)) {
      kt_tacocat_print_error_on(&main->program.error, macro_kt_tacocat_f(fll_fss_extended_read), direction, set->network, set->status, set->name);

      set->status = set->state.status;

      return;
    }

    // @todo maybe index 8 and beyond in the abstruse shall represent signatures?

    set->status = F_okay;
  }
#endif // _di_kt_tacocat_packet_extract_signature_

#ifdef __cplusplus
} // extern "C"
#endif
