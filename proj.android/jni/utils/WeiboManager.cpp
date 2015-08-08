//
//  WeiboManager.cpp
//  AmazingBrick
//
//  Created by liuwei on 15/7/26.
//
//

#include "WeiboManager.h"

static WeiboManager* sp_WeiboManager = 0;

WeiboManager* WeiboManager::getInstance(){
    if (!sp_WeiboManager)
    {
        sp_WeiboManager = new WeiboManager();
    }
    
    return sp_WeiboManager;
}


bool WeiboManager::init(JNIEnv * pEnv, jobject pJava) {
    LOGE("开始创建微博manager！ ");
    ClassSF = pEnv->GetObjectClass(pJava);
    if (!ClassSF)
    {
        LOGE("get GameSharing class Failed!");
        return false;
    }
    ClassSF = (jclass) ST_JNI_Helper::makeGlobalRef(pEnv, ClassSF);
    
    MethodSendWeibo = pEnv->GetMethodID(ClassSF, "sendWeibo", "(I)V");
    if (!MethodSendWeibo)
    {
        LOGE("get MethodSendWeibo id Failed!");
        return false;
    }
    
    stSFJava = ST_JNI_Helper::makeGlobalRef(pEnv, pJava);
    if (!stSFJava)
    {
        LOGE("Cache stSFJava Failed!");
        return false;
    }

    LOGE("创建微博manager成功！！ ");
    return true;
}


void WeiboManager::sendWeibo(int score) {
    if (!stSFJava)
    {
        LOGE("WeiboManager::sendWeibo() failed!");
        return;
    }
    JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();
    lEnv->CallVoidMethod(stSFJava, MethodSendWeibo, score);
    LOGE("WeiboManager::sendWeibo() 成功!");
}
