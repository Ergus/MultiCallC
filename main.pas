program Main_Pascal;

(*
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
 *)

{$linklib libfun.so}

uses crt, sysutils, CTypes;

type
   farray = array of ctypes.cdouble;

function square(x: ctypes.cint32):ctypes.cint32; cdecl; external;
function cube(x: ctypes.cint32):ctypes.cint32; cdecl; external;
procedure print(size: ctypes.cint32; oarray: farray); cdecl; external;
procedure printstr(str : pChar); cdecl; external;

var
   i, size : integer;
   sline   : string;
   myarray : farray;
   text    : ansistring;

(* Here the main program block starts *)
begin
   for i:= 0 to 4 do
   begin
	  sline := Format('%d'#9'x^2=%2d'#9'x^3=%2d', [i, square(i), cube(i)]);
	  writeln(sline);
   end;

   (* Array of doubles *)
   size := 6;
   setlength(myarray, size);

   for i:= 1 to size do
	  myarray[i-1] := i;

   print(size, myarray);

   (* String *)
   text := 'my array';
   printstr(pChar(text));

end.
