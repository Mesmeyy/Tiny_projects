	.file	"9.1.c"
	.section	.rodata
.LC0:
	.string	"%d"
.LC1:
	.string	"1"
.LC2:
	.string	"2"
.LC3:
	.string	"3"
.LC4:
	.string	"4"
.LC5:
	.string	"5"
.LC6:
	.string	"6"
.LC7:
	.string	"7"
.LC8:
	.string	"8"
.LC9:
	.string	"9"
.LC10:
	.string	"10"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-12(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	-12(%rbp), %eax
	cmpl	$10, %eax
	ja	.L2
	movl	%eax, %eax
	movq	.L4(,%rax,8), %rax
	jmp	*%rax
	.section	.rodata
	.align 8
	.align 4
.L4:
	.quad	.L2
	.quad	.L3
	.quad	.L5
	.quad	.L6
	.quad	.L7
	.quad	.L8
	.quad	.L9
	.quad	.L10
	.quad	.L11
	.quad	.L12
	.quad	.L13
	.text
.L3:
	movl	$.LC1, %edi
	call	puts
.L5:
	movl	$.LC2, %edi
	call	puts
.L6:
	movl	$.LC3, %edi
	call	puts
.L7:
	movl	$.LC4, %edi
	call	puts
.L8:
	movl	$.LC5, %edi
	call	puts
.L9:
	movl	$.LC6, %edi
	call	puts
.L10:
	movl	$.LC7, %edi
	call	puts
.L11:
	movl	$.LC8, %edi
	call	puts
.L12:
	movl	$.LC9, %edi
	call	puts
.L13:
	movl	$.LC10, %edi
	call	puts
.L2:
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	xorq	%fs:40, %rdx
	je	.L15
	call	__stack_chk_fail
.L15:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
