	.file	"nBody_best.c"
	.text
	.p2align 4,,15
.globl getState
	.type	getState, @function
getState:
.LFB21:
	.cfi_startproc
	movslq	%edx, %rdx
	xorpd	%xmm3, %xmm3
	leaq	0(,%rdx,8), %rcx
	salq	$6, %rdx
	movq	%rdi, %rax
	subq	%rcx, %rdx
	movapd	%xmm3, %xmm4
	leaq	(%rsi,%rdx), %rdx
	movapd	%xmm3, %xmm5
	cmpq	%rdx, %rsi
	jae	.L3
	xorpd	%xmm3, %xmm3
	movsd	.LC1(%rip), %xmm7
	movapd	%xmm3, %xmm4
	movapd	%xmm3, %xmm5
	.p2align 4,,10
	.p2align 3
.L4:
	movsd	(%rsi), %xmm0
	movsd	24(%rsi), %xmm1
	movapd	%xmm0, %xmm2
	movapd	%xmm0, %xmm6
	mulsd	%xmm7, %xmm0
	mulsd	%xmm1, %xmm2
	mulsd	%xmm1, %xmm1
	addsd	%xmm2, %xmm3
	movsd	32(%rsi), %xmm2
	addq	$56, %rsi
	mulsd	%xmm2, %xmm6
	cmpq	%rdx, %rsi
	mulsd	%xmm2, %xmm2
	addsd	%xmm6, %xmm4
	addsd	%xmm2, %xmm1
	mulsd	%xmm1, %xmm0
	addsd	%xmm0, %xmm5
	jb	.L4
.L3:
	movsd	%xmm5, 16(%rax)
	movsd	%xmm4, 8(%rax)
	movsd	%xmm3, (%rax)
	ret
	.cfi_endproc
.LFE21:
	.size	getState, .-getState
	.p2align 4,,15
.globl fastInvSqrt
	.type	fastInvSqrt, @function
fastInvSqrt:
.LFB24:
	.cfi_startproc
	movq	%xmm0, -8(%rsp)
	movq	-8(%rsp), %rdx
	movabsq	$6910469410427058089, %rax
	movsd	.LC1(%rip), %xmm1
	shrq	%rdx
	mulsd	%xmm0, %xmm1
	subq	%rdx, %rax
	movsd	.LC2(%rip), %xmm0
	movq	%rax, -16(%rsp)
	movsd	-16(%rsp), %xmm2
	mulsd	%xmm2, %xmm1
	mulsd	%xmm2, %xmm1
	subsd	%xmm1, %xmm0
	mulsd	%xmm2, %xmm0
	ret
	.cfi_endproc
.LFE24:
	.size	fastInvSqrt, .-fastInvSqrt
	.p2align 4,,15
.globl fastInvSqrtCube
	.type	fastInvSqrtCube, @function
fastInvSqrtCube:
.LFB25:
	.cfi_startproc
	movq	%xmm0, -8(%rsp)
	movq	-8(%rsp), %rdx
	movabsq	$6910469410427058089, %rax
	movsd	.LC1(%rip), %xmm1
	shrq	%rdx
	mulsd	%xmm0, %xmm1
	subq	%rdx, %rax
	movsd	.LC2(%rip), %xmm0
	movq	%rax, -16(%rsp)
	movsd	-16(%rsp), %xmm2
	mulsd	%xmm2, %xmm1
	mulsd	%xmm2, %xmm1
	subsd	%xmm1, %xmm0
	mulsd	%xmm2, %xmm0
	ret
	.cfi_endproc
.LFE25:
	.size	fastInvSqrtCube, .-fastInvSqrtCube
	.p2align 4,,15
.globl quickNormalize
	.type	quickNormalize, @function
quickNormalize:
.LFB26:
	.cfi_startproc
	movsd	(%rdi), %xmm2
	movabsq	$6910469410427058089, %rax
	movsd	(%rsi), %xmm1
	movapd	%xmm2, %xmm0
	mulsd	%xmm1, %xmm1
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	movq	%xmm0, -8(%rsp)
	movq	-8(%rsp), %rdx
	mulsd	.LC3(%rip), %xmm0
	shrq	%rdx
	subq	%rdx, %rax
	movq	%rax, -16(%rsp)
	movsd	-16(%rsp), %xmm1
	mulsd	%xmm1, %xmm0
	mulsd	%xmm1, %xmm0
	addsd	.LC2(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	movapd	%xmm0, %xmm1
	mulsd	%xmm0, %xmm1
	mulsd	%xmm0, %xmm1
	mulsd	%xmm1, %xmm2
	movsd	%xmm2, (%rdi)
	mulsd	(%rsi), %xmm1
	movsd	%xmm1, (%rsi)
	ret
	.cfi_endproc
.LFE26:
	.size	quickNormalize, .-quickNormalize
	.p2align 4,,15
.globl randTest
	.type	randTest, @function
randTest:
.LFB28:
	.cfi_startproc
	cmpl	%edx, %esi
	jge	.L17
	movslq	%esi, %rax
	movsd	.LC5(%rip), %xmm1
	leaq	0(,%rax,8), %rcx
	salq	$6, %rax
	subq	%rcx, %rax
	addq	%rax, %rdi
	.p2align 4,,10
	.p2align 3
.L16:
	cvtsi2sd	%esi, %xmm0
	movabsq	$4607182418800017408, %r8
	movabsq	$4607182418800017408, %rcx
	movabsq	$4607182418800017408, %rax
	addl	$1, %esi
	movq	%r8, (%rdi)
	movq	%rcx, 24(%rdi)
	movq	%rax, 32(%rdi)
	movq	$0, 40(%rdi)
	movq	$0, 48(%rdi)
	mulsd	%xmm1, %xmm0
	movsd	%xmm0, 8(%rdi)
	movsd	%xmm0, 16(%rdi)
	addq	$56, %rdi
	cmpl	%esi, %edx
	jg	.L16
.L17:
	rep
	ret
	.cfi_endproc
.LFE28:
	.size	randTest, .-randTest
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC6:
	.string	"p={%f, %f}\n"
.LC7:
	.string	"v={%f, %f}\n"
.LC8:
	.string	"a={%f, %f}\n"
.LC9:
	.string	", "
.LC10:
	.string	"}, "
	.text
	.p2align 4,,15
.globl bodiesPrint
	.type	bodiesPrint, @function
bodiesPrint:
.LFB30:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movl	%edx, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movl	%esi, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	movl	$123, %edi
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	call	putchar
	cmpl	%r12d, %ebp
	jge	.L20
	movslq	%ebp, %rax
	leal	-1(%r12), %r13d
	leaq	0(,%rax,8), %rdx
	salq	$6, %rax
	subq	%rdx, %rax
	leaq	16(%rbx,%rax), %rbx
	jmp	.L21
	.p2align 4,,10
	.p2align 3
.L24:
	xorl	%eax, %eax
	movl	$.LC9, %edi
	addl	$1, %ebp
	call	printf
	addq	$56, %rbx
	cmpl	%ebp, %r12d
	jle	.L20
.L21:
	movsd	-8(%rbx), %xmm0
	movl	$.LC6, %edi
	movsd	(%rbx), %xmm1
	movl	$2, %eax
	call	printf
	movsd	8(%rbx), %xmm0
	movl	$.LC7, %edi
	movsd	16(%rbx), %xmm1
	movl	$2, %eax
	call	printf
	movsd	24(%rbx), %xmm0
	movl	$.LC8, %edi
	movsd	32(%rbx), %xmm1
	movl	$2, %eax
	call	printf
	cmpl	%r13d, %ebp
	jne	.L24
.L20:
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
	movl	$.LC10, %edi
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	jmp	puts
	.cfi_endproc
.LFE30:
	.size	bodiesPrint, .-bodiesPrint
	.section	.rodata.str1.1
.LC11:
	.string	"{mvx=%f, mvy=%f, energy=%f}\n"
	.text
	.p2align 4,,15
.globl statePrint
	.type	statePrint, @function
statePrint:
.LFB22:
	.cfi_startproc
	movsd	16(%rdi), %xmm2
	movl	$3, %eax
	movsd	8(%rdi), %xmm1
	movsd	(%rdi), %xmm0
	movl	$.LC11, %edi
	jmp	printf
	.cfi_endproc
.LFE22:
	.size	statePrint, .-statePrint
	.p2align 4,,15
.globl randInit
	.type	randInit, @function
randInit:
.LFB29:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movl	%edx, %r12d
	movslq	%r12d, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movl	%esi, %ebp
	movslq	%ebp, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbx
	xorl	%edi, %edi
	call	time
	movl	%eax, %edi
	call	srand
	leaq	0(,%rbp,8), %rax
	salq	$6, %rbp
	subq	%rax, %rbp
	leaq	0(,%r12,8), %rax
	salq	$6, %r12
	leaq	(%rbx,%rbp), %rbp
	subq	%rax, %r12
	addq	%r12, %rbx
	cmpq	%rbx, %rbp
	jae	.L30
	.p2align 4,,10
	.p2align 3
.L29:
	call	rand
	cvtsi2ss	%eax, %xmm0
	mulss	.LC12(%rip), %xmm0
	unpcklps	%xmm0, %xmm0
	cvtps2pd	%xmm0, %xmm0
	movsd	%xmm0, 0(%rbp)
	call	rand
	cvtsi2ss	%eax, %xmm0
	mulss	.LC12(%rip), %xmm0
	unpcklps	%xmm0, %xmm0
	cvtps2pd	%xmm0, %xmm0
	movsd	%xmm0, 8(%rbp)
	call	rand
	cvtsi2ss	%eax, %xmm0
	mulss	.LC12(%rip), %xmm0
	unpcklps	%xmm0, %xmm0
	cvtps2pd	%xmm0, %xmm0
	movsd	%xmm0, 16(%rbp)
	call	rand
	cvtsi2ss	%eax, %xmm0
	unpcklps	%xmm0, %xmm0
	cvtps2pd	%xmm0, %xmm0
	mulsd	.LC2(%rip), %xmm0
	mulsd	.LC13(%rip), %xmm0
	movsd	%xmm0, 24(%rbp)
	call	rand
	cvtsi2ss	%eax, %xmm0
	unpcklps	%xmm0, %xmm0
	cvtps2pd	%xmm0, %xmm0
	mulsd	.LC2(%rip), %xmm0
	mulsd	.LC13(%rip), %xmm0
	movsd	%xmm0, 32(%rbp)
	addq	$56, %rbp
	cmpq	%rbx, %rbp
	jb	.L29
.L30:
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE29:
	.size	randInit, .-randInit
	.p2align 4,,15
.globl reNormalize
	.type	reNormalize, @function
reNormalize:
.LFB27:
	.cfi_startproc
	movq	%rbx, -16(%rsp)
	movq	%rbp, -8(%rsp)
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -16
	.cfi_offset 3, -24
	movsd	(%rdi), %xmm2
	movq	%rdi, %rbx
	movsd	(%rsi), %xmm0
	movq	%rsi, %rbp
	movapd	%xmm2, %xmm1
	mulsd	%xmm0, %xmm0
	mulsd	%xmm2, %xmm1
	addsd	%xmm0, %xmm1
	sqrtsd	%xmm1, %xmm0
	ucomisd	%xmm0, %xmm0
	jp	.L36
	je	.L33
.L36:
	movapd	%xmm1, %xmm0
	movsd	%xmm1, (%rsp)
	call	sqrt
	movsd	(%rbx), %xmm2
	movsd	(%rsp), %xmm1
.L33:
	mulsd	%xmm0, %xmm1
	divsd	%xmm1, %xmm2
	movsd	%xmm2, (%rbx)
	movsd	0(%rbp), %xmm2
	divsd	%xmm1, %xmm2
	movsd	%xmm2, 0(%rbp)
	movq	24(%rsp), %rbx
	movq	32(%rsp), %rbp
	addq	$40, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE27:
	.size	reNormalize, .-reNormalize
	.p2align 4,,15
.globl wctime
	.type	wctime, @function
wctime:
.LFB23:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	xorl	%esi, %esi
	movq	%rdi, %rbx
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	movq	%rsp, %rdi
	call	gettimeofday
	cvtsi2sdq	8(%rsp), %xmm1
	cvtsi2sdq	(%rsp), %xmm0
	mulsd	.LC14(%rip), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, (%rbx)
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE23:
	.size	wctime, .-wctime
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC15:
	.string	"Usage: Please input the number of bodies"
	.text
	.p2align 4,,15
.globl main
	.type	main, @function
main:
.LFB32:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
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
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$168, %rsp
	.cfi_def_cfa_offset 224
	cmpl	$1, %edi
	jle	.L64
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol
	movslq	%eax, %rbx
	imulq	$56, %rbx, %rbx
	movq	%rbx, %rdi
	call	malloc
	movq	%rax, %r13
	xorl	%edi, %edi
	leaq	0(%r13,%rbx), %rbx
	movq	%r13, %rbp
	call	time
	movl	%eax, %edi
	call	srand
	cmpq	%rbx, %r13
	jae	.L65
.L44:
	call	rand
	cvtsi2ss	%eax, %xmm0
	mulss	.LC12(%rip), %xmm0
	unpcklps	%xmm0, %xmm0
	cvtps2pd	%xmm0, %xmm0
	movsd	%xmm0, 0(%rbp)
	call	rand
	cvtsi2ss	%eax, %xmm0
	mulss	.LC12(%rip), %xmm0
	unpcklps	%xmm0, %xmm0
	cvtps2pd	%xmm0, %xmm0
	movsd	%xmm0, 8(%rbp)
	call	rand
	cvtsi2ss	%eax, %xmm0
	mulss	.LC12(%rip), %xmm0
	unpcklps	%xmm0, %xmm0
	cvtps2pd	%xmm0, %xmm0
	movsd	%xmm0, 16(%rbp)
	call	rand
	cvtsi2ss	%eax, %xmm0
	unpcklps	%xmm0, %xmm0
	cvtps2pd	%xmm0, %xmm0
	mulsd	.LC2(%rip), %xmm0
	mulsd	.LC13(%rip), %xmm0
	movsd	%xmm0, 24(%rbp)
	call	rand
	cvtsi2ss	%eax, %xmm0
	unpcklps	%xmm0, %xmm0
	cvtps2pd	%xmm0, %xmm0
	mulsd	.LC2(%rip), %xmm0
	mulsd	.LC13(%rip), %xmm0
	movsd	%xmm0, 32(%rbp)
	addq	$56, %rbp
	cmpq	%rbx, %rbp
	jb	.L44
	xorl	%r14d, %r14d
	movsd	.LC1(%rip), %xmm6
	movq	%r13, %rax
	movq	%r14, 80(%rsp)
	movq	%r14, 72(%rsp)
	movq	%r14, 64(%rsp)
.L45:
	movsd	(%rax), %xmm0
	movsd	24(%rax), %xmm1
	movapd	%xmm0, %xmm2
	movapd	%xmm0, %xmm3
	mulsd	%xmm6, %xmm0
	mulsd	%xmm1, %xmm2
	mulsd	%xmm1, %xmm1
	addsd	64(%rsp), %xmm2
	movsd	%xmm2, 64(%rsp)
	movsd	32(%rax), %xmm2
	addq	$56, %rax
	cmpq	%rbx, %rax
	mulsd	%xmm2, %xmm3
	mulsd	%xmm2, %xmm2
	addsd	72(%rsp), %xmm3
	addsd	%xmm2, %xmm1
	mulsd	%xmm1, %xmm0
	movsd	%xmm3, 72(%rsp)
	addsd	80(%rsp), %xmm0
	movsd	%xmm0, 80(%rsp)
	jb	.L45
.L43:
	leaq	144(%rsp), %r15
	xorl	%esi, %esi
	leaq	96(%rsp), %r12
	movabsq	$6910469410427058089, %rbp
	movq	%r15, %rdi
	call	gettimeofday
	cvtsi2sdq	152(%rsp), %xmm1
	cvtsi2sdq	144(%rsp), %xmm0
	mulsd	.LC14(%rip), %xmm1
	leaq	32(%r12), %rax
	addq	$8, %r12
	movsd	.LC16(%rip), %xmm11
	movsd	.LC2(%rip), %xmm2
	movq	%rax, 88(%rsp)
	movsd	.LC3(%rip), %xmm10
	addsd	%xmm1, %xmm0
	movsd	%xmm0, 96(%rsp)
.L46:
	cmpq	%rbx, %r13
	movq	%r13, %rcx
	je	.L52
	.p2align 4,,10
	.p2align 3
.L49:
	movsd	40(%rcx), %xmm6
	movsd	48(%rcx), %xmm5
	addq	$56, %rcx
	cmpq	%rbx, %rcx
	je	.L66
	movsd	-48(%rcx), %xmm9
	movq	%rcx, %rax
	movsd	-40(%rcx), %xmm8
	movsd	-56(%rcx), %xmm7
	.p2align 4,,10
	.p2align 3
.L48:
	movapd	%xmm9, %xmm4
	movq	%rbp, %rsi
	movapd	%xmm8, %xmm3
	subsd	8(%rax), %xmm4
	subsd	16(%rax), %xmm3
	movapd	%xmm4, %xmm0
	movapd	%xmm3, %xmm1
	mulsd	%xmm4, %xmm0
	mulsd	%xmm3, %xmm1
	addsd	%xmm1, %xmm0
	movq	%xmm0, 8(%rsp)
	movq	8(%rsp), %rdx
	mulsd	%xmm10, %xmm0
	shrq	%rdx
	subq	%rdx, %rsi
	movq	%rsi, (%rsp)
	movsd	(%rsp), %xmm1
	mulsd	%xmm1, %xmm0
	mulsd	%xmm1, %xmm0
	addsd	%xmm2, %xmm0
	mulsd	%xmm1, %xmm0
	movapd	%xmm0, %xmm1
	mulsd	%xmm0, %xmm1
	mulsd	%xmm0, %xmm1
	movsd	(%rax), %xmm0
	mulsd	%xmm1, %xmm4
	mulsd	%xmm3, %xmm1
	movapd	%xmm0, %xmm3
	mulsd	%xmm4, %xmm3
	mulsd	%xmm1, %xmm0
	mulsd	%xmm7, %xmm4
	mulsd	%xmm7, %xmm1
	subsd	%xmm3, %xmm6
	subsd	%xmm0, %xmm5
	addsd	40(%rax), %xmm4
	addsd	48(%rax), %xmm1
	movsd	%xmm4, 40(%rax)
	movsd	%xmm1, 48(%rax)
	addq	$56, %rax
	cmpq	%rbx, %rax
	jne	.L48
.L47:
	movsd	-32(%rcx), %xmm0
	cmpq	%rbx, %rcx
	mulsd	%xmm11, %xmm6
	movq	$0, -16(%rcx)
	movq	$0, -8(%rcx)
	mulsd	%xmm11, %xmm0
	mulsd	%xmm11, %xmm5
	addsd	-32(%rcx), %xmm6
	addsd	%xmm9, %xmm0
	addsd	-24(%rcx), %xmm5
	movsd	%xmm0, -48(%rcx)
	movsd	-24(%rcx), %xmm0
	movsd	%xmm6, -32(%rcx)
	mulsd	%xmm11, %xmm0
	movsd	%xmm5, -24(%rcx)
	addsd	%xmm8, %xmm0
	movsd	%xmm0, -40(%rcx)
	jne	.L49
.L52:
	xorl	%esi, %esi
	movq	%r15, %rdi
	movsd	%xmm2, 32(%rsp)
	movsd	%xmm10, 16(%rsp)
	movsd	%xmm11, 48(%rsp)
	call	gettimeofday
	cvtsi2sdq	152(%rsp), %xmm1
	cvtsi2sdq	144(%rsp), %xmm0
	mulsd	.LC14(%rip), %xmm1
	cmpq	88(%rsp), %r12
	movsd	32(%rsp), %xmm2
	movsd	16(%rsp), %xmm10
	movsd	48(%rsp), %xmm11
	addsd	%xmm1, %xmm0
	movsd	%xmm0, (%r12)
	je	.L50
	addq	$8, %r12
	jmp	.L46
.L66:
	movsd	-48(%rcx), %xmm9
	movsd	-40(%rcx), %xmm8
	jmp	.L47
.L50:
	cmpq	%rbx, %r13
	jae	.L67
	movq	%r14, (%rsp)
	movsd	.LC1(%rip), %xmm6
	movsd	(%rsp), %xmm3
	movq	%r13, %rax
	movapd	%xmm3, %xmm5
	movapd	%xmm3, %xmm4
.L55:
	movsd	(%rax), %xmm0
	movsd	24(%rax), %xmm1
	movapd	%xmm0, %xmm2
	movapd	%xmm0, %xmm7
	mulsd	%xmm6, %xmm0
	mulsd	%xmm1, %xmm2
	mulsd	%xmm1, %xmm1
	addsd	%xmm2, %xmm4
	movsd	32(%rax), %xmm2
	addq	$56, %rax
	mulsd	%xmm2, %xmm7
	cmpq	%rbx, %rax
	mulsd	%xmm2, %xmm2
	addsd	%xmm7, %xmm5
	addsd	%xmm2, %xmm1
	mulsd	%xmm1, %xmm0
	addsd	%xmm0, %xmm3
	jb	.L55
.L54:
	movsd	80(%rsp), %xmm2
	movl	$.LC11, %edi
	movsd	72(%rsp), %xmm1
	movl	$3, %eax
	movsd	64(%rsp), %xmm0
	movsd	%xmm3, 16(%rsp)
	movsd	%xmm4, 48(%rsp)
	movsd	%xmm5, 32(%rsp)
	call	printf
	movsd	16(%rsp), %xmm3
	movl	$.LC11, %edi
	movsd	32(%rsp), %xmm5
	movl	$3, %eax
	movsd	48(%rsp), %xmm4
	movapd	%xmm3, %xmm2
	movapd	%xmm5, %xmm1
	movapd	%xmm4, %xmm0
	call	printf
	movq	%r13, %rdi
	call	free
	xorl	%eax, %eax
.L41:
	addq	$168, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
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
.L64:
	.cfi_restore_state
	movl	$.LC15, %edi
	call	puts
	movl	$1, %eax
	jmp	.L41
.L67:
	movq	%r14, (%rsp)
	movsd	(%rsp), %xmm3
	movapd	%xmm3, %xmm5
	movapd	%xmm3, %xmm4
	jmp	.L54
.L65:
	xorl	%r14d, %r14d
	movq	%r14, 80(%rsp)
	movq	%r14, 72(%rsp)
	movq	%r14, 64(%rsp)
	jmp	.L43
	.cfi_endproc
.LFE32:
	.size	main, .-main
	.p2align 4,,15
.globl nextPhase
	.type	nextPhase, @function
nextPhase:
.LFB31:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	movq	%rcx, %r13
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movl	%edx, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movl	%esi, %ebp
	xorl	%esi, %esi
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rdi, %rbx
	subq	$104, %rsp
	.cfi_def_cfa_offset 160
	leaq	80(%rsp), %rdi
	call	gettimeofday
	cvtsi2sdq	88(%rsp), %xmm1
	cvtsi2sdq	80(%rsp), %xmm0
	mulsd	.LC14(%rip), %xmm1
	testl	%r12d, %r12d
	addsd	%xmm1, %xmm0
	movsd	%xmm0, 0(%r13)
	jle	.L76
	movslq	%ebp, %rbp
	movsd	.LC16(%rip), %xmm11
	imulq	$56, %rbp, %rbp
	movsd	.LC3(%rip), %xmm10
	movsd	.LC2(%rip), %xmm9
	leaq	8(%r13), %rdx
	xorl	%r15d, %r15d
	xorl	%r14d, %r14d
	movabsq	$6910469410427058089, %r13
	leaq	(%rbx,%rbp), %rbp
.L70:
	cmpq	%rbp, %rbx
	movq	%rbx, %rsi
	je	.L75
	.p2align 4,,10
	.p2align 3
.L73:
	movsd	40(%rsi), %xmm5
	movsd	48(%rsi), %xmm4
	addq	$56, %rsi
	cmpq	%rbp, %rsi
	je	.L81
	movsd	-48(%rsi), %xmm8
	movq	%rsi, %rax
	movsd	-40(%rsi), %xmm7
	movsd	-56(%rsi), %xmm6
	.p2align 4,,10
	.p2align 3
.L72:
	movapd	%xmm8, %xmm3
	movq	%r13, %rdi
	movapd	%xmm7, %xmm2
	subsd	8(%rax), %xmm3
	subsd	16(%rax), %xmm2
	movapd	%xmm3, %xmm0
	movapd	%xmm2, %xmm1
	mulsd	%xmm3, %xmm0
	mulsd	%xmm2, %xmm1
	addsd	%xmm1, %xmm0
	movq	%xmm0, 8(%rsp)
	movq	8(%rsp), %rcx
	mulsd	%xmm10, %xmm0
	shrq	%rcx
	subq	%rcx, %rdi
	movq	%rdi, (%rsp)
	movsd	(%rsp), %xmm1
	mulsd	%xmm1, %xmm0
	mulsd	%xmm1, %xmm0
	addsd	%xmm9, %xmm0
	mulsd	%xmm1, %xmm0
	movapd	%xmm0, %xmm1
	mulsd	%xmm0, %xmm1
	mulsd	%xmm0, %xmm1
	movapd	%xmm3, %xmm0
	mulsd	%xmm1, %xmm0
	mulsd	%xmm2, %xmm1
	movsd	(%rax), %xmm2
	movapd	%xmm2, %xmm3
	mulsd	%xmm1, %xmm2
	mulsd	%xmm0, %xmm3
	mulsd	%xmm6, %xmm1
	mulsd	%xmm6, %xmm0
	subsd	%xmm2, %xmm4
	subsd	%xmm3, %xmm5
	addsd	48(%rax), %xmm1
	addsd	40(%rax), %xmm0
	movsd	%xmm1, 48(%rax)
	movsd	%xmm0, 40(%rax)
	addq	$56, %rax
	cmpq	%rbp, %rax
	jne	.L72
.L71:
	movsd	-32(%rsi), %xmm0
	cmpq	%rbp, %rsi
	mulsd	%xmm11, %xmm5
	movq	%r14, -16(%rsi)
	movq	%r14, -8(%rsi)
	mulsd	%xmm11, %xmm0
	mulsd	%xmm11, %xmm4
	addsd	-32(%rsi), %xmm5
	addsd	%xmm8, %xmm0
	addsd	-24(%rsi), %xmm4
	movsd	%xmm0, -48(%rsi)
	movsd	-24(%rsi), %xmm0
	movsd	%xmm5, -32(%rsi)
	mulsd	%xmm11, %xmm0
	movsd	%xmm4, -24(%rsi)
	addsd	%xmm7, %xmm0
	movsd	%xmm0, -40(%rsi)
	jne	.L73
.L75:
	leaq	80(%rsp), %rdi
	xorl	%esi, %esi
	movq	%rdx, 72(%rsp)
	movsd	%xmm9, 16(%rsp)
	addl	$1, %r15d
	movsd	%xmm10, 32(%rsp)
	movsd	%xmm11, 48(%rsp)
	call	gettimeofday
	cvtsi2sdq	88(%rsp), %xmm1
	cvtsi2sdq	80(%rsp), %xmm0
	mulsd	.LC14(%rip), %xmm1
	cmpl	%r15d, %r12d
	movq	72(%rsp), %rdx
	movsd	16(%rsp), %xmm9
	movsd	32(%rsp), %xmm10
	movsd	48(%rsp), %xmm11
	addsd	%xmm1, %xmm0
	movsd	%xmm0, (%rdx)
	jle	.L76
	addq	$8, %rdx
	jmp	.L70
.L81:
	movsd	-48(%rbp), %xmm8
	movsd	-40(%rbp), %xmm7
	jmp	.L71
.L76:
	addq	$104, %rsp
	.cfi_def_cfa_offset 56
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
	.cfi_endproc
.LFE31:
	.size	nextPhase, .-nextPhase
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC1:
	.long	0
	.long	1071644672
	.align 8
.LC2:
	.long	0
	.long	1073217536
	.align 8
.LC3:
	.long	0
	.long	-1075838976
	.align 8
.LC5:
	.long	2576980378
	.long	1069128089
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC12:
	.long	805306368
	.section	.rodata.cst8
	.align 8
.LC13:
	.long	0
	.long	1040187392
	.align 8
.LC14:
	.long	2696277389
	.long	1051772663
	.align 8
.LC16:
	.long	3539053052
	.long	1062232653
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-3)"
	.section	.note.GNU-stack,"",@progbits
