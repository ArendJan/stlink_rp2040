#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
int main() {
    // stdio_init_all();
    // printf("Hello, world!\n");
    io_bank0_hw->io[25].ctrl = GPIO_FUNC_SIO;
    sio_hw->gpio_oe_set = 1u << 25;
    sio_hw->gpio_hi_oe_set = 1u << 25;
    while(1) {
        sio_hw->gpio_togl = 1u << 25;
        sleep_ms(1000);

    }        // io_bank0_hw->io->ctrl[];
                // sio_hw->gpio_hi_out = 1u << 25;

        // sio_hw->gpio_out = 1u << 25;
        // sio_hw->gpio_out = 0;
        // sio_hw->gpio_hi_out = 0;
        // sleep_ms(500);

 __asm__ (
        R"(
	ldr  r3, =0x400140cc  ;@IO_BANK0.GPIO25_CTRL
	movs r2, #5           ;@Function 5 (SIO)
	str  r2, [r3, #0]

	ldr  r3, =0xd0000020  ;@SIO_BASE.GPIO_OE
	movs r2, #128         ;@GPIO25
	lsl  r2, r2, #18
	str  r2, [r3, #0]

_blink:
	ldr  r3, =0xd000001c  ;@SIO_BASE.GPIO_XOR
	movs r2, #128         ;@GPIO25
	lsl  r2, r2, #18
	str  r2, [r3, #0]

	ldr r0, =10000000
	bl  _delay

	b   _blink

/* delay function */
.thumb_func
_delay:
	mov r4,r0
	nop
	nop
	nop
_loop:
	sub r4,r4,#1
	cmp r4, #0
	nop
	nop
	nop
	bne _loop
	bx lr 
    )"
    );
}