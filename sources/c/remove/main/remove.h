/**
 * Kevux Tools - Remove
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * This program provides a program to perform file, directory, and symbolic link remove file removals.
 */
#ifndef _kt_remove_h
#define _kt_remove_h

// Libc includes.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/account.h>
#include <fll/level_0/color.h>
#include <fll/level_0/compare.h>
#include <fll/level_0/console.h>
#include <fll/level_0/conversion.h>
#include <fll/level_0/directory.h>
#include <fll/level_0/file.h>
#include <fll/level_0/fss.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/rip.h>
#include <fll/level_0/signal.h>
#include <fll/level_0/thread.h>

// FLL-1 includes.
#include <fll/level_1/conversion.h>
#include <fll/level_1/directory.h>
#include <fll/level_1/print.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// Kevux Tools includes.
#include <program/kevux/tools/remove/main/common/define.h>
#include <program/kevux/tools/remove/main/common/enumeration.h>
#include <program/kevux/tools/remove/main/common/print.h>
#include <program/kevux/tools/remove/main/common/string.h>
#include <program/kevux/tools/remove/main/common/type.h>
#include <program/kevux/tools/remove/main/common.h>
#include <program/kevux/tools/remove/main/convert.h>
#include <program/kevux/tools/remove/main/operate.h>
#include <program/kevux/tools/remove/main/print/error.h>
#include <program/kevux/tools/remove/main/print/message.h>
#include <program/kevux/tools/remove/main/print/simulate.h>
#include <program/kevux/tools/remove/main/print/verbose.h>
#include <program/kevux/tools/remove/main/print/warning.h>
#include <program/kevux/tools/remove/main/signal.h>
#include <program/kevux/tools/remove/main/thread.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Execute main program.
 *
 * If main.signal is non-zero, then this blocks and handles the following signals:
 *   - F_signal_abort
 *   - F_signal_broken_pipe
 *   - F_signal_hangup
 *   - F_signal_interrupt
 *   - F_signal_quit
 *   - F_signal_termination
 *
 * @param main
 *   The main program and settings data.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *     F_true on success when performing verification and verify passed.
 *     F_false on success when performing verification and verify failed.
 *
 *     F_interrupt (with error bit) on (exit) signal received.
 *
 *     Errors (with error bit) from: main.callback.process_normal().
 */
#ifndef _di_kt_remove_main_
  extern void kt_remove_main(kt_remove_main_t * const main);
#endif // _di_kt_remove_main_

/**
 * Process printing help.
 *
 * @param main
 *   The main program and settings data.
 *
 *   This must be of type kt_remove_main_t.
 *
 *   This does not alter main.setting.state.status.
 *
 * @return
 *   F_none on success.
 *   F_output_not on success, but no printing is performed.
 */
#ifndef _di_kt_remove_process_help_
  extern f_status_t kt_remove_process_help(void * const main);
#endif // _di_kt_remove_process_help_

/**
 * Process normally, writing to the output.
 *
 * @param main
 *   The main program and settings data.
 *
 *   This must be of type kt_remove_main_t.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 *
 *     Errors with (error bit set) from: kt_remove_process_normal_operate()
 *
 * @see kt_remove_process_normal_operate()
 */
#ifndef _di_kt_remove_process_normal_
  extern void kt_remove_process_normal(void * const main);
#endif // _di_kt_remove_process_normal_

/**
 * Perform the normal processing.
 *
 * @param main
 *   The main program and settings data.
 *
 *   This alters main.setting.state.status:
 *     F_none on success.
 */
#ifndef _di_kt_remove_process_normal_operate_
  extern void kt_remove_process_normal_operate(kt_remove_main_t * const main);
#endif // _di_kt_remove_process_normal_operate_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_remove_h
