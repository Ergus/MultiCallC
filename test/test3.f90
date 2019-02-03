
PROGRAM main

  USE, INTRINSIC :: iso_c_binding

  IMPLICIT NONE

  ! Interfaces to C

  INTERFACE
     INTEGER FUNCTION square( x ) bind(C)
       USE, INTRINSIC       :: iso_c_binding
       INTEGER(kind=c_int), VALUE, INTENT(IN)  :: x
     END FUNCTION square
  END INTERFACE

  INTERFACE
     INTEGER FUNCTION cube( x ) bind(C)
       USE, INTRINSIC       :: iso_c_binding
       INTEGER(kind=c_int), VALUE, INTENT(IN)  :: x
     END FUNCTION cube
  END INTERFACE

  ! Here really starts the test

  INTEGER i, j, k

  DO i=0,4
     j=square(i)
     k=cube(i)
     CALL assert(j==i*i)
     CALL assert(k==i*i*i)
  END DO

  ! The assert function
CONTAINS

  PURE SUBROUTINE assert(cond)
    logical, intent(in) :: cond
    INTEGER :: r
    r=1
    IF (.not. cond) THEN
       r=r/0
    END IF
  END SUBROUTINE assert

END PROGRAM main
