#!/usr/bin/guile --no-auto-compile
!#

(use-modules (srfi srfi-4))
(load-extension "./libmodulescheme" "init_module")

;; Simple function

(do ((i 0 (1+ i)))
    ((> i 4))
  (format #t "~s\tx^2=~s\tx^3=~s\n" i (square i) (cube i)))

;; Array
(define size 6)

(define array (make-f64vector size))

(do ((i 0 (1+ i)))
    ((>= i size))
  (f64vector-set! array i (+ i 1)))
(print size array)

;; string
(define mystring "my string")
(printstr mystring)

