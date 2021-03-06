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
#include "LeaderboardAdaptor.h"
#include "STSystemFunction.h"
#include "Config.h"
#include "ShareLayer.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "ActivityManager.h"
#include "GameSharing.h"
#endif
Scene* HomeScene::scene(){
    Scene* pScene = Scene::create();
    
    HomeScene* pLayer = HomeScene::create();
    
    pScene->addChild(pLayer);
    
    return pScene;
}

bool HomeScene::init(){
    if (GameLayerBase::initWithColor(Color4B::WHITE)) {
        setShowAds(true);
        Sprite* smallTitle = Sprite::create("res/ui/logo_small.png");
        smallTitle->setAnchorPoint(Vec2(0.5, 0));
        smallTitle->setPosition(Vec2(STVisibleRect::getCenterOfScene().x, STVisibleRect::getOriginalPoint().y + 140));
        addChild(smallTitle);
        
        Size frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
        
        float deltaHeight = STVisibleRect::getGlvisibleSize().width * 0.18;
        
        gameTitle = new CrippleSprite();   
        gameTitle->init("res/ui/title.png", 8);
        gameTitle->setPosition(STVisibleRect::getCenterOfScene() + Vec2(0, deltaHeight / 0.618 + gameTitle->getContentSize().height / 2.0));
        gameTitle->scheduleUpdate();
        addChild(gameTitle);
        
        
        
        MenuItemSprite* play = CocosHelper::menuItemSprite("res/ui/play.png");
        play->setPosition(STVisibleRect::getCenterOfScene() + Vec2(0, -50));
        play->setTag(kPlayBtn);
        play->setCallback(CC_CALLBACK_1(HomeScene::onButtonsClicked, this));
        

        string soundFile = "res/ui/sound_on.png";
        if (!SoundPlayer::getInstance()->isMusicOpen()) {
            soundFile = "res/ui/sound_off.png";
        }
        MenuItemSprite* soundBtn = CocosHelper::menuItemSprite(soundFile.c_str());
        soundBtn->setPosition(play->getPosition() + Vec2(-65, 0 - deltaHeight*0.618 - play->getContentSize().height/2.0 - soundBtn->getContentSize().height / 2.0));
        soundBtn->setTag(kSoundBtn);
        soundBtn->setCallback(CC_CALLBACK_1(HomeScene::onButtonsClicked, this));
        
        STSystemFunction st;
        MenuItemSprite* rankBtn = CocosHelper::menuItemSprite("res/ui/rank.png");
        rankBtn->setTag(kRankBtn);
//        if (st.getIsSupportGoogle() == false) {
//            rankBtn = CocosHelper::menuItemSprite("res/ui/share.png");
//            rankBtn->setTag(kRankBtn);
//        }
        rankBtn->setPosition(soundBtn->getPosition() + Vec2(-80/0.618-rankBtn->getContentSize().width/2.0, 0));
        
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
        log("the ad showing ");
        GameLayerBase::setShowAds(true);
        log("the ad showing 222");

        LeaderboardAdaptor::authenticateLocalPlayer();
        LeaderboardAdaptor::requestScore([=](int score){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
            int sc = UserDefault::getInstance()->getIntegerForKey(kHighestScore, 0);
            if (score > sc) {
                UserDefault::getInstance()->setIntegerForKey(kHighestScore, score);
                UserDefault::getInstance()->flush();
            }
#endif
        });
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
    SoundPlayer::getInstance()->playCommonEffect("sound/click.wav");
    switch (pNode->getTag()) {
        case kPlayBtn:
        {
            replaceTheScene<Box2dLayer>();
        }
         break;
        case kSoundBtn:
        {
            SoundPlayer::getInstance()->switchVolume();
            string soundFile = "res/ui/sound_on.png";
            if (!SoundPlayer::getInstance()->isMusicOpen()) {
                soundFile = "res/ui/sound_off.png";
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
            LeaderboardAdaptor::showLeaderboard();
        }
            break;
        case kRateBtn:
        {
            STSystemFunction st;
            st.rating();

        }
            break;
        case kShareBtn:
        {
            Sprite* title = Sprite::createWithTexture(gameTitle->getTexture());
            title->setPosition(gameTitle->getPosition());
            addChild(title, gameTitle->getLocalZOrder());
            gameTitle->setVisible(false);
            RenderTexture* pRender = RenderTexture::create(this->getContentSize().width, this->getContentSize().height, Texture2D::PixelFormat::RGBA8888);
            
            pRender->beginWithClear(0, 0, 0, 255);
            this->visit();
            pRender->end();
            gameTitle->setVisible(true);
            title->removeFromParent();
            Director::getInstance()->getRenderer()->render();
            
            Image* pImage = pRender->newImage();
            log("%s",(STFileUtility::getStoragePath() + "amazingcircle/temp.png").c_str());
            pImage->saveToFile(STFileUtility::getStoragePath() + "amazingcircle/temp.png", true);
            pImage->release();
            ShareLayer* pLayer = ShareLayer::create();
            this->addChild(pLayer, 9999);
        }
        default:
            break;
    }
}

void HomeScene::onKeyBackClicked(){
    GameLayerBase::onKeyBackClicked();

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
//    STSystemFunction st;
//    if (st.getIsSupportGoogle() == false) {
//        ActivityManager::getInstance()->exitGame();
//    }else {
//        GameSharing::getInstance()->ExitGame();
//    }
    
    
#endif
    Director::getInstance()->end();
}
