package com.google.games.basegameutils;

import cn.afterwind.gamecenter.entity.BaseEntity;
import cn.afterwind.gamecenter.until.Constants;
import cn.afterwind.gamecenter.view.LeaderboardActivity;

import com.google.android.gms.common.api.ResultCallback;
import com.google.android.gms.games.Games;
import com.google.android.gms.games.GamesStatusCodes;
import com.google.android.gms.games.leaderboard.LeaderboardVariant;
import com.google.android.gms.games.leaderboard.Leaderboards;
import com.kekestudio.amazingcircle.R;
import com.kelberos.develop.http.HttpResult;
import com.kelberos.develop.http.NetWork;
import com.kelberos.develop.http.TaskHandler;
import com.kelberos.develop.superclass.ParentParameter;
import com.kelberos.develop.utils.DateBaseSave;
import com.kelberos.develop.utils.JsonUtil;

import android.app.Activity;
import android.app.Application;
import android.content.Context;
import android.content.Intent;
import android.text.TextUtils;

public class LeaderBoardManager {
	private static LeaderBoardManager mInstance = null;
    private int currentID;
    private int currentAchievementID;
    private String[] leaderboardIDs;
    private String[] achievementIDs;
    private Context currentContext;
    private int currentScore;
    private boolean gpgAvailable = false;
    private boolean isgpgLogined = false;
	
	public static LeaderBoardManager getInstance(){
		return mInstance;
	}
	
	public static void setup(Context context){
		if (mInstance == null) {
		 	mInstance = new LeaderBoardManager(context);
		}
	}
	
	public void setGPGisAvailable(boolean isAvailable) {
		gpgAvailable = isAvailable;
	}
	
	public void setGPGisLogined(boolean isLogined){
		isgpgLogined = isLogined;
	}
	
	public boolean isGPGSupported(){
		return gpgAvailable;
	}
	
	private LeaderBoardManager(Context context) {
		currentContext = context;
		String leaderboardIdsRaw = currentContext.getString(R.string.leaderboard_up__up);
        String achievementIdsRaw = currentContext.getString(R.string.event_up__up_achievement);
        
        leaderboardIDs = leaderboardIdsRaw.split(";");
        achievementIDs =  achievementIdsRaw.split(";");
		nativeInit();
	}
	

   public void openLeaderboard(int leaderboardID){
        currentID = leaderboardID;
   }
   
   /*@brief This function opens the leaderboards ui for an leaderboard id*/
   public void openLeaderboardUI(){
	   
       if(gpgAvailable){
    	   if (isgpgLogined == false) return;
           ((Activity)currentContext).runOnUiThread(new Runnable() {
        	   public void run() {
        		   ((Activity)currentContext).startActivityForResult(Games.Leaderboards.getLeaderboardIntent(((BaseGameActivity)currentContext).getGameHelper().getApiClient(), leaderboardIDs[currentID]),2);
        	   }
           });
       }else {
    	   Intent intent = new Intent(currentContext, LeaderboardActivity.class);
    	   currentContext.startActivity(intent);
       }
   }
   
   /*@brief Submits a score to the leaderboard that is currently actvie*/
   public void submitScoreToLeaderboard(int score)
   {
       if(gpgAvailable){
    	   if (isgpgLogined == false) return;
    	   Games.Leaderboards.submitScore(((BaseGameActivity)currentContext).getGameHelper().getApiClient(),leaderboardIDs[currentID],score);
    	   currentScore = score;
       }else {
	    	String token = DateBaseSave.getStrInfo("token", currentContext);
	    	if(TextUtils.isEmpty(token)){
	    		return ;
	    	}
	    	
			ParentParameter p=new ParentParameter("/api/v1/leaderboard/upload_score");
			p.setParam(Constants.LB_SECRET_PARA, Constants.LB_SECRET_KEY);
			p.setParam("token", token);
			p.setParam("score", String.valueOf(score));
			
			NetWork.doPost(p, new TaskHandler() {
				
				@Override
				public void httpResult(HttpResult result) {
					if(result.isSuccess()){
						BaseEntity entity=JsonUtil.jsonToObject(result.response, BaseEntity.class);
						if(entity.isOK()){
//    							Toast.makeText(this, "分享成功", Toast.LENGTH_SHORT).show();
							android.util.Log.e("leaderboardmanager", "submit sorce succeed！！");
						}
					}else{
//    						Toast.makeText(this, "网络请求失败", Toast.LENGTH_SHORT).show();
						android.util.Log.e("leaderboardmanager", "submit sorce failed！！");
					}
				}
			});
       }
   }
   
   public void requestScoreFromLeaderboard()
   {
       if(gpgAvailable){
    	   if (isgpgLogined == false) return;
           Games.Leaderboards.loadCurrentPlayerLeaderboardScore(((BaseGameActivity)currentContext).getGameHelper().getApiClient(), leaderboardIDs[currentID], LeaderboardVariant.TIME_SPAN_ALL_TIME, LeaderboardVariant.COLLECTION_PUBLIC).setResultCallback(new ResultCallback<Leaderboards.LoadPlayerScoreResult>() {
               @Override
               public void onResult(final Leaderboards.LoadPlayerScoreResult scoreResult) {
                   if (scoreResult.getStatus().getStatusCode() == GamesStatusCodes.STATUS_OK) {
                       currentScore = (int)scoreResult.getScore().getRawScore();
                       callCppCallback(currentScore);
                   }
               }
           });
       }
   }

   public int collectScore()
   {
       return currentScore;
   }
   
    /*@brief Shows the achievements ui*/
   public void showAchievements() {
       if(gpgAvailable){
    	   if (isgpgLogined == false) return;
	       ((BaseGameActivity)currentContext).runOnUiThread(new Runnable() {
	           public void run() {
	               ((BaseGameActivity)currentContext).startActivityForResult(Games.Achievements.getAchievementsIntent(((BaseGameActivity)currentContext).getGameHelper().getApiClient()), 5);
	           }
	       });
       }
   }
   
   /*@brief Changes the actvie Achievement
 @param The index of the achievement in the list*/
   public void openAchievement(int achievementID){
       currentAchievementID = achievementID;
   }
   
   public void updateAchievement(int percentage){
       if(gpgAvailable){
    	   if (isgpgLogined == false) return;
    	   Games.Achievements.unlock(((BaseGameActivity)currentContext).getGameHelper().getApiClient(), achievementIDs[currentAchievementID]);
       }
   }
   
   public void exitGame()
   {
	   
   }
	
	   
	public native void callCppCallback(int score);
	public native void nativeInit();
	
}
