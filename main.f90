
PROGRAM main

  USE, INTRINSIC :: iso_c_binding
  
  IMPLICIT NONE

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
    
  INTEGER i, j, k
  
  DO i=0,4
     j=square(i)
     k=cube(i)
     write(*,*) i, "x^2=", j,"x^3=", k
  END DO

END PROGRAM main
