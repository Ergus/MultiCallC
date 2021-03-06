!
! This file is part of the MultiCallC distribution Copyright (c) 2015 Jimmy
! Aguilar Mena.
!
! This program is free software: you can redistribute it and/or modify
! it under the terms of the GNU General Public License as published by
! the Free Software Foundation, version 3.
!
! This program is distributed in the hope that it will be useful, but
! WITHOUT ANY WARRANTY; without even the implied warranty of
! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
! General Public License for more details.
!
! You should have received a copy of the GNU General Public License
! along with this program. If not, see <http://www.gnu.org/licenses/>.
!

PROGRAM main

  USE, INTRINSIC :: iso_c_binding

  IMPLICIT NONE

  ! First test

  INTERFACE
     INTEGER FUNCTION square( x ) bind(C)
       use, intrinsic       :: iso_c_binding
       INTEGER(kind=c_int), VALUE, INTENT(IN)  :: x
     END FUNCTION square
  END INTERFACE

  INTERFACE
     INTEGER FUNCTION cube( x ) bind(C)
       use, intrinsic       :: iso_c_binding
       INTEGER(kind=c_int), VALUE, INTENT(IN)  :: x
     END FUNCTION cube
  END INTERFACE

  ! Second test.

  INTERFACE
     SUBROUTINE print(size, array) bind(C)
       use, intrinsic       :: iso_c_binding
       INTEGER(kind=c_int), VALUE, INTENT(IN)  :: size
       REAL(kind=c_double), INTENT(IN), DIMENSION(*)  :: array
     END SUBROUTINE print
  END INTERFACE

  ! Third test

  INTERFACE
     SUBROUTINE printstr(str) bind(C)
       use, intrinsic       :: iso_c_binding
       CHARACTER(kind=c_char) :: str(*)
     END SUBROUTINE printstr
  END INTERFACE

  INTEGER i, j, k

  INTEGER :: size=6
  REAL(8), DIMENSION(1:6) :: array

  ! For third test
  CHARACTER (LEN=*), PARAMETER :: str="my string"

  ! First

  DO i=0,4
     j=square(i)
     k=cube(i)
     write(*,*) i, "x^2=", j,"x^3=", k
  END DO

  ! Second

  DO i=1,size
     array(i)=dble(i)
  END DO

  CALL print(size,array)

  ! Third

  call printstr(str)


END PROGRAM main
