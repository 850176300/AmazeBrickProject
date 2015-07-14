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
        totalTime = (Director::getInstance()->getVisibleOrigin().x + Director::getInstance()->getVisibleSize().height * 0.6 - _startPosition.y) / MoveY ;
        if (fabs(totalTime) < 0.05){
            timeOver = 0.45;
            _direction = kNone;
            NotificationCenter::getInstance()->postNotification(kMoveNotifyEvent, __String::create("0.4,200"));
        }else {
            moveHeight = MoveY;
            if (totalTime < 1.0) {
                moveHeight = MoveY*totalTime;
            }
            firstTimeOver = true;
            totalTime = .8f;
            timeOver = totalTime / 2.0;
            _parent->unschedule(schedule_selector(BrickSprite::scheduleSelector));
            
        }
        
//        log("the total time is %.2f", totalTime);
    }else if (_parent->getStatues() == BrickSprite::kTouchR){
        _parent->setStatues(BrickSprite::kIdle);
        _elapsed = 0;
        _previousPos = _startPosition = _parent->getPosition();
        _direction = kUp;
        deltaX = MoveX;
        firstTimeOver = true;
        totalTime = (Director::getInstance()->getVisibleOrigin().x + Director::getInstance()->getVisibleSize().height * 0.6 - _startPosition.y) / MoveY ;
        if (fabs(totalTime) < 0.05){
            timeOver = 0.45;
            _direction = kNone;
            NotificationCenter::getInstance()->postNotification(kMoveNotifyEvent, __String::create("0.4,200"));
        }else {
            moveHeight = MoveY;
            if (totalTime < 1.0) {
                moveHeight = MoveY * totalTime;
            }
            totalTime = 0.8f;
            timeOver = totalTime / 2.0;
            //        log("the total time is %.2f", totalTime);
            _parent->unschedule(schedule_selector(BrickSprite::scheduleSelector));
        }
//        totalTime = totalTime > 1.0 ? 1.0 : totalTime;
//        totalTime = totalTime > 0.5 ? totalTime : 0.5;
        
    }else if (_parent->getStatues() == BrickSprite::kDie){
        return;
    }else if (_parent->getStatues() == BrickSprite::kTapEnded) {
//        if (deltat > 0.5) {
            _elapsed = 0;
            _direction = kJump;
        _startPosition = _previousPos;
//        }else {
//            _elapsed = timeOver;
//            _direction = kNone;
//        }

         _parent->setStatues(BrickSprite::kIdle);
        return;
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
    bool gotoJump = false;
    bool gotoNone = false;
    float y = 0;
    switch (_direction) {
        case kUp:
        {
//            log("the move durantion is %.2f", t);
            y = MoveY * 1/.16 *  t * (totalTime - t);
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
                    float dlt = 0.4 - moveHeight / MoveY * 0.4 + 0.1;

                    __String* _data = __String::createWithFormat("%.2f", dlt);
                    __String* distance = __String::createWithFormat("%.2f", (MoveY - moveHeight));
                    ss<<_data->getCString()<<","<<distance->getCString();
                    NotificationCenter::getInstance()->postNotification(kMoveNotifyEvent, __String::create(ss.str()));
                    timeOver = dlt;
                    gotoNone = true;
                    log("the distance is %.2f, and the time is %.2f", MoveY - moveHeight, dlt);
                }
            }
           
        }
            break;
        case kDown:
        {
            y = MoveY * 1/.16 *  t * (totalTime - t);
            
        }
            break;
        case kJump:
        {
            y = -MoveY * 5 * t * t;
//            y = _previousPos.y + y - _startPosition.y;
        }
            break;
        case kNone:
        {
            if (t > timeOver) {
                gotoJump = true;
            }
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
    
    _previousPos = newPos;
    if (_parent->boundingBox().getMinY() < Director::getInstance()->getVisibleOrigin().y) {
        _parent->brickDie();
        
    }
    if (gotoJump == true) {
        _direction = kJump;
        _elapsed = 0;
        _startPosition = _previousPos;
    }
    
    if (gotoNone == true) {
        _direction = kNone;
        _startPosition = _previousPos;
    }
}

void RunComponent::scheduleResume(float dt) {

    _parent->setStatues(BrickSprite::BrickStatues::kTapEnded);
   
    log("void RunComponent::scheduleResume(float dt)");

}
