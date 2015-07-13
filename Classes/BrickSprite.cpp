//
//  BrickSprite.cpp
//  com.kekeapp.amazebrick
//
//  Created by liuwei on 15/6/14.
//
//

#include "BrickSprite.h"
#include "SoundPlayer.h"

BrickSprite* BrickSprite::create(const string &file) {
    BrickSprite* pRet = new BrickSprite();
    if (pRet && pRet->initWithFilename(file)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
}

BrickSprite* BrickSprite::createWithSpriteFrame(cocos2d::SpriteFrame *frame) {
    BrickSprite* pRet = new BrickSprite();
    if (pRet && pRet->initWithFrame(frame)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
}

bool BrickSprite::initWithFrame(cocos2d::SpriteFrame *frame) {
    if (Sprite::initWithSpriteFrame(frame)) {
        statue = kIdle;
        return true;
    }
    return false;
}


bool BrickSprite::initWithFilename(const string &file) {
    if (Sprite::initWithFile(file)) {
        statue = kStatic;
        return true;
    }
    return false;
}

void BrickSprite::tapLSide(){
    if (statue == kDie) {
        return;
    }
    statue = kTouchL;
}

void BrickSprite::tapRSide(){
    if (statue == kDie) {
        return;
    }
    statue = kTouchR;
}

void BrickSprite::tapEnded(){
    if (statue == kDie) {
        return;
    }
    statue = kTapEnded;
}

void BrickSprite::scheduleSelector(float dt) {
    
//    unscheduleUpdate();
//    statue = kDie;
    tapEnded();
//    scheduleUpdate();
}

void BrickSprite::brickDie(){
    statue = kDie;
    SoundPlayer::getInstance()->playCommonEffect("sound/bound.mp3");
    unscheduleUpdate();
    runAction(Sequence::create(EaseSineIn::create(MoveBy::create(0.5, Vec2(0, -1000))), CallFunc::create([=]{
        NotificationCenter::getInstance()->postNotification(kBrickDieEvent);
        
    }), NULL));
}
