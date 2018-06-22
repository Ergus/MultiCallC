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

// Wraper for Java execution generated using
// the header from javah.

#include <jni.h>
#include <stdio.h>

#include "c-java.h"
#include "libfun.h"

JNIEXPORT jint JNICALL Java_main_1j_square(JNIEnv *, jobject, jint x)
{
	int tmp = x;
	return square(tmp);
}

JNIEXPORT jint JNICALL Java_main_1j_cube(JNIEnv *, jobject, jint x)
{
	int tmp = x;
	return cube(tmp);
}

JNIEXPORT void JNICALL Java_main_1j_print
(JNIEnv *env, jobject, jint size, jdoubleArray array)
{
	jdouble *tmp_array = env->GetDoubleArrayElements(array, 0);

	print(size,tmp_array);

	env->ReleaseDoubleArrayElements(array, tmp_array, 0);
}

JNIEXPORT void JNICALL Java_main_1j_printstr (JNIEnv *env, jobject, jstring str)
{
	const char *tmpstr = env->GetStringUTFChars(str, 0);
	printstr(tmpstr);
}
