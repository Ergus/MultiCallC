/*
 * This file is part of the MultiCallC distribution Copyright (c) 2015 Jimmy
 * Aguilar Mena.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

package main

/*
   #cgo CFLAGS: -I${SRCDIR}/include
   #cgo LDFLAGS: -L${SRCDIR}/build -Wl,-rpath,${SRCDIR}/build -lfun
   #include "libfun.h"
*/
import "C"
import "fmt"
import "unsafe"

func main() {

	// First test
	for i := 0; i < 5; i++ {
		ci := C.int(i)
		fmt.Printf("%d\tx^2=%2d\tx^3=%2d\n",
			i, C.square(ci), C.cube(ci))
	}

	// Secound test, pass array
	const size = 6
	var arr [size]float64
	for i:=0; i < size; i++ { arr[i]=float64(i+1) }
	C.print(C.int(size), (*C.double)(&arr[0]))

	// Third test
	str := C.CString("my string")
	C.printstr(str)
	C.free(unsafe.Pointer(str))
}
