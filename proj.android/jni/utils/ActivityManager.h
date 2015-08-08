//
//  ActivityManager.h
//  AmazingBrick
//
//  Created by liuwei on 15/7/28.
//
//

#ifndef __AmazingBrick__ActivityManager__
#define __AmazingBrick__ActivityManager__

#include <iostream>
#include "ST_JNI_Helper.h"

using namespace std;

class ActivityManager{

public:
	ActivityManager():MethodExitGame(0){

    }

    static ActivityManager* getInstance();

    bool init(JNIEnv * pEnv, jobject pJava);
    void exitGame();


private:
    jclass ClassSF;
    // Cached java object
    jobject stSFJava;

    jmethodID MethodExitGame;
};

#endif /* defined(__AmazingBrick__ActivityManager__) */
