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

#include <jni.h>
/* Header for class main_j */

#ifndef _Included_main_j
#define _Included_main_j
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     main_j
 * Method:    square
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_main_1j_square(JNIEnv *, jobject, jint);

/*
 * Class:     main_j
 * Method:    cube
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_main_1j_cube(JNIEnv *, jobject, jint);

/*
 * Class:     main_j
 * Method:    print
 * Signature: (I[D)V
 */
JNIEXPORT void JNICALL Java_main_1j_print
(JNIEnv *, jobject, jint, jdoubleArray);

/*
 * Class:     main_j
 * Method:    printstr
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_main_1j_printstr
  (JNIEnv *, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif
