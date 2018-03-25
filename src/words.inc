section .bss
rs: resq 65536
dict: resq 65536

section .data
native '+', plus
	pop rax
	add [rsp], rax
	jmp next

native '-', minus
	pop rax
	sub [rsp], rax
	jmp next

native '*', mul
	pop rax
	pop rcx
	imul rax, rcx
	push rax
	jmp next

native '/', div
	xor rdx, rdx
	pop rbx
	pop rax
	idiv rbx
	push rax
	jmp next

native '.S', show
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

native 'quit', quit
    mov rax, 60
    xor rdi, rdi
    syscall
