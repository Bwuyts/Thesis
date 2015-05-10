	.file	"timing.c"
	.text
.Ltext0:
	.p2align 4,,15
	.globl	HiResTime
	.type	HiResTime, @function
HiResTime:
.LFB1071:
	.file 1 "timing.c"
	.loc 1 34 0
	.cfi_startproc
	.loc 1 51 0
#APP
# 51 "timing.c" 1
	rdtsc
# 0 "" 2
.LVL0:
	.loc 1 63 0
#NO_APP
	ret
	.cfi_endproc
.LFE1071:
	.size	HiResTime, .-HiResTime
	.p2align 4,,15
	.globl	calibrate
	.type	calibrate, @function
calibrate:
.LFB1072:
	.loc 1 70 0
	.cfi_startproc
.LVL1:
	.loc 1 70 0
	movl	$10000, %esi
	.loc 1 71 0
	movl	$-1, %ecx
.LVL2:
	.p2align 4,,10
	.p2align 3
.L4:
.LBB16:
.LBB17:
	.loc 1 51 0
#APP
# 51 "timing.c" 1
	rdtsc
# 0 "" 2
#NO_APP
	movl	%eax, %edi
.LVL3:
.LBE17:
.LBE16:
.LBB18:
.LBB19:
#APP
# 51 "timing.c" 1
	rdtsc
# 0 "" 2
.LVL4:
#NO_APP
.LBE19:
.LBE18:
	.loc 1 78 0
	subl	%edi, %eax
.LVL5:
	cmpl	%eax, %ecx
	cmova	%eax, %ecx
.LVL6:
	.loc 1 74 0
	subl	$1, %esi
	jne	.L4
	.loc 1 82 0
	movl	%ecx, %eax
	ret
	.cfi_endproc
.LFE1072:
	.size	calibrate, .-calibrate
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"Cycles for calibrate: %d\n"
.LC3:
	.string	"Cycles for AEGIS: %d\n"
.LC5:
	.string	"Cycles per byte:   %f\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB1073:
	.loc 1 88 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	.loc 1 97 0
	xorl	%edi, %edi
	.loc 1 88 0
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	andq	$-32, %rsp
	subq	$22480, %rsp
	.cfi_offset 14, -24
	.cfi_offset 13, -32
	.cfi_offset 12, -40
	.cfi_offset 3, -48
	.loc 1 90 0
	vmovdqa	.LC0(%rip), %xmm0
	leaq	80(%rsp), %rbx
	leaq	11200(%rbx), %r12
	vmovdqa	%xmm0, 16(%rsp)
	.loc 1 91 0
	vmovdqa	.LC1(%rip), %xmm0
	vmovdqa	%xmm0, 48(%rsp)
.LVL7:
	.loc 1 97 0
	call	time
.LVL8:
	movl	%eax, %edi
	call	srand
.LVL9:
	.p2align 4,,10
	.p2align 3
.L8:
	.loc 1 99 0 discriminator 2
	call	rand
.LVL10:
	addq	$1, %rbx
.LVL11:
	movb	%al, -1(%rbx)
	.loc 1 98 0 discriminator 2
	cmpq	%r12, %rbx
	jne	.L8
	.loc 1 98 0 is_stmt 0
	movl	$10000, %ecx
	movl	$-1, %ebx
	.p2align 4,,10
	.p2align 3
.L10:
.LVL12:
.LBB20:
.LBB21:
.LBB22:
.LBB23:
	.loc 1 51 0 is_stmt 1
#APP
# 51 "timing.c" 1
	rdtsc
# 0 "" 2
#NO_APP
	movl	%eax, %esi
.LVL13:
.LBE23:
.LBE22:
.LBB24:
.LBB25:
#APP
# 51 "timing.c" 1
	rdtsc
# 0 "" 2
.LVL14:
#NO_APP
.LBE25:
.LBE24:
	.loc 1 78 0
	subl	%esi, %eax
.LVL15:
	cmpl	%eax, %ebx
	cmova	%eax, %ebx
.LVL16:
	.loc 1 74 0
	subl	$1, %ecx
	jne	.L10
.LBE21:
.LBE20:
	.loc 1 117 0
	movl	%ebx, %esi
.LVL17:
	movl	$.LC2, %edi
	xorl	%eax, %eax
	call	printf
.LVL18:
	movl	$1000, %r12d
.LVL19:
	.p2align 4,,10
	.p2align 3
.L12:
	.loc 1 121 0 discriminator 2
	movq	$89600, 8(%rsp)
	leaq	64(%rsp), %r9
	xorl	%edx, %edx
	movq	$0, (%rsp)
	leaq	11280(%rsp), %r8
	leaq	80(%rsp), %rcx
	leaq	48(%rsp), %rsi
	leaq	16(%rsp), %rdi
	call	encrypt
.LVL20:
	.loc 1 119 0 discriminator 2
	subl	$1, %r12d
	jne	.L12
	.loc 1 119 0 is_stmt 0
	movl	$10000, %r13d
	movl	$4294967295, %r12d
	.p2align 4,,10
	.p2align 3
.L14:
.LVL21:
.LBB26:
.LBB27:
	.loc 1 51 0 is_stmt 1
#APP
# 51 "timing.c" 1
	rdtsc
# 0 "" 2
#NO_APP
.LBE27:
.LBE26:
	.loc 1 127 0
	xorl	%edx, %edx
	movq	$0, (%rsp)
.LBB29:
.LBB28:
	.loc 1 51 0
	movl	%eax, %r14d
.LVL22:
.LBE28:
.LBE29:
	.loc 1 127 0
	movq	$89600, 8(%rsp)
	leaq	64(%rsp), %r9
	leaq	11280(%rsp), %r8
	leaq	80(%rsp), %rcx
	leaq	48(%rsp), %rsi
	leaq	16(%rsp), %rdi
	call	encrypt
.LVL23:
.LBB30:
.LBB31:
	.loc 1 51 0
#APP
# 51 "timing.c" 1
	rdtsc
# 0 "" 2
.LVL24:
#NO_APP
.LBE31:
.LBE30:
	.loc 1 131 0
	subl	%r14d, %eax
.LVL25:
	subl	%ebx, %eax
	cmpl	%eax, %r12d
	cmova	%rax, %r12
.LVL26:
	.loc 1 123 0
	subl	$1, %r13d
	jne	.L14
	.loc 1 136 0
	movl	%r12d, %esi
	movl	$.LC3, %edi
	xorl	%eax, %eax
	call	printf
.LVL27:
	.loc 1 137 0
	movl	$.LC5, %edi
	movl	$1, %eax
	vcvtsi2sdq	%r12, %xmm0, %xmm0
	vdivsd	.LC4(%rip), %xmm0, %xmm0
	call	printf
.LVL28:
	.loc 1 147 0
	xorl	%eax, %eax
	leaq	-32(%rbp), %rsp
	popq	%rbx
.LVL29:
	popq	%r12
.LVL30:
	popq	%r13
	popq	%r14
.LVL31:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1073:
	.size	main, .-main
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.byte	127
	.byte	126
	.byte	125
	.byte	124
	.byte	123
	.byte	122
	.byte	121
	.byte	120
	.byte	119
	.byte	118
	.byte	117
	.byte	116
	.byte	115
	.byte	114
	.byte	113
	.byte	112
	.align 16
.LC1:
	.byte	9
	.byte	-7
	.byte	17
	.byte	2
	.byte	-99
	.byte	116
	.byte	-29
	.byte	91
	.byte	-40
	.byte	65
	.byte	86
	.byte	-59
	.byte	99
	.byte	86
	.byte	-120
	.byte	-64
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC4:
	.long	0
	.long	1086709760
	.text
.Letext0:
	.file 2 "/usr/lib/gcc/x86_64-redhat-linux/4.8.2/include/stddef.h"
	.file 3 "/usr/include/bits/types.h"
	.file 4 "/usr/include/libio.h"
	.file 5 "/usr/include/stdint.h"
	.file 6 "/usr/include/time.h"
	.file 7 "/usr/include/stdio.h"
	.file 8 "/usr/include/stdlib.h"
	.file 9 "aegis.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x7d7
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF64
	.byte	0x1
	.long	.LASF65
	.long	.LASF66
	.long	.Ldebug_ranges0+0x30
	.quad	0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.long	.LASF0
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF1
	.uleb128 0x3
	.long	.LASF8
	.byte	0x2
	.byte	0xd4
	.long	0x42
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF2
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF3
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF4
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF5
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF6
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.long	.LASF7
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.long	.LASF9
	.byte	0x3
	.byte	0x8c
	.long	0x30
	.uleb128 0x3
	.long	.LASF10
	.byte	0x3
	.byte	0x8d
	.long	0x30
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF11
	.uleb128 0x3
	.long	.LASF12
	.byte	0x3
	.byte	0x94
	.long	0x30
	.uleb128 0x5
	.byte	0x8
	.uleb128 0x6
	.byte	0x8
	.long	0xa3
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF13
	.uleb128 0x7
	.long	.LASF43
	.byte	0xd8
	.byte	0x4
	.byte	0xf6
	.long	0x22b
	.uleb128 0x8
	.long	.LASF14
	.byte	0x4
	.byte	0xf7
	.long	0x6c
	.byte	0
	.uleb128 0x8
	.long	.LASF15
	.byte	0x4
	.byte	0xfc
	.long	0x9d
	.byte	0x8
	.uleb128 0x8
	.long	.LASF16
	.byte	0x4
	.byte	0xfd
	.long	0x9d
	.byte	0x10
	.uleb128 0x8
	.long	.LASF17
	.byte	0x4
	.byte	0xfe
	.long	0x9d
	.byte	0x18
	.uleb128 0x8
	.long	.LASF18
	.byte	0x4
	.byte	0xff
	.long	0x9d
	.byte	0x20
	.uleb128 0x9
	.long	.LASF19
	.byte	0x4
	.value	0x100
	.long	0x9d
	.byte	0x28
	.uleb128 0x9
	.long	.LASF20
	.byte	0x4
	.value	0x101
	.long	0x9d
	.byte	0x30
	.uleb128 0x9
	.long	.LASF21
	.byte	0x4
	.value	0x102
	.long	0x9d
	.byte	0x38
	.uleb128 0x9
	.long	.LASF22
	.byte	0x4
	.value	0x103
	.long	0x9d
	.byte	0x40
	.uleb128 0x9
	.long	.LASF23
	.byte	0x4
	.value	0x105
	.long	0x9d
	.byte	0x48
	.uleb128 0x9
	.long	.LASF24
	.byte	0x4
	.value	0x106
	.long	0x9d
	.byte	0x50
	.uleb128 0x9
	.long	.LASF25
	.byte	0x4
	.value	0x107
	.long	0x9d
	.byte	0x58
	.uleb128 0x9
	.long	.LASF26
	.byte	0x4
	.value	0x109
	.long	0x263
	.byte	0x60
	.uleb128 0x9
	.long	.LASF27
	.byte	0x4
	.value	0x10b
	.long	0x269
	.byte	0x68
	.uleb128 0x9
	.long	.LASF28
	.byte	0x4
	.value	0x10d
	.long	0x6c
	.byte	0x70
	.uleb128 0x9
	.long	.LASF29
	.byte	0x4
	.value	0x111
	.long	0x6c
	.byte	0x74
	.uleb128 0x9
	.long	.LASF30
	.byte	0x4
	.value	0x113
	.long	0x73
	.byte	0x78
	.uleb128 0x9
	.long	.LASF31
	.byte	0x4
	.value	0x117
	.long	0x50
	.byte	0x80
	.uleb128 0x9
	.long	.LASF32
	.byte	0x4
	.value	0x118
	.long	0x5e
	.byte	0x82
	.uleb128 0x9
	.long	.LASF33
	.byte	0x4
	.value	0x119
	.long	0x26f
	.byte	0x83
	.uleb128 0x9
	.long	.LASF34
	.byte	0x4
	.value	0x11d
	.long	0x27f
	.byte	0x88
	.uleb128 0x9
	.long	.LASF35
	.byte	0x4
	.value	0x126
	.long	0x7e
	.byte	0x90
	.uleb128 0x9
	.long	.LASF36
	.byte	0x4
	.value	0x12f
	.long	0x9b
	.byte	0x98
	.uleb128 0x9
	.long	.LASF37
	.byte	0x4
	.value	0x130
	.long	0x9b
	.byte	0xa0
	.uleb128 0x9
	.long	.LASF38
	.byte	0x4
	.value	0x131
	.long	0x9b
	.byte	0xa8
	.uleb128 0x9
	.long	.LASF39
	.byte	0x4
	.value	0x132
	.long	0x9b
	.byte	0xb0
	.uleb128 0x9
	.long	.LASF40
	.byte	0x4
	.value	0x133
	.long	0x37
	.byte	0xb8
	.uleb128 0x9
	.long	.LASF41
	.byte	0x4
	.value	0x135
	.long	0x6c
	.byte	0xc0
	.uleb128 0x9
	.long	.LASF42
	.byte	0x4
	.value	0x137
	.long	0x285
	.byte	0xc4
	.byte	0
	.uleb128 0xa
	.long	.LASF67
	.byte	0x4
	.byte	0x9b
	.uleb128 0x7
	.long	.LASF44
	.byte	0x18
	.byte	0x4
	.byte	0xa1
	.long	0x263
	.uleb128 0x8
	.long	.LASF45
	.byte	0x4
	.byte	0xa2
	.long	0x263
	.byte	0
	.uleb128 0x8
	.long	.LASF46
	.byte	0x4
	.byte	0xa3
	.long	0x269
	.byte	0x8
	.uleb128 0x8
	.long	.LASF47
	.byte	0x4
	.byte	0xa7
	.long	0x6c
	.byte	0x10
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x232
	.uleb128 0x6
	.byte	0x8
	.long	0xaa
	.uleb128 0xb
	.long	0xa3
	.long	0x27f
	.uleb128 0xc
	.long	0x89
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x22b
	.uleb128 0xb
	.long	0xa3
	.long	0x295
	.uleb128 0xc
	.long	0x89
	.byte	0x13
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x29b
	.uleb128 0xd
	.long	0xa3
	.uleb128 0x3
	.long	.LASF48
	.byte	0x5
	.byte	0x28
	.long	0x30
	.uleb128 0x3
	.long	.LASF49
	.byte	0x5
	.byte	0x33
	.long	0x57
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF50
	.uleb128 0x3
	.long	.LASF51
	.byte	0x6
	.byte	0x4b
	.long	0x90
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF52
	.uleb128 0x2
	.byte	0x4
	.byte	0x4
	.long	.LASF53
	.uleb128 0xe
	.long	.LASF58
	.byte	0x1
	.byte	0x21
	.long	0x2ab
	.byte	0x1
	.long	0x2f0
	.uleb128 0xf
	.string	"x"
	.byte	0x1
	.byte	0x24
	.long	0x2f0
	.byte	0
	.uleb128 0xb
	.long	0x2ab
	.long	0x300
	.uleb128 0xc
	.long	0x89
	.byte	0x1
	.byte	0
	.uleb128 0x10
	.long	.LASF60
	.byte	0x1
	.byte	0x45
	.long	0x2ab
	.byte	0x1
	.long	0x339
	.uleb128 0x11
	.long	.LASF54
	.byte	0x1
	.byte	0x47
	.long	0x2ab
	.uleb128 0xf
	.string	"t0"
	.byte	0x1
	.byte	0x48
	.long	0x2ab
	.uleb128 0xf
	.string	"t1"
	.byte	0x1
	.byte	0x48
	.long	0x2ab
	.uleb128 0xf
	.string	"i"
	.byte	0x1
	.byte	0x48
	.long	0x2ab
	.byte	0
	.uleb128 0x12
	.long	0x2d6
	.quad	.LFB1071
	.quad	.LFE1071-.LFB1071
	.uleb128 0x1
	.byte	0x9c
	.long	0x360
	.uleb128 0x13
	.long	0x2e6
	.uleb128 0x5
	.byte	0x50
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x4
	.byte	0
	.uleb128 0x12
	.long	0x300
	.quad	.LFB1072
	.quad	.LFE1072-.LFB1072
	.uleb128 0x1
	.byte	0x9c
	.long	0x402
	.uleb128 0x14
	.long	0x310
	.long	.LLST0
	.uleb128 0x15
	.long	0x31b
	.uleb128 0x15
	.long	0x325
	.uleb128 0x14
	.long	0x32f
	.long	.LLST1
	.uleb128 0x16
	.long	0x2d6
	.quad	.LBB16
	.quad	.LBE16-.LBB16
	.byte	0x1
	.byte	0x4c
	.long	0x3ce
	.uleb128 0x17
	.quad	.LBB17
	.quad	.LBE17-.LBB17
	.uleb128 0x14
	.long	0x2e6
	.long	.LLST2
	.byte	0
	.byte	0
	.uleb128 0x18
	.long	0x2d6
	.quad	.LBB18
	.quad	.LBE18-.LBB18
	.byte	0x1
	.byte	0x4d
	.uleb128 0x17
	.quad	.LBB19
	.quad	.LBE19-.LBB19
	.uleb128 0x14
	.long	0x2e6
	.long	.LLST3
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x19
	.long	.LASF68
	.byte	0x1
	.byte	0x58
	.long	0x6c
	.quad	.LFB1073
	.quad	.LFE1073-.LFB1073
	.uleb128 0x1
	.byte	0x9c
	.long	0x709
	.uleb128 0x1a
	.string	"key"
	.byte	0x1
	.byte	0x5a
	.long	0x719
	.uleb128 0x2
	.byte	0x77
	.sleb128 16
	.uleb128 0x1a
	.string	"IV"
	.byte	0x1
	.byte	0x5b
	.long	0x709
	.uleb128 0x2
	.byte	0x77
	.sleb128 48
	.uleb128 0x1a
	.string	"in"
	.byte	0x1
	.byte	0x5c
	.long	0x71e
	.uleb128 0x3
	.byte	0x77
	.sleb128 80
	.uleb128 0x1a
	.string	"out"
	.byte	0x1
	.byte	0x5c
	.long	0x71e
	.uleb128 0x4
	.byte	0x77
	.sleb128 11280
	.uleb128 0x1a
	.string	"tag"
	.byte	0x1
	.byte	0x5c
	.long	0x709
	.uleb128 0x3
	.byte	0x77
	.sleb128 64
	.uleb128 0x1b
	.string	"i"
	.byte	0x1
	.byte	0x5f
	.long	0x6c
	.long	.LLST4
	.uleb128 0x1b
	.string	"j"
	.byte	0x1
	.byte	0x5f
	.long	0x6c
	.long	.LLST5
	.uleb128 0xf
	.string	"k"
	.byte	0x1
	.byte	0x5f
	.long	0x6c
	.uleb128 0x1c
	.string	"l"
	.byte	0x1
	.byte	0x5f
	.long	0x6c
	.byte	0x64
	.uleb128 0xf
	.string	"t0"
	.byte	0x1
	.byte	0x70
	.long	0x2ab
	.uleb128 0xf
	.string	"t1"
	.byte	0x1
	.byte	0x70
	.long	0x2ab
	.uleb128 0x1d
	.long	.LASF55
	.byte	0x1
	.byte	0x72
	.long	0x2ab
	.long	.LLST6
	.uleb128 0x11
	.long	.LASF54
	.byte	0x1
	.byte	0x74
	.long	0x2ab
	.uleb128 0x16
	.long	0x300
	.quad	.LBB20
	.quad	.LBE20-.LBB20
	.byte	0x1
	.byte	0x74
	.long	0x56e
	.uleb128 0x17
	.quad	.LBB21
	.quad	.LBE21-.LBB21
	.uleb128 0x14
	.long	0x310
	.long	.LLST7
	.uleb128 0x15
	.long	0x31b
	.uleb128 0x15
	.long	0x325
	.uleb128 0x15
	.long	0x32f
	.uleb128 0x16
	.long	0x2d6
	.quad	.LBB22
	.quad	.LBE22-.LBB22
	.byte	0x1
	.byte	0x4c
	.long	0x53d
	.uleb128 0x17
	.quad	.LBB23
	.quad	.LBE23-.LBB23
	.uleb128 0x15
	.long	0x2e6
	.byte	0
	.byte	0
	.uleb128 0x18
	.long	0x2d6
	.quad	.LBB24
	.quad	.LBE24-.LBB24
	.byte	0x1
	.byte	0x4d
	.uleb128 0x17
	.quad	.LBB25
	.quad	.LBE25-.LBB25
	.uleb128 0x15
	.long	0x2e6
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1e
	.long	0x2d6
	.quad	.LBB26
	.long	.Ldebug_ranges0+0
	.byte	0x1
	.byte	0x7c
	.long	0x595
	.uleb128 0x1f
	.long	.Ldebug_ranges0+0
	.uleb128 0x14
	.long	0x2e6
	.long	.LLST8
	.byte	0
	.byte	0
	.uleb128 0x16
	.long	0x2d6
	.quad	.LBB30
	.quad	.LBE30-.LBB30
	.byte	0x1
	.byte	0x82
	.long	0x5cc
	.uleb128 0x17
	.quad	.LBB31
	.quad	.LBE31-.LBB31
	.uleb128 0x14
	.long	0x2e6
	.long	.LLST9
	.byte	0
	.byte	0
	.uleb128 0x20
	.quad	.LVL8
	.long	0x745
	.long	0x5e3
	.uleb128 0x21
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.uleb128 0x22
	.quad	.LVL9
	.long	0x760
	.uleb128 0x22
	.quad	.LVL10
	.long	0x772
	.uleb128 0x20
	.quad	.LVL18
	.long	0x77e
	.long	0x622
	.uleb128 0x21
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x9
	.byte	0x3
	.quad	.LC2
	.uleb128 0x21
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x2
	.byte	0x73
	.sleb128 0
	.byte	0
	.uleb128 0x20
	.quad	.LVL20
	.long	0x795
	.long	0x66a
	.uleb128 0x21
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x2
	.byte	0x77
	.sleb128 16
	.uleb128 0x21
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x2
	.byte	0x77
	.sleb128 48
	.uleb128 0x21
	.uleb128 0x1
	.byte	0x51
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x21
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x3
	.byte	0x77
	.sleb128 80
	.uleb128 0x21
	.uleb128 0x1
	.byte	0x58
	.uleb128 0x4
	.byte	0x77
	.sleb128 11280
	.uleb128 0x21
	.uleb128 0x1
	.byte	0x59
	.uleb128 0x3
	.byte	0x77
	.sleb128 64
	.uleb128 0x21
	.uleb128 0x2
	.byte	0x77
	.sleb128 0
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x21
	.uleb128 0x2
	.byte	0x77
	.sleb128 8
	.uleb128 0x4
	.byte	0x8
	.byte	0xaf
	.byte	0x39
	.byte	0x24
	.byte	0
	.uleb128 0x20
	.quad	.LVL23
	.long	0x795
	.long	0x6b2
	.uleb128 0x21
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x2
	.byte	0x77
	.sleb128 16
	.uleb128 0x21
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x2
	.byte	0x77
	.sleb128 48
	.uleb128 0x21
	.uleb128 0x1
	.byte	0x51
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x21
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x3
	.byte	0x77
	.sleb128 80
	.uleb128 0x21
	.uleb128 0x1
	.byte	0x58
	.uleb128 0x4
	.byte	0x77
	.sleb128 11280
	.uleb128 0x21
	.uleb128 0x1
	.byte	0x59
	.uleb128 0x3
	.byte	0x77
	.sleb128 64
	.uleb128 0x21
	.uleb128 0x2
	.byte	0x77
	.sleb128 0
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x21
	.uleb128 0x2
	.byte	0x77
	.sleb128 8
	.uleb128 0x4
	.byte	0x8
	.byte	0xaf
	.byte	0x39
	.byte	0x24
	.byte	0
	.uleb128 0x20
	.quad	.LVL27
	.long	0x77e
	.long	0x6d7
	.uleb128 0x21
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x9
	.byte	0x3
	.quad	.LC3
	.uleb128 0x21
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x2
	.byte	0x7c
	.sleb128 0
	.byte	0
	.uleb128 0x23
	.quad	.LVL28
	.long	0x77e
	.uleb128 0x21
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x9
	.byte	0x3
	.quad	.LC5
	.uleb128 0x21
	.uleb128 0x1
	.byte	0x61
	.uleb128 0x12
	.byte	0x7c
	.sleb128 0
	.byte	0xf7
	.uleb128 0x30
	.byte	0xf7
	.uleb128 0x29
	.byte	0xf4
	.uleb128 0x29
	.byte	0x8
	.long	0
	.long	0x40c5e000
	.byte	0x1b
	.byte	0
	.byte	0
	.uleb128 0xb
	.long	0x49
	.long	0x719
	.uleb128 0xc
	.long	0x89
	.byte	0xf
	.byte	0
	.uleb128 0xd
	.long	0x709
	.uleb128 0xb
	.long	0x49
	.long	0x72f
	.uleb128 0x24
	.long	0x89
	.value	0x2bbf
	.byte	0
	.uleb128 0x25
	.long	.LASF56
	.byte	0x7
	.byte	0xa8
	.long	0x269
	.uleb128 0x25
	.long	.LASF57
	.byte	0x7
	.byte	0xa9
	.long	0x269
	.uleb128 0x26
	.long	.LASF59
	.byte	0x6
	.byte	0xc0
	.long	0x2bd
	.long	0x75a
	.uleb128 0x27
	.long	0x75a
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x2bd
	.uleb128 0x28
	.long	.LASF61
	.byte	0x8
	.value	0x178
	.long	0x772
	.uleb128 0x27
	.long	0x57
	.byte	0
	.uleb128 0x29
	.long	.LASF69
	.byte	0x8
	.value	0x176
	.long	0x6c
	.uleb128 0x2a
	.long	.LASF62
	.byte	0x7
	.value	0x16a
	.long	0x6c
	.long	0x795
	.uleb128 0x27
	.long	0x295
	.uleb128 0x2b
	.byte	0
	.uleb128 0x2c
	.long	.LASF63
	.byte	0x9
	.byte	0x3
	.long	0x7c9
	.uleb128 0x27
	.long	0x7c9
	.uleb128 0x27
	.long	0x7d4
	.uleb128 0x27
	.long	0x7d4
	.uleb128 0x27
	.long	0x7d4
	.uleb128 0x27
	.long	0x7d4
	.uleb128 0x27
	.long	0x7d4
	.uleb128 0x27
	.long	0x2a0
	.uleb128 0x27
	.long	0x2a0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x7cf
	.uleb128 0xd
	.long	0x49
	.uleb128 0x6
	.byte	0x8
	.long	0x49
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x2111
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x28
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2b
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.quad	.LVL1
	.quad	.LVL2
	.value	0x3
	.byte	0x9
	.byte	0xff
	.byte	0x9f
	.quad	.LVL2
	.quad	.LFE1072
	.value	0x1
	.byte	0x52
	.quad	0
	.quad	0
.LLST1:
	.quad	.LVL1
	.quad	.LVL2
	.value	0x2
	.byte	0x30
	.byte	0x9f
	.quad	0
	.quad	0
.LLST2:
	.quad	.LVL3
	.quad	.LVL4
	.value	0x5
	.byte	0x50
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x4
	.quad	.LVL4
	.quad	.LFE1072
	.value	0x5
	.byte	0x55
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x4
	.quad	0
	.quad	0
.LLST3:
	.quad	.LVL4
	.quad	.LVL5
	.value	0x5
	.byte	0x50
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x4
	.quad	0
	.quad	0
.LLST4:
	.quad	.LVL9
	.quad	.LVL11
	.value	0x9
	.byte	0x73
	.sleb128 0
	.byte	0x77
	.sleb128 0
	.byte	0x1c
	.byte	0x8
	.byte	0x50
	.byte	0x1c
	.byte	0x9f
	.quad	0
	.quad	0
.LLST5:
	.quad	.LVL18
	.quad	.LVL19
	.value	0x2
	.byte	0x30
	.byte	0x9f
	.quad	0
	.quad	0
.LLST6:
	.quad	.LVL21
	.quad	.LVL30
	.value	0x1
	.byte	0x5c
	.quad	0
	.quad	0
.LLST7:
	.quad	.LVL12
	.quad	.LVL29
	.value	0x1
	.byte	0x53
	.quad	0
	.quad	0
.LLST8:
	.quad	.LVL22
	.quad	.LVL23-1
	.value	0x5
	.byte	0x50
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x4
	.quad	.LVL23-1
	.quad	.LVL31
	.value	0x5
	.byte	0x5e
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x4
	.quad	0
	.quad	0
.LLST9:
	.quad	.LVL24
	.quad	.LVL25
	.value	0x5
	.byte	0x50
	.byte	0x93
	.uleb128 0x4
	.byte	0x93
	.uleb128 0x4
	.quad	0
	.quad	0
	.section	.debug_aranges,"",@progbits
	.long	0x3c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	.LFB1073
	.quad	.LFE1073-.LFB1073
	.quad	0
	.quad	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.quad	.LBB26
	.quad	.LBE26
	.quad	.LBB29
	.quad	.LBE29
	.quad	0
	.quad	0
	.quad	.Ltext0
	.quad	.Letext0
	.quad	.LFB1073
	.quad	.LFE1073
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF62:
	.string	"printf"
.LASF9:
	.string	"__off_t"
.LASF15:
	.string	"_IO_read_ptr"
.LASF27:
	.string	"_chain"
.LASF66:
	.string	"/users/start2012/r0256089/Documents/Thesis/aegis/timing"
.LASF8:
	.string	"size_t"
.LASF33:
	.string	"_shortbuf"
.LASF21:
	.string	"_IO_buf_base"
.LASF52:
	.string	"long long unsigned int"
.LASF58:
	.string	"HiResTime"
.LASF55:
	.string	"tMin"
.LASF65:
	.string	"timing.c"
.LASF6:
	.string	"signed char"
.LASF28:
	.string	"_fileno"
.LASF16:
	.string	"_IO_read_end"
.LASF1:
	.string	"long int"
.LASF14:
	.string	"_flags"
.LASF22:
	.string	"_IO_buf_end"
.LASF31:
	.string	"_cur_column"
.LASF50:
	.string	"long long int"
.LASF0:
	.string	"double"
.LASF30:
	.string	"_old_offset"
.LASF35:
	.string	"_offset"
.LASF44:
	.string	"_IO_marker"
.LASF56:
	.string	"stdin"
.LASF5:
	.string	"unsigned int"
.LASF2:
	.string	"long unsigned int"
.LASF69:
	.string	"rand"
.LASF19:
	.string	"_IO_write_ptr"
.LASF63:
	.string	"encrypt"
.LASF46:
	.string	"_sbuf"
.LASF4:
	.string	"short unsigned int"
.LASF23:
	.string	"_IO_save_base"
.LASF60:
	.string	"calibrate"
.LASF34:
	.string	"_lock"
.LASF29:
	.string	"_flags2"
.LASF41:
	.string	"_mode"
.LASF57:
	.string	"stdout"
.LASF11:
	.string	"sizetype"
.LASF20:
	.string	"_IO_write_end"
.LASF67:
	.string	"_IO_lock_t"
.LASF43:
	.string	"_IO_FILE"
.LASF59:
	.string	"time"
.LASF64:
	.ascii	"GNU C 4.8.2 20140120 (Red Hat 4.8.2-16) -march=core-avx-i -m"
	.ascii	"cx16 -msahf -mno-movbe -mpclmul -mpopcnt -mno-abm -mno-lwp -"
	.ascii	"mno-fma -mno-fma4 -mno-xop -mno-bmi -mno-bmi2 -mno-tbm -mavx"
	.ascii	" -msse4.2 -msse4.1 -mn"
	.string	"o-lzcnt -mno-rtm -mno-hle -mrdrnd -mf16c -mfsgsbase -mno-rdseed -mno-prfchw -mno-adx -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=6144 -mtune=core-avx-i -maes -mavx2 -m64 -g -O3 -fomit-frame-pointer"
.LASF53:
	.string	"float"
.LASF47:
	.string	"_pos"
.LASF26:
	.string	"_markers"
.LASF61:
	.string	"srand"
.LASF51:
	.string	"time_t"
.LASF54:
	.string	"dtMin"
.LASF3:
	.string	"unsigned char"
.LASF7:
	.string	"short int"
.LASF32:
	.string	"_vtable_offset"
.LASF49:
	.string	"uint32_t"
.LASF13:
	.string	"char"
.LASF45:
	.string	"_next"
.LASF10:
	.string	"__off64_t"
.LASF17:
	.string	"_IO_read_base"
.LASF25:
	.string	"_IO_save_end"
.LASF36:
	.string	"__pad1"
.LASF37:
	.string	"__pad2"
.LASF38:
	.string	"__pad3"
.LASF39:
	.string	"__pad4"
.LASF40:
	.string	"__pad5"
.LASF12:
	.string	"__time_t"
.LASF42:
	.string	"_unused2"
.LASF24:
	.string	"_IO_backup_base"
.LASF48:
	.string	"int64_t"
.LASF68:
	.string	"main"
.LASF18:
	.string	"_IO_write_base"
	.ident	"GCC: (GNU) 4.8.2 20140120 (Red Hat 4.8.2-16)"
	.section	.note.GNU-stack,"",@progbits
