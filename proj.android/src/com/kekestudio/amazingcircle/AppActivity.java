/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.kekestudio.amazingcircle;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;

import com.common.android.PlatformCode;
import com.google.android.gms.common.api.ResultCallback;
import com.google.android.gms.games.Games;
import com.google.android.gms.games.GamesStatusCodes;
import com.google.android.gms.games.leaderboard.LeaderboardVariant;
import com.google.android.gms.games.leaderboard.Leaderboards;
import com.google.games.basegameutils.BaseGameActivity;

public class AppActivity extends BaseGameActivity {
    static int currentID;
    static int currentAchievementID;
    static boolean gpgAvailable;
    
    static String[] leaderboardIDs;
    static String[] achievementIDs;
    static Context currentContext;
    
    static int currentScore;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		String leaderboardIdsRaw = getString(R.string.leaderboard_up__up);
        String achievementIdsRaw = getString(R.string.event_up__up_achievement);
        
        leaderboardIDs = leaderboardIdsRaw.split(";");
        achievementIDs =  achievementIdsRaw.split(";");
        
        currentContext = this;
		super.onCreate(savedInstanceState);
	}
	@Override
	public int getPlatformCode() {
		return PlatformCode.GOOGLEPLAY;
	}

	@Override
	public boolean getDebugMode() {
		return true;
	}

	@Override
	public boolean enableEvent() {
		return !getDebugMode();
	}
	
	@Override
	public void onSignInFailed() {
		// TODO Auto-generated method stub
		gpgAvailable = false;
	}
	@Override
	public void onSignInSucceeded() {
		// TODO Auto-generated method stub
		gpgAvailable = true;
	}
	
    static public void openLeaderboard(int leaderboardID){
        currentID = leaderboardID;
   }
   
   /*@brief This function opens the leaderboards ui for an leaderboard id*/
   static public void openLeaderboardUI(){
       if(gpgAvailable){
               ((AppActivity)currentContext).runOnUiThread(new Runnable() {
           public void run() {
               ((AppActivity)currentContext).startActivityForResult(Games.Leaderboards.getLeaderboardIntent(((AppActivity)currentContext).getGameHelper().getApiClient(), leaderboardIDs[currentID]),2);
           }
               });
       }
   }
   
   static public boolean isGPGSupported(){
       return gpgAvailable;
   }
   
   /*@brief Submits a score to the leaderboard that is currently actvie*/
   static public void submitScoreToLeaderboard(int score)
   {
       if(gpgAvailable){
       Games.Leaderboards.submitScore(((AppActivity)currentContext).getGameHelper().getApiClient(),leaderboardIDs[currentID],score);
       }
   }
   
   static public void requestScoreFromLeaderboard()
   {
       if(gpgAvailable){
           Games.Leaderboards.loadCurrentPlayerLeaderboardScore(((AppActivity)currentContext).getGameHelper().getApiClient(), leaderboardIDs[currentID], LeaderboardVariant.TIME_SPAN_ALL_TIME, LeaderboardVariant.COLLECTION_PUBLIC).setResultCallback(new ResultCallback<Leaderboards.LoadPlayerScoreResult>() {
               @Override
               public void onResult(final Leaderboards.LoadPlayerScoreResult scoreResult) {
                   if (scoreResult.getStatus().getStatusCode() == GamesStatusCodes.STATUS_OK) {
                       AppActivity.currentScore = (int)scoreResult.getScore().getRawScore();
                       AppActivity.callCppCallback();
                   }
               }
           });
       }
   }

   static public int collectScore()
   {
       return AppActivity.currentScore;
   }
   
    /*@brief Shows the achievements ui*/
   static public void showAchievements() {
       if(gpgAvailable){
       ((AppActivity)currentContext).runOnUiThread(new Runnable() {
           public void run() {
               ((AppActivity)currentContext).startActivityForResult(Games.Achievements.getAchievementsIntent(((AppActivity)currentContext).getGameHelper().getApiClient()), 5);
           }
       });
       }
   }
   
   /*@brief Changes the actvie Achievement
     @param The index of the achievement in the list*/
   static public void openAchievement(int achievementID){
       currentAchievementID = achievementID;
   }
   
   static public void updateAchievement(int percentage){
       if(gpgAvailable){
      Games.Achievements.unlock(((AppActivity)currentContext).getGameHelper().getApiClient(), achievementIDs[currentAchievementID]);
       }
   }
   
   static public void exitGame()
   {
       Intent intent = new Intent(currentContext, MainActivity.class);
       MainActivity.exiting=true;
       currentContext.startActivity(intent);
   }
   
   static public native void callCppCallback();
}
