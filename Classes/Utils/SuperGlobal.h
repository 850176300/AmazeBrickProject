
//
//  SuperGlobal.h
//  DND2052_Baby_Play_Town
//
//  Created by liuwei on 14-12-25.
//
//

#ifndef DND2052_Baby_Play_Town_SuperGlobal_h
#define DND2052_Baby_Play_Town_SuperGlobal_h

#include <iostream>
#include "cocos2d.h"
#include "HomeScene.h"
#include "STFileUtility.h"
#include "Box2dLayer.h"
#include "FinishScene.h"
using namespace std;
USING_NS_CC;

inline string LocalizeString(const string& str);
string LocalizeString(const string& str){
    LanguageType currentType = Application::getInstance()->getCurrentLanguage();
    string temp = string(str);
    if (currentType == LanguageType::ENGLISH) {
        string en = temp.replace(str.size() - 4, str.size() - 1, "_en.png");
        if (STFileUtility::isFileExist(FileUtils::getInstance()->fullPathForFilename(en))) {
            return en;
        }
    }else if (currentType == LanguageType::CHINESE){
        string zh = temp.replace(str.size() - 4, str.size() - 1, "_zh.png");
        if (STFileUtility::isFileExist(FileUtils::getInstance()->fullPathForFilename(zh))) {
            return zh;
        }
    }
    return str;

}


template<typename T> void replaceTheScene() {
    Scene* targetScene = T::scene();
    auto pScene=TransitionFade::create(1, targetScene);
    if (Director::getInstance()->getRunningScene()) {
        Director::getInstance()->replaceScene(pScene);
    }else {
        Director::getInstance()->runWithScene(pScene);
    }
}

template<typename T> void pushTheScene() {
    Scene* targetScene = T::scene();
    auto pScene=TransitionFade::create(1, targetScene);
    if (Director::getInstance()->getRunningScene()) {
        Director::getInstance()->pushScene(pScene);
    }else {
        Director::getInstance()->runWithScene(pScene);
    }
}

inline string convertIntToString(int num);
string convertIntToString(int num){
    __String* tempString = __String::createWithFormat("%d", num);
    stringstream ss;
    ss<<tempString->getCString();
    return ss.str();
}
enum ALLItemOrder{
    kHomeBtn = 100,
    kPrompt,
    kDialog,
    
    kHomeDialog,
    kBackDialog,
    
    kLockTags = 120125,
};

#define IAPCOUTNS 6
#define DealAllIAP string("net.babyandmommy.ponyoutdoor.bestdeal")
#define MoreBabyIAP string("net.babyandmommy.ponyoutdoor.unlockallponies")
#define MazeGameIAP string("net.babyandmommy.ponyoutdoor.unlockfariytaleforest")
#define GoldCoaseIAP string("net.babyandmommy.ponyoutdoor.unlockgoldcoast")
#define RemoveADIAP string("net.babyandmommy.ponyoutdoor.noads")
#define UnlockallIAP string("net.babyandmommy.ponyoutdoor.unlockall")


#define BackGroundEvent "BackGroundEvent"
#define PURCHASESUCCEED "PurchaseSucceed"

#define kUnlockModel1 "eric"
#define kUnlockModel2 "danny"
#define kUnlockModel3 "sara"


#define kPuaseGame "pause"
#define kResumeGame "resume"
#define kLightOnOff "LightOnOff"
#define kPuaseTip "pauseTip"
#define kResumeTip "resumeTip"
#endif
