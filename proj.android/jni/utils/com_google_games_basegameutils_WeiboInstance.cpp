#include "com_google_games_basegameutils_WeiboInstance.h"
#include "WeiboManager.h"

JNIEXPORT void JNICALL Java_com_google_games_basegameutils_WeiboInstance_nativeInit
(JNIEnv *pEnv, jobject jObj){
	WeiboManager::getInstance()->init(pEnv, jObj);
}
