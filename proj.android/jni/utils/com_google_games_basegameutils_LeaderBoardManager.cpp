#include "com_google_games_basegameutils_LeaderBoardManager.h"
#include "GameSharing.h"
JNIEXPORT void JNICALL Java_com_google_games_basegameutils_LeaderBoardManager_callCppCallback
  (JNIEnv *pEnv, jobject thisObj, jlong jScore){
	GameSharing::getInstance()->callThefunction((long)jScore);
}


JNIEXPORT void JNICALL Java_com_google_games_basegameutils_LeaderBoardManager_nativeInit
(JNIEnv * pEnv, jobject thisObj){
	GameSharing::getInstance()->initGameSharing(pEnv, thisObj);
}

