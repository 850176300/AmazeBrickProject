/*
 * com_common_android_LaunchActivity.cpp
 *
 *  Created on: 2013-8-29
 *      Author: Steven.Xc.Tian
 */

#include "com_common_android_LaunchActivity.h"
#include "../utils/ST_JNI_Helper.h"
#include "ST_IAB_Android.h"

JNIEXPORT void JNICALL Java_com_common_android_LaunchActivity_nativeInit
(JNIEnv * pEnv, jobject jobj)
{
    LOGE("%s",__func__);
	ST_JNI_Helper::getInstance()->init(pEnv);
}

JNIEXPORT void JNICALL Java_com_common_android_LaunchActivity_nativeFinalize
(JNIEnv * pEnv, jobject)
{
	ST_JNI_Helper::getInstance()->finalize();
	AndroidIAPManager::getInstance()->destroy();
}

JNIEXPORT void JNICALL Java_com_common_android_LaunchActivity_NativeSetupFinished
(JNIEnv * pEnv, jobject jobj, jboolean result)
{
	/*
	if(result)
	{
		LOGI("native setup result OK");
		AndroidIAPManager::isSetupOK = true;
	}
    else
    {
    	LOGI("native setup result Failed");
    	AndroidIAPManager::isSetupOK = false;
    }
*/
	// init iap environment
	AndroidIAPManager::getInstance()->init(pEnv, jobj);
}

JNIEXPORT void JNICALL Java_com_common_android_LaunchActivity_querySuccess
(JNIEnv *pEnv, jobject pIAPJava, jobjectArray skus)
{
    LOGE("%s", __func__);
	if(!skus)
	{
		// it means nothing purchased before.
		AndroidIAPManager::getInstance()->nothingRestored();
		return;
	}

	// Get the value of each String object in the array
	jsize length = pEnv->GetArrayLength(skus);
    
    if (length == 0) {
		AndroidIAPManager::getInstance()->nothingRestored();
		return;
	}
    
	for (int i = 0; i < length; i++)
	{
		jstring objString = (jstring) pEnv->GetObjectArrayElement(skus, i);
		if (0 == objString)
			return;

		// Convert the JNI String (jstring) into C-String (char*)
		const char *inCStr = pEnv->GetStringUTFChars(objString, 0);
		if (!inCStr)
			return;

		// inform delegate
		AndroidIAPManager::getInstance()->restoreSuccessful(inCStr);

		// release resources
		pEnv->ReleaseStringUTFChars(objString, inCStr);
	}
}

JNIEXPORT void JNICALL Java_com_common_android_LaunchActivity_queryFailed
(JNIEnv * pEnv, jobject, jint errorCode)
{
	AndroidIAPManager::getInstance()->restoreFailed("", errorCode);
}

JNIEXPORT void JNICALL Java_com_common_android_LaunchActivity_purchaseFailed
(JNIEnv * pEnv, jobject, jint errorCode)
{
	LOGE("purchase failed");
	AndroidIAPManager::getInstance()->purchaseFailed("", errorCode);
}

JNIEXPORT void JNICALL Java_com_common_android_LaunchActivity_purchaseSuccess
(JNIEnv * pEnv, jobject, jstring sku)
{
	// Convert the JNI String (jstring) into C-String (char*)
	const char *inCStr = pEnv->GetStringUTFChars(sku, 0);
	if (!inCStr)
		return;
	LOGE("purchase sucess");
	// inform delegate
	AndroidIAPManager::getInstance()->purchaseSuccessful(inCStr);

	// release resources
	pEnv->ReleaseStringUTFChars(sku, inCStr);
}

JNIEXPORT void JNICALL Java_com_common_android_LaunchActivity_consumeSuccess
(JNIEnv * pEnv, jobject, jstring)
{
	/* Unused !*/
}

JNIEXPORT void JNICALL Java_com_common_android_LaunchActivity_consumeFailed
(JNIEnv * pEnv, jobject, jint, jstring)
{
	/* Unused !*/
}

