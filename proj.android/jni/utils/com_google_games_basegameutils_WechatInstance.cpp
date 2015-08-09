#include "com_google_games_basegameutils_WechatInstance.h"
#include "WechatManager.h"
JNIEXPORT void JNICALL Java_com_google_games_basegameutils_WechatInstance_nativeInit
(JNIEnv *pEnv, jobject pObj){
	WechatManager::getInstance()->init(pEnv, pObj);
}

