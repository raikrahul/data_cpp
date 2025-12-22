	.file	"72_vptr_vtable_task2.cpp"
	.text
#APP
	.globl _ZSt21ios_base_library_initv
#NO_APP
	.section	.text._ZN17AnimalBaseVirtualC2Eii,"axG",@progbits,_ZN17AnimalBaseVirtualC5Eii,comdat
	.align 2
	.weak	_ZN17AnimalBaseVirtualC2Eii
	.type	_ZN17AnimalBaseVirtualC2Eii, @function
_ZN17AnimalBaseVirtualC2Eii:
.LFB2358:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	%edx, -16(%rbp)
	leaq	16+_ZTV17AnimalBaseVirtual(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movl	-12(%rbp), %edx
	movl	%edx, 8(%rax)
	movq	-8(%rbp), %rax
	movl	-16(%rbp), %edx
	movl	%edx, 12(%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2358:
	.size	_ZN17AnimalBaseVirtualC2Eii, .-_ZN17AnimalBaseVirtualC2Eii
	.weak	_ZN17AnimalBaseVirtualC1Eii
	.set	_ZN17AnimalBaseVirtualC1Eii,_ZN17AnimalBaseVirtualC2Eii
	.section	.rodata
.LC0:
	.string	"nonVirt: weight="
.LC1:
	.string	", x="
.LC2:
	.string	"\n"
	.section	.text._ZN17AnimalBaseVirtual7nonVirtEi,"axG",@progbits,_ZN17AnimalBaseVirtual7nonVirtEi,comdat
	.align 2
	.weak	_ZN17AnimalBaseVirtual7nonVirtEi
	.type	_ZN17AnimalBaseVirtual7nonVirtEi, @function
_ZN17AnimalBaseVirtual7nonVirtEi:
.LFB2360:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	_ZSt4cout(%rip), %rax
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movl	8(%rax), %eax
	movl	%eax, %esi
	movq	%rdx, %rdi
	call	_ZNSolsEi@PLT
	movq	%rax, %rdx
	leaq	.LC1(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	movq	%rdx, %rdi
	call	_ZNSolsEi@PLT
	movq	%rax, %rdx
	leaq	.LC2(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2360:
	.size	_ZN17AnimalBaseVirtual7nonVirtEi, .-_ZN17AnimalBaseVirtual7nonVirtEi
	.section	.rodata
	.align 8
.LC3:
	.string	"AnimalBaseVirtual::speak: weight="
.LC4:
	.string	", volume="
	.section	.text._ZN17AnimalBaseVirtual5speakEi,"axG",@progbits,_ZN17AnimalBaseVirtual5speakEi,comdat
	.align 2
	.weak	_ZN17AnimalBaseVirtual5speakEi
	.type	_ZN17AnimalBaseVirtual5speakEi, @function
_ZN17AnimalBaseVirtual5speakEi:
.LFB2361:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	leaq	.LC3(%rip), %rax
	movq	%rax, %rsi
	leaq	_ZSt4cout(%rip), %rax
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movl	8(%rax), %eax
	movl	%eax, %esi
	movq	%rdx, %rdi
	call	_ZNSolsEi@PLT
	movq	%rax, %rdx
	leaq	.LC4(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	movq	%rdx, %rdi
	call	_ZNSolsEi@PLT
	movq	%rax, %rdx
	leaq	.LC2(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2361:
	.size	_ZN17AnimalBaseVirtual5speakEi, .-_ZN17AnimalBaseVirtual5speakEi
	.section	.text._ZN17AnimalBaseVirtualD2Ev,"axG",@progbits,_ZN17AnimalBaseVirtualD5Ev,comdat
	.align 2
	.weak	_ZN17AnimalBaseVirtualD2Ev
	.type	_ZN17AnimalBaseVirtualD2Ev, @function
_ZN17AnimalBaseVirtualD2Ev:
.LFB2364:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTV17AnimalBaseVirtual(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2364:
	.size	_ZN17AnimalBaseVirtualD2Ev, .-_ZN17AnimalBaseVirtualD2Ev
	.weak	_ZN17AnimalBaseVirtualD1Ev
	.set	_ZN17AnimalBaseVirtualD1Ev,_ZN17AnimalBaseVirtualD2Ev
	.section	.text._ZN17AnimalBaseVirtualD0Ev,"axG",@progbits,_ZN17AnimalBaseVirtualD5Ev,comdat
	.align 2
	.weak	_ZN17AnimalBaseVirtualD0Ev
	.type	_ZN17AnimalBaseVirtualD0Ev, @function
_ZN17AnimalBaseVirtualD0Ev:
.LFB2366:
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
	call	_ZN17AnimalBaseVirtualD1Ev
	movq	-8(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2366:
	.size	_ZN17AnimalBaseVirtualD0Ev, .-_ZN17AnimalBaseVirtualD0Ev
	.section	.rodata
.LC5:
	.string	"sizeof(AnimalBaseVirtual) = "
.LC6:
	.string	"&obj = "
.LC7:
	.string	"&obj.weight = "
.LC8:
	.string	"&obj.age = "
	.text
	.globl	main
	.type	main, @function
main:
.LFB2362:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2362
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
	leaq	.LC5(%rip), %rax
	movq	%rax, %rsi
	leaq	_ZSt4cout(%rip), %rax
	movq	%rax, %rdi
.LEHB0:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movl	$16, %esi
	movq	%rax, %rdi
	call	_ZNSolsEm@PLT
	movq	%rax, %rdx
	leaq	.LC2(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
.LEHE0:
	leaq	-48(%rbp), %rax
	movl	$5, %edx
	movl	$100, %esi
	movq	%rax, %rdi
	call	_ZN17AnimalBaseVirtualC1Eii
	leaq	-48(%rbp), %rax
	movl	$42, %esi
	movq	%rax, %rdi
.LEHB1:
	call	_ZN17AnimalBaseVirtual7nonVirtEi
	leaq	-48(%rbp), %rax
	movl	$77, %esi
	movq	%rax, %rdi
	call	_ZN17AnimalBaseVirtual5speakEi
	leaq	.LC6(%rip), %rax
	movq	%rax, %rsi
	leaq	_ZSt4cout(%rip), %rax
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	leaq	-48(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEPKv@PLT
	movq	%rax, %rdx
	leaq	.LC2(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	leaq	.LC7(%rip), %rax
	movq	%rax, %rsi
	leaq	_ZSt4cout(%rip), %rax
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	leaq	-48(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEPKv@PLT
	movq	%rax, %rdx
	leaq	.LC2(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	leaq	.LC8(%rip), %rax
	movq	%rax, %rsi
	leaq	_ZSt4cout(%rip), %rax
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	leaq	-48(%rbp), %rax
	addq	$12, %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEPKv@PLT
	movq	%rax, %rdx
	leaq	.LC2(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
.LEHE1:
	movl	$0, %ebx
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN17AnimalBaseVirtualD1Ev
	movl	%ebx, %eax
	movq	-24(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L10
	jmp	.L12
.L11:
	endbr64
	movq	%rax, %rbx
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN17AnimalBaseVirtualD1Ev
	movq	%rbx, %rax
	movq	-24(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L9
	call	__stack_chk_fail@PLT
.L9:
	movq	%rax, %rdi
.LEHB2:
	call	_Unwind_Resume@PLT
.LEHE2:
.L12:
	call	__stack_chk_fail@PLT
.L10:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2362:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA2362:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2362-.LLSDACSB2362
.LLSDACSB2362:
	.uleb128 .LEHB0-.LFB2362
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB2362
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L11-.LFB2362
	.uleb128 0
	.uleb128 .LEHB2-.LFB2362
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSE2362:
	.text
	.size	main, .-main
	.weak	_ZTV17AnimalBaseVirtual
	.section	.data.rel.ro.local._ZTV17AnimalBaseVirtual,"awG",@progbits,_ZTV17AnimalBaseVirtual,comdat
	.align 8
	.type	_ZTV17AnimalBaseVirtual, @object
	.size	_ZTV17AnimalBaseVirtual, 40
_ZTV17AnimalBaseVirtual:
	.quad	0
	.quad	_ZTI17AnimalBaseVirtual
	.quad	_ZN17AnimalBaseVirtual5speakEi
	.quad	_ZN17AnimalBaseVirtualD1Ev
	.quad	_ZN17AnimalBaseVirtualD0Ev
	.weak	_ZTI17AnimalBaseVirtual
	.section	.data.rel.ro._ZTI17AnimalBaseVirtual,"awG",@progbits,_ZTI17AnimalBaseVirtual,comdat
	.align 8
	.type	_ZTI17AnimalBaseVirtual, @object
	.size	_ZTI17AnimalBaseVirtual, 16
_ZTI17AnimalBaseVirtual:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTS17AnimalBaseVirtual
	.weak	_ZTS17AnimalBaseVirtual
	.section	.rodata._ZTS17AnimalBaseVirtual,"aG",@progbits,_ZTS17AnimalBaseVirtual,comdat
	.align 16
	.type	_ZTS17AnimalBaseVirtual, @object
	.size	_ZTS17AnimalBaseVirtual, 20
_ZTS17AnimalBaseVirtual:
	.string	"17AnimalBaseVirtual"
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
