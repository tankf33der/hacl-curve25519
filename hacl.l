`(== 64 64)
(de hex2L (H)
   (make
      (for (L H L (cddr L))
         (link (hex (pack (car L) (cadr L)))) ) ) )
(de hacl51 (S P)
   (use R
      (native
         "libmsotoodeh.so.0"
         "curve25519_dh_CreateSharedKey"
         NIL
         '(R (32 B . 32))
         (cons NIL (32) P)
         (cons NIL (32) S) )
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
         (unless (= SH (crypto_scalarmult SK PK)) 
            (printsp C) ) ) ) )
(prinl)
(msg 'all-hacls-ok)
(bye)
