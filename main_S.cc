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

#include <dlfcn.h>
#include <stdio.h>

int main()
{
	void *libfun;
	int (*square) (int);
	int (*cube) (int);
	void (*print) (int, double *);
	void (*printstr) (char *);

	libfun = dlopen("./libfun.so", RTLD_LAZY);

	if (libfun) {
		square = (int (*)(int))dlsym(libfun, "square");
		cube = (int (*)(int))dlsym(libfun, "cube");
		print = (void (*)(int, double *))dlsym(libfun, "print");
		printstr = (void (*)(char *))dlsym(libfun, "printstr");
	} else {
		printf("Error Opening plugging\n");
		return -1;
	}

	// First test
	for (int i = 0; i < 5; ++i)
		printf("%d\tx^2=%2d\tx^3=%2d\n", i, (*square) (i), (*cube) (i));

	//Secound test, pass array
	const int size = 6;
	double arr[size];

	for (int i = 0; i < size; i++)
		arr[i] = double(i + 1);

	(*print) (size, arr);

	// Third test
	char str[] = "my string";
	(*printstr) (str);

	dlclose(libfun);

	return 0;
}
