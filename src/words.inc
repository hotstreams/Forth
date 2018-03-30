section .bss
rs: resq 65536
u_mem: resq 65536
dict: resq 65536

native ".S", show
	mov rax, rsp
.loop:
	cmp rax, [rsp_b]
	jz next
	mov rdi, [rax]
	push rax
	call print_int
	call print_newline
	pop rax
	add rax, 8
	jmp .loop

native "quit", quit
    mov rax, 60
    xor rdi, rdi
    syscall

native "+", plus
	pop rax
	add [rsp], rax
	jmp next

native "-", minus
	pop rax
	sub [rsp], rax
	jmp next

native "*", mul
	pop rax
	pop rcx
	imul rax, rcx
	push rax
	jmp next

native "/", div
	xor rdx, rdx
	pop rbx
	pop rax
	idiv rbx
	push rax
	jmp next

native "=", equal
    pop rax
    pop rcx
    cmp rax, rcx
    jz .eq
    push 0
    jmp next
.eq:
    push 1
    jmp next

native "<", ls
    pop rax
    pop rcx
    cmp rcx, rax
    jl .less
    push 0
    jmp next
.less:
    push 1
    jmp next

native "land", land
    pop rax
    pop rcx
    test rax, rax
    jz .no
    push rcx
    jmp next
.no:
    push rax
    jmp next

native "not", not
    pop rax
    test rax, rax
    setz al
    movzx rax, al
    push rax
    jmp next

native "rot", rot
    pop rax
    pop rcx
    pop rdx
    push rcx
    push rax
    push rdx
    jmp next

native "swap", swap
    pop rax
    pop rcx
    push rax
    push rcx
    jmp next

native "dup", dup
    push qword [rsp]
    jmp next

native "drop", drop
    pop rax
    xor rax, rax
    jmp next

native ".", printi
    pop rdi
    call print_int
    jmp next

native "key", key
    call read_char
    push rax
    jmp next

native "emit", emit
    pop rdi
    call print_char
    jmp next

native "number", number
    call read_word
    mov rdi, word_buffer
    call parse_int
    push rax
    jmp next

native "mem", mem
    push qword u_mem
    jmp next

native "!", write
    pop rax
    pop rdx
    mov [rax], rdx
    jmp next

native "@", read
    pop rax
    push qword [rax]
    jmp next

native ":", col
    mov rax, [here]
    mov rcx, [last_word]

    ; define header
    mov [rax], rcx          ; link to previous word

    mov [last_word], rax    ; update last word

    add rax, 8

    push rax
    call read_word
    pop rax
    mov rdi, word_buffer
    mov rsi, rax
    call string_copy        ; define name

    mov rax, rsi
    inc rax                 ; skip flag

    ; define ex token
    mov qword [rax], docol   ; docol
    add rax, 8

    mov byte [state], 1     ; compil mode now
    mov [here], rax
    jmp next

native ";", semicol, 1
    mov rax, [here]
    mov qword [rax], xt_exit    ; add xt_exit to end of colon word
    add rax, 8
    mov [here], rax

    mov byte [state], 0
    jmp next

native "lit", lit
    push qword [pc]
    add pc, 8
    jmp next
