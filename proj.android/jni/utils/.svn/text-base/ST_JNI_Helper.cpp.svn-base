//
//  ST_JNI_Helper.cpp
//  MysteryGuardians
//
//  Created by Steven.Xc.Tian on 13-6-25.
//
//

#include "ST_JNI_Helper.h"

JavaVM* ST_JNI_Helper::stJavaVM = 0;

void ST_JNI_Helper::init(JNIEnv * pEnv)
{
	// Caches the VM.
	if (pEnv->GetJavaVM(&stJavaVM) != JNI_OK)
	{
		LOGE("get JavaVM Failed!");
		return;
	}
}

JNIEnv* ST_JNI_Helper::getJNIEnv()
{
	JavaVMAttachArgs lJavaVMAttachArgs;
	lJavaVMAttachArgs.version = JNI_VERSION_1_6;
	lJavaVMAttachArgs.name = "NativeThread";
	lJavaVMAttachArgs.group = 0;

	JNIEnv* lEnv;
	if (stJavaVM->AttachCurrentThread(&lEnv, &lJavaVMAttachArgs) != JNI_OK)
	{
		lEnv = 0;
	}
	return lEnv;
}

jobject ST_JNI_Helper::makeGlobalRef(jobject pRef)
{
	return makeGlobalRef(getJNIEnv(), pRef);
}

jobject ST_JNI_Helper::makeGlobalRef(JNIEnv* pEnv, jobject pRef)
{
	if (pRef)
	{
		jobject lGlobalRef = pEnv->NewGlobalRef(pRef);
		// No need for a local reference any more.
		pEnv->DeleteLocalRef(pRef);
		// Here, lGlobalRef may be null.
		return lGlobalRef;
	}
}

void ST_JNI_Helper::deleteGlobalRef(jobject pRef)
{
	deleteGlobalRef(getJNIEnv(), pRef);
}

void ST_JNI_Helper::deleteGlobalRef(JNIEnv* pEnv, jobject pRef)
{
	if (pRef)
	{
		pEnv->DeleteGlobalRef(pRef);
		pRef = 0;
	}
}

// singleton stuff
static ST_JNI_Helper *s_InAppBilling = 0;

void ST_JNI_Helper::finalize()
{
	if (s_InAppBilling)
	{
		delete s_InAppBilling;
		s_InAppBilling = 0;
	}
}

ST_JNI_Helper* ST_JNI_Helper::getInstance()
{
	if (!s_InAppBilling)
	{
		s_InAppBilling = new ST_JNI_Helper();
	}

	return s_InAppBilling;
}

ST_JNI_Helper::~ST_JNI_Helper()
{
    stJavaVM = 0;
}
