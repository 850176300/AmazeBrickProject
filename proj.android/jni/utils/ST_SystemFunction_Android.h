/*
 * ST_SystemFunction_Android.h
 *
 *  Created on: 2013-9-2
 *      Author: Steven.Xc.Tian
 */
#ifndef ST_SYSTEMFUNCTION_ANDROID_H_
#define ST_SYSTEMFUNCTION_ANDROID_H_

#include "ST_JNI_Helper.h"
//#include "IOSControlDelegate.h"
#include <string>
using namespace std;
class SystemFunctionManager
{
public:
	SystemFunctionManager() :
			ClassSF(0),
			stSFJava(0),
			MethodSendMailByIntent(0),
			MethodPopAlertDialog(0),
			MethodMakeToast(0),
			MethodShowMoreGame(0),
			MethodGo2MarketDetail(0),
			MethodRating(0),
			MethodContactUs(0),
			MethodSendEmailAndAssetPic(0),
			MethodSendEmailAndFilePic(0),
			MethodGetSdCardPath(0),
			MethodCheckNetworkAvailable(0),
			MethodIsTabletAvailable(0),
			MethodDensityScale(0),
			MethodRateUs(0),
            MethodDismissRateus(0),
            MethodNewsBlast(0),
            MethodRefreshDCIM(0),
            MethodGetScreenRatation(0)
//            MethodshowActionSheetOne(0),
//            MethodshowActionSheetTwo(0),
//            MethodshowActionSheetThree(0),
//            MethodshowAlertView(0)

	{
	}
	~SystemFunctionManager();

	static SystemFunctionManager* getInstance();

	static void destroy();

	bool init(JNIEnv * pEnv, jobject pJava);
//private:
//	IOSControlDelegate* pDelegate;
public:
//	void setControlDelegate(IOSControlDelegate* delegate);
//	void cleanControlDelegate();
	void sendEmail(const char* subject, const char* body);
	void popAlertDialog(const char* message);
	void makeToast(const char* message);
	void showMoreGame();
	void go2MarketDetail(std::string packagename);
	void rating();
	void contactUs();
	void sendEmailAndAssetPic(std::string subject, std::string message, std::string assetName);
	void sendEmailAndFilePic(std::string subject, std::string message,std::string fileName);
	std::string getSdCardPath();
	bool checkNetworkAvailable();
	bool isTabletAvailable();
	float densityScale();
	void rateUs();
	void dismissRateUs();
    void doNewsBlast();
    /*
     * �����������������������������������������������������������������PP������������������������������
     */
	void endAnalytics();
    void refreshDCIM(std::string sFileDir);
    int getScreenRotation();

//	void onRecieveSheetAction(int num);
//	void onRecievePositiveAction();
//	void onRecieveNegativeAction();

//	void showSheetView(std::string itemString1, std::string itemString2, std::string itemString3);
//	void showSheetView(std::string itemString1, std::string itemString2);
//	void showSheetView(std::string itemString1);
//	void showAlertView(std::string itemString1, std::string itemString2, std::string itemString3, std::string itemString4);

private:
	/*>>>>>>>> below declaration is used by jni <<<<<<<<*/
	// Cached Classes.
	jclass ClassSF;
	// Cached java object
	jobject stSFJava;
	// Cached active Methods.
	jmethodID MethodSendMailByIntent;
	jmethodID MethodPopAlertDialog;
	jmethodID MethodMakeToast;
	jmethodID MethodShowMoreGame;
	jmethodID MethodRating;
	jmethodID MethodGo2MarketDetail;
	jmethodID MethodContactUs;
	jmethodID MethodSendEmailAndAssetPic;
	jmethodID MethodSendEmailAndFilePic;
	jmethodID MethodGetSdCardPath;
	jmethodID MethodCheckNetworkAvailable;
	jmethodID MethodIsTabletAvailable;
	jmethodID MethodDensityScale;
	jmethodID MethodRateUs;
	jmethodID MethodDismissRateus;
    jmethodID MethodNewsBlast;
    jmethodID MethodEndAnalytics;
    jmethodID MethodRefreshDCIM;
    jmethodID MethodGetScreenRatation;
//    jmethodID MethodshowActionSheetOne;
//    jmethodID MethodshowActionSheetTwo;
//    jmethodID MethodshowActionSheetThree;
//    jmethodID MethodshowAlertView;
};

#endif /* ST_SYSTEMFUNCTION_ANDROID_H_ */
