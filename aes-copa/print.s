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
	.file	"print.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.align	2
	.global	printchar
	.thumb
	.thumb_func
	.type	printchar, %function
printchar:
.LFB24:
	.file 1 "print.c"
	.loc 1 4 0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
.LVL0:
	push	{r3, r4, r5, r6, r7, lr}
.LCFI0:
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	.cfi_offset 4, -20
	.cfi_offset 5, -16
	.cfi_offset 6, -12
	.cfi_offset 7, -8
	.cfi_offset 14, -4
	.loc 1 4 0
	mov	r6, r1
	.loc 1 8 0
	add	r5, r6, r6, lsr #31
	.loc 1 4 0
	mov	r7, r0
.LBB10:
.LBB11:
	.file 2 "/usr/include/arm-linux-gnueabihf/bits/stdio2.h"
	.loc 2 104 0
	ldr	r1, .L10
.LVL1:
	movs	r0, #1
.LVL2:
.LBE11:
.LBE10:
	.loc 1 8 0
	asrs	r5, r5, #1
.LBB13:
.LBB12:
	.loc 2 104 0
	bl	__printf_chk
.LVL3:
.LBE12:
.LBE13:
	.loc 1 8 0
	cmp	r5, #0
	.loc 1 4 0
	itt	gt
	addgt	r5, r7, r5, lsl #1
	movgt	r4, r7
	.loc 1 8 0
	ble	.L6
.LVL4:
.L5:
.LBB14:
.LBB15:
	.loc 2 104 0 discriminator 2
	ldrb	r2, [r4, #0]	@ zero_extendqisi2
	movs	r0, #1
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	adds	r4, r4, #2
	ldr	r1, .L10+4
	bl	__printf_chk
.LVL5:
.LBE15:
.LBE14:
	.loc 1 8 0 discriminator 2
	cmp	r4, r5
	bne	.L5
.LVL6:
.L6:
	.loc 1 13 0
	lsrs	r3, r6, #31
	adds	r0, r6, r3
	and	r0, r0, #1
	subs	r0, r0, r3
	cmp	r0, #1
	beq	.L9
.LVL7:
.L4:
.LBB16:
.LBB17:
	.loc 2 104 0
	movs	r0, #10
.LBE17:
.LBE16:
	.loc 1 17 0
	pop	{r3, r4, r5, r6, r7, lr}
.LBB19:
.LBB18:
	.loc 2 104 0
	b	putchar
.LVL8:
.L9:
.LBE18:
.LBE19:
	.loc 1 14 0
	adds	r6, r7, r6
.LVL9:
.LBB20:
.LBB21:
	.loc 2 104 0
	ldr	r1, .L10+8
	ldrb	r2, [r6, #-1]	@ zero_extendqisi2
	bl	__printf_chk
.LVL10:
	b	.L4
.L11:
	.align	2
.L10:
	.word	.LC0
	.word	.LC1
	.word	.LC2
.LBE21:
.LBE20:
	.cfi_endproc
.LFE24:
	.size	printchar, .-printchar
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"%s:\012\000"
	.space	3
.LC1:
	.ascii	"%02x%02x \000"
	.space	2
.LC2:
	.ascii	"%02x \000"
	.text
.Letext0:
	.file 3 "/usr/lib/gcc/arm-linux-gnueabihf/4.7/include/stddef.h"
	.file 4 "/usr/include/arm-linux-gnueabihf/bits/types.h"
	.file 5 "/usr/include/libio.h"
	.file 6 "/usr/include/stdio.h"
	.file 7 "<built-in>"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0x476
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF56
	.byte	0x1
	.4byte	.LASF57
	.4byte	.LASF58
	.4byte	.Ltext0
	.4byte	.Letext0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.4byte	.LASF8
	.byte	0x3
	.byte	0xd5
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
	.byte	0x4
	.byte	0x37
	.4byte	0x61
	.uleb128 0x2
	.4byte	.LASF10
	.byte	0x4
	.byte	0x83
	.4byte	0x85
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.4byte	.LASF11
	.uleb128 0x2
	.4byte	.LASF12
	.byte	0x4
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
	.byte	0x5
	.byte	0xf5
	.4byte	0x267
	.uleb128 0x8
	.4byte	.LASF15
	.byte	0x5
	.byte	0xf6
	.4byte	0x5a
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.4byte	.LASF16
	.byte	0x5
	.byte	0xfb
	.4byte	0xa0
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x8
	.4byte	.LASF17
	.byte	0x5
	.byte	0xfc
	.4byte	0xa0
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x8
	.4byte	.LASF18
	.byte	0x5
	.byte	0xfd
	.4byte	0xa0
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x8
	.4byte	.LASF19
	.byte	0x5
	.byte	0xfe
	.4byte	0xa0
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0x8
	.4byte	.LASF20
	.byte	0x5
	.byte	0xff
	.4byte	0xa0
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0x9
	.4byte	.LASF21
	.byte	0x5
	.2byte	0x100
	.4byte	0xa0
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0x9
	.4byte	.LASF22
	.byte	0x5
	.2byte	0x101
	.4byte	0xa0
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0x9
	.4byte	.LASF23
	.byte	0x5
	.2byte	0x102
	.4byte	0xa0
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0x9
	.4byte	.LASF24
	.byte	0x5
	.2byte	0x104
	.4byte	0xa0
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0x9
	.4byte	.LASF25
	.byte	0x5
	.2byte	0x105
	.4byte	0xa0
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0x9
	.4byte	.LASF26
	.byte	0x5
	.2byte	0x106
	.4byte	0xa0
	.byte	0x2
	.byte	0x23
	.uleb128 0x2c
	.uleb128 0x9
	.4byte	.LASF27
	.byte	0x5
	.2byte	0x108
	.4byte	0x2a5
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0x9
	.4byte	.LASF28
	.byte	0x5
	.2byte	0x10a
	.4byte	0x2ab
	.byte	0x2
	.byte	0x23
	.uleb128 0x34
	.uleb128 0x9
	.4byte	.LASF29
	.byte	0x5
	.2byte	0x10c
	.4byte	0x5a
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0x9
	.4byte	.LASF30
	.byte	0x5
	.2byte	0x110
	.4byte	0x5a
	.byte	0x2
	.byte	0x23
	.uleb128 0x3c
	.uleb128 0x9
	.4byte	.LASF31
	.byte	0x5
	.2byte	0x112
	.4byte	0x7a
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.uleb128 0x9
	.4byte	.LASF32
	.byte	0x5
	.2byte	0x116
	.4byte	0x3e
	.byte	0x2
	.byte	0x23
	.uleb128 0x44
	.uleb128 0x9
	.4byte	.LASF33
	.byte	0x5
	.2byte	0x117
	.4byte	0x4c
	.byte	0x2
	.byte	0x23
	.uleb128 0x46
	.uleb128 0x9
	.4byte	.LASF34
	.byte	0x5
	.2byte	0x118
	.4byte	0x2b1
	.byte	0x2
	.byte	0x23
	.uleb128 0x47
	.uleb128 0x9
	.4byte	.LASF35
	.byte	0x5
	.2byte	0x11c
	.4byte	0x2c1
	.byte	0x2
	.byte	0x23
	.uleb128 0x48
	.uleb128 0x9
	.4byte	.LASF36
	.byte	0x5
	.2byte	0x125
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x50
	.uleb128 0x9
	.4byte	.LASF37
	.byte	0x5
	.2byte	0x12e
	.4byte	0x9e
	.byte	0x2
	.byte	0x23
	.uleb128 0x58
	.uleb128 0x9
	.4byte	.LASF38
	.byte	0x5
	.2byte	0x12f
	.4byte	0x9e
	.byte	0x2
	.byte	0x23
	.uleb128 0x5c
	.uleb128 0x9
	.4byte	.LASF39
	.byte	0x5
	.2byte	0x130
	.4byte	0x9e
	.byte	0x2
	.byte	0x23
	.uleb128 0x60
	.uleb128 0x9
	.4byte	.LASF40
	.byte	0x5
	.2byte	0x131
	.4byte	0x9e
	.byte	0x2
	.byte	0x23
	.uleb128 0x64
	.uleb128 0x9
	.4byte	.LASF41
	.byte	0x5
	.2byte	0x132
	.4byte	0x25
	.byte	0x2
	.byte	0x23
	.uleb128 0x68
	.uleb128 0x9
	.4byte	.LASF42
	.byte	0x5
	.2byte	0x134
	.4byte	0x5a
	.byte	0x2
	.byte	0x23
	.uleb128 0x6c
	.uleb128 0x9
	.4byte	.LASF43
	.byte	0x5
	.2byte	0x136
	.4byte	0x2c7
	.byte	0x2
	.byte	0x23
	.uleb128 0x70
	.byte	0
	.uleb128 0xa
	.4byte	.LASF59
	.byte	0x5
	.byte	0x9a
	.uleb128 0x7
	.4byte	.LASF45
	.byte	0xc
	.byte	0x5
	.byte	0xa0
	.4byte	0x2a5
	.uleb128 0x8
	.4byte	.LASF46
	.byte	0x5
	.byte	0xa1
	.4byte	0x2a5
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.4byte	.LASF47
	.byte	0x5
	.byte	0xa2
	.4byte	0x2ab
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x8
	.4byte	.LASF48
	.byte	0x5
	.byte	0xa6
	.4byte	0x5a
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x26e
	.uleb128 0x6
	.byte	0x4
	.4byte	0xad
	.uleb128 0xb
	.4byte	0xa6
	.4byte	0x2c1
	.uleb128 0xc
	.4byte	0x97
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x267
	.uleb128 0xb
	.4byte	0xa6
	.4byte	0x2d7
	.uleb128 0xc
	.4byte	0x97
	.byte	0x27
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x2dd
	.uleb128 0xd
	.4byte	0xa6
	.uleb128 0xe
	.byte	0x1
	.4byte	.LASF60
	.byte	0x2
	.byte	0x66
	.byte	0x1
	.4byte	0x5a
	.byte	0x3
	.byte	0x1
	.4byte	0x302
	.uleb128 0xf
	.4byte	.LASF61
	.byte	0x2
	.byte	0x66
	.4byte	0x2d7
	.uleb128 0x10
	.byte	0
	.uleb128 0x11
	.byte	0x1
	.4byte	.LASF62
	.byte	0x1
	.byte	0x4
	.byte	0x1
	.4byte	.LFB24
	.4byte	.LFE24
	.4byte	.LLST0
	.byte	0x1
	.4byte	0x423
	.uleb128 0x12
	.4byte	.LASF49
	.byte	0x1
	.byte	0x4
	.4byte	0x423
	.4byte	.LLST1
	.uleb128 0x12
	.4byte	.LASF50
	.byte	0x1
	.byte	0x4
	.4byte	0x5a
	.4byte	.LLST2
	.uleb128 0x12
	.4byte	.LASF51
	.byte	0x1
	.byte	0x4
	.4byte	0xa0
	.4byte	.LLST3
	.uleb128 0x13
	.ascii	"i\000"
	.byte	0x1
	.byte	0x5
	.4byte	0x5a
	.4byte	.LLST4
	.uleb128 0x14
	.4byte	0x2e2
	.4byte	.LBB10
	.4byte	.Ldebug_ranges0+0
	.byte	0x1
	.byte	0x6
	.4byte	0x395
	.uleb128 0x15
	.4byte	0x2f5
	.byte	0x6
	.byte	0x3
	.4byte	.LC0
	.byte	0x9f
	.uleb128 0x16
	.4byte	.LVL3
	.4byte	0x443
	.uleb128 0x17
	.byte	0x1
	.byte	0x52
	.byte	0x3
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x17
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	.LC0
	.uleb128 0x17
	.byte	0x1
	.byte	0x50
	.byte	0x1
	.byte	0x31
	.byte	0
	.byte	0
	.uleb128 0x18
	.4byte	0x2e2
	.4byte	.LBB14
	.4byte	.LBE14
	.byte	0x1
	.byte	0x9
	.4byte	0x3ca
	.uleb128 0x19
	.4byte	0x2f5
	.4byte	.LLST5
	.uleb128 0x16
	.4byte	.LVL5
	.4byte	0x443
	.uleb128 0x17
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	.LC1
	.uleb128 0x17
	.byte	0x1
	.byte	0x50
	.byte	0x1
	.byte	0x31
	.byte	0
	.byte	0
	.uleb128 0x14
	.4byte	0x2e2
	.4byte	.LBB16
	.4byte	.Ldebug_ranges0+0x18
	.byte	0x1
	.byte	0x10
	.4byte	0x3f3
	.uleb128 0x1a
	.4byte	0x2f5
	.uleb128 0x1b
	.4byte	.LVL8
	.byte	0x1
	.4byte	0x461
	.uleb128 0x17
	.byte	0x1
	.byte	0x50
	.byte	0x1
	.byte	0x3a
	.byte	0
	.byte	0
	.uleb128 0x1c
	.4byte	0x2e2
	.4byte	.LBB20
	.4byte	.LBE20
	.byte	0x1
	.byte	0xe
	.uleb128 0x15
	.4byte	0x2f5
	.byte	0x6
	.byte	0x3
	.4byte	.LC2
	.byte	0x9f
	.uleb128 0x16
	.4byte	.LVL10
	.4byte	0x443
	.uleb128 0x17
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	.LC2
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x37
	.uleb128 0x1d
	.4byte	.LASF52
	.byte	0x6
	.byte	0xa8
	.4byte	0x2ab
	.byte	0x1
	.byte	0x1
	.uleb128 0x1d
	.4byte	.LASF53
	.byte	0x6
	.byte	0xa9
	.4byte	0x2ab
	.byte	0x1
	.byte	0x1
	.uleb128 0x1e
	.byte	0x1
	.4byte	.LASF54
	.byte	0x2
	.byte	0x57
	.byte	0x1
	.4byte	0x5a
	.byte	0x1
	.4byte	0x461
	.uleb128 0x1f
	.4byte	0x5a
	.uleb128 0x1f
	.4byte	0x2d7
	.uleb128 0x10
	.byte	0
	.uleb128 0x20
	.byte	0x1
	.4byte	.LASF55
	.byte	0x7
	.byte	0
	.4byte	.LASF63
	.byte	0x1
	.4byte	0x5a
	.byte	0x1
	.uleb128 0x1f
	.4byte	0x5a
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
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
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
	.uleb128 0x27
	.uleb128 0xc
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
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x13
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
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x14
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
	.uleb128 0x15
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0xa
	.uleb128 0x2111
	.uleb128 0xa
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
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x2115
	.uleb128 0xc
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
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
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
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
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x20
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
	.uleb128 0x2007
	.uleb128 0xe
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
	.4byte	.LFB24-.Ltext0
	.4byte	.LCFI0-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI0-.Ltext0
	.4byte	.LFE24-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 24
	.4byte	0
	.4byte	0
.LLST1:
	.4byte	.LVL0-.Ltext0
	.4byte	.LVL2-.Ltext0
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL2-.Ltext0
	.4byte	.LFE24-.Ltext0
	.2byte	0x1
	.byte	0x57
	.4byte	0
	.4byte	0
.LLST2:
	.4byte	.LVL0-.Ltext0
	.4byte	.LVL1-.Ltext0
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL1-.Ltext0
	.4byte	.LVL7-.Ltext0
	.2byte	0x1
	.byte	0x56
	.4byte	.LVL7-.Ltext0
	.4byte	.LVL8-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	.LVL8-.Ltext0
	.4byte	.LVL9-.Ltext0
	.2byte	0x1
	.byte	0x56
	.4byte	.LVL9-.Ltext0
	.4byte	.LFE24-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST3:
	.4byte	.LVL0-.Ltext0
	.4byte	.LVL3-1-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL3-1-.Ltext0
	.4byte	.LFE24-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST4:
	.4byte	.LVL3-.Ltext0
	.4byte	.LVL4-.Ltext0
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST5:
	.4byte	.LVL4-.Ltext0
	.4byte	.LVL6-.Ltext0
	.2byte	0x6
	.byte	0x3
	.4byte	.LC1
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
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LBB10-.Ltext0
	.4byte	.LBE10-.Ltext0
	.4byte	.LBB13-.Ltext0
	.4byte	.LBE13-.Ltext0
	.4byte	0
	.4byte	0
	.4byte	.LBB16-.Ltext0
	.4byte	.LBE16-.Ltext0
	.4byte	.LBB19-.Ltext0
	.4byte	.LBE19-.Ltext0
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF23:
	.ascii	"_IO_buf_end\000"
.LASF9:
	.ascii	"__quad_t\000"
.LASF31:
	.ascii	"_old_offset\000"
.LASF54:
	.ascii	"__printf_chk\000"
.LASF57:
	.ascii	"print.c\000"
.LASF26:
	.ascii	"_IO_save_end\000"
.LASF5:
	.ascii	"short int\000"
.LASF8:
	.ascii	"size_t\000"
.LASF13:
	.ascii	"sizetype\000"
.LASF36:
	.ascii	"_offset\000"
.LASF63:
	.ascii	"putchar\000"
.LASF20:
	.ascii	"_IO_write_ptr\000"
.LASF15:
	.ascii	"_flags\000"
.LASF22:
	.ascii	"_IO_buf_base\000"
.LASF51:
	.ascii	"message\000"
.LASF27:
	.ascii	"_markers\000"
.LASF17:
	.ascii	"_IO_read_end\000"
.LASF6:
	.ascii	"long long int\000"
.LASF35:
	.ascii	"_lock\000"
.LASF11:
	.ascii	"long int\000"
.LASF60:
	.ascii	"printf\000"
.LASF32:
	.ascii	"_cur_column\000"
.LASF48:
	.ascii	"_pos\000"
.LASF47:
	.ascii	"_sbuf\000"
.LASF44:
	.ascii	"_IO_FILE\000"
.LASF1:
	.ascii	"unsigned char\000"
.LASF4:
	.ascii	"signed char\000"
.LASF7:
	.ascii	"long long unsigned int\000"
.LASF0:
	.ascii	"unsigned int\000"
.LASF45:
	.ascii	"_IO_marker\000"
.LASF34:
	.ascii	"_shortbuf\000"
.LASF56:
	.ascii	"GNU C 4.7.4\000"
.LASF19:
	.ascii	"_IO_write_base\000"
.LASF43:
	.ascii	"_unused2\000"
.LASF16:
	.ascii	"_IO_read_ptr\000"
.LASF2:
	.ascii	"short unsigned int\000"
.LASF14:
	.ascii	"char\000"
.LASF46:
	.ascii	"_next\000"
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
.LASF55:
	.ascii	"__builtin_putchar\000"
.LASF61:
	.ascii	"__fmt\000"
.LASF3:
	.ascii	"long unsigned int\000"
.LASF21:
	.ascii	"_IO_write_end\000"
.LASF12:
	.ascii	"__off64_t\000"
.LASF10:
	.ascii	"__off_t\000"
.LASF28:
	.ascii	"_chain\000"
.LASF62:
	.ascii	"printchar\000"
.LASF25:
	.ascii	"_IO_backup_base\000"
.LASF52:
	.ascii	"stdin\000"
.LASF30:
	.ascii	"_flags2\000"
.LASF42:
	.ascii	"_mode\000"
.LASF18:
	.ascii	"_IO_read_base\000"
.LASF58:
	.ascii	"/home/linaro/Documents/Thesis/aes-copa\000"
.LASF33:
	.ascii	"_vtable_offset\000"
.LASF24:
	.ascii	"_IO_save_base\000"
.LASF29:
	.ascii	"_fileno\000"
.LASF49:
	.ascii	"toPrint\000"
.LASF53:
	.ascii	"stdout\000"
.LASF59:
	.ascii	"_IO_lock_t\000"
.LASF50:
	.ascii	"printLength\000"
	.ident	"GCC: (Ubuntu/Linaro 4.7.4-2ubuntu1) 4.7.4"
	.section	.note.GNU-stack,"",%progbits
