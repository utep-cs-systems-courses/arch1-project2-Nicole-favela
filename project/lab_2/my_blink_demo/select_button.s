	.arch msp430g2553
	.text
	.p2align 1,0
JT:				;jump table
	.word default		;default case
	.word S0		;first button case 1
	.word S1		;button 2 case 2
	.word S2		;button 3 case 3 
	.word S3		;button 4 case 4

	
	.global select_button	; name of method 
select_button:
	cmp #5, r12		;checks that the range of the jump table is within the cases
	jnc	default		;if out of range goes to default
	add r12, r12		;allocates space in array (same as multiplying by 2)
	mov JT(r12), r0		;moves r12 to program counter (returns)
	
S0:

	ret	#1		;returns 1
S1:
	ret	#2		;returns 2
S2:
	ret	#3		;returns 3
S3:
	ret	#4		;returns 4
default:
	ret 	#0		;returns 0 for default (no button pressed)
	
