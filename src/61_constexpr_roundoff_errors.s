	.file	"61_constexpr_roundoff_errors.cpp"
	.text
#APP
	.globl _ZSt21ios_base_library_initv
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Float: "
.LC1:
	.string	" | Hex: 0x"
.LC2:
	.string	"\n"
#NO_APP
	.text
	.p2align 4
	.globl	_Z10print_bitsf
	.type	_Z10print_bitsf, @function
_Z10print_bitsf:
.LFB3382:
	.cfi_startproc
	endbr64
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	leaq	.LC0(%rip), %rsi
	movl	$7, %edx
	movd	%xmm0, %r14d
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	leaq	_ZSt4cout(%rip), %rbx
	movq	%rbx, %rdi
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	_ZSt4cout(%rip), %rax
	movq	%rbx, %rdi
	pxor	%xmm0, %xmm0
	movd	%r14d, %xmm1
	movq	-24(%rax), %rdx
	cvtss2sd	%xmm1, %xmm0
	addq	%rbx, %rdx
	movl	24(%rdx), %eax
	movq	$10, 8(%rdx)
	andl	$-261, %eax
	orl	$4, %eax
	movl	%eax, 24(%rdx)
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$10, %edx
	leaq	.LC1(%rip), %rsi
	movq	%rax, %rbx
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	(%rbx), %rax
	movl	%r14d, %esi
	movq	%rbx, %rdi
	movq	-24(%rax), %rdx
	addq	%rbx, %rdx
	movl	24(%rdx), %eax
	andl	$-75, %eax
	orl	$8, %eax
	movl	%eax, 24(%rdx)
	call	_ZNSo9_M_insertImEERSoT_@PLT
	leaq	.LC2(%rip), %rsi
	movq	%rax, %rdi
	movq	(%rax), %rax
	movq	-24(%rax), %rdx
	addq	%rdi, %rdx
	movl	24(%rdx), %eax
	andl	$-75, %eax
	orl	$2, %eax
	movl	%eax, 24(%rdx)
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	movl	$1, %edx
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	jmp	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	.cfi_endproc
.LFE3382:
	.size	_Z10print_bitsf, .-_Z10print_bitsf
	.section	.rodata.str1.1
.LC5:
	.string	"Runtime: "
.LC6:
	.string	"Compile: "
.LC8:
	.string	"Matches \342\234\223\n"
.LC9:
	.string	"Differs \342\234\227\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB3386:
	.cfi_startproc
	endbr64
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	movss	.LC4(%rip), %xmm0
	call	_Z10print_bitsf
	movss	.LC3(%rip), %xmm3
	movl	$2, %edx
	movaps	%xmm3, %xmm2
	.p2align 4,,10
	.p2align 3
.L5:
	movaps	%xmm3, %xmm0
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L6:
	pxor	%xmm1, %xmm1
	cvtsi2ssl	%eax, %xmm1
	addl	$1, %eax
	mulss	%xmm1, %xmm0
	cmpl	%eax, %edx
	jne	.L6
	movaps	%xmm3, %xmm1
	addl	$1, %edx
	divss	%xmm0, %xmm1
	addss	%xmm1, %xmm2
	cmpl	$17, %edx
	jne	.L5
	leaq	_ZSt4cout(%rip), %rbx
	leaq	.LC5(%rip), %rsi
	movss	%xmm2, 12(%rsp)
	movq	%rbx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movss	12(%rsp), %xmm2
	movaps	%xmm2, %xmm0
	call	_Z10print_bitsf
	leaq	.LC6(%rip), %rsi
	movq	%rbx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movss	.LC7(%rip), %xmm0
	call	_Z10print_bitsf
	movss	12(%rsp), %xmm2
	ucomiss	.LC7(%rip), %xmm2
	jp	.L8
	jne	.L8
	leaq	.LC8(%rip), %rsi
	movq	%rbx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
.L10:
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L8:
	.cfi_restore_state
	leaq	.LC9(%rip), %rsi
	movq	%rbx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	jmp	.L10
	.cfi_endproc
.LFE3386:
	.size	main, .-main
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC3:
	.long	1065353216
	.align 4
.LC4:
	.long	1076754516
	.align 4
.LC7:
	.long	1076754517
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
