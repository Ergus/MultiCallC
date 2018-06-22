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

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <stdlib.h>

#include "libfun.h"

static int l_square(lua_State *L)
{
	int d = luaL_checkinteger(L, 1); // get argument
	lua_pushinteger(L, square(d));   // push results
	return 1;                       // number of results
}

static int l_cube(lua_State *L)
{
	int d = luaL_checkinteger(L, 1); // get argument
	lua_pushinteger(L, cube(d));   // push results
	return 1;                       // number of results
}

static int l_print(lua_State *L)
{
	int i;
	int size = luaL_checkinteger(L, 1); // get argument
	luaL_checktype(L, 2, LUA_TTABLE);

	double *array = (double *) malloc(size * sizeof(double));

	for (i = 1; i <= size; ++i) {
		lua_rawgeti(L, 2, i);                    // push t[i]
		array[i - 1] = luaL_checknumber(L, -1);  // get val on top
		lua_pop(L, 1);                           // remove it
	}

	print(size, array);
	free(array);
	return 0;                       // number of results
}

static int l_printstr(lua_State *L)
{
	int i;
	const char *mystring = luaL_checkstring(L, 1); // get argument
	printstr(mystring);

	return 0;                       // number of results
}

int luaopen_libmodulelua(lua_State *L) {
	luaL_Reg fns[] =	{
		{"square", l_square},
		{"cube", l_cube},
		{"print", l_print},
		{"printstr", l_printstr},
		{NULL, NULL}
	};
	luaL_newlib(L, fns);
	return 1;
}
