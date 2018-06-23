--
-- This file is part of the MultiCallC distribution Copyright (c) 2015 Jimmy
-- Aguilar Mena.
--
-- This program is free software: you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, version 3.
--
-- This program is distributed in the hope that it will be useful, but
-- WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
-- General Public License for more details.
--
-- You should have received a copy of the GNU General Public License
-- along with this program. If not, see <http://www.gnu.org/licenses/>.
--

with Ada.Text_IO;

procedure main_ada is
   package Integer_Text_IO is new Ada.Text_IO.Integer_IO (Integer);

   -- types
   type Vector is array(Integer range <>) of Long_Float;

   -- C functions
   function square(x : in Integer) return Integer;
   pragma Import(C, square);

   function cube(x : in Integer) return Integer;
   pragma Import(C, cube);

   procedure print(x : in Integer; Carray : in Vector);
   pragma Import(C, print);

   procedure printstr(x : in String);
   pragma Import(C, printstr);

   -- Variables
   Ret2, Ret3 : Integer;
   Size : Integer := 6;

begin
For_Loop :
	for I in Integer range 0 .. 4 loop
	   Ret2 := square(I);
	   Ret3 := cube(I);

	   Integer_Text_IO.Put(I,1);
	   Ada.Text_IO.Put("   x^2=");
	   Integer_Text_IO.Put(Ret2, 2);
	   Ada.Text_IO.Put("   x^3=");
	   Integer_Text_IO.Put(Ret3, 2);
	   Ada.Text_IO.New_Line;
	end loop For_Loop;

	-- Array
	Size := 6;
	declare
	   Carray : Vector(1..Size);
	begin
	   for I in 1..size Loop
		  carray(i) := Long_Float(I);
	   end Loop;
	   	print(Size, Carray);
	end;

	-- String
	declare
	   Str : constant String := "my array";
	begin
	   printstr(Str);
	end;

end main_ada;

