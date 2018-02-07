#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#include <libopencm3/stm32/dbgmcu.h>
#include <libopencm3/cm3/scs.h>
#include <libopencm3/cm3/tpiu.h>
#include <libopencm3/cm3/itm.h>

#include "trace.h"

#ifdef ENABLE_TRACE
int _write(int file, char *ptr, int len);

void trace_init(void)
{
	/* Enable trace subsystem (we'll use ITM and TPIU). */
	SCS_DEMCR |= SCS_DEMCR_TRCENA;

	/* Use Manchester code for asynchronous transmission. */
	TPIU_SPPR = TPIU_SPPR_ASYNC_NRZ;

	/* Async Clock Prescaler Register */
	TPIU_ACPR = 7;

	/* Formatter and flush control. */
	TPIU_FFCR &= ~TPIU_FFCR_ENFCONT;

	/* Enable TRACESWO pin for async mode. */
	DBGMCU_CR = DBGMCU_CR_TRACE_IOEN | DBGMCU_CR_TRACE_MODE_ASYNC;

	/* Unlock access to ITM registers. */
	/* FIXME: Magic numbers... Is this Cortex-M3 generic? */
	*((volatile uint32_t *)0xE0000FB0) = 0xC5ACCE55;

	/* Enable ITM with ID = 1. */
	ITM_TCR = (1 << 16) | ITM_TCR_ITMENA;
	/* Enable stimulus port 1. */
	ITM_TER[0] = 1;
}

static void trace_send_blocking(char c)
{
	while (!(ITM_STIM8(0) & ITM_STIM_FIFOREADY))
		;

	ITM_STIM8(0) = c;
}

/**
 * Use SWO as a console.
 * This is a syscall for newlib
 * @param file
 * @param ptr
 * @param len
 * @return
 */
int _write(int file, char *ptr, int len)
{
	int i;

	if (file == STDOUT_FILENO || file == STDERR_FILENO) {
		for (i = 0; i < len; i++) {
			if (ptr[i] == '\n') {
				trace_send_blocking('\r');
			}
			trace_send_blocking(ptr[i]);
		}
		return i;
	}
	errno = EIO;
	return -1;
}

#else
void trace_init(void) { }
#endif
