# Simple routine to demo a loop
# Compute the sum of N integers: 1 + 2 + 3 + ... + N
# From: http://labs.cs.upt.ro/labs/so2/html/resources/nachos-doc/mipsf.html

	.text

	.globl	WriteMatrix
WriteMatrix:
	li	$v0,4		# print_string syscall code = 4
	la	$a0, msg21	
	syscall	

	jr $ra

	# Start .data segment (data!)
	.data
msg21:	.asciiz	"1231231Number of integers (N)?  "
