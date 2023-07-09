/**
 * Kevux Tools - TacocaT
 *
 * Project: Kevux Tools
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * This program provides a program to perform file, directory, and symbolic link remove file removals.
 */
#ifndef _kt_tacocat_h
#define _kt_tacocat_h

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
#include <fll/level_0/type_array.h>
#include <fll/level_0/type_array_file.h>
#include <fll/level_0/string.h>
#include <fll/level_0/color.h>
#include <fll/level_0/compare.h>
#include <fll/level_0/console.h>
#include <fll/level_0/file.h>
#include <fll/level_0/network.h>
#include <fll/level_0/path.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/signal.h>
#include <fll/level_0/socket.h>
#include <fll/level_0/thread.h>

// FLL-1 includes.
#include <fll/level_1/conversion.h>
#include <fll/level_1/print.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// Kevux Tools includes.
#include <program/kevux/tools/tacocat/main/common/define.h>
#include <program/kevux/tools/tacocat/main/common/enumeration.h>
#include <program/kevux/tools/tacocat/main/common/print.h>
#include <program/kevux/tools/tacocat/main/common/string.h>
#include <program/kevux/tools/tacocat/main/common/type.h>
#include <program/kevux/tools/tacocat/main/common.h>
#include <program/kevux/tools/tacocat/main/print/error.h>
#include <program/kevux/tools/tacocat/main/print/message.h>
#include <program/kevux/tools/tacocat/main/print/verbose.h>
#include <program/kevux/tools/tacocat/main/print/warning.h>
#include <program/kevux/tools/tacocat/main/process.h>
#include <program/kevux/tools/tacocat/main/signal.h>
#include <program/kevux/tools/tacocat/main/thread.h>

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
#ifndef _di_kt_tacocat_main_
  extern void kt_tacocat_main(kt_tacocat_main_t * const main);
#endif // _di_kt_tacocat_main_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _kt_tacocat_h
