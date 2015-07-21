/*
 * ST_SystemFunction_Android.cpp
 *
 *  Created on: 2013-9-2
 *      Author: Steven.Xc.Tian
 */
#include "ST_SystemFunction_Android.h"

static SystemFunctionManager* sp_SystemFunctionManager = 0;





SystemFunctionManager* SystemFunctionManager::getInstance()
{
	if (!sp_SystemFunctionManager)
	{
		sp_SystemFunctionManager = new SystemFunctionManager();
	}

	return sp_SystemFunctionManager;
}

void SystemFunctionManager::destroy()
{
	if (sp_SystemFunctionManager)
	{
		delete sp_SystemFunctionManager;

		sp_SystemFunctionManager = 0;
	}
}

bool SystemFunctionManager::init(JNIEnv * pEnv, jobject pJava)
{
    LOGE("%s", __func__);
//    pDelegate = 0;
	// get class
	ClassSF = pEnv->GetObjectClass(pJava);
	if (!ClassSF)
	{
		LOGE("get STSystemFunction class Failed!");
		return false;
	}
	ClassSF = (jclass) ST_JNI_Helper::makeGlobalRef(pEnv, ClassSF);

	// get method id --- purchaseManaged(String)
	MethodSendMailByIntent = pEnv->GetMethodID(ClassSF, "sendMailByIntent", "(Ljava/lang/String;Ljava/lang/String;)V");
	if (!MethodSendMailByIntent)
	{
		LOGE("get Method SendEmail id Failed!");
		return false;
	}

	// SharedPreferences

	MethodPopAlertDialog = pEnv->GetMethodID(ClassSF, "popAlertDialog", "(Ljava/lang/String;)V");
	if (!MethodPopAlertDialog)
	{
		LOGE("get Method popAlertDialog id Failed!");
		return false;
	}

	MethodMakeToast = pEnv->GetMethodID(ClassSF, "makeToast", "(Ljava/lang/String;)V");
	if (!MethodMakeToast)
	{
		LOGE("get Method makeToast id Failed!");
		return false;
	}

	MethodShowMoreGame = pEnv->GetMethodID(ClassSF, "showMoreGame", "()V");
	if (!MethodShowMoreGame)
	{
		LOGE("get Method ShowMoreGame id Failed!");
		return false;
	}
	MethodGo2MarketDetail = pEnv->GetMethodID(ClassSF, "go2MarketDetail", "(Ljava/lang/String;)V");
	if (!MethodGo2MarketDetail)
	{
		LOGE("get MethodGo2MarketDetail id Failed!");
		return false;
	}
	MethodRating = pEnv->GetMethodID(ClassSF, "rating", "()V");
	if (!MethodRating)
	{
		LOGE("get MethodRating id Failed!");
		return false;
	}
	// get method id --- void contactUs()
	MethodContactUs = pEnv->GetMethodID(ClassSF, "contactUs", "()V");
	if (!MethodContactUs)
	{
		LOGE("get MethodContactUs id Failed!");
		return false;
	}
	// get method id --- void sendEmailAndAssetPic(final String subject, final String text, final String assetName)
	MethodSendEmailAndAssetPic = pEnv->GetMethodID(ClassSF, "sendEmailAndAssetPic",
			"(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (!MethodSendEmailAndAssetPic)
	{
		LOGE("get MethodSendEmailAndAssetPic id Failed!");
		return false;
	}
	// get method id --- void sendEmailAndFilePic(final String subject, final String text, final String fileName)
	MethodSendEmailAndFilePic = pEnv->GetMethodID(ClassSF, "sendEmailAndFilePic",
			"(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (!MethodSendEmailAndFilePic)
	{
		LOGE("get MethodSendEmailAndFilePic id Failed!");
		return false;
	}
	// get method id --- String getSdCardPath()
	MethodGetSdCardPath = pEnv->GetMethodID(ClassSF, "getSdCardPath", "()Ljava/lang/String;");
	if (!MethodGetSdCardPath)
	{
		LOGE("get MethodGetSdCardPath id Failed!");
		return false;
	}
	// check network available --- boolean checkNetworkAvailable()
	MethodCheckNetworkAvailable = pEnv->GetMethodID(ClassSF, "checkNetworkAvailable", "()Z");
	if (!MethodCheckNetworkAvailable)
	{
		LOGE("get MethodCheckNetworkAvailable id Failed!");
		return false;
	}
	//istablet
	MethodIsTabletAvailable = pEnv->GetMethodID(ClassSF, "isTabletAvailable", "()Z");
	if (!MethodIsTabletAvailable)
	{
		LOGE("get MethodIsTableAvailable id Failed!");
		return false;
	}
	MethodDensityScale = pEnv->GetMethodID(ClassSF, "densityScale", "()F");
	if (!MethodDensityScale)
	{
		LOGE("get MethodDensityScale id Failed!");
		return false;
	}
	MethodRateUs = pEnv->GetMethodID(ClassSF, "rating", "()V");
	if (!MethodRateUs)
	{
		LOGE("get MethodRateUs id Failed!");
		return false;
	}
//	MethodDismissRateus = pEnv->GetMethodID(ClassSF, "dismissRateUs", "()V");
//	if (!MethodDismissRateus)
//	{
//		LOGE("get MethodDismissRateus id Failed!");
//		return false;
//	}
    MethodNewsBlast =pEnv->GetMethodID(ClassSF, "newsBlast", "()V");
	if (!MethodNewsBlast)
	{
		LOGE("get MethodNewsBlast id Failed!");
		return false;
	}


	MethodGetScreenRatation = pEnv->GetMethodID(ClassSF, "getScreenRotation", "()I");
	if (!MethodGetScreenRatation)
	{
		LOGE("get getScreenRotation id Failed!");
		return false;
	}
//	MethodshowActionSheetOne = pEnv->GetMethodID(ClassSF, "showActionSheet", "(Ljava/lang/String;)V");
//	if (!MethodshowActionSheetOne)
//	{
//		LOGE("get showActionSheetOne id Failed!");
//		return false;
//	}
//
//	MethodshowActionSheetTwo = pEnv->GetMethodID(ClassSF, "showActionSheet", "(Ljava/lang/String;Ljava/lang/String;)V");
//	if (!MethodshowActionSheetTwo)
//	{
//		LOGE("get MethodshowActionSheet2 id Failed!");
//		return false;
//	}
//
//	MethodshowActionSheetThree = pEnv->GetMethodID(ClassSF, "showActionSheet", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
//	if (!MethodshowActionSheetThree)
//	{
//		LOGE("get MethodshowActionSheet3 id Failed!");
//		return false;
//	}
//
//	MethodshowAlertView = pEnv->GetMethodID(ClassSF, "showAlertView", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
//	if (!MethodshowAlertView)
//	{
//		LOGE("get MethodshowAlertView id Failed!");
//		return false;
//	}

    MethodEndAnalytics = pEnv->GetMethodID(ClassSF, "endSession", "()V");
	if (!MethodEndAnalytics)
	{
		LOGE("get MethodEndAnalytics id Failed!");
		return false;
	}

    MethodRefreshDCIM = pEnv->GetMethodID(ClassSF, "refreshDCIM", "(Ljava/lang/String;)V");
	if (!MethodRefreshDCIM)
	{
		LOGE("get MethodRefreshDCIM id Failed!");
		return false;
	}

	// Caches objects.

	// Caches objects.
	stSFJava = ST_JNI_Helper::makeGlobalRef(pEnv, pJava);
	if (!stSFJava)
	{
		LOGE("Cache stSFJava Failed!");
		return false;
	}

	return true;
}

void SystemFunctionManager::sendEmail(const char* subject, const char* body)
{
	if (!stSFJava)
	{
		LOGE("SystemFunctionManager::sendEmail() failed!");
		return;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

	// Convert the C++ string to C-string, then to JNI String (jstring) for method args
	jstring sub = lEnv->NewStringUTF(subject);
	jstring content = lEnv->NewStringUTF(body);

	lEnv->CallVoidMethod(stSFJava, MethodSendMailByIntent, sub, content);

	lEnv->DeleteLocalRef(sub);
	lEnv->DeleteLocalRef(content);
}

void SystemFunctionManager::popAlertDialog(const char* message)
{
	if (!stSFJava)
	{
		LOGE("SystemFunctionManager::popAlertDialog() failed!");
		return;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

	// Convert the C++ string to C-string, then to JNI String (jstring) for method args
	jstring msg = lEnv->NewStringUTF(message);

	lEnv->CallVoidMethod(stSFJava, MethodPopAlertDialog, msg);

	lEnv->DeleteLocalRef(msg);
}

void SystemFunctionManager::makeToast(const char* message)
{
	if (!stSFJava)
	{
		LOGE("SystemFunctionManager::makeToast() failed!");
		return;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

	// Convert the C++ string to C-string, then to JNI String (jstring) for method args
	jstring msg = lEnv->NewStringUTF(message);

	lEnv->CallVoidMethod(stSFJava, MethodMakeToast, msg);

	lEnv->DeleteLocalRef(msg);
}

void SystemFunctionManager::showMoreGame()
{
	if (!stSFJava)
	{
		LOGE("SystemFunctionManager::showMoreGame() failed!");
		return;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

	lEnv->CallVoidMethod(stSFJava, MethodShowMoreGame);
}
void SystemFunctionManager::go2MarketDetail(std::string packagename)
{
	if (!stSFJava)
	{
		LOGE("SystemFunctionManager::Go2MarketDetail() failed!");
		return;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();
	jstring jniPackagename = lEnv->NewStringUTF(packagename.c_str());

	lEnv->CallVoidMethod(stSFJava, MethodGo2MarketDetail, jniPackagename);
	lEnv->DeleteLocalRef(jniPackagename);
}

void SystemFunctionManager::rating()
{
	if (!stSFJava)
	{
		LOGE("SystemFunctionManager::rating() failed!");
		return;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

	lEnv->CallVoidMethod(stSFJava, MethodRating);
}

void SystemFunctionManager::contactUs()
{
	if (!stSFJava)
	{
		LOGE("SystemFunctionManager::ContactUs() failed!");
		return;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

	lEnv->CallVoidMethod(stSFJava, MethodContactUs);
}
void SystemFunctionManager::sendEmailAndAssetPic(std::string subject, std::string message, std::string assetName)
{
	if (!stSFJava)
	{
		LOGE("SystemFunctionManager::sendEmailAndAssetPic() failed!");
		return;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();
	jstring jniSubject = lEnv->NewStringUTF(subject.c_str());
	jstring jniMessage = lEnv->NewStringUTF(message.c_str());
	jstring jniAssetName = lEnv->NewStringUTF(assetName.c_str());

	lEnv->CallVoidMethod(stSFJava, MethodSendEmailAndAssetPic, jniSubject, jniMessage, jniAssetName);
	lEnv->DeleteLocalRef(jniSubject);
	lEnv->DeleteLocalRef(jniMessage);
	lEnv->DeleteLocalRef(jniAssetName);
}
void SystemFunctionManager::sendEmailAndFilePic(std::string subject, std::string message, std::string fileName)
{
	if (!stSFJava)
	{
		LOGE("SystemFunctionManager::sendEmailAndFilePic() failed!");
		return;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();
	jstring jniSubject = lEnv->NewStringUTF(subject.c_str());
	jstring jniMessage = lEnv->NewStringUTF(message.c_str());
	jstring jniFileName = lEnv->NewStringUTF(fileName.c_str());

	lEnv->CallVoidMethod(stSFJava, MethodSendEmailAndFilePic, jniSubject, jniMessage, jniFileName);
	lEnv->DeleteLocalRef(jniSubject);
	lEnv->DeleteLocalRef(jniMessage);
	lEnv->DeleteLocalRef(jniFileName);
}

int  SystemFunctionManager::getScreenRotation(){


		if (!stSFJava)
	    {
	        LOGE("SystemFunctionManager::getScreenRotation() failed!");
	        return -1;
	    }

	    JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

	    jint rotation = lEnv->CallIntMethod(stSFJava, MethodGetScreenRatation);

	    return (int)rotation;

}

std::string SystemFunctionManager::getSdCardPath()
{
	if (!stSFJava)
	{
		LOGE("SystemFunctionManager::getSdCardPath() failed!");
		return "";
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

	//lEnv->CallObjectMethod(stSFJava, MethodGetSdCardPath);

	jstring path = static_cast<jstring>(lEnv->CallObjectMethod(stSFJava, MethodGetSdCardPath));
	if (path == NULL)
	{
		return "";
	}
	const char* pathchars = lEnv->GetStringUTFChars(path, NULL);
	string ret(pathchars);
	lEnv->ReleaseStringUTFChars(path, pathchars);
	return ret;

}
bool SystemFunctionManager::checkNetworkAvailable()
{
	if (!stSFJava)
	{
		LOGE("SystemFunctionManager::checkNetworkAvailable() failed!");
		return "";
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

	jboolean ret = lEnv->CallBooleanMethod(stSFJava, MethodCheckNetworkAvailable);
	return (ret == JNI_TRUE ? true : false);
}
bool SystemFunctionManager::isTabletAvailable()
{
	if (!stSFJava)
	{
		LOGE("SystemFunctionManager::isTabletAvailable() failed!");
		return "";
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

	jboolean ret = lEnv->CallBooleanMethod(stSFJava, MethodIsTabletAvailable);
	return (ret == JNI_TRUE ? true : false);
}
float SystemFunctionManager::densityScale()
{
	if (!stSFJava)
	{
		LOGE("SystemFunctionManager::densityScale() failed!");
		return 0;
	}
	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();
	jfloat f = lEnv->CallFloatMethod(stSFJava, MethodDensityScale);
	return (float) f;
}
void SystemFunctionManager::rateUs(){
	if (!stSFJava)
		{
			LOGE("SystemFunctionManager::rateUs() failed!");
			return;
		}

		JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

		lEnv->CallVoidMethod(stSFJava, MethodRateUs);
}
void SystemFunctionManager::dismissRateUs(){
//	if (!stSFJava)
//		{
//			LOGE("SystemFunctionManager::dismissRateUs() failed!");
//			return;
//		}
//
//		JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();
//
//		lEnv->CallVoidMethod(stSFJava, MethodDismissRateus);
}

void SystemFunctionManager::doNewsBlast(){
    if (!stSFJava)
    {
        LOGE("SystemFunctionManager::doNewsBlast() failed!");
        return;
    }

    LOGE("%s %s", __FILE__, __FUNCTION__);
    JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

    lEnv->CallVoidMethod(stSFJava, MethodNewsBlast);
}

void SystemFunctionManager::endAnalytics()
{
    if (!stSFJava)
    {
        LOGE("SystemFunctionManager::%s() failed!", __FUNCTION__);
        return;
    }
    LOGE("%s %s", __FILE__, __FUNCTION__);
    JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

    lEnv->CallVoidMethod(stSFJava, MethodEndAnalytics);
}

void SystemFunctionManager::refreshDCIM(std::string sFileDir)
{
    if (!stSFJava)
    {
        LOGE("SystemFunctionManager::%s() failed!", __FUNCTION__);
        return;
    }
    LOGE("%s %s", __FILE__, __FUNCTION__);
    JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();
    jstring msg = lEnv->NewStringUTF(sFileDir.c_str());
    lEnv->CallVoidMethod(stSFJava, MethodRefreshDCIM, msg);
}

SystemFunctionManager::~SystemFunctionManager()
{
	ST_JNI_Helper::deleteGlobalRef(ClassSF);
	ST_JNI_Helper::deleteGlobalRef(stSFJava);
}

//void SystemFunctionManager::setControlDelegate(IOSControlDelegate* delegate)
//{
//	pDelegate = delegate;
//}
//void SystemFunctionManager::cleanControlDelegate()
//{
//	pDelegate = 0;
//}

//void SystemFunctionManager::onRecieveSheetAction(int num)
//{
//	LOGE("%s %s --->onRecieveSheetAction, THE NUM is %d", __FILE__, __FUNCTION__, num);
//	if (pDelegate != 0){
//		pDelegate->onSheetAction(num);
//		LOGE("%s %s --->has RUN  onRecieveSheetAction", __FILE__, __FUNCTION__);
//	}
//}
//
//void SystemFunctionManager::onRecievePositiveAction()
//{
//	LOGE("%s %s --->onRecievePositiveAction", __FILE__, __FUNCTION__);
//	if (pDelegate != 0){
//		pDelegate->onPositiveClicked();
//		LOGE("%s %s --->>has RUN onRecievePositiveAction", __FILE__, __FUNCTION__);
//	}
//
//}
//
//void SystemFunctionManager::onRecieveNegativeAction()
//{
//	LOGE("%s %s --->onRecieveNegativeAction", __FILE__, __FUNCTION__);
//	if (pDelegate != 0){
//		pDelegate->onNegativeClicked();
//		LOGE("%s %s --->has RUN  onRecieveNegativeAction", __FILE__, __FUNCTION__);
//	}
//}

//SystemFunctionManager::~SystemFunctionManager()
//{
////	cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification("fsadf");
//	ST_JNI_Helper::deleteGlobalRef(ClassSF);
//	ST_JNI_Helper::deleteGlobalRef(stSFJava);
//}


