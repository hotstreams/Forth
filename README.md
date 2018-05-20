# Forth

/* words */

* ".S"      ( a b -- a b ) ; show stack

* "rot"     ( a b c -- b c a )

* "swap"    ( a b -- b a )

* "dup"     ( a -- a a )

* "drop"    ( a --   )

* "."       ( a --   ) ; print int

* "key"     (   -- c ) ; read char

* "emit"    ( c --   ) ; write char

* "number"  (   -- n ) ; read int

* "mem_addr"     (   -- mem_address )

* "!"       ( data address -- ) ; write data to address

* "@"       ( address -- data ) ; read data from address

* "quit" ; rip

* ":" ; start defining word

* ";" ; end of definition IMMEDIATE

* "lit" "n" ; push n 

* "word"    ( addr -- length ) ; read word from stdin 

* "count"   ( str_address -- length )

* ">r"      ( data --  ) ; from data stack to rstack

* "r>"      (  -- data ) ; from rstack to data stack

* "r@"      (  -- data ) ; non destructive

* "c!"	    ( char address -- ) write char

* "c@"	    ( addr -- char) read char

* "branch addr"  ; jmp to xt is stored by addr
* "branch0 addr" ; jmp if tos == 0

* "printc"  ( addr count -- ) ; print count chars from addr

* "prints"  ( addr -- ) ; print string from addr

* "syscall" ( call_num a1 a2 a3 a4 a5 a6 -- new_rax new_rdx )

* "," ( a -- ) ; add a to defining word

* "c," ( a -- ) ; add byte to defining word

* "last_word_addr" (  -- last_word )

* "word_buffer_addr" (  -- word_buffer )

* "state_addr" (  -- state )

* "here_addr" (  -- [here] )

* "find_word" ( word_addr -- w_word )

* "cfa"	      ( w_word -- ex_token )

* "'"         (  -- ex_token ) ; read word and place it's xt

* "execute"   ( ex_token --  ) ; execute word

* "IMMEDIATE" ; set last word's flag = 1

* "push_xt_branch" (  -- xt_branch )

* "push_xt_branch0" ( -- xt_branch0 )

* "if else then" ; for compiler mode

* "print_colon word" ; print ex_tokens for word

Arithmetic:
* "+"       ( a b -- [a + b] )
* "-"       ( a b -- [a - b] )
* "*"       ( a b -- [a * b] )
* "/"       ( a b -- [a / b] )
* "<"	    ( a b -- [a < b] )
* "%"	    ( a b -- [a mod b] )

Logic:
* "land"    ( a b -- [a && b] )
* "lor"     ( a b -- [a || b] )
* "not"     ( a -- [!a] )
* "="	    ( a b -- [a == b])

Bit:
* "and"     ( a b -- [a & b] )
* "or"      ( a b -- [a | b] )
