#include "tacocat.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_kt_tacocat_process_main_
  void kt_tacocat_process_main(kt_tacocat_main_t * const main) {

    if (!main) return;

    f_number_unsigned_t i = 0;

    // @todo:
    //   1: Establish connections.
    //   2: read / write from files.
    //   3: work or wait until told to terminate.
    //   4: terminate.

    main->setting.state.status = F_none;
  }
#endif // _di_kt_tacocat_process_main_

#ifdef __cplusplus
} // extern "C"
#endif
