#include "lcddraw.h"
#include "lcdutils.h"
	
	.arch msp430g2553
	.p2align 1,0

	.text

	.extern clearScreen
	
	.global changeScreen
changeScreen:
	cmp #0x3666, r12
	jz pickPink
	mov #0x3666, r12
	push r12
	CALL #clearScreen
	jmp callClear
pickPink:
	mov #0xce1f, r12
	push r12
	CALL #clearScreen
callClear:
	pop r12
	pop r0
