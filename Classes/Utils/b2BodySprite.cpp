//
//  b2BodySprite.cpp
//  DND2052_Baby_Play_Town
//
//  Created by liuwei on 15-1-13.
//
//

#include "b2BodySprite.h"
#include "Config.h"
#include "Shake.h"

b2BodySprite::b2BodySprite(){
    _delegate = nullptr;
    needCheckSkip = false;
}

b2BodySprite::~b2BodySprite(){
    if (hadAddNotify == true) {
        NotificationCenter::getInstance()->removeObserver(this, kMoveNotifyEvent);
    }
}

b2BodySprite* b2BodySprite::create(const string &filename) {
    b2BodySprite* pRet = new b2BodySprite();
    if (pRet && pRet->initWithFile(filename)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return pRet;
    }
}


b2BodySprite* b2BodySprite::createWithTexture(cocos2d::Texture2D *texture) {
    b2BodySprite* pRet = new b2BodySprite();
    if (pRet && pRet->initWithTexture(texture)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return pRet;
    }
}

b2BodySprite* b2BodySprite::createWithSpriteFrame(SpriteFrame* frame) {
    b2BodySprite* pRet = new b2BodySprite();
    if (pRet && pRet->initWithSpriteFrame(frame)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return pRet;
    }
}

void b2BodySprite::setB2Body(b2Body *pBody) {
    _pB2Body = pBody;
}

void b2BodySprite::setPTMRatio(float fPTMRatio) {
    PTMRatio = fPTMRatio;
}

b2Body* b2BodySprite::getB2Body() const
{
    return _pB2Body;
}

float b2BodySprite::getPTMRatio() const{
    return PTMRatio;
}


void b2BodySprite::setPosition(const cocos2d::Vec2 &pos) {
    Sprite::setPosition(pos);
    Vec2 pos11 = pos + Vec2(this->getContentSize().width*(0.5-this->getAnchorPoint().x), this->getContentSize().height*(0.5-this->getAnchorPoint().y));
    if (_pB2Body != nullptr) {
        _pB2Body->SetTransform(b2Vec2(pos11.x/PTMRatio, pos11.y/PTMRatio),0);
    }
}

void b2BodySprite::setPositionWithBool(const cocos2d::Vec2 &pos, bool ignorgAnchorPoint /*= false*/) {
    Sprite::setPosition(pos);
    if (ignorgAnchorPoint == true) {
        Vec2 pos11 = pos + Vec2(this->getContentSize().width*(0.5-this->getAnchorPoint().x), this->getContentSize().height*(0.5-this->getAnchorPoint().y));
        if (_pB2Body != nullptr) {
            _pB2Body->SetTransform(b2Vec2(pos11.x/PTMRatio, pos11.y/PTMRatio),0);
        }
    }else {
        if (_pB2Body != nullptr) {
            _pB2Body->SetTransform(b2Vec2((pos.x-50)/PTMRatio, pos.y/PTMRatio),0);
        }
    }
}

//void b2BodySprite::addMoveEventNotify(){
//    if (hadAddNotify == true){
//        return;
//    }
//    hadAddNotify = true;
//    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(b2BodySprite::onRecieveEvent), kMoveNotifyEvent, nullptr);
//}
//
//void b2BodySprite::onRecieveEvent(cocos2d::Ref *pRef) {
//    __String* data = dynamic_cast<__String*>(pRef);
//    float infor = atof(data->getCString());
//    float distance = infor - (((int)infor) / 1000)*1000;
//    float dt = (((int)infor) / 1000) * 0.1;
//    
//    this->runAction(Sequence::create(EaseSineInOut::create(MoveBy::create(dt, Vec2(0, -distance))), CallFunc::create(std::bind(&b2BodySprite::checkNeedRemove, this)),NULL));
//}
//
//void b2BodySprite::checkNeedRemove(){
//    if (getBoundingBox().getMaxY() < Director::getInstance()->getVisibleOrigin().y) {
//        if (_pB2Body != nullptr) {
//            _pB2Body->GetWorld()->DestroyBody(_pB2Body);
//        }
//        removeFromParent();
//    }
//}
void b2BodySprite::addMoveEventNotify(){
    if (hadAddNotify == true){
        return;
    }
    hadAddNotify = true;
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(b2BodySprite::onRecieveEvent), kMoveNotifyEvent, nullptr);
}



// string toolkit
void b2BodySprite::split(const std::string& src, const char* token, strArray& vect)
{
    int nend=0;
    int nbegin=0;
    while(nend != -1)
    {
        nend = src.find(token, nbegin);
        if(nend == -1)
            vect.push_back(src.substr(nbegin, src.length()-nbegin));
        else
            vect.push_back(src.substr(nbegin, nend-nbegin));
        nbegin = nend + strlen(token);
    }
}

void b2BodySprite::onRecieveEvent(cocos2d::Ref *pRef) {
    
    __String* data = dynamic_cast<__String*>(pRef);
    if (data->compare("shake") == 0) {
        stopAllActions();
//        _pB2Body->GetWorld()->DestroyBody(_pB2Body);
//        _pB2Body = nullptr;
        this->runAction(Shake::create(0.2, 5));
        return;
    }
    
    strArray str;
    split(data->getCString(), ",", str);
    
    float distance = atof(str.at(1).c_str());
    float dt = atof(str.at(0).c_str());
    
//    log("the duration is %.2f distance is %.2f", dt, distance);
    
    this->runAction(Sequence::create(EaseSineInOut::create(MoveBy::create(dt, Vec2(0, -distance))), CallFunc::create(std::bind(&b2BodySprite::checkNeedRemove, this)),NULL));
}

void b2BodySprite::checkNeedRemove(){
    
    Vec2 originPP = Director::getInstance()->getVisibleOrigin();
    Size glSize = Director::getInstance()->getVisibleSize();
    
    if (firstTimeRecieveMove == true && getBoundingBox().getMidY() < originPP.y + glSize.height * 0.7) {
        firstTimeRecieveMove = false;
        if (_delegate != nullptr) {
            _delegate->onFirstTimeMove(this);
        }
    }
    if (needCheckSkip == true && hasSendEvent == false) {
        if (getBoundingBox().getMidY() <= originPP.y + glSize.height * 0.5 && hasSendEvent == false) {
            NotificationCenter::getInstance()->postNotification(kAddBlockEvent);
            hasSendEvent = true;
            needCheckSkip = false;
        }
    }
    if (getBoundingBox().getMaxY() < Director::getInstance()->getVisibleOrigin().y) {
        _pB2Body->GetWorld()->DestroyBody(_pB2Body);
        removeFromParent();
    }
}


