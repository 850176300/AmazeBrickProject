//
//  LoadingScene.cpp
//  AmazingBrick
//
//  Created by liuwei on 15/7/2.
//
//

#include "LoadingScene.h"
#include "STVisibleRect.h"
#include "SuperGlobal.h"
USING_NS_ST;

Scene* LoadingScene::scene(){
    Scene* pScene = Scene::create();
    
    LoadingScene* pLayer = LoadingScene::create();
    
    pScene->addChild(pLayer);
    
    return pScene;
}

bool LoadingScene::init(){
    if (LayerColor::initWithColor(Color4B::WHITE)) {
        
        logo = new CrippleSprite();//Sprite::create("res/ui/logo.png");
        logo->init("res/ui/logo.png", 8);
//        logo->setPosition(Vec2(STVisibleRect::getCenterOfScene().x - STVisibleRect::getGlvisibleSize().width, STVisibleRect::getCenterOfScene().y));
        logo->setPosition(STVisibleRect::getCenterOfScene());
        logo->scheduleUpdate();
        addChild(logo);
        logo->autorelease();
        
        
        this->schedule(schedule_selector(LoadingScene::flipUpdate), 2.0, -1, 1.0);
        this->scheduleOnce(schedule_selector(LoadingScene::gotoHome), 3.0);
        return true;
    }
    return false;
}

void LoadingScene::gotoHome(float) {
    replaceTheScene<HomeScene>();
}

void LoadingScene::onEnterTransitionDidFinish(){
    LayerColor::onEnterTransitionDidFinish();
    logo->doTouch(STVisibleRect::getCenterOfScene(), 512, 20);
}

void LoadingScene::flipUpdate(float dt) {
    int streight = arc4random() % 10 + 10;
    logo->doTouch(STVisibleRect::getCenterOfScene(), 512, streight);
//    logo->doTouch(Vec2(logo->getBoundingBox().getMinX()+startx, logo->getPositionY()), 512, 12);
//    startx += 40;
//    
//    if (startx > logo->getContentSize().width) {
//        unschedule(schedule_selector(LoadingScene::flipUpdate));
//    }
}

