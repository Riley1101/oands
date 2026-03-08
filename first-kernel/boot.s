.set ALIGN, 1 << 0 /* Align loaded modules on page boundaries */
.set MEMINFO, 1<<1 /* provide memory map */
.set FLAGS, ALIGN | MEMINFO /* This is multiboot flag field" */


.set MAGIC, 0x1BADB002 /* let magic number "badboot" bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are in multiboot */

/*
Declare a multiboot header, that marks program as kernel.
These are magic values that are documented in multiboot standard.
Boot loader will search for the first 8kb of kernel file.
320bit boundary. Signature is in its own section so header can be force to be withing 8kib
of kernel file
*/

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/*
Multiboot standard does not define the value of stack pointer register (esp) and
it is up to kernel to provide a stack. 
This allocates room for a small stack by creating a symbol at the bottom.
then allocating 16384 bytes for it. and finally creating a symbol at the top. 

The stack grow DOWNWARDS on x86. The stack is in its own section so it can be mark at nobits.
Meaning, smaller kernel file which does not contain uninitialized stack.
The stack on x86 must be 16 bytes, according to System v ABI standards. 
*/

.section .bss
.align 16
stack_bottom:
.skip 16384 # defining a downwards stack
stack_top:

/*
Linker script specifies _start as entry point to kernel
*/
.section .text
.global _start
.type _start, @function
_start:

/*
Bootloader loaded to 32 bit protected mode on a x86 machine.
Interrupts are disable, paging is disabled. 
Process stat is defined in multiboot standard.
The kernel has full control of the CPU. 
No printf no debugging mechanism, no security restriction, 
only what ever the kernel provides 

Move stack pointer to the top.typeSo it can grows downwards.
This is necessarily done in assembly as languages such as C cannot function without a stack
*/

mov $stack_top, %esp

/*
This is also a good place to initialize crucial processor states.
Features such 
- floating point instructions 
- instructions set extensions are not initialized 
Paging should be enabled here

C++ features like global constructors and exception requies runtime support here.
*/


/*
Now we call the main kernel

ABI requires the stack 16 byte (protected mode) to align at the time of call instruction
,which afterwards puses the return pointer of size 4 bytes.
The stack was empty originally and 16 byte aligned. so the call should be well defined
*/

call kernel_main

/*

Since system has nothing to do 

1. disable the cli (clear interrupt enable in eflags), mind that you may enable inteerupts and return from kernel main later on.
2. wait for next interrupt with hlt (halt instruction)
3. jump from hlt instruction if it ever waks up gue to a non maskable interrupt occuring due to system mode 
*/

   cli
1: hlt
   jmp 1b

/*
Set size of _start symbol to current location . minusits start

*/

.size _start, . - _start


