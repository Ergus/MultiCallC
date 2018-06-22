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

#include <libfun.h>
#include <string.h>

int square(int x)
{
	return x*x;
}

int cube(int x)
{
	return x*x*x;
}

void print(int size, double* array)
{
	for(int i = 0; i < size; ++i)
		printf("%2.3lf; ",array[i]);

	printf("\n");
}


void printstr(const char *str)
{
	printf("The string \"%s\" has %u letters\n",str,(unsigned)strlen(str));
}
