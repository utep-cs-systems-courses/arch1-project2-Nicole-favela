	.arch
	.text
	.global select_button
select_button:
	cmp #1, r12
	jeq	.S0
	cmp #2, r12
	jeq     .S1
	cmp #3, r12
	jeq 	.S2
	cmp #4, r12
	jeq	.S3
.S0:

	ret	#1
.S1:
	ret	#2
.S2:
	ret	#3
.S3:
	ret	#4
	
	
