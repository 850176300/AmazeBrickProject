//
//  SpriteInScrollview.h
//  DND2052_Baby_Play_Town
//
//  Created by liuwei on 15-1-19.
//
//

#ifndef __DND2052_Baby_Play_Town__SpriteInScrollview__
#define __DND2052_Baby_Play_Town__SpriteInScrollview__

#include <stdio.h>
#include "cocos2d.h"
#include "SuperGlobal.h"
USING_NS_CC;
class SpriteInScrollview: public Sprite{
public:
    static SpriteInScrollview* create(const char* apName);
    static SpriteInScrollview* createWithTexture(Texture2D* texture);
    virtual bool initWithFile(const char *pszFilename);
    virtual bool initWithTexture(cocos2d::Texture2D *pTexture);
    CC_SYNTHESIZE(Vec2, startLocation, StartLocation);
};
#endif /* defined(__DND2052_Baby_Play_Town__SpriteInScrollview__) */
