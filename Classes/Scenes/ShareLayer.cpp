//
//  ShareLayer.cpp
//  AmazingBrick
//
//  Created by liuwei on 15/7/26.
//
//

#include "ShareLayer.h"
#include "STVisibleRect.h"
#include "CocosHelper.h"
#include "STFileUtility.h"
#include "Config.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "WeiboManager.h"
#include "WechatManager.h"
#endif
USING_NS_ST;

bool ShareLayer::init(){
    if (LayerColor::initWithColor(Color4B(0, 0, 0, 150))) {
//        STFileUtility::createDirectory((STFileUtility::getStoragePath() + "/amazingcircle").c_str());
        bool result = STFileUtility::createDirectory((STFileUtility::getStoragePath() + "amazingcircle").c_str());
        if (result == false) {
            log("创建文件夹失败");
        }else {
           log("创建文件夹成功");
        }
        
        pframe = ui::ImageView::create("res/ui/frame.png");
        pframe->setPosition(STVisibleRect::getCenterOfScene());
        addChild(pframe, 1);
        
        ui::Button* pSinaBtn = ui::Button::create("res/ui/share2.png");
        ui::Button* pWechatBtn = ui::Button::create("res/ui/share1.png");
        
        pSinaBtn->setPosition(Vec2(pframe->getContentSize().width / 2.0, pframe->getContentSize().height / 2.0) + Vec2(-100, -20));
        pWechatBtn->setPosition(Vec2(pframe->getContentSize().width / 2.0, pframe->getContentSize().height / 2.0) + Vec2(100, -20));
        pSinaBtn->setTag(kSinaShare);
        pWechatBtn->setTag(kWechatShare);
        
        pSinaBtn->addTouchEventListener(CC_CALLBACK_2(ShareLayer::onShareClicked, this));
        pWechatBtn->addTouchEventListener(CC_CALLBACK_2(ShareLayer::onShareClicked, this));
        
        pframe->addChild(pSinaBtn);
        pframe->addChild(pWechatBtn);
        pframe->setScale(0);
        
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        
        listener->onTouchBegan = CC_CALLBACK_2(Layer::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(Layer::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(Layer::onTouchEnded, this);
        listener->onTouchCancelled = CC_CALLBACK_2(Layer::onTouchCancelled, this);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        _touchListener = listener;
        return true;
    }
    return false;
}

bool ShareLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    this->removeFromParent();
    return true;
}

void ShareLayer::onEnter(){
    LayerColor::onEnter();
    pframe->runAction(EaseElasticInOut::create(ScaleTo::create(0.8, 1.0), 0.6));
}

void ShareLayer::onExit(){
    pframe->runAction(EaseBounceInOut::create(FadeOut::create(0.5)));
    LayerColor::onExit();
    
}

void ShareLayer::onShareClicked(cocos2d::Ref *pRef, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED) {
        Node* pNode = dynamic_cast<Node*>(pRef);
        
        int score = UserDefault::getInstance()->getIntegerForKey(kHighestScore, 0);
        if (pNode->getTag() == kSinaShare) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
            WeiboManager::getInstance()->sendWeibo(score);
#endif
        }else {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
            WechatManager::getInstance()->sharetoCircle(score);
#endif
        }
        this->removeFromParent();
    }
}








