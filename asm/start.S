.global _start

.intel_syntax noprefix

_start:


_exit:
  mov eax, 1
  mov ebx, 0
  int 0x80

