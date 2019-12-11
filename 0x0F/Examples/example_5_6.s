	.file	1 "example_5_6.c"
	.section .mdebug.abi64
	.previous
	.nan	legacy
	.module	fp=64
	.module	oddspreg
	.abicalls
	.text
	.rdata
	.align	3
.LC0:
	.ascii	"y=%i\012\000"
	.text
	.align	2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,48,$31		# vars= 16, regs= 3/0, args= 0, gp= 0
	.mask	0xd0000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	daddiu	$sp,$sp,-48
	sd	$31,40($sp)
	sd	$fp,32($sp)
	sd	$28,24($sp)
	move	$fp,$sp
	lui	$28,%hi(%neg(%gp_rel(main)))
	daddu	$28,$28,$25
	daddiu	$28,$28,%lo(%neg(%gp_rel(main)))
	li	$2,5			# 0x5
	sw	$2,8($fp)
	lw	$2,8($fp)
	move	$4,$2
	ld	$2,%got_disp(function)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,function
1:	jalr	$25
	nop

	sw	$2,12($fp)
	lw	$2,12($fp)
	move	$5,$2
	ld	$2,%got_page(.LC0)($28)
	daddiu	$4,$2,%got_ofst(.LC0)
	ld	$2,%call16(printf)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,printf
1:	jalr	$25
	nop

	move	$2,$0
	move	$sp,$fp
	ld	$31,40($sp)
	ld	$fp,32($sp)
	ld	$28,24($sp)
	daddiu	$sp,$sp,48
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.align	2
	.globl	function
	.set	nomips16
	.set	nomicromips
	.ent	function
	.type	function, @function
function:
	.frame	$fp,32,$31		# vars= 16, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	daddiu	$sp,$sp,-32
	sd	$fp,24($sp)
	move	$fp,$sp
	move	$2,$4
	sll	$2,$2,0
	sw	$2,12($fp)
	lw	$3,12($fp)
	move	$2,$3
	sll	$2,$2,1
	addu	$2,$2,$3
	addiu	$2,$2,5
	move	$sp,$fp
	ld	$fp,24($sp)
	daddiu	$sp,$sp,32
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	function
	.size	function, .-function
	.ident	"GCC: (Ubuntu 8.3.0-7ubuntu1) 8.3.0"
