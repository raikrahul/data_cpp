.file	"44_assembly_virtual_dispatch.s"
.text
.section	.rodata
	
	# =============================================================================
	# BLOCK 0: STRING LITERALS (READY - DO NOT MODIFY)
	# =============================================================================
.LC0:
	.string		"Block 1: Register operations"
.LC1:
	.string		"Block 2: Memory read"
.LC2:
	.string		"Block 3: Stack operations"
.LC3:
	.string		"Block 4: Object on stack"
.LC4:
	.string		"Block 5: Virtual dispatch"
.LC5:
	.string		"VirtualFunc called"
.LC6:
	.string		"%s\n"
.LC7:
	.string		"Value in rax: %ld\n"
.LC8:
	.string		"Value at address: %ld\n"
	# =============================================================================
	# BLOCK 1: VIRTUAL FUNCTION IMPLEMENTATION (READY - DO NOT MODIFY)
	# =============================================================================
.text
.type	VirtualFunc, @function
VirtualFunc:
pushq	%rbp
	movq	%rsp, %rbp
subq	$16, %rsp
	movq	%rdi, -8(%rbp)          # this pointer stored at -8(%rbp)
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
nop
leave
ret
.size	VirtualFunc, .-VirtualFunc
	
	# =============================================================================
	# VTABLE SECTION (READY - DO NOT MODIFY)
	# =============================================================================
.section	.data.rel.ro.local,"aw"
.align 8
.type	MyVTable, @object
.size	MyVTable, 24
MyVTable:
.quad	0                       # offset to top
.quad	0                       # typeinfo pointer
.quad	VirtualFunc             # slot 0: pointer to VirtualFunc
	
	# =============================================================================
	# MAIN FUNCTION - YOU FILL THE TODO BLOCKS
	# =============================================================================
.text
.globl	main
.type	main, @function

main:
pushq	%rbp
	movq	%rsp, %rbp
subq	$32, %rsp               # allocate 32 bytes on stack
	
	# =============================================================================
	# TODO BLOCK 1: REGISTER OPERATIONS
	# =============================================================================
	# TASK: Move value 42 into %rax, then print it
	# ASSEMBLY CONCEPTS:
	#   - movq $immediate, %register  → move constant to register
	#   - %rax is 64-bit register
	# 
	# YOUR DERIVATION BEFORE CODING:
	#   mov instruction: source → destination
	#   $42 = immediate value 42
	#   %rax = destination register
	leaq	.LC0(%rip), %rdi
	call	puts@PLT

	movq	$42, %rax
	movq	%rax, %rsi              # 42 is safe here
	leaq	.LC7(%rip), %rdi
	movl	$0, %eax                # printf is variadic
	call	printf@PLT
	
	# =============================================================================
	# TODO BLOCK 2: MEMORY READ
	# =============================================================================
	# TASK: Store value 99 on stack, then read it back
	# ASSEMBLY CONCEPTS:
	#   - -8(%rbp) = memory location: %rbp - 8
	#   - movq %reg, -8(%rbp) → write register to memory
	#   - movq -8(%rbp), %reg → read memory to register
	#
	# YOUR DERIVATION:
	#   %rbp = base pointer (e.g., 0x7fff_0000)
	#   -8(%rbp) = %rbp - 8 = 0x7fff_0000 - 8 = 0x7ffe_fff8
	#   movq $99, %rax → %rax = 99
	#   movq %rax, -8(%rbp) → memory[0x7ffe_fff8] = 99
	#   movq -8(%rbp), %rsi → %rsi = memory[0x7ffe_fff8] = 99
	#
	# EXPECTED OUTPUT: "Value at address: 99"
	#
	# TODO: Write 3 instructions:
	#   1. Move 99 into %rax
	#   2. Write %rax to -8(%rbp)
	#   3. Read -8(%rbp) into %rsi
	
	leaq	.LC1(%rip), %rdi
	call	puts@PLT
	
	# TODO: Write your 3 movq instructions here
	movq	$99, %rax         # step 1: %rax = 99
	movq	%rax, -8(%rbp)  # step 2: memory[rbp-8] = %rax
	movq	-8(%rbp), %rsi  # step 3: %rsi = memory[rbp-8]
	
	# TODO: Uncomment after completing above
	leaq	.LC8(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	
	# =============================================================================
	# TODO BLOCK 3: ADDRESS COMPUTATION
	# =============================================================================
	# TASK: Compute address of -16(%rbp) without dereferencing
	# ASSEMBLY CONCEPTS:
	#   - leaq = load effective address (compute, no memory read)
	#   - movq = move (may dereference with ( ))
	#   - leaq X, %reg → %reg = &X (address of X)
	#   - movq X, %reg → %reg = X (value at X)
	#
	# YOUR DERIVATION:
	#   %rbp = 0x7fff_0000
	#   -16(%rbp) = 0x7fff_0000 - 16 = 0x7ffe_fff0
	#   leaq -16(%rbp), %rax → %rax = 0x7ffe_fff0 (address)
	#   movq -16(%rbp), %rax → %rax = memory[0x7ffe_fff0] (value)
	#
	# DIFFERENCE:
	#   leaq → address only (no [ ], arithmetic)
	#   movq → value (with [ ], memory read)
	#
	# TODO: Write 1 instruction to compute address of -16(%rbp) into %rax
	
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	
	# TODO: Write leaq instruction
	leaq    -16(%rbp), %rax
	movq    %rax, %rsi
	leaq    .LC7(%rip), %rdi
	movl    $0, %eax
	call    printf@PLT
	
	# =============================================================================
	# TODO BLOCK 4: OBJECT CONSTRUCTION
	# =============================================================================
	# TASK: Create object at -24(%rbp) with vptr = &MyVTable + 16
	# ASSEMBLY CONCEPTS:
	#   - object layout: [vptr][data...]
	#   - vptr at offset +0
	#   - vtable + 16 skips metadata (offset_to_top, typeinfo)
	#
	# YOUR DERIVATION:
	#   MyVTable:
	#     +0x00: 0 (offset_to_top)
	#     +0x08: 0 (typeinfo)
	#     +0x10: &VirtualFunc (slot 0) ← vptr points here
	#   
	#   leaq 16+MyVTable(%rip), %rax → %rax = &MyVTable + 16
	#   movq %rax, -24(%rbp) → object vptr = %rax
	#
	# OBJECT LAYOUT:
	#   -24(%rbp) + 0 = vptr
	#   sizeof(object) = 8 (vptr only)
	#
	# TODO: Write 2 instructions:
	#   1. Compute vptr value (&MyVTable + 16) into %rax
	#   2. Write %rax to object location (-24(%rbp))
	
	leaq	.LC3(%rip), %rdi
	call	puts@PLT
	
	# TODO: Write your 2 instructions
	# leaq	_____+MyVTable(%rip), %_____   # step 1: %rax = vptr value
	# movq	%_____, _____(%_____)          # step 2: object.vptr = %rax
	leaq 16+MyVTable(%rip), %rax
	movq %rax, -24(%rbp)
	
	# =============================================================================
	# TODO BLOCK 5: VIRTUAL DISPATCH
	# =============================================================================
	# TASK: Call virtual function through vptr
	# ASSEMBLY CONCEPTS:
	#   - ptr->virtual_func() → 3 memory reads + indirect call
	#   - step 1: load object address
	#   - step 2: load vptr from object
	#   - step 3: load function pointer from vtable
	#   - step 4: call function
	#
	# YOUR DERIVATION:
	#   object at -24(%rbp) = 0x7ffe_ffe8
	#   
	#   step 1: leaq -24(%rbp), %rax
	#           %rax = 0x7ffe_ffe8 (object address)
	#   step 5: call *%rdx
	#           jump to 0x4000_2000 (VirtualFunc)
	#
	# EXPECTED OUTPUT: "VirtualFunc called"
	#
	# TODO: Write 5 instructions for virtual dispatch
	
	leaq	.LC4(%rip), %rdi
	call	puts@PLT
	
	# TODO: Write your 5 instructions
	leaq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rdx
	leaq	-24(%rbp), %rdi
	call	*%rdx
	
	
	# =============================================================================
	# CLEANUP AND RETURN
	# =============================================================================
	movl	$0, %eax
leave
ret
.size	main, .-main
	
	# =============================================================================
	# COMPILE AND RUN:
	# as 44_assembly_virtual_dispatch.s -o 44_assembly_virtual_dispatch.o
	# gcc 44_assembly_virtual_dispatch.o -o 44_assembly_virtual_dispatch
	# ./44_assembly_virtual_dispatch
	#
	# DEBUG WITH GDB:
	# gdb ./44_assembly_virtual_dispatch
	# (gdb) break main
	# (gdb) run
	# (gdb) layout asm
	# (gdb) info registers
	# (gdb) x/8xb $rbp-24    # examine object memory
	# (gdb) stepi            # step one instruction
	# =============================================================================
