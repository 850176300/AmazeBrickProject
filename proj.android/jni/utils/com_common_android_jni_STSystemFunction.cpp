/*
 * com_common_android_jni_STSystemFunction.cpp
 *
 *  Created on: 2013-9-2
 *      Author: Steven.Xc.Tian
 */
#include "com_common_android_jni_STSystemFunction.h"
#include "ST_SystemFunction_Android.h"

JNIEXPORT void JNICALL Java_com_common_android_jni_STSystemFunction_nativeInit
(JNIEnv * pEnv, jobject thisObj)
{
	SystemFunctionManager::getInstance()->init(pEnv, thisObj);
}

JNIEXPORT void JNICALL Java_com_common_android_jni_STSystemFunction_nativeDestroy
(JNIEnv * pEnv, jobject jobjSf)
{
	SystemFunctionManager::getInstance()->destroy();
}

