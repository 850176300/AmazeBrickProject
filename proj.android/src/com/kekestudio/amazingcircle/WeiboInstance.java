package com.kekestudio.amazingcircle;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.widget.Toast;
import cn.afterwind.gamecenter.until.Constants;

import com.sina.weibo.sdk.api.ImageObject;
import com.sina.weibo.sdk.api.TextObject;
import com.sina.weibo.sdk.api.WeiboMultiMessage;
import com.sina.weibo.sdk.api.share.BaseResponse;
import com.sina.weibo.sdk.api.share.IWeiboHandler;
import com.sina.weibo.sdk.api.share.IWeiboShareAPI;
import com.sina.weibo.sdk.api.share.SendMultiMessageToWeiboRequest;
import com.sina.weibo.sdk.api.share.WeiboShareSDK;
import com.sina.weibo.sdk.auth.AuthInfo;
import com.sina.weibo.sdk.auth.Oauth2AccessToken;
import com.sina.weibo.sdk.auth.WeiboAuthListener;
import com.sina.weibo.sdk.auth.sso.SsoHandler;
import com.sina.weibo.sdk.constant.WBConstants;
import com.sina.weibo.sdk.exception.WeiboException;

public class WeiboInstance implements IWeiboHandler.Response{

	private static WeiboInstance mInstance = null;
	private Context mContext = null;
    private AuthInfo mAuthInfo;
    
    /** 封装了 "access_token"，"expires_in"，"refresh_token"，并提供了他们的管理功能  */
    private Oauth2AccessToken mAccessToken;

    /** 注意：SsoHandler 仅当 SDK 支持 SSO 时有效 */
    private SsoHandler mSsoHandler;
    private IWeiboShareAPI  mWeiboShareAPI = null;
    
	public static WeiboInstance getInstance() {
		return mInstance;
	}
	
	public static void setup(final Context context) {
		if (mInstance == null) {
			mInstance = new WeiboInstance(context);
		}
	}
	
	private WeiboInstance(Context context) {
		mContext = context;
	    mWeiboShareAPI = WeiboShareSDK.createWeiboAPI(mContext, Constants.APP_KEY);
	    mWeiboShareAPI.registerApp();
	    nativeInit();
	}
	
	public void handleRespone(Intent intent){
		mWeiboShareAPI.handleWeiboResponse(intent, this);
	}
	
	public void authWeibo(){//两种认证方式，首选微博客户端，如果客户端没有装，就选择用网页登陆
//		if (AccessTokenKeeper.readAccessToken((Activity)mContext) != null) {
//			return;
//		}
        mAuthInfo = new AuthInfo(mContext, Constants.APP_KEY, Constants.REDIRECT_URL, Constants.SCOPE);
        mSsoHandler = new SsoHandler((Activity)mContext, mAuthInfo);
        mSsoHandler.authorize(new AuthListener());
	}
	
	public void sendWeibo(int score){
		Log.e("AmazingCircle", "分享微博到新浪微博！！");
		WeiboMultiMessage weiboMessage = new WeiboMultiMessage();
		TextObject textObject = new TextObject();
        String text = mContext.getString(R.string.share_text);
        String mtextString = String.format(text, score);
        textObject.text = mtextString;
        weiboMessage.textObject = textObject;
        
        ImageObject imageObject = new ImageObject();
        FileHelper helper = new FileHelper(mContext);
        Bitmap bitmap = helper.readImage("amazingcircle/temp.png");
        if (bitmap != null) {
            imageObject.setImageObject(bitmap);
            weiboMessage.imageObject = imageObject;
		}


        // 2. 初始化从第三方到微博的消息请求
        SendMultiMessageToWeiboRequest request = new SendMultiMessageToWeiboRequest();
        // 用transaction唯一标识一个请求
        request.transaction = String.valueOf(System.currentTimeMillis());
        request.multiMessage = weiboMessage;
        Log.e("WeiboException", "分享新浪微博");
        
        AuthInfo authInfo = new AuthInfo(mContext, Constants.APP_KEY, Constants.REDIRECT_URL, Constants.SCOPE);
        Oauth2AccessToken accessToken = AccessTokenKeeper.readAccessToken(mContext.getApplicationContext());
        String token = "";
        if (accessToken != null) {
            token = accessToken.getToken();
        }
        mWeiboShareAPI.sendRequest((Activity)mContext, request, authInfo, token, new WeiboAuthListener() {
            
            @Override
            public void onWeiboException( WeiboException arg0 ) {
            	Log.e("WeiboException", arg0.toString());
            }
            
            @Override
            public void onComplete( Bundle bundle ) {
                // TODO Auto-generated method stub
                Oauth2AccessToken newToken = Oauth2AccessToken.parseAccessToken(bundle);
                AccessTokenKeeper.writeAccessToken(mContext.getApplicationContext(), newToken);
                Toast.makeText(mContext.getApplicationContext(), "onAuthorizeComplete token = " + newToken.getToken(), 0).show();
            }
            
            @Override
            public void onCancel() {
            	
            }
        });
	}
	
	
    /**
     * 微博认证授权回调类。
     * 1. SSO 授权时，需要在 {@link #onActivityResult} 中调用 {@link SsoHandler#authorizeCallBack} 后，
     *    该回调才会被执行。
     * 2. 非 SSO 授权时，当授权结束后，该回调就会被执行。
     * 当授权成功后，请保存该 access_token、expires_in、uid 等信息到 SharedPreferences 中。
     */
    class AuthListener implements WeiboAuthListener {
        
        @Override
        public void onComplete(Bundle values) {
            // 从 Bundle 中解析 Token
            mAccessToken = Oauth2AccessToken.parseAccessToken(values);
            //从这里获取用户输入的 电话号码信息 
            String  phoneNum =  mAccessToken.getPhoneNum();
            if (mAccessToken.isSessionValid()) {
                AccessTokenKeeper.writeAccessToken(mContext, mAccessToken);
            } else {
                String code = values.getString("code");
                String message = "验证失败：";
                if (!TextUtils.isEmpty(code)) {
                    message = message + "\nObtained the code: " + code;
                }
                Toast.makeText((Activity)mContext, message, Toast.LENGTH_LONG).show();
            }
        }

        @Override
        public void onCancel() {
        	
        }

        @Override
        public void onWeiboException(WeiboException e) {

        }
    }


	@Override
	public void onResponse(BaseResponse arg0) {
		// TODO Auto-generated method stub
        switch (arg0.errCode) {
        case WBConstants.ErrorCode.ERR_OK:
        	Log.e("onResponse", "分享成功");
            Toast.makeText(mContext, "分享成功", Toast.LENGTH_LONG).show();
            break;
        case WBConstants.ErrorCode.ERR_CANCEL:
        	Log.e("onResponse", "取消分享");
            Toast.makeText(mContext, "取消分享", Toast.LENGTH_LONG).show();
            break;
        case WBConstants.ErrorCode.ERR_FAIL:
        	Log.e("onResponse", "分享失败");
            Toast.makeText(mContext, 
                    "分享失败" + "Error Message: " + arg0.errMsg, 
                    Toast.LENGTH_LONG).show();
            break;
        }
	}
	
	private native void nativeInit();
	
}
