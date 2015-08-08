#include "com_kekestudio_amazingcircle_WeiboInstance.h"
#include "WeiboManager.h"
JNIEXPORT void JNICALL Java_com_kekestudio_amazingcircle_WeiboInstance_nativeInit
  (JNIEnv *pEnv, jobject jObj){
  	WeiboManager::getInstance()->init(pEnv, jObj);
  }
