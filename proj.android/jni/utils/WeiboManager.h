//
//  WeiboManager.h
//  AmazingBrick
//
//  Created by liuwei on 15/7/26.
//
//

#ifndef __AmazingBrick__WeiboManager__
#define __AmazingBrick__WeiboManager__

#include <iostream>
#include "ST_JNI_Helper.h"

using namespace std;

class WeiboManager{
    
public:
    WeiboManager():MethodSendWeibo(0){
        
    }
    
    static WeiboManager* getInstance();
    
    bool init(JNIEnv * pEnv, jobject pJava);
    void sendWeibo(int score);
    
    
private:
    jclass ClassSF;
    // Cached java object
    jobject stSFJava;
    
    jmethodID MethodSendWeibo;
};


#endif /* defined(__AmazingBrick__WeiboManager__) */
