/*
GameSharing.h

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
#ifndef __GameSharing__
#define __GameSharing__

#include <iostream>
#include "cocos2d.h"

#include "ST_JNI_Helper.h"


class GameSharing{
public:
	
	GameSharing():		
			ClassSF(0),
			stSFJava(0),
			MethodSubmitScore(0),
			MethodShowLeaderboards(0),
			MethodOpenAchivement(0),
			MethodUpdateAchivement(0),
			MethodShowAchievementsUI(0),
			MethodExitGame(0),
			MethodIsGPGAvailable(0),
			MethodRequestCurrentScore(0),
			MethodCallFunc(0),
			MethodopenLeaderboardUI(0){
				bIsGPGAvailable = true;
				wasGPGAvailableCalled = false;
				errorHandler = nullptr;
				localPlayerScore = -1;
				requestIsBeingProcessed = false;
				requestCallback = nullptr;
			}
		
	static GameSharing* getInstance();
	
    bool initGameSharing(JNIEnv * pEnv, jobject pJava);
	
	void callThefunction(int score);

    void SubmitScore(int score,int leaderboardId = 0);

    void ShowLeaderboards(int leaderbaordID = 0);

    void UnlockAchivement(int ID);

    void ShowAchievementsUI();

    void ExitGame();

    bool IsGPGAvailable();

    void SetErrorHandler(std::function<void()> handler);

    void ActivateStdErrorHandler();

    void RequestCurrentScoreFromLeaderboard(int leaderboardID,std::function<void(int)> callback = NULL);
	
private:
    std::function<void(int)> requestCallback;
	std::function<void()> errorHandler;
    bool wasGPGAvailableCalled;
    bool bIsGPGAvailable;
    int localPlayerScore;
    bool requestIsBeingProcessed;
	//method id
	jclass ClassSF;
	// Cached java object
	jobject stSFJava;
	// Cached active Methods.
	jmethodID MethodSubmitScore;
	jmethodID MethodShowLeaderboards;
	jmethodID MethodopenLeaderboardUI;
	jmethodID MethodOpenAchivement;
	jmethodID MethodUpdateAchivement;
	jmethodID MethodShowAchievementsUI;
	jmethodID MethodExitGame;
	jmethodID MethodIsGPGAvailable;
	jmethodID MethodRequestCurrentScore;
	jmethodID MethodCallFunc;
    
};

#endif
