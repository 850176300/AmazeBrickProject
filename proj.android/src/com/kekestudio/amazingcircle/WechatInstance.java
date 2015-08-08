package com.kekestudio.amazingcircle;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Bitmap.CompressFormat;
import android.util.Log;
import android.widget.Toast;
import cn.afterwind.gamecenter.until.Constants;

import com.tencent.mm.sdk.openapi.BaseReq;
import com.tencent.mm.sdk.openapi.BaseResp;
import com.tencent.mm.sdk.openapi.IWXAPI;
import com.tencent.mm.sdk.openapi.IWXAPIEventHandler;
import com.tencent.mm.sdk.openapi.SendMessageToWX;
import com.tencent.mm.sdk.openapi.WXAPIFactory;
import com.tencent.mm.sdk.openapi.WXImageObject;
import com.tencent.mm.sdk.openapi.WXMediaMessage;
import com.tencent.mm.sdk.openapi.WXTextObject;
import com.tencent.mm.sdk.openapi.WXWebpageObject;
import com.tencent.mm.sdk.platformtools.Util;

public class WechatInstance implements IWXAPIEventHandler{

	private static WechatInstance mInstance = null;
	private Context mContext = null;
	
    private static final int TIMELINE_SUPPORTED_VERSION = 0x21020001;
	private static final int ICON_SIZE = 150;
	private static final int IMAGE_SIZE = 150;
	private boolean isWXinstalled = true;
	private IWXAPI wxApi;
	
	public static WechatInstance getInstance() {
		return mInstance;
	}
	
	public static void setup(final Context context) {
		if (mInstance == null) {
			mInstance = new WechatInstance(context);
		}
	}
	
	private WechatInstance(Context context) {
		mContext = context;
		wxApi = WXAPIFactory.createWXAPI(mContext, Constants.WX_APP_KEY);
		isWXinstalled = wxApi.isWXAppInstalled();
		if (isWXinstalled == true) {
			wxApi.registerApp(Constants.WX_APP_KEY);
		}
		nativeInit();
	}
	
	public void handleRespone(Intent intent){
		wxApi.handleIntent(intent, this);
	}
	
	private void shareToCircle(int score){
		if (isWXinstalled == false) {
			error("您的手机未安装微信客户端，无法进行分享");
		}else {
			if (wxApi.isWXAppSupportAPI()) {
				int wxSdkVersion = wxApi.getWXAppSupportAPI();
				if (wxSdkVersion < TIMELINE_SUPPORTED_VERSION) {
					error("您的微信版本太低，不支持朋友圈分享");
					shareWithouCircle(score);
				}else {
					String text = mContext.getString(R.string.share_text);
					String message = String.format(text, score);
					Log.e("微信分享", "分享内容"+message);
					FileHelper helper = new FileHelper(mContext);
				    Bitmap bitmap = helper.readImage("amazingcircle/temp.png");
					send(mContext.getString(R.string.app_name), message,"http://www.wandoujia.com/apps/com.kekestudio.amazingcircle", bitmap, true);
				}
			}
		}
	}
	
	private void shareWithouCircle(int score){
		if (isWXinstalled == false) {
			error("您的手机未安装微信客户端，无法进行分享");
		}else {
			String text = mContext.getString(R.string.share_text);
			String message = String.format(text, score);
			FileHelper helper = new FileHelper(mContext);
		    Bitmap bitmap = helper.readImage("amazingcircle/temp.png");
			send(mContext.getString(R.string.app_name), message,"http://www.wandoujia.com/apps/com.kekestudio.amazingcircle", bitmap, true);
		}
	}
	
	/**
	 * 图片＋文字＋url分享
	 * 
	 * @param title
	 *            String 标题
	 * @param message
	 *            String 分享内容
	 * @param url
	 *            String 网址
	 * @param bmp
	 *            Bitmap 图片位图
	 * @param isCircle
	 *            boolean 是否是分享到朋友圈
	 */
	private void send(String title,String message,String url,Bitmap bmp,boolean isCircle){
		try {
			
			Bitmap thumbBmp = Bitmap.createScaledBitmap(bmp, ICON_SIZE, ICON_SIZE, true);
			
			WXWebpageObject webpage = new WXWebpageObject();
            webpage.webpageUrl = url;
            WXMediaMessage msg = new WXMediaMessage(webpage);
            msg.title = message;
//            msg.description = message;
            msg.thumbData = Util.bmpToByteArray(thumbBmp, true);
            
			SendMessageToWX.Req req = new SendMessageToWX.Req();
			
			req.transaction = String.valueOf(System.currentTimeMillis());
			req.message = msg;
			
			req.scene = !isCircle ? SendMessageToWX.Req.WXSceneSession
					: SendMessageToWX.Req.WXSceneTimeline;
			wxApi.sendReq(req);
		} finally{
			
		}
	}

	/**
	 * 文字分享
	 *
	 * @param title
	 *            String 标题
	 * @param message
	 *            String 分享内容
	 * @param isCircle
	 *            boolean 是否是分享到朋友圈
	 */
	private void send(String title,String message,boolean isCircle){
		try {
			//发送文字//////////////////////////////////////////
			//发送文字//////////////////////////////////////////
			WXTextObject txtobj=new WXTextObject();
			Log.i("wexin", "-----------send share context");
			txtobj.text="测试";
			WXMediaMessage msg= new WXMediaMessage(txtobj);
			msg.description="测试数据";
			
//			WXMediaMessage msg= new WXMediaMessage();
//			msg.description= message;
//			msg.title = title;
			
			SendMessageToWX.Req req = new SendMessageToWX.Req();
			req.transaction = String.valueOf(System.currentTimeMillis());
			req.message = msg;
			
			req.scene = !isCircle ? SendMessageToWX.Req.WXSceneSession
					: SendMessageToWX.Req.WXSceneTimeline;
			wxApi.sendReq(req);
		} finally{
				
		}
	}

	/**
	 * 图片分享
	 *
	 * @param bmp
	 *            Bitmap 图片
	 * @param message
	 *            String 分享内容
	 * @param isCircle
	 *            boolean 是否是分享到朋友圈
	 */
	private void send(Bitmap bmp,boolean isCircle){
		try {
			Bitmap thumbBmp = Bitmap.createScaledBitmap(bmp, IMAGE_SIZE, IMAGE_SIZE, true);
			WXImageObject imgObj = new WXImageObject(bmp);
			
			WXMediaMessage msg= new WXMediaMessage();
			msg.mediaObject = imgObj;
            msg.thumbData = Util.bmpToByteArray(thumbBmp, true);
			
			SendMessageToWX.Req req = new SendMessageToWX.Req();
			req.transaction = String.valueOf(System.currentTimeMillis());
			req.message = msg;
			
			req.scene = !isCircle ? SendMessageToWX.Req.WXSceneSession
					: SendMessageToWX.Req.WXSceneTimeline;
			wxApi.sendReq(req);
			
		} finally{
			
		}
	}
	private byte[] InputStreamToByte(InputStream inputStream) throws IOException {
		// TODO Auto-generated method stub

        ByteArrayOutputStream bytestream = new ByteArrayOutputStream();
        int ch;
        while ((ch = inputStream.read()) != -1) {
            bytestream.write(ch);
        }
        byte imgdata[] = bytestream.toByteArray();
        bytestream.close();
        return imgdata;
	}


	public byte[] bmpToByteArray(final Bitmap bmp, final boolean needRecycle) {
		ByteArrayOutputStream output = new ByteArrayOutputStream();
		bmp.compress(CompressFormat.PNG, 100, output);
		if (needRecycle) {
			bmp.recycle();
		}

		byte[] result = output.toByteArray();
		try {
			output.close();
		} catch (Exception e) {
			e.printStackTrace();
		}

		return result;
	}

	private void error(String msg) {
		if (msg != null) {
			Toast.makeText((Activity)mContext, msg, Toast.LENGTH_SHORT).show();
		}
	}
	
	@Override
	public void onReq(BaseReq arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onResp(BaseResp arg0) {
		// TODO Auto-generated method stub
		switch (arg0.errCode) {
		case BaseResp.ErrCode.ERR_OK:
		{	
			Toast.makeText((Activity)mContext, "分享成功", Toast.LENGTH_LONG).show();
		}
		break;
		case BaseResp.ErrCode.ERR_USER_CANCEL:{

			Toast.makeText((Activity)mContext, "分享取消", Toast.LENGTH_LONG).show();

		}
		break;
		default:{
			Toast.makeText((Activity)mContext, "分享失败，请重试", Toast.LENGTH_LONG).show();
		}
		break;
		}
	}
	private native void nativeInit();
}


