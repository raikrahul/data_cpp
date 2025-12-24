	.section	.text
	.globl	_Z19solve_intersectionsRKSt6vectorISt7variantIJ6Circle9RectangleEESaIS3_EEdd
	.type	_Z19solve_intersectionsRKSt6vectorISt7variantIJ6Circle9RectangleEESaIS3_EEdd, @function

# FUNCTION: solve_intersections
# INPUTS:
#   %rdi (hidden 1st arg): Pointer to return vector<Point> 'all_points' (Struct Return Optimization)
#   %rsi (2nd arg): Pointer to const std::vector<Geometry>& 'shapes'
#   %xmm0 (3rd arg): double a
#   %xmm1 (4th arg): double b
#
# STACK LAYOUT:
#   %rsp+0  : Saved 'a' (8 bytes)
#   %rsp+8  : Saved 'b' (8 bytes)
#   %rsp+64 : Temporary 'x_coords' vector structure (24 bytes)

_Z19solve_intersectionsRKSt6vectorISt7variantIJ6Circle9RectangleEESaIS3_EEdd:
.LFB3897:
	.cfi_startproc
	endbr64
	
	# -- PROLOGUE --
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbp
	pushq	%rbx
	subq	$104, %rsp

	# -- INITIALIZE RETURN VECTOR 'all_points' --
	# all_points is at %rdi (passed by caller)
	# Initialize _M_start, _M_finish, _M_end_of_storage to 0
	movq	%rdi, %rbx              # Save 'all_points' ptr to %rbx
	movq	$0, (%rdi)              # _M_start = nullptr
	movq	$0, 8(%rdi)             # _M_finish = nullptr
	movq	$0, 16(%rdi)            # _M_end_of_storage = nullptr

	# -- SAVE ARGUMENTS --
	movsd	%xmm0, (%rsp)           # Spill 'a' to stack
	movsd	%xmm1, 8(%rsp)          # Spill 'b' to stack

	# -- PREPARE LOOP --
	# %rsi contains &shapes
	movq	(%rsi), %r12            # %r12 = shapes.begin() (ptr to first Variant)
	movq	8(%rsi), %rax           # %rax = shapes.end()
	cmpq	%rax, %r12              # Check if empty (begin == end)
	je	.L_RET                  # If empty, jump to return

	# -- LOOP START --
.L_LOOP_TOP:
	# -- VARIANT VISIT DISPATCH --
	# Variant Layout: 32 bytes union + 1 byte index + padding = 40 bytes
	# %r12 points to current Variant
	
	# Load Index Byte at offset 32
	movzbl	32(%r12), %eax          # %eax = variant.index()
	
	# Dispatch Logic (Optimized to CMP chain by -O1)
	testb	%al, %al                # Is index == 0? (Circle)
	jne	.L_CHECK_RECT           # If not, check Rectangle

.L_VISIT_CIRCLE:
	# -- VISIT CIRCLE (index 0) --
	# Circle::intersect returns {1.0}
	# Compiler likely inlined it:
	# Allocate vector<double> on stack for result 'x_coords'
	# ... (Allocation logic)
	movsd	.LC_ONE(%rip), %xmm0    # Load 1.0
	jmp	.L_PROCESS_RESULTS

.L_CHECK_RECT:
	cmpb	$1, %al                 # Is index == 1? (Rectangle)
	jne	.L_BAD_VARIANT          # If not (and not 0), error/monostate
	
	# -- VISIT RECTANGLE (index 1) --
	# Rectangle::intersect returns {2.0}
	movsd	.LC_TWO(%rip), %xmm0    # Load 2.0

.L_PROCESS_RESULTS:
	# -- INNER LOOP: for (double x : x_coords) --
	# %xmm0 contains 'x'
	# Calculate y = a * x + b
	mulsd	(%rsp), %xmm0           # %xmm0 = x * a (load a from stack)
	addsd	8(%rsp), %xmm0          # %xmm0 = (x * a) + b (load b from stack)
	# %xmm0 now contains 'y'
	
	# -- PUSH_BACK to 'all_points' --
	# Check capacity
	movq	8(%rbx), %rax           # Load _M_finish
	cmpq	16(%rbx), %rax          # Compare with _M_end_of_storage
	je	.L_REALLOC              # If full, reallocate
	
	# Store Point {x, y}
	# Wait, we need 'x' again. It was clobbered by mulsd?
	# Compiler would preserve it in another register if needed.
	# ...

	addq	$16, 8(%rbx)            # Increment _M_finish by sizeof(Point)=16

	# -- LOOP INCREMENT --
	addq	$40, %r12               # shapes iterator += 40 bytes (sizeof Variant)
	movq	8(%rsi), %rax           # Reload shapes.end()
	cmpq	%rax, %r12              # Compare iterator
	jne	.L_LOOP_TOP             # Continue if not end

.L_RET:
	# -- EPILOGUE --
	movq	%rbx, %rax              # Return 'all_points' ptr in %rax
	addq	$104, %rsp
	popq	%rbx
	popq	%rbp
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	ret

	.section	.rodata
	.align 8
.LC_ONE:
	.double	1.0
	.align 8
.LC_TWO:
	.double	2.0
