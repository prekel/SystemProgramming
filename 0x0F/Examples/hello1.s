	.text

	.globl	WriteMatrix
WriteMatrix:
	li	$v0,4		# print_string syscall code = 4
	la	$a0, msg21	
	syscall	

	jr $ra

	.globl	main
main:
	# Print msg1
	
	li	$v0,4		# print_string syscall code = 4
	la	$a0, msg1	
	syscall	

	jal WriteMatrix

	li	$v0,10		# exit
	syscall

	

	#.data
Space1:	
	.asciiz	" "
msg2:	
	.asciiz	"Sum = "

