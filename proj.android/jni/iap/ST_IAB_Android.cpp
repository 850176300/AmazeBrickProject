//
//  ST_IAB_Android.cpp
//
//  Created by Steven.Xc.Tian on 13-8-29.
//
//

#include "ST_IAB_Android.h"

//bool AndroidIAPManager::isSetupOK = false;

static AndroidIAPManager* sp_AndroidIAPManager = 0;

AndroidIAPManager* AndroidIAPManager::getInstance()
{
	if (!sp_AndroidIAPManager)
	{
		sp_AndroidIAPManager = new AndroidIAPManager();
	}

	return sp_AndroidIAPManager;
}

void AndroidIAPManager::destroy()
{
	if (sp_AndroidIAPManager)
	{
		delete sp_AndroidIAPManager;

		sp_AndroidIAPManager = 0;
	}
}

bool AndroidIAPManager::init(JNIEnv * pEnv, jobject pIAPJava)
{

	// get class
	ClassIAP = pEnv->GetObjectClass(pIAPJava);
	if (!ClassIAP)
	{
		LOGE("get LaunchActivity class Failed!");
		return false;
	}
	ClassIAP = (jclass) ST_JNI_Helper::makeGlobalRef(pEnv, ClassIAP);

	// get method id --- purchaseManaged(String)
	method_onPurchase_Native = pEnv->GetMethodID(ClassIAP, "onPurchase_Native",
			"(Ljava/lang/String;Ljava/lang/String;)V");
	if (!method_onPurchase_Native)
	{
		LOGE("get method_onPurchase_Native id Failed!");
		return false;
	}

	// get method id --- purchaseUnmanaged(String)
	method_onQuery_Native = pEnv->GetMethodID(ClassIAP, "onQuery_Native", "(Z)V");
	if (!method_onQuery_Native)
	{
		LOGE("get method_onQuery_Native id Failed!");
		return false;
	}

	// Caches objects.
	stIABJava = ST_JNI_Helper::makeGlobalRef(pEnv, pIAPJava);

	if (!stIABJava)
	{
		LOGE("Cache stIABJava Failed!");
		return false;
	}
	return true;
}

void AndroidIAPManager::setIABDelegate(STIABDelegate* pDelegate)
{
	st_m_Delegate = pDelegate;
}

void AndroidIAPManager::purchase(const char* sku, const char* type)
{


	if (0 == stIABJava)
	{
		LOGE("AndroidIAPManager::purchase failed!");
		return;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();
	// Convert the C++ string to C-string, then to JNI String (jstring) for method arg
	jstring arg_sku = lEnv->NewStringUTF(sku);
	jstring arg_type = lEnv->NewStringUTF(type);

	lEnv->CallVoidMethod(stIABJava, method_onPurchase_Native, arg_sku, arg_type);

	// release
	lEnv->DeleteLocalRef(arg_sku);
	lEnv->DeleteLocalRef(arg_type);

}

void AndroidIAPManager::restore()
{


	if (0 == stIABJava)
	{
		LOGE("AndroidIAPManager::restore() failed!");
		return;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

	lEnv->CallVoidMethod(stIABJava, method_onQuery_Native, false);

}

void AndroidIAPManager::query()
{
	/*
	 * although the IAP environment is not setup correctly,
	 * we can query the local records if users purchased before.
	 */
//	if (!isSetupOK)
//	{
//		LOGE("IAP Environment not set up correctly");
//		return false;
//	}
	if (0 == stIABJava)
	{
		LOGE("AndroidIAPManager::query() failed!");
		return;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

	lEnv->CallVoidMethod(stIABJava, method_onQuery_Native, true);
}

void AndroidIAPManager::purchaseSuccessful(const char* pid)
{
	LOGE("AndroidIAPManager sucess");
	if (st_m_Delegate)
	{
		LOGE("AndroidIAPManager sucess222");
		st_m_Delegate->purchaseSuccessful(pid);
	}
}

void AndroidIAPManager::purchaseFailed(const char *pid, int errorCode)
{
	LOGE("AndroidIAPManager failed");
	if (st_m_Delegate)
	{
		st_m_Delegate->purchaseFailed(pid, errorCode);
	}
}

void AndroidIAPManager::restoreSuccessful(const char* pid)
{


	if ( st_m_Delegate)
	{
		st_m_Delegate->restoreSuccessful(pid);
	}


}

void AndroidIAPManager::restoreFailed(const char* pid, int errorCode)
{
	if ( st_m_Delegate)
	{
		st_m_Delegate->restoreFailed(pid, errorCode);
	}
}

void AndroidIAPManager::nothingRestored()
{
    if( st_m_Delegate)
        st_m_Delegate->nothingRestored();
}

AndroidIAPManager::AndroidIAPManager() :
		st_m_Delegate(0), stIABJava(0), ClassIAP(0), method_onPurchase_Native(0), method_onQuery_Native(0)
{
}

AndroidIAPManager::~AndroidIAPManager()
{
	ST_JNI_Helper::deleteGlobalRef(ClassIAP);
	ST_JNI_Helper::deleteGlobalRef(stIABJava);
}
