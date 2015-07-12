//
//  AppConfigs.h
//  AdsPopupDemo
//
//  Created by tang.wei on 13-12-13.
//  Copyright (c) 2013年 tang.wei. All rights reserved.
//

/*************************** MoPub账号设置 **************************/

#define IPHONE_BANNER_ID         @"44a242033046450991074d4bbfcefbd0"
#define IPHONE_FULLSCREEN_ID     @"ac616a24c5284505a29793aa6e5e4085"

#define IPAD_BANNER_ID           @"a050c1937e3a40288907c3fe6ee4d136"
#define IPAD_FULLSCREEN_ID       @"6fefdd66a2884e7a863d753713b0a08b"

#define IPHONE_FULLSCREEN_ID_CROSSPROMO   @""
#define IPAD_FULLSCREEN_ID_CROSSPROMO     @""
// 方块广告，如果不需要支持可以留空
#define IPHONE_MEDIUM_RECT_ID    @""
#define IPAD_MEDIUM_RECT_ID      @""

// Chartboost账号，如果不需要支持开启chartboost会话，可以留空
#define CHARTBOOST_APP_ID        @""
#define CHARTBOOST_APP_SIGNATURE @""

/*************************** Flurry账号 ****************************/
// 如果留空不设置，那么表示不支持Flurry
#define FLURRY_KEY               @"DZMR692CH3J6JYPJNP4R"

/*************************** Privacy Page设置 ****************************/
// 如果留空默认为http://www.xxx.com/privacy.html, 其中xxx为bundle id中间部分
#define PRIVACY_PAGE_URL         @""