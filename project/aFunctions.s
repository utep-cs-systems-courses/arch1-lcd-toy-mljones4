#include "lcddraw.h"
#include "lcdutils.h"
#include "switches.h"
	
	.arch msp430g2553
	.p2align 1,0

	.text

	.extern clearScreen
	.extern switch_state
	.extern switch1_state
	.extern switch2_state
	.extern switch3_state
	.extern switch4_state
	
jt:
	.word switch1
	.word switch2
	.word switch3
	.word switch4 
	.word default
	
	.global stateMachine
stateMachine:
	mov &switch_state, r13
	sub #1, r13
	cmp #5, r13
	jc default
	add r13, r13
	mov jt(r13), r0
nswitch:
	jmp default
switch1:
	CALL #switch1_state
	jmp default		
switch2:	
	CALL #switch2_state
	jmp default
switch3:	
	CALL #switch3_state
	jmp default
switch4:	
	CALL #switch4_state
default:
	pop r0
	
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
