#include "com_kekestudio_amazingcircle_AppActivity.h"
#include "GameSharing.h"

JNIEXPORT void JNICALL Java_com_kekestudio_amazingcircle_AppActivity_callCppCallback
  (JNIEnv *pEnv, jobject thisObj, jlong jScore){
	GameSharing::getInstance()->callThefunction((long)jScore);
}


JNIEXPORT void JNICALL Java_com_kekestudio_amazingcircle_AppActivity_nativeInit
(JNIEnv * pEnv, jobject thisObj){
	GameSharing::getInstance()->initGameSharing(pEnv, thisObj);
}

