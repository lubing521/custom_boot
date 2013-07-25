.global _start

_start:
	/*peripheral port setup*/
	ldr	r0, =0x70000000
	orr	r0, r0, #0x13
	mcr	p15, 0, r0, c15, c2, 4

	/*disable watchdog*/
	ldr	r0, =0x7E004000 
	mov	r1, #0x0
	str	r1, [r0]

	/*lowlevel init*/
	bl	clock_init
	ldr	sp, =8*1024
	#bl	uart_init
	bl	ddr_init
	
clear_bss:
	ldr	r0, =bss_start
	ldr	r1, =bss_end
	ldr	r2, =0x0

clbss_loop:
	str	r1, [r0], #4
	cmp	r0, r1
	ble	clbss_loop

#ifndef NAND_SPL
	ldr	pc, =start_armboot
#else
/*
	adr	r0, _start
	ldr	r1, =_start
	ldr	r2, =bss_start
	sub	r2, r2, r1
	cmp	r0, r1
*/	
	b	nand_boot
#endif

error:
	b	error
