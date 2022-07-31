.set MAGIC,    0x1BADB002
.set FLAGS,    0
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot

.long MAGIC
.long FLAGS
.long CHECKSUM

stack_bottom:
.skip 32768
stack_top:

.section .text

.global _start
.type _start, @function

_start:
	mov $stack_top, %esp
	call init
	cli

hlt_loop:
	hlt
	jmp hlt_loop

.size _start, . - _start
