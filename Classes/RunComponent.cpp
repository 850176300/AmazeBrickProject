//
//  RunComponent.cpp
//  AmazingBrick
//
//  Created by liuwei on 15/7/11.
//
//

#include "RunComponent.h"
#include "Config.h"

RunComponent::RunComponent(){
    setName("RunComponent");
    
}

void RunComponent::onEnter(){
    _parent = (BrickSprite*)getOwner();
}

void RunComponent::update(float dt) {
    if (_parent->getStatues() == BrickSprite::kTouchL) {
        _parent->setStatues(BrickSprite::kIdle);
        _elapsed = 0;
        _previousPos = _startPosition = _parent->getPosition();
        _direction = kUp;
        deltaX = 0-MoveX;
        
//        totalTime = (Director::getInstance()->getVisibleOrigin().x + Director::getInstance()->getVisibleSize().height * 0.6 - _startPosition.y) / MoveY ;
//        totalTime = totalTime > 1.0 ? 1.0 : totalTime;
//        totalTime = totalTime > 0.5 ? totalTime : 0.5;
        firstTimeOver = true;
        totalTime = 1.0f;
        timeOver = totalTime / 2.0;
        _parent->unschedule(schedule_selector(BrickSprite::resume));
//        log("the total time is %.2f", totalTime);
    }else if (_parent->getStatues() == BrickSprite::kTouchR){
        _parent->setStatues(BrickSprite::kIdle);
        _elapsed = 0;
        _previousPos = _startPosition = _parent->getPosition();
        _direction = kUp;
        deltaX = MoveX;
        firstTimeOver = true;
//        totalTime = (Director::getInstance()->getVisibleOrigin().x + Director::getInstance()->getVisibleSize().height * 0.6 - _startPosition.y) / MoveY ;
//        totalTime = totalTime > 1.0 ? 1.0 : totalTime;
//        totalTime = totalTime > 0.5 ? totalTime : 0.5;
        totalTime = 1.0f;
        timeOver = totalTime / 2.0;
//        log("the total time is %.2f", totalTime);
        _parent->unschedule(schedule_selector(BrickSprite::resume));
    }else if (_parent->getStatues() == BrickSprite::kDie){
        return;
    }else if (_parent->getStatues() == BrickSprite::kTapEnded) {
//        if (deltat > 0.5) {
            _elapsed = 0;
            _direction = kJump;
//        }else {
//            _elapsed = timeOver;
//            _direction = kDown;
//        }

         _parent->setStatues(BrickSprite::kIdle);
    }
    if (_parent->getStatues() == BrickSprite::kIdle) {
        _elapsed += dt;
        this->step(MAX (0,                                  // needed for rewind. elapsed could be negative
                        MIN(4.0, _elapsed /
                            MAX(1.0, FLT_EPSILON)   // division by 0
                            )
                        )
                   );
    }
}

void RunComponent::step(float t) {
//    log("the move durantion is %.2f", t);
//    return;
    float y = 0;
    switch (_direction) {
        case kUp:
        {
//            log("the move durantion is %.2f", t);
            y = MoveY * 4 *  t * (totalTime - t);
            if (t >= timeOver) {
                _direction = kDown;
            }
            
            if (_startPosition.y + y >= Director::getInstance()->getVisibleOrigin().x + Director::getInstance()->getVisibleSize().height * 0.6) {
                y = Director::getInstance()->getVisibleOrigin().x + Director::getInstance()->getVisibleSize().height * 0.6 - _startPosition.y;
                if (firstTimeOver == true) {
                    firstTimeOver = false;
                    timeOver = totalTime - t;
                    deltat = totalTime - t * 2;
                    stringstream ss("");
                    __String* _data = __String::createWithFormat("%.2f", deltat > 0.5 ? 0.5f : deltat);
//                    log("the time over  is %s", _data->getCString());
                    _parent->scheduleOnce(schedule_selector(BrickSprite::resume), deltat > 0.5 ? 0.5f : deltat);
//                    log("the data timer is %s, %.2f, and total time is %.2f", _data->getCString(), timeOver, totalTime);
                    __String* distance = __String::createWithFormat("%.2f", (MoveY - y));
                    ss<<_data->getCString()<<","<<distance->getCString();
                    NotificationCenter::getInstance()->postNotification(kMoveNotifyEvent, __String::create(ss.str()));
                }
            }
           
        }
            break;
        case kDown:
        {
            y = MoveY * 4 *  t * (totalTime - t);
            
        }
            break;
        case kJump:
        {
            y = -MoveY * 4 * t * t;
        }
            break;
        default:
            break;
    }
    
    float x = deltaX * 0.02;
    
    Vec2 currentPos = _parent->getPosition();
    
    Vec2 diff = currentPos - _previousPos;
    
    _startPosition = diff + _startPosition;
    
    Vec2 newPos = _startPosition + Vec2(x,y);
    newPos.x = _previousPos.x + x;
    if (newPos.x <= Director::getInstance()->getVisibleOrigin().x + _parent->getContentSize().width / 2.0) {
        newPos.x = Director::getInstance()->getVisibleOrigin().x + Director::getInstance()->getVisibleOrigin().x + _parent->getContentSize().width / 2.0;
    }
    if (newPos.x >= Director::getInstance()->getVisibleOrigin().x + Director::getInstance()->getVisibleSize().width - _parent->getContentSize().width / 2.0) {
        newPos.x = Director::getInstance()->getVisibleOrigin().x + Director::getInstance()->getVisibleSize().width - _parent->getContentSize().width / 2.0;
    }
    
    _parent->setPosition(newPos);
     log("the y Value is %.2f", newPos.y);
    _previousPos = newPos;
    if (_parent->boundingBox().getMinY() < Director::getInstance()->getVisibleOrigin().y) {
        _parent->brickDie();
        
    }
}

void RunComponent::scheduleResume(float dt) {

    _parent->setStatues(BrickSprite::BrickStatues::kTapEnded);
   
    log("void RunComponent::scheduleResume(float dt)");

}
