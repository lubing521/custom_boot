.global _start

_start:
	b	reset
	ldr	pc, _undefined_instruction
	ldr	pc, _sofrware_insterrupt
	ldr	pc, _prefetch_abort
	ldr	pc, _data_abort
	ldr	pc, _not_used
	ldr	pc, _irq
	ldr	pc, _fiq

_undefined_instruction:
        .word undefined_instruction
_software_interrupt:
        .word software_interrupt
_prefetch_abort:
        .word prefetch_abort
_data_abort:
        .word data_abort
_not_used:
        .word not_used
_irq:
        .word irq
_fiq:
        .word fiq

reset:
	/*set the CPU to SVC32 mode*/
	mrs	r0, cpsr
	bic	r0, r0, #0x3f
	orr	r0, r0, #0xd3
	msr	cpsr, r0

	/*peripheral port setup*/
	ldr	r0, =0x70000000
	orr	r0, r0, #0x13
	mcr	p15, 0, r0, c15, c2, 4

	/*lowlevel: clock, uart, nand*/
	bl	lowlevel_init
	ldr	sp, =8*1024
#	bl	led_run
	bl	ddr_init
	
	/*copy code to ram*/
	adr	r0, _start
	ldr	r1, =_start
	ldr	r2, =bss_start
	sub	r2, r2, r1
#	cmp	r0, r1
#	beq	clean_bss
	
	bl	nand_read
#	bl	led_run

clean_bss:
	ldr	r0, =bss_start
	ldr	r1, =bss_end
	ldr	r2, =0x0
	cmp	r0, r1
	beq	after_copy
bss_loop:
	str	r1, [r0], #4
	cmp	r0, r1
	bne	bss_loop

after_copy:
#	ldr	lr, =error
	ldr	pc, =start_armboot

/*
 * exception handlers
 */
        .align  5
undefined_instruction:
        get_bad_stack
        bad_save_user_regs
        bl      do_undefined_instruction

        .align  5
software_interrupt:
        get_bad_stack_swi
        bad_save_user_regs
        bl      do_software_interrupt

        .align  5
prefetch_abort:
        get_bad_stack
        bad_save_user_regs
        bl      do_prefetch_abort

        .align  5
data_abort:
        get_bad_stack
        bad_save_user_regs
        bl      do_data_abort

        .align  5
not_used:
        get_bad_stack
        bad_save_user_regs
        bl      do_not_used

        .align  5
irq:
        get_bad_stack
        bad_save_user_regs
        bl      do_irq

        .align  5
fiq:
        get_bad_stack
        bad_save_user_regs
        bl      do_fiq
