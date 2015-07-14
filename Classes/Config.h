//
//  Config.h
//  com.kekeapp.amazebrickx
//
//  Created by liuwei on 15/6/14.
//
//

#ifndef com_kekeapp_amazebrick_Config_h
#define com_kekeapp_amazebrick_Config_h
#include <iostream>
#include "cocos2d.h"
USING_NS_CC;


#define MoveY 200
#define MoveX 150
#define XChange 120
#define MoveDelta 180
#define SecondTime 0.5
#define MoveDuration 0.7
#define DropDuration 1.6
#define SpeedX 8
#define SpeedY 50
#define ACCY -0

#define kMoveNotifyEvent "kMoveNotifyEvent"
#define kAddBlockEvent "kAddBlockEvent"
#define kHighestScore "kHighestScore"
#define kCurrentScore "kCurrentScore"


#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#define FONT_NAME  "fonts/atn.ttf"//"AvantGarde LT Book"
#else
#define FONT_NAME  "fonts/atn.ttf"
#endif

#endif
