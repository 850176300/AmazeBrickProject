//
//  RunComponent.h
//  AmazingBrick
//
//  Created by liuwei on 15/7/11.
//
//

#ifndef __AmazingBrick__RunComponent__
#define __AmazingBrick__RunComponent__

#include <iostream>
#include <sstream>
#include "cocos2d.h"
#include "BrickSprite.h"
using namespace std;
USING_NS_CC;

class RunComponent : public Component{
    enum RunDirection{
        kUp = 1,
        kDown = 2,
        kJump,
    };
public:
    RunComponent();
    
protected:
    virtual void onEnter();
    void update(float dt);
    void step(float dt);
    void scheduleResume(float dt);
private:
    Vec2 _startPosition;
    Vec2 _previousPos;
    BrickSprite* _parent = nullptr;
//    float accSpeed;
    RunDirection _direction = kUp;
    float _elapsed = 0;
    float _durantion = 0;
    float deltaX;
    bool firstTimeOver = true;
    float timeOver = 0.5;
    float totalTime = 0;
    float deltat = 0;
//    float recordTimeOver = 0;
};

#endif /* defined(__AmazingBrick__RunComponent__) */
