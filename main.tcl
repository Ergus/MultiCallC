#!/usr/bin/env tclsh

#
# This file is part of the MultiCallC distribution Copyright (c) 2015 Jimmy
# Aguilar Mena.
#
# This program is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, version 3.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#

load ./moduletcl.so

# SImple function calls
for {set i 0} {$i < 5} {incr i} {
	set sq [square $i]
	set cu [cube $i]
    puts "$i\tx^2=$sq\tx^3=$cu"
}

# Prints an array (the keys)
set size 6

for {set i 1} {$i <= $size} {incr i} {
	lappend arr $i
}

print $size $arr


# String
set mystring "my string"

printstr $mystring
