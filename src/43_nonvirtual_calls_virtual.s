	.file	"43_nonvirtual_calls_virtual.cpp"
	.text
	.section	.rodata
.LC0:
	.string	"Base::bar"
	.section	.text._ZN4Base3barEv,"axG",@progbits,_ZN4Base3barEv,comdat
	.align 2
	.weak	_ZN4Base3barEv
	.type	_ZN4Base3barEv, @function
_ZN4Base3barEv:
.LFB2:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	_ZN4Base3barEv, .-_ZN4Base3barEv
	.section	.rodata
.LC1:
	.string	"D::foo calling bar()..."
	.section	.text._ZN1D3fooEv,"axG",@progbits,_ZN1D3fooEv,comdat
	.align 2
	.weak	_ZN1D3fooEv
	.type	_ZN1D3fooEv, @function
_ZN1D3fooEv:
.LFB3:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	*%rdx
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	_ZN1D3fooEv, .-_ZN1D3fooEv
	.section	.rodata
.LC2:
	.string	"D::bar"
	.section	.text._ZN1D3barEv,"axG",@progbits,_ZN1D3barEv,comdat
	.align 2
	.weak	_ZN1D3barEv
	.type	_ZN1D3barEv, @function
_ZN1D3barEv:
.LFB4:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	_ZN1D3barEv, .-_ZN1D3barEv
	.section	.rodata
.LC3:
	.string	"[%s] vptr = %p\n"
	.text
	.globl	_Z9dump_vptrPKvPKc
	.type	_Z9dump_vptrPKvPKc, @function
_Z9dump_vptrPKvPKc:
.LFB5:
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
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	_Z9dump_vptrPKvPKc, .-_Z9dump_vptrPKvPKc
	.section	.text._ZN4BaseD2Ev,"axG",@progbits,_ZN4BaseD5Ev,comdat
	.align 2
	.weak	_ZN4BaseD2Ev
	.type	_ZN4BaseD2Ev, @function
_ZN4BaseD2Ev:
.LFB12:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTV4Base(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	_ZN4BaseD2Ev, .-_ZN4BaseD2Ev
	.weak	_ZN4BaseD1Ev
	.set	_ZN4BaseD1Ev,_ZN4BaseD2Ev
	.section	.text._ZN4BaseD0Ev,"axG",@progbits,_ZN4BaseD5Ev,comdat
	.align 2
	.weak	_ZN4BaseD0Ev
	.type	_ZN4BaseD0Ev, @function
_ZN4BaseD0Ev:
.LFB14:
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
	call	_ZN4BaseD1Ev
	movq	-8(%rbp), %rax
	movl	$8, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	_ZN4BaseD0Ev, .-_ZN4BaseD0Ev
	.section	.text._ZN1DD2Ev,"axG",@progbits,_ZN1DD5Ev,comdat
	.align 2
	.weak	_ZN1DD2Ev
	.type	_ZN1DD2Ev, @function
_ZN1DD2Ev:
.LFB18:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTV1D(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN4BaseD2Ev
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	_ZN1DD2Ev, .-_ZN1DD2Ev
	.weak	_ZN1DD1Ev
	.set	_ZN1DD1Ev,_ZN1DD2Ev
	.section	.text._ZN1DD0Ev,"axG",@progbits,_ZN1DD5Ev,comdat
	.align 2
	.weak	_ZN1DD0Ev
	.type	_ZN1DD0Ev, @function
_ZN1DD0Ev:
.LFB20:
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
	call	_ZN1DD1Ev
	movq	-8(%rbp), %rax
	movl	$8, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE20:
	.size	_ZN1DD0Ev, .-_ZN1DD0Ev
	.section	.rodata
.LC4:
	.string	"=== Object layout ==="
.LC5:
	.string	"&d = %p\n"
.LC6:
	.string	"D"
.LC7:
	.string	"sizeof(D) = %zu\n\n"
	.align 8
.LC8:
	.string	"=== D* pd = &d; pd->foo(); ==="
	.align 8
.LC9:
	.string	"=== Base* pb = &d; pb->bar(); ==="
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	16+_ZTV1D(%rip), %rax
	movq	%rax, -48(%rbp)
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	-48(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-48(%rbp), %rax
	leaq	.LC6(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_Z9dump_vptrPKvPKc
	movl	$8, %esi
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	-48(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1D3fooEv
	movl	$10, %edi
	call	putchar@PLT
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	-48(%rbp), %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	*%rdx
	movl	$0, %ebx
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN1DD1Ev
	movl	%ebx, %eax
	movq	-24(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L11
	call	__stack_chk_fail@PLT
.L11:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.weak	_ZTV1D
	.section	.data.rel.ro.local._ZTV1D,"awG",@progbits,_ZTV1D,comdat
	.align 8
	.type	_ZTV1D, @object
	.size	_ZTV1D, 40
_ZTV1D:
	.quad	0
	.quad	_ZTI1D
	.quad	_ZN1D3barEv
	.quad	_ZN1DD1Ev
	.quad	_ZN1DD0Ev
	.weak	_ZTV4Base
	.section	.data.rel.ro.local._ZTV4Base,"awG",@progbits,_ZTV4Base,comdat
	.align 8
	.type	_ZTV4Base, @object
	.size	_ZTV4Base, 40
_ZTV4Base:
	.quad	0
	.quad	_ZTI4Base
	.quad	_ZN4Base3barEv
	.quad	_ZN4BaseD1Ev
	.quad	_ZN4BaseD0Ev
	.weak	_ZTI1D
	.section	.data.rel.ro._ZTI1D,"awG",@progbits,_ZTI1D,comdat
	.align 8
	.type	_ZTI1D, @object
	.size	_ZTI1D, 24
_ZTI1D:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTS1D
	.quad	_ZTI4Base
	.weak	_ZTS1D
	.section	.rodata._ZTS1D,"aG",@progbits,_ZTS1D,comdat
	.type	_ZTS1D, @object
	.size	_ZTS1D, 3
_ZTS1D:
	.string	"1D"
	.weak	_ZTI4Base
	.section	.data.rel.ro._ZTI4Base,"awG",@progbits,_ZTI4Base,comdat
	.align 8
	.type	_ZTI4Base, @object
	.size	_ZTI4Base, 16
_ZTI4Base:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTS4Base
	.weak	_ZTS4Base
	.section	.rodata._ZTS4Base,"aG",@progbits,_ZTS4Base,comdat
	.type	_ZTS4Base, @object
	.size	_ZTS4Base, 6
_ZTS4Base:
	.string	"4Base"
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
