#!/usr/bin/guile --no-auto-compile
!#

;;
;; This file is part of the MultiCallC distribution Copyright (c) 2015 Jimmy
;; Aguilar Mena.
;;
;; This program is free software: you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation, version 3.
;;
;; This program is distributed in the hope that it will be useful, but
;; WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
;; General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with this program. If not, see <http://www.gnu.org/licenses/>.
;;

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

