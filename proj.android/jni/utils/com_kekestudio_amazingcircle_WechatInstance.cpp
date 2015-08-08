#include "com_kekestudio_amazingcircle_WechatInstance.h"
#include "WechatManager.h"

JNIEXPORT void JNICALL Java_com_kekestudio_amazingcircle_WechatInstance_nativeInit
  (JNIEnv *pEnv, jobject pObj){
	WechatManager::getInstance()->init(pEnv, pObj);
}

