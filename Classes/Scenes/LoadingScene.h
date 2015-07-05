//
//  LoadingScene.h
//  AmazingBrick
//
//  Created by liuwei on 15/7/2.
//
//

#ifndef __AmazingBrick__LoadingScene__
#define __AmazingBrick__LoadingScene__

#include <iostream>
#include "cocos2d.h"
#include "ensRippleNode.h"
using namespace std;
USING_NS_CC;
using namespace ens;

class LoadingScene: public LayerColor{
public:
    static Scene* scene();
    
    CREATE_FUNC(LoadingScene);
    
    virtual bool init();
    
protected:
    virtual void onEnterTransitionDidFinish();
    void flipUpdate(float dt);
    void gotoHome(float);
private:
    CrippleSprite* logo = nullptr;
    float startx = 0;
};

#endif /* defined(__AmazingBrick__LoadingScene__) */
