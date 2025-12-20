	.file	"49_template_vs_auto_asm.cpp"
	.text
	.section	.text._Z9iPow_autoIiEDaT_i,"axG",@progbits,_Z9iPow_autoIiEDaT_i,comdat
	.weak	_Z9iPow_autoIiEDaT_i
	.type	_Z9iPow_autoIiEDaT_i, @function
_Z9iPow_autoIiEDaT_i:
.LFB5:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	$1, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L3:
	movl	-8(%rbp), %eax
	imull	-20(%rbp), %eax
	movl	%eax, -8(%rbp)
	addl	$1, -4(%rbp)
.L2:
	movl	-4(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L3
	movl	-8(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	_Z9iPow_autoIiEDaT_i, .-_Z9iPow_autoIiEDaT_i
	.section	.text._Z9iPow_autoIdEDaT_i,"axG",@progbits,_Z9iPow_autoIdEDaT_i,comdat
	.weak	_Z9iPow_autoIdEDaT_i
	.type	_Z9iPow_autoIdEDaT_i, @function
_Z9iPow_autoIdEDaT_i:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movsd	%xmm0, -24(%rbp)
	movl	%edi, -28(%rbp)
	movsd	.LC0(%rip), %xmm0
	movsd	%xmm0, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L6
.L7:
	movsd	-8(%rbp), %xmm0
	mulsd	-24(%rbp), %xmm0
	movsd	%xmm0, -8(%rbp)
	addl	$1, -12(%rbp)
.L6:
	movl	-12(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L7
	movsd	-8(%rbp), %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	_Z9iPow_autoIdEDaT_i, .-_Z9iPow_autoIdEDaT_i
	.section	.rodata
.LC2:
	.string	"template<int>(2,3) = %d\n"
.LC3:
	.string	"auto<int>(2,3) = %d\n"
.LC4:
	.string	"template<double>(2.5,4) = %f\n"
.LC5:
	.string	"auto<double>(2.5,4) = %f\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB4:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	$3, %esi
	movl	$2, %edi
	call	_Z13iPow_templateIiET_S0_i
	movl	%eax, -24(%rbp)
	movl	$3, %esi
	movl	$2, %edi
	call	_Z9iPow_autoIiEDaT_i
	movl	%eax, -20(%rbp)
	movq	.LC1(%rip), %rax
	movl	$4, %edi
	movq	%rax, %xmm0
	call	_Z13iPow_templateIdET_S0_i
	movq	%xmm0, %rax
	movq	%rax, -16(%rbp)
	movq	.LC1(%rip), %rax
	movl	$4, %edi
	movq	%rax, %xmm0
	call	_Z9iPow_autoIdEDaT_i
	movq	%xmm0, %rax
	movq	%rax, -8(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-16(%rbp), %rax
	movq	%rax, %xmm0
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %xmm0
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	movl	-24(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jne	.L10
	movsd	-16(%rbp), %xmm0
	ucomisd	-8(%rbp), %xmm0
	jp	.L10
	movsd	-16(%rbp), %xmm0
	ucomisd	-8(%rbp), %xmm0
	je	.L11
.L10:
	movl	$1, %eax
	jmp	.L13
.L11:
	movl	$0, %eax
.L13:
	movzbl	%al, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	main, .-main
	.section	.text._Z13iPow_templateIiET_S0_i,"axG",@progbits,_Z13iPow_templateIiET_S0_i,comdat
	.weak	_Z13iPow_templateIiET_S0_i
	.type	_Z13iPow_templateIiET_S0_i, @function
_Z13iPow_templateIiET_S0_i:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	$1, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L16
.L17:
	movl	-8(%rbp), %eax
	imull	-20(%rbp), %eax
	movl	%eax, -8(%rbp)
	addl	$1, -4(%rbp)
.L16:
	movl	-4(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L17
	movl	-8(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	_Z13iPow_templateIiET_S0_i, .-_Z13iPow_templateIiET_S0_i
	.section	.text._Z13iPow_templateIdET_S0_i,"axG",@progbits,_Z13iPow_templateIdET_S0_i,comdat
	.weak	_Z13iPow_templateIdET_S0_i
	.type	_Z13iPow_templateIdET_S0_i, @function
_Z13iPow_templateIdET_S0_i:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movsd	%xmm0, -24(%rbp)
	movl	%edi, -28(%rbp)
	movsd	.LC0(%rip), %xmm0
	movsd	%xmm0, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L20
.L21:
	movsd	-8(%rbp), %xmm0
	mulsd	-24(%rbp), %xmm0
	movsd	%xmm0, -8(%rbp)
	addl	$1, -12(%rbp)
.L20:
	movl	-12(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L21
	movsd	-8(%rbp), %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	_Z13iPow_templateIdET_S0_i, .-_Z13iPow_templateIdET_S0_i
	.section	.rodata
	.align 8
.LC0:
	.long	0
	.long	1072693248
	.align 8
.LC1:
	.long	0
	.long	1074003968
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
