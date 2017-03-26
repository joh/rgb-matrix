#include <libopencm3/cm3/systick.h>

#include "utils.h"

void sys_tick_handler(void);

/* monotonically increasing number of microseconds from reset
 * overflows every 49 days if you're wondering
 */
static volatile uint32_t system_micros;

/* Called when systick fires */
void sys_tick_handler(void)
{
    system_micros++;
}

/* Set up a timer to create 1us ticks. */
void systick_init(void)
{
    systick_set_frequency(1000000, 168000000);
    systick_counter_enable();
    systick_interrupt_enable();
}

/* sleep for delay microseconds */
void usleep(uint32_t delay)
{
    uint32_t wake = system_micros + delay;
    while (wake > system_micros);
}
