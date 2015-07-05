//
//  HomeScene.cpp
//  AmazingBrick
//
//  Created by liuwei on 15/7/2.
//
//

#include "SuperGlobal.h"
#include "CocosHelper.h"
#include "SoundPlayer.h"


Scene* HomeScene::scene(){
    Scene* pScene = Scene::create();
    
    HomeScene* pLayer = HomeScene::create();
    
    pScene->addChild(pLayer);
    
    return pScene;
}

bool HomeScene::init(){
    if (GameLayerBase::initWithColor(Color4B::WHITE)) {
        Sprite* smallTitle = Sprite::create(LocalizeString("res/ui/logo_small.png"));
        smallTitle->setAnchorPoint(Vec2(0.5, 0));
        smallTitle->setPosition(Vec2(STVisibleRect::getCenterOfScene().x, STVisibleRect::getOriginalPoint().y + 120));
        addChild(smallTitle);
        
        Size frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
        
        float deltaHeight = frameSize.height / 960.0 * 120;
        
        gameTitle = new CrippleSprite();
        gameTitle->init(LocalizeString("res/ui/title.png"), 8);
        gameTitle->setPosition(STVisibleRect::getCenterOfScene() + Vec2(0, deltaHeight / 0.618 + gameTitle->getContentSize().height / 2.0));
        gameTitle->scheduleUpdate();
        addChild(gameTitle);
        
        
        
        MenuItemSprite* play = CocosHelper::menuItemSprite(LocalizeString("res/ui/play.png").c_str());
        play->setPosition(STVisibleRect::getCenterOfScene() + Vec2(0, -50));
        play->setTag(kPlayBtn);
        play->setCallback(CC_CALLBACK_1(HomeScene::onButtonsClicked, this));
        

        string soundFile = LocalizeString("res/ui/sound_on.png");
        if (!SoundPlayer::getInstance()->isMusicOpen()) {
            soundFile = LocalizeString("res/ui/sound_off.png");
        }
        MenuItemSprite* soundBtn = CocosHelper::menuItemSprite(soundFile.c_str());
        soundBtn->setPosition(play->getPosition() + Vec2(-65, 0 - deltaHeight*0.618 - play->getContentSize().height/2.0 - soundBtn->getContentSize().height / 2.0));
        soundBtn->setTag(kSoundBtn);
        soundBtn->setCallback(CC_CALLBACK_1(HomeScene::onButtonsClicked, this));
        
        MenuItemSprite* rankBtn = CocosHelper::menuItemSprite(LocalizeString("res/ui/rank.png").c_str());
        rankBtn->setPosition(soundBtn->getPosition() + Vec2(-80/0.618-rankBtn->getContentSize().width/2.0, 0));
        rankBtn->setTag(kRankBtn);
        rankBtn->setCallback(CC_CALLBACK_1(HomeScene::onButtonsClicked, this));
        
        MenuItemSprite* rateBtn = CocosHelper::menuItemSprite(LocalizeString("res/ui/rate.png").c_str());
        rateBtn->setPosition(soundBtn->getPosition()+Vec2(80/0.618+rateBtn->getContentSize().width / 2.0, 0));
        rateBtn->setTag(kRateBtn);
        rateBtn->setCallback(CC_CALLBACK_1(HomeScene::onButtonsClicked, this));
        
        btnsMenu = Menu::create(play, soundBtn, rateBtn, rankBtn, NULL);
        btnsMenu->setAnchorPoint(Vec2::ZERO);
        btnsMenu->setPosition(Vec2::ZERO);
        addChild(btnsMenu);
        
        
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        
        listener->onTouchBegan = CC_CALLBACK_2(HomeScene::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(HomeScene::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(HomeScene::onTouchEnded, this);
        listener->onTouchCancelled = CC_CALLBACK_2(HomeScene::onTouchCancelled, this);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        touchListener = listener;
        return true;
    }
    return false;
}

bool HomeScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    Vec2 location = touch->getLocationInView();
    
    location = Director::getInstance()->convertToGL(location);
    
    gameTitle->doTouch(location, 512, arc4random() % 10 + 8);
    return true;
}

void HomeScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    Vec2 location = touch->getLocationInView();
    
    location = Director::getInstance()->convertToGL(location);
    
    gameTitle->doTouch(location, 512, 12);
}

void HomeScene::onButtonsClicked(cocos2d::Ref *pRef) {
    MenuItemSprite* pNode = dynamic_cast<MenuItemSprite*>(pRef);
    switch (pNode->getTag()) {
        case kPlayBtn:
        {
            replaceTheScene<Box2dLayer>();
        }
            break;
        case kSoundBtn:
        {
            SoundPlayer::getInstance()->switchMusic();
            string soundFile = LocalizeString("res/ui/sound_on.png");
            if (!SoundPlayer::getInstance()->isMusicOpen()) {
                soundFile = LocalizeString("res/ui/sound_off.png");
            }
            Sprite* spr = Sprite::create(soundFile);
            Sprite* spr2 = Sprite::create(soundFile);
            spr2->setColor(Color3B::GRAY);
            pNode->setNormalImage(spr);
            pNode->setSelectedImage(spr2);
        }
            break;
        case kRankBtn:
        {
            
        }
            break;
        case kRateBtn:
        {
            
        }
            break;
        default:
            break;
    }
}
