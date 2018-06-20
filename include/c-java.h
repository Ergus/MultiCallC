
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