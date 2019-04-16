/*
 * Copyright (c) 2016, Devan Lai
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted, provided
 * that the above copyright notice and this permission notice
 * appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>



int main(void) {
    rcc_clock_setup_in_hsi_out_48mhz();
    rcc_periph_clock_enable(RCC_GPIOA);

    /* gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO7 | GPIO15);*/
    GPIOA_CRH &= ~(0b1111 << 28);
    GPIOA_CRH |= (0b0011 << 28);

    GPIOA_CRL &= ~(0b1111 << 28);
    GPIOA_CRL |= (0b0011 << 28);

    // Strobe USB_EN and LED indefinitely
    for(;;) {
        /* gpio_toggle(GPIOA, GPIO7 | GPIO15);*/
        GPIOA_BRR |= (1 << 15) | (1 << 7);

        // Super unscientific ~1sec. delay loop
        volatile uint32_t i = 5000000;
        while(i--);

        /* gpio_toggle(GPIOA, GPIO7 | GPIO15);*/
        GPIOA_BSRR |= (1 << 15) | (1 << 7);

        // Super unscientific ~1sec. delay loop
        volatile uint32_t j = 1000000;
        while(j--);
    }

}
