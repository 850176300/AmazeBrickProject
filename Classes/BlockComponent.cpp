//
//  BlockComponent.cpp
//  AmazingBrick
//
//  Created by liuwei on 15/7/8.
//
//

#include "BlockComponent.h"
#include "STVisibleRect.h"
USING_NS_ST;

BlockComponent::BlockComponent(){
    setName("BlockComponent");
}

void BlockComponent::onEnter(){
    Node* parent = getOwner();
    if (parent != nullptr) {
        parent->scheduleUpdate();
    }
}

void BlockComponent::update(float dt) {
    Node* parent = getOwner();
    if (parent != nullptr) {
        if (parent->getPositionY() < STVisibleRect::getPointOfSceneLeftUp().y+36 - 100) {
            if (firstPost == false) {
                firstPost = true;
                NotificationCenter::getInstance()->postNotification(kFirstEvent, nullptr);
            }
        }
        if (parent->getPositionY() < STVisibleRect::getPointOfSceneLeftUp().y+36 - 500) {
            if (secondPost == false) {
                secondPost = true;
                 NotificationCenter::getInstance()->postNotification(kSecondEvent, nullptr);
                parent->unscheduleUpdate();
            }
        }
    }
}
