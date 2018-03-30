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

* "mem"     (   -- mem_address )

* "!"       ( data address -- ) ; write data to address

* "@"       ( address -- data ) ; read data from address

* "quit" ; exits

* ":" ; start defining word

* ";" ; end of definition IMMEDIATE

* "lit" "n" ; push n   

Arithmetic:
* "+"       ( a b -- [a + b] )
* "-"       ( a b -- [a - b] )
* "*"       ( a b -- [a * b] )
* "/"       ( a b -- [a / b] )

Logic:
* "land"    ( a b -- a && b )
* "not"     ( a -- !a )
