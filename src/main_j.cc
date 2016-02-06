// Wraper for Java execution generated using
// the header from javah.

#include <jni.h>
#include <stdio.h>

#include "main_j.h"
#include "libfun.h"

JNIEXPORT jint JNICALL Java_main_1j_square
(JNIEnv *, jobject, jint x){
    int tmp= x;
    return square(tmp);
    }

JNIEXPORT jint JNICALL Java_main_1j_cube
(JNIEnv *, jobject, jint x){
    int tmp= x;
    return cube(tmp);
    }

JNIEXPORT jint JNICALL Java_main_1j_print
(JNIEnv *env, jobject, jint size, jdoubleArray array){
  
  jdouble *tmp_array = env->GetDoubleArrayElements(array,0);

  print(size,tmp_array);

  env->ReleaseDoubleArrayElements(array,tmp_array,0);
  
  return 0;
  }

JNIEXPORT jint JNICALL Java_main_1j_printstr
(JNIEnv *env, jobject, jstring str){
    const char *tmpstr = env->GetStringUTFChars(str, 0);
    printstr(tmpstr);

    //(*env)->ReleaseStringUTFChars(env, javaString, nativeString);
    return 0;
    }
