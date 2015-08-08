//
//  WechatManager.h
//  AmazingBrick
//
//  Created by liuwei on 15/7/28.
//
//

#ifndef __AmazingBrick__WechatManager__
#define __AmazingBrick__WechatManager__

#include <iostream>
#include "ST_JNI_Helper.h"

using namespace std;

class WechatManager{

public:
	WechatManager():MethodShareToCircle(0),MethodShareWithoutCircle(0){

    }

    static WechatManager* getInstance();

    bool init(JNIEnv * pEnv, jobject pJava);
    void sharetoCircle(int score);
    void shareWithoutCircle(int score);


private:
    jclass ClassSF;
    // Cached java object
    jobject stSFJava;

    jmethodID MethodShareToCircle;
    jmethodID MethodShareWithoutCircle;
};
#endif /* defined(__AmazingBrick__WechatManager__) */
