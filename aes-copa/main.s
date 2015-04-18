	.syntax unified
	.arch armv7-a
	.eabi_attribute 27, 3
	.eabi_attribute 28, 1
	.fpu vfpv3-d16
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.thumb
	.file	"main.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.thumb
	.thumb_func
	.type	main, %function
main:
.LFB46:
	.file 1 "main.c"
	.loc 1 54 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, sl, fp, lr}
.LCFI0:
	.cfi_def_cfa_offset 36
	.cfi_offset 4, -36
	.cfi_offset 5, -32
	.cfi_offset 6, -28
	.cfi_offset 7, -24
	.cfi_offset 8, -20
	.cfi_offset 9, -16
	.cfi_offset 10, -12
	.cfi_offset 11, -8
	.cfi_offset 14, -4
	.loc 1 56 0
	movw	r8, #:lower16:.LANCHOR0
	movt	r8, #:upper16:.LANCHOR0
	.loc 1 57 0
	movw	r6, #:lower16:.LANCHOR1
	movt	r6, #:upper16:.LANCHOR1
	.loc 1 54 0
	sub	sp, sp, #44
.LCFI1:
	.cfi_def_cfa_offset 80
	.loc 1 56 0
	mov	r0, r8
	movs	r1, #16
	movw	r2, #:lower16:.LC0
	.loc 1 58 0
	add	fp, r6, r1
	.loc 1 56 0
	movt	r2, #:upper16:.LC0
	.loc 1 60 0
	add	sl, r6, #44
	.loc 1 56 0
	bl	printchar
.LVL0:
	.loc 1 57 0
	mov	r0, r6
	movs	r1, #16
	movw	r2, #:lower16:.LC1
	movt	r2, #:upper16:.LC1
	.loc 1 63 0
	movw	r7, #:lower16:cipher
	.loc 1 57 0
	bl	printchar
.LVL1:
	.loc 1 63 0
	movt	r7, #:upper16:cipher
	.loc 1 58 0
	mov	r0, fp
	movs	r1, #26
	movw	r2, #:lower16:.LC2
	movt	r2, #:upper16:.LC2
	bl	printchar
.LVL2:
	.loc 1 60 0
	mov	r0, sl
	movs	r1, #26
	movw	r2, #:lower16:.LC3
	movt	r2, #:upper16:.LC3
	.loc 1 63 0
	movs	r4, #26
	.loc 1 60 0
	bl	printchar
.LVL3:
	.loc 1 63 0
	movs	r5, #0
	mov	r9, #0
	mov	r2, sl
	str	fp, [sp, #8]
	mov	r0, r7
	str	r6, [sp, #28]
	movw	r1, #:lower16:tag
	str	r8, [sp, #32]
	movt	r1, #:upper16:tag
	strd	r4, [sp]
	.loc 1 69 0
	movw	sl, #:lower16:decrypted
	.loc 1 63 0
	strd	r4, [sp, #16]
	.loc 1 69 0
	movt	sl, #:upper16:decrypted
	.loc 1 63 0
	str	r9, [sp, #24]
	bl	crypto_aead_encrypt
.LVL4:
	.loc 1 64 0
	mov	r0, r7
	movs	r1, #26
	movw	r2, #:lower16:.LC4
	movt	r2, #:upper16:.LC4
	bl	printchar
.LVL5:
	.loc 1 65 0
	add	r0, r7, #26
	movs	r1, #16
	movw	r2, #:lower16:.LC5
	movt	r2, #:upper16:.LC5
	bl	printchar
.LVL6:
	.loc 1 69 0
	mov	r3, r7
	mov	r1, r9
	mov	r2, r9
	str	fp, [sp, #8]
	mov	r0, sl
	str	r6, [sp, #24]
	str	r8, [sp, #28]
	strd	r4, [sp]
	strd	r4, [sp, #16]
	bl	crypto_aead_decrypt
.LVL7:
.LBB4:
.LBB5:
	.file 2 "/usr/include/arm-linux-gnueabihf/bits/stdio2.h"
	.loc 2 104 0
	movw	r1, #:lower16:.LC6
	movt	r1, #:upper16:.LC6
.LBE5:
.LBE4:
	.loc 1 69 0
	mov	r2, r0
.LVL8:
.LBB7:
.LBB6:
	.loc 2 104 0
	movs	r0, #1
.LVL9:
	bl	__printf_chk
.LVL10:
.LBE6:
.LBE7:
	.loc 1 71 0
	mov	r0, sl
	movs	r1, #26
	movw	r2, #:lower16:.LC7
	movt	r2, #:upper16:.LC7
	bl	printchar
.LVL11:
	.loc 1 73 0
	mov	r0, r9
	add	sp, sp, #44
	pop	{r4, r5, r6, r7, r8, r9, sl, fp, pc}
	.cfi_endproc
.LFE46:
	.size	main, .-main
	.comm	tag,16,8
	.comm	decrypted,26,4
	.comm	cipher,26,4
	.global	plain
	.global	nonce
	.global	adata
	.global	key
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	key, %object
	.size	key, 16
key:
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
	.data
	.align	2
.LANCHOR1 = . + 0
	.type	nonce, %object
	.size	nonce, 16
nonce:
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
	.type	adata, %object
	.size	adata, 26
adata:
	.byte	0
	.byte	17
	.byte	34
	.byte	51
	.byte	68
	.byte	85
	.byte	102
	.byte	119
	.byte	-120
	.byte	-103
	.byte	-86
	.byte	-69
	.byte	-52
	.byte	-35
	.byte	-18
	.byte	-1
	.byte	-1
	.byte	-18
	.byte	-35
	.byte	-52
	.byte	-69
	.byte	-86
	.byte	-103
	.byte	-120
	.byte	119
	.byte	102
	.space	2
	.type	plain, %object
	.size	plain, 26
plain:
	.byte	116
	.byte	104
	.byte	105
	.byte	115
	.byte	32
	.byte	105
	.byte	115
	.byte	32
	.byte	115
	.byte	111
	.byte	109
	.byte	101
	.byte	32
	.byte	112
	.byte	108
	.byte	97
	.byte	105
	.byte	110
	.byte	116
	.byte	101
	.byte	120
	.byte	116
	.byte	32
	.byte	116
	.byte	111
	.byte	32
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"key\000"
.LC1:
	.ascii	"nonce\000"
	.space	2
.LC2:
	.ascii	"adata\000"
	.space	2
.LC3:
	.ascii	"plain\000"
	.space	2
.LC4:
	.ascii	"cipher\000"
	.space	1
.LC5:
	.ascii	"tag\000"
.LC6:
	.ascii	"succes = %i\012\000"
	.space	3
.LC7:
	.ascii	"decrypt\000"
	.text
.Letext0:
	.file 3 "/usr/lib/gcc/arm-linux-gnueabihf/4.7/include/stddef.h"
	.file 4 "/usr/include/arm-linux-gnueabihf/bits/types.h"
	.file 5 "/usr/include/libio.h"
	.file 6 "/usr/include/stdio.h"
	.file 7 "encrypt.h"
	.file 8 "print.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0x68b
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF49
	.byte	0x1
	.4byte	.LASF50
	.4byte	.LASF51
	.4byte	.Ldebug_ranges0+0x18
	.4byte	0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF0
	.uleb128 0x3
	.4byte	.LASF8
	.byte	0x3
	.byte	0xd5
	.4byte	0x3b
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF1
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF2
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF4
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF5
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF7
	.uleb128 0x3
	.4byte	.LASF9
	.byte	0x4
	.byte	0x37
	.4byte	0x6c
	.uleb128 0x3
	.4byte	.LASF10
	.byte	0x4
	.byte	0x83
	.4byte	0x89
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF11
	.uleb128 0x3
	.4byte	.LASF12
	.byte	0x4
	.byte	0x84
	.4byte	0x73
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF13
	.uleb128 0x5
	.byte	0x4
	.uleb128 0x6
	.byte	0x4
	.4byte	0xaa
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF14
	.uleb128 0x7
	.4byte	.LASF44
	.byte	0x98
	.byte	0x5
	.byte	0xf5
	.4byte	0x26b
	.uleb128 0x8
	.4byte	.LASF15
	.byte	0x5
	.byte	0xf6
	.4byte	0x65
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.4byte	.LASF16
	.byte	0x5
	.byte	0xfb
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x8
	.4byte	.LASF17
	.byte	0x5
	.byte	0xfc
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x8
	.4byte	.LASF18
	.byte	0x5
	.byte	0xfd
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x8
	.4byte	.LASF19
	.byte	0x5
	.byte	0xfe
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0x8
	.4byte	.LASF20
	.byte	0x5
	.byte	0xff
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0x9
	.4byte	.LASF21
	.byte	0x5
	.2byte	0x100
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0x9
	.4byte	.LASF22
	.byte	0x5
	.2byte	0x101
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0x9
	.4byte	.LASF23
	.byte	0x5
	.2byte	0x102
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0x9
	.4byte	.LASF24
	.byte	0x5
	.2byte	0x104
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0x9
	.4byte	.LASF25
	.byte	0x5
	.2byte	0x105
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0x9
	.4byte	.LASF26
	.byte	0x5
	.2byte	0x106
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x2c
	.uleb128 0x9
	.4byte	.LASF27
	.byte	0x5
	.2byte	0x108
	.4byte	0x2a9
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0x9
	.4byte	.LASF28
	.byte	0x5
	.2byte	0x10a
	.4byte	0x2af
	.byte	0x2
	.byte	0x23
	.uleb128 0x34
	.uleb128 0x9
	.4byte	.LASF29
	.byte	0x5
	.2byte	0x10c
	.4byte	0x65
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0x9
	.4byte	.LASF30
	.byte	0x5
	.2byte	0x110
	.4byte	0x65
	.byte	0x2
	.byte	0x23
	.uleb128 0x3c
	.uleb128 0x9
	.4byte	.LASF31
	.byte	0x5
	.2byte	0x112
	.4byte	0x7e
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.uleb128 0x9
	.4byte	.LASF32
	.byte	0x5
	.2byte	0x116
	.4byte	0x49
	.byte	0x2
	.byte	0x23
	.uleb128 0x44
	.uleb128 0x9
	.4byte	.LASF33
	.byte	0x5
	.2byte	0x117
	.4byte	0x57
	.byte	0x2
	.byte	0x23
	.uleb128 0x46
	.uleb128 0x9
	.4byte	.LASF34
	.byte	0x5
	.2byte	0x118
	.4byte	0x2b5
	.byte	0x2
	.byte	0x23
	.uleb128 0x47
	.uleb128 0x9
	.4byte	.LASF35
	.byte	0x5
	.2byte	0x11c
	.4byte	0x2c5
	.byte	0x2
	.byte	0x23
	.uleb128 0x48
	.uleb128 0x9
	.4byte	.LASF36
	.byte	0x5
	.2byte	0x125
	.4byte	0x90
	.byte	0x2
	.byte	0x23
	.uleb128 0x50
	.uleb128 0x9
	.4byte	.LASF37
	.byte	0x5
	.2byte	0x12e
	.4byte	0xa2
	.byte	0x2
	.byte	0x23
	.uleb128 0x58
	.uleb128 0x9
	.4byte	.LASF38
	.byte	0x5
	.2byte	0x12f
	.4byte	0xa2
	.byte	0x2
	.byte	0x23
	.uleb128 0x5c
	.uleb128 0x9
	.4byte	.LASF39
	.byte	0x5
	.2byte	0x130
	.4byte	0xa2
	.byte	0x2
	.byte	0x23
	.uleb128 0x60
	.uleb128 0x9
	.4byte	.LASF40
	.byte	0x5
	.2byte	0x131
	.4byte	0xa2
	.byte	0x2
	.byte	0x23
	.uleb128 0x64
	.uleb128 0x9
	.4byte	.LASF41
	.byte	0x5
	.2byte	0x132
	.4byte	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x68
	.uleb128 0x9
	.4byte	.LASF42
	.byte	0x5
	.2byte	0x134
	.4byte	0x65
	.byte	0x2
	.byte	0x23
	.uleb128 0x6c
	.uleb128 0x9
	.4byte	.LASF43
	.byte	0x5
	.2byte	0x136
	.4byte	0x2cb
	.byte	0x2
	.byte	0x23
	.uleb128 0x70
	.byte	0
	.uleb128 0xa
	.4byte	.LASF63
	.byte	0x5
	.byte	0x9a
	.uleb128 0x7
	.4byte	.LASF45
	.byte	0xc
	.byte	0x5
	.byte	0xa0
	.4byte	0x2a9
	.uleb128 0x8
	.4byte	.LASF46
	.byte	0x5
	.byte	0xa1
	.4byte	0x2a9
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.4byte	.LASF47
	.byte	0x5
	.byte	0xa2
	.4byte	0x2af
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x8
	.4byte	.LASF48
	.byte	0x5
	.byte	0xa6
	.4byte	0x65
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x272
	.uleb128 0x6
	.byte	0x4
	.4byte	0xb1
	.uleb128 0xb
	.4byte	0xaa
	.4byte	0x2c5
	.uleb128 0xc
	.4byte	0x9b
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x26b
	.uleb128 0xb
	.4byte	0xaa
	.4byte	0x2db
	.uleb128 0xc
	.4byte	0x9b
	.byte	0x27
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x2e1
	.uleb128 0xd
	.4byte	0xaa
	.uleb128 0xe
	.byte	0x1
	.4byte	.LASF64
	.byte	0x2
	.byte	0x66
	.byte	0x1
	.4byte	0x65
	.byte	0x3
	.byte	0x1
	.4byte	0x306
	.uleb128 0xf
	.4byte	.LASF65
	.byte	0x2
	.byte	0x66
	.4byte	0x2db
	.uleb128 0x10
	.byte	0
	.uleb128 0x11
	.byte	0x1
	.4byte	.LASF66
	.byte	0x1
	.byte	0x36
	.4byte	0x65
	.4byte	.LFB46
	.4byte	.LFE46
	.4byte	.LLST0
	.byte	0x1
	.4byte	0x4f2
	.uleb128 0x12
	.4byte	.LASF67
	.byte	0x1
	.byte	0x37
	.4byte	0x65
	.4byte	.LLST1
	.uleb128 0x13
	.4byte	0x2e6
	.4byte	.LBB4
	.4byte	.Ldebug_ranges0+0
	.byte	0x1
	.byte	0x46
	.4byte	0x36a
	.uleb128 0x14
	.4byte	0x2f9
	.byte	0x6
	.byte	0x3
	.4byte	.LC6
	.byte	0x9f
	.uleb128 0x15
	.4byte	.LVL10
	.4byte	0x5bf
	.uleb128 0x16
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	.LC6
	.uleb128 0x16
	.byte	0x1
	.byte	0x50
	.byte	0x1
	.byte	0x31
	.byte	0
	.byte	0
	.uleb128 0x17
	.4byte	.LVL0
	.4byte	0x5dd
	.4byte	0x38c
	.uleb128 0x16
	.byte	0x1
	.byte	0x52
	.byte	0x5
	.byte	0x3
	.4byte	.LC0
	.uleb128 0x16
	.byte	0x1
	.byte	0x51
	.byte	0x1
	.byte	0x40
	.uleb128 0x16
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x78
	.sleb128 0
	.byte	0
	.uleb128 0x17
	.4byte	.LVL1
	.4byte	0x5dd
	.4byte	0x3ae
	.uleb128 0x16
	.byte	0x1
	.byte	0x52
	.byte	0x5
	.byte	0x3
	.4byte	.LC1
	.uleb128 0x16
	.byte	0x1
	.byte	0x51
	.byte	0x1
	.byte	0x40
	.uleb128 0x16
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x76
	.sleb128 0
	.byte	0
	.uleb128 0x17
	.4byte	.LVL2
	.4byte	0x5dd
	.4byte	0x3d0
	.uleb128 0x16
	.byte	0x1
	.byte	0x52
	.byte	0x5
	.byte	0x3
	.4byte	.LC2
	.uleb128 0x16
	.byte	0x1
	.byte	0x51
	.byte	0x1
	.byte	0x4a
	.uleb128 0x16
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x7b
	.sleb128 0
	.byte	0
	.uleb128 0x17
	.4byte	.LVL3
	.4byte	0x5dd
	.4byte	0x3f3
	.uleb128 0x16
	.byte	0x1
	.byte	0x52
	.byte	0x5
	.byte	0x3
	.4byte	.LC3
	.uleb128 0x16
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x16
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x7a
	.sleb128 0
	.byte	0
	.uleb128 0x17
	.4byte	.LVL4
	.4byte	0x601
	.4byte	0x442
	.uleb128 0x16
	.byte	0x1
	.byte	0x52
	.byte	0x2
	.byte	0x76
	.sleb128 44
	.uleb128 0x16
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	tag
	.uleb128 0x16
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x77
	.sleb128 0
	.uleb128 0x16
	.byte	0x2
	.byte	0x7d
	.sleb128 32
	.byte	0x2
	.byte	0x78
	.sleb128 0
	.uleb128 0x16
	.byte	0x2
	.byte	0x7d
	.sleb128 28
	.byte	0x2
	.byte	0x76
	.sleb128 0
	.uleb128 0x16
	.byte	0x2
	.byte	0x7d
	.sleb128 24
	.byte	0x2
	.byte	0x75
	.sleb128 0
	.uleb128 0x16
	.byte	0x2
	.byte	0x7d
	.sleb128 16
	.byte	0x3
	.byte	0xf5
	.uleb128 0x4
	.uleb128 0x29
	.uleb128 0x16
	.byte	0x2
	.byte	0x7d
	.sleb128 8
	.byte	0x2
	.byte	0x7b
	.sleb128 0
	.uleb128 0x16
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x3
	.byte	0xf5
	.uleb128 0x4
	.uleb128 0x29
	.byte	0
	.uleb128 0x17
	.4byte	.LVL5
	.4byte	0x5dd
	.4byte	0x465
	.uleb128 0x16
	.byte	0x1
	.byte	0x52
	.byte	0x5
	.byte	0x3
	.4byte	.LC4
	.uleb128 0x16
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x16
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x77
	.sleb128 0
	.byte	0
	.uleb128 0x17
	.4byte	.LVL6
	.4byte	0x5dd
	.4byte	0x487
	.uleb128 0x16
	.byte	0x1
	.byte	0x52
	.byte	0x5
	.byte	0x3
	.4byte	.LC5
	.uleb128 0x16
	.byte	0x1
	.byte	0x51
	.byte	0x1
	.byte	0x40
	.uleb128 0x16
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x77
	.sleb128 26
	.byte	0
	.uleb128 0x17
	.4byte	.LVL7
	.4byte	0x652
	.4byte	0x4d2
	.uleb128 0x16
	.byte	0x1
	.byte	0x53
	.byte	0x2
	.byte	0x77
	.sleb128 0
	.uleb128 0x16
	.byte	0x1
	.byte	0x52
	.byte	0x2
	.byte	0x75
	.sleb128 0
	.uleb128 0x16
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x75
	.sleb128 0
	.uleb128 0x16
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x7a
	.sleb128 0
	.uleb128 0x16
	.byte	0x2
	.byte	0x7d
	.sleb128 28
	.byte	0x2
	.byte	0x78
	.sleb128 0
	.uleb128 0x16
	.byte	0x2
	.byte	0x7d
	.sleb128 24
	.byte	0x2
	.byte	0x76
	.sleb128 0
	.uleb128 0x16
	.byte	0x2
	.byte	0x7d
	.sleb128 16
	.byte	0x3
	.byte	0xf5
	.uleb128 0x4
	.uleb128 0x29
	.uleb128 0x16
	.byte	0x2
	.byte	0x7d
	.sleb128 8
	.byte	0x2
	.byte	0x7b
	.sleb128 0
	.uleb128 0x16
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x3
	.byte	0xf5
	.uleb128 0x4
	.uleb128 0x29
	.byte	0
	.uleb128 0x15
	.4byte	.LVL11
	.4byte	0x5dd
	.uleb128 0x16
	.byte	0x1
	.byte	0x52
	.byte	0x5
	.byte	0x3
	.4byte	.LC7
	.uleb128 0x16
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x16
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x7a
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x18
	.4byte	.LASF52
	.byte	0x6
	.byte	0xa8
	.4byte	0x2af
	.byte	0x1
	.byte	0x1
	.uleb128 0x18
	.4byte	.LASF53
	.byte	0x6
	.byte	0xa9
	.4byte	0x2af
	.byte	0x1
	.byte	0x1
	.uleb128 0xb
	.4byte	0x42
	.4byte	0x51c
	.uleb128 0xc
	.4byte	0x9b
	.byte	0xf
	.byte	0
	.uleb128 0x19
	.ascii	"key\000"
	.byte	0x1
	.byte	0x29
	.4byte	0x52e
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	key
	.uleb128 0xd
	.4byte	0x50c
	.uleb128 0xb
	.4byte	0x42
	.4byte	0x543
	.uleb128 0xc
	.4byte	0x9b
	.byte	0x19
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF54
	.byte	0x1
	.byte	0x2a
	.4byte	0x533
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	adata
	.uleb128 0x1a
	.4byte	.LASF55
	.byte	0x1
	.byte	0x2b
	.4byte	0x50c
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	nonce
	.uleb128 0x1a
	.4byte	.LASF56
	.byte	0x1
	.byte	0x2c
	.4byte	0x533
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	plain
	.uleb128 0x1a
	.4byte	.LASF57
	.byte	0x1
	.byte	0x2d
	.4byte	0x533
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	cipher
	.uleb128 0x1a
	.4byte	.LASF58
	.byte	0x1
	.byte	0x31
	.4byte	0x533
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	decrypted
	.uleb128 0xb
	.4byte	0x29
	.4byte	0x5ad
	.uleb128 0xc
	.4byte	0x9b
	.byte	0x1
	.byte	0
	.uleb128 0x19
	.ascii	"tag\000"
	.byte	0x1
	.byte	0x32
	.4byte	0x59d
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	tag
	.uleb128 0x1b
	.byte	0x1
	.4byte	.LASF59
	.byte	0x2
	.byte	0x57
	.byte	0x1
	.4byte	0x65
	.byte	0x1
	.4byte	0x5dd
	.uleb128 0x1c
	.4byte	0x65
	.uleb128 0x1c
	.4byte	0x2db
	.uleb128 0x10
	.byte	0
	.uleb128 0x1d
	.byte	0x1
	.4byte	.LASF61
	.byte	0x8
	.byte	0x4
	.byte	0x1
	.byte	0x1
	.4byte	0x5fb
	.uleb128 0x1c
	.4byte	0x5fb
	.uleb128 0x1c
	.4byte	0x65
	.uleb128 0x1c
	.4byte	0xa4
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x42
	.uleb128 0x1b
	.byte	0x1
	.4byte	.LASF60
	.byte	0x7
	.byte	0x3
	.byte	0x1
	.4byte	0x65
	.byte	0x1
	.4byte	0x641
	.uleb128 0x1c
	.4byte	0x5fb
	.uleb128 0x1c
	.4byte	0x641
	.uleb128 0x1c
	.4byte	0x647
	.uleb128 0x1c
	.4byte	0x29
	.uleb128 0x1c
	.4byte	0x647
	.uleb128 0x1c
	.4byte	0x29
	.uleb128 0x1c
	.4byte	0x647
	.uleb128 0x1c
	.4byte	0x647
	.uleb128 0x1c
	.4byte	0x647
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x29
	.uleb128 0x6
	.byte	0x4
	.4byte	0x64d
	.uleb128 0xd
	.4byte	0x42
	.uleb128 0x1e
	.byte	0x1
	.4byte	.LASF62
	.byte	0x7
	.byte	0x4
	.byte	0x1
	.4byte	0x65
	.byte	0x1
	.uleb128 0x1c
	.4byte	0x5fb
	.uleb128 0x1c
	.4byte	0x641
	.uleb128 0x1c
	.4byte	0x5fb
	.uleb128 0x1c
	.4byte	0x647
	.uleb128 0x1c
	.4byte	0x29
	.uleb128 0x1c
	.4byte	0x647
	.uleb128 0x1c
	.4byte	0x29
	.uleb128 0x1c
	.4byte	0x647
	.uleb128 0x1c
	.4byte	0x647
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",%progbits
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
	.uleb128 0x6
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
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
	.uleb128 0xa
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
	.uleb128 0xa
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
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x34
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x5
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
	.uleb128 0x10
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
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
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
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
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0xa
	.uleb128 0x2111
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x17
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
	.uleb128 0x18
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
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x19
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
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x1a
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
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LLST0:
	.4byte	.LFB46
	.4byte	.LCFI0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI0
	.4byte	.LCFI1
	.2byte	0x2
	.byte	0x7d
	.sleb128 36
	.4byte	.LCFI1
	.4byte	.LFE46
	.2byte	0x3
	.byte	0x7d
	.sleb128 80
	.4byte	0
	.4byte	0
.LLST1:
	.4byte	.LVL8
	.4byte	.LVL9
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL9
	.4byte	.LVL10-1
	.2byte	0x1
	.byte	0x52
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB46
	.4byte	.LFE46-.LFB46
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LBB4
	.4byte	.LBE4
	.4byte	.LBB7
	.4byte	.LBE7
	.4byte	0
	.4byte	0
	.4byte	.LFB46
	.4byte	.LFE46
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF64:
	.ascii	"printf\000"
.LASF10:
	.ascii	"__off_t\000"
.LASF16:
	.ascii	"_IO_read_ptr\000"
.LASF28:
	.ascii	"_chain\000"
.LASF8:
	.ascii	"size_t\000"
.LASF34:
	.ascii	"_shortbuf\000"
.LASF22:
	.ascii	"_IO_buf_base\000"
.LASF0:
	.ascii	"long long unsigned int\000"
.LASF7:
	.ascii	"long long int\000"
.LASF5:
	.ascii	"signed char\000"
.LASF29:
	.ascii	"_fileno\000"
.LASF17:
	.ascii	"_IO_read_end\000"
.LASF11:
	.ascii	"long int\000"
.LASF15:
	.ascii	"_flags\000"
.LASF23:
	.ascii	"_IO_buf_end\000"
.LASF32:
	.ascii	"_cur_column\000"
.LASF9:
	.ascii	"__quad_t\000"
.LASF59:
	.ascii	"__printf_chk\000"
.LASF31:
	.ascii	"_old_offset\000"
.LASF36:
	.ascii	"_offset\000"
.LASF67:
	.ascii	"succes\000"
.LASF45:
	.ascii	"_IO_marker\000"
.LASF52:
	.ascii	"stdin\000"
.LASF54:
	.ascii	"adata\000"
.LASF1:
	.ascii	"unsigned int\000"
.LASF4:
	.ascii	"long unsigned int\000"
.LASF20:
	.ascii	"_IO_write_ptr\000"
.LASF47:
	.ascii	"_sbuf\000"
.LASF3:
	.ascii	"short unsigned int\000"
.LASF61:
	.ascii	"printchar\000"
.LASF24:
	.ascii	"_IO_save_base\000"
.LASF50:
	.ascii	"main.c\000"
.LASF35:
	.ascii	"_lock\000"
.LASF60:
	.ascii	"crypto_aead_encrypt\000"
.LASF30:
	.ascii	"_flags2\000"
.LASF42:
	.ascii	"_mode\000"
.LASF56:
	.ascii	"plain\000"
.LASF53:
	.ascii	"stdout\000"
.LASF13:
	.ascii	"sizetype\000"
.LASF21:
	.ascii	"_IO_write_end\000"
.LASF63:
	.ascii	"_IO_lock_t\000"
.LASF44:
	.ascii	"_IO_FILE\000"
.LASF49:
	.ascii	"GNU C 4.7.4\000"
.LASF48:
	.ascii	"_pos\000"
.LASF27:
	.ascii	"_markers\000"
.LASF2:
	.ascii	"unsigned char\000"
.LASF6:
	.ascii	"short int\000"
.LASF33:
	.ascii	"_vtable_offset\000"
.LASF55:
	.ascii	"nonce\000"
.LASF14:
	.ascii	"char\000"
.LASF46:
	.ascii	"_next\000"
.LASF12:
	.ascii	"__off64_t\000"
.LASF18:
	.ascii	"_IO_read_base\000"
.LASF26:
	.ascii	"_IO_save_end\000"
.LASF65:
	.ascii	"__fmt\000"
.LASF37:
	.ascii	"__pad1\000"
.LASF38:
	.ascii	"__pad2\000"
.LASF39:
	.ascii	"__pad3\000"
.LASF40:
	.ascii	"__pad4\000"
.LASF41:
	.ascii	"__pad5\000"
.LASF43:
	.ascii	"_unused2\000"
.LASF25:
	.ascii	"_IO_backup_base\000"
.LASF57:
	.ascii	"cipher\000"
.LASF62:
	.ascii	"crypto_aead_decrypt\000"
.LASF51:
	.ascii	"/home/linaro/Documents/Thesis/aes-copa\000"
.LASF66:
	.ascii	"main\000"
.LASF19:
	.ascii	"_IO_write_base\000"
.LASF58:
	.ascii	"decrypted\000"
	.ident	"GCC: (Ubuntu/Linaro 4.7.4-2ubuntu1) 4.7.4"
	.section	.note.GNU-stack,"",%progbits
