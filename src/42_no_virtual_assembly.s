	.file	"42_no_virtual_assembly.cpp"
	.intel_syntax noprefix
	.text
	.section	.rodata
.LC0:
	.string	"Base::someFun x=%d y=%d\n"
	.section	.text._ZN4Base7someFunEv,"axG",@progbits,_ZN4Base7someFunEv,comdat
	.align 2
	.weak	_ZN4Base7someFunEv
	.type	_ZN4Base7someFunEv, @function
_ZN4Base7someFunEv:
.LFB2:
	.cfi_startproc
	endbr64
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR -8[rbp], rdi
	mov	rax, QWORD PTR -8[rbp]
	mov	edx, DWORD PTR 4[rax]
	mov	rax, QWORD PTR -8[rbp]
	mov	eax, DWORD PTR [rax]
	mov	esi, eax
	lea	rax, .LC0[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	_ZN4Base7someFunEv, .-_ZN4Base7someFunEv
	.section	.rodata
	.align 8
.LC1:
	.string	"Derived::someFun x=%d y=%d z=%d\n"
	.section	.text._ZN7Derived7someFunEv,"axG",@progbits,_ZN7Derived7someFunEv,comdat
	.align 2
	.weak	_ZN7Derived7someFunEv
	.type	_ZN7Derived7someFunEv, @function
_ZN7Derived7someFunEv:
.LFB3:
	.cfi_startproc
	endbr64
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	QWORD PTR -8[rbp], rdi
	mov	rax, QWORD PTR -8[rbp]
	mov	ecx, DWORD PTR 8[rax]
	mov	rax, QWORD PTR -8[rbp]
	mov	edx, DWORD PTR 4[rax]
	mov	rax, QWORD PTR -8[rbp]
	mov	eax, DWORD PTR [rax]
	mov	esi, eax
	lea	rax, .LC1[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	_ZN7Derived7someFunEv, .-_ZN7Derived7someFunEv
	.text
	.globl	main
	.type	main, @function
main:
.LFB4:
	.cfi_startproc
	endbr64
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 64
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax
	xor	eax, eax
	mov	DWORD PTR -28[rbp], 10
	mov	DWORD PTR -24[rbp], 20
	lea	rax, -28[rbp]
	mov	rdi, rax
	call	_ZN4Base7someFunEv
	lea	rax, -28[rbp]
	mov	QWORD PTR -56[rbp], rax
	mov	rax, QWORD PTR -56[rbp]
	mov	rdi, rax
	call	_ZN4Base7someFunEv
	mov	DWORD PTR -20[rbp], 100
	mov	DWORD PTR -16[rbp], 200
	mov	DWORD PTR -12[rbp], 300
	lea	rax, -20[rbp]
	mov	QWORD PTR -48[rbp], rax
	mov	rax, QWORD PTR -48[rbp]
	mov	rdi, rax
	call	_ZN4Base7someFunEv
	lea	rax, -20[rbp]
	mov	QWORD PTR -40[rbp], rax
	mov	rax, QWORD PTR -40[rbp]
	mov	rdi, rax
	call	_ZN7Derived7someFunEv
	mov	eax, 0
	mov	rdx, QWORD PTR -8[rbp]
	sub	rdx, QWORD PTR fs:40
	je	.L5
	call	__stack_chk_fail@PLT
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
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
