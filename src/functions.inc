section .data
word_buffer times 256 db 0


section .text
string_length:
	xor rax, rax
.loop:
	cmp byte [rdi+rax], 0
	jz .end
	inc rax
	jmp .loop
.end:
	ret

print_string:
	push rdi
	call string_length
	pop rsi
	mov rdx, rax
	mov rax, 1
	mov rdi, 1
	syscall
	ret

print_char:
	push rdi
	mov rsi, rsp
	mov rax, 1
	mov rdx, 1
	mov rdi, 1
	syscall
	pop rdi
	ret

print_newline:
    mov rdi, 0xA
	call print_char
    ret

print_int:
    test rdi, rdi
	jns .plus
	jmp .minus
.plus:
	call print_uint
    ret
.minus:
	push rdi
	mov rdi, '-'
	call print_char
	pop rdi
	neg rdi
	jmp .plus

print_uint:
	mov rax, rdi
	xor r8, r8
	mov rbx, 10
.loop:
	xor rdx, rdx
	div rbx
	push rdx
	inc r8
	test rax, rax
	jnz .loop
	mov rax, 1
	mov rdx, 1
	mov rdi, 1
.print:
	pop r10
	add r10, '0'
	push r10
	mov rsi, rsp
	syscall
	pop r10
	dec r8
	test r8, r8
	jnz .print
	ret

string_equals:
    mov al, byte [rdi]
    cmp al, byte [rsi]
jne .fail
    inc rdi
    inc rsi
    test al, al
    jnz string_equals
    mov rax, 1
    ret
.fail:
    xor rax, rax
    ret

read_char:
	xor rax, rax
	push rax
	mov rax, 0
	mov rsi, rsp
	mov rdi, 0
	mov rdx, 1
	syscall
	pop rax
	ret

section .text
read_word:
	xor r9, r9
	mov qword [word_buffer], 0x00000000
.loop:
	xor rax, rax
	xor r8, r8
	call read_char
	cmp al, 0x20
	jz .check
	cmp al, 0xA
	jz .check
	cmp al, 0x9
	jz .check
	lea r8, [word_buffer+r9]
	mov byte [r8], al
	test rax, rax
	jz .end
	inc r9
	jmp .loop
.check:
	test r9, r9
	jz .loop
	jmp .end
.end:
	mov rax, word_buffer
	mov rdx, r9
	ret

parse_uint:
	xor r9, r9
	mov r9, 10d
   	xor rax, rax
	xor r8, r8
	xor r11, r11
.loop:
	xor r10, r10
	mov r10b, byte[rdi+r11]
	inc r11
.below:
	cmp r10b, '0'
	jb .end
.above:
	cmp r10b, '9'
	ja .end
.value:
	sub r10b, '0'
	mul r9
	add rax, r10
	inc r8
	jmp .loop
.end:
	mov rdx, r8
	ret

parse_int:
	xor r8, r8
	xor rax, rax
	cmp byte [rdi], '-'
	jz .minus
	call parse_uint
	ret
.minus:
	lea rdi, [rdi+1]
	call parse_uint
	test rdx, rdx
	jz .end
	neg rax
	inc rdx
	ret
.end:
	xor rdx, rdx
	ret

string_copy:
    push rdi
    push rsi
    call string_length
    xor r10, r10
    xor r11, r11
    pop rsi
    pop rdi
.loop:
    cmp rax, r10
    jae .copy
    jmp .end
.copy:
    mov r11, [rdi+r10]
    mov qword [rsi], r11
    inc rsi
    inc r10
    jmp .loop
.end:
    ret

; find word in dict
; word_buffer <- word
; w_word or 0 -> rax
find_word:
    xor rax, rax
    mov rax, [last_word]
.loop:
    push rax
    add rax, 8
    mov rdi, rax
    mov rsi, word_buffer
	call string_equals

	test rax, rax
	jnz .found

	pop rax
	mov rax, [rax]
	test rax, rax
	jnz .loop

    xor rax, rax
    ret
.found:
    pop rax
    ret

; code from address
; rdi <- w_word
; xt_word -> rax
cfa:
    add rdi, 8
    call string_length
    add rdi, rax
    add rdi, 2
    mov rax, rdi
    ret
