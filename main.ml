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


external square: int -> int = "my_square";;
external cube: int -> int = "my_cube";;
external print: int -> float array -> unit = "my_print";;
external printstr: string -> unit = "my_printstr";;

(* Function *)
for i = 0 to 4 do
	Printf.printf "%d\tx^2=%2d\tx^3=%2d\n%!" i (square(i)) (cube(i))
done;;

(* Array *)
let size = 6;;
let arr = Array.create_float size;;

for i = 0 to (size-1) do
	arr.(i) <- (float (i + 1))
done;;

print size arr;;

(* String *)
let str = "my string";;
printstr str

