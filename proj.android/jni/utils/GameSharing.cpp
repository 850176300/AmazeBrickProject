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


static GameSharing* sp_GameSharing = 0;

GameSharing* GameSharing::getInstance(){
	if (!sp_GameSharing)
	{
		sp_GameSharing = new GameSharing();
	}

	return sp_GameSharing;
}


bool GameSharing::initGameSharing(JNIEnv * pEnv, jobject pJava){
	ClassSF = pEnv->GetObjectClass(pJava);
	if (!ClassSF)
	{
		LOGE("get GameSharing class Failed!");
		return false;
	}
	ClassSF = (jclass) ST_JNI_Helper::makeGlobalRef(pEnv, ClassSF);
	
	
	MethodCallFunc = pEnv->GetMethodID(ClassSF, "collectScore", "()I");
	if (!MethodCallFunc)
	{
		LOGE("get MethodCallFunc id Failed!");
		return false;
	}
	
	
	MethodSubmitScore = pEnv->GetMethodID(ClassSF, "submitScoreToLeaderboard", "(I)V");
	if (!MethodSubmitScore)
	{
		LOGE("get MethodSubmitScore id Failed!");
		return false;
	}
	
	MethodShowLeaderboards = pEnv->GetMethodID(ClassSF, "openLeaderboard", "(I)V");
	if (!MethodShowLeaderboards)
	{
		LOGE("get MethodShowLeaderboards id Failed!");
		return false;
	}
	
	MethodopenLeaderboardUI = pEnv->GetMethodID(ClassSF, "openLeaderboardUI", "()V");
	if (!MethodopenLeaderboardUI)
	{
		LOGE("get MethodopenLeaderboardUI id Failed!");
		return false;
	}
	
	MethodOpenAchivement = pEnv->GetMethodID(ClassSF, "openAchievement", "(I)V");
	if (!MethodOpenAchivement)
	{
		LOGE("get MethodOpenAchivement id Failed!");
		return false;
	}
	
	MethodUpdateAchivement = pEnv->GetMethodID(ClassSF, "updateAchievement", "(I)V");
	if (!MethodUpdateAchivement)
	{
		LOGE("get MethodUpdateAchivement id Failed!");
		return false;
	}
	
	MethodShowAchievementsUI = pEnv->GetMethodID(ClassSF, "showAchievements", "()V");
	if (!MethodShowAchievementsUI)
	{
		LOGE("get MethodShowAchievementsUI id Failed!");
		return false;
	}
	
	
	MethodExitGame = pEnv->GetMethodID(ClassSF, "exitGame", "()V");
	if (!MethodExitGame)
	{
		LOGE("get MethodExitGame id Failed!");
		return false;
	}
	
	MethodIsGPGAvailable = pEnv->GetMethodID(ClassSF, "isGPGSupported", "()Z");
	if (!MethodIsGPGAvailable)
	{
		LOGE("get MethodIsGPGAvailable id Failed!");
		return false;
	}
	
	MethodRequestCurrentScore = pEnv->GetMethodID(ClassSF, "requestScoreFromLeaderboard", "()V");
	if (!MethodRequestCurrentScore)
	{
		LOGE("get MethodRequestCurrentScore id Failed!");
		return false;
	}
	
	
	
	stSFJava = ST_JNI_Helper::makeGlobalRef(pEnv, pJava);
	if (!stSFJava)
	{
		LOGE("Cache stSFJava Failed!");
		return false;
	}
	
	return true;
	
}

void GameSharing::SubmitScore(int score,int leaderboardID)
{
	if (!stSFJava)
	{
		LOGE("GameSharing::SubmitScore() failed!");
		return;
	}
	
    if(IsGPGAvailable()){
		JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

		lEnv->CallVoidMethod(stSFJava, MethodShowLeaderboards, leaderboardID);

		lEnv->CallVoidMethod(stSFJava, MethodSubmitScore, score);
    }
}

void GameSharing::callThefunction(int score){
	if (requestCallback != nullptr){
		requestCallback(score);
	}
}

void GameSharing::ShowLeaderboards(int id){

	if (!stSFJava)
	{
		LOGE("GameSharing::UnlockAchivement() failed!");
		return;
	}
    if(IsGPGAvailable()){		
		JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

		lEnv->CallVoidMethod(stSFJava, MethodShowLeaderboards, id);

		lEnv->CallVoidMethod(stSFJava, MethodopenLeaderboardUI);
    }
    else{
        //Call the user defined error handler.
        errorHandler();
    }

}

void GameSharing::UnlockAchivement(int ID)
{
	if (!stSFJava)
	{
		LOGE("GameSharing::UnlockAchivement() failed!");
		return;
	}
	
    if(IsGPGAvailable())
    {
		JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

		lEnv->CallVoidMethod(stSFJava, MethodOpenAchivement, ID);

		lEnv->CallVoidMethod(stSFJava, MethodUpdateAchivement, ID);
	
	
    }
    else{
        errorHandler();
    }

}

void GameSharing::ShowAchievementsUI(){

	if (!stSFJava)
	{
		LOGE("GameSharing::ShowAchievementsUI() failed!");
		return;
	}

    if(IsGPGAvailable()){

		JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

		lEnv->CallVoidMethod(stSFJava, MethodShowAchievementsUI);
    }
    else{
        errorHandler();
    }

}

bool GameSharing::IsGPGAvailable(){
	if (!stSFJava)
	{
		LOGE("GameSharing::IsGPGAvailable() failed!");
		return "";
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

	jboolean ret = lEnv->CallBooleanMethod(stSFJava, MethodIsGPGAvailable);
	return (ret == JNI_TRUE ? true : false);

}

void GameSharing::ExitGame(){

	if (!stSFJava)
	{
		LOGE("GameSharing::ExitGame() failed!");
		return;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

	lEnv->CallVoidMethod(stSFJava, MethodExitGame);

}


void GameSharing::ActivateStdErrorHandler(){

	LOGE("get ActivateStdErrorHandler id Failed!!!!!!!!!");
    if (errorHandler != nullptr) {
    	errorHandler();
    }

}

void GameSharing::RequestCurrentScoreFromLeaderboard(int leaderboardID,std::function<void(int)> callback)
{
	if (!stSFJava)
	{
		LOGE("GameSharing::RequestCurrentScoreFromLeaderboard() failed!");
		return;
	}
	
	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

	lEnv->CallVoidMethod(stSFJava, MethodShowLeaderboards, leaderboardID);//绗�涓�姝ュ�����寮����琛�姒�
	
	lEnv->CallVoidMethod(stSFJava, MethodRequestCurrentScore);
	
    requestIsBeingProcessed = true;

    if(callback)
    {
        requestCallback = callback;
    }
}

void GameSharing::SetErrorHandler(std::function<void ()> handler){
    errorHandler = handler;
}
