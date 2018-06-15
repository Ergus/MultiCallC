#!/usr/bin/guile --no-auto-compile
!#

(load-extension "./libmodulescheme" "init_module")

;; Simple function

(do ((i 0 (1+ i)))
    ((> i 4))
  (format #t "~s\tx^2=~s\tx^3=~s\n" i (square i) (cube i)))

;; Array

(define size 5)

(define array (make-uniform-array #t size))

(do ((i 0 (1+ i)))
    ((>= i size))
  (array-set! array i i)
  )



