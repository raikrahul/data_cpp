	.file	"54_recursive_template_asm.cpp"
	.text
#APP
	.globl _ZSt21ios_base_library_initv
#NO_APP
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB2432:
	.cfi_startproc
	endbr64
	movl	$6, %eax
	ret
	.cfi_endproc
.LFE2432:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
