`(== 64 64)
(de hex2L (H)
   (make
      (for (L H L (cddr L))
         (link (hex (pack (car L) (cadr L)))) ) ) )
(de hacl51 (S P)
   (use R
      (native
         "libhaclx255.so.0"
         "Hacl_Curve25519_51_scalarmult"
         NIL
         '(R (32 B . 32))
         (cons NIL (32) S)
         (cons NIL (32) P) )
      R ) )
(de hacl64 (S P)
   (use R
      (native
         "libhaclx255.so.0"
         "Hacl_Curve25519_64_scalarmult"
         NIL
         '(R (32 B . 32))
         (cons NIL (32) S)
         (cons NIL (32) P) )
      R ) )
(de hacl64slow (S P)
   (use R
      (native
         "libhaclx255.so.0"
         "Hacl_Curve25519_64_Slow_scalarmult"
         NIL
         '(R (32 B . 32))
         (cons NIL (32) S)
         (cons NIL (32) P) )
      R ) )
(zero C)
(prinl "tests failed:")
(in "x25519_test.csv"
   (until (eof)
      (let
         (SK (prog1 (hex2L (till ",")) (char))
            PK (prog1 (hex2L (till ",")) (char))
            SH (prog (hex2L (line))) ) 
         (inc 'C)
         (unless (= SH (hacl51 SK PK))
            (printsp C) )
         (unless (= SH (hacl64 SK PK))
            (printsp C) )
         (unless (= SH (hacl64slow SK PK))
            (printsp C) ) ) ) )
(prinl)
(msg 'all-hacls-ok)
(bye)
