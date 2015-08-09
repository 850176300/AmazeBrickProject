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
package com.kekestudio.jumpcircle;

import android.app.ActionBar.LayoutParams;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import cn.afterwind.gamecenter.until.Constants;

import com.common.android.PlatformCode;
import com.common.android.jni.STMopubAds;
import com.common.android.jni.STMopubAds.STAmazonAdSize;
import com.common.android.jni.STSystemFunction;
import com.common.android.utils.Utils;
import com.google.games.basegameutils.BaseGameActivity;
import com.google.games.basegameutils.LeaderBoardManager;
import com.google.games.basegameutils.WechatInstance;
import com.google.games.basegameutils.WeiboInstance;

public class AppActivity extends BaseGameActivity {

    
    public static boolean gpgAvailable;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		/**此段id，可以直接复制，无须重新创建*/
		Constants.LEADERBOARDLAYOUT_ID = R.layout.share;
		Constants.LEADERBOARDDELETEBTN_ID = R.id.img_delete;
		Constants.LEADERBOARDTEXT1_ID = R.id.txt_t0;
		Constants.LEADERBOARDTEXT2_ID = R.id.txt_t1;
		Constants.LEADERBOARDVIEWPAPER_ID = R.id.viewpager;
		
		Constants.RANKFRAMELAYOUT_ID = R.layout.shareframe;
		Constants.RANKFRAMEQQBTN_ID = R.id.lin_wechat;
		Constants.RANKFRAMESINABTN_ID = R.id.lin_sina;
		Constants.RANKFRAMESCROLL_ID = R.id.scrollview;
		
		/**下面id为每个项目需要重新配置的id，需要在此处配置*/
		Constants.APP_KEY = "3976624372";
		Constants.WX_APP_KEY = "wxdae67bd991dae536";
		Constants.LB_SECRET_KEY = getApplicationContext().getPackageName();
		Constants.QQ_APP_ID = "1104802480";
		
		setupNativeEnvironment();
		
		setPlatformCode(getPlatformCode());
		
		LeaderBoardManager.setup(this);
		
		STMopubAds.setup(this, true);	

		if (STSystemFunction.getInstance().isSupportGoogle() == false) {
			WeiboInstance.setup(this);
			if (savedInstanceState != null) {
				WeiboInstance.getInstance().handleRespone(getIntent());
			}
			WechatInstance.setup(this);
		}
		
		
		STMopubAds.getInstance().setAmazonSizeType(STAmazonAdSize.SIZE_600x90,
				STAmazonAdSize.SIZE_320x50);
		// ????????????Banner???????????????
		if (Utils.isTablet(this))
			STMopubAds.getInstance().setBannnerAdViewLayoutParams(
					LayoutParams.MATCH_PARENT, 90,
					Gravity.CENTER | Gravity.BOTTOM);
		else
			STMopubAds.getInstance().setBannnerAdViewLayoutParams(
					LayoutParams.MATCH_PARENT, 50,
					Gravity.CENTER | Gravity.BOTTOM);
		
		//设置google play services是否可用
		LeaderBoardManager.getInstance().setGPGisAvailable(STSystemFunction.getInstance().isSupportGoogle());
	}
	
	@Override
	protected void onNewIntent(Intent intent) {
		// TODO Auto-generated method stub
		super.onNewIntent(intent);
		
		if (STSystemFunction.getInstance().isSupportGoogle() == false) {
			WeiboInstance.getInstance().handleRespone(intent);
			WechatInstance.getInstance().handleRespone(intent);
			Log.e("分享平台", "onNewIntent(Intent intent)");
		}
	}
	
	@Override
	public int getPlatformCode() {
		// TODO Auto-generated method stub
		return PlatformCode.GOOGLEPLAY;
	}

	@Override
	protected void init_RateUs() {
		// TODO Auto-generated method stub
		
	}
	
	@Override
	public boolean getDebugMode() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean enableEvent() {
		// TODO Auto-generated method stub
		return true;
	}
	
	@Override
	public void onSignInFailed() {
		// TODO Auto-generated method stub
		gpgAvailable = false;
		LeaderBoardManager.getInstance().setGPGisLogined(false);
		
	}
	@Override
	public void onSignInSucceeded() {
		// TODO Auto-generated method stub
		gpgAvailable = true;
		LeaderBoardManager.getInstance().setGPGisLogined(true);
	}

   
   

}
