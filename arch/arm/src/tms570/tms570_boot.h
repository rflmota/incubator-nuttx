/************************************************************************************
 * arch/arm/src/tms570/tms570_boot.h
 *
 *   Copyright (C) 2015 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ************************************************************************************/

#ifndef __ARCH_ARM_SRC_TMS570_TMS570_BOOT_H
#define __ARCH_ARM_SRC_TMS570_TMS570_BOOT_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#include "arm_internal.h"
#include "chip.h"

/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/

/************************************************************************************
 * Public Types
 ************************************************************************************/

/************************************************************************************
 * Inline Functions
 ************************************************************************************/

#ifndef __ASSEMBLY__

/************************************************************************************
 * Public Data
 ************************************************************************************/

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/* g_idle_topstack: _sbss is the start of the BSS region as defined by the linker
 * script. _ebss lies at the end of the BSS region. The idle task stack starts at
 * the end of BSS and is of size CONFIG_IDLETHREAD_STACKSIZE.  The IDLE thread is
 * the thread that the system boots on and, eventually, becomes the IDLE, do
 * nothing task that runs only when there is nothing else to run.  The heap
 * continues from there until the end of memory.  g_idle_topstack is a read-only
 * variable the provides this computed address.
 */

EXTERN const uintptr_t g_idle_topstack;

/************************************************************************************
 * Public Function Prototypes
 ************************************************************************************/

/************************************************************************************
 * Name: tms570_lowsetup
 *
 * Description:
 *   Called at the very beginning of _start.  Performs low level initialization
 *   including setup of the console SCI.  This SCI done early so that the serial
 *   console is available for debugging very early in the boot sequence.
 *
 ************************************************************************************/

void tms570_lowsetup(void);

/************************************************************************************
 * Name: tms570_boardinitialize
 *
 * Description:
 *   All TMS570 architectures must provide the following entry point.  This function
 *   is called near the beginning of _start.  This function is called after clocking
 *   has been configured but before caches have been enabled and before any devices
 *   have been initialized.  .data/.bss memory may or may not have been initialized
 *   (see the "special precautions" below).
 *
 *   This function must perform low level initialization including
 *
 *   - Initialization of board-specific memory resources (e.g., SDRAM)
 *   - Configuration of board specific resources (GIOs, LEDs, etc).
 *   - Setup of the console SCI.  This SCI done early so that the serial console
 *     is available for debugging very early in the boot sequence.
 *
 *   Special precautions must be taken if .data/.bss lie in SRAM.  in that case,
 *   the boot logic cannot initialize .data or .bss.  The function must then:
 *
 *   - Take precautions to assume that logic does not access any global data that
 *     might lie in SDRAM.
 *   - Call the function arm_data_initialize() as soon as SDRAM has been
 *     properly configured for use.
 *
 ************************************************************************************/

void tms570_board_initialize(void);

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_TMS570_TMS570_BOOT_H */
