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

import (
	"fmt"
)

func square(val int) int __asm__ ("square");
func cube(val int) int __asm__ ("cube");
func print_c(size int, arr *float64) int __asm__ ("print");
func printstr(arr *byte) int __asm__ ("printstr");

func main() {

	// First test

	for i := 0; i < 5; i++ {
		fmt.Printf("%d\tx^2=%2d\tx^3=%2d\n",
			i,square(i), cube(i))
	}

	// Secound test, pass array
	const size = 6
	arr := make([]float64,size)

	for i:=0;i<size;i++ {arr[i]=float64(i+1)}
	print_c(size,&arr[0])

	// Third test
	str := []byte("my string")

	printstr(&str[0])
}
