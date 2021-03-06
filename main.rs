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

use std::ffi::CString;

mod libfun {
    extern { pub fn square(n: i32) -> i32; }    
    extern { pub fn cube(n: i32) -> i32; }
    extern { pub fn print(n: usize, arr: *const f64);}
    extern { pub fn printstr(inp: *const i8);}
}

fn main() {

    for i in 0..5{
        let sq = unsafe { libfun::square(i)};
        let cu = unsafe { libfun::cube(i)};
        println!{"{}\tx^2={:2}\tx^3={:2}",i,sq,cu};
    }

    const SIZE: usize=6;
    let mut arr: [f64; SIZE]=[0.0; SIZE];

    for i in 0..SIZE { arr[i]= (i+1) as f64; };

    let raw = &arr as *const f64;
    unsafe { libfun::print(SIZE, raw);};

    // detalles en https://doc.rust-lang.org/libc
    let str = CString::new("my string").unwrap();

    unsafe { libfun::printstr(str.as_ptr());};
    
}
