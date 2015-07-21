//
//  ST_JNI_Helper.h
//  MysteryGuardians
//
//  Created by Steven.Xc.Tian on 13-6-25.
//
//

#ifndef __MysteryGuardians__ST_JNI_Helper__
#define __MysteryGuardians__ST_JNI_Helper__

#include <jni.h>
#include <android/log.h>

#define LOG_TAG "from jni"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

class ST_JNI_Helper {
public:
    ST_JNI_Helper(){}
    virtual ~ST_JNI_Helper();
    
    static ST_JNI_Helper* getInstance();
public:
    // Cached JNI references.
	static JavaVM* stJavaVM;
public:
	static JNIEnv* getJNIEnv();
	static jobject makeGlobalRef(JNIEnv* pEnv, jobject pRef);
	static jobject makeGlobalRef(jobject pRef);
	static void deleteGlobalRef(JNIEnv* pEnv, jobject pRef);
	static void deleteGlobalRef(jobject pRef);
public:
	virtual void init(JNIEnv* pEnv);
	virtual void finalize();
};

#endif /* defined(__MysteryGuardians__ST_JNI_Helper__) */
