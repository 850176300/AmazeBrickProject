//
//  ShareLayer.h
//  AmazingBrick
//
//  Created by liuwei on 15/7/26.
//
//

#ifndef __AmazingBrick__ShareLayer__
#define __AmazingBrick__ShareLayer__

#include <iostream>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace cocos2d::ui;
class ShareLayer : public LayerColor{
    enum ShareTag{
        kWechatShare,
        kSinaShare,
    };
public:
    CREATE_FUNC(ShareLayer);
    
    virtual bool init();
    
protected:
    virtual void onEnter();
    virtual void onExit();
    
private:
    void onShareClicked(Ref* pRef, Widget::TouchEventType type);
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event){}
    virtual void onTouchEnded(Touch *touch, Event *unused_event){}
    virtual void onTouchCancelled(Touch *touch, Event *unused_event){}
private:
    ui::ImageView* pframe = nullptr;
};

#endif /* defined(__AmazingBrick__ShareLayer__) */
