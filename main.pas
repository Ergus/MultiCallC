program Main_Pascal;

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
