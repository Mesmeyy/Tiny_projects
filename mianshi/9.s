	.file	"9.c"
	.section	.rodata
.LC0:
	.string	"c is %d\n"
.LC1:
	.string	"a is %d\n"
.LC2:
	.string	"b is %d\n"
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
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$2, -8(%rbp)
	movl	$5, -4(%rbp)
	movl	$1, -12(%rbp)
	jmp	.L2
.L7:
	movl	-12(%rbp), %eax
	cmpl	$1, %eax
	je	.L4
	cmpl	$2, %eax
	jne	.L9
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	jmp	.L6
.L9:
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
.L4:
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	nop
.L6:
	addl	$1, -12(%rbp)
.L2:
	cmpl	$3, -12(%rbp)
	jle	.L7
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
