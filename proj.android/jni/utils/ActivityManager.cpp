//
//  ActivityManager.cpp
//  AmazingBrick
//
//  Created by liuwei on 15/7/28.
//
//

#include "ActivityManager.h"
static ActivityManager* sp_ActivityManager = 0;

ActivityManager* ActivityManager::getInstance(){
    if (!sp_ActivityManager)
    {
        sp_ActivityManager = new ActivityManager();
    }

    return sp_ActivityManager;
}


bool ActivityManager::init(JNIEnv * pEnv, jobject pJava) {
    LOGE("开始创建activitymanager！ ");
    ClassSF = pEnv->GetObjectClass(pJava);
    if (!ClassSF)
    {
        LOGE("get GameSharing class Failed!");
        return false;
    }
    ClassSF = (jclass) ST_JNI_Helper::makeGlobalRef(pEnv, ClassSF);

    MethodExitGame = pEnv->GetMethodID(ClassSF, "exitGame", "()V");
    if (!MethodExitGame)
    {
        LOGE("get MethodExitGame id Failed!");
        return false;
    }

    stSFJava = ST_JNI_Helper::makeGlobalRef(pEnv, pJava);
    if (!stSFJava)
    {
        LOGE("Cache stSFJava Failed!");
        return false;
    }

    LOGE("创建activitymanager成功！！ ");
    return true;
}


void ActivityManager::exitGame() {
    if (!stSFJava)
    {
        LOGE("ActivityManager::exitGame() failed!");
        return;
    }
    JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();
    lEnv->CallVoidMethod(stSFJava, MethodExitGame);
    LOGE("ActivityManager::exitGame() 成功!");
}
