	.arch armv7-a
	.eabi_attribute 27, 3
	.eabi_attribute 28, 1
	.fpu neon-vfpv4
	.eabi_attribute 23, 1
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"main.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.type	main, %function
main:
.LFB46:
	.file 1 "main.c"
	.loc 1 50 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 368
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
	.cfi_def_cfa_offset 8
	.cfi_offset 4, -8
	.cfi_offset 14, -4
	movw	r4, #:lower16:__stack_chk_guard
	movt	r4, #:upper16:__stack_chk_guard
	sub	sp, sp, #368
	.cfi_def_cfa_offset 376
	.loc 1 50 0
	ldr	r3, [r4]
	.loc 1 53 0
	movw	r0, #:lower16:.LANCHOR0
	add	r2, sp, #4
	mov	r1, #128
	movt	r0, #:upper16:.LANCHOR0
	.loc 1 50 0
	str	r3, [sp, #364]
.LVL0:
	.loc 1 53 0
	bl	AES_set_encrypt_key
.LVL1:
	.loc 1 56 0
	movw	r0, #:lower16:.LANCHOR0
	add	r2, sp, #184
.LVL2:
	mov	r1, #128
	movt	r0, #:upper16:.LANCHOR0
	bl	AES_set_decrypt_key
.LVL3:
	.loc 1 57 0
	movw	r2, #:lower16:.LC0
	movw	r0, #:lower16:.LANCHOR0
	movt	r2, #:upper16:.LC0
	movt	r0, #:upper16:.LANCHOR0
	mov	r1, #16
	bl	printchar
.LVL4:
	.loc 1 58 0
	movw	r2, #:lower16:.LC1
	movw	r0, #:lower16:.LANCHOR1
	movt	r2, #:upper16:.LC1
	movt	r0, #:upper16:.LANCHOR1
	mov	r1, #16
	bl	printchar
.LVL5:
	.loc 1 59 0
	movw	r1, #:lower16:cipher
	movw	r0, #:lower16:.LANCHOR1
	add	r2, sp, #4
.LVL6:
	movt	r1, #:upper16:cipher
	movt	r0, #:upper16:.LANCHOR1
	bl	AES_encrypt
.LVL7:
	.loc 1 60 0
	movw	r1, #:lower16:decrypted
	movw	r0, #:lower16:cipher
	add	r2, sp, #184
.LVL8:
	movt	r1, #:upper16:decrypted
	movt	r0, #:upper16:cipher
	bl	AES_decrypt
.LVL9:
	.loc 1 61 0
	movw	r2, #:lower16:.LC2
	movw	r0, #:lower16:cipher
	movt	r2, #:upper16:.LC2
	movt	r0, #:upper16:cipher
	mov	r1, #16
	bl	printchar
.LVL10:
	.loc 1 62 0
	movw	r2, #:lower16:.LC3
	movw	r0, #:lower16:decrypted
	movt	r2, #:upper16:.LC3
	movt	r0, #:upper16:decrypted
	mov	r1, #16
	bl	printchar
.LVL11:
	.loc 1 64 0
	ldr	r2, [sp, #364]
	ldr	r3, [r4]
	mov	r0, #0
	cmp	r2, r3
	bne	.L5
	add	sp, sp, #368
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	@ sp needed
	ldmfd	sp!, {r4, pc}
.L5:
	.cfi_restore_state
	bl	__stack_chk_fail
.LVL12:
	.cfi_endproc
.LFE46:
	.size	main, .-main
	.comm	decrypted,16,4
	.comm	cipher,16,4
	.global	plain
	.global	key
	.section	.rodata
	.align	3
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
	.align	3
.LANCHOR1 = . + 0
	.type	plain, %object
	.size	plain, 16
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
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"key\000"
.LC1:
	.ascii	"plain\000"
	.space	2
.LC2:
	.ascii	"cipher\000"
	.space	1
.LC3:
	.ascii	"decrypt\000"
	.text
.Letext0:
	.file 2 "/usr/lib/gcc/arm-linux-gnueabihf/4.9/include/stddef.h"
	.file 3 "/usr/include/arm-linux-gnueabihf/bits/types.h"
	.file 4 "/usr/include/libio.h"
	.file 5 "aes.h"
	.file 6 "/usr/include/stdio.h"
	.file 7 "print.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0x587
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF67
	.byte	0x1
	.4byte	.LASF68
	.4byte	.LASF69
	.4byte	.Ldebug_ranges0+0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.4byte	.LASF8
	.byte	0x2
	.byte	0xd4
	.4byte	0x30
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF0
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF1
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.4byte	.LASF4
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.4byte	.LASF5
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x2
	.4byte	.LASF9
	.byte	0x3
	.byte	0x37
	.4byte	0x61
	.uleb128 0x2
	.4byte	.LASF10
	.byte	0x3
	.byte	0x83
	.4byte	0x85
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.4byte	.LASF11
	.uleb128 0x2
	.4byte	.LASF12
	.byte	0x3
	.byte	0x84
	.4byte	0x6f
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF13
	.uleb128 0x5
	.byte	0x4
	.uleb128 0x6
	.byte	0x4
	.4byte	0xa6
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF14
	.uleb128 0x7
	.4byte	.LASF44
	.byte	0x98
	.byte	0x4
	.byte	0xf5
	.4byte	0x22d
	.uleb128 0x8
	.4byte	.LASF15
	.byte	0x4
	.byte	0xf6
	.4byte	0x5a
	.byte	0
	.uleb128 0x8
	.4byte	.LASF16
	.byte	0x4
	.byte	0xfb
	.4byte	0xa0
	.byte	0x4
	.uleb128 0x8
	.4byte	.LASF17
	.byte	0x4
	.byte	0xfc
	.4byte	0xa0
	.byte	0x8
	.uleb128 0x8
	.4byte	.LASF18
	.byte	0x4
	.byte	0xfd
	.4byte	0xa0
	.byte	0xc
	.uleb128 0x8
	.4byte	.LASF19
	.byte	0x4
	.byte	0xfe
	.4byte	0xa0
	.byte	0x10
	.uleb128 0x8
	.4byte	.LASF20
	.byte	0x4
	.byte	0xff
	.4byte	0xa0
	.byte	0x14
	.uleb128 0x9
	.4byte	.LASF21
	.byte	0x4
	.2byte	0x100
	.4byte	0xa0
	.byte	0x18
	.uleb128 0x9
	.4byte	.LASF22
	.byte	0x4
	.2byte	0x101
	.4byte	0xa0
	.byte	0x1c
	.uleb128 0x9
	.4byte	.LASF23
	.byte	0x4
	.2byte	0x102
	.4byte	0xa0
	.byte	0x20
	.uleb128 0x9
	.4byte	.LASF24
	.byte	0x4
	.2byte	0x104
	.4byte	0xa0
	.byte	0x24
	.uleb128 0x9
	.4byte	.LASF25
	.byte	0x4
	.2byte	0x105
	.4byte	0xa0
	.byte	0x28
	.uleb128 0x9
	.4byte	.LASF26
	.byte	0x4
	.2byte	0x106
	.4byte	0xa0
	.byte	0x2c
	.uleb128 0x9
	.4byte	.LASF27
	.byte	0x4
	.2byte	0x108
	.4byte	0x265
	.byte	0x30
	.uleb128 0x9
	.4byte	.LASF28
	.byte	0x4
	.2byte	0x10a
	.4byte	0x26b
	.byte	0x34
	.uleb128 0x9
	.4byte	.LASF29
	.byte	0x4
	.2byte	0x10c
	.4byte	0x5a
	.byte	0x38
	.uleb128 0x9
	.4byte	.LASF30
	.byte	0x4
	.2byte	0x110
	.4byte	0x5a
	.byte	0x3c
	.uleb128 0x9
	.4byte	.LASF31
	.byte	0x4
	.2byte	0x112
	.4byte	0x7a
	.byte	0x40
	.uleb128 0x9
	.4byte	.LASF32
	.byte	0x4
	.2byte	0x116
	.4byte	0x3e
	.byte	0x44
	.uleb128 0x9
	.4byte	.LASF33
	.byte	0x4
	.2byte	0x117
	.4byte	0x4c
	.byte	0x46
	.uleb128 0x9
	.4byte	.LASF34
	.byte	0x4
	.2byte	0x118
	.4byte	0x271
	.byte	0x47
	.uleb128 0x9
	.4byte	.LASF35
	.byte	0x4
	.2byte	0x11c
	.4byte	0x281
	.byte	0x48
	.uleb128 0x9
	.4byte	.LASF36
	.byte	0x4
	.2byte	0x125
	.4byte	0x8c
	.byte	0x50
	.uleb128 0x9
	.4byte	.LASF37
	.byte	0x4
	.2byte	0x12e
	.4byte	0x9e
	.byte	0x58
	.uleb128 0x9
	.4byte	.LASF38
	.byte	0x4
	.2byte	0x12f
	.4byte	0x9e
	.byte	0x5c
	.uleb128 0x9
	.4byte	.LASF39
	.byte	0x4
	.2byte	0x130
	.4byte	0x9e
	.byte	0x60
	.uleb128 0x9
	.4byte	.LASF40
	.byte	0x4
	.2byte	0x131
	.4byte	0x9e
	.byte	0x64
	.uleb128 0x9
	.4byte	.LASF41
	.byte	0x4
	.2byte	0x132
	.4byte	0x25
	.byte	0x68
	.uleb128 0x9
	.4byte	.LASF42
	.byte	0x4
	.2byte	0x134
	.4byte	0x5a
	.byte	0x6c
	.uleb128 0x9
	.4byte	.LASF43
	.byte	0x4
	.2byte	0x136
	.4byte	0x287
	.byte	0x70
	.byte	0
	.uleb128 0xa
	.4byte	.LASF70
	.byte	0x4
	.byte	0x9a
	.uleb128 0x7
	.4byte	.LASF45
	.byte	0xc
	.byte	0x4
	.byte	0xa0
	.4byte	0x265
	.uleb128 0x8
	.4byte	.LASF46
	.byte	0x4
	.byte	0xa1
	.4byte	0x265
	.byte	0
	.uleb128 0x8
	.4byte	.LASF47
	.byte	0x4
	.byte	0xa2
	.4byte	0x26b
	.byte	0x4
	.uleb128 0x8
	.4byte	.LASF48
	.byte	0x4
	.byte	0xa6
	.4byte	0x5a
	.byte	0x8
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x234
	.uleb128 0x6
	.byte	0x4
	.4byte	0xad
	.uleb128 0xb
	.4byte	0xa6
	.4byte	0x281
	.uleb128 0xc
	.4byte	0x97
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x22d
	.uleb128 0xb
	.4byte	0xa6
	.4byte	0x297
	.uleb128 0xc
	.4byte	0x97
	.byte	0x27
	.byte	0
	.uleb128 0xd
	.4byte	0x5a
	.uleb128 0x7
	.4byte	.LASF49
	.byte	0xb4
	.byte	0x5
	.byte	0xb
	.4byte	0x2c1
	.uleb128 0x8
	.4byte	.LASF50
	.byte	0x5
	.byte	0xc
	.4byte	0x2c1
	.byte	0
	.uleb128 0x8
	.4byte	.LASF51
	.byte	0x5
	.byte	0xd
	.4byte	0x5a
	.byte	0xb0
	.byte	0
	.uleb128 0xb
	.4byte	0x30
	.4byte	0x2d1
	.uleb128 0xc
	.4byte	0x97
	.byte	0x2b
	.byte	0
	.uleb128 0x2
	.4byte	.LASF52
	.byte	0x5
	.byte	0x10
	.4byte	0x29c
	.uleb128 0xe
	.4byte	.LASF71
	.byte	0x1
	.byte	0x32
	.4byte	0x5a
	.4byte	.LFB46
	.4byte	.LFE46-.LFB46
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x465
	.uleb128 0xf
	.4byte	.LASF53
	.byte	0x1
	.byte	0x33
	.4byte	0x2d1
	.uleb128 0x3
	.byte	0x91
	.sleb128 -372
	.uleb128 0x10
	.4byte	.LASF54
	.byte	0x1
	.byte	0x34
	.4byte	0x465
	.4byte	.LLST0
	.uleb128 0xf
	.4byte	.LASF55
	.byte	0x1
	.byte	0x36
	.4byte	0x2d1
	.uleb128 0x3
	.byte	0x91
	.sleb128 -192
	.uleb128 0x10
	.4byte	.LASF56
	.byte	0x1
	.byte	0x37
	.4byte	0x465
	.4byte	.LLST1
	.uleb128 0x11
	.4byte	.LVL1
	.4byte	0x4da
	.4byte	0x355
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x5
	.byte	0x3
	.4byte	.LANCHOR0
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x51
	.uleb128 0x2
	.byte	0x8
	.byte	0x80
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x3
	.byte	0x91
	.sleb128 -380
	.byte	0
	.uleb128 0x11
	.4byte	.LVL3
	.4byte	0x504
	.4byte	0x379
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x5
	.byte	0x3
	.4byte	.LANCHOR0
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x51
	.uleb128 0x2
	.byte	0x8
	.byte	0x80
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x3
	.byte	0x91
	.sleb128 -200
	.byte	0
	.uleb128 0x11
	.4byte	.LVL4
	.4byte	0x523
	.4byte	0x39e
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x5
	.byte	0x3
	.4byte	.LANCHOR0
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x51
	.uleb128 0x1
	.byte	0x40
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x5
	.byte	0x3
	.4byte	.LC0
	.byte	0
	.uleb128 0x11
	.4byte	.LVL5
	.4byte	0x523
	.4byte	0x3c3
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x5
	.byte	0x3
	.4byte	.LANCHOR1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x51
	.uleb128 0x1
	.byte	0x40
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x5
	.byte	0x3
	.4byte	.LC1
	.byte	0
	.uleb128 0x11
	.4byte	.LVL7
	.4byte	0x544
	.4byte	0x3ea
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x5
	.byte	0x3
	.4byte	.LANCHOR1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x51
	.uleb128 0x5
	.byte	0x3
	.4byte	cipher
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x3
	.byte	0x91
	.sleb128 -380
	.byte	0
	.uleb128 0x11
	.4byte	.LVL9
	.4byte	0x56a
	.4byte	0x411
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x5
	.byte	0x3
	.4byte	cipher
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x51
	.uleb128 0x5
	.byte	0x3
	.4byte	decrypted
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x3
	.byte	0x91
	.sleb128 -200
	.byte	0
	.uleb128 0x11
	.4byte	.LVL10
	.4byte	0x523
	.4byte	0x436
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x5
	.byte	0x3
	.4byte	cipher
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x51
	.uleb128 0x1
	.byte	0x40
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x5
	.byte	0x3
	.4byte	.LC2
	.byte	0
	.uleb128 0x11
	.4byte	.LVL11
	.4byte	0x523
	.4byte	0x45b
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x50
	.uleb128 0x5
	.byte	0x3
	.4byte	decrypted
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x51
	.uleb128 0x1
	.byte	0x40
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x5
	.byte	0x3
	.4byte	.LC3
	.byte	0
	.uleb128 0x13
	.4byte	.LVL12
	.4byte	0x585
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x2d1
	.uleb128 0x14
	.4byte	.LASF57
	.byte	0x6
	.byte	0xa8
	.4byte	0x26b
	.uleb128 0x14
	.4byte	.LASF58
	.byte	0x6
	.byte	0xa9
	.4byte	0x26b
	.uleb128 0xb
	.4byte	0x37
	.4byte	0x491
	.uleb128 0xc
	.4byte	0x97
	.byte	0xf
	.byte	0
	.uleb128 0x15
	.ascii	"key\000"
	.byte	0x1
	.byte	0x1f
	.4byte	0x4a2
	.uleb128 0x5
	.byte	0x3
	.4byte	key
	.uleb128 0xd
	.4byte	0x481
	.uleb128 0x16
	.4byte	.LASF59
	.byte	0x1
	.byte	0x20
	.4byte	0x481
	.uleb128 0x5
	.byte	0x3
	.4byte	plain
	.uleb128 0x16
	.4byte	.LASF60
	.byte	0x1
	.byte	0x21
	.4byte	0x481
	.uleb128 0x5
	.byte	0x3
	.4byte	cipher
	.uleb128 0x16
	.4byte	.LASF61
	.byte	0x1
	.byte	0x2f
	.4byte	0x481
	.uleb128 0x5
	.byte	0x3
	.4byte	decrypted
	.uleb128 0x17
	.4byte	.LASF62
	.byte	0x5
	.byte	0x12
	.4byte	0x5a
	.4byte	0x4f9
	.uleb128 0x18
	.4byte	0x4f9
	.uleb128 0x18
	.4byte	0x297
	.uleb128 0x18
	.4byte	0x465
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x4ff
	.uleb128 0xd
	.4byte	0x37
	.uleb128 0x17
	.4byte	.LASF63
	.byte	0x5
	.byte	0x15
	.4byte	0x5a
	.4byte	0x523
	.uleb128 0x18
	.4byte	0x4f9
	.uleb128 0x18
	.4byte	0x297
	.uleb128 0x18
	.4byte	0x465
	.byte	0
	.uleb128 0x19
	.4byte	.LASF64
	.byte	0x7
	.byte	0x4
	.4byte	0x53e
	.uleb128 0x18
	.4byte	0x53e
	.uleb128 0x18
	.4byte	0x5a
	.uleb128 0x18
	.4byte	0xa0
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x37
	.uleb128 0x19
	.4byte	.LASF65
	.byte	0x5
	.byte	0x1b
	.4byte	0x55f
	.uleb128 0x18
	.4byte	0x4f9
	.uleb128 0x18
	.4byte	0x53e
	.uleb128 0x18
	.4byte	0x55f
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x565
	.uleb128 0xd
	.4byte	0x2d1
	.uleb128 0x19
	.4byte	.LASF66
	.byte	0x5
	.byte	0x18
	.4byte	0x585
	.uleb128 0x18
	.4byte	0x4f9
	.uleb128 0x18
	.4byte	0x53e
	.uleb128 0x18
	.4byte	0x55f
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF72
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
	.uleb128 0x17
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
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
	.uleb128 0x3
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
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
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
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x10
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
	.uleb128 0x11
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
	.uleb128 0x12
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x2111
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
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
	.uleb128 0x15
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
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x16
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
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x17
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
	.uleb128 0x18
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LLST0:
	.4byte	.LVL0
	.4byte	.LVL1-1
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL1-1
	.4byte	.LVL6
	.2byte	0x4
	.byte	0x91
	.sleb128 -380
	.byte	0x9f
	.4byte	.LVL6
	.4byte	.LVL7-1
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL7-1
	.4byte	.LFE46
	.2byte	0x4
	.byte	0x91
	.sleb128 -380
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST1:
	.4byte	.LVL1
	.4byte	.LVL2
	.2byte	0x4
	.byte	0x91
	.sleb128 -200
	.byte	0x9f
	.4byte	.LVL2
	.4byte	.LVL3-1
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL3-1
	.4byte	.LVL8
	.2byte	0x4
	.byte	0x91
	.sleb128 -200
	.byte	0x9f
	.4byte	.LVL8
	.4byte	.LVL9-1
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL9-1
	.4byte	.LFE46
	.2byte	0x4
	.byte	0x91
	.sleb128 -200
	.byte	0x9f
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
	.4byte	.LFB46
	.4byte	.LFE46
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
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
.LASF7:
	.ascii	"long long unsigned int\000"
.LASF67:
	.ascii	"GNU C 4.9.1 -marm -mfpu=neon-vfpv4 -march=armv7-a -"
	.ascii	"mfloat-abi=hard -mtls-dialect=gnu -g -Ofast -fomit-"
	.ascii	"frame-pointer -fstack-protector-strong\000"
.LASF63:
	.ascii	"AES_set_decrypt_key\000"
.LASF6:
	.ascii	"long long int\000"
.LASF4:
	.ascii	"signed char\000"
.LASF29:
	.ascii	"_fileno\000"
.LASF17:
	.ascii	"_IO_read_end\000"
.LASF11:
	.ascii	"long int\000"
.LASF15:
	.ascii	"_flags\000"
.LASF66:
	.ascii	"AES_decrypt\000"
.LASF23:
	.ascii	"_IO_buf_end\000"
.LASF32:
	.ascii	"_cur_column\000"
.LASF53:
	.ascii	"expkeyp\000"
.LASF9:
	.ascii	"__quad_t\000"
.LASF31:
	.ascii	"_old_offset\000"
.LASF36:
	.ascii	"_offset\000"
.LASF51:
	.ascii	"rounds\000"
.LASF49:
	.ascii	"aes_key_struct\000"
.LASF62:
	.ascii	"AES_set_encrypt_key\000"
.LASF45:
	.ascii	"_IO_marker\000"
.LASF57:
	.ascii	"stdin\000"
.LASF0:
	.ascii	"unsigned int\000"
.LASF3:
	.ascii	"long unsigned int\000"
.LASF54:
	.ascii	"expkey\000"
.LASF20:
	.ascii	"_IO_write_ptr\000"
.LASF47:
	.ascii	"_sbuf\000"
.LASF2:
	.ascii	"short unsigned int\000"
.LASF64:
	.ascii	"printchar\000"
.LASF24:
	.ascii	"_IO_save_base\000"
.LASF68:
	.ascii	"main.c\000"
.LASF65:
	.ascii	"AES_encrypt\000"
.LASF35:
	.ascii	"_lock\000"
.LASF30:
	.ascii	"_flags2\000"
.LASF42:
	.ascii	"_mode\000"
.LASF50:
	.ascii	"rd_key\000"
.LASF59:
	.ascii	"plain\000"
.LASF58:
	.ascii	"stdout\000"
.LASF13:
	.ascii	"sizetype\000"
.LASF21:
	.ascii	"_IO_write_end\000"
.LASF70:
	.ascii	"_IO_lock_t\000"
.LASF44:
	.ascii	"_IO_FILE\000"
.LASF48:
	.ascii	"_pos\000"
.LASF27:
	.ascii	"_markers\000"
.LASF1:
	.ascii	"unsigned char\000"
.LASF5:
	.ascii	"short int\000"
.LASF33:
	.ascii	"_vtable_offset\000"
.LASF72:
	.ascii	"__stack_chk_fail\000"
.LASF14:
	.ascii	"char\000"
.LASF46:
	.ascii	"_next\000"
.LASF56:
	.ascii	"expkeyd\000"
.LASF12:
	.ascii	"__off64_t\000"
.LASF18:
	.ascii	"_IO_read_base\000"
.LASF26:
	.ascii	"_IO_save_end\000"
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
.LASF69:
	.ascii	"/home/linaro/Documents/Thesis/AES\000"
.LASF55:
	.ascii	"expkeydp\000"
.LASF25:
	.ascii	"_IO_backup_base\000"
.LASF60:
	.ascii	"cipher\000"
.LASF52:
	.ascii	"AES_KEY\000"
.LASF71:
	.ascii	"main\000"
.LASF19:
	.ascii	"_IO_write_base\000"
.LASF61:
	.ascii	"decrypted\000"
	.ident	"GCC: (Ubuntu/Linaro 4.9.1-16ubuntu6) 4.9.1"
	.section	.note.GNU-stack,"",%progbits
