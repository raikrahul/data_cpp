	.file	"68_stencil_variant_lesson.cpp"
	.text
	.section	.text._ZSt26__throw_bad_variant_accessPKc,"axG",@progbits,_ZSt26__throw_bad_variant_accessPKc,comdat
	.weak	_ZSt26__throw_bad_variant_accessPKc
	.type	_ZSt26__throw_bad_variant_accessPKc, @function
_ZSt26__throw_bad_variant_accessPKc:
.LFB313:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	abort@PLT
	.cfi_endproc
.LFE313:
	.size	_ZSt26__throw_bad_variant_accessPKc, .-_ZSt26__throw_bad_variant_accessPKc
#APP
	.globl _ZSt21ios_base_library_initv
#NO_APP
	.section	.rodata
	.align 32
	.type	_ZL9U_initial, @object
	.size	_ZL9U_initial, 80
_ZL9U_initial:
	.long	0
	.long	0
	.long	1614907703
	.long	1071829221
	.long	-1924145349
	.long	1072590487
	.long	-1924145349
	.long	1072590487
	.long	1614907703
	.long	1071829221
	.long	0
	.long	0
	.long	1614907703
	.long	-1075654427
	.long	-1924145349
	.long	-1074893161
	.long	-1924145349
	.long	-1074893161
	.long	1614907703
	.long	-1075654427
	.text
	.globl	_Z5applyRK9DirichletPKdid
	.type	_Z5applyRK9DirichletPKdid, @function
_Z5applyRK9DirichletPKdid:
.LFB3066:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	movsd	%xmm0, -32(%rbp)
	movq	-8(%rbp), %rax
	movsd	(%rax), %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3066:
	.size	_Z5applyRK9DirichletPKdid, .-_Z5applyRK9DirichletPKdid
	.globl	_Z5applyRK2O2PKdid
	.type	_Z5applyRK2O2PKdid, @function
_Z5applyRK2O2PKdid:
.LFB3067:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movl	%edx, -68(%rbp)
	movsd	%xmm0, -80(%rbp)
	movl	-68(%rbp), %eax
	cltq
	salq	$3, %rax
	leaq	-8(%rax), %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm0
	movsd	%xmm0, -40(%rbp)
	movl	-68(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm0
	movsd	%xmm0, -32(%rbp)
	movl	-68(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,8), %rdx
	movq	-64(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm0
	movsd	%xmm0, -24(%rbp)
	movsd	-40(%rbp), %xmm1
	movsd	.LC0(%rip), %xmm0
	mulsd	%xmm0, %xmm1
	movsd	-32(%rbp), %xmm2
	pxor	%xmm0, %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm0, %xmm1
	movsd	-24(%rbp), %xmm2
	movsd	.LC2(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
	movq	-56(%rbp), %rax
	movsd	(%rax), %xmm0
	mulsd	-80(%rbp), %xmm0
	movsd	-16(%rbp), %xmm1
	mulsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	movsd	-32(%rbp), %xmm0
	addsd	-8(%rbp), %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3067:
	.size	_Z5applyRK2O2PKdid, .-_Z5applyRK2O2PKdid
	.globl	_Z5applyRK2O4PKdid
	.type	_Z5applyRK2O4PKdid, @function
_Z5applyRK2O4PKdid:
.LFB3068:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movl	%edx, -84(%rbp)
	movsd	%xmm0, -96(%rbp)
	movl	-84(%rbp), %eax
	cltq
	salq	$3, %rax
	leaq	-16(%rax), %rdx
	movq	-80(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm0
	movsd	%xmm0, -56(%rbp)
	movl	-84(%rbp), %eax
	cltq
	salq	$3, %rax
	leaq	-8(%rax), %rdx
	movq	-80(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm0
	movsd	%xmm0, -48(%rbp)
	movl	-84(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-80(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm0
	movsd	%xmm0, -40(%rbp)
	movl	-84(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,8), %rdx
	movq	-80(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm0
	movsd	%xmm0, -32(%rbp)
	movl	-84(%rbp), %eax
	cltq
	addq	$2, %rax
	leaq	0(,%rax,8), %rdx
	movq	-80(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm0
	movsd	%xmm0, -24(%rbp)
	movsd	-56(%rbp), %xmm1
	movsd	.LC3(%rip), %xmm0
	mulsd	%xmm0, %xmm1
	movsd	-48(%rbp), %xmm2
	movsd	.LC4(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm0, %xmm1
	movsd	-40(%rbp), %xmm2
	pxor	%xmm0, %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm0, %xmm1
	movsd	-32(%rbp), %xmm2
	movsd	.LC5(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm0, %xmm1
	movsd	-24(%rbp), %xmm2
	movsd	.LC6(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
	movq	-72(%rbp), %rax
	movsd	(%rax), %xmm0
	mulsd	-96(%rbp), %xmm0
	movsd	-16(%rbp), %xmm1
	mulsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	movsd	-40(%rbp), %xmm0
	addsd	-8(%rbp), %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3068:
	.size	_Z5applyRK2O4PKdid, .-_Z5applyRK2O4PKdid
	.section	.text._ZNK7VisitorclERK9Dirichlet,"axG",@progbits,_ZNK7VisitorclERK9Dirichlet,comdat
	.align 2
	.weak	_ZNK7VisitorclERK9Dirichlet
	.type	_ZNK7VisitorclERK9Dirichlet, @function
_ZNK7VisitorclERK9Dirichlet:
.LFB3069:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	16(%rax), %rsi
	movq	-8(%rbp), %rax
	movl	8(%rax), %edx
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-16(%rbp), %rax
	movq	%rsi, %xmm0
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	_Z5applyRK9DirichletPKdid
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3069:
	.size	_ZNK7VisitorclERK9Dirichlet, .-_ZNK7VisitorclERK9Dirichlet
	.section	.text._ZNK7VisitorclERK2O2,"axG",@progbits,_ZNK7VisitorclERK2O2,comdat
	.align 2
	.weak	_ZNK7VisitorclERK2O2
	.type	_ZNK7VisitorclERK2O2, @function
_ZNK7VisitorclERK2O2:
.LFB3070:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	16(%rax), %rsi
	movq	-8(%rbp), %rax
	movl	8(%rax), %edx
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-16(%rbp), %rax
	movq	%rsi, %xmm0
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	_Z5applyRK2O2PKdid
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3070:
	.size	_ZNK7VisitorclERK2O2, .-_ZNK7VisitorclERK2O2
	.section	.text._ZNK7VisitorclERK2O4,"axG",@progbits,_ZNK7VisitorclERK2O4,comdat
	.align 2
	.weak	_ZNK7VisitorclERK2O4
	.type	_ZNK7VisitorclERK2O4, @function
_ZNK7VisitorclERK2O4:
.LFB3071:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	16(%rax), %rsi
	movq	-8(%rbp), %rax
	movl	8(%rax), %edx
	movq	-8(%rbp), %rax
	movq	(%rax), %rcx
	movq	-16(%rbp), %rax
	movq	%rsi, %xmm0
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	_Z5applyRK2O4PKdid
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3071:
	.size	_ZNK7VisitorclERK2O4, .-_ZNK7VisitorclERK2O4
	.section	.rodata
.LC9:
	.string	"Results:\n"
.LC10:
	.string	"new_U["
.LC11:
	.string	"] = "
.LC12:
	.string	"\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3072:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$400, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -388(%rbp)
	jmp	.L15
.L16:
	movl	-388(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	_ZL9U_initial(%rip), %rax
	movsd	(%rdx,%rax), %xmm0
	movl	-388(%rbp), %eax
	cltq
	movsd	%xmm0, -336(%rbp,%rax,8)
	addl	$1, -388(%rbp)
.L15:
	cmpl	$9, -388(%rbp)
	jle	.L16
	leaq	-176(%rbp), %rdx
	movl	$0, %eax
	movl	$20, %ecx
	movq	%rdx, %rdi
	rep stosq
	movsd	.LC7(%rip), %xmm0
	movsd	%xmm0, -160(%rbp)
	movb	$1, -152(%rbp)
	movsd	.LC7(%rip), %xmm0
	movsd	%xmm0, -144(%rbp)
	movb	$1, -136(%rbp)
	movsd	.LC7(%rip), %xmm0
	movsd	%xmm0, -128(%rbp)
	movb	$2, -120(%rbp)
	movsd	.LC7(%rip), %xmm0
	movsd	%xmm0, -112(%rbp)
	movb	$2, -104(%rbp)
	movsd	.LC7(%rip), %xmm0
	movsd	%xmm0, -96(%rbp)
	movb	$2, -88(%rbp)
	movsd	.LC7(%rip), %xmm0
	movsd	%xmm0, -80(%rbp)
	movb	$1, -72(%rbp)
	movsd	.LC7(%rip), %xmm0
	movsd	%xmm0, -64(%rbp)
	movb	$1, -56(%rbp)
	movsd	.LC7(%rip), %xmm0
	movsd	%xmm0, -48(%rbp)
	movb	$1, -40(%rbp)
	movsd	.LC8(%rip), %xmm0
	movsd	%xmm0, -376(%rbp)
	movl	$0, -384(%rbp)
	jmp	.L17
.L18:
	leaq	-336(%rbp), %rax
	movq	%rax, -368(%rbp)
	movl	-384(%rbp), %eax
	movl	%eax, -360(%rbp)
	movsd	-376(%rbp), %xmm0
	movsd	%xmm0, -352(%rbp)
	leaq	-176(%rbp), %rax
	movl	-384(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rax, %rdx
	leaq	-368(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZSt5visitIR7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEENSt13invoke_resultIT_JDpNSt13__conditionalIX21is_lvalue_reference_vIT0_EEE4typeIRNSt19variant_alternativeILm0ENSt16remove_referenceIDTcl4__ascl7declvalISB_EEEEE4typeEE4typeEOSK_EEEE4typeEOS9_DpOSB_
	movq	%xmm0, %rax
	movl	-384(%rbp), %edx
	movslq	%edx, %rdx
	movq	%rax, -256(%rbp,%rdx,8)
	addl	$1, -384(%rbp)
.L17:
	cmpl	$9, -384(%rbp)
	jle	.L18
	leaq	.LC9(%rip), %rax
	movq	%rax, %rsi
	leaq	_ZSt4cout(%rip), %rax
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movl	$0, -380(%rbp)
	jmp	.L19
.L20:
	leaq	.LC10(%rip), %rax
	movq	%rax, %rsi
	leaq	_ZSt4cout(%rip), %rax
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movl	-380(%rbp), %eax
	movl	%eax, %esi
	movq	%rdx, %rdi
	call	_ZNSolsEi@PLT
	movq	%rax, %rdx
	leaq	.LC11(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movl	-380(%rbp), %eax
	cltq
	movq	-256(%rbp,%rax,8), %rax
	movq	%rax, %xmm0
	movq	%rdx, %rdi
	call	_ZNSolsEd@PLT
	movq	%rax, %rdx
	leaq	.LC12(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	addl	$1, -380(%rbp)
.L19:
	cmpl	$9, -380(%rbp)
	jle	.L20
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L22
	call	__stack_chk_fail@PLT
.L22:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3072:
	.size	main, .-main
	.section	.text._ZZSt10__do_visitINSt8__detail9__variant21__deduce_visit_resultIdEER7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_DpOT1_ENKUlSB_zE_clESB_z,"axG",@progbits,_ZZSt10__do_visitINSt8__detail9__variant21__deduce_visit_resultIdEER7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_DpOT1_ENKUlSB_zE_clESB_z,comdat
	.align 2
	.weak	_ZZSt10__do_visitINSt8__detail9__variant21__deduce_visit_resultIdEER7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_DpOT1_ENKUlSB_zE_clESB_z
	.type	_ZZSt10__do_visitINSt8__detail9__variant21__deduce_visit_resultIdEER7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_DpOT1_ENKUlSB_zE_clESB_z, @function
_ZZSt10__do_visitINSt8__detail9__variant21__deduce_visit_resultIdEER7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_DpOT1_ENKUlSB_zE_clESB_z:
.LFB3538:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$72, %rsp
	movq	%rdi, -184(%rbp)
	movq	%rsi, -192(%rbp)
	movq	%rdx, -160(%rbp)
	movq	%rcx, -152(%rbp)
	movq	%r8, -144(%rbp)
	movq	%r9, -136(%rbp)
	testb	%al, %al
	je	.L26
	movaps	%xmm0, -128(%rbp)
	movaps	%xmm1, -112(%rbp)
	movaps	%xmm2, -96(%rbp)
	movaps	%xmm3, -80(%rbp)
	movaps	%xmm4, -64(%rbp)
	movaps	%xmm5, -48(%rbp)
	movaps	%xmm6, -32(%rbp)
	movaps	%xmm7, -16(%rbp)
.L26:
	movq	-192(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3538:
	.size	_ZZSt10__do_visitINSt8__detail9__variant21__deduce_visit_resultIdEER7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_DpOT1_ENKUlSB_zE_clESB_z, .-_ZZSt10__do_visitINSt8__detail9__variant21__deduce_visit_resultIdEER7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_DpOT1_ENKUlSB_zE_clESB_z
	.section	.text._ZNSt8__detail9__variant7__get_nILm0ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_,"axG",@progbits,_ZNSt8__detail9__variant7__get_nILm0ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_,comdat
	.weak	_ZNSt8__detail9__variant7__get_nILm0ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_
	.type	_ZNSt8__detail9__variant7__get_nILm0ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_, @function
_ZNSt8__detail9__variant7__get_nILm0ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_:
.LFB3542:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIRNSt8__detail9__variant15_Variadic_unionIJ9Dirichlet2O22O4EEEEOT_RNSt16remove_referenceIS8_E4typeE
	movq	%rax, %rdi
	call	_ZNRSt8__detail9__variant14_UninitializedI9DirichletLb1EE6_M_getEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3542:
	.size	_ZNSt8__detail9__variant7__get_nILm0ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_, .-_ZNSt8__detail9__variant7__get_nILm0ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_
	.section	.text._ZNSt8__detail9__variant5__getILm0ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_,"axG",@progbits,_ZNSt8__detail9__variant5__getILm0ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_,comdat
	.weak	_ZNSt8__detail9__variant5__getILm0ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_
	.type	_ZNSt8__detail9__variant5__getILm0ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_, @function
_ZNSt8__detail9__variant5__getILm0ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_:
.LFB3541:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIRSt7variantIJ9Dirichlet2O22O4EEEOT_RNSt16remove_referenceIS6_E4typeE
	movq	%rax, %rdi
	call	_ZNSt8__detail9__variant7__get_nILm0ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3541:
	.size	_ZNSt8__detail9__variant5__getILm0ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_, .-_ZNSt8__detail9__variant5__getILm0ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_
	.section	.text._ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm0EEEE28__element_by_index_or_cookieILm0ESC_EEDcOT0_,"axG",@progbits,_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm0EEEE28__element_by_index_or_cookieILm0ESC_EEDcOT0_,comdat
	.weak	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm0EEEE28__element_by_index_or_cookieILm0ESC_EEDcOT0_
	.type	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm0EEEE28__element_by_index_or_cookieILm0ESC_EEDcOT0_, @function
_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm0EEEE28__element_by_index_or_cookieILm0ESC_EEDcOT0_:
.LFB3540:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIRSt7variantIJ9Dirichlet2O22O4EEEOT_RNSt16remove_referenceIS6_E4typeE
	movq	%rax, %rdi
	call	_ZNSt8__detail9__variant5__getILm0ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3540:
	.size	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm0EEEE28__element_by_index_or_cookieILm0ESC_EEDcOT0_, .-_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm0EEEE28__element_by_index_or_cookieILm0ESC_EEDcOT0_
	.section	.text._ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm0EEEE14__visit_invokeES6_SC_,"axG",@progbits,_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm0EEEE14__visit_invokeES6_SC_,comdat
	.weak	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm0EEEE14__visit_invokeES6_SC_
	.type	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm0EEEE14__visit_invokeES6_SC_, @function
_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm0EEEE14__visit_invokeES6_SC_:
.LFB3539:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIRSt7variantIJ9Dirichlet2O22O4EEEOT_RNSt16remove_referenceIS6_E4typeE
	movq	%rax, %rdi
	call	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm0EEEE28__element_by_index_or_cookieILm0ESC_EEDcOT0_
	movq	%rax, %rbx
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIR7VisitorEOT_RNSt16remove_referenceIS2_E4typeE
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZSt8__invokeIR7VisitorJR9DirichletEENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3539:
	.size	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm0EEEE14__visit_invokeES6_SC_, .-_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm0EEEE14__visit_invokeES6_SC_
	.section	.text._ZNSt8__detail9__variant7__get_nILm1ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_,"axG",@progbits,_ZNSt8__detail9__variant7__get_nILm1ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_,comdat
	.weak	_ZNSt8__detail9__variant7__get_nILm1ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_
	.type	_ZNSt8__detail9__variant7__get_nILm1ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_, @function
_ZNSt8__detail9__variant7__get_nILm1ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_:
.LFB3547:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIRNSt8__detail9__variant15_Variadic_unionIJ9Dirichlet2O22O4EEEEOT_RNSt16remove_referenceIS8_E4typeE
	movq	%rax, %rdi
	call	_ZNRSt8__detail9__variant14_UninitializedI2O2Lb1EE6_M_getEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3547:
	.size	_ZNSt8__detail9__variant7__get_nILm1ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_, .-_ZNSt8__detail9__variant7__get_nILm1ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_
	.section	.text._ZNSt8__detail9__variant5__getILm1ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_,"axG",@progbits,_ZNSt8__detail9__variant5__getILm1ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_,comdat
	.weak	_ZNSt8__detail9__variant5__getILm1ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_
	.type	_ZNSt8__detail9__variant5__getILm1ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_, @function
_ZNSt8__detail9__variant5__getILm1ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_:
.LFB3546:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIRSt7variantIJ9Dirichlet2O22O4EEEOT_RNSt16remove_referenceIS6_E4typeE
	movq	%rax, %rdi
	call	_ZNSt8__detail9__variant7__get_nILm1ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3546:
	.size	_ZNSt8__detail9__variant5__getILm1ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_, .-_ZNSt8__detail9__variant5__getILm1ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_
	.section	.text._ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm1EEEE28__element_by_index_or_cookieILm1ESC_EEDcOT0_,"axG",@progbits,_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm1EEEE28__element_by_index_or_cookieILm1ESC_EEDcOT0_,comdat
	.weak	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm1EEEE28__element_by_index_or_cookieILm1ESC_EEDcOT0_
	.type	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm1EEEE28__element_by_index_or_cookieILm1ESC_EEDcOT0_, @function
_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm1EEEE28__element_by_index_or_cookieILm1ESC_EEDcOT0_:
.LFB3545:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIRSt7variantIJ9Dirichlet2O22O4EEEOT_RNSt16remove_referenceIS6_E4typeE
	movq	%rax, %rdi
	call	_ZNSt8__detail9__variant5__getILm1ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3545:
	.size	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm1EEEE28__element_by_index_or_cookieILm1ESC_EEDcOT0_, .-_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm1EEEE28__element_by_index_or_cookieILm1ESC_EEDcOT0_
	.section	.text._ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm1EEEE14__visit_invokeES6_SC_,"axG",@progbits,_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm1EEEE14__visit_invokeES6_SC_,comdat
	.weak	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm1EEEE14__visit_invokeES6_SC_
	.type	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm1EEEE14__visit_invokeES6_SC_, @function
_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm1EEEE14__visit_invokeES6_SC_:
.LFB3544:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIRSt7variantIJ9Dirichlet2O22O4EEEOT_RNSt16remove_referenceIS6_E4typeE
	movq	%rax, %rdi
	call	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm1EEEE28__element_by_index_or_cookieILm1ESC_EEDcOT0_
	movq	%rax, %rbx
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIR7VisitorEOT_RNSt16remove_referenceIS2_E4typeE
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZSt8__invokeIR7VisitorJR2O2EENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3544:
	.size	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm1EEEE14__visit_invokeES6_SC_, .-_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm1EEEE14__visit_invokeES6_SC_
	.section	.text._ZNSt8__detail9__variant7__get_nILm2ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_,"axG",@progbits,_ZNSt8__detail9__variant7__get_nILm2ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_,comdat
	.weak	_ZNSt8__detail9__variant7__get_nILm2ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_
	.type	_ZNSt8__detail9__variant7__get_nILm2ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_, @function
_ZNSt8__detail9__variant7__get_nILm2ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_:
.LFB3552:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIRNSt8__detail9__variant15_Variadic_unionIJ9Dirichlet2O22O4EEEEOT_RNSt16remove_referenceIS8_E4typeE
	movq	%rax, %rdi
	call	_ZNRSt8__detail9__variant14_UninitializedI2O4Lb1EE6_M_getEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3552:
	.size	_ZNSt8__detail9__variant7__get_nILm2ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_, .-_ZNSt8__detail9__variant7__get_nILm2ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_
	.section	.text._ZNSt8__detail9__variant5__getILm2ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_,"axG",@progbits,_ZNSt8__detail9__variant5__getILm2ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_,comdat
	.weak	_ZNSt8__detail9__variant5__getILm2ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_
	.type	_ZNSt8__detail9__variant5__getILm2ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_, @function
_ZNSt8__detail9__variant5__getILm2ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_:
.LFB3551:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIRSt7variantIJ9Dirichlet2O22O4EEEOT_RNSt16remove_referenceIS6_E4typeE
	movq	%rax, %rdi
	call	_ZNSt8__detail9__variant7__get_nILm2ERNS0_15_Variadic_unionIJ9Dirichlet2O22O4EEEEEDcOT0_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3551:
	.size	_ZNSt8__detail9__variant5__getILm2ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_, .-_ZNSt8__detail9__variant5__getILm2ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_
	.section	.text._ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm2EEEE28__element_by_index_or_cookieILm2ESC_EEDcOT0_,"axG",@progbits,_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm2EEEE28__element_by_index_or_cookieILm2ESC_EEDcOT0_,comdat
	.weak	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm2EEEE28__element_by_index_or_cookieILm2ESC_EEDcOT0_
	.type	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm2EEEE28__element_by_index_or_cookieILm2ESC_EEDcOT0_, @function
_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm2EEEE28__element_by_index_or_cookieILm2ESC_EEDcOT0_:
.LFB3550:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIRSt7variantIJ9Dirichlet2O22O4EEEOT_RNSt16remove_referenceIS6_E4typeE
	movq	%rax, %rdi
	call	_ZNSt8__detail9__variant5__getILm2ERSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3550:
	.size	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm2EEEE28__element_by_index_or_cookieILm2ESC_EEDcOT0_, .-_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm2EEEE28__element_by_index_or_cookieILm2ESC_EEDcOT0_
	.section	.text._ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm2EEEE14__visit_invokeES6_SC_,"axG",@progbits,_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm2EEEE14__visit_invokeES6_SC_,comdat
	.weak	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm2EEEE14__visit_invokeES6_SC_
	.type	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm2EEEE14__visit_invokeES6_SC_, @function
_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm2EEEE14__visit_invokeES6_SC_:
.LFB3549:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIRSt7variantIJ9Dirichlet2O22O4EEEOT_RNSt16remove_referenceIS6_E4typeE
	movq	%rax, %rdi
	call	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm2EEEE28__element_by_index_or_cookieILm2ESC_EEDcOT0_
	movq	%rax, %rbx
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIR7VisitorEOT_RNSt16remove_referenceIS2_E4typeE
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZSt8__invokeIR7VisitorJR2O4EENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3549:
	.size	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm2EEEE14__visit_invokeES6_SC_, .-_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm2EEEE14__visit_invokeES6_SC_
	.section	.text._ZSt10__do_visitINSt8__detail9__variant21__deduce_visit_resultIdEER7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_DpOT1_,"axG",@progbits,_ZSt10__do_visitINSt8__detail9__variant21__deduce_visit_resultIdEER7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_DpOT1_,comdat
	.weak	_ZSt10__do_visitINSt8__detail9__variant21__deduce_visit_resultIdEER7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_DpOT1_
	.type	_ZSt10__do_visitINSt8__detail9__variant21__deduce_visit_resultIdEER7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_DpOT1_, @function
_ZSt10__do_visitINSt8__detail9__variant21__deduce_visit_resultIdEER7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_DpOT1_:
.LFB3537:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	$11, -48(%rbp)
	movq	$3, -40(%rbp)
	movq	-80(%rbp), %rdx
	leaq	-49(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	_ZZSt10__do_visitINSt8__detail9__variant21__deduce_visit_resultIdEER7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_DpOT1_ENKUlSB_zE_clESB_z
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt7variantIJ9Dirichlet2O22O4EE5indexEv
	cmpq	$2, %rax
	je	.L52
	cmpq	$2, %rax
	ja	.L53
	testq	%rax, %rax
	je	.L54
	cmpq	$1, %rax
	je	.L55
	jmp	.L53
.L54:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIRSt7variantIJ9Dirichlet2O22O4EEEOT_RNSt16remove_referenceIS6_E4typeE
	movq	%rax, %rbx
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIR7VisitorEOT_RNSt16remove_referenceIS2_E4typeE
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm0EEEE14__visit_invokeES6_SC_
	jmp	.L56
.L55:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIRSt7variantIJ9Dirichlet2O22O4EEEOT_RNSt16remove_referenceIS6_E4typeE
	movq	%rax, %rbx
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIR7VisitorEOT_RNSt16remove_referenceIS2_E4typeE
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm1EEEE14__visit_invokeES6_SC_
	jmp	.L56
.L52:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIRSt7variantIJ9Dirichlet2O22O4EEEOT_RNSt16remove_referenceIS6_E4typeE
	movq	%rax, %rbx
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIR7VisitorEOT_RNSt16remove_referenceIS2_E4typeE
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt8__detail9__variant17__gen_vtable_implINS0_12_Multi_arrayIPFNS0_21__deduce_visit_resultIdEER7VisitorRSt7variantIJ9Dirichlet2O22O4EEEJEEESt16integer_sequenceImJLm2EEEE14__visit_invokeES6_SC_
	jmp	.L56
.L53:
.L56:
	movq	-24(%rbp), %rax
	subq	%fs:40, %rax
	je	.L57
	call	__stack_chk_fail@PLT
.L57:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3537:
	.size	_ZSt10__do_visitINSt8__detail9__variant21__deduce_visit_resultIdEER7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_DpOT1_, .-_ZSt10__do_visitINSt8__detail9__variant21__deduce_visit_resultIdEER7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_DpOT1_
	.section	.rodata
	.align 8
.LC13:
	.string	"std::visit: variant is valueless"
	.section	.text._ZSt5visitIR7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEENSt13invoke_resultIT_JDpNSt13__conditionalIX21is_lvalue_reference_vIT0_EEE4typeIRNSt19variant_alternativeILm0ENSt16remove_referenceIDTcl4__ascl7declvalISB_EEEEE4typeEE4typeEOSK_EEEE4typeEOS9_DpOSB_,"axG",@progbits,_ZSt5visitIR7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEENSt13invoke_resultIT_JDpNSt13__conditionalIX21is_lvalue_reference_vIT0_EEE4typeIRNSt19variant_alternativeILm0ENSt16remove_referenceIDTcl4__ascl7declvalISB_EEEEE4typeEE4typeEOSK_EEEE4typeEOS9_DpOSB_,comdat
	.weak	_ZSt5visitIR7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEENSt13invoke_resultIT_JDpNSt13__conditionalIX21is_lvalue_reference_vIT0_EEE4typeIRNSt19variant_alternativeILm0ENSt16remove_referenceIDTcl4__ascl7declvalISB_EEEEE4typeEE4typeEOSK_EEEE4typeEOS9_DpOSB_
	.type	_ZSt5visitIR7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEENSt13invoke_resultIT_JDpNSt13__conditionalIX21is_lvalue_reference_vIT0_EEE4typeIRNSt19variant_alternativeILm0ENSt16remove_referenceIDTcl4__ascl7declvalISB_EEEEE4typeEE4typeEOSK_EEEE4typeEOS9_DpOSB_, @function
_ZSt5visitIR7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEENSt13invoke_resultIT_JDpNSt13__conditionalIX21is_lvalue_reference_vIT0_EEE4typeIRNSt19variant_alternativeILm0ENSt16remove_referenceIDTcl4__ascl7declvalISB_EEEEE4typeEE4typeEOSK_EEEE4typeEOS9_DpOSB_:
.LFB3533:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt8__detail9__variant4__asIJ9Dirichlet2O22O4EEERSt7variantIJDpT_EES9_
	movq	%rax, %rdi
	call	_ZNKSt7variantIJ9Dirichlet2O22O4EE22valueless_by_exceptionEv
	testb	%al, %al
	je	.L59
	leaq	.LC13(%rip), %rax
	movq	%rax, %rdi
	call	_ZSt26__throw_bad_variant_accessPKc
.L59:
	movb	$1, -1(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIR7VisitorEOT_RNSt16remove_referenceIS2_E4typeE
	movq	%rax, %rdx
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZSt10__do_visitINSt8__detail9__variant21__deduce_visit_resultIdEER7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEEDcOT0_DpOT1_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3533:
	.size	_ZSt5visitIR7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEENSt13invoke_resultIT_JDpNSt13__conditionalIX21is_lvalue_reference_vIT0_EEE4typeIRNSt19variant_alternativeILm0ENSt16remove_referenceIDTcl4__ascl7declvalISB_EEEEE4typeEE4typeEOSK_EEEE4typeEOS9_DpOSB_, .-_ZSt5visitIR7VisitorJRSt7variantIJ9Dirichlet2O22O4EEEENSt13invoke_resultIT_JDpNSt13__conditionalIX21is_lvalue_reference_vIT0_EEE4typeIRNSt19variant_alternativeILm0ENSt16remove_referenceIDTcl4__ascl7declvalISB_EEEEE4typeEE4typeEOSK_EEEE4typeEOS9_DpOSB_
	.section	.text._ZNSt8__detail9__variant4__asIJ9Dirichlet2O22O4EEERSt7variantIJDpT_EES9_,"axG",@progbits,_ZNSt8__detail9__variant4__asIJ9Dirichlet2O22O4EEERSt7variantIJDpT_EES9_,comdat
	.weak	_ZNSt8__detail9__variant4__asIJ9Dirichlet2O22O4EEERSt7variantIJDpT_EES9_
	.type	_ZNSt8__detail9__variant4__asIJ9Dirichlet2O22O4EEERSt7variantIJDpT_EES9_, @function
_ZNSt8__detail9__variant4__asIJ9Dirichlet2O22O4EEERSt7variantIJDpT_EES9_:
.LFB3712:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3712:
	.size	_ZNSt8__detail9__variant4__asIJ9Dirichlet2O22O4EEERSt7variantIJDpT_EES9_, .-_ZNSt8__detail9__variant4__asIJ9Dirichlet2O22O4EEERSt7variantIJDpT_EES9_
	.section	.text._ZNKSt7variantIJ9Dirichlet2O22O4EE22valueless_by_exceptionEv,"axG",@progbits,_ZNKSt7variantIJ9Dirichlet2O22O4EE22valueless_by_exceptionEv,comdat
	.align 2
	.weak	_ZNKSt7variantIJ9Dirichlet2O22O4EE22valueless_by_exceptionEv
	.type	_ZNKSt7variantIJ9Dirichlet2O22O4EE22valueless_by_exceptionEv, @function
_ZNKSt7variantIJ9Dirichlet2O22O4EE22valueless_by_exceptionEv:
.LFB3713:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt8__detail9__variant16_Variant_storageILb1EJ9Dirichlet2O22O4EE8_M_validEv
	xorl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3713:
	.size	_ZNKSt7variantIJ9Dirichlet2O22O4EE22valueless_by_exceptionEv, .-_ZNKSt7variantIJ9Dirichlet2O22O4EE22valueless_by_exceptionEv
	.section	.text._ZSt7forwardIR7VisitorEOT_RNSt16remove_referenceIS2_E4typeE,"axG",@progbits,_ZSt7forwardIR7VisitorEOT_RNSt16remove_referenceIS2_E4typeE,comdat
	.weak	_ZSt7forwardIR7VisitorEOT_RNSt16remove_referenceIS2_E4typeE
	.type	_ZSt7forwardIR7VisitorEOT_RNSt16remove_referenceIS2_E4typeE, @function
_ZSt7forwardIR7VisitorEOT_RNSt16remove_referenceIS2_E4typeE:
.LFB3714:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3714:
	.size	_ZSt7forwardIR7VisitorEOT_RNSt16remove_referenceIS2_E4typeE, .-_ZSt7forwardIR7VisitorEOT_RNSt16remove_referenceIS2_E4typeE
	.section	.text._ZNKSt7variantIJ9Dirichlet2O22O4EE5indexEv,"axG",@progbits,_ZNKSt7variantIJ9Dirichlet2O22O4EE5indexEv,comdat
	.align 2
	.weak	_ZNKSt7variantIJ9Dirichlet2O22O4EE5indexEv
	.type	_ZNKSt7variantIJ9Dirichlet2O22O4EE5indexEv, @function
_ZNKSt7variantIJ9Dirichlet2O22O4EE5indexEv:
.LFB3715:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movzbl	8(%rax), %eax
	movzbl	%al, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3715:
	.size	_ZNKSt7variantIJ9Dirichlet2O22O4EE5indexEv, .-_ZNKSt7variantIJ9Dirichlet2O22O4EE5indexEv
	.section	.text._ZSt7forwardIRSt7variantIJ9Dirichlet2O22O4EEEOT_RNSt16remove_referenceIS6_E4typeE,"axG",@progbits,_ZSt7forwardIRSt7variantIJ9Dirichlet2O22O4EEEOT_RNSt16remove_referenceIS6_E4typeE,comdat
	.weak	_ZSt7forwardIRSt7variantIJ9Dirichlet2O22O4EEEOT_RNSt16remove_referenceIS6_E4typeE
	.type	_ZSt7forwardIRSt7variantIJ9Dirichlet2O22O4EEEOT_RNSt16remove_referenceIS6_E4typeE, @function
_ZSt7forwardIRSt7variantIJ9Dirichlet2O22O4EEEOT_RNSt16remove_referenceIS6_E4typeE:
.LFB3717:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3717:
	.size	_ZSt7forwardIRSt7variantIJ9Dirichlet2O22O4EEEOT_RNSt16remove_referenceIS6_E4typeE, .-_ZSt7forwardIRSt7variantIJ9Dirichlet2O22O4EEEOT_RNSt16remove_referenceIS6_E4typeE
	.section	.text._ZSt7forwardIRNSt8__detail9__variant15_Variadic_unionIJ9Dirichlet2O22O4EEEEOT_RNSt16remove_referenceIS8_E4typeE,"axG",@progbits,_ZSt7forwardIRNSt8__detail9__variant15_Variadic_unionIJ9Dirichlet2O22O4EEEEOT_RNSt16remove_referenceIS8_E4typeE,comdat
	.weak	_ZSt7forwardIRNSt8__detail9__variant15_Variadic_unionIJ9Dirichlet2O22O4EEEEOT_RNSt16remove_referenceIS8_E4typeE
	.type	_ZSt7forwardIRNSt8__detail9__variant15_Variadic_unionIJ9Dirichlet2O22O4EEEEOT_RNSt16remove_referenceIS8_E4typeE, @function
_ZSt7forwardIRNSt8__detail9__variant15_Variadic_unionIJ9Dirichlet2O22O4EEEEOT_RNSt16remove_referenceIS8_E4typeE:
.LFB3718:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3718:
	.size	_ZSt7forwardIRNSt8__detail9__variant15_Variadic_unionIJ9Dirichlet2O22O4EEEEOT_RNSt16remove_referenceIS8_E4typeE, .-_ZSt7forwardIRNSt8__detail9__variant15_Variadic_unionIJ9Dirichlet2O22O4EEEEOT_RNSt16remove_referenceIS8_E4typeE
	.section	.text._ZNRSt8__detail9__variant14_UninitializedI9DirichletLb1EE6_M_getEv,"axG",@progbits,_ZNRSt8__detail9__variant14_UninitializedI9DirichletLb1EE6_M_getEv,comdat
	.align 2
	.weak	_ZNRSt8__detail9__variant14_UninitializedI9DirichletLb1EE6_M_getEv
	.type	_ZNRSt8__detail9__variant14_UninitializedI9DirichletLb1EE6_M_getEv, @function
_ZNRSt8__detail9__variant14_UninitializedI9DirichletLb1EE6_M_getEv:
.LFB3719:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3719:
	.size	_ZNRSt8__detail9__variant14_UninitializedI9DirichletLb1EE6_M_getEv, .-_ZNRSt8__detail9__variant14_UninitializedI9DirichletLb1EE6_M_getEv
	.section	.text._ZSt8__invokeIR7VisitorJR9DirichletEENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_,"axG",@progbits,_ZSt8__invokeIR7VisitorJR9DirichletEENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_,comdat
	.weak	_ZSt8__invokeIR7VisitorJR9DirichletEENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_
	.type	_ZSt8__invokeIR7VisitorJR9DirichletEENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_, @function
_ZSt8__invokeIR7VisitorJR9DirichletEENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_:
.LFB3720:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIR9DirichletEOT_RNSt16remove_referenceIS2_E4typeE
	movq	%rax, %rbx
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIR7VisitorEOT_RNSt16remove_referenceIS2_E4typeE
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZSt13__invoke_implIdR7VisitorJR9DirichletEET_St14__invoke_otherOT0_DpOT1_
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3720:
	.size	_ZSt8__invokeIR7VisitorJR9DirichletEENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_, .-_ZSt8__invokeIR7VisitorJR9DirichletEENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_
	.section	.text._ZNRSt8__detail9__variant14_UninitializedI2O2Lb1EE6_M_getEv,"axG",@progbits,_ZNRSt8__detail9__variant14_UninitializedI2O2Lb1EE6_M_getEv,comdat
	.align 2
	.weak	_ZNRSt8__detail9__variant14_UninitializedI2O2Lb1EE6_M_getEv
	.type	_ZNRSt8__detail9__variant14_UninitializedI2O2Lb1EE6_M_getEv, @function
_ZNRSt8__detail9__variant14_UninitializedI2O2Lb1EE6_M_getEv:
.LFB3721:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3721:
	.size	_ZNRSt8__detail9__variant14_UninitializedI2O2Lb1EE6_M_getEv, .-_ZNRSt8__detail9__variant14_UninitializedI2O2Lb1EE6_M_getEv
	.section	.text._ZSt8__invokeIR7VisitorJR2O2EENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_,"axG",@progbits,_ZSt8__invokeIR7VisitorJR2O2EENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_,comdat
	.weak	_ZSt8__invokeIR7VisitorJR2O2EENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_
	.type	_ZSt8__invokeIR7VisitorJR2O2EENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_, @function
_ZSt8__invokeIR7VisitorJR2O2EENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_:
.LFB3722:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIR2O2EOT_RNSt16remove_referenceIS2_E4typeE
	movq	%rax, %rbx
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIR7VisitorEOT_RNSt16remove_referenceIS2_E4typeE
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZSt13__invoke_implIdR7VisitorJR2O2EET_St14__invoke_otherOT0_DpOT1_
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3722:
	.size	_ZSt8__invokeIR7VisitorJR2O2EENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_, .-_ZSt8__invokeIR7VisitorJR2O2EENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_
	.section	.text._ZNRSt8__detail9__variant14_UninitializedI2O4Lb1EE6_M_getEv,"axG",@progbits,_ZNRSt8__detail9__variant14_UninitializedI2O4Lb1EE6_M_getEv,comdat
	.align 2
	.weak	_ZNRSt8__detail9__variant14_UninitializedI2O4Lb1EE6_M_getEv
	.type	_ZNRSt8__detail9__variant14_UninitializedI2O4Lb1EE6_M_getEv, @function
_ZNRSt8__detail9__variant14_UninitializedI2O4Lb1EE6_M_getEv:
.LFB3723:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3723:
	.size	_ZNRSt8__detail9__variant14_UninitializedI2O4Lb1EE6_M_getEv, .-_ZNRSt8__detail9__variant14_UninitializedI2O4Lb1EE6_M_getEv
	.section	.text._ZSt8__invokeIR7VisitorJR2O4EENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_,"axG",@progbits,_ZSt8__invokeIR7VisitorJR2O4EENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_,comdat
	.weak	_ZSt8__invokeIR7VisitorJR2O4EENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_
	.type	_ZSt8__invokeIR7VisitorJR2O4EENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_, @function
_ZSt8__invokeIR7VisitorJR2O4EENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_:
.LFB3724:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIR2O4EOT_RNSt16remove_referenceIS2_E4typeE
	movq	%rax, %rbx
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIR7VisitorEOT_RNSt16remove_referenceIS2_E4typeE
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZSt13__invoke_implIdR7VisitorJR2O4EET_St14__invoke_otherOT0_DpOT1_
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3724:
	.size	_ZSt8__invokeIR7VisitorJR2O4EENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_, .-_ZSt8__invokeIR7VisitorJR2O4EENSt15__invoke_resultIT_JDpT0_EE4typeEOS5_DpOS6_
	.section	.text._ZNKSt8__detail9__variant16_Variant_storageILb1EJ9Dirichlet2O22O4EE8_M_validEv,"axG",@progbits,_ZNKSt8__detail9__variant16_Variant_storageILb1EJ9Dirichlet2O22O4EE8_M_validEv,comdat
	.align 2
	.weak	_ZNKSt8__detail9__variant16_Variant_storageILb1EJ9Dirichlet2O22O4EE8_M_validEv
	.type	_ZNKSt8__detail9__variant16_Variant_storageILb1EJ9Dirichlet2O22O4EE8_M_validEv, @function
_ZNKSt8__detail9__variant16_Variant_storageILb1EJ9Dirichlet2O22O4EE8_M_validEv:
.LFB3832:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	$1, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3832:
	.size	_ZNKSt8__detail9__variant16_Variant_storageILb1EJ9Dirichlet2O22O4EE8_M_validEv, .-_ZNKSt8__detail9__variant16_Variant_storageILb1EJ9Dirichlet2O22O4EE8_M_validEv
	.section	.text._ZSt7forwardIR9DirichletEOT_RNSt16remove_referenceIS2_E4typeE,"axG",@progbits,_ZSt7forwardIR9DirichletEOT_RNSt16remove_referenceIS2_E4typeE,comdat
	.weak	_ZSt7forwardIR9DirichletEOT_RNSt16remove_referenceIS2_E4typeE
	.type	_ZSt7forwardIR9DirichletEOT_RNSt16remove_referenceIS2_E4typeE, @function
_ZSt7forwardIR9DirichletEOT_RNSt16remove_referenceIS2_E4typeE:
.LFB3833:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3833:
	.size	_ZSt7forwardIR9DirichletEOT_RNSt16remove_referenceIS2_E4typeE, .-_ZSt7forwardIR9DirichletEOT_RNSt16remove_referenceIS2_E4typeE
	.section	.text._ZSt13__invoke_implIdR7VisitorJR9DirichletEET_St14__invoke_otherOT0_DpOT1_,"axG",@progbits,_ZSt13__invoke_implIdR7VisitorJR9DirichletEET_St14__invoke_otherOT0_DpOT1_,comdat
	.weak	_ZSt13__invoke_implIdR7VisitorJR9DirichletEET_St14__invoke_otherOT0_DpOT1_
	.type	_ZSt13__invoke_implIdR7VisitorJR9DirichletEET_St14__invoke_otherOT0_DpOT1_, @function
_ZSt13__invoke_implIdR7VisitorJR9DirichletEET_St14__invoke_otherOT0_DpOT1_:
.LFB3834:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIR7VisitorEOT_RNSt16remove_referenceIS2_E4typeE
	movq	%rax, %rbx
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIR9DirichletEOT_RNSt16remove_referenceIS2_E4typeE
	movq	%rax, %rsi
	movq	%rbx, %rdi
	call	_ZNK7VisitorclERK9Dirichlet
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3834:
	.size	_ZSt13__invoke_implIdR7VisitorJR9DirichletEET_St14__invoke_otherOT0_DpOT1_, .-_ZSt13__invoke_implIdR7VisitorJR9DirichletEET_St14__invoke_otherOT0_DpOT1_
	.section	.text._ZSt7forwardIR2O2EOT_RNSt16remove_referenceIS2_E4typeE,"axG",@progbits,_ZSt7forwardIR2O2EOT_RNSt16remove_referenceIS2_E4typeE,comdat
	.weak	_ZSt7forwardIR2O2EOT_RNSt16remove_referenceIS2_E4typeE
	.type	_ZSt7forwardIR2O2EOT_RNSt16remove_referenceIS2_E4typeE, @function
_ZSt7forwardIR2O2EOT_RNSt16remove_referenceIS2_E4typeE:
.LFB3835:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3835:
	.size	_ZSt7forwardIR2O2EOT_RNSt16remove_referenceIS2_E4typeE, .-_ZSt7forwardIR2O2EOT_RNSt16remove_referenceIS2_E4typeE
	.section	.text._ZSt13__invoke_implIdR7VisitorJR2O2EET_St14__invoke_otherOT0_DpOT1_,"axG",@progbits,_ZSt13__invoke_implIdR7VisitorJR2O2EET_St14__invoke_otherOT0_DpOT1_,comdat
	.weak	_ZSt13__invoke_implIdR7VisitorJR2O2EET_St14__invoke_otherOT0_DpOT1_
	.type	_ZSt13__invoke_implIdR7VisitorJR2O2EET_St14__invoke_otherOT0_DpOT1_, @function
_ZSt13__invoke_implIdR7VisitorJR2O2EET_St14__invoke_otherOT0_DpOT1_:
.LFB3836:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIR7VisitorEOT_RNSt16remove_referenceIS2_E4typeE
	movq	%rax, %rbx
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIR2O2EOT_RNSt16remove_referenceIS2_E4typeE
	movq	%rax, %rsi
	movq	%rbx, %rdi
	call	_ZNK7VisitorclERK2O2
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3836:
	.size	_ZSt13__invoke_implIdR7VisitorJR2O2EET_St14__invoke_otherOT0_DpOT1_, .-_ZSt13__invoke_implIdR7VisitorJR2O2EET_St14__invoke_otherOT0_DpOT1_
	.section	.text._ZSt7forwardIR2O4EOT_RNSt16remove_referenceIS2_E4typeE,"axG",@progbits,_ZSt7forwardIR2O4EOT_RNSt16remove_referenceIS2_E4typeE,comdat
	.weak	_ZSt7forwardIR2O4EOT_RNSt16remove_referenceIS2_E4typeE
	.type	_ZSt7forwardIR2O4EOT_RNSt16remove_referenceIS2_E4typeE, @function
_ZSt7forwardIR2O4EOT_RNSt16remove_referenceIS2_E4typeE:
.LFB3837:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3837:
	.size	_ZSt7forwardIR2O4EOT_RNSt16remove_referenceIS2_E4typeE, .-_ZSt7forwardIR2O4EOT_RNSt16remove_referenceIS2_E4typeE
	.section	.text._ZSt13__invoke_implIdR7VisitorJR2O4EET_St14__invoke_otherOT0_DpOT1_,"axG",@progbits,_ZSt13__invoke_implIdR7VisitorJR2O4EET_St14__invoke_otherOT0_DpOT1_,comdat
	.weak	_ZSt13__invoke_implIdR7VisitorJR2O4EET_St14__invoke_otherOT0_DpOT1_
	.type	_ZSt13__invoke_implIdR7VisitorJR2O4EET_St14__invoke_otherOT0_DpOT1_, @function
_ZSt13__invoke_implIdR7VisitorJR2O4EET_St14__invoke_otherOT0_DpOT1_:
.LFB3838:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIR7VisitorEOT_RNSt16remove_referenceIS2_E4typeE
	movq	%rax, %rbx
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIR2O4EOT_RNSt16remove_referenceIS2_E4typeE
	movq	%rax, %rsi
	movq	%rbx, %rdi
	call	_ZNK7VisitorclERK2O4
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3838:
	.size	_ZSt13__invoke_implIdR7VisitorJR2O4EET_St14__invoke_otherOT0_DpOT1_, .-_ZSt13__invoke_implIdR7VisitorJR2O4EET_St14__invoke_otherOT0_DpOT1_
	.section	.rodata
	.type	_ZNSt8__detail30__integer_to_chars_is_unsignedIjEE, @object
	.size	_ZNSt8__detail30__integer_to_chars_is_unsignedIjEE, 1
_ZNSt8__detail30__integer_to_chars_is_unsignedIjEE:
	.byte	1
	.type	_ZNSt8__detail30__integer_to_chars_is_unsignedImEE, @object
	.size	_ZNSt8__detail30__integer_to_chars_is_unsignedImEE, 1
_ZNSt8__detail30__integer_to_chars_is_unsignedImEE:
	.byte	1
	.type	_ZNSt8__detail30__integer_to_chars_is_unsignedIyEE, @object
	.size	_ZNSt8__detail30__integer_to_chars_is_unsignedIyEE, 1
_ZNSt8__detail30__integer_to_chars_is_unsignedIyEE:
	.byte	1
	.align 8
.LC0:
	.long	0
	.long	-1075838976
	.align 8
.LC2:
	.long	0
	.long	1071644672
	.align 8
.LC3:
	.long	1431655765
	.long	1068848469
	.align 8
.LC4:
	.long	1431655765
	.long	-1075489451
	.align 8
.LC5:
	.long	1431655765
	.long	1071994197
	.align 8
.LC6:
	.long	1431655765
	.long	-1078635179
	.align 8
.LC7:
	.long	0
	.long	1072693248
	.align 8
.LC8:
	.long	-1717986918
	.long	1069128089
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
