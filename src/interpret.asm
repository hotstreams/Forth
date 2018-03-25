%include "macroses.inc"
%include "functions.inc"

%define pc r12
%define w r13
%define rstack r14

%include "words.inc"


section .data
last_word: dq link
rsp_b: dq 0
no_word: db 'There is no such word', 10, 0

program_stub: dq 0
; two indirect level
xt_interpreter: dq .interpreter
    .interpreter: dq interpreter_loop


section .text
global _start
_start:
	mov rstack, rs + 65536 * 8
	mov [rsp_b], rsp
    mov pc, xt_interpreter
    jmp next

interpreter_loop:
	call read_word		    ; word <- stdin

	mov rdi, word_buffer
	call find_word		    ; try as defined word

	test rax, rax
	jz .parse_number	    ; if !(word in dict) -> try parse as number

	mov rdi, rax
	call cfa		        ; else rax <- xt_word

	mov [program_stub], rax
	mov pc, program_stub	; ptr to next execution token = found xt_word
	jmp next
.parse_number:
	mov rdi, word_buffer
	call parse_int

	test rdx, rdx
	jz .no_word		        ; if lenght == 0 rip

	push rax		        ; else push n
	jmp interpreter_loop
.no_word:
	mov rdi, no_word
	call print_string
	jmp interpreter_loop

next:
	mov w, pc	; ptr to current xt_word
	add pc, 8	; set pc as ptr to next xt (xt_interpreter / (xt_word or xt_exit) for colon)
	mov w, [w]	; ptr to word_impl or docol
	jmp [w]		; jmp to word_impl or docol

; for colon-words
docol:
	sub rstack, 8	; rstack ptr to new value
	mov [rstack], pc; push next xt
	add w, 8	    ; set w as ptr to first xt_word of colon-word
	mov pc, w	    ; pc = w
	jmp next	    ; jmp to set pc, w and execute first xt_word

exit:
	mov pc, [rstack]; restore ptr to next xt
	add rstack, 8	; rstack ptr to last value
	jmp next	    ; jmp to execution next xt
