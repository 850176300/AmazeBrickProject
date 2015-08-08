/*
 * STSystemFunction.cpp
 *
 *  Created on: 2013-9-2
 *      Author: Steven.Xc.Tian
 */
#include "STSystemFunction.h"
#include "ST_SystemFunction_Android.h"

STSystemFunction::STSystemFunction()
{
}
STSystemFunction::~STSystemFunction()
{
}

void STSystemFunction::sendEmail(const char* subject, const char* body)
{
	SystemFunctionManager::getInstance()->sendEmail(subject, body);
}

void STSystemFunction::popAlertDialog(const char* message)
{
	SystemFunctionManager::getInstance()->popAlertDialog(message);
}

void STSystemFunction::showMoreGame()
{
	SystemFunctionManager::getInstance()->showMoreGame();
}
void STSystemFunction::rating()
{
	SystemFunctionManager::getInstance()->rating();
}
void STSystemFunction::go2MarketDetail(std::string packagename)
{
	SystemFunctionManager::getInstance()->go2MarketDetail(packagename);
}
void STSystemFunction::contactUs()
	{
		SystemFunctionManager::getInstance()->contactUs();
	}

void STSystemFunction::sendEmailAndAssetPic(std::string subject, std::string message, std::string assetName)
	{
		SystemFunctionManager::getInstance()->sendEmailAndAssetPic(subject,message,assetName);
	}
void STSystemFunction::sendEmailAndFilePic(std::string subject, std::string message,std::string fileName)
{
	SystemFunctionManager::getInstance()->sendEmailAndFilePic(subject,message,fileName);

}
std::string STSystemFunction::getSdCardPath()
{
	return SystemFunctionManager::getInstance()->getSdCardPath();
}

bool STSystemFunction::checkNetworkAvailable()
{
	return SystemFunctionManager::getInstance()->checkNetworkAvailable();

}

bool STSystemFunction::isTabletAvailable()
{
	return SystemFunctionManager::getInstance()->isTabletAvailable();

}
float STSystemFunction::densityScale()
{
	return SystemFunctionManager::getInstance()->densityScale();
}
void STSystemFunction::makeToast(const char* message)
{

}

void STSystemFunction::rateUs(){
	SystemFunctionManager::getInstance()->rateUs();
}
void STSystemFunction::dismissRateUs(){
	SystemFunctionManager::getInstance()->dismissRateUs();
}

void STSystemFunction::saveImage(std::string fileCache,Ref* selector,CallFunction callback){
}

void STSystemFunction::goToPrivacy()
{

}

void STSystemFunction::showNewsBlast()
{
    CCLOG("%s", __func__);
    SystemFunctionManager::getInstance()->doNewsBlast();
}


void STSystemFunction::showNewsBlast(NewsBlastMode mode){
    SystemFunctionManager::getInstance()->doNewsBlast();
}

void STSystemFunction::endAnalytics()
{
    CCLOG("%s", __func__);
    SystemFunctionManager::getInstance()->endAnalytics();
}

void STSystemFunction::refreshDCIM(std::string sFileDir)
{
    CCLOG("%s", __func__);
    SystemFunctionManager::getInstance()->refreshDCIM(sFileDir);
}


int STSystemFunction::getScreenRotation(){



	return SystemFunctionManager::getInstance()->getScreenRotation();
}

bool STSystemFunction::getIsSupportGoogle(){

	return SystemFunctionManager::getInstance()->getIsSupportGoogle();
}

//void  STSystemFunction::setManagerDelegate(IOSControlDelegate* delegate)
//{
//	CCLOG("%s", __func__);
//	SystemFunctionManager::getInstance()->setControlDelegate(delegate);
//}

//void  STSystemFunction::cleanManagerDelegate()
//{
//	CCLOG("%s", __func__);
//	SystemFunctionManager::getInstance()->cleanControlDelegate();
//}
//
//void STSystemFunction::showSheetView(std::string itemString1, std::string itemString2, std::string itemString3)
//{
//	CCLOG("%s", __func__);
//	SystemFunctionManager::getInstance()->showSheetView(itemString1, itemString2, itemString3);
//}
//
//void STSystemFunction::showSheetView(std::string itemString1, std::string itemString2)
//{
//	CCLOG("%s", __func__);
//	SystemFunctionManager::getInstance()->showSheetView(itemString1, itemString2);
//}
//
//void STSystemFunction::showSheetView(std::string itemString1)
//{
//	CCLOG("%s", __func__);
//	SystemFunctionManager::getInstance()->showSheetView(itemString1);
//}
//
//void STSystemFunction::showAlertView(std::string itemString1, std::string itemString2, std::string itemString3, std::string itemString4)
//{
//	CCLOG("%s", __func__);
//	SystemFunctionManager::getInstance()->showAlertView(itemString1, itemString2, itemString3, itemString4);
//}


