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
(add-to-list 'load-path (expand-file-name "."))

(require 'moduleelisp)

;; Simple function

(dotimes (i 5)
  (message "%d\tx^2=%d\tx^3=%d" i (square i) (cube i)))

(setq size 6)
(setq myarray (make-vector size 0))

(dotimes (i size)
  (aset myarray i (float (+ i 1))))

(myprint size myarray)

(myprintstr "my string")

(provide 'main.el)
;;; main.el ends here

