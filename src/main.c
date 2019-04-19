#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/gpio.h"

int main(void) {
    rcc_clock_setup_in_hsi_out_48mhz();
    rcc_periph_clock_enable(RCC_GPIOA);

    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO7 | GPIO15);

    for(;;) {
        gpio_toggle(GPIOA, GPIO7 | GPIO15);

        // Super unscientific ~1sec. delay loop
        volatile uint32_t i = 5000000;
        while(i--);
    }
}
