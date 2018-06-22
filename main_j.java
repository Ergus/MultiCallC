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

// We generate the thisfile.h with:
// javac thisfile.java
// javah thisfile
// In Java an externa wrapper is mandatory

public class main_j {
	native int square(int i);
	native int cube(int i);
	native void print(int i, double [] array);
	native void printstr(String str);

	static {
		System.loadLibrary("modulejava");
    }

	static public void main(String argv[])
	{
		// First Part
		main_j libfun = new main_j() ;

		for(int i = 0; i < 5; ++i) {
			System.out.printf("%d\tx^2=%2d\tx^3=%2d\n",
							  i,libfun.square(i),libfun.cube(i));
		}

		// Second part
		int size = 6;
		double[] array = new double[size];

		for(int i = 0; i < size; ++i)
			array[i] = i + 1;

		libfun.print(size, array);

		// Third part
		String str="my string";
		libfun.printstr(str);
    }

}
