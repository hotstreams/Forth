: even dup 0 < if 0 swap - then 2 % not ;

: prime dup 2 = if drop 1 exit then ( if x == 2 return 1 ) 
	dup 1 = if drop 0 exit then ( if x == 1 return 0 )
	dup 0 = if drop 0 exit then ( if x == 0 return 0 ) 
	
	2 >r			    ( rstack i = 2 ) 
	dup			    ( x x )	
	repeat
		dup	            ( x x x )
		r> dup 1 + >r	    ( x x x i   rstack i++ )  
		dup dup * rot swap  ( x x i x i*i )
		< not rot rot % land ( if x >= i*i && x % i continue )  
		if dup 0 else 1 then
	until 
	r> 1 - dup * < ; ( return x < [i-1]^2 )

: prime-allot 
	prime
	1 allot
	dup rot swap ! ;

: concat
	( s1 s2 )
	dup count 	( s1 s2 l2 )
	rot dup count 	( s2 l2 s1 l1 )
	rot 		( s2 s1 l1 l2 )
	+ 		( s2 s1 l12 )
	1 + 		( s2 s1 l12+1 )
	heap-alloc  	( s2 s1 ad )
	dup rot 	( s2 ad ad s1 ) 
	dup rot 	( s2 ad s1 s1 ad )
	swap string-copy dup 	( s2 ad s1 s1 		ad = str1 )
	count swap heap-free 	( s2 ad l1 		heap-free for string_1 )
	swap dup 	( s2 l1 ad ad )
	rot + 		( s2 ad ad+l1 ) 
	rot dup 	( ad ad+l1 s2 s2 ) 
	rot 		( ad s2 s2 ad+l1 )
	dup 		( ad s2 s2 ad+l1 ad+l1 )	
	rot 		( ad s2 ad+l1 ad+l1 s2 )
	dup count rot 	( ad s2 ad+l1 s2 l2 ad+l1 ) 
	+ 		( ad s2 ad+l1 s2 ad+l12 )
	swap rot 	( ad s2 ad+l12 s2 ad+l1 )
	swap string-copy 	( ad s2 adl1+l2 	ad = str1str2 )
	0 swap c! 	( ad s2   			ad = str1str2\0 ) 
	heap-free 	( ad 				heap-free for string_2 ) ;

( m" Владимирский" string-hash 3 %   = 0 )

: collatz
	repeat
		dup . 32 emit			( print x' ' )	
		dup 1 = if drop exit then	( if x == 1 exit colon )
		dup even			( if x % 2 == 0  x /= 2 ) 
		if 2 / else 3 * 1 + then 	( else x = 3x + 1 )
		0
	until ;	
