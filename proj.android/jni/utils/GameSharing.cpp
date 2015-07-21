/*
 GameSharing.cpp
 
 Copyright 2015 Adrian Dawid
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 
 
 Created by Adrian Dawid on 17.08.14.
 */



#include "GameSharing.h"

USING_NS_CC;

bool GameSharing::bIsGPGAvailable = true;
bool GameSharing::wasGPGAvailableCalled = false;
std::function<void()> GameSharing::errorHandler = nullptr;
int GameSharing::localPlayerScore = -1;
bool GameSharing::requestIsBeingProcessed = false;
std::function<void(int)> GameSharing::requestCallback = nullptr;




extern "C"
{
    JNIEXPORT void JNICALL Java_com_kekestudio_amazingcircle_AppActivity_callCppCallback(JNIEnv* env, jobject thiz);

};

JNIEXPORT void JNICALL Java_com_kekestudio_amazingcircle_AppActivity_callCppCallback(JNIEnv* env, jobject thiz)
{
    int newScore = 0;
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t
                                     , "com/kekestudio/amazingcircle/AppActivity"
                                     , "collectScore"
                                     , "()I"))
    {
        newScore = t.env->CallStaticIntMethod(t.classID, t.methodID);
    }
    GameSharing::localPlayerScore = newScore;
    GameSharing::requestIsBeingProcessed = false;
    if(GameSharing::requestCallback)
    {
          GameSharing::requestCallback(newScore);
    }

}


void GameSharing::initGameSharing(){
    
}

void GameSharing::SubmitScore(int score,int leaderboardID)
{
    if(IsGPGAvailable()){
        JniMethodInfo t;
        //Is the Java method org.cocos2dx.cpp.AppActivty.openLeaderboard available?
        if (JniHelper::getStaticMethodInfo(t
                                           , "com/kekestudio/amazingcircle/AppActivity"
                                           , "openLeaderboard"
                                           , "(I)V"))
        {
            //Call the method with the leaderboardID as parameter
            t.env->CallStaticVoidMethod(t.classID, t.methodID, leaderboardID);
            
        }
        //Is the Java method org.cocos2dx.cpp.AppActivty.submitScoreToLeaderboard available?
        if (JniHelper::getStaticMethodInfo(t
                                           , "com/kekestudio/amazingcircle/AppActivity"
                                           , "submitScoreToLeaderboard"
                                           , "(I)V"))
        {
            //Call the method, this actually uploads the score to the leaderboard.
            t.env->CallStaticVoidMethod(t.classID, t.methodID, score);
        }
    }
}

void GameSharing::ShowLeaderboards(int id){

    if(IsGPGAvailable()){
        JniMethodInfo t;
        //Is the Java method org.cocos2dx.cpp.AppActivty.openLeaderboard available?
        if (JniHelper::getStaticMethodInfo(t
                                           , "com/kekestudio/amazingcircle/AppActivity"
                                           , "openLeaderboard"
                                           , "(I)V"))
        {
            //Call the method, over the JNI.
            //This changes the current leaderboard ID to id.
            t.env->CallStaticVoidMethod(t.classID, t.methodID, id);
        }
        //Is the Java method org.cocos2dx.cpp.AppActivty.openLeaderboardUI available?
        if (JniHelper::getStaticMethodInfo(t
                                           , "com/kekestudio/amazingcircle/AppActivity"
                                           , "openLeaderboardUI"
                                           , "()V"))
        {
            //Call the method, this actually shows the UI.
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
        }
    }
    else{
        //Call the user defined error handler.
        errorHandler();
    }

}

void GameSharing::UnlockAchivement(int ID)
{

    if(IsGPGAvailable())
    {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t
                                           , "com/kekestudio/amazingcircle/AppActivity"
                                           , "openAchievement"
                                           , "(I)V"))
        {
            t.env->CallStaticVoidMethod(t.classID, t.methodID , ID);
        }
        JniMethodInfo tmp;
        if (JniHelper::getStaticMethodInfo(tmp
                                           , "com/kekestudio/amazingcircle/AppActivity"
                                           , "updateAchievement"
                                           , "(I)V"))
        {
            tmp.env->CallStaticVoidMethod(tmp.classID, tmp.methodID , 100);
        }
    }
    else{
        errorHandler();
    }

}

void GameSharing::ShowAchievementsUI(){

    if(IsGPGAvailable()){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t
                                           , "com/kekestudio/amazingcircle/AppActivity"
                                           , "showAchievements"
                                           , "()V"))
        {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
        }
    }
    else{
        errorHandler();
    }

}

bool GameSharing::IsGPGAvailable(){
    bool tmp = false;

    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t
                                       , "com/kekestudio/amazingcircle/AppActivity"
                                       , "isGPGSupported"
                                       , "()Z"))
    {
        tmp = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
    }

}

void GameSharing::ExitGame(){

    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t
                                       , "com/kekestudio/amazingcircle/AppActivity"
                                       , "exitGame"
                                       , "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
    }

}


void GameSharing::ActivateStdErrorHandler(){

    SetErrorHandler([]() -> void{
        MessageBox("A problem with Google Play Games was encountered.", "Error");
        return;
    });

}

void GameSharing::RequestCurrentScoreFromLeaderboard(int leaderboardID,std::function<void(int)> callback)
{

    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t
                                   , "com/kekestudio/amazingcircle/AppActivity"
                                   , "requestScoreFromLeaderboard"
                                   , "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
    }
    requestIsBeingProcessed = true;

    if(callback)
    {
        requestCallback = callback;
    }
}

void GameSharing::SetErrorHandler(std::function<void ()> handler){
    errorHandler = handler;
}
