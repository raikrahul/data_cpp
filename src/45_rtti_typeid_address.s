	.file	"45_rtti_typeid_address.cpp"
# GNU C++20 (Ubuntu 13.3.0-6ubuntu2~24.04) version 13.3.0 (x86_64-linux-gnu)
#	compiled by GNU C version 13.3.0, GMP version 6.3.0, MPFR version 4.2.1, MPC version 1.3.1, isl version isl-0.26-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -O0 -std=c++20 -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection
	.text
	.section	.text._ZSt23__is_constant_evaluatedv,"axG",@progbits,_ZSt23__is_constant_evaluatedv,comdat
	.weak	_ZSt23__is_constant_evaluatedv
	.type	_ZSt23__is_constant_evaluatedv, @function
_ZSt23__is_constant_evaluatedv:
.LFB1:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
# /usr/include/x86_64-linux-gnu/c++/13/bits/c++config.h:547:     return __builtin_is_constant_evaluated();
	movl	$0, %eax	#, _1
# /usr/include/x86_64-linux-gnu/c++/13/bits/c++config.h:551:   }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1:
	.size	_ZSt23__is_constant_evaluatedv, .-_ZSt23__is_constant_evaluatedv
	.section	.text._ZnwmPv,"axG",@progbits,_ZnwmPv,comdat
	.weak	_ZnwmPv
	.type	_ZnwmPv, @function
_ZnwmPv:
.LFB39:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# D.4018, D.4018
	movq	%rsi, -16(%rbp)	# __p, __p
# /usr/include/c++/13/new:175: { return __p; }
	movq	-16(%rbp), %rax	# __p, _2
# /usr/include/c++/13/new:175: { return __p; }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE39:
	.size	_ZnwmPv, .-_ZnwmPv
#APP
	.globl _ZSt21ios_base_library_initv
	.section	.rodata
.LC0:
	.string	"Circle (Address check: "
.LC1:
	.string	" == "
.LC2:
	.string	")\n"
.LC3:
	.string	"Rectangle (Address check: "
#NO_APP
	.text
	.align 2
	.globl	_ZNK6Circle6whoAmIEv
	.type	_ZNK6Circle6whoAmIEv, @function
_ZNK6Circle6whoAmIEv:
.LFB3628:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$48, %rsp	#,
	movq	%rdi, -40(%rbp)	# this, this
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:26:     const std::type_info& ti = typeid(*this);
	movq	-40(%rbp), %rax	# this, tmp91
	movq	(%rax), %rax	# this_12(D)->D.78928._vptr.Shape, _1
	movq	-8(%rax), %rax	# MEM[(int (*) () *)_1 + -8B], tmp92
	movq	%rax, -24(%rbp)	# tmp92, ti
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:27:     const std::type_info& ti_circle = typeid(Circle);
	leaq	_ZTI6Circle(%rip), %rax	#, tmp93
	movq	%rax, -16(%rbp)	# tmp93, ti_circle
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:28:     const std::type_info& ti_rect = typeid(Rectangle);
	leaq	_ZTI9Rectangle(%rip), %rax	#, tmp94
	movq	%rax, -8(%rbp)	# tmp94, ti_rect
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:30:     if (&ti == &ti_circle) {
	movq	-24(%rbp), %rax	# ti, tmp95
	cmpq	-16(%rbp), %rax	# ti_circle, tmp95
	jne	.L6	#,
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:31:         std::cout << "Circle (Address check: " << &ti << " == " << &ti_circle << ")\n";
	leaq	.LC0(%rip), %rax	#, tmp96
	movq	%rax, %rsi	# tmp96,
	leaq	_ZSt4cout(%rip), %rax	#, tmp97
	movq	%rax, %rdi	# tmp97,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
	movq	%rax, %rdx	#, _2
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:31:         std::cout << "Circle (Address check: " << &ti << " == " << &ti_circle << ")\n";
	movq	-24(%rbp), %rax	# ti, tmp98
	movq	%rax, %rsi	# tmp98,
	movq	%rdx, %rdi	# _2,
	call	_ZNSolsEPKv@PLT	#
	movq	%rax, %rdx	#, _3
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:31:         std::cout << "Circle (Address check: " << &ti << " == " << &ti_circle << ")\n";
	leaq	.LC1(%rip), %rax	#, tmp99
	movq	%rax, %rsi	# tmp99,
	movq	%rdx, %rdi	# _3,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
	movq	%rax, %rdx	#, _4
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:31:         std::cout << "Circle (Address check: " << &ti << " == " << &ti_circle << ")\n";
	movq	-16(%rbp), %rax	# ti_circle, tmp100
	movq	%rax, %rsi	# tmp100,
	movq	%rdx, %rdi	# _4,
	call	_ZNSolsEPKv@PLT	#
	movq	%rax, %rdx	#, _5
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:31:         std::cout << "Circle (Address check: " << &ti << " == " << &ti_circle << ")\n";
	leaq	.LC2(%rip), %rax	#, tmp101
	movq	%rax, %rsi	# tmp101,
	movq	%rdx, %rdi	# _5,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:35: }
	jmp	.L8	#
.L6:
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:32:     } else if (&ti == &ti_rect) {
	movq	-24(%rbp), %rax	# ti, tmp102
	cmpq	-8(%rbp), %rax	# ti_rect, tmp102
	jne	.L8	#,
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:33:         std::cout << "Rectangle (Address check: " << &ti << " == " << &ti_rect << ")\n";
	leaq	.LC3(%rip), %rax	#, tmp103
	movq	%rax, %rsi	# tmp103,
	leaq	_ZSt4cout(%rip), %rax	#, tmp104
	movq	%rax, %rdi	# tmp104,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
	movq	%rax, %rdx	#, _6
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:33:         std::cout << "Rectangle (Address check: " << &ti << " == " << &ti_rect << ")\n";
	movq	-24(%rbp), %rax	# ti, tmp105
	movq	%rax, %rsi	# tmp105,
	movq	%rdx, %rdi	# _6,
	call	_ZNSolsEPKv@PLT	#
	movq	%rax, %rdx	#, _7
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:33:         std::cout << "Rectangle (Address check: " << &ti << " == " << &ti_rect << ")\n";
	leaq	.LC1(%rip), %rax	#, tmp106
	movq	%rax, %rsi	# tmp106,
	movq	%rdx, %rdi	# _7,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
	movq	%rax, %rdx	#, _8
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:33:         std::cout << "Rectangle (Address check: " << &ti << " == " << &ti_rect << ")\n";
	movq	-8(%rbp), %rax	# ti_rect, tmp107
	movq	%rax, %rsi	# tmp107,
	movq	%rdx, %rdi	# _8,
	call	_ZNSolsEPKv@PLT	#
	movq	%rax, %rdx	#, _9
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:33:         std::cout << "Rectangle (Address check: " << &ti << " == " << &ti_rect << ")\n";
	leaq	.LC2(%rip), %rax	#, tmp108
	movq	%rax, %rsi	# tmp108,
	movq	%rdx, %rdi	# _9,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
.L8:
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:35: }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE3628:
	.size	_ZNK6Circle6whoAmIEv, .-_ZNK6Circle6whoAmIEv
	.align 2
	.globl	_ZNK9Rectangle6whoAmIEv
	.type	_ZNK9Rectangle6whoAmIEv, @function
_ZNK9Rectangle6whoAmIEv:
.LFB3629:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$48, %rsp	#,
	movq	%rdi, -40(%rbp)	# this, this
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:38:     const std::type_info& ti = typeid(*this);
	movq	-40(%rbp), %rax	# this, tmp91
	movq	(%rax), %rax	# this_12(D)->D.78950._vptr.Shape, _1
	movq	-8(%rax), %rax	# MEM[(int (*) () *)_1 + -8B], tmp92
	movq	%rax, -24(%rbp)	# tmp92, ti
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:39:     const std::type_info& ti_circle = typeid(Circle);
	leaq	_ZTI6Circle(%rip), %rax	#, tmp93
	movq	%rax, -16(%rbp)	# tmp93, ti_circle
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:40:     const std::type_info& ti_rect = typeid(Rectangle);
	leaq	_ZTI9Rectangle(%rip), %rax	#, tmp94
	movq	%rax, -8(%rbp)	# tmp94, ti_rect
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:42:     if (&ti == &ti_circle) {
	movq	-24(%rbp), %rax	# ti, tmp95
	cmpq	-16(%rbp), %rax	# ti_circle, tmp95
	jne	.L10	#,
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:43:         std::cout << "Circle (Address check: " << &ti << " == " << &ti_circle << ")\n";
	leaq	.LC0(%rip), %rax	#, tmp96
	movq	%rax, %rsi	# tmp96,
	leaq	_ZSt4cout(%rip), %rax	#, tmp97
	movq	%rax, %rdi	# tmp97,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
	movq	%rax, %rdx	#, _2
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:43:         std::cout << "Circle (Address check: " << &ti << " == " << &ti_circle << ")\n";
	movq	-24(%rbp), %rax	# ti, tmp98
	movq	%rax, %rsi	# tmp98,
	movq	%rdx, %rdi	# _2,
	call	_ZNSolsEPKv@PLT	#
	movq	%rax, %rdx	#, _3
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:43:         std::cout << "Circle (Address check: " << &ti << " == " << &ti_circle << ")\n";
	leaq	.LC1(%rip), %rax	#, tmp99
	movq	%rax, %rsi	# tmp99,
	movq	%rdx, %rdi	# _3,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
	movq	%rax, %rdx	#, _4
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:43:         std::cout << "Circle (Address check: " << &ti << " == " << &ti_circle << ")\n";
	movq	-16(%rbp), %rax	# ti_circle, tmp100
	movq	%rax, %rsi	# tmp100,
	movq	%rdx, %rdi	# _4,
	call	_ZNSolsEPKv@PLT	#
	movq	%rax, %rdx	#, _5
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:43:         std::cout << "Circle (Address check: " << &ti << " == " << &ti_circle << ")\n";
	leaq	.LC2(%rip), %rax	#, tmp101
	movq	%rax, %rsi	# tmp101,
	movq	%rdx, %rdi	# _5,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:47: }
	jmp	.L12	#
.L10:
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:44:     } else if (&ti == &ti_rect) {
	movq	-24(%rbp), %rax	# ti, tmp102
	cmpq	-8(%rbp), %rax	# ti_rect, tmp102
	jne	.L12	#,
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:45:         std::cout << "Rectangle (Address check: " << &ti << " == " << &ti_rect << ")\n";
	leaq	.LC3(%rip), %rax	#, tmp103
	movq	%rax, %rsi	# tmp103,
	leaq	_ZSt4cout(%rip), %rax	#, tmp104
	movq	%rax, %rdi	# tmp104,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
	movq	%rax, %rdx	#, _6
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:45:         std::cout << "Rectangle (Address check: " << &ti << " == " << &ti_rect << ")\n";
	movq	-24(%rbp), %rax	# ti, tmp105
	movq	%rax, %rsi	# tmp105,
	movq	%rdx, %rdi	# _6,
	call	_ZNSolsEPKv@PLT	#
	movq	%rax, %rdx	#, _7
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:45:         std::cout << "Rectangle (Address check: " << &ti << " == " << &ti_rect << ")\n";
	leaq	.LC1(%rip), %rax	#, tmp106
	movq	%rax, %rsi	# tmp106,
	movq	%rdx, %rdi	# _7,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
	movq	%rax, %rdx	#, _8
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:45:         std::cout << "Rectangle (Address check: " << &ti << " == " << &ti_rect << ")\n";
	movq	-8(%rbp), %rax	# ti_rect, tmp107
	movq	%rax, %rsi	# tmp107,
	movq	%rdx, %rdi	# _8,
	call	_ZNSolsEPKv@PLT	#
	movq	%rax, %rdx	#, _9
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:45:         std::cout << "Rectangle (Address check: " << &ti << " == " << &ti_rect << ")\n";
	leaq	.LC2(%rip), %rax	#, tmp108
	movq	%rax, %rsi	# tmp108,
	movq	%rdx, %rdi	# _9,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
.L12:
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:47: }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE3629:
	.size	_ZNK9Rectangle6whoAmIEv, .-_ZNK9Rectangle6whoAmIEv
	.section	.text._ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12_Vector_implD2Ev,"axG",@progbits,_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12_Vector_implD5Ev,comdat
	.align 2
	.weak	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12_Vector_implD2Ev
	.type	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12_Vector_implD2Ev, @function
_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12_Vector_implD2Ev:
.LFB3635:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)	# this, this
	movq	-24(%rbp), %rax	# this, tmp82
	movq	%rax, -8(%rbp)	# tmp82, this
# /usr/include/c++/13/bits/allocator.h:184:       ~allocator() _GLIBCXX_NOTHROW { }
	nop	
# /usr/include/c++/13/bits/stl_vector.h:133:       struct _Vector_impl
	nop	
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE3635:
	.size	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12_Vector_implD2Ev, .-_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12_Vector_implD2Ev
	.weak	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12_Vector_implD1Ev
	.set	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12_Vector_implD1Ev,_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12_Vector_implD2Ev
	.section	.text._ZN9__gnu_cxxeqIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEEbRKNS_17__normal_iteratorIT_T0_EESF_,"axG",@progbits,_ZN9__gnu_cxxeqIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEEbRKNS_17__normal_iteratorIT_T0_EESF_,comdat
	.weak	_ZN9__gnu_cxxeqIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEEbRKNS_17__normal_iteratorIT_T0_EESF_
	.type	_ZN9__gnu_cxxeqIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEEbRKNS_17__normal_iteratorIT_T0_EESF_, @function
_ZN9__gnu_cxxeqIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEEbRKNS_17__normal_iteratorIT_T0_EESF_:
.LFB3677:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$24, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)	# __lhs, __lhs
	movq	%rsi, -32(%rbp)	# __rhs, __rhs
# /usr/include/c++/13/bits/stl_iterator.h:1203:     { return __lhs.base() == __rhs.base(); }
	movq	-24(%rbp), %rax	# __lhs, tmp88
	movq	%rax, %rdi	# tmp88,
	call	_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEE4baseEv	#
# /usr/include/c++/13/bits/stl_iterator.h:1203:     { return __lhs.base() == __rhs.base(); }
	movq	(%rax), %rbx	# *_1, _2
# /usr/include/c++/13/bits/stl_iterator.h:1203:     { return __lhs.base() == __rhs.base(); }
	movq	-32(%rbp), %rax	# __rhs, tmp89
	movq	%rax, %rdi	# tmp89,
	call	_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEE4baseEv	#
# /usr/include/c++/13/bits/stl_iterator.h:1203:     { return __lhs.base() == __rhs.base(); }
	movq	(%rax), %rax	# *_3, _4
# /usr/include/c++/13/bits/stl_iterator.h:1203:     { return __lhs.base() == __rhs.base(); }
	cmpq	%rax, %rbx	# _4, _2
	sete	%al	#, _10
# /usr/include/c++/13/bits/stl_iterator.h:1203:     { return __lhs.base() == __rhs.base(); }
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE3677:
	.size	_ZN9__gnu_cxxeqIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEEbRKNS_17__normal_iteratorIT_T0_EESF_, .-_ZN9__gnu_cxxeqIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEEbRKNS_17__normal_iteratorIT_T0_EESF_
	.section	.text._ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEE4baseEv,"axG",@progbits,_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEE4baseEv,comdat
	.align 2
	.weak	_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEE4baseEv
	.type	_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEE4baseEv, @function
_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEE4baseEv:
.LFB3678:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/bits/stl_iterator.h:1163:       { return _M_current; }
	movq	-8(%rbp), %rax	# this, _2
# /usr/include/c++/13/bits/stl_iterator.h:1163:       { return _M_current; }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE3678:
	.size	_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEE4baseEv, .-_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEE4baseEv
	.section	.text._ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEdeEv,"axG",@progbits,_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEdeEv,comdat
	.align 2
	.weak	_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEdeEv
	.type	_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEdeEv, @function
_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEdeEv:
.LFB3679:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/bits/stl_iterator.h:1100:       { return *_M_current; }
	movq	-8(%rbp), %rax	# this, tmp84
	movq	(%rax), %rax	# this_2(D)->_M_current, _3
# /usr/include/c++/13/bits/stl_iterator.h:1100:       { return *_M_current; }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE3679:
	.size	_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEdeEv, .-_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEdeEv
	.section	.rodata
	.align 8
.LC4:
	.string	"=== RTTI via typeid and Address Comparison ===\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3630:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3630
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$72, %rsp	#,
	.cfi_offset 3, -24
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:49: int main() {
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp138
	movq	%rax, -24(%rbp)	# tmp138, D.99508
	xorl	%eax, %eax	# tmp138
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:50:     std::vector<std::unique_ptr<Shape>> shapes;
	pxor	%xmm0, %xmm0	# tmp91
	movaps	%xmm0, -48(%rbp)	# tmp91, shapes
	movq	%xmm0, -32(%rbp)	# tmp91, shapes
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:51:     shapes.push_back(std::make_unique<Circle>());
	leaq	-80(%rbp), %rax	#, tmp92
	movq	%rax, %rdi	# tmp92,
.LEHB0:
	call	_ZSt11make_uniqueI6CircleJEENSt8__detail9_MakeUniqIT_E15__single_objectEDpOT0_	#
.LEHE0:
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:51:     shapes.push_back(std::make_unique<Circle>());
	leaq	-80(%rbp), %rdx	#, tmp93
	leaq	-72(%rbp), %rax	#, tmp94
	movq	%rdx, %rsi	# tmp93,
	movq	%rax, %rdi	# tmp94,
	call	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC1I6CircleS1_IS5_EvEEOS_IT_T0_E	#
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:51:     shapes.push_back(std::make_unique<Circle>());
	leaq	-72(%rbp), %rdx	#, tmp95
	leaq	-48(%rbp), %rax	#, tmp96
	movq	%rdx, %rsi	# tmp95,
	movq	%rax, %rdi	# tmp96,
.LEHB1:
	call	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE9push_backEOS4_	#
.LEHE1:
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:51:     shapes.push_back(std::make_unique<Circle>());
	leaq	-72(%rbp), %rax	#, tmp97
	movq	%rax, %rdi	# tmp97,
	call	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EED1Ev	#
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:51:     shapes.push_back(std::make_unique<Circle>());
	leaq	-80(%rbp), %rax	#, tmp98
	movq	%rax, %rdi	# tmp98,
	call	_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EED1Ev	#
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:52:     shapes.push_back(std::make_unique<Rectangle>());
	leaq	-80(%rbp), %rax	#, tmp99
	movq	%rax, %rdi	# tmp99,
.LEHB2:
	call	_ZSt11make_uniqueI9RectangleJEENSt8__detail9_MakeUniqIT_E15__single_objectEDpOT0_	#
.LEHE2:
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:52:     shapes.push_back(std::make_unique<Rectangle>());
	leaq	-80(%rbp), %rdx	#, tmp100
	leaq	-72(%rbp), %rax	#, tmp101
	movq	%rdx, %rsi	# tmp100,
	movq	%rax, %rdi	# tmp101,
	call	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC1I9RectangleS1_IS5_EvEEOS_IT_T0_E	#
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:52:     shapes.push_back(std::make_unique<Rectangle>());
	leaq	-72(%rbp), %rdx	#, tmp102
	leaq	-48(%rbp), %rax	#, tmp103
	movq	%rdx, %rsi	# tmp102,
	movq	%rax, %rdi	# tmp103,
.LEHB3:
	call	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE9push_backEOS4_	#
.LEHE3:
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:52:     shapes.push_back(std::make_unique<Rectangle>());
	leaq	-72(%rbp), %rax	#, tmp104
	movq	%rax, %rdi	# tmp104,
	call	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EED1Ev	#
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:52:     shapes.push_back(std::make_unique<Rectangle>());
	leaq	-80(%rbp), %rax	#, tmp105
	movq	%rax, %rdi	# tmp105,
	call	_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EED1Ev	#
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:54:     std::cout << "=== RTTI via typeid and Address Comparison ===\n";
	leaq	.LC4(%rip), %rax	#, tmp106
	movq	%rax, %rsi	# tmp106,
	leaq	_ZSt4cout(%rip), %rax	#, tmp107
	movq	%rax, %rdi	# tmp107,
.LEHB4:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:55:     for (const auto& shape : shapes) {
	leaq	-48(%rbp), %rax	#, tmp108
	movq	%rax, -64(%rbp)	# tmp108, __for_range
	movq	-64(%rbp), %rax	# __for_range, tmp109
	movq	%rax, %rdi	# tmp109,
	call	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE5beginEv	#
	movq	%rax, -80(%rbp)	# tmp111, MEM[(struct __normal_iterator *)_58]
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:55:     for (const auto& shape : shapes) {
	movq	-64(%rbp), %rax	# __for_range, tmp112
	movq	%rax, %rdi	# tmp112,
	call	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE3endEv	#
	movq	%rax, -72(%rbp)	# tmp114, MEM[(struct __normal_iterator *)_59]
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:55:     for (const auto& shape : shapes) {
	jmp	.L21	#
.L22:
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:55:     for (const auto& shape : shapes) {
	leaq	-80(%rbp), %rax	#, tmp115
	movq	%rax, %rdi	# tmp115,
	call	_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEdeEv	#
	movq	%rax, -56(%rbp)	# tmp116, shape
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:56:         shape->whoAmI();
	movq	-56(%rbp), %rax	# shape, tmp117
	movq	%rax, %rdi	# tmp117,
	call	_ZNKSt10unique_ptrI5ShapeSt14default_deleteIS0_EEptEv	#
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:56:         shape->whoAmI();
	movq	(%rax), %rdx	# _39->_vptr.Shape, _1
	addq	$16, %rdx	#, _2
	movq	(%rdx), %rdx	# *_2, _3
	movq	%rax, %rdi	# _39,
	call	*%rdx	# _3
.LEHE4:
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:55:     for (const auto& shape : shapes) {
	leaq	-80(%rbp), %rax	#, tmp118
	movq	%rax, %rdi	# tmp118,
	call	_ZN9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEppEv	#
.L21:
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:55:     for (const auto& shape : shapes) {
	leaq	-72(%rbp), %rdx	#, tmp119
	leaq	-80(%rbp), %rax	#, tmp120
	movq	%rdx, %rsi	# tmp119,
	movq	%rax, %rdi	# tmp120,
	call	_ZN9__gnu_cxxeqIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEEbRKNS_17__normal_iteratorIT_T0_EESF_	#
	xorl	$1, %eax	#, retval.0_30
	testb	%al, %al	# retval.0_30
	jne	.L22	#,
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:59:     return 0;
	movl	$0, %ebx	#, _33
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:60: }
	leaq	-48(%rbp), %rax	#, tmp121
	movq	%rax, %rdi	# tmp121,
	call	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED1Ev	#
	movl	%ebx, %eax	# _33, <retval>
	movq	-24(%rbp), %rdx	# D.99508, tmp139
	subq	%fs:40, %rdx	# MEM[(<address-space-1> long unsigned int *)40B], tmp139
	je	.L28	#,
	jmp	.L32	#
.L29:
	endbr64	
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:51:     shapes.push_back(std::make_unique<Circle>());
	movq	%rax, %rbx	#, tmp125
	leaq	-72(%rbp), %rax	#, tmp123
	movq	%rax, %rdi	# tmp123,
	call	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EED1Ev	#
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:51:     shapes.push_back(std::make_unique<Circle>());
	leaq	-80(%rbp), %rax	#, tmp128
	movq	%rax, %rdi	# tmp128,
	call	_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EED1Ev	#
	jmp	.L25	#
.L31:
	endbr64	
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:52:     shapes.push_back(std::make_unique<Rectangle>());
	movq	%rax, %rbx	#, tmp133
	leaq	-72(%rbp), %rax	#, tmp131
	movq	%rax, %rdi	# tmp131,
	call	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EED1Ev	#
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:52:     shapes.push_back(std::make_unique<Rectangle>());
	leaq	-80(%rbp), %rax	#, tmp136
	movq	%rax, %rdi	# tmp136,
	call	_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EED1Ev	#
	jmp	.L25	#
.L30:
	endbr64	
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:60: }
	movq	%rax, %rbx	#, tmp129
.L25:
	leaq	-48(%rbp), %rax	#, tmp137
	movq	%rax, %rdi	# tmp137,
	call	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED1Ev	#
	movq	%rbx, %rax	# tmp129, D.99506
	movq	-24(%rbp), %rdx	# D.99508, tmp140
	subq	%fs:40, %rdx	# MEM[(<address-space-1> long unsigned int *)40B], tmp140
	je	.L27	#,
	call	__stack_chk_fail@PLT	#
.L27:
	movq	%rax, %rdi	# D.99506,
.LEHB5:
	call	_Unwind_Resume@PLT	#
.LEHE5:
.L32:
	call	__stack_chk_fail@PLT	#
.L28:
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE3630:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA3630:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3630-.LLSDACSB3630
.LLSDACSB3630:
	.uleb128 .LEHB0-.LFB3630
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L30-.LFB3630
	.uleb128 0
	.uleb128 .LEHB1-.LFB3630
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L29-.LFB3630
	.uleb128 0
	.uleb128 .LEHB2-.LFB3630
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L30-.LFB3630
	.uleb128 0
	.uleb128 .LEHB3-.LFB3630
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L31-.LFB3630
	.uleb128 0
	.uleb128 .LEHB4-.LFB3630
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L30-.LFB3630
	.uleb128 0
	.uleb128 .LEHB5-.LFB3630
	.uleb128 .LEHE5-.LEHB5
	.uleb128 0
	.uleb128 0
.LLSDACSE3630:
	.text
	.size	main, .-main
	.section	.text._ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED2Ev,"axG",@progbits,_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED5Ev,comdat
	.align 2
	.weak	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED2Ev
	.type	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED2Ev, @function
_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED2Ev:
.LFB3994:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3994
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/bits/stl_vector.h:370: 		      _M_impl._M_end_of_storage - _M_impl._M_start);
	movq	-8(%rbp), %rax	# this, tmp89
	movq	16(%rax), %rdx	# this_9(D)->_M_impl.D.79372._M_end_of_storage, _1
# /usr/include/c++/13/bits/stl_vector.h:370: 		      _M_impl._M_end_of_storage - _M_impl._M_start);
	movq	-8(%rbp), %rax	# this, tmp90
	movq	(%rax), %rax	# this_9(D)->_M_impl.D.79372._M_start, _2
# /usr/include/c++/13/bits/stl_vector.h:370: 		      _M_impl._M_end_of_storage - _M_impl._M_start);
	subq	%rax, %rdx	# _2, _3
	movq	%rdx, %rax	# _3, _3
	sarq	$3, %rax	#, _3
# /usr/include/c++/13/bits/stl_vector.h:369: 	_M_deallocate(_M_impl._M_start,
	movq	%rax, %rdx	# _4, _5
	movq	-8(%rbp), %rax	# this, tmp92
	movq	(%rax), %rcx	# this_9(D)->_M_impl.D.79372._M_start, _6
	movq	-8(%rbp), %rax	# this, tmp93
	movq	%rcx, %rsi	# _6,
	movq	%rax, %rdi	# tmp93,
	call	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE13_M_deallocateEPS4_m	#
# /usr/include/c++/13/bits/stl_vector.h:371:       }
	movq	-8(%rbp), %rax	# this, _7
	movq	%rax, %rdi	# _7,
	call	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12_Vector_implD1Ev	#
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE3994:
	.section	.gcc_except_table
.LLSDA3994:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3994-.LLSDACSB3994
.LLSDACSB3994:
.LLSDACSE3994:
	.section	.text._ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED2Ev,"axG",@progbits,_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED5Ev,comdat
	.size	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED2Ev, .-_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED2Ev
	.weak	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED1Ev
	.set	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED1Ev,_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED2Ev
	.section	.text._ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED2Ev,"axG",@progbits,_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED5Ev,comdat
	.align 2
	.weak	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED2Ev
	.type	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED2Ev, @function
_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED2Ev:
.LFB3997:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3997
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$48, %rsp	#,
	movq	%rdi, -40(%rbp)	# this, this
# /usr/include/c++/13/bits/stl_vector.h:736: 		      _M_get_Tp_allocator());
	movq	-40(%rbp), %rax	# this, _1
	movq	%rax, %rdi	# _1,
	call	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE19_M_get_Tp_allocatorEv	#
# /usr/include/c++/13/bits/stl_vector.h:735: 	std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
	movq	-40(%rbp), %rdx	# this, tmp87
	movq	8(%rdx), %rdx	# this_6(D)->D.80067._M_impl.D.79372._M_finish, _3
	movq	-40(%rbp), %rcx	# this, tmp88
	movq	(%rcx), %rcx	# this_6(D)->D.80067._M_impl.D.79372._M_start, _4
	movq	%rcx, -24(%rbp)	# _4, __first
	movq	%rdx, -16(%rbp)	# _3, __last
	movq	%rax, -8(%rbp)	# _2, D.99456
# /usr/include/c++/13/bits/alloc_traits.h:948:       std::_Destroy(__first, __last);
	movq	-16(%rbp), %rdx	# __last, tmp89
	movq	-24(%rbp), %rax	# __first, tmp90
	movq	%rdx, %rsi	# tmp89,
	movq	%rax, %rdi	# tmp90,
	call	_ZSt8_DestroyIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvT_S6_	#
# /usr/include/c++/13/bits/alloc_traits.h:949:     }
	nop	
# /usr/include/c++/13/bits/stl_vector.h:738:       }
	movq	-40(%rbp), %rax	# this, _5
	movq	%rax, %rdi	# _5,
	call	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED2Ev	#
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE3997:
	.section	.gcc_except_table
.LLSDA3997:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3997-.LLSDACSB3997
.LLSDACSB3997:
.LLSDACSE3997:
	.section	.text._ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED2Ev,"axG",@progbits,_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED5Ev,comdat
	.size	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED2Ev, .-_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED2Ev
	.weak	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED1Ev
	.set	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED1Ev,_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EED2Ev
	.section	.text._ZN5ShapeC2Ev,"axG",@progbits,_ZN5ShapeC5Ev,comdat
	.align 2
	.weak	_ZN5ShapeC2Ev
	.type	_ZN5ShapeC2Ev, @function
_ZN5ShapeC2Ev:
.LFB4002:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:6: class Shape {
	leaq	16+_ZTV5Shape(%rip), %rdx	#, _1
	movq	-8(%rbp), %rax	# this, tmp83
	movq	%rdx, (%rax)	# _1, this_3(D)->_vptr.Shape
	nop	
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4002:
	.size	_ZN5ShapeC2Ev, .-_ZN5ShapeC2Ev
	.weak	_ZN5ShapeC1Ev
	.set	_ZN5ShapeC1Ev,_ZN5ShapeC2Ev
	.section	.text._ZN5ShapeD2Ev,"axG",@progbits,_ZN5ShapeD5Ev,comdat
	.align 2
	.weak	_ZN5ShapeD2Ev
	.type	_ZN5ShapeD2Ev, @function
_ZN5ShapeD2Ev:
.LFB4005:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:8:     virtual ~Shape() = default;
	leaq	16+_ZTV5Shape(%rip), %rdx	#, _1
	movq	-8(%rbp), %rax	# this, tmp83
	movq	%rdx, (%rax)	# _1, this_3(D)->_vptr.Shape
	nop	
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4005:
	.size	_ZN5ShapeD2Ev, .-_ZN5ShapeD2Ev
	.weak	_ZN5ShapeD1Ev
	.set	_ZN5ShapeD1Ev,_ZN5ShapeD2Ev
	.section	.text._ZN5ShapeD0Ev,"axG",@progbits,_ZN5ShapeD5Ev,comdat
	.align 2
	.weak	_ZN5ShapeD0Ev
	.type	_ZN5ShapeD0Ev, @function
_ZN5ShapeD0Ev:
.LFB4007:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:8:     virtual ~Shape() = default;
	movq	-8(%rbp), %rax	# this, tmp82
	movq	%rax, %rdi	# tmp82,
	call	_ZN5ShapeD1Ev	#
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:8:     virtual ~Shape() = default;
	movq	-8(%rbp), %rax	# this, tmp83
	movl	$8, %esi	#,
	movq	%rax, %rdi	# tmp83,
	call	_ZdlPvm@PLT	#
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:8:     virtual ~Shape() = default;
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4007:
	.size	_ZN5ShapeD0Ev, .-_ZN5ShapeD0Ev
	.section	.text._ZN6CircleC2Ev,"axG",@progbits,_ZN6CircleC5Ev,comdat
	.align 2
	.weak	_ZN6CircleC2Ev
	.type	_ZN6CircleC2Ev, @function
_ZN6CircleC2Ev:
.LFB4008:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:15: class Circle : public Shape {
	movq	-8(%rbp), %rax	# this, _1
	movq	%rax, %rdi	# _1,
	call	_ZN5ShapeC2Ev	#
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:15: class Circle : public Shape {
	leaq	16+_ZTV6Circle(%rip), %rdx	#, _2
	movq	-8(%rbp), %rax	# this, tmp85
	movq	%rdx, (%rax)	# _2, this_4(D)->D.78928._vptr.Shape
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:15: class Circle : public Shape {
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4008:
	.size	_ZN6CircleC2Ev, .-_ZN6CircleC2Ev
	.weak	_ZN6CircleC1Ev
	.set	_ZN6CircleC1Ev,_ZN6CircleC2Ev
	.section	.text._ZSt11make_uniqueI6CircleJEENSt8__detail9_MakeUniqIT_E15__single_objectEDpOT0_,"axG",@progbits,_ZSt11make_uniqueI6CircleJEENSt8__detail9_MakeUniqIT_E15__single_objectEDpOT0_,comdat
	.weak	_ZSt11make_uniqueI6CircleJEENSt8__detail9_MakeUniqIT_E15__single_objectEDpOT0_
	.type	_ZSt11make_uniqueI6CircleJEENSt8__detail9_MakeUniqIT_E15__single_objectEDpOT0_, @function
_ZSt11make_uniqueI6CircleJEENSt8__detail9_MakeUniqIT_E15__single_objectEDpOT0_:
.LFB3999:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$24, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)	# .result_ptr, .result_ptr
# /usr/include/c++/13/bits/unique_ptr.h:1070:     { return unique_ptr<_Tp>(new _Tp(std::forward<_Args>(__args)...)); }
	movl	$8, %edi	#,
	call	_Znwm@PLT	#
	movq	%rax, %rbx	# tmp85, _3
# /usr/include/c++/13/bits/unique_ptr.h:1070:     { return unique_ptr<_Tp>(new _Tp(std::forward<_Args>(__args)...)); }
	movq	$0, (%rbx)	#, MEM[(struct Circle *)_4].D.78928._vptr.Shape
	movq	%rbx, %rdi	# _3,
	call	_ZN6CircleC1Ev	#
# /usr/include/c++/13/bits/unique_ptr.h:1070:     { return unique_ptr<_Tp>(new _Tp(std::forward<_Args>(__args)...)); }
	movq	-24(%rbp), %rax	# <retval>, tmp86
	movq	%rbx, %rsi	# _3,
	movq	%rax, %rdi	# tmp86,
	call	_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EEC1IS2_vEEPS0_	#
# /usr/include/c++/13/bits/unique_ptr.h:1070:     { return unique_ptr<_Tp>(new _Tp(std::forward<_Args>(__args)...)); }
	movq	-24(%rbp), %rax	# <retval>,
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE3999:
	.size	_ZSt11make_uniqueI6CircleJEENSt8__detail9_MakeUniqIT_E15__single_objectEDpOT0_, .-_ZSt11make_uniqueI6CircleJEENSt8__detail9_MakeUniqIT_E15__single_objectEDpOT0_
	.section	.text._ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EED2Ev,"axG",@progbits,_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EED5Ev,comdat
	.align 2
	.weak	_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EED2Ev
	.type	_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EED2Ev, @function
_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EED2Ev:
.LFB4011:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$40, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)	# this, this
# /usr/include/c++/13/bits/unique_ptr.h:402: 	auto& __ptr = _M_t._M_ptr();
	movq	-40(%rbp), %rax	# this, _1
	movq	%rax, %rdi	# _1,
	call	_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE6_M_ptrEv	#
	movq	%rax, -24(%rbp)	# tmp87, __ptr
# /usr/include/c++/13/bits/unique_ptr.h:403: 	if (__ptr != nullptr)
	movq	-24(%rbp), %rax	# __ptr, tmp88
	movq	(%rax), %rax	# *__ptr_10, _2
# /usr/include/c++/13/bits/unique_ptr.h:403: 	if (__ptr != nullptr)
	testq	%rax, %rax	# _2
	je	.L42	#,
# /usr/include/c++/13/bits/unique_ptr.h:404: 	  get_deleter()(std::move(__ptr));
	movq	-40(%rbp), %rax	# this, tmp89
	movq	%rax, %rdi	# tmp89,
	call	_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EE11get_deleterEv	#
	movq	%rax, %rbx	#, _3
# /usr/include/c++/13/bits/unique_ptr.h:404: 	  get_deleter()(std::move(__ptr));
	movq	-24(%rbp), %rax	# __ptr, tmp90
	movq	%rax, %rdi	# tmp90,
	call	_ZSt4moveIRP6CircleEONSt16remove_referenceIT_E4typeEOS4_	#
# /usr/include/c++/13/bits/unique_ptr.h:404: 	  get_deleter()(std::move(__ptr));
	movq	(%rax), %rax	# *_4, _5
	movq	%rax, %rsi	# _5,
	movq	%rbx, %rdi	# _3,
	call	_ZNKSt14default_deleteI6CircleEclEPS0_	#
.L42:
# /usr/include/c++/13/bits/unique_ptr.h:405: 	__ptr = pointer();
	movq	-24(%rbp), %rax	# __ptr, tmp91
	movq	$0, (%rax)	#, *__ptr_10
# /usr/include/c++/13/bits/unique_ptr.h:406:       }
	nop	
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4011:
	.size	_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EED2Ev, .-_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EED2Ev
	.weak	_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EED1Ev
	.set	_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EED1Ev,_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EED2Ev
	.section	.text._ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EIS1_I6CircleEEEPS0_OT_,"axG",@progbits,_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EECI5St15__uniq_ptr_implIS0_S2_EIS1_I6CircleEEEPS0_OT_,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EIS1_I6CircleEEEPS0_OT_
	.type	_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EIS1_I6CircleEEEPS0_OT_, @function
_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EIS1_I6CircleEEEPS0_OT_:
.LFB4015:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$32, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# D.92818, D.92818
	movq	%rdx, -24(%rbp)	# D.92819, D.92819
# /usr/include/c++/13/bits/unique_ptr.h:241:       using __uniq_ptr_impl<_Tp, _Dp>::__uniq_ptr_impl;
	movq	-8(%rbp), %rax	# this, _1
	movq	-16(%rbp), %rcx	# D.92818, _2
	movq	-24(%rbp), %rdx	# D.92819, tmp84
	movq	%rcx, %rsi	# _2,
	movq	%rax, %rdi	# _1,
	call	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2IS1_I6CircleEEEPS0_OT_	#
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4015:
	.size	_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EIS1_I6CircleEEEPS0_OT_, .-_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EIS1_I6CircleEEEPS0_OT_
	.weak	_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EECI1St15__uniq_ptr_implIS0_S2_EIS1_I6CircleEEEPS0_OT_
	.set	_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EECI1St15__uniq_ptr_implIS0_S2_EIS1_I6CircleEEEPS0_OT_,_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EIS1_I6CircleEEEPS0_OT_
	.section	.text._ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC2I6CircleS1_IS5_EvEEOS_IT_T0_E,"axG",@progbits,_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC5I6CircleS1_IS5_EvEEOS_IT_T0_E,comdat
	.align 2
	.weak	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC2I6CircleS1_IS5_EvEEOS_IT_T0_E
	.type	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC2I6CircleS1_IS5_EvEEOS_IT_T0_E, @function
_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC2I6CircleS1_IS5_EvEEOS_IT_T0_E:
.LFB4017:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA4017
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%r12	#
	pushq	%rbx	#
	subq	$16, %rsp	#,
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -24(%rbp)	# this, this
	movq	%rsi, -32(%rbp)	# __u, __u
# /usr/include/c++/13/bits/unique_ptr.h:381: 	: _M_t(__u.release(), std::forward<_Ep>(__u.get_deleter()))
	movq	-24(%rbp), %rbx	# this, _1
# /usr/include/c++/13/bits/unique_ptr.h:381: 	: _M_t(__u.release(), std::forward<_Ep>(__u.get_deleter()))
	movq	-32(%rbp), %rax	# __u, tmp86
	movq	%rax, %rdi	# tmp86,
	call	_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EE11get_deleterEv	#
# /usr/include/c++/13/bits/unique_ptr.h:381: 	: _M_t(__u.release(), std::forward<_Ep>(__u.get_deleter()))
	movq	%rax, %rdi	# _2,
	call	_ZSt7forwardISt14default_deleteI6CircleEEOT_RNSt16remove_referenceIS3_E4typeE	#
	movq	%rax, %r12	#, _3
# /usr/include/c++/13/bits/unique_ptr.h:381: 	: _M_t(__u.release(), std::forward<_Ep>(__u.get_deleter()))
	movq	-32(%rbp), %rax	# __u, tmp87
	movq	%rax, %rdi	# tmp87,
	call	_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EE7releaseEv	#
# /usr/include/c++/13/bits/unique_ptr.h:381: 	: _M_t(__u.release(), std::forward<_Ep>(__u.get_deleter()))
	movq	%r12, %rdx	# _3,
	movq	%rax, %rsi	# _4,
	movq	%rbx, %rdi	# _1,
	call	_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EECI1St15__uniq_ptr_implIS0_S2_EIS1_I6CircleEEEPS0_OT_	#
# /usr/include/c++/13/bits/unique_ptr.h:382: 	{ }
	nop	
	addq	$16, %rsp	#,
	popq	%rbx	#
	popq	%r12	#
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4017:
	.section	.gcc_except_table
.LLSDA4017:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4017-.LLSDACSB4017
.LLSDACSB4017:
.LLSDACSE4017:
	.section	.text._ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC2I6CircleS1_IS5_EvEEOS_IT_T0_E,"axG",@progbits,_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC5I6CircleS1_IS5_EvEEOS_IT_T0_E,comdat
	.size	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC2I6CircleS1_IS5_EvEEOS_IT_T0_E, .-_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC2I6CircleS1_IS5_EvEEOS_IT_T0_E
	.weak	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC1I6CircleS1_IS5_EvEEOS_IT_T0_E
	.set	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC1I6CircleS1_IS5_EvEEOS_IT_T0_E,_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC2I6CircleS1_IS5_EvEEOS_IT_T0_E
	.section	.text._ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EED2Ev,"axG",@progbits,_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EED5Ev,comdat
	.align 2
	.weak	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EED2Ev
	.type	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EED2Ev, @function
_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EED2Ev:
.LFB4020:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$40, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)	# this, this
# /usr/include/c++/13/bits/unique_ptr.h:402: 	auto& __ptr = _M_t._M_ptr();
	movq	-40(%rbp), %rax	# this, _1
	movq	%rax, %rdi	# _1,
	call	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE6_M_ptrEv	#
	movq	%rax, -24(%rbp)	# tmp87, __ptr
# /usr/include/c++/13/bits/unique_ptr.h:403: 	if (__ptr != nullptr)
	movq	-24(%rbp), %rax	# __ptr, tmp88
	movq	(%rax), %rax	# *__ptr_10, _2
# /usr/include/c++/13/bits/unique_ptr.h:403: 	if (__ptr != nullptr)
	testq	%rax, %rax	# _2
	je	.L46	#,
# /usr/include/c++/13/bits/unique_ptr.h:404: 	  get_deleter()(std::move(__ptr));
	movq	-40(%rbp), %rax	# this, tmp89
	movq	%rax, %rdi	# tmp89,
	call	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EE11get_deleterEv	#
	movq	%rax, %rbx	#, _3
# /usr/include/c++/13/bits/unique_ptr.h:404: 	  get_deleter()(std::move(__ptr));
	movq	-24(%rbp), %rax	# __ptr, tmp90
	movq	%rax, %rdi	# tmp90,
	call	_ZSt4moveIRP5ShapeEONSt16remove_referenceIT_E4typeEOS4_	#
# /usr/include/c++/13/bits/unique_ptr.h:404: 	  get_deleter()(std::move(__ptr));
	movq	(%rax), %rax	# *_4, _5
	movq	%rax, %rsi	# _5,
	movq	%rbx, %rdi	# _3,
	call	_ZNKSt14default_deleteI5ShapeEclEPS0_	#
.L46:
# /usr/include/c++/13/bits/unique_ptr.h:405: 	__ptr = pointer();
	movq	-24(%rbp), %rax	# __ptr, tmp91
	movq	$0, (%rax)	#, *__ptr_10
# /usr/include/c++/13/bits/unique_ptr.h:406:       }
	nop	
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4020:
	.size	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EED2Ev, .-_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EED2Ev
	.weak	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EED1Ev
	.set	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EED1Ev,_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EED2Ev
	.section	.text._ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE9push_backEOS4_,"axG",@progbits,_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE9push_backEOS4_,comdat
	.align 2
	.weak	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE9push_backEOS4_
	.type	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE9push_backEOS4_, @function
_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE9push_backEOS4_:
.LFB4022:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# __x, __x
# /usr/include/c++/13/bits/stl_vector.h:1299:       { emplace_back(std::move(__x)); }
	movq	-16(%rbp), %rax	# __x, tmp83
	movq	%rax, %rdi	# tmp83,
	call	_ZSt4moveIRSt10unique_ptrI5ShapeSt14default_deleteIS1_EEEONSt16remove_referenceIT_E4typeEOS7_	#
	movq	%rax, %rdx	#, _1
# /usr/include/c++/13/bits/stl_vector.h:1299:       { emplace_back(std::move(__x)); }
	movq	-8(%rbp), %rax	# this, tmp84
	movq	%rdx, %rsi	# _1,
	movq	%rax, %rdi	# tmp84,
	call	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12emplace_backIJS4_EEERS4_DpOT_	#
# /usr/include/c++/13/bits/stl_vector.h:1299:       { emplace_back(std::move(__x)); }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4022:
	.size	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE9push_backEOS4_, .-_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE9push_backEOS4_
	.section	.text._ZN9RectangleC2Ev,"axG",@progbits,_ZN9RectangleC5Ev,comdat
	.align 2
	.weak	_ZN9RectangleC2Ev
	.type	_ZN9RectangleC2Ev, @function
_ZN9RectangleC2Ev:
.LFB4025:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:20: class Rectangle : public Shape {
	movq	-8(%rbp), %rax	# this, _1
	movq	%rax, %rdi	# _1,
	call	_ZN5ShapeC2Ev	#
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:20: class Rectangle : public Shape {
	leaq	16+_ZTV9Rectangle(%rip), %rdx	#, _2
	movq	-8(%rbp), %rax	# this, tmp85
	movq	%rdx, (%rax)	# _2, this_4(D)->D.78950._vptr.Shape
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:20: class Rectangle : public Shape {
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4025:
	.size	_ZN9RectangleC2Ev, .-_ZN9RectangleC2Ev
	.weak	_ZN9RectangleC1Ev
	.set	_ZN9RectangleC1Ev,_ZN9RectangleC2Ev
	.section	.text._ZSt11make_uniqueI9RectangleJEENSt8__detail9_MakeUniqIT_E15__single_objectEDpOT0_,"axG",@progbits,_ZSt11make_uniqueI9RectangleJEENSt8__detail9_MakeUniqIT_E15__single_objectEDpOT0_,comdat
	.weak	_ZSt11make_uniqueI9RectangleJEENSt8__detail9_MakeUniqIT_E15__single_objectEDpOT0_
	.type	_ZSt11make_uniqueI9RectangleJEENSt8__detail9_MakeUniqIT_E15__single_objectEDpOT0_, @function
_ZSt11make_uniqueI9RectangleJEENSt8__detail9_MakeUniqIT_E15__single_objectEDpOT0_:
.LFB4023:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$24, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)	# .result_ptr, .result_ptr
# /usr/include/c++/13/bits/unique_ptr.h:1070:     { return unique_ptr<_Tp>(new _Tp(std::forward<_Args>(__args)...)); }
	movl	$8, %edi	#,
	call	_Znwm@PLT	#
	movq	%rax, %rbx	# tmp85, _3
# /usr/include/c++/13/bits/unique_ptr.h:1070:     { return unique_ptr<_Tp>(new _Tp(std::forward<_Args>(__args)...)); }
	movq	$0, (%rbx)	#, MEM[(struct Rectangle *)_4].D.78950._vptr.Shape
	movq	%rbx, %rdi	# _3,
	call	_ZN9RectangleC1Ev	#
# /usr/include/c++/13/bits/unique_ptr.h:1070:     { return unique_ptr<_Tp>(new _Tp(std::forward<_Args>(__args)...)); }
	movq	-24(%rbp), %rax	# <retval>, tmp86
	movq	%rbx, %rsi	# _3,
	movq	%rax, %rdi	# tmp86,
	call	_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EEC1IS2_vEEPS0_	#
# /usr/include/c++/13/bits/unique_ptr.h:1070:     { return unique_ptr<_Tp>(new _Tp(std::forward<_Args>(__args)...)); }
	movq	-24(%rbp), %rax	# <retval>,
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4023:
	.size	_ZSt11make_uniqueI9RectangleJEENSt8__detail9_MakeUniqIT_E15__single_objectEDpOT0_, .-_ZSt11make_uniqueI9RectangleJEENSt8__detail9_MakeUniqIT_E15__single_objectEDpOT0_
	.section	.text._ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EED2Ev,"axG",@progbits,_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EED5Ev,comdat
	.align 2
	.weak	_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EED2Ev
	.type	_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EED2Ev, @function
_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EED2Ev:
.LFB4028:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$40, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)	# this, this
# /usr/include/c++/13/bits/unique_ptr.h:402: 	auto& __ptr = _M_t._M_ptr();
	movq	-40(%rbp), %rax	# this, _1
	movq	%rax, %rdi	# _1,
	call	_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE6_M_ptrEv	#
	movq	%rax, -24(%rbp)	# tmp87, __ptr
# /usr/include/c++/13/bits/unique_ptr.h:403: 	if (__ptr != nullptr)
	movq	-24(%rbp), %rax	# __ptr, tmp88
	movq	(%rax), %rax	# *__ptr_10, _2
# /usr/include/c++/13/bits/unique_ptr.h:403: 	if (__ptr != nullptr)
	testq	%rax, %rax	# _2
	je	.L52	#,
# /usr/include/c++/13/bits/unique_ptr.h:404: 	  get_deleter()(std::move(__ptr));
	movq	-40(%rbp), %rax	# this, tmp89
	movq	%rax, %rdi	# tmp89,
	call	_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EE11get_deleterEv	#
	movq	%rax, %rbx	#, _3
# /usr/include/c++/13/bits/unique_ptr.h:404: 	  get_deleter()(std::move(__ptr));
	movq	-24(%rbp), %rax	# __ptr, tmp90
	movq	%rax, %rdi	# tmp90,
	call	_ZSt4moveIRP9RectangleEONSt16remove_referenceIT_E4typeEOS4_	#
# /usr/include/c++/13/bits/unique_ptr.h:404: 	  get_deleter()(std::move(__ptr));
	movq	(%rax), %rax	# *_4, _5
	movq	%rax, %rsi	# _5,
	movq	%rbx, %rdi	# _3,
	call	_ZNKSt14default_deleteI9RectangleEclEPS0_	#
.L52:
# /usr/include/c++/13/bits/unique_ptr.h:405: 	__ptr = pointer();
	movq	-24(%rbp), %rax	# __ptr, tmp91
	movq	$0, (%rax)	#, *__ptr_10
# /usr/include/c++/13/bits/unique_ptr.h:406:       }
	nop	
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4028:
	.size	_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EED2Ev, .-_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EED2Ev
	.weak	_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EED1Ev
	.set	_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EED1Ev,_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EED2Ev
	.section	.text._ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EIS1_I9RectangleEEEPS0_OT_,"axG",@progbits,_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EECI5St15__uniq_ptr_implIS0_S2_EIS1_I9RectangleEEEPS0_OT_,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EIS1_I9RectangleEEEPS0_OT_
	.type	_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EIS1_I9RectangleEEEPS0_OT_, @function
_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EIS1_I9RectangleEEEPS0_OT_:
.LFB4032:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$32, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# D.93048, D.93048
	movq	%rdx, -24(%rbp)	# D.93049, D.93049
# /usr/include/c++/13/bits/unique_ptr.h:241:       using __uniq_ptr_impl<_Tp, _Dp>::__uniq_ptr_impl;
	movq	-8(%rbp), %rax	# this, _1
	movq	-16(%rbp), %rcx	# D.93048, _2
	movq	-24(%rbp), %rdx	# D.93049, tmp84
	movq	%rcx, %rsi	# _2,
	movq	%rax, %rdi	# _1,
	call	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2IS1_I9RectangleEEEPS0_OT_	#
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4032:
	.size	_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EIS1_I9RectangleEEEPS0_OT_, .-_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EIS1_I9RectangleEEEPS0_OT_
	.weak	_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EECI1St15__uniq_ptr_implIS0_S2_EIS1_I9RectangleEEEPS0_OT_
	.set	_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EECI1St15__uniq_ptr_implIS0_S2_EIS1_I9RectangleEEEPS0_OT_,_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EIS1_I9RectangleEEEPS0_OT_
	.section	.text._ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC2I9RectangleS1_IS5_EvEEOS_IT_T0_E,"axG",@progbits,_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC5I9RectangleS1_IS5_EvEEOS_IT_T0_E,comdat
	.align 2
	.weak	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC2I9RectangleS1_IS5_EvEEOS_IT_T0_E
	.type	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC2I9RectangleS1_IS5_EvEEOS_IT_T0_E, @function
_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC2I9RectangleS1_IS5_EvEEOS_IT_T0_E:
.LFB4034:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA4034
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%r12	#
	pushq	%rbx	#
	subq	$16, %rsp	#,
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -24(%rbp)	# this, this
	movq	%rsi, -32(%rbp)	# __u, __u
# /usr/include/c++/13/bits/unique_ptr.h:381: 	: _M_t(__u.release(), std::forward<_Ep>(__u.get_deleter()))
	movq	-24(%rbp), %rbx	# this, _1
# /usr/include/c++/13/bits/unique_ptr.h:381: 	: _M_t(__u.release(), std::forward<_Ep>(__u.get_deleter()))
	movq	-32(%rbp), %rax	# __u, tmp86
	movq	%rax, %rdi	# tmp86,
	call	_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EE11get_deleterEv	#
# /usr/include/c++/13/bits/unique_ptr.h:381: 	: _M_t(__u.release(), std::forward<_Ep>(__u.get_deleter()))
	movq	%rax, %rdi	# _2,
	call	_ZSt7forwardISt14default_deleteI9RectangleEEOT_RNSt16remove_referenceIS3_E4typeE	#
	movq	%rax, %r12	#, _3
# /usr/include/c++/13/bits/unique_ptr.h:381: 	: _M_t(__u.release(), std::forward<_Ep>(__u.get_deleter()))
	movq	-32(%rbp), %rax	# __u, tmp87
	movq	%rax, %rdi	# tmp87,
	call	_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EE7releaseEv	#
# /usr/include/c++/13/bits/unique_ptr.h:381: 	: _M_t(__u.release(), std::forward<_Ep>(__u.get_deleter()))
	movq	%r12, %rdx	# _3,
	movq	%rax, %rsi	# _4,
	movq	%rbx, %rdi	# _1,
	call	_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EECI1St15__uniq_ptr_implIS0_S2_EIS1_I9RectangleEEEPS0_OT_	#
# /usr/include/c++/13/bits/unique_ptr.h:382: 	{ }
	nop	
	addq	$16, %rsp	#,
	popq	%rbx	#
	popq	%r12	#
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4034:
	.section	.gcc_except_table
.LLSDA4034:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4034-.LLSDACSB4034
.LLSDACSB4034:
.LLSDACSE4034:
	.section	.text._ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC2I9RectangleS1_IS5_EvEEOS_IT_T0_E,"axG",@progbits,_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC5I9RectangleS1_IS5_EvEEOS_IT_T0_E,comdat
	.size	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC2I9RectangleS1_IS5_EvEEOS_IT_T0_E, .-_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC2I9RectangleS1_IS5_EvEEOS_IT_T0_E
	.weak	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC1I9RectangleS1_IS5_EvEEOS_IT_T0_E
	.set	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC1I9RectangleS1_IS5_EvEEOS_IT_T0_E,_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC2I9RectangleS1_IS5_EvEEOS_IT_T0_E
	.section	.text._ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE5beginEv,"axG",@progbits,_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE5beginEv,comdat
	.align 2
	.weak	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE5beginEv
	.type	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE5beginEv, @function
_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE5beginEv:
.LFB4036:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$32, %rsp	#,
	movq	%rdi, -24(%rbp)	# this, this
# /usr/include/c++/13/bits/stl_vector.h:873:       begin() _GLIBCXX_NOEXCEPT
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp87
	movq	%rax, -8(%rbp)	# tmp87, D.99515
	xorl	%eax, %eax	# tmp87
# /usr/include/c++/13/bits/stl_vector.h:874:       { return iterator(this->_M_impl._M_start); }
	movq	-24(%rbp), %rdx	# this, _1
# /usr/include/c++/13/bits/stl_vector.h:874:       { return iterator(this->_M_impl._M_start); }
	leaq	-16(%rbp), %rax	#, tmp85
	movq	%rdx, %rsi	# _1,
	movq	%rax, %rdi	# tmp85,
	call	_ZN9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEC1ERKS6_	#
# /usr/include/c++/13/bits/stl_vector.h:874:       { return iterator(this->_M_impl._M_start); }
	movq	-16(%rbp), %rax	# D.93074, D.99208
# /usr/include/c++/13/bits/stl_vector.h:874:       { return iterator(this->_M_impl._M_start); }
	movq	-8(%rbp), %rdx	# D.99515, tmp88
	subq	%fs:40, %rdx	# MEM[(<address-space-1> long unsigned int *)40B], tmp88
	je	.L57	#,
	call	__stack_chk_fail@PLT	#
.L57:
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4036:
	.size	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE5beginEv, .-_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE5beginEv
	.section	.text._ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE3endEv,"axG",@progbits,_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE3endEv,comdat
	.align 2
	.weak	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE3endEv
	.type	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE3endEv, @function
_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE3endEv:
.LFB4037:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$32, %rsp	#,
	movq	%rdi, -24(%rbp)	# this, this
# /usr/include/c++/13/bits/stl_vector.h:893:       end() _GLIBCXX_NOEXCEPT
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp88
	movq	%rax, -8(%rbp)	# tmp88, D.99516
	xorl	%eax, %eax	# tmp88
# /usr/include/c++/13/bits/stl_vector.h:894:       { return iterator(this->_M_impl._M_finish); }
	movq	-24(%rbp), %rax	# this, tmp85
	leaq	8(%rax), %rdx	#, _1
# /usr/include/c++/13/bits/stl_vector.h:894:       { return iterator(this->_M_impl._M_finish); }
	leaq	-16(%rbp), %rax	#, tmp86
	movq	%rdx, %rsi	# _1,
	movq	%rax, %rdi	# tmp86,
	call	_ZN9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEC1ERKS6_	#
# /usr/include/c++/13/bits/stl_vector.h:894:       { return iterator(this->_M_impl._M_finish); }
	movq	-16(%rbp), %rax	# D.93079, D.99211
# /usr/include/c++/13/bits/stl_vector.h:894:       { return iterator(this->_M_impl._M_finish); }
	movq	-8(%rbp), %rdx	# D.99516, tmp89
	subq	%fs:40, %rdx	# MEM[(<address-space-1> long unsigned int *)40B], tmp89
	je	.L60	#,
	call	__stack_chk_fail@PLT	#
.L60:
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4037:
	.size	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE3endEv, .-_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE3endEv
	.section	.text._ZN9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEppEv,"axG",@progbits,_ZN9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEppEv,comdat
	.align 2
	.weak	_ZN9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEppEv
	.type	_ZN9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEppEv, @function
_ZN9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEppEv:
.LFB4038:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/bits/stl_iterator.h:1111: 	++_M_current;
	movq	-8(%rbp), %rax	# this, tmp86
	movq	(%rax), %rax	# this_4(D)->_M_current, _1
# /usr/include/c++/13/bits/stl_iterator.h:1111: 	++_M_current;
	leaq	8(%rax), %rdx	#, _2
	movq	-8(%rbp), %rax	# this, tmp87
	movq	%rdx, (%rax)	# _2, this_4(D)->_M_current
# /usr/include/c++/13/bits/stl_iterator.h:1112: 	return *this;
	movq	-8(%rbp), %rax	# this, _6
# /usr/include/c++/13/bits/stl_iterator.h:1113:       }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4038:
	.size	_ZN9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEppEv, .-_ZN9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEppEv
	.section	.text._ZNKSt10unique_ptrI5ShapeSt14default_deleteIS0_EEptEv,"axG",@progbits,_ZNKSt10unique_ptrI5ShapeSt14default_deleteIS0_EEptEv,comdat
	.align 2
	.weak	_ZNKSt10unique_ptrI5ShapeSt14default_deleteIS0_EEptEv
	.type	_ZNKSt10unique_ptrI5ShapeSt14default_deleteIS0_EEptEv, @function
_ZNKSt10unique_ptrI5ShapeSt14default_deleteIS0_EEptEv:
.LFB4039:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/bits/unique_ptr.h:463: 	return get();
	movq	-8(%rbp), %rax	# this, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZNKSt10unique_ptrI5ShapeSt14default_deleteIS0_EE3getEv	#
# /usr/include/c++/13/bits/unique_ptr.h:464:       }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4039:
	.size	_ZNKSt10unique_ptrI5ShapeSt14default_deleteIS0_EEptEv, .-_ZNKSt10unique_ptrI5ShapeSt14default_deleteIS0_EEptEv
	.section	.text._ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE13_M_deallocateEPS4_m,"axG",@progbits,_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE13_M_deallocateEPS4_m,comdat
	.align 2
	.weak	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE13_M_deallocateEPS4_m
	.type	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE13_M_deallocateEPS4_m, @function
_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE13_M_deallocateEPS4_m:
.LFB4183:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$80, %rsp	#,
	movq	%rdi, -56(%rbp)	# this, this
	movq	%rsi, -64(%rbp)	# __p, __p
	movq	%rdx, -72(%rbp)	# __n, __n
# /usr/include/c++/13/bits/stl_vector.h:389: 	if (__p)
	cmpq	$0, -64(%rbp)	#, __p
	je	.L69	#,
# /usr/include/c++/13/bits/stl_vector.h:390: 	  _Tr::deallocate(_M_impl, __p, __n);
	movq	-56(%rbp), %rax	# this, _1
	movq	%rax, -48(%rbp)	# _1, __a
	movq	-64(%rbp), %rax	# __p, tmp84
	movq	%rax, -40(%rbp)	# tmp84, __p
	movq	-72(%rbp), %rax	# __n, tmp85
	movq	%rax, -32(%rbp)	# tmp85, __n
	movq	-48(%rbp), %rax	# __a, tmp86
	movq	%rax, -24(%rbp)	# tmp86, this
	movq	-40(%rbp), %rax	# __p, tmp87
	movq	%rax, -16(%rbp)	# tmp87, __p
	movq	-32(%rbp), %rax	# __n, tmp88
	movq	%rax, -8(%rbp)	# tmp88, __n
# /usr/include/c++/13/bits/allocator.h:205: 	if (std::__is_constant_evaluated())
	call	_ZSt23__is_constant_evaluatedv	#
# /usr/include/c++/13/bits/allocator.h:205: 	if (std::__is_constant_evaluated())
	testb	%al, %al	# retval.13_13
	je	.L67	#,
# /usr/include/c++/13/bits/allocator.h:207: 	    ::operator delete(__p);
	movq	-16(%rbp), %rax	# __p, tmp89
	movq	%rax, %rdi	# tmp89,
	call	_ZdlPv@PLT	#
# /usr/include/c++/13/bits/allocator.h:208: 	    return;
	jmp	.L68	#
.L67:
# /usr/include/c++/13/bits/allocator.h:210: 	__allocator_base<_Tp>::deallocate(__p, __n);
	movq	-8(%rbp), %rdx	# __n, tmp90
	movq	-16(%rbp), %rcx	# __p, tmp91
	movq	-24(%rbp), %rax	# this, tmp92
	movq	%rcx, %rsi	# tmp91,
	movq	%rax, %rdi	# tmp92,
	call	_ZNSt15__new_allocatorISt10unique_ptrI5ShapeSt14default_deleteIS1_EEE10deallocateEPS4_m	#
.L68:
# /usr/include/c++/13/bits/alloc_traits.h:517:       { __a.deallocate(__p, __n); }
	nop	
.L69:
# /usr/include/c++/13/bits/stl_vector.h:391:       }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4183:
	.size	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE13_M_deallocateEPS4_m, .-_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE13_M_deallocateEPS4_m
	.section	.text._ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE19_M_get_Tp_allocatorEv,"axG",@progbits,_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE19_M_get_Tp_allocatorEv,comdat
	.align 2
	.weak	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE19_M_get_Tp_allocatorEv
	.type	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE19_M_get_Tp_allocatorEv, @function
_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE19_M_get_Tp_allocatorEv:
.LFB4184:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/bits/stl_vector.h:302:       { return this->_M_impl; }
	movq	-8(%rbp), %rax	# this, _2
# /usr/include/c++/13/bits/stl_vector.h:302:       { return this->_M_impl; }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4184:
	.size	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE19_M_get_Tp_allocatorEv, .-_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE19_M_get_Tp_allocatorEv
	.section	.text._ZNSt15__uniq_ptr_dataI6CircleSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EEPS0_,"axG",@progbits,_ZNSt15__uniq_ptr_dataI6CircleSt14default_deleteIS0_ELb1ELb1EECI5St15__uniq_ptr_implIS0_S2_EEPS0_,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_dataI6CircleSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EEPS0_
	.type	_ZNSt15__uniq_ptr_dataI6CircleSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EEPS0_, @function
_ZNSt15__uniq_ptr_dataI6CircleSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EEPS0_:
.LFB4188:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# D.83055, D.83055
# /usr/include/c++/13/bits/unique_ptr.h:241:       using __uniq_ptr_impl<_Tp, _Dp>::__uniq_ptr_impl;
	movq	-8(%rbp), %rax	# this, _1
	movq	-16(%rbp), %rdx	# D.83055, _2
	movq	%rdx, %rsi	# _2,
	movq	%rax, %rdi	# _1,
	call	_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EEC2EPS0_	#
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4188:
	.size	_ZNSt15__uniq_ptr_dataI6CircleSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EEPS0_, .-_ZNSt15__uniq_ptr_dataI6CircleSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EEPS0_
	.weak	_ZNSt15__uniq_ptr_dataI6CircleSt14default_deleteIS0_ELb1ELb1EECI1St15__uniq_ptr_implIS0_S2_EEPS0_
	.set	_ZNSt15__uniq_ptr_dataI6CircleSt14default_deleteIS0_ELb1ELb1EECI1St15__uniq_ptr_implIS0_S2_EEPS0_,_ZNSt15__uniq_ptr_dataI6CircleSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EEPS0_
	.section	.text._ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EEC2IS2_vEEPS0_,"axG",@progbits,_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EEC5IS2_vEEPS0_,comdat
	.align 2
	.weak	_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EEC2IS2_vEEPS0_
	.type	_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EEC2IS2_vEEPS0_, @function
_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EEC2IS2_vEEPS0_:
.LFB4190:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# __p, __p
# /usr/include/c++/13/bits/unique_ptr.h:318: 	: _M_t(__p)
	movq	-8(%rbp), %rax	# this, _1
	movq	-16(%rbp), %rdx	# __p, tmp83
	movq	%rdx, %rsi	# tmp83,
	movq	%rax, %rdi	# _1,
	call	_ZNSt15__uniq_ptr_dataI6CircleSt14default_deleteIS0_ELb1ELb1EECI1St15__uniq_ptr_implIS0_S2_EEPS0_	#
# /usr/include/c++/13/bits/unique_ptr.h:319:         { }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4190:
	.size	_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EEC2IS2_vEEPS0_, .-_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EEC2IS2_vEEPS0_
	.weak	_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EEC1IS2_vEEPS0_
	.set	_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EEC1IS2_vEEPS0_,_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EEC2IS2_vEEPS0_
	.section	.text._ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE6_M_ptrEv,"axG",@progbits,_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE6_M_ptrEv,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE6_M_ptrEv
	.type	_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE6_M_ptrEv, @function
_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE6_M_ptrEv:
.LFB4192:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/bits/unique_ptr.h:197:       pointer&   _M_ptr() noexcept { return std::get<0>(_M_t); }
	movq	-8(%rbp), %rax	# this, _1
# /usr/include/c++/13/bits/unique_ptr.h:197:       pointer&   _M_ptr() noexcept { return std::get<0>(_M_t); }
	movq	%rax, %rdi	# _1,
	call	_ZSt3getILm0EJP6CircleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_	#
# /usr/include/c++/13/bits/unique_ptr.h:197:       pointer&   _M_ptr() noexcept { return std::get<0>(_M_t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4192:
	.size	_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE6_M_ptrEv, .-_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE6_M_ptrEv
	.section	.text._ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EE11get_deleterEv,"axG",@progbits,_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EE11get_deleterEv,comdat
	.align 2
	.weak	_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EE11get_deleterEv
	.type	_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EE11get_deleterEv, @function
_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EE11get_deleterEv:
.LFB4193:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/bits/unique_ptr.h:476:       { return _M_t._M_deleter(); }
	movq	-8(%rbp), %rax	# this, _1
	movq	%rax, %rdi	# _1,
	call	_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE10_M_deleterEv	#
# /usr/include/c++/13/bits/unique_ptr.h:476:       { return _M_t._M_deleter(); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4193:
	.size	_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EE11get_deleterEv, .-_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EE11get_deleterEv
	.section	.text._ZSt4moveIRP6CircleEONSt16remove_referenceIT_E4typeEOS4_,"axG",@progbits,_ZSt4moveIRP6CircleEONSt16remove_referenceIT_E4typeEOS4_,comdat
	.weak	_ZSt4moveIRP6CircleEONSt16remove_referenceIT_E4typeEOS4_
	.type	_ZSt4moveIRP6CircleEONSt16remove_referenceIT_E4typeEOS4_, @function
_ZSt4moveIRP6CircleEONSt16remove_referenceIT_E4typeEOS4_:
.LFB4194:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/bits/move.h:98:     { return static_cast<typename std::remove_reference<_Tp>::type&&>(__t); }
	movq	-8(%rbp), %rax	# __t, _2
# /usr/include/c++/13/bits/move.h:98:     { return static_cast<typename std::remove_reference<_Tp>::type&&>(__t); }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4194:
	.size	_ZSt4moveIRP6CircleEONSt16remove_referenceIT_E4typeEOS4_, .-_ZSt4moveIRP6CircleEONSt16remove_referenceIT_E4typeEOS4_
	.section	.text._ZN6CircleD2Ev,"axG",@progbits,_ZN6CircleD5Ev,comdat
	.align 2
	.weak	_ZN6CircleD2Ev
	.type	_ZN6CircleD2Ev, @function
_ZN6CircleD2Ev:
.LFB4197:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:15: class Circle : public Shape {
	leaq	16+_ZTV6Circle(%rip), %rdx	#, _1
	movq	-8(%rbp), %rax	# this, tmp84
	movq	%rdx, (%rax)	# _1, this_4(D)->D.78928._vptr.Shape
	movq	-8(%rbp), %rax	# this, _2
	movq	%rax, %rdi	# _2,
	call	_ZN5ShapeD2Ev	#
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4197:
	.size	_ZN6CircleD2Ev, .-_ZN6CircleD2Ev
	.weak	_ZN6CircleD1Ev
	.set	_ZN6CircleD1Ev,_ZN6CircleD2Ev
	.section	.text._ZN6CircleD0Ev,"axG",@progbits,_ZN6CircleD5Ev,comdat
	.align 2
	.weak	_ZN6CircleD0Ev
	.type	_ZN6CircleD0Ev, @function
_ZN6CircleD0Ev:
.LFB4199:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:15: class Circle : public Shape {
	movq	-8(%rbp), %rax	# this, tmp82
	movq	%rax, %rdi	# tmp82,
	call	_ZN6CircleD1Ev	#
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:15: class Circle : public Shape {
	movq	-8(%rbp), %rax	# this, tmp83
	movl	$8, %esi	#,
	movq	%rax, %rdi	# tmp83,
	call	_ZdlPvm@PLT	#
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:15: class Circle : public Shape {
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4199:
	.size	_ZN6CircleD0Ev, .-_ZN6CircleD0Ev
	.section	.text._ZNKSt14default_deleteI6CircleEclEPS0_,"axG",@progbits,_ZNKSt14default_deleteI6CircleEclEPS0_,comdat
	.align 2
	.weak	_ZNKSt14default_deleteI6CircleEclEPS0_
	.type	_ZNKSt14default_deleteI6CircleEclEPS0_, @function
_ZNKSt14default_deleteI6CircleEclEPS0_:
.LFB4195:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# __ptr, __ptr
# /usr/include/c++/13/bits/unique_ptr.h:99: 	delete __ptr;
	movq	-16(%rbp), %rax	# __ptr, __ptr.15_6
# /usr/include/c++/13/bits/unique_ptr.h:99: 	delete __ptr;
	testq	%rax, %rax	# __ptr.15_6
	je	.L84	#,
# /usr/include/c++/13/bits/unique_ptr.h:99: 	delete __ptr;
	movq	(%rax), %rdx	# __ptr.15_6->D.78928._vptr.Shape, _1
	addq	$8, %rdx	#, _2
	movq	(%rdx), %rdx	# *_2, _3
	movq	%rax, %rdi	# __ptr.15_6,
	call	*%rdx	# _3
.L84:
# /usr/include/c++/13/bits/unique_ptr.h:100:       }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4195:
	.size	_ZNKSt14default_deleteI6CircleEclEPS0_, .-_ZNKSt14default_deleteI6CircleEclEPS0_
	.section	.text._ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EE7releaseEv,"axG",@progbits,_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EE7releaseEv,comdat
	.align 2
	.weak	_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EE7releaseEv
	.type	_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EE7releaseEv, @function
_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EE7releaseEv:
.LFB4200:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/bits/unique_ptr.h:495:       { return _M_t.release(); }
	movq	-8(%rbp), %rax	# this, _1
	movq	%rax, %rdi	# _1,
	call	_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE7releaseEv	#
# /usr/include/c++/13/bits/unique_ptr.h:495:       { return _M_t.release(); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4200:
	.size	_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EE7releaseEv, .-_ZNSt10unique_ptrI6CircleSt14default_deleteIS0_EE7releaseEv
	.section	.text._ZSt7forwardISt14default_deleteI6CircleEEOT_RNSt16remove_referenceIS3_E4typeE,"axG",@progbits,_ZSt7forwardISt14default_deleteI6CircleEEOT_RNSt16remove_referenceIS3_E4typeE,comdat
	.weak	_ZSt7forwardISt14default_deleteI6CircleEEOT_RNSt16remove_referenceIS3_E4typeE
	.type	_ZSt7forwardISt14default_deleteI6CircleEEOT_RNSt16remove_referenceIS3_E4typeE, @function
_ZSt7forwardISt14default_deleteI6CircleEEOT_RNSt16remove_referenceIS3_E4typeE:
.LFB4201:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/bits/move.h:71:     { return static_cast<_Tp&&>(__t); }
	movq	-8(%rbp), %rax	# __t, _2
# /usr/include/c++/13/bits/move.h:71:     { return static_cast<_Tp&&>(__t); }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4201:
	.size	_ZSt7forwardISt14default_deleteI6CircleEEOT_RNSt16remove_referenceIS3_E4typeE, .-_ZSt7forwardISt14default_deleteI6CircleEEOT_RNSt16remove_referenceIS3_E4typeE
	.section	.text._ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2IS1_I6CircleEEEPS0_OT_,"axG",@progbits,_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC5IS1_I6CircleEEEPS0_OT_,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2IS1_I6CircleEEEPS0_OT_
	.type	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2IS1_I6CircleEEEPS0_OT_, @function
_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2IS1_I6CircleEEEPS0_OT_:
.LFB4209:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$40, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)	# this, this
	movq	%rsi, -32(%rbp)	# __p, __p
	movq	%rdx, -40(%rbp)	# __d, __d
# /usr/include/c++/13/bits/unique_ptr.h:181: 	: _M_t(__p, std::forward<_Del>(__d)) { }
	movq	-24(%rbp), %rbx	# this, _1
	movq	-40(%rbp), %rax	# __d, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZSt7forwardISt14default_deleteI6CircleEEOT_RNSt16remove_referenceIS3_E4typeE	#
	movq	%rax, %rdx	#, _2
# /usr/include/c++/13/bits/unique_ptr.h:181: 	: _M_t(__p, std::forward<_Del>(__d)) { }
	leaq	-32(%rbp), %rax	#, tmp85
	movq	%rax, %rsi	# tmp85,
	movq	%rbx, %rdi	# _1,
	call	_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC1IRS1_S2_I6CircleELb1EEEOT_OT0_	#
# /usr/include/c++/13/bits/unique_ptr.h:181: 	: _M_t(__p, std::forward<_Del>(__d)) { }
	nop	
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4209:
	.size	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2IS1_I6CircleEEEPS0_OT_, .-_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2IS1_I6CircleEEEPS0_OT_
	.weak	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC1IS1_I6CircleEEEPS0_OT_
	.set	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC1IS1_I6CircleEEEPS0_OT_,_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2IS1_I6CircleEEEPS0_OT_
	.section	.text._ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE6_M_ptrEv,"axG",@progbits,_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE6_M_ptrEv,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE6_M_ptrEv
	.type	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE6_M_ptrEv, @function
_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE6_M_ptrEv:
.LFB4211:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/bits/unique_ptr.h:197:       pointer&   _M_ptr() noexcept { return std::get<0>(_M_t); }
	movq	-8(%rbp), %rax	# this, _1
# /usr/include/c++/13/bits/unique_ptr.h:197:       pointer&   _M_ptr() noexcept { return std::get<0>(_M_t); }
	movq	%rax, %rdi	# _1,
	call	_ZSt3getILm0EJP5ShapeSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_	#
# /usr/include/c++/13/bits/unique_ptr.h:197:       pointer&   _M_ptr() noexcept { return std::get<0>(_M_t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4211:
	.size	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE6_M_ptrEv, .-_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE6_M_ptrEv
	.section	.text._ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EE11get_deleterEv,"axG",@progbits,_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EE11get_deleterEv,comdat
	.align 2
	.weak	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EE11get_deleterEv
	.type	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EE11get_deleterEv, @function
_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EE11get_deleterEv:
.LFB4212:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/bits/unique_ptr.h:476:       { return _M_t._M_deleter(); }
	movq	-8(%rbp), %rax	# this, _1
	movq	%rax, %rdi	# _1,
	call	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE10_M_deleterEv	#
# /usr/include/c++/13/bits/unique_ptr.h:476:       { return _M_t._M_deleter(); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4212:
	.size	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EE11get_deleterEv, .-_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EE11get_deleterEv
	.section	.text._ZSt4moveIRP5ShapeEONSt16remove_referenceIT_E4typeEOS4_,"axG",@progbits,_ZSt4moveIRP5ShapeEONSt16remove_referenceIT_E4typeEOS4_,comdat
	.weak	_ZSt4moveIRP5ShapeEONSt16remove_referenceIT_E4typeEOS4_
	.type	_ZSt4moveIRP5ShapeEONSt16remove_referenceIT_E4typeEOS4_, @function
_ZSt4moveIRP5ShapeEONSt16remove_referenceIT_E4typeEOS4_:
.LFB4213:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/bits/move.h:98:     { return static_cast<typename std::remove_reference<_Tp>::type&&>(__t); }
	movq	-8(%rbp), %rax	# __t, _2
# /usr/include/c++/13/bits/move.h:98:     { return static_cast<typename std::remove_reference<_Tp>::type&&>(__t); }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4213:
	.size	_ZSt4moveIRP5ShapeEONSt16remove_referenceIT_E4typeEOS4_, .-_ZSt4moveIRP5ShapeEONSt16remove_referenceIT_E4typeEOS4_
	.section	.text._ZNKSt14default_deleteI5ShapeEclEPS0_,"axG",@progbits,_ZNKSt14default_deleteI5ShapeEclEPS0_,comdat
	.align 2
	.weak	_ZNKSt14default_deleteI5ShapeEclEPS0_
	.type	_ZNKSt14default_deleteI5ShapeEclEPS0_, @function
_ZNKSt14default_deleteI5ShapeEclEPS0_:
.LFB4214:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# __ptr, __ptr
# /usr/include/c++/13/bits/unique_ptr.h:99: 	delete __ptr;
	movq	-16(%rbp), %rax	# __ptr, __ptr.16_6
# /usr/include/c++/13/bits/unique_ptr.h:99: 	delete __ptr;
	testq	%rax, %rax	# __ptr.16_6
	je	.L98	#,
# /usr/include/c++/13/bits/unique_ptr.h:99: 	delete __ptr;
	movq	(%rax), %rdx	# __ptr.16_6->_vptr.Shape, _1
	addq	$8, %rdx	#, _2
	movq	(%rdx), %rdx	# *_2, _3
	movq	%rax, %rdi	# __ptr.16_6,
	call	*%rdx	# _3
.L98:
# /usr/include/c++/13/bits/unique_ptr.h:100:       }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4214:
	.size	_ZNKSt14default_deleteI5ShapeEclEPS0_, .-_ZNKSt14default_deleteI5ShapeEclEPS0_
	.section	.text._ZSt4moveIRSt10unique_ptrI5ShapeSt14default_deleteIS1_EEEONSt16remove_referenceIT_E4typeEOS7_,"axG",@progbits,_ZSt4moveIRSt10unique_ptrI5ShapeSt14default_deleteIS1_EEEONSt16remove_referenceIT_E4typeEOS7_,comdat
	.weak	_ZSt4moveIRSt10unique_ptrI5ShapeSt14default_deleteIS1_EEEONSt16remove_referenceIT_E4typeEOS7_
	.type	_ZSt4moveIRSt10unique_ptrI5ShapeSt14default_deleteIS1_EEEONSt16remove_referenceIT_E4typeEOS7_, @function
_ZSt4moveIRSt10unique_ptrI5ShapeSt14default_deleteIS1_EEEONSt16remove_referenceIT_E4typeEOS7_:
.LFB4215:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/bits/move.h:98:     { return static_cast<typename std::remove_reference<_Tp>::type&&>(__t); }
	movq	-8(%rbp), %rax	# __t, _2
# /usr/include/c++/13/bits/move.h:98:     { return static_cast<typename std::remove_reference<_Tp>::type&&>(__t); }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4215:
	.size	_ZSt4moveIRSt10unique_ptrI5ShapeSt14default_deleteIS1_EEEONSt16remove_referenceIT_E4typeEOS7_, .-_ZSt4moveIRSt10unique_ptrI5ShapeSt14default_deleteIS1_EEEONSt16remove_referenceIT_E4typeEOS7_
	.section	.text._ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12emplace_backIJS4_EEERS4_DpOT_,"axG",@progbits,_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12emplace_backIJS4_EEERS4_DpOT_,comdat
	.align 2
	.weak	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12emplace_backIJS4_EEERS4_DpOT_
	.type	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12emplace_backIJS4_EEERS4_DpOT_, @function
_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12emplace_backIJS4_EEERS4_DpOT_:
.LFB4216:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$56, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -56(%rbp)	# this, this
	movq	%rsi, -64(%rbp)	# __args#0, __args#0
# /usr/include/c++/13/bits/vector.tcc:114: 	if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
	movq	-56(%rbp), %rax	# this, tmp94
	movq	8(%rax), %rdx	# this_11(D)->D.80067._M_impl.D.79372._M_finish, _1
# /usr/include/c++/13/bits/vector.tcc:114: 	if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
	movq	-56(%rbp), %rax	# this, tmp95
	movq	16(%rax), %rax	# this_11(D)->D.80067._M_impl.D.79372._M_end_of_storage, _2
# /usr/include/c++/13/bits/vector.tcc:114: 	if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
	cmpq	%rax, %rdx	# _2, _1
	je	.L102	#,
# /usr/include/c++/13/bits/vector.tcc:117: 	    _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish,
	movq	-64(%rbp), %rax	# __args#0, tmp96
	movq	%rax, %rdi	# tmp96,
	call	_ZSt7forwardISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEOT_RNSt16remove_referenceIS5_E4typeE	#
# /usr/include/c++/13/bits/vector.tcc:117: 	    _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish,
	movq	-56(%rbp), %rdx	# this, tmp97
	movq	8(%rdx), %rdx	# this_11(D)->D.80067._M_impl.D.79372._M_finish, _4
# /usr/include/c++/13/bits/vector.tcc:117: 	    _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish,
	movq	-56(%rbp), %rcx	# this, _5
	movq	%rcx, -40(%rbp)	# _5, __a
	movq	%rdx, -32(%rbp)	# _4, __p
	movq	%rax, -24(%rbp)	# _3, __args#0
# /usr/include/c++/13/bits/alloc_traits.h:540: 	  std::construct_at(__p, std::forward<_Args>(__args)...);
	movq	-24(%rbp), %rax	# __args#0, tmp98
	movq	%rax, %rdi	# tmp98,
	call	_ZSt7forwardISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEOT_RNSt16remove_referenceIS5_E4typeE	#
	movq	%rax, %rdx	#, _23
# /usr/include/c++/13/bits/alloc_traits.h:540: 	  std::construct_at(__p, std::forward<_Args>(__args)...);
	movq	-32(%rbp), %rax	# __p, tmp99
	movq	%rdx, %rsi	# _23,
	movq	%rax, %rdi	# tmp99,
	call	_ZSt12construct_atISt10unique_ptrI5ShapeSt14default_deleteIS1_EEJS4_EEDTgsnwcvPvLi0E_T_pispcl7declvalIT0_EEEEPS6_DpOS7_	#
# /usr/include/c++/13/bits/alloc_traits.h:542: 	}
	nop	
# /usr/include/c++/13/bits/vector.tcc:119: 	    ++this->_M_impl._M_finish;
	movq	-56(%rbp), %rax	# this, tmp100
	movq	8(%rax), %rax	# this_11(D)->D.80067._M_impl.D.79372._M_finish, _6
# /usr/include/c++/13/bits/vector.tcc:119: 	    ++this->_M_impl._M_finish;
	leaq	8(%rax), %rdx	#, _7
	movq	-56(%rbp), %rax	# this, tmp101
	movq	%rdx, 8(%rax)	# _7, this_11(D)->D.80067._M_impl.D.79372._M_finish
	jmp	.L103	#
.L102:
# /usr/include/c++/13/bits/vector.tcc:123: 	  _M_realloc_insert(end(), std::forward<_Args>(__args)...);
	movq	-64(%rbp), %rax	# __args#0, tmp102
	movq	%rax, %rdi	# tmp102,
	call	_ZSt7forwardISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEOT_RNSt16remove_referenceIS5_E4typeE	#
	movq	%rax, %rbx	#, _8
# /usr/include/c++/13/bits/vector.tcc:123: 	  _M_realloc_insert(end(), std::forward<_Args>(__args)...);
	movq	-56(%rbp), %rax	# this, tmp103
	movq	%rax, %rdi	# tmp103,
	call	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE3endEv	#
	movq	%rax, %rcx	#, D.99080
# /usr/include/c++/13/bits/vector.tcc:123: 	  _M_realloc_insert(end(), std::forward<_Args>(__args)...);
	movq	-56(%rbp), %rax	# this, tmp104
	movq	%rbx, %rdx	# _8,
	movq	%rcx, %rsi	# D.99080,
	movq	%rax, %rdi	# tmp104,
	call	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE17_M_realloc_insertIJS4_EEEvN9__gnu_cxx17__normal_iteratorIPS4_S6_EEDpOT_	#
.L103:
# /usr/include/c++/13/bits/vector.tcc:125: 	return back();
	movq	-56(%rbp), %rax	# this, tmp105
	movq	%rax, %rdi	# tmp105,
	call	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE4backEv	#
# /usr/include/c++/13/bits/vector.tcc:127:       }
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4216:
	.size	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12emplace_backIJS4_EEERS4_DpOT_, .-_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12emplace_backIJS4_EEERS4_DpOT_
	.section	.text._ZNSt15__uniq_ptr_dataI9RectangleSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EEPS0_,"axG",@progbits,_ZNSt15__uniq_ptr_dataI9RectangleSt14default_deleteIS0_ELb1ELb1EECI5St15__uniq_ptr_implIS0_S2_EEPS0_,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_dataI9RectangleSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EEPS0_
	.type	_ZNSt15__uniq_ptr_dataI9RectangleSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EEPS0_, @function
_ZNSt15__uniq_ptr_dataI9RectangleSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EEPS0_:
.LFB4220:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# D.89168, D.89168
# /usr/include/c++/13/bits/unique_ptr.h:241:       using __uniq_ptr_impl<_Tp, _Dp>::__uniq_ptr_impl;
	movq	-8(%rbp), %rax	# this, _1
	movq	-16(%rbp), %rdx	# D.89168, _2
	movq	%rdx, %rsi	# _2,
	movq	%rax, %rdi	# _1,
	call	_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EEC2EPS0_	#
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4220:
	.size	_ZNSt15__uniq_ptr_dataI9RectangleSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EEPS0_, .-_ZNSt15__uniq_ptr_dataI9RectangleSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EEPS0_
	.weak	_ZNSt15__uniq_ptr_dataI9RectangleSt14default_deleteIS0_ELb1ELb1EECI1St15__uniq_ptr_implIS0_S2_EEPS0_
	.set	_ZNSt15__uniq_ptr_dataI9RectangleSt14default_deleteIS0_ELb1ELb1EECI1St15__uniq_ptr_implIS0_S2_EEPS0_,_ZNSt15__uniq_ptr_dataI9RectangleSt14default_deleteIS0_ELb1ELb1EECI2St15__uniq_ptr_implIS0_S2_EEPS0_
	.section	.text._ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EEC2IS2_vEEPS0_,"axG",@progbits,_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EEC5IS2_vEEPS0_,comdat
	.align 2
	.weak	_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EEC2IS2_vEEPS0_
	.type	_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EEC2IS2_vEEPS0_, @function
_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EEC2IS2_vEEPS0_:
.LFB4222:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# __p, __p
# /usr/include/c++/13/bits/unique_ptr.h:318: 	: _M_t(__p)
	movq	-8(%rbp), %rax	# this, _1
	movq	-16(%rbp), %rdx	# __p, tmp83
	movq	%rdx, %rsi	# tmp83,
	movq	%rax, %rdi	# _1,
	call	_ZNSt15__uniq_ptr_dataI9RectangleSt14default_deleteIS0_ELb1ELb1EECI1St15__uniq_ptr_implIS0_S2_EEPS0_	#
# /usr/include/c++/13/bits/unique_ptr.h:319:         { }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4222:
	.size	_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EEC2IS2_vEEPS0_, .-_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EEC2IS2_vEEPS0_
	.weak	_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EEC1IS2_vEEPS0_
	.set	_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EEC1IS2_vEEPS0_,_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EEC2IS2_vEEPS0_
	.section	.text._ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE6_M_ptrEv,"axG",@progbits,_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE6_M_ptrEv,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE6_M_ptrEv
	.type	_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE6_M_ptrEv, @function
_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE6_M_ptrEv:
.LFB4224:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/bits/unique_ptr.h:197:       pointer&   _M_ptr() noexcept { return std::get<0>(_M_t); }
	movq	-8(%rbp), %rax	# this, _1
# /usr/include/c++/13/bits/unique_ptr.h:197:       pointer&   _M_ptr() noexcept { return std::get<0>(_M_t); }
	movq	%rax, %rdi	# _1,
	call	_ZSt3getILm0EJP9RectangleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_	#
# /usr/include/c++/13/bits/unique_ptr.h:197:       pointer&   _M_ptr() noexcept { return std::get<0>(_M_t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4224:
	.size	_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE6_M_ptrEv, .-_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE6_M_ptrEv
	.section	.text._ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EE11get_deleterEv,"axG",@progbits,_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EE11get_deleterEv,comdat
	.align 2
	.weak	_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EE11get_deleterEv
	.type	_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EE11get_deleterEv, @function
_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EE11get_deleterEv:
.LFB4225:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/bits/unique_ptr.h:476:       { return _M_t._M_deleter(); }
	movq	-8(%rbp), %rax	# this, _1
	movq	%rax, %rdi	# _1,
	call	_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE10_M_deleterEv	#
# /usr/include/c++/13/bits/unique_ptr.h:476:       { return _M_t._M_deleter(); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4225:
	.size	_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EE11get_deleterEv, .-_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EE11get_deleterEv
	.section	.text._ZSt4moveIRP9RectangleEONSt16remove_referenceIT_E4typeEOS4_,"axG",@progbits,_ZSt4moveIRP9RectangleEONSt16remove_referenceIT_E4typeEOS4_,comdat
	.weak	_ZSt4moveIRP9RectangleEONSt16remove_referenceIT_E4typeEOS4_
	.type	_ZSt4moveIRP9RectangleEONSt16remove_referenceIT_E4typeEOS4_, @function
_ZSt4moveIRP9RectangleEONSt16remove_referenceIT_E4typeEOS4_:
.LFB4226:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/bits/move.h:98:     { return static_cast<typename std::remove_reference<_Tp>::type&&>(__t); }
	movq	-8(%rbp), %rax	# __t, _2
# /usr/include/c++/13/bits/move.h:98:     { return static_cast<typename std::remove_reference<_Tp>::type&&>(__t); }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4226:
	.size	_ZSt4moveIRP9RectangleEONSt16remove_referenceIT_E4typeEOS4_, .-_ZSt4moveIRP9RectangleEONSt16remove_referenceIT_E4typeEOS4_
	.section	.text._ZN9RectangleD2Ev,"axG",@progbits,_ZN9RectangleD5Ev,comdat
	.align 2
	.weak	_ZN9RectangleD2Ev
	.type	_ZN9RectangleD2Ev, @function
_ZN9RectangleD2Ev:
.LFB4229:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:20: class Rectangle : public Shape {
	leaq	16+_ZTV9Rectangle(%rip), %rdx	#, _1
	movq	-8(%rbp), %rax	# this, tmp84
	movq	%rdx, (%rax)	# _1, this_4(D)->D.78950._vptr.Shape
	movq	-8(%rbp), %rax	# this, _2
	movq	%rax, %rdi	# _2,
	call	_ZN5ShapeD2Ev	#
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4229:
	.size	_ZN9RectangleD2Ev, .-_ZN9RectangleD2Ev
	.weak	_ZN9RectangleD1Ev
	.set	_ZN9RectangleD1Ev,_ZN9RectangleD2Ev
	.section	.text._ZN9RectangleD0Ev,"axG",@progbits,_ZN9RectangleD5Ev,comdat
	.align 2
	.weak	_ZN9RectangleD0Ev
	.type	_ZN9RectangleD0Ev, @function
_ZN9RectangleD0Ev:
.LFB4231:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:20: class Rectangle : public Shape {
	movq	-8(%rbp), %rax	# this, tmp82
	movq	%rax, %rdi	# tmp82,
	call	_ZN9RectangleD1Ev	#
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:20: class Rectangle : public Shape {
	movq	-8(%rbp), %rax	# this, tmp83
	movl	$8, %esi	#,
	movq	%rax, %rdi	# tmp83,
	call	_ZdlPvm@PLT	#
# /home/r/Desktop/lecpp/src/45_rtti_typeid_address.cpp:20: class Rectangle : public Shape {
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4231:
	.size	_ZN9RectangleD0Ev, .-_ZN9RectangleD0Ev
	.section	.text._ZNKSt14default_deleteI9RectangleEclEPS0_,"axG",@progbits,_ZNKSt14default_deleteI9RectangleEclEPS0_,comdat
	.align 2
	.weak	_ZNKSt14default_deleteI9RectangleEclEPS0_
	.type	_ZNKSt14default_deleteI9RectangleEclEPS0_, @function
_ZNKSt14default_deleteI9RectangleEclEPS0_:
.LFB4227:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# __ptr, __ptr
# /usr/include/c++/13/bits/unique_ptr.h:99: 	delete __ptr;
	movq	-16(%rbp), %rax	# __ptr, __ptr.17_6
# /usr/include/c++/13/bits/unique_ptr.h:99: 	delete __ptr;
	testq	%rax, %rax	# __ptr.17_6
	je	.L117	#,
# /usr/include/c++/13/bits/unique_ptr.h:99: 	delete __ptr;
	movq	(%rax), %rdx	# __ptr.17_6->D.78950._vptr.Shape, _1
	addq	$8, %rdx	#, _2
	movq	(%rdx), %rdx	# *_2, _3
	movq	%rax, %rdi	# __ptr.17_6,
	call	*%rdx	# _3
.L117:
# /usr/include/c++/13/bits/unique_ptr.h:100:       }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4227:
	.size	_ZNKSt14default_deleteI9RectangleEclEPS0_, .-_ZNKSt14default_deleteI9RectangleEclEPS0_
	.section	.text._ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EE7releaseEv,"axG",@progbits,_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EE7releaseEv,comdat
	.align 2
	.weak	_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EE7releaseEv
	.type	_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EE7releaseEv, @function
_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EE7releaseEv:
.LFB4232:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/bits/unique_ptr.h:495:       { return _M_t.release(); }
	movq	-8(%rbp), %rax	# this, _1
	movq	%rax, %rdi	# _1,
	call	_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE7releaseEv	#
# /usr/include/c++/13/bits/unique_ptr.h:495:       { return _M_t.release(); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4232:
	.size	_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EE7releaseEv, .-_ZNSt10unique_ptrI9RectangleSt14default_deleteIS0_EE7releaseEv
	.section	.text._ZSt7forwardISt14default_deleteI9RectangleEEOT_RNSt16remove_referenceIS3_E4typeE,"axG",@progbits,_ZSt7forwardISt14default_deleteI9RectangleEEOT_RNSt16remove_referenceIS3_E4typeE,comdat
	.weak	_ZSt7forwardISt14default_deleteI9RectangleEEOT_RNSt16remove_referenceIS3_E4typeE
	.type	_ZSt7forwardISt14default_deleteI9RectangleEEOT_RNSt16remove_referenceIS3_E4typeE, @function
_ZSt7forwardISt14default_deleteI9RectangleEEOT_RNSt16remove_referenceIS3_E4typeE:
.LFB4233:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/bits/move.h:71:     { return static_cast<_Tp&&>(__t); }
	movq	-8(%rbp), %rax	# __t, _2
# /usr/include/c++/13/bits/move.h:71:     { return static_cast<_Tp&&>(__t); }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4233:
	.size	_ZSt7forwardISt14default_deleteI9RectangleEEOT_RNSt16remove_referenceIS3_E4typeE, .-_ZSt7forwardISt14default_deleteI9RectangleEEOT_RNSt16remove_referenceIS3_E4typeE
	.section	.text._ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2IS1_I9RectangleEEEPS0_OT_,"axG",@progbits,_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC5IS1_I9RectangleEEEPS0_OT_,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2IS1_I9RectangleEEEPS0_OT_
	.type	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2IS1_I9RectangleEEEPS0_OT_, @function
_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2IS1_I9RectangleEEEPS0_OT_:
.LFB4238:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$40, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)	# this, this
	movq	%rsi, -32(%rbp)	# __p, __p
	movq	%rdx, -40(%rbp)	# __d, __d
# /usr/include/c++/13/bits/unique_ptr.h:181: 	: _M_t(__p, std::forward<_Del>(__d)) { }
	movq	-24(%rbp), %rbx	# this, _1
	movq	-40(%rbp), %rax	# __d, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZSt7forwardISt14default_deleteI9RectangleEEOT_RNSt16remove_referenceIS3_E4typeE	#
	movq	%rax, %rdx	#, _2
# /usr/include/c++/13/bits/unique_ptr.h:181: 	: _M_t(__p, std::forward<_Del>(__d)) { }
	leaq	-32(%rbp), %rax	#, tmp85
	movq	%rax, %rsi	# tmp85,
	movq	%rbx, %rdi	# _1,
	call	_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC1IRS1_S2_I9RectangleELb1EEEOT_OT0_	#
# /usr/include/c++/13/bits/unique_ptr.h:181: 	: _M_t(__p, std::forward<_Del>(__d)) { }
	nop	
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4238:
	.size	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2IS1_I9RectangleEEEPS0_OT_, .-_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2IS1_I9RectangleEEEPS0_OT_
	.weak	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC1IS1_I9RectangleEEEPS0_OT_
	.set	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC1IS1_I9RectangleEEEPS0_OT_,_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2IS1_I9RectangleEEEPS0_OT_
	.section	.text._ZN9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEC2ERKS6_,"axG",@progbits,_ZN9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEC5ERKS6_,comdat
	.align 2
	.weak	_ZN9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEC2ERKS6_
	.type	_ZN9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEC2ERKS6_, @function
_ZN9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEC2ERKS6_:
.LFB4241:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# __i, __i
# /usr/include/c++/13/bits/stl_iterator.h:1077:       : _M_current(__i) { }
	movq	-16(%rbp), %rax	# __i, tmp83
	movq	(%rax), %rdx	# *__i_5(D), _1
	movq	-8(%rbp), %rax	# this, tmp84
	movq	%rdx, (%rax)	# _1, this_3(D)->_M_current
# /usr/include/c++/13/bits/stl_iterator.h:1077:       : _M_current(__i) { }
	nop	
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4241:
	.size	_ZN9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEC2ERKS6_, .-_ZN9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEC2ERKS6_
	.weak	_ZN9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEC1ERKS6_
	.set	_ZN9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEC1ERKS6_,_ZN9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEC2ERKS6_
	.section	.text._ZNKSt10unique_ptrI5ShapeSt14default_deleteIS0_EE3getEv,"axG",@progbits,_ZNKSt10unique_ptrI5ShapeSt14default_deleteIS0_EE3getEv,comdat
	.align 2
	.weak	_ZNKSt10unique_ptrI5ShapeSt14default_deleteIS0_EE3getEv
	.type	_ZNKSt10unique_ptrI5ShapeSt14default_deleteIS0_EE3getEv, @function
_ZNKSt10unique_ptrI5ShapeSt14default_deleteIS0_EE3getEv:
.LFB4243:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/bits/unique_ptr.h:470:       { return _M_t._M_ptr(); }
	movq	-8(%rbp), %rax	# this, _1
	movq	%rax, %rdi	# _1,
	call	_ZNKSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE6_M_ptrEv	#
# /usr/include/c++/13/bits/unique_ptr.h:470:       { return _M_t._M_ptr(); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4243:
	.size	_ZNKSt10unique_ptrI5ShapeSt14default_deleteIS0_EE3getEv, .-_ZNKSt10unique_ptrI5ShapeSt14default_deleteIS0_EE3getEv
	.section	.text._ZSt8_DestroyIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvT_S6_,"axG",@progbits,_ZSt8_DestroyIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvT_S6_,comdat
	.weak	_ZSt8_DestroyIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvT_S6_
	.type	_ZSt8_DestroyIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvT_S6_, @function
_ZSt8_DestroyIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvT_S6_:
.LFB4340:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __first, __first
	movq	%rsi, -16(%rbp)	# __last, __last
# /usr/include/c++/13/bits/stl_construct.h:192:       if (std::__is_constant_evaluated())
	call	_ZSt23__is_constant_evaluatedv	#
# /usr/include/c++/13/bits/stl_construct.h:192:       if (std::__is_constant_evaluated())
	testb	%al, %al	# retval.18_4
	je	.L127	#,
# /usr/include/c++/13/bits/stl_construct.h:193: 	return std::_Destroy_aux<false>::__destroy(__first, __last);
	movq	-16(%rbp), %rdx	# __last, tmp83
	movq	-8(%rbp), %rax	# __first, tmp84
	movq	%rdx, %rsi	# tmp83,
	movq	%rax, %rdi	# tmp84,
	call	_ZNSt12_Destroy_auxILb0EE9__destroyIPSt10unique_ptrI5ShapeSt14default_deleteIS3_EEEEvT_S8_	#
# /usr/include/c++/13/bits/stl_construct.h:193: 	return std::_Destroy_aux<false>::__destroy(__first, __last);
	jmp	.L126	#
.L127:
# /usr/include/c++/13/bits/stl_construct.h:196: 	__destroy(__first, __last);
	movq	-16(%rbp), %rdx	# __last, tmp85
	movq	-8(%rbp), %rax	# __first, tmp86
	movq	%rdx, %rsi	# tmp85,
	movq	%rax, %rdi	# tmp86,
	call	_ZNSt12_Destroy_auxILb0EE9__destroyIPSt10unique_ptrI5ShapeSt14default_deleteIS3_EEEEvT_S8_	#
.L126:
# /usr/include/c++/13/bits/stl_construct.h:197:     }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4340:
	.size	_ZSt8_DestroyIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvT_S6_, .-_ZSt8_DestroyIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvT_S6_
	.section	.text._ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EEC2EPS0_,"axG",@progbits,_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EEC5EPS0_,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EEC2EPS0_
	.type	_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EEC2EPS0_, @function
_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EEC2EPS0_:
.LFB4343:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$24, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)	# this, this
	movq	%rsi, -32(%rbp)	# __p, __p
# /usr/include/c++/13/bits/unique_ptr.h:176:       __uniq_ptr_impl(pointer __p) : _M_t() { _M_ptr() = __p; }
	movq	-24(%rbp), %rax	# this, _1
	movq	%rax, %rdi	# _1,
	call	_ZNSt5tupleIJP6CircleSt14default_deleteIS0_EEEC1ILb1ELb1EEEv	#
# /usr/include/c++/13/bits/unique_ptr.h:176:       __uniq_ptr_impl(pointer __p) : _M_t() { _M_ptr() = __p; }
	movq	-32(%rbp), %rbx	# __p, __p.1_2
# /usr/include/c++/13/bits/unique_ptr.h:176:       __uniq_ptr_impl(pointer __p) : _M_t() { _M_ptr() = __p; }
	movq	-24(%rbp), %rax	# this, tmp85
	movq	%rax, %rdi	# tmp85,
	call	_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE6_M_ptrEv	#
# /usr/include/c++/13/bits/unique_ptr.h:176:       __uniq_ptr_impl(pointer __p) : _M_t() { _M_ptr() = __p; }
	movq	%rbx, (%rax)	# __p.1_2, *_3
# /usr/include/c++/13/bits/unique_ptr.h:176:       __uniq_ptr_impl(pointer __p) : _M_t() { _M_ptr() = __p; }
	nop	
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4343:
	.size	_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EEC2EPS0_, .-_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EEC2EPS0_
	.weak	_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EEC1EPS0_
	.set	_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EEC1EPS0_,_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EEC2EPS0_
	.section	.text._ZSt3getILm0EJP6CircleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_,"axG",@progbits,_ZSt3getILm0EJP6CircleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_,comdat
	.weak	_ZSt3getILm0EJP6CircleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_
	.type	_ZSt3getILm0EJP6CircleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_, @function
_ZSt3getILm0EJP6CircleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_:
.LFB4345:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/tuple:1804:     { return std::__get_helper<__i>(__t); }
	movq	-8(%rbp), %rax	# __t, _1
	movq	%rax, %rdi	# _1,
	call	_ZSt12__get_helperILm0EP6CircleJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE	#
# /usr/include/c++/13/tuple:1804:     { return std::__get_helper<__i>(__t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4345:
	.size	_ZSt3getILm0EJP6CircleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_, .-_ZSt3getILm0EJP6CircleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_
	.section	.text._ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE10_M_deleterEv,"axG",@progbits,_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE10_M_deleterEv,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE10_M_deleterEv
	.type	_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE10_M_deleterEv, @function
_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE10_M_deleterEv:
.LFB4346:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/bits/unique_ptr.h:201:       _Dp&       _M_deleter() noexcept { return std::get<1>(_M_t); }
	movq	-8(%rbp), %rax	# this, _1
# /usr/include/c++/13/bits/unique_ptr.h:201:       _Dp&       _M_deleter() noexcept { return std::get<1>(_M_t); }
	movq	%rax, %rdi	# _1,
	call	_ZSt3getILm1EJP6CircleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_	#
# /usr/include/c++/13/bits/unique_ptr.h:201:       _Dp&       _M_deleter() noexcept { return std::get<1>(_M_t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4346:
	.size	_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE10_M_deleterEv, .-_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE10_M_deleterEv
	.section	.text._ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE7releaseEv,"axG",@progbits,_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE7releaseEv,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE7releaseEv
	.type	_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE7releaseEv, @function
_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE7releaseEv:
.LFB4347:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$32, %rsp	#,
	movq	%rdi, -24(%rbp)	# this, this
# /usr/include/c++/13/bits/unique_ptr.h:217: 	pointer __p = _M_ptr();
	movq	-24(%rbp), %rax	# this, tmp86
	movq	%rax, %rdi	# tmp86,
	call	_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE6_M_ptrEv	#
# /usr/include/c++/13/bits/unique_ptr.h:217: 	pointer __p = _M_ptr();
	movq	(%rax), %rax	# *_1, tmp87
	movq	%rax, -8(%rbp)	# tmp87, __p
# /usr/include/c++/13/bits/unique_ptr.h:218: 	_M_ptr() = nullptr;
	movq	-24(%rbp), %rax	# this, tmp88
	movq	%rax, %rdi	# tmp88,
	call	_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE6_M_ptrEv	#
# /usr/include/c++/13/bits/unique_ptr.h:218: 	_M_ptr() = nullptr;
	movq	$0, (%rax)	#, *_2
# /usr/include/c++/13/bits/unique_ptr.h:219: 	return __p;
	movq	-8(%rbp), %rax	# __p, _9
# /usr/include/c++/13/bits/unique_ptr.h:220:       }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4347:
	.size	_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE7releaseEv, .-_ZNSt15__uniq_ptr_implI6CircleSt14default_deleteIS0_EE7releaseEv
	.section	.text._ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC2IRS1_S2_I6CircleELb1EEEOT_OT0_,"axG",@progbits,_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC5IRS1_S2_I6CircleELb1EEEOT_OT0_,comdat
	.align 2
	.weak	_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC2IRS1_S2_I6CircleELb1EEEOT_OT0_
	.type	_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC2IRS1_S2_I6CircleELb1EEEOT_OT0_, @function
_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC2IRS1_S2_I6CircleELb1EEEOT_OT0_:
.LFB4349:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA4349
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%r12	#
	pushq	%rbx	#
	subq	$32, %rsp	#,
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -24(%rbp)	# this, this
	movq	%rsi, -32(%rbp)	# __a1, __a1
	movq	%rdx, -40(%rbp)	# __a2, __a2
# /usr/include/c++/13/tuple:1347: 	: _Inherited(std::forward<_U1>(__a1), std::forward<_U2>(__a2)) { }
	movq	-24(%rbp), %rbx	# this, _1
	movq	-40(%rbp), %rax	# __a2, tmp85
	movq	%rax, %rdi	# tmp85,
	call	_ZSt7forwardISt14default_deleteI6CircleEEOT_RNSt16remove_referenceIS3_E4typeE	#
	movq	%rax, %r12	#, _2
# /usr/include/c++/13/tuple:1347: 	: _Inherited(std::forward<_U1>(__a1), std::forward<_U2>(__a2)) { }
	movq	-32(%rbp), %rax	# __a1, tmp86
	movq	%rax, %rdi	# tmp86,
	call	_ZSt7forwardIRP5ShapeEOT_RNSt16remove_referenceIS3_E4typeE	#
# /usr/include/c++/13/tuple:1347: 	: _Inherited(std::forward<_U1>(__a1), std::forward<_U2>(__a2)) { }
	movq	%r12, %rdx	# _2,
	movq	%rax, %rsi	# _3,
	movq	%rbx, %rdi	# _1,
	call	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2IRS1_JS2_I6CircleEEvEEOT_DpOT0_	#
# /usr/include/c++/13/tuple:1347: 	: _Inherited(std::forward<_U1>(__a1), std::forward<_U2>(__a2)) { }
	nop	
	addq	$32, %rsp	#,
	popq	%rbx	#
	popq	%r12	#
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4349:
	.section	.gcc_except_table
.LLSDA4349:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4349-.LLSDACSB4349
.LLSDACSB4349:
.LLSDACSE4349:
	.section	.text._ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC2IRS1_S2_I6CircleELb1EEEOT_OT0_,"axG",@progbits,_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC5IRS1_S2_I6CircleELb1EEEOT_OT0_,comdat
	.size	_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC2IRS1_S2_I6CircleELb1EEEOT_OT0_, .-_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC2IRS1_S2_I6CircleELb1EEEOT_OT0_
	.weak	_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC1IRS1_S2_I6CircleELb1EEEOT_OT0_
	.set	_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC1IRS1_S2_I6CircleELb1EEEOT_OT0_,_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC2IRS1_S2_I6CircleELb1EEEOT_OT0_
	.section	.text._ZSt3getILm0EJP5ShapeSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_,"axG",@progbits,_ZSt3getILm0EJP5ShapeSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_,comdat
	.weak	_ZSt3getILm0EJP5ShapeSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_
	.type	_ZSt3getILm0EJP5ShapeSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_, @function
_ZSt3getILm0EJP5ShapeSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_:
.LFB4351:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/tuple:1804:     { return std::__get_helper<__i>(__t); }
	movq	-8(%rbp), %rax	# __t, _1
	movq	%rax, %rdi	# _1,
	call	_ZSt12__get_helperILm0EP5ShapeJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE	#
# /usr/include/c++/13/tuple:1804:     { return std::__get_helper<__i>(__t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4351:
	.size	_ZSt3getILm0EJP5ShapeSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_, .-_ZSt3getILm0EJP5ShapeSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_
	.section	.text._ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE10_M_deleterEv,"axG",@progbits,_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE10_M_deleterEv,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE10_M_deleterEv
	.type	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE10_M_deleterEv, @function
_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE10_M_deleterEv:
.LFB4352:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/bits/unique_ptr.h:201:       _Dp&       _M_deleter() noexcept { return std::get<1>(_M_t); }
	movq	-8(%rbp), %rax	# this, _1
# /usr/include/c++/13/bits/unique_ptr.h:201:       _Dp&       _M_deleter() noexcept { return std::get<1>(_M_t); }
	movq	%rax, %rdi	# _1,
	call	_ZSt3getILm1EJP5ShapeSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_	#
# /usr/include/c++/13/bits/unique_ptr.h:201:       _Dp&       _M_deleter() noexcept { return std::get<1>(_M_t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4352:
	.size	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE10_M_deleterEv, .-_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE10_M_deleterEv
	.section	.text._ZSt7forwardISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEOT_RNSt16remove_referenceIS5_E4typeE,"axG",@progbits,_ZSt7forwardISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEOT_RNSt16remove_referenceIS5_E4typeE,comdat
	.weak	_ZSt7forwardISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEOT_RNSt16remove_referenceIS5_E4typeE
	.type	_ZSt7forwardISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEOT_RNSt16remove_referenceIS5_E4typeE, @function
_ZSt7forwardISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEOT_RNSt16remove_referenceIS5_E4typeE:
.LFB4353:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/bits/move.h:71:     { return static_cast<_Tp&&>(__t); }
	movq	-8(%rbp), %rax	# __t, _2
# /usr/include/c++/13/bits/move.h:71:     { return static_cast<_Tp&&>(__t); }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4353:
	.size	_ZSt7forwardISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEOT_RNSt16remove_referenceIS5_E4typeE, .-_ZSt7forwardISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEOT_RNSt16remove_referenceIS5_E4typeE
	.section	.text._ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE4sizeEv,"axG",@progbits,_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE4sizeEv,comdat
	.align 2
	.weak	_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE4sizeEv
	.type	_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE4sizeEv, @function
_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE4sizeEv:
.LFB4357:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/bits/stl_vector.h:993:       { return size_type(this->_M_impl._M_finish - this->_M_impl._M_start); }
	movq	-8(%rbp), %rax	# this, tmp88
	movq	8(%rax), %rdx	# this_6(D)->D.80067._M_impl.D.79372._M_finish, _1
# /usr/include/c++/13/bits/stl_vector.h:993:       { return size_type(this->_M_impl._M_finish - this->_M_impl._M_start); }
	movq	-8(%rbp), %rax	# this, tmp89
	movq	(%rax), %rax	# this_6(D)->D.80067._M_impl.D.79372._M_start, _2
# /usr/include/c++/13/bits/stl_vector.h:993:       { return size_type(this->_M_impl._M_finish - this->_M_impl._M_start); }
	subq	%rax, %rdx	# _2, _3
	movq	%rdx, %rax	# _3, _3
	sarq	$3, %rax	#, _3
# /usr/include/c++/13/bits/stl_vector.h:993:       { return size_type(this->_M_impl._M_finish - this->_M_impl._M_start); }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4357:
	.size	_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE4sizeEv, .-_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE4sizeEv
	.section	.text._ZSt3maxImERKT_S2_S2_,"axG",@progbits,_ZSt3maxImERKT_S2_S2_,comdat
	.weak	_ZSt3maxImERKT_S2_S2_
	.type	_ZSt3maxImERKT_S2_S2_, @function
_ZSt3maxImERKT_S2_S2_:
.LFB4358:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# __a, __a
	movq	%rsi, -16(%rbp)	# __b, __b
# /usr/include/c++/13/bits/stl_algobase.h:262:       if (__a < __b)
	movq	-8(%rbp), %rax	# __a, tmp86
	movq	(%rax), %rdx	# *__a_5(D), _1
	movq	-16(%rbp), %rax	# __b, tmp87
	movq	(%rax), %rax	# *__b_6(D), _2
# /usr/include/c++/13/bits/stl_algobase.h:262:       if (__a < __b)
	cmpq	%rax, %rdx	# _2, _1
	jnb	.L146	#,
# /usr/include/c++/13/bits/stl_algobase.h:263: 	return __b;
	movq	-16(%rbp), %rax	# __b, _3
	jmp	.L147	#
.L146:
# /usr/include/c++/13/bits/stl_algobase.h:264:       return __a;
	movq	-8(%rbp), %rax	# __a, _3
.L147:
# /usr/include/c++/13/bits/stl_algobase.h:265:     }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4358:
	.size	_ZSt3maxImERKT_S2_S2_, .-_ZSt3maxImERKT_S2_S2_
	.section	.text._ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12_M_check_lenEmPKc,"axG",@progbits,_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12_M_check_lenEmPKc,comdat
	.align 2
	.weak	_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12_M_check_lenEmPKc
	.type	_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12_M_check_lenEmPKc, @function
_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12_M_check_lenEmPKc:
.LFB4356:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$72, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -56(%rbp)	# this, this
	movq	%rsi, -64(%rbp)	# __n, __n
	movq	%rdx, -72(%rbp)	# __s, __s
# /usr/include/c++/13/bits/stl_vector.h:1896:       _M_check_len(size_type __n, const char* __s) const
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp107
	movq	%rax, -24(%rbp)	# tmp107, D.99517
	xorl	%eax, %eax	# tmp107
# /usr/include/c++/13/bits/stl_vector.h:1898: 	if (max_size() - size() < __n)
	movq	-56(%rbp), %rax	# this, tmp95
	movq	%rax, %rdi	# tmp95,
	call	_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE8max_sizeEv	#
	movq	%rax, %rbx	#, _1
# /usr/include/c++/13/bits/stl_vector.h:1898: 	if (max_size() - size() < __n)
	movq	-56(%rbp), %rax	# this, tmp96
	movq	%rax, %rdi	# tmp96,
	call	_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE4sizeEv	#
# /usr/include/c++/13/bits/stl_vector.h:1898: 	if (max_size() - size() < __n)
	subq	%rax, %rbx	# _2, _1
	movq	%rbx, %rdx	# _1, _3
# /usr/include/c++/13/bits/stl_vector.h:1898: 	if (max_size() - size() < __n)
	movq	-64(%rbp), %rax	# __n, __n.4_4
	cmpq	%rax, %rdx	# __n.4_4, _3
	setb	%al	#, retval.3_18
# /usr/include/c++/13/bits/stl_vector.h:1898: 	if (max_size() - size() < __n)
	testb	%al, %al	# retval.3_18
	je	.L149	#,
# /usr/include/c++/13/bits/stl_vector.h:1899: 	  __throw_length_error(__N(__s));
	movq	-24(%rbp), %rax	# D.99517, tmp108
	subq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp108
	je	.L150	#,
	call	__stack_chk_fail@PLT	#
.L150:
	movq	-72(%rbp), %rax	# __s, tmp97
	movq	%rax, %rdi	# tmp97,
	call	_ZSt20__throw_length_errorPKc@PLT	#
.L149:
# /usr/include/c++/13/bits/stl_vector.h:1901: 	const size_type __len = size() + (std::max)(size(), __n);
	movq	-56(%rbp), %rax	# this, tmp98
	movq	%rax, %rdi	# tmp98,
	call	_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE4sizeEv	#
	movq	%rax, %rbx	#, _5
# /usr/include/c++/13/bits/stl_vector.h:1901: 	const size_type __len = size() + (std::max)(size(), __n);
	movq	-56(%rbp), %rax	# this, tmp99
	movq	%rax, %rdi	# tmp99,
	call	_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE4sizeEv	#
# /usr/include/c++/13/bits/stl_vector.h:1901: 	const size_type __len = size() + (std::max)(size(), __n);
	movq	%rax, -40(%rbp)	# _6, D.97056
# /usr/include/c++/13/bits/stl_vector.h:1901: 	const size_type __len = size() + (std::max)(size(), __n);
	leaq	-64(%rbp), %rdx	#, tmp100
	leaq	-40(%rbp), %rax	#, tmp101
	movq	%rdx, %rsi	# tmp100,
	movq	%rax, %rdi	# tmp101,
	call	_ZSt3maxImERKT_S2_S2_	#
# /usr/include/c++/13/bits/stl_vector.h:1901: 	const size_type __len = size() + (std::max)(size(), __n);
	movq	(%rax), %rax	# *_7, _8
# /usr/include/c++/13/bits/stl_vector.h:1901: 	const size_type __len = size() + (std::max)(size(), __n);
	addq	%rbx, %rax	# _5, tmp102
	movq	%rax, -32(%rbp)	# tmp102, __len
# /usr/include/c++/13/bits/stl_vector.h:1902: 	return (__len < size() || __len > max_size()) ? max_size() : __len;
	movq	-56(%rbp), %rax	# this, tmp103
	movq	%rax, %rdi	# tmp103,
	call	_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE4sizeEv	#
# /usr/include/c++/13/bits/stl_vector.h:1902: 	return (__len < size() || __len > max_size()) ? max_size() : __len;
	cmpq	%rax, -32(%rbp)	# _9, __len
	jb	.L151	#,
# /usr/include/c++/13/bits/stl_vector.h:1902: 	return (__len < size() || __len > max_size()) ? max_size() : __len;
	movq	-56(%rbp), %rax	# this, tmp104
	movq	%rax, %rdi	# tmp104,
	call	_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE8max_sizeEv	#
# /usr/include/c++/13/bits/stl_vector.h:1902: 	return (__len < size() || __len > max_size()) ? max_size() : __len;
	cmpq	-32(%rbp), %rax	# __len, _10
	jnb	.L152	#,
.L151:
# /usr/include/c++/13/bits/stl_vector.h:1902: 	return (__len < size() || __len > max_size()) ? max_size() : __len;
	movq	-56(%rbp), %rax	# this, tmp105
	movq	%rax, %rdi	# tmp105,
	call	_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE8max_sizeEv	#
# /usr/include/c++/13/bits/stl_vector.h:1902: 	return (__len < size() || __len > max_size()) ? max_size() : __len;
	jmp	.L153	#
.L152:
# /usr/include/c++/13/bits/stl_vector.h:1902: 	return (__len < size() || __len > max_size()) ? max_size() : __len;
	movq	-32(%rbp), %rax	# __len, iftmp.5_11
.L153:
# /usr/include/c++/13/bits/stl_vector.h:1903:       }
	movq	-24(%rbp), %rdx	# D.99517, tmp109
	subq	%fs:40, %rdx	# MEM[(<address-space-1> long unsigned int *)40B], tmp109
	je	.L155	#,
	call	__stack_chk_fail@PLT	#
.L155:
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4356:
	.size	_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12_M_check_lenEmPKc, .-_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12_M_check_lenEmPKc
	.section	.text._ZN9__gnu_cxxmiIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEENS_17__normal_iteratorIT_T0_E15difference_typeERKSD_SG_,"axG",@progbits,_ZN9__gnu_cxxmiIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEENS_17__normal_iteratorIT_T0_E15difference_typeERKSD_SG_,comdat
	.weak	_ZN9__gnu_cxxmiIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEENS_17__normal_iteratorIT_T0_E15difference_typeERKSD_SG_
	.type	_ZN9__gnu_cxxmiIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEENS_17__normal_iteratorIT_T0_E15difference_typeERKSD_SG_, @function
_ZN9__gnu_cxxmiIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEENS_17__normal_iteratorIT_T0_E15difference_typeERKSD_SG_:
.LFB4359:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$24, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)	# __lhs, __lhs
	movq	%rsi, -32(%rbp)	# __rhs, __rhs
# /usr/include/c++/13/bits/stl_iterator.h:1337:     { return __lhs.base() - __rhs.base(); }
	movq	-24(%rbp), %rax	# __lhs, tmp89
	movq	%rax, %rdi	# tmp89,
	call	_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEE4baseEv	#
# /usr/include/c++/13/bits/stl_iterator.h:1337:     { return __lhs.base() - __rhs.base(); }
	movq	(%rax), %rbx	# *_1, _2
# /usr/include/c++/13/bits/stl_iterator.h:1337:     { return __lhs.base() - __rhs.base(); }
	movq	-32(%rbp), %rax	# __rhs, tmp90
	movq	%rax, %rdi	# tmp90,
	call	_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEE4baseEv	#
# /usr/include/c++/13/bits/stl_iterator.h:1337:     { return __lhs.base() - __rhs.base(); }
	movq	(%rax), %rax	# *_3, _4
	movq	%rbx, %rdx	# _2, _2
	subq	%rax, %rdx	# _4, _2
# /usr/include/c++/13/bits/stl_iterator.h:1337:     { return __lhs.base() - __rhs.base(); }
	movq	%rdx, %rax	# _5, _5
	sarq	$3, %rax	#, _5
# /usr/include/c++/13/bits/stl_iterator.h:1337:     { return __lhs.base() - __rhs.base(); }
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4359:
	.size	_ZN9__gnu_cxxmiIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEENS_17__normal_iteratorIT_T0_E15difference_typeERKSD_SG_, .-_ZN9__gnu_cxxmiIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEENS_17__normal_iteratorIT_T0_E15difference_typeERKSD_SG_
	.section	.rodata
.LC5:
	.string	"vector::_M_realloc_insert"
	.section	.text._ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE17_M_realloc_insertIJS4_EEEvN9__gnu_cxx17__normal_iteratorIPS4_S6_EEDpOT_,"axG",@progbits,_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE17_M_realloc_insertIJS4_EEEvN9__gnu_cxx17__normal_iteratorIPS4_S6_EEDpOT_,comdat
	.align 2
	.weak	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE17_M_realloc_insertIJS4_EEEvN9__gnu_cxx17__normal_iteratorIPS4_S6_EEDpOT_
	.type	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE17_M_realloc_insertIJS4_EEEvN9__gnu_cxx17__normal_iteratorIPS4_S6_EEDpOT_, @function
_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE17_M_realloc_insertIJS4_EEEvN9__gnu_cxx17__normal_iteratorIPS4_S6_EEDpOT_:
.LFB4355:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$136, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -120(%rbp)	# this, this
	movq	%rsi, -128(%rbp)	# __position, __position
	movq	%rdx, -136(%rbp)	# __args#0, __args#0
# /usr/include/c++/13/bits/vector.tcc:445:       vector<_Tp, _Alloc>::
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp149
	movq	%rax, -24(%rbp)	# tmp149, D.99518
	xorl	%eax, %eax	# tmp149
# /usr/include/c++/13/bits/vector.tcc:455: 	_M_check_len(size_type(1), "vector::_M_realloc_insert");
	movq	-120(%rbp), %rax	# this, tmp113
	leaq	.LC5(%rip), %rdx	#, tmp114
	movl	$1, %esi	#,
	movq	%rax, %rdi	# tmp113,
	call	_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE12_M_check_lenEmPKc	#
# /usr/include/c++/13/bits/vector.tcc:455: 	_M_check_len(size_type(1), "vector::_M_realloc_insert");
	movq	%rax, -96(%rbp)	# _32, __len
# /usr/include/c++/13/bits/vector.tcc:456:       pointer __old_start = this->_M_impl._M_start;
	movq	-120(%rbp), %rax	# this, tmp115
	movq	(%rax), %rax	# this_30(D)->D.80067._M_impl.D.79372._M_start, tmp116
	movq	%rax, -88(%rbp)	# tmp116, __old_start
# /usr/include/c++/13/bits/vector.tcc:457:       pointer __old_finish = this->_M_impl._M_finish;
	movq	-120(%rbp), %rax	# this, tmp117
	movq	8(%rax), %rax	# this_30(D)->D.80067._M_impl.D.79372._M_finish, tmp118
	movq	%rax, -80(%rbp)	# tmp118, __old_finish
# /usr/include/c++/13/bits/vector.tcc:458:       const size_type __elems_before = __position - begin();
	movq	-120(%rbp), %rax	# this, tmp119
	movq	%rax, %rdi	# tmp119,
	call	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE5beginEv	#
	movq	%rax, -104(%rbp)	# tmp121, D.97075
# /usr/include/c++/13/bits/vector.tcc:458:       const size_type __elems_before = __position - begin();
	leaq	-104(%rbp), %rdx	#, tmp122
	leaq	-128(%rbp), %rax	#, tmp123
	movq	%rdx, %rsi	# tmp122,
	movq	%rax, %rdi	# tmp123,
	call	_ZN9__gnu_cxxmiIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEENS_17__normal_iteratorIT_T0_E15difference_typeERKSD_SG_	#
# /usr/include/c++/13/bits/vector.tcc:458:       const size_type __elems_before = __position - begin();
	movq	%rax, -72(%rbp)	# _1, __elems_before
# /usr/include/c++/13/bits/vector.tcc:459:       pointer __new_start(this->_M_allocate(__len));
	movq	-120(%rbp), %rax	# this, _2
	movq	-96(%rbp), %rdx	# __len, tmp124
	movq	%rdx, %rsi	# tmp124,
	movq	%rax, %rdi	# _2,
	call	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_M_allocateEm	#
# /usr/include/c++/13/bits/vector.tcc:459:       pointer __new_start(this->_M_allocate(__len));
	movq	%rax, -64(%rbp)	# _41, __new_start
# /usr/include/c++/13/bits/vector.tcc:460:       pointer __new_finish(__new_start);
	movq	-64(%rbp), %rax	# __new_start, tmp125
	movq	%rax, -56(%rbp)	# tmp125, __new_finish
# /usr/include/c++/13/bits/vector.tcc:468: 	  _Alloc_traits::construct(this->_M_impl,
	movq	-136(%rbp), %rax	# __args#0, tmp126
	movq	%rax, %rdi	# tmp126,
	call	_ZSt7forwardISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEOT_RNSt16remove_referenceIS5_E4typeE	#
# /usr/include/c++/13/bits/vector.tcc:469: 				   __new_start + __elems_before,
	movq	-72(%rbp), %rdx	# __elems_before, tmp127
	leaq	0(,%rdx,8), %rcx	#, _4
# /usr/include/c++/13/bits/vector.tcc:468: 	  _Alloc_traits::construct(this->_M_impl,
	movq	-64(%rbp), %rdx	# __new_start, tmp128
	addq	%rdx, %rcx	# tmp128, _5
# /usr/include/c++/13/bits/vector.tcc:468: 	  _Alloc_traits::construct(this->_M_impl,
	movq	-120(%rbp), %rdx	# this, _6
	movq	%rdx, -48(%rbp)	# _6, __a
	movq	%rcx, -40(%rbp)	# _5, __p
	movq	%rax, -32(%rbp)	# _3, __args#0
# /usr/include/c++/13/bits/alloc_traits.h:540: 	  std::construct_at(__p, std::forward<_Args>(__args)...);
	movq	-32(%rbp), %rax	# __args#0, tmp129
	movq	%rax, %rdi	# tmp129,
	call	_ZSt7forwardISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEOT_RNSt16remove_referenceIS5_E4typeE	#
	movq	%rax, %rdx	#, _63
# /usr/include/c++/13/bits/alloc_traits.h:540: 	  std::construct_at(__p, std::forward<_Args>(__args)...);
	movq	-40(%rbp), %rax	# __p, tmp130
	movq	%rdx, %rsi	# _63,
	movq	%rax, %rdi	# tmp130,
	call	_ZSt12construct_atISt10unique_ptrI5ShapeSt14default_deleteIS1_EEJS4_EEDTgsnwcvPvLi0E_T_pispcl7declvalIT0_EEEEPS6_DpOS7_	#
# /usr/include/c++/13/bits/alloc_traits.h:542: 	}
	nop	
# /usr/include/c++/13/bits/vector.tcc:475: 	  __new_finish = pointer();
	movq	$0, -56(%rbp)	#, __new_finish
# /usr/include/c++/13/bits/vector.tcc:481: 					 __new_start, _M_get_Tp_allocator());
	movq	-120(%rbp), %rax	# this, _7
	movq	%rax, %rdi	# _7,
	call	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE19_M_get_Tp_allocatorEv	#
	movq	%rax, %rbx	#, _8
# /usr/include/c++/13/bits/vector.tcc:480: 	      __new_finish = _S_relocate(__old_start, __position.base(),
	leaq	-128(%rbp), %rax	#, tmp131
	movq	%rax, %rdi	# tmp131,
	call	_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEE4baseEv	#
# /usr/include/c++/13/bits/vector.tcc:480: 	      __new_finish = _S_relocate(__old_start, __position.base(),
	movq	(%rax), %rsi	# *_9, _10
	movq	-64(%rbp), %rdx	# __new_start, tmp132
	movq	-88(%rbp), %rax	# __old_start, tmp133
	movq	%rbx, %rcx	# _8,
	movq	%rax, %rdi	# tmp133,
	call	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_S_relocateEPS4_S7_S7_RS5_	#
	movq	%rax, -56(%rbp)	# tmp134, __new_finish
# /usr/include/c++/13/bits/vector.tcc:483: 	      ++__new_finish;
	addq	$8, -56(%rbp)	#, __new_finish
# /usr/include/c++/13/bits/vector.tcc:486: 					 __new_finish, _M_get_Tp_allocator());
	movq	-120(%rbp), %rax	# this, _11
	movq	%rax, %rdi	# _11,
	call	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE19_M_get_Tp_allocatorEv	#
	movq	%rax, %rbx	#, _12
# /usr/include/c++/13/bits/vector.tcc:485: 	      __new_finish = _S_relocate(__position.base(), __old_finish,
	leaq	-128(%rbp), %rax	#, tmp135
	movq	%rax, %rdi	# tmp135,
	call	_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEE4baseEv	#
# /usr/include/c++/13/bits/vector.tcc:485: 	      __new_finish = _S_relocate(__position.base(), __old_finish,
	movq	(%rax), %rax	# *_13, _14
	movq	-56(%rbp), %rdx	# __new_finish, tmp136
	movq	-80(%rbp), %rsi	# __old_finish, tmp137
	movq	%rbx, %rcx	# _12,
	movq	%rax, %rdi	# _14,
	call	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_S_relocateEPS4_S7_S7_RS5_	#
	movq	%rax, -56(%rbp)	# tmp138, __new_finish
# /usr/include/c++/13/bits/vector.tcc:519:       _M_deallocate(__old_start,
	movq	-120(%rbp), %rax	# this, _22
# /usr/include/c++/13/bits/vector.tcc:520: 		    this->_M_impl._M_end_of_storage - __old_start);
	movq	-120(%rbp), %rdx	# this, tmp139
	movq	16(%rdx), %rdx	# this_30(D)->D.80067._M_impl.D.79372._M_end_of_storage, _23
# /usr/include/c++/13/bits/vector.tcc:520: 		    this->_M_impl._M_end_of_storage - __old_start);
	subq	-88(%rbp), %rdx	# __old_start, _24
	sarq	$3, %rdx	#, tmp140
# /usr/include/c++/13/bits/vector.tcc:519:       _M_deallocate(__old_start,
	movq	-88(%rbp), %rcx	# __old_start, tmp141
	movq	%rcx, %rsi	# tmp141,
	movq	%rax, %rdi	# _22,
	call	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE13_M_deallocateEPS4_m	#
# /usr/include/c++/13/bits/vector.tcc:521:       this->_M_impl._M_start = __new_start;
	movq	-120(%rbp), %rax	# this, tmp142
	movq	-64(%rbp), %rdx	# __new_start, tmp143
	movq	%rdx, (%rax)	# tmp143, this_30(D)->D.80067._M_impl.D.79372._M_start
# /usr/include/c++/13/bits/vector.tcc:522:       this->_M_impl._M_finish = __new_finish;
	movq	-120(%rbp), %rax	# this, tmp144
	movq	-56(%rbp), %rdx	# __new_finish, tmp145
	movq	%rdx, 8(%rax)	# tmp145, this_30(D)->D.80067._M_impl.D.79372._M_finish
# /usr/include/c++/13/bits/vector.tcc:523:       this->_M_impl._M_end_of_storage = __new_start + __len;
	movq	-96(%rbp), %rax	# __len, tmp146
	leaq	0(,%rax,8), %rdx	#, _27
	movq	-64(%rbp), %rax	# __new_start, tmp147
	addq	%rax, %rdx	# tmp147, _28
# /usr/include/c++/13/bits/vector.tcc:523:       this->_M_impl._M_end_of_storage = __new_start + __len;
	movq	-120(%rbp), %rax	# this, tmp148
	movq	%rdx, 16(%rax)	# _28, this_30(D)->D.80067._M_impl.D.79372._M_end_of_storage
# /usr/include/c++/13/bits/vector.tcc:524:     }
	nop	
	movq	-24(%rbp), %rax	# D.99518, tmp150
	subq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp150
	je	.L159	#,
	call	__stack_chk_fail@PLT	#
.L159:
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4355:
	.size	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE17_M_realloc_insertIJS4_EEEvN9__gnu_cxx17__normal_iteratorIPS4_S6_EEDpOT_, .-_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE17_M_realloc_insertIJS4_EEEvN9__gnu_cxx17__normal_iteratorIPS4_S6_EEDpOT_
	.section	.text._ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE4backEv,"axG",@progbits,_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE4backEv,comdat
	.align 2
	.weak	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE4backEv
	.type	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE4backEv, @function
_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE4backEv:
.LFB4363:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$48, %rsp	#,
	movq	%rdi, -40(%rbp)	# this, this
# /usr/include/c++/13/bits/stl_vector.h:1233:       back() _GLIBCXX_NOEXCEPT
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp92
	movq	%rax, -8(%rbp)	# tmp92, D.99520
	xorl	%eax, %eax	# tmp92
# /usr/include/c++/13/bits/stl_vector.h:1236: 	return *(end() - 1);
	movq	-40(%rbp), %rax	# this, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE3endEv	#
	movq	%rax, -24(%rbp)	# tmp86, D.97334
# /usr/include/c++/13/bits/stl_vector.h:1236: 	return *(end() - 1);
	leaq	-24(%rbp), %rax	#, tmp87
	movl	$1, %esi	#,
	movq	%rax, %rdi	# tmp87,
	call	_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEmiEl	#
	movq	%rax, -16(%rbp)	# tmp89, D.97335
# /usr/include/c++/13/bits/stl_vector.h:1236: 	return *(end() - 1);
	leaq	-16(%rbp), %rax	#, tmp90
	movq	%rax, %rdi	# tmp90,
	call	_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEdeEv	#
# /usr/include/c++/13/bits/stl_vector.h:1237:       }
	movq	-8(%rbp), %rdx	# D.99520, tmp93
	subq	%fs:40, %rdx	# MEM[(<address-space-1> long unsigned int *)40B], tmp93
	je	.L162	#,
	call	__stack_chk_fail@PLT	#
.L162:
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4363:
	.size	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE4backEv, .-_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE4backEv
	.section	.text._ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EEC2EPS0_,"axG",@progbits,_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EEC5EPS0_,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EEC2EPS0_
	.type	_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EEC2EPS0_, @function
_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EEC2EPS0_:
.LFB4366:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$24, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)	# this, this
	movq	%rsi, -32(%rbp)	# __p, __p
# /usr/include/c++/13/bits/unique_ptr.h:176:       __uniq_ptr_impl(pointer __p) : _M_t() { _M_ptr() = __p; }
	movq	-24(%rbp), %rax	# this, _1
	movq	%rax, %rdi	# _1,
	call	_ZNSt5tupleIJP9RectangleSt14default_deleteIS0_EEEC1ILb1ELb1EEEv	#
# /usr/include/c++/13/bits/unique_ptr.h:176:       __uniq_ptr_impl(pointer __p) : _M_t() { _M_ptr() = __p; }
	movq	-32(%rbp), %rbx	# __p, __p.2_2
# /usr/include/c++/13/bits/unique_ptr.h:176:       __uniq_ptr_impl(pointer __p) : _M_t() { _M_ptr() = __p; }
	movq	-24(%rbp), %rax	# this, tmp85
	movq	%rax, %rdi	# tmp85,
	call	_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE6_M_ptrEv	#
# /usr/include/c++/13/bits/unique_ptr.h:176:       __uniq_ptr_impl(pointer __p) : _M_t() { _M_ptr() = __p; }
	movq	%rbx, (%rax)	# __p.2_2, *_3
# /usr/include/c++/13/bits/unique_ptr.h:176:       __uniq_ptr_impl(pointer __p) : _M_t() { _M_ptr() = __p; }
	nop	
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4366:
	.size	_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EEC2EPS0_, .-_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EEC2EPS0_
	.weak	_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EEC1EPS0_
	.set	_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EEC1EPS0_,_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EEC2EPS0_
	.section	.text._ZSt3getILm0EJP9RectangleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_,"axG",@progbits,_ZSt3getILm0EJP9RectangleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_,comdat
	.weak	_ZSt3getILm0EJP9RectangleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_
	.type	_ZSt3getILm0EJP9RectangleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_, @function
_ZSt3getILm0EJP9RectangleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_:
.LFB4368:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/tuple:1804:     { return std::__get_helper<__i>(__t); }
	movq	-8(%rbp), %rax	# __t, _1
	movq	%rax, %rdi	# _1,
	call	_ZSt12__get_helperILm0EP9RectangleJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE	#
# /usr/include/c++/13/tuple:1804:     { return std::__get_helper<__i>(__t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4368:
	.size	_ZSt3getILm0EJP9RectangleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_, .-_ZSt3getILm0EJP9RectangleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_
	.section	.text._ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE10_M_deleterEv,"axG",@progbits,_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE10_M_deleterEv,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE10_M_deleterEv
	.type	_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE10_M_deleterEv, @function
_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE10_M_deleterEv:
.LFB4369:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/bits/unique_ptr.h:201:       _Dp&       _M_deleter() noexcept { return std::get<1>(_M_t); }
	movq	-8(%rbp), %rax	# this, _1
# /usr/include/c++/13/bits/unique_ptr.h:201:       _Dp&       _M_deleter() noexcept { return std::get<1>(_M_t); }
	movq	%rax, %rdi	# _1,
	call	_ZSt3getILm1EJP9RectangleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_	#
# /usr/include/c++/13/bits/unique_ptr.h:201:       _Dp&       _M_deleter() noexcept { return std::get<1>(_M_t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4369:
	.size	_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE10_M_deleterEv, .-_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE10_M_deleterEv
	.section	.text._ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE7releaseEv,"axG",@progbits,_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE7releaseEv,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE7releaseEv
	.type	_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE7releaseEv, @function
_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE7releaseEv:
.LFB4370:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$32, %rsp	#,
	movq	%rdi, -24(%rbp)	# this, this
# /usr/include/c++/13/bits/unique_ptr.h:217: 	pointer __p = _M_ptr();
	movq	-24(%rbp), %rax	# this, tmp86
	movq	%rax, %rdi	# tmp86,
	call	_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE6_M_ptrEv	#
# /usr/include/c++/13/bits/unique_ptr.h:217: 	pointer __p = _M_ptr();
	movq	(%rax), %rax	# *_1, tmp87
	movq	%rax, -8(%rbp)	# tmp87, __p
# /usr/include/c++/13/bits/unique_ptr.h:218: 	_M_ptr() = nullptr;
	movq	-24(%rbp), %rax	# this, tmp88
	movq	%rax, %rdi	# tmp88,
	call	_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE6_M_ptrEv	#
# /usr/include/c++/13/bits/unique_ptr.h:218: 	_M_ptr() = nullptr;
	movq	$0, (%rax)	#, *_2
# /usr/include/c++/13/bits/unique_ptr.h:219: 	return __p;
	movq	-8(%rbp), %rax	# __p, _9
# /usr/include/c++/13/bits/unique_ptr.h:220:       }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4370:
	.size	_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE7releaseEv, .-_ZNSt15__uniq_ptr_implI9RectangleSt14default_deleteIS0_EE7releaseEv
	.section	.text._ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC2IRS1_S2_I9RectangleELb1EEEOT_OT0_,"axG",@progbits,_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC5IRS1_S2_I9RectangleELb1EEEOT_OT0_,comdat
	.align 2
	.weak	_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC2IRS1_S2_I9RectangleELb1EEEOT_OT0_
	.type	_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC2IRS1_S2_I9RectangleELb1EEEOT_OT0_, @function
_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC2IRS1_S2_I9RectangleELb1EEEOT_OT0_:
.LFB4372:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA4372
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%r12	#
	pushq	%rbx	#
	subq	$32, %rsp	#,
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -24(%rbp)	# this, this
	movq	%rsi, -32(%rbp)	# __a1, __a1
	movq	%rdx, -40(%rbp)	# __a2, __a2
# /usr/include/c++/13/tuple:1347: 	: _Inherited(std::forward<_U1>(__a1), std::forward<_U2>(__a2)) { }
	movq	-24(%rbp), %rbx	# this, _1
	movq	-40(%rbp), %rax	# __a2, tmp85
	movq	%rax, %rdi	# tmp85,
	call	_ZSt7forwardISt14default_deleteI9RectangleEEOT_RNSt16remove_referenceIS3_E4typeE	#
	movq	%rax, %r12	#, _2
# /usr/include/c++/13/tuple:1347: 	: _Inherited(std::forward<_U1>(__a1), std::forward<_U2>(__a2)) { }
	movq	-32(%rbp), %rax	# __a1, tmp86
	movq	%rax, %rdi	# tmp86,
	call	_ZSt7forwardIRP5ShapeEOT_RNSt16remove_referenceIS3_E4typeE	#
# /usr/include/c++/13/tuple:1347: 	: _Inherited(std::forward<_U1>(__a1), std::forward<_U2>(__a2)) { }
	movq	%r12, %rdx	# _2,
	movq	%rax, %rsi	# _3,
	movq	%rbx, %rdi	# _1,
	call	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2IRS1_JS2_I9RectangleEEvEEOT_DpOT0_	#
# /usr/include/c++/13/tuple:1347: 	: _Inherited(std::forward<_U1>(__a1), std::forward<_U2>(__a2)) { }
	nop	
	addq	$32, %rsp	#,
	popq	%rbx	#
	popq	%r12	#
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4372:
	.section	.gcc_except_table
.LLSDA4372:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4372-.LLSDACSB4372
.LLSDACSB4372:
.LLSDACSE4372:
	.section	.text._ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC2IRS1_S2_I9RectangleELb1EEEOT_OT0_,"axG",@progbits,_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC5IRS1_S2_I9RectangleELb1EEEOT_OT0_,comdat
	.size	_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC2IRS1_S2_I9RectangleELb1EEEOT_OT0_, .-_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC2IRS1_S2_I9RectangleELb1EEEOT_OT0_
	.weak	_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC1IRS1_S2_I9RectangleELb1EEEOT_OT0_
	.set	_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC1IRS1_S2_I9RectangleELb1EEEOT_OT0_,_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC2IRS1_S2_I9RectangleELb1EEEOT_OT0_
	.section	.text._ZNKSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE6_M_ptrEv,"axG",@progbits,_ZNKSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE6_M_ptrEv,comdat
	.align 2
	.weak	_ZNKSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE6_M_ptrEv
	.type	_ZNKSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE6_M_ptrEv, @function
_ZNKSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE6_M_ptrEv:
.LFB4374:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/bits/unique_ptr.h:199:       pointer    _M_ptr() const noexcept { return std::get<0>(_M_t); }
	movq	-8(%rbp), %rax	# this, _1
# /usr/include/c++/13/bits/unique_ptr.h:199:       pointer    _M_ptr() const noexcept { return std::get<0>(_M_t); }
	movq	%rax, %rdi	# _1,
	call	_ZSt3getILm0EJP5ShapeSt14default_deleteIS0_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKS8_	#
# /usr/include/c++/13/bits/unique_ptr.h:199:       pointer    _M_ptr() const noexcept { return std::get<0>(_M_t); }
	movq	(%rax), %rax	# *_2, _6
# /usr/include/c++/13/bits/unique_ptr.h:199:       pointer    _M_ptr() const noexcept { return std::get<0>(_M_t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4374:
	.size	_ZNKSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE6_M_ptrEv, .-_ZNKSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE6_M_ptrEv
	.section	.text._ZNSt12_Destroy_auxILb0EE9__destroyIPSt10unique_ptrI5ShapeSt14default_deleteIS3_EEEEvT_S8_,"axG",@progbits,_ZNSt12_Destroy_auxILb0EE9__destroyIPSt10unique_ptrI5ShapeSt14default_deleteIS3_EEEEvT_S8_,comdat
	.weak	_ZNSt12_Destroy_auxILb0EE9__destroyIPSt10unique_ptrI5ShapeSt14default_deleteIS3_EEEEvT_S8_
	.type	_ZNSt12_Destroy_auxILb0EE9__destroyIPSt10unique_ptrI5ShapeSt14default_deleteIS3_EEEEvT_S8_, @function
_ZNSt12_Destroy_auxILb0EE9__destroyIPSt10unique_ptrI5ShapeSt14default_deleteIS3_EEEEvT_S8_:
.LFB4450:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __first, __first
	movq	%rsi, -16(%rbp)	# __last, __last
# /usr/include/c++/13/bits/stl_construct.h:162: 	  for (; __first != __last; ++__first)
	jmp	.L174	#
.L175:
# /usr/include/c++/13/bits/stl_construct.h:163: 	    std::_Destroy(std::__addressof(*__first));
	movq	-8(%rbp), %rax	# __first, tmp83
	movq	%rax, %rdi	# tmp83,
	call	_ZSt11__addressofISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEPT_RS5_	#
# /usr/include/c++/13/bits/stl_construct.h:163: 	    std::_Destroy(std::__addressof(*__first));
	movq	%rax, %rdi	# _1,
	call	_ZSt8_DestroyISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvPT_	#
# /usr/include/c++/13/bits/stl_construct.h:162: 	  for (; __first != __last; ++__first)
	addq	$8, -8(%rbp)	#, __first
.L174:
# /usr/include/c++/13/bits/stl_construct.h:162: 	  for (; __first != __last; ++__first)
	movq	-8(%rbp), %rax	# __first, tmp84
	cmpq	-16(%rbp), %rax	# __last, tmp84
	jne	.L175	#,
# /usr/include/c++/13/bits/stl_construct.h:164: 	}
	nop	
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4450:
	.size	_ZNSt12_Destroy_auxILb0EE9__destroyIPSt10unique_ptrI5ShapeSt14default_deleteIS3_EEEEvT_S8_, .-_ZNSt12_Destroy_auxILb0EE9__destroyIPSt10unique_ptrI5ShapeSt14default_deleteIS3_EEEEvT_S8_
	.section	.text._ZNSt5tupleIJP6CircleSt14default_deleteIS0_EEEC2ILb1ELb1EEEv,"axG",@progbits,_ZNSt5tupleIJP6CircleSt14default_deleteIS0_EEEC5ILb1ELb1EEEv,comdat
	.align 2
	.weak	_ZNSt5tupleIJP6CircleSt14default_deleteIS0_EEEC2ILb1ELb1EEEv
	.type	_ZNSt5tupleIJP6CircleSt14default_deleteIS0_EEEC2ILb1ELb1EEEv, @function
_ZNSt5tupleIJP6CircleSt14default_deleteIS0_EEEC2ILb1ELb1EEEv:
.LFB4452:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA4452
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/tuple:1319: 	: _Inherited() { }
	movq	-8(%rbp), %rax	# this, _1
	movq	%rax, %rdi	# _1,
	call	_ZNSt11_Tuple_implILm0EJP6CircleSt14default_deleteIS0_EEEC2Ev	#
# /usr/include/c++/13/tuple:1319: 	: _Inherited() { }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4452:
	.section	.gcc_except_table
.LLSDA4452:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4452-.LLSDACSB4452
.LLSDACSB4452:
.LLSDACSE4452:
	.section	.text._ZNSt5tupleIJP6CircleSt14default_deleteIS0_EEEC2ILb1ELb1EEEv,"axG",@progbits,_ZNSt5tupleIJP6CircleSt14default_deleteIS0_EEEC5ILb1ELb1EEEv,comdat
	.size	_ZNSt5tupleIJP6CircleSt14default_deleteIS0_EEEC2ILb1ELb1EEEv, .-_ZNSt5tupleIJP6CircleSt14default_deleteIS0_EEEC2ILb1ELb1EEEv
	.weak	_ZNSt5tupleIJP6CircleSt14default_deleteIS0_EEEC1ILb1ELb1EEEv
	.set	_ZNSt5tupleIJP6CircleSt14default_deleteIS0_EEEC1ILb1ELb1EEEv,_ZNSt5tupleIJP6CircleSt14default_deleteIS0_EEEC2ILb1ELb1EEEv
	.section	.text._ZSt12__get_helperILm0EP6CircleJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE,"axG",@progbits,_ZSt12__get_helperILm0EP6CircleJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE,comdat
	.weak	_ZSt12__get_helperILm0EP6CircleJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE
	.type	_ZSt12__get_helperILm0EP6CircleJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE, @function
_ZSt12__get_helperILm0EP6CircleJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE:
.LFB4454:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/tuple:1788:     { return _Tuple_impl<__i, _Head, _Tail...>::_M_head(__t); }
	movq	-8(%rbp), %rax	# __t, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZNSt11_Tuple_implILm0EJP6CircleSt14default_deleteIS0_EEE7_M_headERS4_	#
# /usr/include/c++/13/tuple:1788:     { return _Tuple_impl<__i, _Head, _Tail...>::_M_head(__t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4454:
	.size	_ZSt12__get_helperILm0EP6CircleJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE, .-_ZSt12__get_helperILm0EP6CircleJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE
	.section	.text._ZSt3getILm1EJP6CircleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_,"axG",@progbits,_ZSt3getILm1EJP6CircleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_,comdat
	.weak	_ZSt3getILm1EJP6CircleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_
	.type	_ZSt3getILm1EJP6CircleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_, @function
_ZSt3getILm1EJP6CircleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_:
.LFB4455:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/tuple:1804:     { return std::__get_helper<__i>(__t); }
	movq	-8(%rbp), %rax	# __t, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZSt12__get_helperILm1ESt14default_deleteI6CircleEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE	#
# /usr/include/c++/13/tuple:1804:     { return std::__get_helper<__i>(__t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4455:
	.size	_ZSt3getILm1EJP6CircleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_, .-_ZSt3getILm1EJP6CircleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_
	.section	.text._ZSt7forwardIRP5ShapeEOT_RNSt16remove_referenceIS3_E4typeE,"axG",@progbits,_ZSt7forwardIRP5ShapeEOT_RNSt16remove_referenceIS3_E4typeE,comdat
	.weak	_ZSt7forwardIRP5ShapeEOT_RNSt16remove_referenceIS3_E4typeE
	.type	_ZSt7forwardIRP5ShapeEOT_RNSt16remove_referenceIS3_E4typeE, @function
_ZSt7forwardIRP5ShapeEOT_RNSt16remove_referenceIS3_E4typeE:
.LFB4456:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/bits/move.h:71:     { return static_cast<_Tp&&>(__t); }
	movq	-8(%rbp), %rax	# __t, _2
# /usr/include/c++/13/bits/move.h:71:     { return static_cast<_Tp&&>(__t); }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4456:
	.size	_ZSt7forwardIRP5ShapeEOT_RNSt16remove_referenceIS3_E4typeE, .-_ZSt7forwardIRP5ShapeEOT_RNSt16remove_referenceIS3_E4typeE
	.section	.text._ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2IRS1_JS2_I6CircleEEvEEOT_DpOT0_,"axG",@progbits,_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC5IRS1_JS2_I6CircleEEvEEOT_DpOT0_,comdat
	.align 2
	.weak	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2IRS1_JS2_I6CircleEEvEEOT_DpOT0_
	.type	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2IRS1_JS2_I6CircleEEvEEOT_DpOT0_, @function
_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2IRS1_JS2_I6CircleEEvEEOT_DpOT0_:
.LFB4458:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$40, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)	# this, this
	movq	%rsi, -32(%rbp)	# __head, __head
	movq	%rdx, -40(%rbp)	# __tail#0, __tail#0
# /usr/include/c++/13/tuple:293: 	  _Base(std::forward<_UHead>(__head))
	movq	-40(%rbp), %rax	# __tail#0, tmp85
	movq	%rax, %rdi	# tmp85,
	call	_ZSt7forwardISt14default_deleteI6CircleEEOT_RNSt16remove_referenceIS3_E4typeE	#
	movq	%rax, %rdx	#, _1
# /usr/include/c++/13/tuple:293: 	  _Base(std::forward<_UHead>(__head))
	movq	-24(%rbp), %rax	# this, tmp86
	movq	%rdx, %rsi	# _1,
	movq	%rax, %rdi	# tmp86,
	call	_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2IS0_I6CircleEEEOT_	#
# /usr/include/c++/13/tuple:293: 	  _Base(std::forward<_UHead>(__head))
	movq	-24(%rbp), %rbx	# this, _2
	movq	-32(%rbp), %rax	# __head, tmp87
	movq	%rax, %rdi	# tmp87,
	call	_ZSt7forwardIRP5ShapeEOT_RNSt16remove_referenceIS3_E4typeE	#
# /usr/include/c++/13/tuple:293: 	  _Base(std::forward<_UHead>(__head))
	movq	%rax, %rsi	# _3,
	movq	%rbx, %rdi	# _2,
	call	_ZNSt10_Head_baseILm0EP5ShapeLb0EEC2IRS1_EEOT_	#
# /usr/include/c++/13/tuple:294: 	{ }
	nop	
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4458:
	.size	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2IRS1_JS2_I6CircleEEvEEOT_DpOT0_, .-_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2IRS1_JS2_I6CircleEEvEEOT_DpOT0_
	.weak	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC1IRS1_JS2_I6CircleEEvEEOT_DpOT0_
	.set	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC1IRS1_JS2_I6CircleEEvEEOT_DpOT0_,_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2IRS1_JS2_I6CircleEEvEEOT_DpOT0_
	.section	.text._ZSt12__get_helperILm0EP5ShapeJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE,"axG",@progbits,_ZSt12__get_helperILm0EP5ShapeJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE,comdat
	.weak	_ZSt12__get_helperILm0EP5ShapeJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE
	.type	_ZSt12__get_helperILm0EP5ShapeJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE, @function
_ZSt12__get_helperILm0EP5ShapeJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE:
.LFB4460:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/tuple:1788:     { return _Tuple_impl<__i, _Head, _Tail...>::_M_head(__t); }
	movq	-8(%rbp), %rax	# __t, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEE7_M_headERS4_	#
# /usr/include/c++/13/tuple:1788:     { return _Tuple_impl<__i, _Head, _Tail...>::_M_head(__t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4460:
	.size	_ZSt12__get_helperILm0EP5ShapeJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE, .-_ZSt12__get_helperILm0EP5ShapeJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE
	.section	.text._ZSt3getILm1EJP5ShapeSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_,"axG",@progbits,_ZSt3getILm1EJP5ShapeSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_,comdat
	.weak	_ZSt3getILm1EJP5ShapeSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_
	.type	_ZSt3getILm1EJP5ShapeSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_, @function
_ZSt3getILm1EJP5ShapeSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_:
.LFB4461:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/tuple:1804:     { return std::__get_helper<__i>(__t); }
	movq	-8(%rbp), %rax	# __t, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZSt12__get_helperILm1ESt14default_deleteI5ShapeEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE	#
# /usr/include/c++/13/tuple:1804:     { return std::__get_helper<__i>(__t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4461:
	.size	_ZSt3getILm1EJP5ShapeSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_, .-_ZSt3getILm1EJP5ShapeSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_
	.section	.text._ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EEC2EOS3_,"axG",@progbits,_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EEC5EOS3_,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EEC2EOS3_
	.type	_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EEC2EOS3_, @function
_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EEC2EOS3_:
.LFB4465:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# D.86121, D.86121
# /usr/include/c++/13/bits/unique_ptr.h:242:       __uniq_ptr_data(__uniq_ptr_data&&) = default;
	movq	-8(%rbp), %rax	# this, _1
	movq	-16(%rbp), %rdx	# D.86121, _2
	movq	%rdx, %rsi	# _2,
	movq	%rax, %rdi	# _1,
	call	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2EOS3_	#
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4465:
	.size	_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EEC2EOS3_, .-_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EEC2EOS3_
	.weak	_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EEC1EOS3_
	.set	_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EEC1EOS3_,_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EEC2EOS3_
	.section	.text._ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC2EOS3_,"axG",@progbits,_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC5EOS3_,comdat
	.align 2
	.weak	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC2EOS3_
	.type	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC2EOS3_, @function
_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC2EOS3_:
.LFB4467:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# D.86344, D.86344
# /usr/include/c++/13/bits/unique_ptr.h:366:       unique_ptr(unique_ptr&&) = default;
	movq	-8(%rbp), %rax	# this, _1
	movq	-16(%rbp), %rdx	# D.86344, _2
	movq	%rdx, %rsi	# _2,
	movq	%rax, %rdi	# _1,
	call	_ZNSt15__uniq_ptr_dataI5ShapeSt14default_deleteIS0_ELb1ELb1EEC1EOS3_	#
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4467:
	.size	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC2EOS3_, .-_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC2EOS3_
	.weak	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC1EOS3_
	.set	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC1EOS3_,_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC2EOS3_
	.section	.text._ZSt12construct_atISt10unique_ptrI5ShapeSt14default_deleteIS1_EEJS4_EEDTgsnwcvPvLi0E_T_pispcl7declvalIT0_EEEEPS6_DpOS7_,"axG",@progbits,_ZSt12construct_atISt10unique_ptrI5ShapeSt14default_deleteIS1_EEJS4_EEDTgsnwcvPvLi0E_T_pispcl7declvalIT0_EEEEPS6_DpOS7_,comdat
	.weak	_ZSt12construct_atISt10unique_ptrI5ShapeSt14default_deleteIS1_EEJS4_EEDTgsnwcvPvLi0E_T_pispcl7declvalIT0_EEEEPS6_DpOS7_
	.type	_ZSt12construct_atISt10unique_ptrI5ShapeSt14default_deleteIS1_EEJS4_EEDTgsnwcvPvLi0E_T_pispcl7declvalIT0_EEEEPS6_DpOS7_, @function
_ZSt12construct_atISt10unique_ptrI5ShapeSt14default_deleteIS1_EEJS4_EEDTgsnwcvPvLi0E_T_pispcl7declvalIT0_EEEEPS6_DpOS7_:
.LFB4462:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$24, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)	# __location, __location
	movq	%rsi, -32(%rbp)	# __args#0, __args#0
# /usr/include/c++/13/bits/stl_construct.h:97:     { return ::new((void*)__location) _Tp(std::forward<_Args>(__args)...); }
	movq	-24(%rbp), %rax	# __location, _4
# /usr/include/c++/13/bits/stl_construct.h:97:     { return ::new((void*)__location) _Tp(std::forward<_Args>(__args)...); }
	movq	%rax, %rsi	# _4,
	movl	$8, %edi	#,
	call	_ZnwmPv	#
	movq	%rax, %rbx	#, _1
# /usr/include/c++/13/bits/stl_construct.h:97:     { return ::new((void*)__location) _Tp(std::forward<_Args>(__args)...); }
	movq	-32(%rbp), %rax	# __args#0, tmp88
	movq	%rax, %rdi	# tmp88,
	call	_ZSt7forwardISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEOT_RNSt16remove_referenceIS5_E4typeE	#
# /usr/include/c++/13/bits/stl_construct.h:97:     { return ::new((void*)__location) _Tp(std::forward<_Args>(__args)...); }
	movq	%rax, %rsi	# _2,
	movq	%rbx, %rdi	# _1,
	call	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EEC1EOS3_	#
# /usr/include/c++/13/bits/stl_construct.h:97:     { return ::new((void*)__location) _Tp(std::forward<_Args>(__args)...); }
	movq	%rbx, %rax	# _1, <retval>
# /usr/include/c++/13/bits/stl_construct.h:97:     { return ::new((void*)__location) _Tp(std::forward<_Args>(__args)...); }
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4462:
	.size	_ZSt12construct_atISt10unique_ptrI5ShapeSt14default_deleteIS1_EEJS4_EEDTgsnwcvPvLi0E_T_pispcl7declvalIT0_EEEEPS6_DpOS7_, .-_ZSt12construct_atISt10unique_ptrI5ShapeSt14default_deleteIS1_EEJS4_EEDTgsnwcvPvLi0E_T_pispcl7declvalIT0_EEEEPS6_DpOS7_
	.section	.text._ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE8max_sizeEv,"axG",@progbits,_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE8max_sizeEv,comdat
	.align 2
	.weak	_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE8max_sizeEv
	.type	_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE8max_sizeEv, @function
_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE8max_sizeEv:
.LFB4469:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/bits/stl_vector.h:999:       { return _S_max_size(_M_get_Tp_allocator()); }
	movq	-8(%rbp), %rax	# this, _1
	movq	%rax, %rdi	# _1,
	call	_ZNKSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE19_M_get_Tp_allocatorEv	#
# /usr/include/c++/13/bits/stl_vector.h:999:       { return _S_max_size(_M_get_Tp_allocator()); }
	movq	%rax, %rdi	# _2,
	call	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_S_max_sizeERKS5_	#
# /usr/include/c++/13/bits/stl_vector.h:999:       { return _S_max_size(_M_get_Tp_allocator()); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4469:
	.size	_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE8max_sizeEv, .-_ZNKSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE8max_sizeEv
	.section	.text._ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_M_allocateEm,"axG",@progbits,_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_M_allocateEm,comdat
	.align 2
	.weak	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_M_allocateEm
	.type	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_M_allocateEm, @function
_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_M_allocateEm:
.LFB4470:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$64, %rsp	#,
	movq	%rdi, -56(%rbp)	# this, this
	movq	%rsi, -64(%rbp)	# __n, __n
# /usr/include/c++/13/bits/stl_vector.h:378:       _M_allocate(size_t __n)
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp102
	movq	%rax, -8(%rbp)	# tmp102, D.99521
	xorl	%eax, %eax	# tmp102
# /usr/include/c++/13/bits/stl_vector.h:381: 	return __n != 0 ? _Tr::allocate(_M_impl, __n) : pointer();
	cmpq	$0, -64(%rbp)	#, __n
	je	.L195	#,
# /usr/include/c++/13/bits/stl_vector.h:381: 	return __n != 0 ? _Tr::allocate(_M_impl, __n) : pointer();
	movq	-56(%rbp), %rax	# this, _1
	movq	%rax, -32(%rbp)	# _1, __a
	movq	-64(%rbp), %rax	# __n, tmp94
	movq	%rax, -24(%rbp)	# tmp94, __n
	movq	-32(%rbp), %rax	# __a, tmp95
	movq	%rax, -16(%rbp)	# tmp95, this
	movq	-24(%rbp), %rax	# __n, tmp96
	movq	%rax, -40(%rbp)	# tmp96, __n
# /usr/include/c++/13/bits/allocator.h:191: 	if (std::__is_constant_evaluated())
	call	_ZSt23__is_constant_evaluatedv	#
# /usr/include/c++/13/bits/allocator.h:191: 	if (std::__is_constant_evaluated())
	testb	%al, %al	# retval.7_14
	je	.L196	#,
# /usr/include/c++/13/bits/allocator.h:193: 	    if (__builtin_mul_overflow(__n, sizeof(_Tp), &__n))
	movq	-40(%rbp), %rax	# __n, __n.9_15
	movl	$0, %ecx	#, _16
	leaq	0(,%rax,8), %rdx	#, tmp97
	shrq	$61, %rax	#, tmp98
	testq	%rax, %rax	# tmp98
	je	.L197	#,
	movl	$1, %ecx	#, _16
.L197:
	movq	%rdx, %rax	# tmp97, _16
# /usr/include/c++/13/bits/allocator.h:193: 	    if (__builtin_mul_overflow(__n, sizeof(_Tp), &__n))
	movq	%rax, -40(%rbp)	# _17, __n
	movq	%rcx, %rax	# _16, _18
	andl	$1, %eax	#, retval.8_19
# /usr/include/c++/13/bits/allocator.h:193: 	    if (__builtin_mul_overflow(__n, sizeof(_Tp), &__n))
	testb	%al, %al	# retval.8_19
	je	.L199	#,
# /usr/include/c++/13/bits/allocator.h:194: 	      std::__throw_bad_array_new_length();
	movq	-8(%rbp), %rax	# D.99521, tmp103
	subq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp103
	je	.L200	#,
	call	__stack_chk_fail@PLT	#
.L200:
	call	_ZSt28__throw_bad_array_new_lengthv@PLT	#
.L199:
# /usr/include/c++/13/bits/allocator.h:195: 	    return static_cast<_Tp*>(::operator new(__n));
	movq	-40(%rbp), %rax	# __n, __n.10_20
	movq	%rax, %rdi	# __n.10_20,
	call	_Znwm@PLT	#
# /usr/include/c++/13/bits/allocator.h:195: 	    return static_cast<_Tp*>(::operator new(__n));
	jmp	.L201	#
.L196:
# /usr/include/c++/13/bits/allocator.h:198: 	return __allocator_base<_Tp>::allocate(__n, 0);
	movq	-40(%rbp), %rcx	# __n, __n.11_23
	movq	-16(%rbp), %rax	# this, tmp100
	movl	$0, %edx	#,
	movq	%rcx, %rsi	# __n.11_23,
	movq	%rax, %rdi	# tmp100,
	call	_ZNSt15__new_allocatorISt10unique_ptrI5ShapeSt14default_deleteIS1_EEE8allocateEmPKv	#
# /usr/include/c++/13/bits/allocator.h:198: 	return __allocator_base<_Tp>::allocate(__n, 0);
	nop	
.L201:
# /usr/include/c++/13/bits/alloc_traits.h:482:       { return __a.allocate(__n); }
	nop	
	jmp	.L203	#
.L195:
# /usr/include/c++/13/bits/stl_vector.h:381: 	return __n != 0 ? _Tr::allocate(_M_impl, __n) : pointer();
	movl	$0, %eax	#, D.99476
.L203:
# /usr/include/c++/13/bits/stl_vector.h:382:       }
	movq	-8(%rbp), %rdx	# D.99521, tmp104
	subq	%fs:40, %rdx	# MEM[(<address-space-1> long unsigned int *)40B], tmp104
	je	.L205	#,
	call	__stack_chk_fail@PLT	#
.L205:
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4470:
	.size	_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_M_allocateEm, .-_ZNSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_M_allocateEm
	.section	.text._ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_S_relocateEPS4_S7_S7_RS5_,"axG",@progbits,_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_S_relocateEPS4_S7_S7_RS5_,comdat
	.weak	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_S_relocateEPS4_S7_S7_RS5_
	.type	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_S_relocateEPS4_S7_S7_RS5_, @function
_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_S_relocateEPS4_S7_S7_RS5_:
.LFB4471:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$32, %rsp	#,
	movq	%rdi, -8(%rbp)	# __first, __first
	movq	%rsi, -16(%rbp)	# __last, __last
	movq	%rdx, -24(%rbp)	# __result, __result
	movq	%rcx, -32(%rbp)	# __alloc, __alloc
# /usr/include/c++/13/bits/stl_vector.h:509: 	return std::__relocate_a(__first, __last, __result, __alloc);
	movq	-32(%rbp), %rcx	# __alloc, tmp84
	movq	-24(%rbp), %rdx	# __result, tmp85
	movq	-16(%rbp), %rsi	# __last, tmp86
	movq	-8(%rbp), %rax	# __first, tmp87
	movq	%rax, %rdi	# tmp87,
	call	_ZSt12__relocate_aIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EES5_SaIS4_EET0_T_S8_S7_RT1_	#
# /usr/include/c++/13/bits/stl_vector.h:514:       }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4471:
	.size	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_S_relocateEPS4_S7_S7_RS5_, .-_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_S_relocateEPS4_S7_S7_RS5_
	.section	.text._ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEmiEl,"axG",@progbits,_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEmiEl,comdat
	.align 2
	.weak	_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEmiEl
	.type	_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEmiEl, @function
_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEmiEl:
.LFB4473:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$48, %rsp	#,
	movq	%rdi, -40(%rbp)	# this, this
	movq	%rsi, -48(%rbp)	# __n, __n
# /usr/include/c++/13/bits/stl_iterator.h:1157:       operator-(difference_type __n) const _GLIBCXX_NOEXCEPT
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp93
	movq	%rax, -8(%rbp)	# tmp93, D.99522
	xorl	%eax, %eax	# tmp93
# /usr/include/c++/13/bits/stl_iterator.h:1158:       { return __normal_iterator(_M_current - __n); }
	movq	-40(%rbp), %rax	# this, tmp89
	movq	(%rax), %rax	# this_7(D)->_M_current, _1
# /usr/include/c++/13/bits/stl_iterator.h:1158:       { return __normal_iterator(_M_current - __n); }
	movq	-48(%rbp), %rdx	# __n, __n.14_2
# /usr/include/c++/13/bits/stl_iterator.h:1158:       { return __normal_iterator(_M_current - __n); }
	salq	$3, %rdx	#, _3
	negq	%rdx	# _4
	addq	%rdx, %rax	# _4, _5
	movq	%rax, -24(%rbp)	# _5, D.98145
# /usr/include/c++/13/bits/stl_iterator.h:1158:       { return __normal_iterator(_M_current - __n); }
	leaq	-24(%rbp), %rdx	#, tmp90
	leaq	-16(%rbp), %rax	#, tmp91
	movq	%rdx, %rsi	# tmp90,
	movq	%rax, %rdi	# tmp91,
	call	_ZN9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEC1ERKS6_	#
# /usr/include/c++/13/bits/stl_iterator.h:1158:       { return __normal_iterator(_M_current - __n); }
	movq	-16(%rbp), %rax	# D.98146, D.99204
# /usr/include/c++/13/bits/stl_iterator.h:1158:       { return __normal_iterator(_M_current - __n); }
	movq	-8(%rbp), %rdx	# D.99522, tmp94
	subq	%fs:40, %rdx	# MEM[(<address-space-1> long unsigned int *)40B], tmp94
	je	.L210	#,
	call	__stack_chk_fail@PLT	#
.L210:
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4473:
	.size	_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEmiEl, .-_ZNK9__gnu_cxx17__normal_iteratorIPSt10unique_ptrI5ShapeSt14default_deleteIS2_EESt6vectorIS5_SaIS5_EEEmiEl
	.section	.text._ZNSt5tupleIJP9RectangleSt14default_deleteIS0_EEEC2ILb1ELb1EEEv,"axG",@progbits,_ZNSt5tupleIJP9RectangleSt14default_deleteIS0_EEEC5ILb1ELb1EEEv,comdat
	.align 2
	.weak	_ZNSt5tupleIJP9RectangleSt14default_deleteIS0_EEEC2ILb1ELb1EEEv
	.type	_ZNSt5tupleIJP9RectangleSt14default_deleteIS0_EEEC2ILb1ELb1EEEv, @function
_ZNSt5tupleIJP9RectangleSt14default_deleteIS0_EEEC2ILb1ELb1EEEv:
.LFB4475:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA4475
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/tuple:1319: 	: _Inherited() { }
	movq	-8(%rbp), %rax	# this, _1
	movq	%rax, %rdi	# _1,
	call	_ZNSt11_Tuple_implILm0EJP9RectangleSt14default_deleteIS0_EEEC2Ev	#
# /usr/include/c++/13/tuple:1319: 	: _Inherited() { }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4475:
	.section	.gcc_except_table
.LLSDA4475:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4475-.LLSDACSB4475
.LLSDACSB4475:
.LLSDACSE4475:
	.section	.text._ZNSt5tupleIJP9RectangleSt14default_deleteIS0_EEEC2ILb1ELb1EEEv,"axG",@progbits,_ZNSt5tupleIJP9RectangleSt14default_deleteIS0_EEEC5ILb1ELb1EEEv,comdat
	.size	_ZNSt5tupleIJP9RectangleSt14default_deleteIS0_EEEC2ILb1ELb1EEEv, .-_ZNSt5tupleIJP9RectangleSt14default_deleteIS0_EEEC2ILb1ELb1EEEv
	.weak	_ZNSt5tupleIJP9RectangleSt14default_deleteIS0_EEEC1ILb1ELb1EEEv
	.set	_ZNSt5tupleIJP9RectangleSt14default_deleteIS0_EEEC1ILb1ELb1EEEv,_ZNSt5tupleIJP9RectangleSt14default_deleteIS0_EEEC2ILb1ELb1EEEv
	.section	.text._ZSt12__get_helperILm0EP9RectangleJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE,"axG",@progbits,_ZSt12__get_helperILm0EP9RectangleJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE,comdat
	.weak	_ZSt12__get_helperILm0EP9RectangleJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE
	.type	_ZSt12__get_helperILm0EP9RectangleJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE, @function
_ZSt12__get_helperILm0EP9RectangleJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE:
.LFB4477:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/tuple:1788:     { return _Tuple_impl<__i, _Head, _Tail...>::_M_head(__t); }
	movq	-8(%rbp), %rax	# __t, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZNSt11_Tuple_implILm0EJP9RectangleSt14default_deleteIS0_EEE7_M_headERS4_	#
# /usr/include/c++/13/tuple:1788:     { return _Tuple_impl<__i, _Head, _Tail...>::_M_head(__t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4477:
	.size	_ZSt12__get_helperILm0EP9RectangleJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE, .-_ZSt12__get_helperILm0EP9RectangleJSt14default_deleteIS0_EEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE
	.section	.text._ZSt3getILm1EJP9RectangleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_,"axG",@progbits,_ZSt3getILm1EJP9RectangleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_,comdat
	.weak	_ZSt3getILm1EJP9RectangleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_
	.type	_ZSt3getILm1EJP9RectangleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_, @function
_ZSt3getILm1EJP9RectangleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_:
.LFB4478:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/tuple:1804:     { return std::__get_helper<__i>(__t); }
	movq	-8(%rbp), %rax	# __t, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZSt12__get_helperILm1ESt14default_deleteI9RectangleEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE	#
# /usr/include/c++/13/tuple:1804:     { return std::__get_helper<__i>(__t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4478:
	.size	_ZSt3getILm1EJP9RectangleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_, .-_ZSt3getILm1EJP9RectangleSt14default_deleteIS0_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS8_
	.section	.text._ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2IRS1_JS2_I9RectangleEEvEEOT_DpOT0_,"axG",@progbits,_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC5IRS1_JS2_I9RectangleEEvEEOT_DpOT0_,comdat
	.align 2
	.weak	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2IRS1_JS2_I9RectangleEEvEEOT_DpOT0_
	.type	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2IRS1_JS2_I9RectangleEEvEEOT_DpOT0_, @function
_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2IRS1_JS2_I9RectangleEEvEEOT_DpOT0_:
.LFB4480:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$40, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)	# this, this
	movq	%rsi, -32(%rbp)	# __head, __head
	movq	%rdx, -40(%rbp)	# __tail#0, __tail#0
# /usr/include/c++/13/tuple:293: 	  _Base(std::forward<_UHead>(__head))
	movq	-40(%rbp), %rax	# __tail#0, tmp85
	movq	%rax, %rdi	# tmp85,
	call	_ZSt7forwardISt14default_deleteI9RectangleEEOT_RNSt16remove_referenceIS3_E4typeE	#
	movq	%rax, %rdx	#, _1
# /usr/include/c++/13/tuple:293: 	  _Base(std::forward<_UHead>(__head))
	movq	-24(%rbp), %rax	# this, tmp86
	movq	%rdx, %rsi	# _1,
	movq	%rax, %rdi	# tmp86,
	call	_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2IS0_I9RectangleEEEOT_	#
# /usr/include/c++/13/tuple:293: 	  _Base(std::forward<_UHead>(__head))
	movq	-24(%rbp), %rbx	# this, _2
	movq	-32(%rbp), %rax	# __head, tmp87
	movq	%rax, %rdi	# tmp87,
	call	_ZSt7forwardIRP5ShapeEOT_RNSt16remove_referenceIS3_E4typeE	#
# /usr/include/c++/13/tuple:293: 	  _Base(std::forward<_UHead>(__head))
	movq	%rax, %rsi	# _3,
	movq	%rbx, %rdi	# _2,
	call	_ZNSt10_Head_baseILm0EP5ShapeLb0EEC2IRS1_EEOT_	#
# /usr/include/c++/13/tuple:294: 	{ }
	nop	
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4480:
	.size	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2IRS1_JS2_I9RectangleEEvEEOT_DpOT0_, .-_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2IRS1_JS2_I9RectangleEEvEEOT_DpOT0_
	.weak	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC1IRS1_JS2_I9RectangleEEvEEOT_DpOT0_
	.set	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC1IRS1_JS2_I9RectangleEEvEEOT_DpOT0_,_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2IRS1_JS2_I9RectangleEEvEEOT_DpOT0_
	.section	.text._ZSt3getILm0EJP5ShapeSt14default_deleteIS0_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKS8_,"axG",@progbits,_ZSt3getILm0EJP5ShapeSt14default_deleteIS0_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKS8_,comdat
	.weak	_ZSt3getILm0EJP5ShapeSt14default_deleteIS0_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKS8_
	.type	_ZSt3getILm0EJP5ShapeSt14default_deleteIS0_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKS8_, @function
_ZSt3getILm0EJP5ShapeSt14default_deleteIS0_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKS8_:
.LFB4482:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/tuple:1810:     { return std::__get_helper<__i>(__t); }
	movq	-8(%rbp), %rax	# __t, _1
	movq	%rax, %rdi	# _1,
	call	_ZSt12__get_helperILm0EP5ShapeJSt14default_deleteIS0_EEERKT0_RKSt11_Tuple_implIXT_EJS4_DpT1_EE	#
# /usr/include/c++/13/tuple:1810:     { return std::__get_helper<__i>(__t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4482:
	.size	_ZSt3getILm0EJP5ShapeSt14default_deleteIS0_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKS8_, .-_ZSt3getILm0EJP5ShapeSt14default_deleteIS0_EEERKNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERKS8_
	.section	.text._ZNSt15__new_allocatorISt10unique_ptrI5ShapeSt14default_deleteIS1_EEE10deallocateEPS4_m,"axG",@progbits,_ZNSt15__new_allocatorISt10unique_ptrI5ShapeSt14default_deleteIS1_EEE10deallocateEPS4_m,comdat
	.align 2
	.weak	_ZNSt15__new_allocatorISt10unique_ptrI5ShapeSt14default_deleteIS1_EEE10deallocateEPS4_m
	.type	_ZNSt15__new_allocatorISt10unique_ptrI5ShapeSt14default_deleteIS1_EEE10deallocateEPS4_m, @function
_ZNSt15__new_allocatorISt10unique_ptrI5ShapeSt14default_deleteIS1_EEE10deallocateEPS4_m:
.LFB4521:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$32, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# __p, __p
	movq	%rdx, -24(%rbp)	# __n, __n
# /usr/include/c++/13/bits/new_allocator.h:172: 	_GLIBCXX_OPERATOR_DELETE(_GLIBCXX_SIZED_DEALLOC(__p, __n));
	movq	-24(%rbp), %rax	# __n, tmp83
	leaq	0(,%rax,8), %rdx	#, _2
	movq	-16(%rbp), %rax	# __p, tmp84
	movq	%rdx, %rsi	# _2,
	movq	%rax, %rdi	# tmp84,
	call	_ZdlPvm@PLT	#
# /usr/include/c++/13/bits/new_allocator.h:173:       }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4521:
	.size	_ZNSt15__new_allocatorISt10unique_ptrI5ShapeSt14default_deleteIS1_EEE10deallocateEPS4_m, .-_ZNSt15__new_allocatorISt10unique_ptrI5ShapeSt14default_deleteIS1_EEE10deallocateEPS4_m
	.section	.text._ZSt11__addressofISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEPT_RS5_,"axG",@progbits,_ZSt11__addressofISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEPT_RS5_,comdat
	.weak	_ZSt11__addressofISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEPT_RS5_
	.type	_ZSt11__addressofISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEPT_RS5_, @function
_ZSt11__addressofISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEPT_RS5_:
.LFB4522:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# __r, __r
# /usr/include/c++/13/bits/move.h:52:     { return __builtin_addressof(__r); }
	movq	-8(%rbp), %rax	# __r, _2
# /usr/include/c++/13/bits/move.h:52:     { return __builtin_addressof(__r); }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4522:
	.size	_ZSt11__addressofISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEPT_RS5_, .-_ZSt11__addressofISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEPT_RS5_
	.section	.text._ZSt8_DestroyISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvPT_,"axG",@progbits,_ZSt8_DestroyISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvPT_,comdat
	.weak	_ZSt8_DestroyISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvPT_
	.type	_ZSt8_DestroyISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvPT_, @function
_ZSt8_DestroyISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvPT_:
.LFB4523:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __pointer, __pointer
# /usr/include/c++/13/bits/stl_construct.h:149:       std::destroy_at(__pointer);
	movq	-8(%rbp), %rax	# __pointer, tmp82
	movq	%rax, %rdi	# tmp82,
	call	_ZSt10destroy_atISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvPT_	#
# /usr/include/c++/13/bits/stl_construct.h:153:     }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4523:
	.size	_ZSt8_DestroyISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvPT_, .-_ZSt8_DestroyISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvPT_
	.section	.text._ZNSt11_Tuple_implILm0EJP6CircleSt14default_deleteIS0_EEEC2Ev,"axG",@progbits,_ZNSt11_Tuple_implILm0EJP6CircleSt14default_deleteIS0_EEEC5Ev,comdat
	.align 2
	.weak	_ZNSt11_Tuple_implILm0EJP6CircleSt14default_deleteIS0_EEEC2Ev
	.type	_ZNSt11_Tuple_implILm0EJP6CircleSt14default_deleteIS0_EEEC2Ev, @function
_ZNSt11_Tuple_implILm0EJP6CircleSt14default_deleteIS0_EEEC2Ev:
.LFB4525:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/tuple:281:       : _Inherited(), _Base() { }
	movq	-8(%rbp), %rax	# this, tmp83
	movq	%rax, %rdi	# tmp83,
	call	_ZNSt11_Tuple_implILm1EJSt14default_deleteI6CircleEEEC2Ev	#
# /usr/include/c++/13/tuple:281:       : _Inherited(), _Base() { }
	movq	-8(%rbp), %rax	# this, _1
	movq	%rax, %rdi	# _1,
	call	_ZNSt10_Head_baseILm0EP6CircleLb0EEC2Ev	#
# /usr/include/c++/13/tuple:281:       : _Inherited(), _Base() { }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4525:
	.size	_ZNSt11_Tuple_implILm0EJP6CircleSt14default_deleteIS0_EEEC2Ev, .-_ZNSt11_Tuple_implILm0EJP6CircleSt14default_deleteIS0_EEEC2Ev
	.weak	_ZNSt11_Tuple_implILm0EJP6CircleSt14default_deleteIS0_EEEC1Ev
	.set	_ZNSt11_Tuple_implILm0EJP6CircleSt14default_deleteIS0_EEEC1Ev,_ZNSt11_Tuple_implILm0EJP6CircleSt14default_deleteIS0_EEEC2Ev
	.section	.text._ZNSt11_Tuple_implILm0EJP6CircleSt14default_deleteIS0_EEE7_M_headERS4_,"axG",@progbits,_ZNSt11_Tuple_implILm0EJP6CircleSt14default_deleteIS0_EEE7_M_headERS4_,comdat
	.weak	_ZNSt11_Tuple_implILm0EJP6CircleSt14default_deleteIS0_EEE7_M_headERS4_
	.type	_ZNSt11_Tuple_implILm0EJP6CircleSt14default_deleteIS0_EEE7_M_headERS4_, @function
_ZNSt11_Tuple_implILm0EJP6CircleSt14default_deleteIS0_EEE7_M_headERS4_:
.LFB4527:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/tuple:269:       _M_head(_Tuple_impl& __t) noexcept { return _Base::_M_head(__t); }
	movq	-8(%rbp), %rax	# __t, _1
	movq	%rax, %rdi	# _1,
	call	_ZNSt10_Head_baseILm0EP6CircleLb0EE7_M_headERS2_	#
# /usr/include/c++/13/tuple:269:       _M_head(_Tuple_impl& __t) noexcept { return _Base::_M_head(__t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4527:
	.size	_ZNSt11_Tuple_implILm0EJP6CircleSt14default_deleteIS0_EEE7_M_headERS4_, .-_ZNSt11_Tuple_implILm0EJP6CircleSt14default_deleteIS0_EEE7_M_headERS4_
	.section	.text._ZSt12__get_helperILm1ESt14default_deleteI6CircleEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE,"axG",@progbits,_ZSt12__get_helperILm1ESt14default_deleteI6CircleEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE,comdat
	.weak	_ZSt12__get_helperILm1ESt14default_deleteI6CircleEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE
	.type	_ZSt12__get_helperILm1ESt14default_deleteI6CircleEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE, @function
_ZSt12__get_helperILm1ESt14default_deleteI6CircleEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE:
.LFB4528:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/tuple:1788:     { return _Tuple_impl<__i, _Head, _Tail...>::_M_head(__t); }
	movq	-8(%rbp), %rax	# __t, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZNSt11_Tuple_implILm1EJSt14default_deleteI6CircleEEE7_M_headERS3_	#
# /usr/include/c++/13/tuple:1788:     { return _Tuple_impl<__i, _Head, _Tail...>::_M_head(__t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4528:
	.size	_ZSt12__get_helperILm1ESt14default_deleteI6CircleEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE, .-_ZSt12__get_helperILm1ESt14default_deleteI6CircleEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE
	.section	.text._ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2IS0_I6CircleEEEOT_,"axG",@progbits,_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC5IS0_I6CircleEEEOT_,comdat
	.align 2
	.weak	_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2IS0_I6CircleEEEOT_
	.type	_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2IS0_I6CircleEEEOT_, @function
_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2IS0_I6CircleEEEOT_:
.LFB4530:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# __head, __head
# /usr/include/c++/13/tuple:514: 	: _Base(std::forward<_UHead>(__head))
	movq	-16(%rbp), %rax	# __head, tmp83
	movq	%rax, %rdi	# tmp83,
	call	_ZSt7forwardISt14default_deleteI6CircleEEOT_RNSt16remove_referenceIS3_E4typeE	#
	movq	%rax, %rdx	#, _1
# /usr/include/c++/13/tuple:514: 	: _Base(std::forward<_UHead>(__head))
	movq	-8(%rbp), %rax	# this, tmp84
	movq	%rdx, %rsi	# _1,
	movq	%rax, %rdi	# tmp84,
	call	_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EEC2IS0_I6CircleEEEOT_	#
# /usr/include/c++/13/tuple:515: 	{ }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4530:
	.size	_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2IS0_I6CircleEEEOT_, .-_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2IS0_I6CircleEEEOT_
	.weak	_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC1IS0_I6CircleEEEOT_
	.set	_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC1IS0_I6CircleEEEOT_,_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2IS0_I6CircleEEEOT_
	.section	.text._ZNSt10_Head_baseILm0EP5ShapeLb0EEC2IRS1_EEOT_,"axG",@progbits,_ZNSt10_Head_baseILm0EP5ShapeLb0EEC5IRS1_EEOT_,comdat
	.align 2
	.weak	_ZNSt10_Head_baseILm0EP5ShapeLb0EEC2IRS1_EEOT_
	.type	_ZNSt10_Head_baseILm0EP5ShapeLb0EEC2IRS1_EEOT_, @function
_ZNSt10_Head_baseILm0EP5ShapeLb0EEC2IRS1_EEOT_:
.LFB4533:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# __h, __h
# /usr/include/c++/13/tuple:201: 	: _M_head_impl(std::forward<_UHead>(__h)) { }
	movq	-16(%rbp), %rax	# __h, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZSt7forwardIRP5ShapeEOT_RNSt16remove_referenceIS3_E4typeE	#
# /usr/include/c++/13/tuple:201: 	: _M_head_impl(std::forward<_UHead>(__h)) { }
	movq	(%rax), %rdx	# *_1, _2
	movq	-8(%rbp), %rax	# this, tmp85
	movq	%rdx, (%rax)	# _2, this_4(D)->_M_head_impl
# /usr/include/c++/13/tuple:201: 	: _M_head_impl(std::forward<_UHead>(__h)) { }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4533:
	.size	_ZNSt10_Head_baseILm0EP5ShapeLb0EEC2IRS1_EEOT_, .-_ZNSt10_Head_baseILm0EP5ShapeLb0EEC2IRS1_EEOT_
	.weak	_ZNSt10_Head_baseILm0EP5ShapeLb0EEC1IRS1_EEOT_
	.set	_ZNSt10_Head_baseILm0EP5ShapeLb0EEC1IRS1_EEOT_,_ZNSt10_Head_baseILm0EP5ShapeLb0EEC2IRS1_EEOT_
	.section	.text._ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEE7_M_headERS4_,"axG",@progbits,_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEE7_M_headERS4_,comdat
	.weak	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEE7_M_headERS4_
	.type	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEE7_M_headERS4_, @function
_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEE7_M_headERS4_:
.LFB4535:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/tuple:269:       _M_head(_Tuple_impl& __t) noexcept { return _Base::_M_head(__t); }
	movq	-8(%rbp), %rax	# __t, _1
	movq	%rax, %rdi	# _1,
	call	_ZNSt10_Head_baseILm0EP5ShapeLb0EE7_M_headERS2_	#
# /usr/include/c++/13/tuple:269:       _M_head(_Tuple_impl& __t) noexcept { return _Base::_M_head(__t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4535:
	.size	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEE7_M_headERS4_, .-_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEE7_M_headERS4_
	.section	.text._ZSt12__get_helperILm1ESt14default_deleteI5ShapeEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE,"axG",@progbits,_ZSt12__get_helperILm1ESt14default_deleteI5ShapeEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE,comdat
	.weak	_ZSt12__get_helperILm1ESt14default_deleteI5ShapeEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE
	.type	_ZSt12__get_helperILm1ESt14default_deleteI5ShapeEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE, @function
_ZSt12__get_helperILm1ESt14default_deleteI5ShapeEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE:
.LFB4536:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/tuple:1788:     { return _Tuple_impl<__i, _Head, _Tail...>::_M_head(__t); }
	movq	-8(%rbp), %rax	# __t, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEE7_M_headERS3_	#
# /usr/include/c++/13/tuple:1788:     { return _Tuple_impl<__i, _Head, _Tail...>::_M_head(__t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4536:
	.size	_ZSt12__get_helperILm1ESt14default_deleteI5ShapeEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE, .-_ZSt12__get_helperILm1ESt14default_deleteI5ShapeEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE
	.section	.text._ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2EOS4_,"axG",@progbits,_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC5EOS4_,comdat
	.align 2
	.weak	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2EOS4_
	.type	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2EOS4_, @function
_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2EOS4_:
.LFB4540:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# D.84721, D.84721
# /usr/include/c++/13/tuple:302:       _Tuple_impl(_Tuple_impl&&) = default;
	movq	-16(%rbp), %rdx	# D.84721, tmp82
	movq	-8(%rbp), %rax	# this, tmp83
	movq	%rdx, %rsi	# tmp82,
	movq	%rax, %rdi	# tmp83,
	call	_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2EOS3_	#
# /usr/include/c++/13/tuple:302:       _Tuple_impl(_Tuple_impl&&) = default;
	movq	-8(%rbp), %rax	# this, tmp84
	movq	-16(%rbp), %rdx	# D.84721, tmp85
	movq	(%rdx), %rdx	# _4(D)->D.84751, tmp86
	movq	%rdx, (%rax)	# tmp86, this_2(D)->D.84751
# /usr/include/c++/13/tuple:302:       _Tuple_impl(_Tuple_impl&&) = default;
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4540:
	.size	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2EOS4_, .-_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2EOS4_
	.weak	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC1EOS4_
	.set	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC1EOS4_,_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2EOS4_
	.section	.text._ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC2EOS4_,"axG",@progbits,_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC5EOS4_,comdat
	.align 2
	.weak	_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC2EOS4_
	.type	_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC2EOS4_, @function
_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC2EOS4_:
.LFB4542:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# D.85764, D.85764
# /usr/include/c++/13/tuple:1358:       constexpr tuple(tuple&&) = default;
	movq	-8(%rbp), %rax	# this, _1
	movq	-16(%rbp), %rdx	# D.85764, _2
	movq	%rdx, %rsi	# _2,
	movq	%rax, %rdi	# _1,
	call	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEEC2EOS4_	#
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4542:
	.size	_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC2EOS4_, .-_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC2EOS4_
	.weak	_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC1EOS4_
	.set	_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC1EOS4_,_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC2EOS4_
	.section	.text._ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2EOS3_,"axG",@progbits,_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC5EOS3_,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2EOS3_
	.type	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2EOS3_, @function
_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2EOS3_:
.LFB4544:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$24, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)	# this, this
	movq	%rsi, -32(%rbp)	# __u, __u
# /usr/include/c++/13/bits/unique_ptr.h:185:       : _M_t(std::move(__u._M_t))
	movq	-24(%rbp), %rbx	# this, _1
# /usr/include/c++/13/bits/unique_ptr.h:185:       : _M_t(std::move(__u._M_t))
	movq	-32(%rbp), %rax	# __u, _2
# /usr/include/c++/13/bits/unique_ptr.h:185:       : _M_t(std::move(__u._M_t))
	movq	%rax, %rdi	# _2,
	call	_ZSt4moveIRSt5tupleIJP5ShapeSt14default_deleteIS1_EEEEONSt16remove_referenceIT_E4typeEOS8_	#
# /usr/include/c++/13/bits/unique_ptr.h:185:       : _M_t(std::move(__u._M_t))
	movq	%rax, %rsi	# _3,
	movq	%rbx, %rdi	# _1,
	call	_ZNSt5tupleIJP5ShapeSt14default_deleteIS0_EEEC1EOS4_	#
# /usr/include/c++/13/bits/unique_ptr.h:186:       { __u._M_ptr() = nullptr; }
	movq	-32(%rbp), %rax	# __u, tmp86
	movq	%rax, %rdi	# tmp86,
	call	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EE6_M_ptrEv	#
# /usr/include/c++/13/bits/unique_ptr.h:186:       { __u._M_ptr() = nullptr; }
	movq	$0, (%rax)	#, *_4
# /usr/include/c++/13/bits/unique_ptr.h:186:       { __u._M_ptr() = nullptr; }
	nop	
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4544:
	.size	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2EOS3_, .-_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2EOS3_
	.weak	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC1EOS3_
	.set	_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC1EOS3_,_ZNSt15__uniq_ptr_implI5ShapeSt14default_deleteIS0_EEC2EOS3_
	.section	.text._ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_S_max_sizeERKS5_,"axG",@progbits,_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_S_max_sizeERKS5_,comdat
	.weak	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_S_max_sizeERKS5_
	.type	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_S_max_sizeERKS5_, @function
_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_S_max_sizeERKS5_:
.LFB4546:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$48, %rsp	#,
	movq	%rdi, -40(%rbp)	# __a, __a
# /usr/include/c++/13/bits/stl_vector.h:1916:       _S_max_size(const _Tp_alloc_type& __a) _GLIBCXX_NOEXCEPT
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp90
	movq	%rax, -8(%rbp)	# tmp90, D.99523
	xorl	%eax, %eax	# tmp90
# /usr/include/c++/13/bits/stl_vector.h:1921: 	const size_t __diffmax
	movabsq	$1152921504606846975, %rax	#, tmp93
	movq	%rax, -32(%rbp)	# tmp93, __diffmax
	movq	-40(%rbp), %rax	# __a, tmp86
	movq	%rax, -16(%rbp)	# tmp86, __a
# /usr/include/c++/13/bits/alloc_traits.h:576: 	return size_t(-1) / sizeof(value_type);
	movabsq	$2305843009213693951, %rax	#, D.99458
# /usr/include/c++/13/bits/stl_vector.h:1923: 	const size_t __allocmax = _Alloc_traits::max_size(__a);
	movq	%rax, -24(%rbp)	# D.99458, __allocmax
# /usr/include/c++/13/bits/stl_vector.h:1924: 	return (std::min)(__diffmax, __allocmax);
	leaq	-24(%rbp), %rdx	#, tmp87
	leaq	-32(%rbp), %rax	#, tmp88
	movq	%rdx, %rsi	# tmp87,
	movq	%rax, %rdi	# tmp88,
	call	_ZSt3minImERKT_S2_S2_	#
# /usr/include/c++/13/bits/stl_vector.h:1924: 	return (std::min)(__diffmax, __allocmax);
	movq	(%rax), %rax	# *_2, _8
# /usr/include/c++/13/bits/stl_vector.h:1925:       }
	movq	-8(%rbp), %rdx	# D.99523, tmp91
	subq	%fs:40, %rdx	# MEM[(<address-space-1> long unsigned int *)40B], tmp91
	je	.L241	#,
	call	__stack_chk_fail@PLT	#
.L241:
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4546:
	.size	_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_S_max_sizeERKS5_, .-_ZNSt6vectorISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE11_S_max_sizeERKS5_
	.section	.text._ZNKSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE19_M_get_Tp_allocatorEv,"axG",@progbits,_ZNKSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE19_M_get_Tp_allocatorEv,comdat
	.align 2
	.weak	_ZNKSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE19_M_get_Tp_allocatorEv
	.type	_ZNKSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE19_M_get_Tp_allocatorEv, @function
_ZNKSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE19_M_get_Tp_allocatorEv:
.LFB4548:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/bits/stl_vector.h:307:       { return this->_M_impl; }
	movq	-8(%rbp), %rax	# this, _2
# /usr/include/c++/13/bits/stl_vector.h:307:       { return this->_M_impl; }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4548:
	.size	_ZNKSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE19_M_get_Tp_allocatorEv, .-_ZNKSt12_Vector_baseISt10unique_ptrI5ShapeSt14default_deleteIS1_EESaIS4_EE19_M_get_Tp_allocatorEv
	.section	.text._ZSt12__relocate_aIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EES5_SaIS4_EET0_T_S8_S7_RT1_,"axG",@progbits,_ZSt12__relocate_aIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EES5_SaIS4_EET0_T_S8_S7_RT1_,comdat
	.weak	_ZSt12__relocate_aIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EES5_SaIS4_EET0_T_S8_S7_RT1_
	.type	_ZSt12__relocate_aIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EES5_SaIS4_EET0_T_S8_S7_RT1_, @function
_ZSt12__relocate_aIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EES5_SaIS4_EET0_T_S8_S7_RT1_:
.LFB4550:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%r12	#
	pushq	%rbx	#
	subq	$32, %rsp	#,
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -24(%rbp)	# __first, __first
	movq	%rsi, -32(%rbp)	# __last, __last
	movq	%rdx, -40(%rbp)	# __result, __result
	movq	%rcx, -48(%rbp)	# __alloc, __alloc
# /usr/include/c++/13/bits/stl_uninitialized.h:1147:       return std::__relocate_a_1(std::__niter_base(__first),
	movq	-40(%rbp), %rax	# __result, tmp87
	movq	%rax, %rdi	# tmp87,
	call	_ZSt12__niter_baseIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EEET_S6_	#
	movq	%rax, %r12	#, _1
# /usr/include/c++/13/bits/stl_uninitialized.h:1147:       return std::__relocate_a_1(std::__niter_base(__first),
	movq	-32(%rbp), %rax	# __last, tmp88
	movq	%rax, %rdi	# tmp88,
	call	_ZSt12__niter_baseIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EEET_S6_	#
	movq	%rax, %rbx	#, _2
# /usr/include/c++/13/bits/stl_uninitialized.h:1147:       return std::__relocate_a_1(std::__niter_base(__first),
	movq	-24(%rbp), %rax	# __first, tmp89
	movq	%rax, %rdi	# tmp89,
	call	_ZSt12__niter_baseIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EEET_S6_	#
	movq	%rax, %rdi	#, _3
# /usr/include/c++/13/bits/stl_uninitialized.h:1147:       return std::__relocate_a_1(std::__niter_base(__first),
	movq	-48(%rbp), %rax	# __alloc, tmp90
	movq	%rax, %rcx	# tmp90,
	movq	%r12, %rdx	# _1,
	movq	%rbx, %rsi	# _2,
	call	_ZSt14__relocate_a_1IPSt10unique_ptrI5ShapeSt14default_deleteIS1_EES5_SaIS4_EET0_T_S8_S7_RT1_	#
# /usr/include/c++/13/bits/stl_uninitialized.h:1150:     }
	addq	$32, %rsp	#,
	popq	%rbx	#
	popq	%r12	#
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4550:
	.size	_ZSt12__relocate_aIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EES5_SaIS4_EET0_T_S8_S7_RT1_, .-_ZSt12__relocate_aIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EES5_SaIS4_EET0_T_S8_S7_RT1_
	.section	.text._ZSt10destroy_atISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvPT_,"axG",@progbits,_ZSt10destroy_atISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvPT_,comdat
	.weak	_ZSt10destroy_atISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvPT_
	.type	_ZSt10destroy_atISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvPT_, @function
_ZSt10destroy_atISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvPT_:
.LFB4551:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __location, __location
# /usr/include/c++/13/bits/stl_construct.h:88: 	__location->~_Tp();
	movq	-8(%rbp), %rax	# __location, tmp82
	movq	%rax, %rdi	# tmp82,
	call	_ZNSt10unique_ptrI5ShapeSt14default_deleteIS0_EED1Ev	#
# /usr/include/c++/13/bits/stl_construct.h:89:     }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4551:
	.size	_ZSt10destroy_atISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvPT_, .-_ZSt10destroy_atISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvPT_
	.section	.text._ZNSt11_Tuple_implILm0EJP9RectangleSt14default_deleteIS0_EEEC2Ev,"axG",@progbits,_ZNSt11_Tuple_implILm0EJP9RectangleSt14default_deleteIS0_EEEC5Ev,comdat
	.align 2
	.weak	_ZNSt11_Tuple_implILm0EJP9RectangleSt14default_deleteIS0_EEEC2Ev
	.type	_ZNSt11_Tuple_implILm0EJP9RectangleSt14default_deleteIS0_EEEC2Ev, @function
_ZNSt11_Tuple_implILm0EJP9RectangleSt14default_deleteIS0_EEEC2Ev:
.LFB4553:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/tuple:281:       : _Inherited(), _Base() { }
	movq	-8(%rbp), %rax	# this, tmp83
	movq	%rax, %rdi	# tmp83,
	call	_ZNSt11_Tuple_implILm1EJSt14default_deleteI9RectangleEEEC2Ev	#
# /usr/include/c++/13/tuple:281:       : _Inherited(), _Base() { }
	movq	-8(%rbp), %rax	# this, _1
	movq	%rax, %rdi	# _1,
	call	_ZNSt10_Head_baseILm0EP9RectangleLb0EEC2Ev	#
# /usr/include/c++/13/tuple:281:       : _Inherited(), _Base() { }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4553:
	.size	_ZNSt11_Tuple_implILm0EJP9RectangleSt14default_deleteIS0_EEEC2Ev, .-_ZNSt11_Tuple_implILm0EJP9RectangleSt14default_deleteIS0_EEEC2Ev
	.weak	_ZNSt11_Tuple_implILm0EJP9RectangleSt14default_deleteIS0_EEEC1Ev
	.set	_ZNSt11_Tuple_implILm0EJP9RectangleSt14default_deleteIS0_EEEC1Ev,_ZNSt11_Tuple_implILm0EJP9RectangleSt14default_deleteIS0_EEEC2Ev
	.section	.text._ZNSt11_Tuple_implILm0EJP9RectangleSt14default_deleteIS0_EEE7_M_headERS4_,"axG",@progbits,_ZNSt11_Tuple_implILm0EJP9RectangleSt14default_deleteIS0_EEE7_M_headERS4_,comdat
	.weak	_ZNSt11_Tuple_implILm0EJP9RectangleSt14default_deleteIS0_EEE7_M_headERS4_
	.type	_ZNSt11_Tuple_implILm0EJP9RectangleSt14default_deleteIS0_EEE7_M_headERS4_, @function
_ZNSt11_Tuple_implILm0EJP9RectangleSt14default_deleteIS0_EEE7_M_headERS4_:
.LFB4555:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/tuple:269:       _M_head(_Tuple_impl& __t) noexcept { return _Base::_M_head(__t); }
	movq	-8(%rbp), %rax	# __t, _1
	movq	%rax, %rdi	# _1,
	call	_ZNSt10_Head_baseILm0EP9RectangleLb0EE7_M_headERS2_	#
# /usr/include/c++/13/tuple:269:       _M_head(_Tuple_impl& __t) noexcept { return _Base::_M_head(__t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4555:
	.size	_ZNSt11_Tuple_implILm0EJP9RectangleSt14default_deleteIS0_EEE7_M_headERS4_, .-_ZNSt11_Tuple_implILm0EJP9RectangleSt14default_deleteIS0_EEE7_M_headERS4_
	.section	.text._ZSt12__get_helperILm1ESt14default_deleteI9RectangleEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE,"axG",@progbits,_ZSt12__get_helperILm1ESt14default_deleteI9RectangleEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE,comdat
	.weak	_ZSt12__get_helperILm1ESt14default_deleteI9RectangleEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE
	.type	_ZSt12__get_helperILm1ESt14default_deleteI9RectangleEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE, @function
_ZSt12__get_helperILm1ESt14default_deleteI9RectangleEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE:
.LFB4556:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/tuple:1788:     { return _Tuple_impl<__i, _Head, _Tail...>::_M_head(__t); }
	movq	-8(%rbp), %rax	# __t, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZNSt11_Tuple_implILm1EJSt14default_deleteI9RectangleEEE7_M_headERS3_	#
# /usr/include/c++/13/tuple:1788:     { return _Tuple_impl<__i, _Head, _Tail...>::_M_head(__t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4556:
	.size	_ZSt12__get_helperILm1ESt14default_deleteI9RectangleEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE, .-_ZSt12__get_helperILm1ESt14default_deleteI9RectangleEJEERT0_RSt11_Tuple_implIXT_EJS3_DpT1_EE
	.section	.text._ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2IS0_I9RectangleEEEOT_,"axG",@progbits,_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC5IS0_I9RectangleEEEOT_,comdat
	.align 2
	.weak	_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2IS0_I9RectangleEEEOT_
	.type	_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2IS0_I9RectangleEEEOT_, @function
_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2IS0_I9RectangleEEEOT_:
.LFB4558:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# __head, __head
# /usr/include/c++/13/tuple:514: 	: _Base(std::forward<_UHead>(__head))
	movq	-16(%rbp), %rax	# __head, tmp83
	movq	%rax, %rdi	# tmp83,
	call	_ZSt7forwardISt14default_deleteI9RectangleEEOT_RNSt16remove_referenceIS3_E4typeE	#
	movq	%rax, %rdx	#, _1
# /usr/include/c++/13/tuple:514: 	: _Base(std::forward<_UHead>(__head))
	movq	-8(%rbp), %rax	# this, tmp84
	movq	%rdx, %rsi	# _1,
	movq	%rax, %rdi	# tmp84,
	call	_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EEC2IS0_I9RectangleEEEOT_	#
# /usr/include/c++/13/tuple:515: 	{ }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4558:
	.size	_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2IS0_I9RectangleEEEOT_, .-_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2IS0_I9RectangleEEEOT_
	.weak	_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC1IS0_I9RectangleEEEOT_
	.set	_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC1IS0_I9RectangleEEEOT_,_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2IS0_I9RectangleEEEOT_
	.section	.text._ZSt12__get_helperILm0EP5ShapeJSt14default_deleteIS0_EEERKT0_RKSt11_Tuple_implIXT_EJS4_DpT1_EE,"axG",@progbits,_ZSt12__get_helperILm0EP5ShapeJSt14default_deleteIS0_EEERKT0_RKSt11_Tuple_implIXT_EJS4_DpT1_EE,comdat
	.weak	_ZSt12__get_helperILm0EP5ShapeJSt14default_deleteIS0_EEERKT0_RKSt11_Tuple_implIXT_EJS4_DpT1_EE
	.type	_ZSt12__get_helperILm0EP5ShapeJSt14default_deleteIS0_EEERKT0_RKSt11_Tuple_implIXT_EJS4_DpT1_EE, @function
_ZSt12__get_helperILm0EP5ShapeJSt14default_deleteIS0_EEERKT0_RKSt11_Tuple_implIXT_EJS4_DpT1_EE:
.LFB4560:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/tuple:1793:     { return _Tuple_impl<__i, _Head, _Tail...>::_M_head(__t); }
	movq	-8(%rbp), %rax	# __t, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEE7_M_headERKS4_	#
# /usr/include/c++/13/tuple:1793:     { return _Tuple_impl<__i, _Head, _Tail...>::_M_head(__t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4560:
	.size	_ZSt12__get_helperILm0EP5ShapeJSt14default_deleteIS0_EEERKT0_RKSt11_Tuple_implIXT_EJS4_DpT1_EE, .-_ZSt12__get_helperILm0EP5ShapeJSt14default_deleteIS0_EEERKT0_RKSt11_Tuple_implIXT_EJS4_DpT1_EE
	.section	.text._ZNSt11_Tuple_implILm1EJSt14default_deleteI6CircleEEEC2Ev,"axG",@progbits,_ZNSt11_Tuple_implILm1EJSt14default_deleteI6CircleEEEC5Ev,comdat
	.align 2
	.weak	_ZNSt11_Tuple_implILm1EJSt14default_deleteI6CircleEEEC2Ev
	.type	_ZNSt11_Tuple_implILm1EJSt14default_deleteI6CircleEEEC2Ev, @function
_ZNSt11_Tuple_implILm1EJSt14default_deleteI6CircleEEEC2Ev:
.LFB4578:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/tuple:504:       : _Base() { }
	movq	-8(%rbp), %rax	# this, tmp82
	movq	%rax, %rdi	# tmp82,
	call	_ZNSt10_Head_baseILm1ESt14default_deleteI6CircleELb1EEC2Ev	#
# /usr/include/c++/13/tuple:504:       : _Base() { }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4578:
	.size	_ZNSt11_Tuple_implILm1EJSt14default_deleteI6CircleEEEC2Ev, .-_ZNSt11_Tuple_implILm1EJSt14default_deleteI6CircleEEEC2Ev
	.weak	_ZNSt11_Tuple_implILm1EJSt14default_deleteI6CircleEEEC1Ev
	.set	_ZNSt11_Tuple_implILm1EJSt14default_deleteI6CircleEEEC1Ev,_ZNSt11_Tuple_implILm1EJSt14default_deleteI6CircleEEEC2Ev
	.section	.text._ZNSt10_Head_baseILm0EP6CircleLb0EEC2Ev,"axG",@progbits,_ZNSt10_Head_baseILm0EP6CircleLb0EEC5Ev,comdat
	.align 2
	.weak	_ZNSt10_Head_baseILm0EP6CircleLb0EEC2Ev
	.type	_ZNSt10_Head_baseILm0EP6CircleLb0EEC2Ev, @function
_ZNSt10_Head_baseILm0EP6CircleLb0EEC2Ev:
.LFB4581:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/tuple:191:       : _M_head_impl() { }
	movq	-8(%rbp), %rax	# this, tmp82
	movq	$0, (%rax)	#, this_2(D)->_M_head_impl
# /usr/include/c++/13/tuple:191:       : _M_head_impl() { }
	nop	
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4581:
	.size	_ZNSt10_Head_baseILm0EP6CircleLb0EEC2Ev, .-_ZNSt10_Head_baseILm0EP6CircleLb0EEC2Ev
	.weak	_ZNSt10_Head_baseILm0EP6CircleLb0EEC1Ev
	.set	_ZNSt10_Head_baseILm0EP6CircleLb0EEC1Ev,_ZNSt10_Head_baseILm0EP6CircleLb0EEC2Ev
	.section	.text._ZNSt10_Head_baseILm0EP6CircleLb0EE7_M_headERS2_,"axG",@progbits,_ZNSt10_Head_baseILm0EP6CircleLb0EE7_M_headERS2_,comdat
	.weak	_ZNSt10_Head_baseILm0EP6CircleLb0EE7_M_headERS2_
	.type	_ZNSt10_Head_baseILm0EP6CircleLb0EE7_M_headERS2_, @function
_ZNSt10_Head_baseILm0EP6CircleLb0EE7_M_headERS2_:
.LFB4583:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# __b, __b
# /usr/include/c++/13/tuple:234:       _M_head(_Head_base& __b) noexcept { return __b._M_head_impl; }
	movq	-8(%rbp), %rax	# __b, _2
# /usr/include/c++/13/tuple:234:       _M_head(_Head_base& __b) noexcept { return __b._M_head_impl; }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4583:
	.size	_ZNSt10_Head_baseILm0EP6CircleLb0EE7_M_headERS2_, .-_ZNSt10_Head_baseILm0EP6CircleLb0EE7_M_headERS2_
	.section	.text._ZNSt11_Tuple_implILm1EJSt14default_deleteI6CircleEEE7_M_headERS3_,"axG",@progbits,_ZNSt11_Tuple_implILm1EJSt14default_deleteI6CircleEEE7_M_headERS3_,comdat
	.weak	_ZNSt11_Tuple_implILm1EJSt14default_deleteI6CircleEEE7_M_headERS3_
	.type	_ZNSt11_Tuple_implILm1EJSt14default_deleteI6CircleEEE7_M_headERS3_, @function
_ZNSt11_Tuple_implILm1EJSt14default_deleteI6CircleEEE7_M_headERS3_:
.LFB4584:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/tuple:497:       _M_head(_Tuple_impl& __t) noexcept { return _Base::_M_head(__t); }
	movq	-8(%rbp), %rax	# __t, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZNSt10_Head_baseILm1ESt14default_deleteI6CircleELb1EE7_M_headERS3_	#
# /usr/include/c++/13/tuple:497:       _M_head(_Tuple_impl& __t) noexcept { return _Base::_M_head(__t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4584:
	.size	_ZNSt11_Tuple_implILm1EJSt14default_deleteI6CircleEEE7_M_headERS3_, .-_ZNSt11_Tuple_implILm1EJSt14default_deleteI6CircleEEE7_M_headERS3_
	.section	.text._ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EEC2IS0_I6CircleEEEOT_,"axG",@progbits,_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EEC5IS0_I6CircleEEEOT_,comdat
	.align 2
	.weak	_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EEC2IS0_I6CircleEEEOT_
	.type	_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EEC2IS0_I6CircleEEEOT_, @function
_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EEC2IS0_I6CircleEEEOT_:
.LFB4586:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$24, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)	# this, this
	movq	%rsi, -32(%rbp)	# __h, __h
# /usr/include/c++/13/tuple:92: 	: _M_head_impl(std::forward<_UHead>(__h)) { }
	movq	-24(%rbp), %rbx	# this, _1
# /usr/include/c++/13/tuple:92: 	: _M_head_impl(std::forward<_UHead>(__h)) { }
	movq	-32(%rbp), %rax	# __h, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZSt7forwardISt14default_deleteI6CircleEEOT_RNSt16remove_referenceIS3_E4typeE	#
# /usr/include/c++/13/tuple:92: 	: _M_head_impl(std::forward<_UHead>(__h)) { }
	movq	%rax, %rsi	# _2,
	movq	%rbx, %rdi	# _1,
	call	_ZNSt14default_deleteI5ShapeEC1I6CirclevEERKS_IT_E	#
# /usr/include/c++/13/tuple:92: 	: _M_head_impl(std::forward<_UHead>(__h)) { }
	nop	
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4586:
	.size	_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EEC2IS0_I6CircleEEEOT_, .-_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EEC2IS0_I6CircleEEEOT_
	.weak	_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EEC1IS0_I6CircleEEEOT_
	.set	_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EEC1IS0_I6CircleEEEOT_,_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EEC2IS0_I6CircleEEEOT_
	.section	.text._ZNSt10_Head_baseILm0EP5ShapeLb0EE7_M_headERS2_,"axG",@progbits,_ZNSt10_Head_baseILm0EP5ShapeLb0EE7_M_headERS2_,comdat
	.weak	_ZNSt10_Head_baseILm0EP5ShapeLb0EE7_M_headERS2_
	.type	_ZNSt10_Head_baseILm0EP5ShapeLb0EE7_M_headERS2_, @function
_ZNSt10_Head_baseILm0EP5ShapeLb0EE7_M_headERS2_:
.LFB4588:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# __b, __b
# /usr/include/c++/13/tuple:234:       _M_head(_Head_base& __b) noexcept { return __b._M_head_impl; }
	movq	-8(%rbp), %rax	# __b, _2
# /usr/include/c++/13/tuple:234:       _M_head(_Head_base& __b) noexcept { return __b._M_head_impl; }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4588:
	.size	_ZNSt10_Head_baseILm0EP5ShapeLb0EE7_M_headERS2_, .-_ZNSt10_Head_baseILm0EP5ShapeLb0EE7_M_headERS2_
	.section	.text._ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEE7_M_headERS3_,"axG",@progbits,_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEE7_M_headERS3_,comdat
	.weak	_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEE7_M_headERS3_
	.type	_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEE7_M_headERS3_, @function
_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEE7_M_headERS3_:
.LFB4589:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/tuple:497:       _M_head(_Tuple_impl& __t) noexcept { return _Base::_M_head(__t); }
	movq	-8(%rbp), %rax	# __t, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EE7_M_headERS3_	#
# /usr/include/c++/13/tuple:497:       _M_head(_Tuple_impl& __t) noexcept { return _Base::_M_head(__t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4589:
	.size	_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEE7_M_headERS3_, .-_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEE7_M_headERS3_
	.section	.text._ZSt4moveIRSt5tupleIJP5ShapeSt14default_deleteIS1_EEEEONSt16remove_referenceIT_E4typeEOS8_,"axG",@progbits,_ZSt4moveIRSt5tupleIJP5ShapeSt14default_deleteIS1_EEEEONSt16remove_referenceIT_E4typeEOS8_,comdat
	.weak	_ZSt4moveIRSt5tupleIJP5ShapeSt14default_deleteIS1_EEEEONSt16remove_referenceIT_E4typeEOS8_
	.type	_ZSt4moveIRSt5tupleIJP5ShapeSt14default_deleteIS1_EEEEONSt16remove_referenceIT_E4typeEOS8_, @function
_ZSt4moveIRSt5tupleIJP5ShapeSt14default_deleteIS1_EEEEONSt16remove_referenceIT_E4typeEOS8_:
.LFB4590:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/bits/move.h:98:     { return static_cast<typename std::remove_reference<_Tp>::type&&>(__t); }
	movq	-8(%rbp), %rax	# __t, _2
# /usr/include/c++/13/bits/move.h:98:     { return static_cast<typename std::remove_reference<_Tp>::type&&>(__t); }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4590:
	.size	_ZSt4moveIRSt5tupleIJP5ShapeSt14default_deleteIS1_EEEEONSt16remove_referenceIT_E4typeEOS8_, .-_ZSt4moveIRSt5tupleIJP5ShapeSt14default_deleteIS1_EEEEONSt16remove_referenceIT_E4typeEOS8_
	.section	.text._ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2EOS3_,"axG",@progbits,_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC5EOS3_,comdat
	.align 2
	.weak	_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2EOS3_
	.type	_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2EOS3_, @function
_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2EOS3_:
.LFB4592:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# __in, __in
# /usr/include/c++/13/tuple:530:       { }
	nop	
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4592:
	.size	_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2EOS3_, .-_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2EOS3_
	.weak	_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC1EOS3_
	.set	_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC1EOS3_,_ZNSt11_Tuple_implILm1EJSt14default_deleteI5ShapeEEEC2EOS3_
	.section	.text._ZSt3minImERKT_S2_S2_,"axG",@progbits,_ZSt3minImERKT_S2_S2_,comdat
	.weak	_ZSt3minImERKT_S2_S2_
	.type	_ZSt3minImERKT_S2_S2_, @function
_ZSt3minImERKT_S2_S2_:
.LFB4594:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# __a, __a
	movq	%rsi, -16(%rbp)	# __b, __b
# /usr/include/c++/13/bits/stl_algobase.h:238:       if (__b < __a)
	movq	-16(%rbp), %rax	# __b, tmp86
	movq	(%rax), %rdx	# *__b_5(D), _1
	movq	-8(%rbp), %rax	# __a, tmp87
	movq	(%rax), %rax	# *__a_6(D), _2
# /usr/include/c++/13/bits/stl_algobase.h:238:       if (__b < __a)
	cmpq	%rax, %rdx	# _2, _1
	jnb	.L270	#,
# /usr/include/c++/13/bits/stl_algobase.h:239: 	return __b;
	movq	-16(%rbp), %rax	# __b, _3
	jmp	.L271	#
.L270:
# /usr/include/c++/13/bits/stl_algobase.h:240:       return __a;
	movq	-8(%rbp), %rax	# __a, _3
.L271:
# /usr/include/c++/13/bits/stl_algobase.h:241:     }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4594:
	.size	_ZSt3minImERKT_S2_S2_, .-_ZSt3minImERKT_S2_S2_
	.section	.text._ZSt12__niter_baseIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EEET_S6_,"axG",@progbits,_ZSt12__niter_baseIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EEET_S6_,comdat
	.weak	_ZSt12__niter_baseIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EEET_S6_
	.type	_ZSt12__niter_baseIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EEET_S6_, @function
_ZSt12__niter_baseIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EEET_S6_:
.LFB4596:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# __it, __it
# /usr/include/c++/13/bits/stl_algobase.h:318:     { return __it; }
	movq	-8(%rbp), %rax	# __it, _2
# /usr/include/c++/13/bits/stl_algobase.h:318:     { return __it; }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4596:
	.size	_ZSt12__niter_baseIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EEET_S6_, .-_ZSt12__niter_baseIPSt10unique_ptrI5ShapeSt14default_deleteIS1_EEET_S6_
	.section	.text._ZSt14__relocate_a_1IPSt10unique_ptrI5ShapeSt14default_deleteIS1_EES5_SaIS4_EET0_T_S8_S7_RT1_,"axG",@progbits,_ZSt14__relocate_a_1IPSt10unique_ptrI5ShapeSt14default_deleteIS1_EES5_SaIS4_EET0_T_S8_S7_RT1_,comdat
	.weak	_ZSt14__relocate_a_1IPSt10unique_ptrI5ShapeSt14default_deleteIS1_EES5_SaIS4_EET0_T_S8_S7_RT1_
	.type	_ZSt14__relocate_a_1IPSt10unique_ptrI5ShapeSt14default_deleteIS1_EES5_SaIS4_EET0_T_S8_S7_RT1_, @function
_ZSt14__relocate_a_1IPSt10unique_ptrI5ShapeSt14default_deleteIS1_EES5_SaIS4_EET0_T_S8_S7_RT1_:
.LFB4597:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$56, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)	# __first, __first
	movq	%rsi, -48(%rbp)	# __last, __last
	movq	%rdx, -56(%rbp)	# __result, __result
	movq	%rcx, -64(%rbp)	# __alloc, __alloc
# /usr/include/c++/13/bits/stl_uninitialized.h:1103:       _ForwardIterator __cur = __result;
	movq	-56(%rbp), %rax	# __result, tmp86
	movq	%rax, -24(%rbp)	# tmp86, __cur
# /usr/include/c++/13/bits/stl_uninitialized.h:1104:       for (; __first != __last; ++__first, (void)++__cur)
	jmp	.L275	#
.L276:
# /usr/include/c++/13/bits/stl_uninitialized.h:1105: 	std::__relocate_object_a(std::__addressof(*__cur),
	movq	-40(%rbp), %rax	# __first, tmp87
	movq	%rax, %rdi	# tmp87,
	call	_ZSt11__addressofISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEPT_RS5_	#
	movq	%rax, %rbx	#, _1
# /usr/include/c++/13/bits/stl_uninitialized.h:1105: 	std::__relocate_object_a(std::__addressof(*__cur),
	movq	-24(%rbp), %rax	# __cur, tmp88
	movq	%rax, %rdi	# tmp88,
	call	_ZSt11__addressofISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEPT_RS5_	#
	movq	%rax, %rcx	#, _2
# /usr/include/c++/13/bits/stl_uninitialized.h:1105: 	std::__relocate_object_a(std::__addressof(*__cur),
	movq	-64(%rbp), %rax	# __alloc, tmp89
	movq	%rax, %rdx	# tmp89,
	movq	%rbx, %rsi	# _1,
	movq	%rcx, %rdi	# _2,
	call	_ZSt19__relocate_object_aISt10unique_ptrI5ShapeSt14default_deleteIS1_EES4_SaIS4_EEvPT_PT0_RT1_	#
# /usr/include/c++/13/bits/stl_uninitialized.h:1104:       for (; __first != __last; ++__first, (void)++__cur)
	addq	$8, -40(%rbp)	#, __first
# /usr/include/c++/13/bits/stl_uninitialized.h:1104:       for (; __first != __last; ++__first, (void)++__cur)
	addq	$8, -24(%rbp)	#, __cur
.L275:
# /usr/include/c++/13/bits/stl_uninitialized.h:1104:       for (; __first != __last; ++__first, (void)++__cur)
	movq	-40(%rbp), %rax	# __first, tmp90
	cmpq	-48(%rbp), %rax	# __last, tmp90
	jne	.L276	#,
# /usr/include/c++/13/bits/stl_uninitialized.h:1107:       return __cur;
	movq	-24(%rbp), %rax	# __cur, _11
# /usr/include/c++/13/bits/stl_uninitialized.h:1108:     }
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4597:
	.size	_ZSt14__relocate_a_1IPSt10unique_ptrI5ShapeSt14default_deleteIS1_EES5_SaIS4_EET0_T_S8_S7_RT1_, .-_ZSt14__relocate_a_1IPSt10unique_ptrI5ShapeSt14default_deleteIS1_EES5_SaIS4_EET0_T_S8_S7_RT1_
	.section	.text._ZNSt11_Tuple_implILm1EJSt14default_deleteI9RectangleEEEC2Ev,"axG",@progbits,_ZNSt11_Tuple_implILm1EJSt14default_deleteI9RectangleEEEC5Ev,comdat
	.align 2
	.weak	_ZNSt11_Tuple_implILm1EJSt14default_deleteI9RectangleEEEC2Ev
	.type	_ZNSt11_Tuple_implILm1EJSt14default_deleteI9RectangleEEEC2Ev, @function
_ZNSt11_Tuple_implILm1EJSt14default_deleteI9RectangleEEEC2Ev:
.LFB4599:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/tuple:504:       : _Base() { }
	movq	-8(%rbp), %rax	# this, tmp82
	movq	%rax, %rdi	# tmp82,
	call	_ZNSt10_Head_baseILm1ESt14default_deleteI9RectangleELb1EEC2Ev	#
# /usr/include/c++/13/tuple:504:       : _Base() { }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4599:
	.size	_ZNSt11_Tuple_implILm1EJSt14default_deleteI9RectangleEEEC2Ev, .-_ZNSt11_Tuple_implILm1EJSt14default_deleteI9RectangleEEEC2Ev
	.weak	_ZNSt11_Tuple_implILm1EJSt14default_deleteI9RectangleEEEC1Ev
	.set	_ZNSt11_Tuple_implILm1EJSt14default_deleteI9RectangleEEEC1Ev,_ZNSt11_Tuple_implILm1EJSt14default_deleteI9RectangleEEEC2Ev
	.section	.text._ZNSt10_Head_baseILm0EP9RectangleLb0EEC2Ev,"axG",@progbits,_ZNSt10_Head_baseILm0EP9RectangleLb0EEC5Ev,comdat
	.align 2
	.weak	_ZNSt10_Head_baseILm0EP9RectangleLb0EEC2Ev
	.type	_ZNSt10_Head_baseILm0EP9RectangleLb0EEC2Ev, @function
_ZNSt10_Head_baseILm0EP9RectangleLb0EEC2Ev:
.LFB4602:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/tuple:191:       : _M_head_impl() { }
	movq	-8(%rbp), %rax	# this, tmp82
	movq	$0, (%rax)	#, this_2(D)->_M_head_impl
# /usr/include/c++/13/tuple:191:       : _M_head_impl() { }
	nop	
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4602:
	.size	_ZNSt10_Head_baseILm0EP9RectangleLb0EEC2Ev, .-_ZNSt10_Head_baseILm0EP9RectangleLb0EEC2Ev
	.weak	_ZNSt10_Head_baseILm0EP9RectangleLb0EEC1Ev
	.set	_ZNSt10_Head_baseILm0EP9RectangleLb0EEC1Ev,_ZNSt10_Head_baseILm0EP9RectangleLb0EEC2Ev
	.section	.text._ZNSt10_Head_baseILm0EP9RectangleLb0EE7_M_headERS2_,"axG",@progbits,_ZNSt10_Head_baseILm0EP9RectangleLb0EE7_M_headERS2_,comdat
	.weak	_ZNSt10_Head_baseILm0EP9RectangleLb0EE7_M_headERS2_
	.type	_ZNSt10_Head_baseILm0EP9RectangleLb0EE7_M_headERS2_, @function
_ZNSt10_Head_baseILm0EP9RectangleLb0EE7_M_headERS2_:
.LFB4604:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# __b, __b
# /usr/include/c++/13/tuple:234:       _M_head(_Head_base& __b) noexcept { return __b._M_head_impl; }
	movq	-8(%rbp), %rax	# __b, _2
# /usr/include/c++/13/tuple:234:       _M_head(_Head_base& __b) noexcept { return __b._M_head_impl; }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4604:
	.size	_ZNSt10_Head_baseILm0EP9RectangleLb0EE7_M_headERS2_, .-_ZNSt10_Head_baseILm0EP9RectangleLb0EE7_M_headERS2_
	.section	.text._ZNSt11_Tuple_implILm1EJSt14default_deleteI9RectangleEEE7_M_headERS3_,"axG",@progbits,_ZNSt11_Tuple_implILm1EJSt14default_deleteI9RectangleEEE7_M_headERS3_,comdat
	.weak	_ZNSt11_Tuple_implILm1EJSt14default_deleteI9RectangleEEE7_M_headERS3_
	.type	_ZNSt11_Tuple_implILm1EJSt14default_deleteI9RectangleEEE7_M_headERS3_, @function
_ZNSt11_Tuple_implILm1EJSt14default_deleteI9RectangleEEE7_M_headERS3_:
.LFB4605:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/tuple:497:       _M_head(_Tuple_impl& __t) noexcept { return _Base::_M_head(__t); }
	movq	-8(%rbp), %rax	# __t, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZNSt10_Head_baseILm1ESt14default_deleteI9RectangleELb1EE7_M_headERS3_	#
# /usr/include/c++/13/tuple:497:       _M_head(_Tuple_impl& __t) noexcept { return _Base::_M_head(__t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4605:
	.size	_ZNSt11_Tuple_implILm1EJSt14default_deleteI9RectangleEEE7_M_headERS3_, .-_ZNSt11_Tuple_implILm1EJSt14default_deleteI9RectangleEEE7_M_headERS3_
	.section	.text._ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EEC2IS0_I9RectangleEEEOT_,"axG",@progbits,_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EEC5IS0_I9RectangleEEEOT_,comdat
	.align 2
	.weak	_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EEC2IS0_I9RectangleEEEOT_
	.type	_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EEC2IS0_I9RectangleEEEOT_, @function
_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EEC2IS0_I9RectangleEEEOT_:
.LFB4607:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$24, %rsp	#,
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)	# this, this
	movq	%rsi, -32(%rbp)	# __h, __h
# /usr/include/c++/13/tuple:92: 	: _M_head_impl(std::forward<_UHead>(__h)) { }
	movq	-24(%rbp), %rbx	# this, _1
# /usr/include/c++/13/tuple:92: 	: _M_head_impl(std::forward<_UHead>(__h)) { }
	movq	-32(%rbp), %rax	# __h, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZSt7forwardISt14default_deleteI9RectangleEEOT_RNSt16remove_referenceIS3_E4typeE	#
# /usr/include/c++/13/tuple:92: 	: _M_head_impl(std::forward<_UHead>(__h)) { }
	movq	%rax, %rsi	# _2,
	movq	%rbx, %rdi	# _1,
	call	_ZNSt14default_deleteI5ShapeEC1I9RectanglevEERKS_IT_E	#
# /usr/include/c++/13/tuple:92: 	: _M_head_impl(std::forward<_UHead>(__h)) { }
	nop	
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4607:
	.size	_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EEC2IS0_I9RectangleEEEOT_, .-_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EEC2IS0_I9RectangleEEEOT_
	.weak	_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EEC1IS0_I9RectangleEEEOT_
	.set	_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EEC1IS0_I9RectangleEEEOT_,_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EEC2IS0_I9RectangleEEEOT_
	.section	.text._ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEE7_M_headERKS4_,"axG",@progbits,_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEE7_M_headERKS4_,comdat
	.weak	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEE7_M_headERKS4_
	.type	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEE7_M_headERKS4_, @function
_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEE7_M_headERKS4_:
.LFB4609:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# __t, __t
# /usr/include/c++/13/tuple:272:       _M_head(const _Tuple_impl& __t) noexcept { return _Base::_M_head(__t); }
	movq	-8(%rbp), %rax	# __t, _1
	movq	%rax, %rdi	# _1,
	call	_ZNSt10_Head_baseILm0EP5ShapeLb0EE7_M_headERKS2_	#
# /usr/include/c++/13/tuple:272:       _M_head(const _Tuple_impl& __t) noexcept { return _Base::_M_head(__t); }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4609:
	.size	_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEE7_M_headERKS4_, .-_ZNSt11_Tuple_implILm0EJP5ShapeSt14default_deleteIS0_EEE7_M_headERKS4_
	.section	.text._ZNSt10_Head_baseILm1ESt14default_deleteI6CircleELb1EEC2Ev,"axG",@progbits,_ZNSt10_Head_baseILm1ESt14default_deleteI6CircleELb1EEC5Ev,comdat
	.align 2
	.weak	_ZNSt10_Head_baseILm1ESt14default_deleteI6CircleELb1EEC2Ev
	.type	_ZNSt10_Head_baseILm1ESt14default_deleteI6CircleELb1EEC2Ev, @function
_ZNSt10_Head_baseILm1ESt14default_deleteI6CircleELb1EEC2Ev:
.LFB4620:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/tuple:82:       : _M_head_impl() { }
	nop	
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4620:
	.size	_ZNSt10_Head_baseILm1ESt14default_deleteI6CircleELb1EEC2Ev, .-_ZNSt10_Head_baseILm1ESt14default_deleteI6CircleELb1EEC2Ev
	.weak	_ZNSt10_Head_baseILm1ESt14default_deleteI6CircleELb1EEC1Ev
	.set	_ZNSt10_Head_baseILm1ESt14default_deleteI6CircleELb1EEC1Ev,_ZNSt10_Head_baseILm1ESt14default_deleteI6CircleELb1EEC2Ev
	.section	.text._ZNSt10_Head_baseILm1ESt14default_deleteI6CircleELb1EE7_M_headERS3_,"axG",@progbits,_ZNSt10_Head_baseILm1ESt14default_deleteI6CircleELb1EE7_M_headERS3_,comdat
	.weak	_ZNSt10_Head_baseILm1ESt14default_deleteI6CircleELb1EE7_M_headERS3_
	.type	_ZNSt10_Head_baseILm1ESt14default_deleteI6CircleELb1EE7_M_headERS3_, @function
_ZNSt10_Head_baseILm1ESt14default_deleteI6CircleELb1EE7_M_headERS3_:
.LFB4622:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# __b, __b
# /usr/include/c++/13/tuple:125:       _M_head(_Head_base& __b) noexcept { return __b._M_head_impl; }
	movq	-8(%rbp), %rax	# __b, _2
# /usr/include/c++/13/tuple:125:       _M_head(_Head_base& __b) noexcept { return __b._M_head_impl; }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4622:
	.size	_ZNSt10_Head_baseILm1ESt14default_deleteI6CircleELb1EE7_M_headERS3_, .-_ZNSt10_Head_baseILm1ESt14default_deleteI6CircleELb1EE7_M_headERS3_
	.section	.text._ZNSt14default_deleteI5ShapeEC2I6CirclevEERKS_IT_E,"axG",@progbits,_ZNSt14default_deleteI5ShapeEC5I6CirclevEERKS_IT_E,comdat
	.align 2
	.weak	_ZNSt14default_deleteI5ShapeEC2I6CirclevEERKS_IT_E
	.type	_ZNSt14default_deleteI5ShapeEC2I6CirclevEERKS_IT_E, @function
_ZNSt14default_deleteI5ShapeEC2I6CirclevEERKS_IT_E:
.LFB4624:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# D.86451, D.86451
# /usr/include/c++/13/bits/unique_ptr.h:88:         default_delete(const default_delete<_Up>&) noexcept { }
	nop	
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4624:
	.size	_ZNSt14default_deleteI5ShapeEC2I6CirclevEERKS_IT_E, .-_ZNSt14default_deleteI5ShapeEC2I6CirclevEERKS_IT_E
	.weak	_ZNSt14default_deleteI5ShapeEC1I6CirclevEERKS_IT_E
	.set	_ZNSt14default_deleteI5ShapeEC1I6CirclevEERKS_IT_E,_ZNSt14default_deleteI5ShapeEC2I6CirclevEERKS_IT_E
	.section	.text._ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EE7_M_headERS3_,"axG",@progbits,_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EE7_M_headERS3_,comdat
	.weak	_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EE7_M_headERS3_
	.type	_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EE7_M_headERS3_, @function
_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EE7_M_headERS3_:
.LFB4626:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# __b, __b
# /usr/include/c++/13/tuple:125:       _M_head(_Head_base& __b) noexcept { return __b._M_head_impl; }
	movq	-8(%rbp), %rax	# __b, _2
# /usr/include/c++/13/tuple:125:       _M_head(_Head_base& __b) noexcept { return __b._M_head_impl; }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4626:
	.size	_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EE7_M_headERS3_, .-_ZNSt10_Head_baseILm1ESt14default_deleteI5ShapeELb1EE7_M_headERS3_
	.section	.text._ZNSt15__new_allocatorISt10unique_ptrI5ShapeSt14default_deleteIS1_EEE8allocateEmPKv,"axG",@progbits,_ZNSt15__new_allocatorISt10unique_ptrI5ShapeSt14default_deleteIS1_EEE8allocateEmPKv,comdat
	.align 2
	.weak	_ZNSt15__new_allocatorISt10unique_ptrI5ShapeSt14default_deleteIS1_EEE8allocateEmPKv
	.type	_ZNSt15__new_allocatorISt10unique_ptrI5ShapeSt14default_deleteIS1_EEE8allocateEmPKv, @function
_ZNSt15__new_allocatorISt10unique_ptrI5ShapeSt14default_deleteIS1_EEE8allocateEmPKv:
.LFB4627:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$48, %rsp	#,
	movq	%rdi, -24(%rbp)	# this, this
	movq	%rsi, -32(%rbp)	# __n, __n
	movq	%rdx, -40(%rbp)	# D.98887, D.98887
	movq	-24(%rbp), %rax	# this, tmp90
	movq	%rax, -8(%rbp)	# tmp90, this
# /usr/include/c++/13/bits/new_allocator.h:233: 	return std::size_t(__PTRDIFF_MAX__) / sizeof(_Tp);
	movabsq	$1152921504606846975, %rax	#, D.99499
# /usr/include/c++/13/bits/new_allocator.h:134: 	if (__builtin_expect(__n > this->_M_max_size(), false))
	cmpq	-32(%rbp), %rax	# __n, D.99499
	setb	%al	#, _2
# /usr/include/c++/13/bits/new_allocator.h:134: 	if (__builtin_expect(__n > this->_M_max_size(), false))
	movzbl	%al, %eax	# _2, _3
# /usr/include/c++/13/bits/new_allocator.h:134: 	if (__builtin_expect(__n > this->_M_max_size(), false))
	testq	%rax, %rax	# _4
	setne	%al	#, retval.12_9
# /usr/include/c++/13/bits/new_allocator.h:134: 	if (__builtin_expect(__n > this->_M_max_size(), false))
	testb	%al, %al	# retval.12_9
	je	.L295	#,
# /usr/include/c++/13/bits/new_allocator.h:138: 	    if (__n > (std::size_t(-1) / sizeof(_Tp)))
	movabsq	$2305843009213693951, %rax	#, tmp91
	cmpq	-32(%rbp), %rax	# __n, tmp91
	jnb	.L296	#,
# /usr/include/c++/13/bits/new_allocator.h:139: 	      std::__throw_bad_array_new_length();
	call	_ZSt28__throw_bad_array_new_lengthv@PLT	#
.L296:
# /usr/include/c++/13/bits/new_allocator.h:140: 	    std::__throw_bad_alloc();
	call	_ZSt17__throw_bad_allocv@PLT	#
.L295:
# /usr/include/c++/13/bits/new_allocator.h:151: 	return static_cast<_Tp*>(_GLIBCXX_OPERATOR_NEW(__n * sizeof(_Tp)));
	movq	-32(%rbp), %rax	# __n, tmp92
	salq	$3, %rax	#, _6
	movq	%rax, %rdi	# _6,
	call	_Znwm@PLT	#
# /usr/include/c++/13/bits/new_allocator.h:151: 	return static_cast<_Tp*>(_GLIBCXX_OPERATOR_NEW(__n * sizeof(_Tp)));
	nop	
# /usr/include/c++/13/bits/new_allocator.h:152:       }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4627:
	.size	_ZNSt15__new_allocatorISt10unique_ptrI5ShapeSt14default_deleteIS1_EEE8allocateEmPKv, .-_ZNSt15__new_allocatorISt10unique_ptrI5ShapeSt14default_deleteIS1_EEE8allocateEmPKv
	.section	.text._ZSt19__relocate_object_aISt10unique_ptrI5ShapeSt14default_deleteIS1_EES4_SaIS4_EEvPT_PT0_RT1_,"axG",@progbits,_ZSt19__relocate_object_aISt10unique_ptrI5ShapeSt14default_deleteIS1_EES4_SaIS4_EEvPT_PT0_RT1_,comdat
	.weak	_ZSt19__relocate_object_aISt10unique_ptrI5ShapeSt14default_deleteIS1_EES4_SaIS4_EEvPT_PT0_RT1_
	.type	_ZSt19__relocate_object_aISt10unique_ptrI5ShapeSt14default_deleteIS1_EES4_SaIS4_EEvPT_PT0_RT1_, @function
_ZSt19__relocate_object_aISt10unique_ptrI5ShapeSt14default_deleteIS1_EES4_SaIS4_EEvPT_PT0_RT1_:
.LFB4628:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$80, %rsp	#,
	movq	%rdi, -56(%rbp)	# __dest, __dest
	movq	%rsi, -64(%rbp)	# __orig, __orig
	movq	%rdx, -72(%rbp)	# __alloc, __alloc
# /usr/include/c++/13/bits/stl_uninitialized.h:1077:       __traits::construct(__alloc, __dest, std::move(*__orig));
	movq	-64(%rbp), %rax	# __orig, tmp85
	movq	%rax, %rdi	# tmp85,
	call	_ZSt4moveIRSt10unique_ptrI5ShapeSt14default_deleteIS1_EEEONSt16remove_referenceIT_E4typeEOS7_	#
	movq	-72(%rbp), %rdx	# __alloc, tmp86
	movq	%rdx, -24(%rbp)	# tmp86, __a
	movq	-56(%rbp), %rdx	# __dest, tmp87
	movq	%rdx, -16(%rbp)	# tmp87, __p
	movq	%rax, -8(%rbp)	# _1, __args#0
# /usr/include/c++/13/bits/alloc_traits.h:540: 	  std::construct_at(__p, std::forward<_Args>(__args)...);
	movq	-8(%rbp), %rax	# __args#0, tmp88
	movq	%rax, %rdi	# tmp88,
	call	_ZSt7forwardISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEOT_RNSt16remove_referenceIS5_E4typeE	#
	movq	%rax, %rdx	#, _14
# /usr/include/c++/13/bits/alloc_traits.h:540: 	  std::construct_at(__p, std::forward<_Args>(__args)...);
	movq	-16(%rbp), %rax	# __p, tmp89
	movq	%rdx, %rsi	# _14,
	movq	%rax, %rdi	# tmp89,
	call	_ZSt12construct_atISt10unique_ptrI5ShapeSt14default_deleteIS1_EEJS4_EEDTgsnwcvPvLi0E_T_pispcl7declvalIT0_EEEEPS6_DpOS7_	#
# /usr/include/c++/13/bits/alloc_traits.h:542: 	}
	nop	
# /usr/include/c++/13/bits/stl_uninitialized.h:1078:       __traits::destroy(__alloc, std::__addressof(*__orig));
	movq	-64(%rbp), %rax	# __orig, tmp90
	movq	%rax, %rdi	# tmp90,
	call	_ZSt11__addressofISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEPT_RS5_	#
	movq	-72(%rbp), %rdx	# __alloc, tmp91
	movq	%rdx, -40(%rbp)	# tmp91, __a
	movq	%rax, -32(%rbp)	# _2, __p
# /usr/include/c++/13/bits/alloc_traits.h:560: 	  std::destroy_at(__p);
	movq	-32(%rbp), %rax	# __p, tmp92
	movq	%rax, %rdi	# tmp92,
	call	_ZSt10destroy_atISt10unique_ptrI5ShapeSt14default_deleteIS1_EEEvPT_	#
# /usr/include/c++/13/bits/alloc_traits.h:562: 	}
	nop	
# /usr/include/c++/13/bits/stl_uninitialized.h:1079:     }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4628:
	.size	_ZSt19__relocate_object_aISt10unique_ptrI5ShapeSt14default_deleteIS1_EES4_SaIS4_EEvPT_PT0_RT1_, .-_ZSt19__relocate_object_aISt10unique_ptrI5ShapeSt14default_deleteIS1_EES4_SaIS4_EEvPT_PT0_RT1_
	.section	.text._ZNSt10_Head_baseILm1ESt14default_deleteI9RectangleELb1EEC2Ev,"axG",@progbits,_ZNSt10_Head_baseILm1ESt14default_deleteI9RectangleELb1EEC5Ev,comdat
	.align 2
	.weak	_ZNSt10_Head_baseILm1ESt14default_deleteI9RectangleELb1EEC2Ev
	.type	_ZNSt10_Head_baseILm1ESt14default_deleteI9RectangleELb1EEC2Ev, @function
_ZNSt10_Head_baseILm1ESt14default_deleteI9RectangleELb1EEC2Ev:
.LFB4630:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# /usr/include/c++/13/tuple:82:       : _M_head_impl() { }
	nop	
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4630:
	.size	_ZNSt10_Head_baseILm1ESt14default_deleteI9RectangleELb1EEC2Ev, .-_ZNSt10_Head_baseILm1ESt14default_deleteI9RectangleELb1EEC2Ev
	.weak	_ZNSt10_Head_baseILm1ESt14default_deleteI9RectangleELb1EEC1Ev
	.set	_ZNSt10_Head_baseILm1ESt14default_deleteI9RectangleELb1EEC1Ev,_ZNSt10_Head_baseILm1ESt14default_deleteI9RectangleELb1EEC2Ev
	.section	.text._ZNSt10_Head_baseILm1ESt14default_deleteI9RectangleELb1EE7_M_headERS3_,"axG",@progbits,_ZNSt10_Head_baseILm1ESt14default_deleteI9RectangleELb1EE7_M_headERS3_,comdat
	.weak	_ZNSt10_Head_baseILm1ESt14default_deleteI9RectangleELb1EE7_M_headERS3_
	.type	_ZNSt10_Head_baseILm1ESt14default_deleteI9RectangleELb1EE7_M_headERS3_, @function
_ZNSt10_Head_baseILm1ESt14default_deleteI9RectangleELb1EE7_M_headERS3_:
.LFB4632:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# __b, __b
# /usr/include/c++/13/tuple:125:       _M_head(_Head_base& __b) noexcept { return __b._M_head_impl; }
	movq	-8(%rbp), %rax	# __b, _2
# /usr/include/c++/13/tuple:125:       _M_head(_Head_base& __b) noexcept { return __b._M_head_impl; }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4632:
	.size	_ZNSt10_Head_baseILm1ESt14default_deleteI9RectangleELb1EE7_M_headERS3_, .-_ZNSt10_Head_baseILm1ESt14default_deleteI9RectangleELb1EE7_M_headERS3_
	.section	.text._ZNSt14default_deleteI5ShapeEC2I9RectanglevEERKS_IT_E,"axG",@progbits,_ZNSt14default_deleteI5ShapeEC5I9RectanglevEERKS_IT_E,comdat
	.align 2
	.weak	_ZNSt14default_deleteI5ShapeEC2I9RectanglevEERKS_IT_E
	.type	_ZNSt14default_deleteI5ShapeEC2I9RectanglevEERKS_IT_E, @function
_ZNSt14default_deleteI5ShapeEC2I9RectanglevEERKS_IT_E:
.LFB4634:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
	movq	%rsi, -16(%rbp)	# D.89526, D.89526
# /usr/include/c++/13/bits/unique_ptr.h:88:         default_delete(const default_delete<_Up>&) noexcept { }
	nop	
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4634:
	.size	_ZNSt14default_deleteI5ShapeEC2I9RectanglevEERKS_IT_E, .-_ZNSt14default_deleteI5ShapeEC2I9RectanglevEERKS_IT_E
	.weak	_ZNSt14default_deleteI5ShapeEC1I9RectanglevEERKS_IT_E
	.set	_ZNSt14default_deleteI5ShapeEC1I9RectanglevEERKS_IT_E,_ZNSt14default_deleteI5ShapeEC2I9RectanglevEERKS_IT_E
	.section	.text._ZNSt10_Head_baseILm0EP5ShapeLb0EE7_M_headERKS2_,"axG",@progbits,_ZNSt10_Head_baseILm0EP5ShapeLb0EE7_M_headERKS2_,comdat
	.weak	_ZNSt10_Head_baseILm0EP5ShapeLb0EE7_M_headERKS2_
	.type	_ZNSt10_Head_baseILm0EP5ShapeLb0EE7_M_headERKS2_, @function
_ZNSt10_Head_baseILm0EP5ShapeLb0EE7_M_headERKS2_:
.LFB4636:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# __b, __b
# /usr/include/c++/13/tuple:237:       _M_head(const _Head_base& __b) noexcept { return __b._M_head_impl; }
	movq	-8(%rbp), %rax	# __b, _2
# /usr/include/c++/13/tuple:237:       _M_head(const _Head_base& __b) noexcept { return __b._M_head_impl; }
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE4636:
	.size	_ZNSt10_Head_baseILm0EP5ShapeLb0EE7_M_headERKS2_, .-_ZNSt10_Head_baseILm0EP5ShapeLb0EE7_M_headERKS2_
	.weak	_ZTV9Rectangle
	.section	.data.rel.ro.local._ZTV9Rectangle,"awG",@progbits,_ZTV9Rectangle,comdat
	.align 8
	.type	_ZTV9Rectangle, @object
	.size	_ZTV9Rectangle, 40
_ZTV9Rectangle:
	.quad	0
	.quad	_ZTI9Rectangle
	.quad	_ZN9RectangleD1Ev
	.quad	_ZN9RectangleD0Ev
	.quad	_ZNK9Rectangle6whoAmIEv
	.weak	_ZTV6Circle
	.section	.data.rel.ro.local._ZTV6Circle,"awG",@progbits,_ZTV6Circle,comdat
	.align 8
	.type	_ZTV6Circle, @object
	.size	_ZTV6Circle, 40
_ZTV6Circle:
	.quad	0
	.quad	_ZTI6Circle
	.quad	_ZN6CircleD1Ev
	.quad	_ZN6CircleD0Ev
	.quad	_ZNK6Circle6whoAmIEv
	.weak	_ZTV5Shape
	.section	.data.rel.ro._ZTV5Shape,"awG",@progbits,_ZTV5Shape,comdat
	.align 8
	.type	_ZTV5Shape, @object
	.size	_ZTV5Shape, 40
_ZTV5Shape:
	.quad	0
	.quad	_ZTI5Shape
	.quad	0
	.quad	0
	.quad	__cxa_pure_virtual
	.weak	_ZTI9Rectangle
	.section	.data.rel.ro._ZTI9Rectangle,"awG",@progbits,_ZTI9Rectangle,comdat
	.align 8
	.type	_ZTI9Rectangle, @object
	.size	_ZTI9Rectangle, 24
_ZTI9Rectangle:
# <anonymous>:
# <anonymous>:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
# <anonymous>:
	.quad	_ZTS9Rectangle
# <anonymous>:
	.quad	_ZTI5Shape
	.weak	_ZTS9Rectangle
	.section	.rodata._ZTS9Rectangle,"aG",@progbits,_ZTS9Rectangle,comdat
	.align 8
	.type	_ZTS9Rectangle, @object
	.size	_ZTS9Rectangle, 11
_ZTS9Rectangle:
	.string	"9Rectangle"
	.weak	_ZTI6Circle
	.section	.data.rel.ro._ZTI6Circle,"awG",@progbits,_ZTI6Circle,comdat
	.align 8
	.type	_ZTI6Circle, @object
	.size	_ZTI6Circle, 24
_ZTI6Circle:
# <anonymous>:
# <anonymous>:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
# <anonymous>:
	.quad	_ZTS6Circle
# <anonymous>:
	.quad	_ZTI5Shape
	.weak	_ZTS6Circle
	.section	.rodata._ZTS6Circle,"aG",@progbits,_ZTS6Circle,comdat
	.align 8
	.type	_ZTS6Circle, @object
	.size	_ZTS6Circle, 8
_ZTS6Circle:
	.string	"6Circle"
	.weak	_ZTI5Shape
	.section	.data.rel.ro._ZTI5Shape,"awG",@progbits,_ZTI5Shape,comdat
	.align 8
	.type	_ZTI5Shape, @object
	.size	_ZTI5Shape, 16
_ZTI5Shape:
# <anonymous>:
# <anonymous>:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
# <anonymous>:
	.quad	_ZTS5Shape
	.weak	_ZTS5Shape
	.section	.rodata._ZTS5Shape,"aG",@progbits,_ZTS5Shape,comdat
	.type	_ZTS5Shape, @object
	.size	_ZTS5Shape, 7
_ZTS5Shape:
	.string	"5Shape"
	.section	.rodata
	.type	_ZNSt8__detail14__destructibleISt13_Bit_iteratorEE, @object
	.size	_ZNSt8__detail14__destructibleISt13_Bit_iteratorEE, 1
_ZNSt8__detail14__destructibleISt13_Bit_iteratorEE:
	.byte	1
	.type	_ZNSt8__detail19__destructible_implISt13_Bit_iteratorEE, @object
	.size	_ZNSt8__detail19__destructible_implISt13_Bit_iteratorEE, 1
_ZNSt8__detail19__destructible_implISt13_Bit_iteratorEE:
	.byte	1
	.type	_ZNSt8__detail14__destructibleISt19_Bit_const_iteratorEE, @object
	.size	_ZNSt8__detail14__destructibleISt19_Bit_const_iteratorEE, 1
_ZNSt8__detail14__destructibleISt19_Bit_const_iteratorEE:
	.byte	1
	.type	_ZNSt8__detail19__destructible_implISt19_Bit_const_iteratorEE, @object
	.size	_ZNSt8__detail19__destructible_implISt19_Bit_const_iteratorEE, 1
_ZNSt8__detail19__destructible_implISt19_Bit_const_iteratorEE:
	.byte	1
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
	.weak	__cxa_pure_virtual
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
