//
//  FinishScene.cpp
//  AmazingBrick
//
//  Created by liuwei on 15/7/2.
//
//

#include "SuperGlobal.h"
#include "CocosHelper.h"
#include "SoundPlayer.h"


Scene* FinishScene::scene(){
    Scene* pScene = Scene::create();
    
    FinishScene* pLayer = FinishScene::create();
    
    pScene->addChild(pLayer);
    
    return pScene;
}

bool FinishScene::init(){
    if (GameLayerBase::initWithColor(Color4B::WHITE)) {

        
        Size frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
        
        float deltaHeight = frameSize.height / 960.0 * 40;
        
        gameTitle = new CrippleSprite();
        gameTitle->init(LocalizeString("res/ui/score.png"), 8);
        gameTitle->setPosition(Vec2(STVisibleRect::getCenterOfScene().x, STVisibleRect::getCenterOfScene().y + 100));
        gameTitle->scheduleUpdate();
        addChild(gameTitle);
        
        TTFConfig config = TTFConfig("fonts/Marker Felt.ttf", 40,GlyphCollection::DYNAMIC);
        Label* label1 = Label::createWithTTF(config, "3233");
        label1->setPosition(Vec2(50, 50));
        gameTitle->addChild(label1);
        
        Sprite* smallTitle = Sprite::create(LocalizeString("res/ui/end.png"));
        smallTitle->setAnchorPoint(Vec2(0.5, 0));
        smallTitle->setPosition(Vec2(STVisibleRect::getCenterOfScene().x, gameTitle->getPositionY()+gameTitle->getContentSize().height / 2.0 + deltaHeight/1.5+smallTitle->getContentSize().height / 2.0));
        addChild(smallTitle);
        
        
        MenuItemSprite* play = CocosHelper::menuItemSprite(LocalizeString("res/ui/play.png").c_str());
        play->setPosition(gameTitle->getPosition() + Vec2(0, -gameTitle->getContentSize().height / 2.0-play->getContentSize().height/2.0 - deltaHeight/1.5));
        play->setTag(kPlayBtn);
        play->setCallback(CC_CALLBACK_1(FinishScene::onButtonsClicked, this));
        
        
        string soundFile = LocalizeString("res/ui/sound_on.png");
        if (!SoundPlayer::getInstance()->isMusicOpen()) {
            soundFile = LocalizeString("res/ui/sound_off.png");
        }
        MenuItemSprite* soundBtn = CocosHelper::menuItemSprite(soundFile.c_str());
        soundBtn->setPosition(play->getPosition() + Vec2(-65, 0 - deltaHeight*0.618/1.5 - play->getContentSize().height/2.0 - soundBtn->getContentSize().height / 2.0));
        soundBtn->setTag(kSoundBtn);
        soundBtn->setCallback(CC_CALLBACK_1(FinishScene::onButtonsClicked, this));
        
        MenuItemSprite* rankBtn = CocosHelper::menuItemSprite(LocalizeString("res/ui/rank.png").c_str());
        rankBtn->setPosition(soundBtn->getPosition() + Vec2(-80/0.618-rankBtn->getContentSize().width/2.0, 0));
        rankBtn->setTag(kRankBtn);
        rankBtn->setCallback(CC_CALLBACK_1(FinishScene::onButtonsClicked, this));
        
        MenuItemSprite* rateBtn = CocosHelper::menuItemSprite(LocalizeString("res/ui/home.png").c_str());
        rateBtn->setPosition(soundBtn->getPosition()+Vec2(80/0.618+rateBtn->getContentSize().width / 2.0, 0));
        rateBtn->setTag(kHomeBtn);
        rateBtn->setCallback(CC_CALLBACK_1(FinishScene::onButtonsClicked, this));
        
        btnsMenu = Menu::create(play, soundBtn, rateBtn, rankBtn, NULL);
        btnsMenu->setAnchorPoint(Vec2::ZERO);
        btnsMenu->setPosition(Vec2::ZERO);
        addChild(btnsMenu);
        
        
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        
        listener->onTouchBegan = CC_CALLBACK_2(FinishScene::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(FinishScene::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(FinishScene::onTouchEnded, this);
        listener->onTouchCancelled = CC_CALLBACK_2(FinishScene::onTouchCancelled, this);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        touchListener = listener;
        return true;
    }
    return false;
}

bool FinishScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    Vec2 location = touch->getLocationInView();
    
    location = Director::getInstance()->convertToGL(location);
    
    gameTitle->doTouch(location, 512, arc4random() % 10 + 8);
    return true;
}

void FinishScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    Vec2 location = touch->getLocationInView();
    
    location = Director::getInstance()->convertToGL(location);
    
    gameTitle->doTouch(location, 512, 12);
}

void FinishScene::onButtonsClicked(cocos2d::Ref *pRef) {
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
        case kHomeBtn:
        {
            replaceTheScene<HomeScene>();
        }
            break;
        default:
            break;
    }
}
