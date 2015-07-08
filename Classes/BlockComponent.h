//
//  BlockComponent.h
//  AmazingBrick
//
//  Created by liuwei on 15/7/8.
//
//

#ifndef __AmazingBrick__BlockComponent__
#define __AmazingBrick__BlockComponent__

#include <iostream>
#include "cocos2d.h"
using namespace std;
USING_NS_CC;

#define kFirstEvent "firstPost"
#define kSecondEvent "secondPost"

class BlockComponent : public Component{
public:
    BlockComponent();
protected:
    virtual void onEnter();
    virtual void update(float dt);
private:
    bool firstPost = false;
    bool secondPost = false;
    
};


#endif /* defined(__AmazingBrick__BlockComponent__) */
