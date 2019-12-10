	.text
	.option	pic0
	.text
	.globl	main                    # -- Begin function main
	.set	nomicromips
	.set	nomips16
	.ent	main
main:                                   # @main
	.frame	$fp,32,$ra
	.mask 	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# %bb.0:
	addiu	$sp, $sp, -32
	sw	$ra, 28($sp)            # 4-byte Folded Spill
	sw	$fp, 24($sp)            # 4-byte Folded Spill
	move	$fp, $sp
	sw	$zero, 20($fp)
	lui	$1, %hi($.str)
	addiu	$4, $1, %lo($.str)
	jal	printf
	nop
	addiu	$1, $zero, 0
	sw	$2, 16($fp)             # 4-byte Folded Spill
	move	$2, $1
	move	$sp, $fp
	lw	$fp, 24($sp)            # 4-byte Folded Reload
	lw	$ra, 28($sp)            # 4-byte Folded Reload
	addiu	$sp, $sp, 32
	jr	$ra
	nop
	.set	at
	.set	macro
	.set	reorder
	.end	main
$func_end0:
	.size	main, ($func_end0)-main
                                        # -- End function
	.type	$.str,@object           # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
$.str:
	.asciz	"Hello world\n"
	.size	$.str, 13


	.ident	"clang version 9.0.0-2 (tags/RELEASE_900/final)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym printf
	.text
