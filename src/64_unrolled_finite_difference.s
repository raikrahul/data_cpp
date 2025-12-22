	.file	"64_unrolled_finite_difference.cpp"
	.text
#APP
	.globl _ZSt21ios_base_library_initv
#NO_APP
	.p2align 4
	.type	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0, @function
_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0:
.LFB5676:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	(%rdi), %rax
	movq	-24(%rax), %rax
	movq	240(%rdi,%rax), %rbp
	testq	%rbp, %rbp
	je	.L7
	cmpb	$0, 56(%rbp)
	movq	%rdi, %rbx
	je	.L3
	movsbl	67(%rbp), %esi
.L4:
	movq	%rbx, %rdi
	call	_ZNSo3putEc@PLT
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	movq	%rax, %rdi
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZNSo5flushEv@PLT
.L3:
	.cfi_restore_state
	movq	%rbp, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	0(%rbp), %rax
	movl	$10, %esi
	movq	%rbp, %rdi
	call	*48(%rax)
	movsbl	%al, %esi
	jmp	.L4
.L7:
	call	_ZSt16__throw_bad_castv@PLT
	.cfi_endproc
.LFE5676:
	.size	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0, .-_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	.p2align 4
	.globl	_Z15stencil_runtimeRKSt6vectorIdSaIdEEiRKS_IiSaIiEES3_
	.type	_Z15stencil_runtimeRKSt6vectorIdSaIdEEiRKS_IiSaIiEES3_, @function
_Z15stencil_runtimeRKSt6vectorIdSaIdEEiRKS_IiSaIiEES3_:
.LFB4644:
	.cfi_startproc
	endbr64
	movq	8(%rdx), %rax
	movl	%esi, %r8d
	movq	(%rdx), %rsi
	movq	%rax, %r9
	subq	%rsi, %r9
	sarq	$2, %r9
	cmpq	%rsi, %rax
	je	.L11
	movq	(%rdi), %rdi
	movq	(%rcx), %rcx
	xorl	%eax, %eax
	pxor	%xmm1, %xmm1
	.p2align 4,,10
	.p2align 3
.L10:
	movl	(%rsi,%rax,4), %edx
	addl	%r8d, %edx
	movslq	%edx, %rdx
	movsd	(%rdi,%rdx,8), %xmm0
	mulsd	(%rcx,%rax,8), %xmm0
	addq	$1, %rax
	addsd	%xmm0, %xmm1
	cmpq	%r9, %rax
	jb	.L10
	movapd	%xmm1, %xmm0
	ret
	.p2align 4,,10
	.p2align 3
.L11:
	pxor	%xmm1, %xmm1
	movapd	%xmm1, %xmm0
	ret
	.cfi_endproc
.LFE4644:
	.size	_Z15stencil_runtimeRKSt6vectorIdSaIdEEiRKS_IiSaIiEES3_, .-_Z15stencil_runtimeRKSt6vectorIdSaIdEEiRKS_IiSaIiEES3_
	.section	.text._ZNSt6vectorIdSaIdEED2Ev,"axG",@progbits,_ZNSt6vectorIdSaIdEED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorIdSaIdEED2Ev
	.type	_ZNSt6vectorIdSaIdEED2Ev, @function
_ZNSt6vectorIdSaIdEED2Ev:
.LFB5134:
	.cfi_startproc
	endbr64
	movq	(%rdi), %rax
	testq	%rax, %rax
	je	.L13
	movq	16(%rdi), %rsi
	movq	%rax, %rdi
	subq	%rax, %rsi
	jmp	_ZdlPvm@PLT
	.p2align 4,,10
	.p2align 3
.L13:
	ret
	.cfi_endproc
.LFE5134:
	.size	_ZNSt6vectorIdSaIdEED2Ev, .-_ZNSt6vectorIdSaIdEED2Ev
	.weak	_ZNSt6vectorIdSaIdEED1Ev
	.set	_ZNSt6vectorIdSaIdEED1Ev,_ZNSt6vectorIdSaIdEED2Ev
	.section	.text._ZNSt6vectorIiSaIiEED2Ev,"axG",@progbits,_ZNSt6vectorIiSaIiEED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorIiSaIiEED2Ev
	.type	_ZNSt6vectorIiSaIiEED2Ev, @function
_ZNSt6vectorIiSaIiEED2Ev:
.LFB5143:
	.cfi_startproc
	endbr64
	movq	(%rdi), %rax
	testq	%rax, %rax
	je	.L15
	movq	16(%rdi), %rsi
	movq	%rax, %rdi
	subq	%rax, %rsi
	jmp	_ZdlPvm@PLT
	.p2align 4,,10
	.p2align 3
.L15:
	ret
	.cfi_endproc
.LFE5143:
	.size	_ZNSt6vectorIiSaIiEED2Ev, .-_ZNSt6vectorIiSaIiEED2Ev
	.weak	_ZNSt6vectorIiSaIiEED1Ev
	.set	_ZNSt6vectorIiSaIiEED1Ev,_ZNSt6vectorIiSaIiEED2Ev
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"vector::_M_realloc_insert"
.LC6:
	.string	"Runtime Loop Result: "
.LC7:
	.string	" (Expected 2.0)"
.LC8:
	.string	"Unrolled Result:     "
	.section	.text.unlikely,"ax",@progbits
.LCOLDB11:
	.section	.text.startup,"ax",@progbits
.LHOTB11:
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB4650:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA4650
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pxor	%xmm0, %xmm0
	xorl	%r15d, %r15d
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	xorl	%ebp, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	xorl	%ebx, %ebx
	subq	$152, %rsp
	.cfi_def_cfa_offset 208
	movq	%fs:40, %rax
	movq	%rax, 136(%rsp)
	xorl	%eax, %eax
	movaps	%xmm0, 16(%rsp)
	movq	$0, 32(%rsp)
	jmp	.L30
	.p2align 4,,10
	.p2align 3
.L49:
	movsd	%xmm2, (%r15)
	addl	$1, %ebx
	addq	$8, %r15
	movq	%r15, 24(%rsp)
	cmpl	$10, %ebx
	je	.L48
.L30:
	movl	%ebx, %eax
	pxor	%xmm2, %xmm2
	imull	%ebx, %eax
	cvtsi2sdl	%eax, %xmm2
	movsd	%xmm2, 8(%rsp)
	cmpq	%rbp, %r15
	jne	.L49
	movabsq	$1152921504606846975, %rcx
	movq	16(%rsp), %r13
	subq	%r13, %r15
	movq	%r15, %rax
	movq	%r15, %r12
	sarq	$3, %rax
	cmpq	%rcx, %rax
	je	.L50
	cmpq	%rbp, %r13
	je	.L51
	leaq	(%rax,%rax), %rdx
	cmpq	%rax, %rdx
	jb	.L37
	testq	%rdx, %rdx
	jne	.L52
	xorl	%r14d, %r14d
	xorl	%ecx, %ecx
.L26:
	movsd	8(%rsp), %xmm3
	leaq	8(%rcx,%r12), %r15
	movsd	%xmm3, (%rcx,%r12)
	testq	%r12, %r12
	jg	.L53
	testq	%r13, %r13
	jne	.L28
.L29:
	addl	$1, %ebx
	movq	%rcx, 16(%rsp)
	movq	%r14, %rbp
	movq	%r15, 24(%rsp)
	movq	%r14, 32(%rsp)
	cmpl	$10, %ebx
	jne	.L30
	.p2align 4,,10
	.p2align 3
.L48:
	movq	.LC2(%rip), %rax
	pxor	%xmm0, %xmm0
	movl	$12, %edi
	movl	$1, 120(%rsp)
	movups	%xmm0, 56(%rsp)
	movq	%rax, 112(%rsp)
.LEHB0:
	call	_Znwm@PLT
.LEHE0:
	movq	112(%rsp), %rdx
	movq	%rax, %rbx
	movq	%rax, 48(%rsp)
	leaq	12(%rax), %rax
	movapd	.LC3(%rip), %xmm0
	movq	%rax, 64(%rsp)
	movl	$24, %edi
	movq	%rdx, (%rbx)
	movl	120(%rsp), %edx
	movq	%rax, 56(%rsp)
	movq	.LC4(%rip), %rax
	movl	%edx, 8(%rbx)
	movaps	%xmm0, 112(%rsp)
	pxor	%xmm0, %xmm0
	movq	%rax, 128(%rsp)
	movups	%xmm0, 88(%rsp)
.LEHB1:
	call	_Znwm@PLT
.LEHE1:
	movq	%rax, %rbp
	movq	%rax, 80(%rsp)
	leaq	24(%rax), %rax
	movq	16(%rsp), %r14
	movq	%rax, 96(%rsp)
	pxor	%xmm1, %xmm1
	movsd	.LC5(%rip), %xmm0
	leaq	_ZSt4cout(%rip), %r12
	movq	%rax, 88(%rsp)
	movl	(%rbx), %eax
	leaq	.LC6(%rip), %rsi
	movq	%r12, %rdi
	movq	128(%rsp), %rdx
	movdqa	112(%rsp), %xmm4
	addl	$2, %eax
	cltq
	movq	%rdx, 16(%rbp)
	movl	$21, %edx
	addsd	(%r14,%rax,8), %xmm1
	movl	4(%rbx), %eax
	movups	%xmm4, 0(%rbp)
	addl	$2, %eax
	cltq
	mulsd	(%r14,%rax,8), %xmm0
	movl	8(%rbx), %eax
	addl	$2, %eax
	cltq
	addsd	%xmm1, %xmm0
	addsd	(%r14,%rax,8), %xmm0
	movq	%xmm0, %r13
.LEHB2:
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%r13, %xmm0
	movq	%r12, %rdi
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	leaq	.LC7(%rip), %r13
	movl	$15, %edx
	movq	%rax, %rdi
	movq	%rax, %r15
	movq	%r13, %rsi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%r15, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
	movl	8(%rbx), %eax
	pxor	%xmm1, %xmm1
	movl	$21, %edx
	movq	%r12, %rdi
	leaq	.LC8(%rip), %rsi
	addl	$2, %eax
	cltq
	movsd	(%r14,%rax,8), %xmm0
	mulsd	16(%rbp), %xmm0
	movl	4(%rbx), %eax
	addl	$2, %eax
	cltq
	addsd	%xmm1, %xmm0
	movsd	(%r14,%rax,8), %xmm1
	mulsd	8(%rbp), %xmm1
	movl	(%rbx), %eax
	addl	$2, %eax
	cltq
	addsd	%xmm1, %xmm0
	movsd	(%r14,%rax,8), %xmm1
	mulsd	0(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movq	%xmm0, %rbx
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%rbx, %xmm0
	movq	%r12, %rdi
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$15, %edx
	movq	%r13, %rsi
	movq	%rax, %rdi
	movq	%rax, %rbx
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%rbx, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.isra.0
.LEHE2:
	leaq	80(%rsp), %rdi
	call	_ZNSt6vectorIdSaIdEED1Ev
	leaq	48(%rsp), %rdi
	call	_ZNSt6vectorIiSaIiEED1Ev
	leaq	16(%rsp), %rdi
	call	_ZNSt6vectorIdSaIdEED1Ev
	movq	136(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L46
	addq	$152, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L53:
	.cfi_restore_state
	movq	%rcx, %rdi
	movq	%r12, %rdx
	movq	%r13, %rsi
	call	memmove@PLT
	movq	%rax, %rcx
.L28:
	movq	%rbp, %rsi
	movq	%r13, %rdi
	movq	%rcx, 8(%rsp)
	subq	%r13, %rsi
	call	_ZdlPvm@PLT
	movq	8(%rsp), %rcx
	jmp	.L29
.L51:
	movabsq	$1152921504606846975, %rdx
	addq	$1, %rax
	jc	.L25
	cmpq	%rdx, %rax
	cmovbe	%rax, %rdx
.L25:
	leaq	0(,%rdx,8), %r14
	movq	%r14, %rdi
.LEHB3:
	call	_Znwm@PLT
	movq	%rax, %rcx
	addq	%rax, %r14
	jmp	.L26
.L37:
	movabsq	$1152921504606846975, %rdx
	jmp	.L25
.L52:
	movabsq	$1152921504606846975, %rax
	cmpq	%rax, %rdx
	cmova	%rax, %rdx
	jmp	.L25
.L50:
	movq	136(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L46
	leaq	.LC1(%rip), %rdi
	call	_ZSt20__throw_length_errorPKc@PLT
.LEHE3:
.L46:
	call	__stack_chk_fail@PLT
.L39:
	endbr64
	movq	%rax, %rbx
	jmp	.L33
.L41:
	endbr64
	movq	%rax, %rbx
	jmp	.L31
.L40:
	endbr64
	movq	%rax, %rbx
	jmp	.L32
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA4650:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4650-.LLSDACSB4650
.LLSDACSB4650:
	.uleb128 .LEHB0-.LFB4650
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L39-.LFB4650
	.uleb128 0
	.uleb128 .LEHB1-.LFB4650
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L40-.LFB4650
	.uleb128 0
	.uleb128 .LEHB2-.LFB4650
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L41-.LFB4650
	.uleb128 0
	.uleb128 .LEHB3-.LFB4650
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L39-.LFB4650
	.uleb128 0
.LLSDACSE4650:
	.section	.text.startup
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC4650
	.type	main.cold, @function
main.cold:
.LFSB4650:
.L31:
	.cfi_def_cfa_offset 208
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	leaq	80(%rsp), %rdi
	call	_ZNSt6vectorIdSaIdEED1Ev
.L32:
	leaq	48(%rsp), %rdi
	call	_ZNSt6vectorIiSaIiEED1Ev
.L33:
	leaq	16(%rsp), %rdi
	call	_ZNSt6vectorIdSaIdEED1Ev
	movq	136(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L54
	movq	%rbx, %rdi
.LEHB4:
	call	_Unwind_Resume@PLT
.LEHE4:
.L54:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE4650:
	.section	.gcc_except_table
.LLSDAC4650:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC4650-.LLSDACSBC4650
.LLSDACSBC4650:
	.uleb128 .LEHB4-.LCOLDB11
	.uleb128 .LEHE4-.LEHB4
	.uleb128 0
	.uleb128 0
.LLSDACSEC4650:
	.section	.text.unlikely
	.section	.text.startup
	.size	main, .-main
	.section	.text.unlikely
	.size	main.cold, .-main.cold
.LCOLDE11:
	.section	.text.startup
.LHOTE11:
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC2:
	.long	-1
	.long	0
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC3:
	.long	0
	.long	1072693248
	.long	0
	.long	-1073741824
	.set	.LC4,.LC3
	.set	.LC5,.LC3+8
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
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
