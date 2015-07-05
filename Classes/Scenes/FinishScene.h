//
//  LoadingScene.h
//  AmazingBrick
//
//  Created by liuwei on 15/7/2.
//
//

#ifndef __AmazingBrick__FinishScene__
#define __AmazingBrick__FinishScene__

#include <iostream>
#include "cocos2d.h"
#include "GameLayerBase.h"
#include "ui/CocosGUI.h"
#include "ensRippleNode.h"

using namespace ens;
USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;

class FinishScene : public GameLayerBase{
    enum itemTags{
        kPlayBtn = 11,
        kHomeBtn,
        kSoundBtn,
        kRankBtn
    };
public:
    static Scene* scene();
    
    CREATE_FUNC(FinishScene);
    
    virtual bool init();
    
protected:
    void onButtonsClicked(Ref* pRef);
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event){};
    virtual void onTouchCancelled(Touch *touch, Event *unused_event){};
private:
    CrippleSprite* gameTitle = nullptr;
    Menu* btnsMenu = nullptr;
    EventListener* touchListener;
};
#endif /* defined(__AmazingBrick__FinishScene__) */
