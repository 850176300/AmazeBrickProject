//
//  ST_IAB_Android.h
//
//  Created by Steven.Xc.Tian on 13-8-29.
//
//

#ifndef __HIDD_BIGB02__STInAppBillingAndroid__
#define __HIDD_BIGB02__STInAppBillingAndroid__

#include "../utils/ST_JNI_Helper.h"
#include "STInAppBilling.h"

// 受Google Play服务器管理的商品类型
#define SKU_TYPE_MANAGE     "Managed"
// 不受Google Play服务器管理的商品类型，即消耗品
#define SKU_TYPE_UNMANAGE   "Unmanaged"

class AndroidIAPManager: public STIABDelegate
{
	STIABDelegate* st_m_Delegate;

public:
	AndroidIAPManager();
	~AndroidIAPManager();

	static AndroidIAPManager* getInstance();

	static void destroy();

	bool init(JNIEnv * pEnv, jobject pIAPJava);

public:
	void setIABDelegate(STIABDelegate* pDelegate);

	/**
	 * @return false if the IAP environment is NOT setup correctly, otherwise return true
	 */
	void purchase(const char* sku, const char* skuType);

	/**
	 * @return false if the IAP environment is NOT setup correctly, otherwise return true
	 */
	void restore();

	/**
	 * @return false if the IAP environment is NOT setup correctly, otherwise return true
	 */
	void query();

public:
	/* the below methods derived from STIABDelegate class */
	void purchaseSuccessful(const char* pid);

	void purchaseFailed(const char *pid, int errorCode);

	void restoreSuccessful(const char* pid);

	void restoreFailed(const char* pid, int errorCode);

	/**
	 * when we call restore or query method, but nothing returned
	 */
	void nothingRestored();

private:
	/*>>>>>>>> below declaration is used by jni <<<<<<<<*/

	// Cached Classes.
	jclass ClassIAP;
	// Cached java object
	jobject stIABJava;
	// Cached active Methods.
	jmethodID method_onPurchase_Native;
	jmethodID method_onQuery_Native;

public:
	// indicate whether IAP environment is set up successfully.
	static bool isSetupOK;
};

#endif /* defined(__HIDD_BIGB02__STInAppBillingAndroid__) */
