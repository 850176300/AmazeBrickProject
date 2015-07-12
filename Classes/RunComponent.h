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
#include "cocos2d.h"
using namespace std;
USING_NS_CC;

class RunComponent : public Component{
public:
    RunComponent();
    
protected:
    virtual void onEnter();
    void update(float dt);
    
    
private:
    float startSpeed;
    float accy;
    
    
    
};

#endif /* defined(__AmazingBrick__RunComponent__) */
