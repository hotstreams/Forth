%define link 0

%macro previous 1
    dq link
    %define link w_%1
%endmacro

; native words
; %1 - name, %2 - id, %3 - flag
; | link | \0 | name | \0 | flag | impl |
%macro native 3
    section .data
    w_%2:
        previous %2
        db 0
        db %1, 0
        db %3
    xt_%2:
        dq %2_impl
    section .text
    %2_impl:
%endmacro

%macro native 2
    native %1, %2, 0
%endmacro

; colon words
; | link | \0 | name | \0 | flag | docol_impl | tokens ... | xt_exit
%macro colon 3
    section .data
    w_%2:
        previous %2
 	db 0
        db %1, 0
        db %3
    xt_%2:
        dq docol
%endmacro

%macro colon 2
    colon %1, %2, 0
%endmacro
