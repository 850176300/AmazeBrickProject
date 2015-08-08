//
//  WechatManager.cpp
//  AmazingBrick
//
//  Created by liuwei on 15/7/28.
//
//

#include "WechatManager.h"
static WechatManager* sp_WechatManager = 0;

WechatManager* WechatManager::getInstance(){
    if (!sp_WechatManager)
    {
        sp_WechatManager = new WechatManager();
    }

    return sp_WechatManager;
}


bool WechatManager::init(JNIEnv * pEnv, jobject pJava) {
    LOGE("开始创建微信manager！ ");
    ClassSF = pEnv->GetObjectClass(pJava);
    if (!ClassSF)
    {
        LOGE("get GameSharing class Failed!");
        return false;
    }
    ClassSF = (jclass) ST_JNI_Helper::makeGlobalRef(pEnv, ClassSF);

    MethodShareToCircle = pEnv->GetMethodID(ClassSF, "shareToCircle", "(I)V");
    if (!MethodShareToCircle)
    {
        LOGE("get MethodShareToCircle id Failed!");
        return false;
    }

    MethodShareWithoutCircle = pEnv->GetMethodID(ClassSF, "shareWithouCircle", "(I)V");
    if (!MethodShareWithoutCircle)
    {
        LOGE("get MethodShareWithoutCircle id Failed!");
        return false;
    }

    stSFJava = ST_JNI_Helper::makeGlobalRef(pEnv, pJava);
    if (!stSFJava)
    {
        LOGE("Cache stSFJava Failed!");
        return false;
    }

    LOGE("创建微信manager成功！！ ");
    return true;
}


void WechatManager::sharetoCircle(int score) {
    if (!stSFJava)
    {
        LOGE("WechatManager::sharetoCircle() failed!");
        return;
    }
    JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();
    lEnv->CallVoidMethod(stSFJava, MethodShareToCircle, score);
    LOGE("WechatManager::sharetoCircle() 成功!");
}

void WechatManager::shareWithoutCircle(int score){
    if (!stSFJava)
    {
        LOGE("WechatManager::shareWithoutCircle() failed!");
        return;
    }
    JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();
    lEnv->CallVoidMethod(stSFJava, MethodShareWithoutCircle, score);
    LOGE("WechatManager::shareWithoutCircle() 成功!");
}


