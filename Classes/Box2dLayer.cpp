//
//  Box2dLayer.cpp
//  com.kekeapp.amazebrick
//
//  Created by liuwei on 15/6/8.
//
//

#include "Box2dLayer.h"
#include "VisibleRect.h"
#include "CocosHelper.h"
#include "STVisibleRect.h"
#include "b2BodySprite.h"
#include "GB2ShapeCache-x.h"
#include "Config.h"
#include "SuperGlobal.h"
#include "BlockComponent.h"
#include "STAds.h"
#include "LeaderboardAdaptor.h"
#define ColorCount 6
#define PTM_RATIO 32.0
USING_NS_ST;


Box2dLayer::Box2dLayer(){
//    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Box2dLayer::onRecieveEvent), kMoveNotifyEvent, nullptr);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Box2dLayer::addSkipScore), kAddBlockEvent, nullptr);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Box2dLayer::onGameOver), kBrickDieEvent, nullptr);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Box2dLayer::addPauseLayer), BackGroundEvent, nullptr);
//    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Box2dLayer::addSmallBrick2), kSecondEvent, nullptr);
}

Box2dLayer::~Box2dLayer(){
//    NotificationCenter::getInstance()->removeObserver(this, kMoveNotifyEvent);
    NotificationCenter::getInstance()->removeObserver(this, kAddBlockEvent);
    NotificationCenter::getInstance()->removeObserver(this, kBrickDieEvent);
    NotificationCenter::getInstance()->removeObserver(this, BackGroundEvent);
//    NotificationCenter::getInstance()->removeObserver(this, kSecondEvent);
}

Scene* Box2dLayer::scene(){
    Scene* pscene = Scene::create();
    
    Box2dLayer* pLayer = Box2dLayer::createWithePhysic();
    
    pscene->addChild(pLayer);
    
    return pscene;
}

Box2dLayer*  Box2dLayer::createWithePhysic(){
    Box2dLayer* pRet = new Box2dLayer();
    if (pRet && pRet->init()) {
        pRet->initPhysics();
        pRet->scheduleUpdate();
        pRet->addB2Body(Vec2::ZERO);
        pRet->addBrickBody();
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
}

bool Box2dLayer::init(){
    if (Layer::init()) {
        
        allColors = {Color3B(238, 143, 102),
            Color3B(168, 102, 238),
            Color3B(102, 161, 238),
            Color3B(110, 214, 124),
            Color3B(217, 189, 111),
            Color3B(213, 159, 128)};
        
        Sprite* bg = Sprite::create("bg.png");
        bg->setScale(STVisibleRect::getRealDesignScale());
        bg->setPosition(STVisibleRect::getCenterOfScene());
        addChild(bg);
        
        obstacleY = STVisibleRect::getPointOfSceneLeftUp().y+36;
        centerY = STVisibleRect::getCenterOfScene().y + 50;
        
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common.plist");
        
        auto listener = EventListenerTouchAllAtOnce::create();
        
        listener->onTouchesBegan = CC_CALLBACK_2(Box2dLayer::onTouchesBegan, this);
        listener->onTouchesMoved = CC_CALLBACK_2(Box2dLayer::onTouchesMoved, this);
        listener->onTouchesEnded = CC_CALLBACK_2(Box2dLayer::onTouchesEnded, this);
        listener->onTouchesCancelled = CC_CALLBACK_2(Box2dLayer::onTouchesCancelled, this);
        
        setTouchMode(Touch::DispatchMode::ALL_AT_ONCE);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
        
        TTFConfig config = TTFConfig(FONT_NAME, 40,GlyphCollection::DYNAMIC);
        scoreLabel = Label::createWithTTF(config, convertIntToString(score));
        scoreLabel->setAnchorPoint(Vec2(1.0, 1.0));
        scoreLabel->setPosition(STVisibleRect::getPointOfSceneRightUp() + Vec2(-15, -15));
        scoreLabel->setTextColor(Color4B(0, 50, 50, 255));
        addChild(scoreLabel, 10);
        
        MenuItemSprite* pauseBtn = CocosHelper::menuItemSprite("res/ui/pause.png");
        pauseBtn->setAnchorPoint(Vec2(0, 1.0));
        pauseBtn->setPosition(STVisibleRect::getPointOfSceneLeftUp()+Vec2(15, -15));
        pauseBtn->setCallback([=](Ref* pRef){
            SoundPlayer::getInstance()->playCommonEffect("sound/click.wav");
            this->addPauseLayer(nullptr);
        });
        
        Menu* pMenu = Menu::create(pauseBtn, NULL);
        pMenu->setAnchorPoint(Vec2::ZERO);
        pMenu->setPosition(Vec2::ZERO);
        addChild(pMenu, 100);
        
        STAds ads;
        ads.requestAds();
        return true;
    }
    return false;
}

void Box2dLayer::initPhysics()
{
    b2Vec2 gravity;
    gravity.Set(0.0f, 40.0f);
    world = new b2World(gravity);
    
    // Do we want to let bodies sleep?
    world->SetAllowSleeping(true);
    world->SetContactListener(this);
    world->SetContinuousPhysics(true);
    
             _debugDraw = new GLESDebugDraw( PTM_RATIO );
             world->SetDebugDraw(_debugDraw);
    
        uint32 flags = 0;
        flags += b2Draw::e_shapeBit;
                flags += b2Draw::e_jointBit;
                flags += b2Draw::e_aabbBit;
    //            flags += b2Draw::e_pairBit;
                flags += b2Draw::e_centerOfMassBit;
        _debugDraw->SetFlags(flags);
    //
    
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.userData = (void*)kEdge;
    groundBodyDef.position.Set(0, 0); // bottom-left corner
    
    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    
    // Define the ground box shape.
    b2EdgeShape groundBox;
    
    // bottom
    groundBox.Set(b2Vec2(VisibleRect::leftBottom().x/PTM_RATIO,VisibleRect::leftBottom().y/PTM_RATIO), b2Vec2(VisibleRect::rightBottom().x/PTM_RATIO,VisibleRect::rightBottom().y/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    
//    // top
//    groundBox.Set(b2Vec2(VisibleRect::leftTop().x/PTM_RATIO,VisibleRect::leftTop().y/PTM_RATIO), b2Vec2(VisibleRect::rightTop().x/PTM_RATIO,VisibleRect::rightTop().y/PTM_RATIO));
//    groundBody->CreateFixture(&groundBox,0);
    
    // left
    groundBox.Set(b2Vec2(VisibleRect::leftTop().x/PTM_RATIO,VisibleRect::leftTop().y/PTM_RATIO), b2Vec2(VisibleRect::leftBottom().x/PTM_RATIO,VisibleRect::leftBottom().y/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    
    // right
    groundBox.Set(b2Vec2(VisibleRect::rightBottom().x/PTM_RATIO,VisibleRect::rightBottom().y/PTM_RATIO), b2Vec2(VisibleRect::rightTop().x/PTM_RATIO,VisibleRect::rightTop().y/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
}

void Box2dLayer::update(float dt) {
    int velocityIterations = 8;
    int positionIterations = 1;
    
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    world->Step(dt, velocityIterations, positionIterations);
   
}

void Box2dLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    //
    // IMPORTANT:
    // This is only for debug purposes
    // It is recommend to disable it
    //
    Layer::draw(renderer, transform, flags);
    
    GL::enableVertexAttribs( cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION );
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

    _modelViewMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(Box2dLayer::onDraw, this);
    renderer->addCommand(&_customCommand);

    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

}

void Box2dLayer::onDraw()
{
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    
    Mat4 oldMV;
    oldMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewMV);
    world->DrawDebugData();
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, oldMV);
}

//void Box2dLayer::onRecieveEvent(cocos2d::Ref *pref) {
//    __String* data = dynamic_cast<__String*>(pref);
//    float infor = atof(data->getCString());
//    float distance = infor - (((int)infor) / 1000)*1000;
//}

void Box2dLayer::addSkipScore(cocos2d::Ref *pRef) {
    score++;
    scoreLabel->setString(convertIntToString(score));
    SoundPlayer::getInstance()->playCommonEffect("sound/score.mp3");
}

void Box2dLayer::addB2Body(Vec2 startPos, bool useStartPos /*=false*/){
    if (centerDelta == -1000) {
        int trueFlase = arc4random() % 2;
        int x = arc4random() % 10 + 25;
        centerDelta = trueFlase == 0 ? x : -x;
    }
//    log("the ceter delta is %.2f", centerDelta);
    addBrickCount++;
    
    float Posy = useStartPos == false ? obstacleY : startPos.y + 750;
    Color3B brickColor = allColors.at((addBrickCount / 5) % ColorCount);
    {
        b2BodySprite* pSprite = b2BodySprite::create("brick2.png");
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.userData = (void*)kMonster;
        bodyDef.position.Set((STVisibleRect::getCenterOfScene().x + centerDelta - 120 - pSprite->getContentSize().width/2.0)/PTM_RATIO, (Posy)/PTM_RATIO);
        b2Body* _body = world->CreateBody(&bodyDef);
        // Define another box shape for our dynamic body.
        GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody(_body, "brick2");
        
        _body->SetGravityScale(0);
        _body->SetBullet(true);
        pSprite->setB2Body(_body);
        pSprite->setPTMRatio(PTM_RATIO);
        pSprite->setColor(brickColor);
        pSprite->setPosition(Vec2(STVisibleRect::getCenterOfScene().x + centerDelta - 120 - pSprite->getContentSize().width/2.0, Posy));
        addChild(pSprite);
        pSprite->addMoveEventNotify();
        pSprite->setCheckSkip(true);
        pSprite->setDelegate(this);
    }
    {
        b2BodySprite* pSprite = b2BodySprite::create("brick2.png");
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.userData = (void*)kMonster;
        bodyDef.position.Set((STVisibleRect::getCenterOfScene().x + 120 + centerDelta + pSprite->getContentSize().width/2.0)/PTM_RATIO, (Posy )/PTM_RATIO);
        b2Body* _body = world->CreateBody(&bodyDef);
        // Define another box shape for our dynamic body.

        
        GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody(_body, "brick2");
        _body->SetGravityScale(0);
        _body->SetBullet(true);
        pSprite->setB2Body(_body);
        pSprite->setPTMRatio(PTM_RATIO);
        pSprite->setPosition(Vec2(STVisibleRect::getCenterOfScene().x + 120 + centerDelta + pSprite->getContentSize().width/2.0, Posy));
        pSprite->setColor(brickColor);
        addChild(pSprite);
        pSprite->addMoveEventNotify();
//        pSprite->addComponent(new BlockComponent());
    }

    {
        addSmallBrick1(Posy);
        addSmallBrick2(Posy);
        
    }
}

void Box2dLayer::addSmallBrick1(float Posy){
    Color3B brickColor = allColors.at((addBrickCount / 5) % ColorCount);
    
    int rand = arc4random() % 11;
    float delta = 25 * (rand - 5);

    b2BodySprite* pSprite = b2BodySprite::create("brick3.png");
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.userData = (void*)kMonster;
    bodyDef.position.Set((STVisibleRect::getCenterOfScene().x +delta)/PTM_RATIO, (Posy +240)/PTM_RATIO);
    b2Body* _body = world->CreateBody(&bodyDef);
    // Define another box shape for our dynamic body.
    
    
    GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody(_body, "brick3");
    _body->SetGravityScale(0);
    _body->SetBullet(true);
    pSprite->setB2Body(_body);
    pSprite->setPTMRatio(PTM_RATIO);
    pSprite->setPosition(Vec2(STVisibleRect::getCenterOfScene().x + centerDelta + delta, Posy+240));
    pSprite->setColor(brickColor);
    addChild(pSprite);

    pSprite->addMoveEventNotify();
//    smallBrick1 = pSprite;
//    smallBrick1->setVisible(false);
}

void Box2dLayer::addSmallBrick2(float Posy){
    int trueFlase = arc4random() % 2;
    int x = arc4random() % 10 + 25;
    centerDelta = trueFlase == 0 ? x : -x;
    Color3B brickColor = allColors.at((addBrickCount / 5) % ColorCount);
    
    int rand = arc4random() % 11;
    float delta = 25 * (rand - 5);
    b2BodySprite* pSprite = b2BodySprite::create("brick3.png");
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.userData = (void*)kMonster;
    bodyDef.position.Set((STVisibleRect::getCenterOfScene().x + delta)/PTM_RATIO, (Posy + 580)/PTM_RATIO);
    b2Body* _body = world->CreateBody(&bodyDef);
    // Define another box shape for our dynamic body.
    
    
    GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody(_body, "brick3");
    _body->SetGravityScale(0);
    _body->SetBullet(true);
    pSprite->setB2Body(_body);
    pSprite->setPTMRatio(PTM_RATIO);
    pSprite->setPosition(Vec2(STVisibleRect::getCenterOfScene().x + centerDelta + delta, Posy+580));
    pSprite->setColor(brickColor);
    addChild(pSprite);
    pSprite->addMoveEventNotify();

//    smallBrick2 = pSprite;
//    smallBrick2->setVisible(false);
}

void Box2dLayer::addBrickBody(){
    brickSprite = BrickSprite::create("brick1.png");
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.userData = (void*)kBrick;
    bodyDef.position.Set(STVisibleRect::getCenterOfScene().x / PTM_RATIO, (STVisibleRect::getCenterOfScene().y - 50) / PTM_RATIO);
    _Brickbody = world->CreateBody(&bodyDef);
    // Define another box shape for our dynamic body.
    
    GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody(_Brickbody, "brick1");
    
    _Brickbody->SetGravityScale(0);
    _Brickbody->SetBullet(true);
    //    b2MassData* pData = nullptr;
    //    _Brickbody->GetMassData(pData);
    brickSprite->setB2Body(_Brickbody);
    brickSprite->setPTMRatio(PTM_RATIO);
    brickSprite->setColor(Color3B::BLACK);
    brickSprite->setIgnoreBodyRotation(true);
    _Brickbody->SetFixedRotation(false);
    brickSprite->addComponent(new RunComponent());
    addChild(brickSprite);
    brickSprite->scheduleUpdate();
    
    tipSprite = Sprite::create("res/ui/tip.png");
    tipSprite->setAnchorPoint(Vec2(0.5, 0));
    tipSprite->setPosition(STVisibleRect::getCenterOfScene().x, STVisibleRect::getCenterOfScene().y - 50 + 32);
    addChild(tipSprite, 12);
    
    Sprite* start = Sprite::create(LocalizeString("res/ui/start.png"));
    start->setPosition(Vec2(tipSprite->getContentSize().width / 2.0, -130));
    tipSprite->addChild(start);
    
}

void Box2dLayer::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *unused_event) {
    
    size_t size = touches.size();
    for (int i = 0; i < size && i < 2; ++i) {
        SoundPlayer::getInstance()->playCommonEffect("sound/jump.mp3");
        Touch* touch = touches.at(i);
        if (tipSprite != nullptr) {
            tipSprite->runAction(Sequence::create(EaseSineInOut::create(FadeOut::create(0.2f)), CallFunc::create([=]{
                tipSprite->removeFromParent();
                tipSprite = nullptr;
            }), NULL));
        }
        if (touch->getLocation().x > Director::getInstance()->getVisibleOrigin().x + Director::getInstance()->getVisibleSize().width / 2.0) {
            brickSprite->tapRSide();
        }else {
            brickSprite->tapLSide();
        }
    }
    
}

//void Box2dLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
//    //    b2Vec2 vel = _Brickbody->GetLinearVelocity();
////    brickSprite->tapEnded();
//}

void Box2dLayer::onFirstTimeMove(b2BodySprite *spr) {
    addB2Body(spr->getPosition() , true);
}

void Box2dLayer::BeginContact(b2Contact *contact) {
    
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    char* Astring = (char*)bodyA->GetUserData();
    char* Bstring = (char*)bodyB->GetUserData();
    //    log("A string is %s", Astring);
    //    log("B string is %s", Bstring);
    if (CompareTwo(__String::create(Astring), __String::create(Bstring), kBrick, kMonster) == true) {
        world->SetContactListener(nullptr);
        brickSprite->brickDie();
    }
}

void Box2dLayer::EndContact(b2Contact *contact) {
    
}

void Box2dLayer::onGameOver(cocos2d::Ref *pref) {
    int highestScore = CCUserDefault::getInstance()->getIntegerForKey(kHighestScore, 0);
    if (score > highestScore) {
        CCUserDefault::getInstance()->setIntegerForKey(kHighestScore, score);
        CCUserDefault::getInstance()->flush();
        LeaderboardAdaptor::submitScore(score, "block_score");
    }
    CCUserDefault::getInstance()->setIntegerForKey(kCurrentScore, score);
    CCUserDefault::getInstance()->flush();
    replaceTheScene<FinishScene>();
    
}


bool Box2dLayer::CompareTwo(cocos2d::__String *src1, cocos2d::__String *src2, const string &dst1, const string &dst2) {
    if (string(src1->getCString()).find(dst1.c_str()) != string::npos && string(src2->getCString()).find(dst2.c_str()) != string::npos) {
        return true;
    }
    if (string(src1->getCString()).find(dst2.c_str()) != string::npos && string(src2->getCString()).find(dst1.c_str())  != string::npos) {
        return true;
    }
    return false;
}

void Box2dLayer::addPauseLayer(cocos2d::Ref *pRef) {
    brickSprite->pause();
    pauseLayer = LayerColor::create(Color4B(0, 0, 0, 180));
    addChild(pauseLayer, 999);
    pauseLayer->setTouchEnabled(true);
    pauseLayer->setSwallowsTouches(true);
    
    MenuItemSprite* play = CocosHelper::menuItemSprite("res/ui/play.png");
    MenuItemSprite* home = CocosHelper::menuItemSprite("res/ui/pause_home.png");
    home->setAnchorPoint(Vec2(0.5, 0));
    play->setAnchorPoint(Vec2(0.5, 1.0));
    play->setPosition(STVisibleRect::getCenterOfScene() + Vec2(0, -8));
    home->setPosition(STVisibleRect::getCenterOfScene() + Vec2(0, 8));
    play->setTag(kPlayBtn);
    home->setTag(kHomeBtn);
    
    play->setCallback(CC_CALLBACK_1(Box2dLayer::onPauseLayerButtonClick, this));
    home->setCallback(CC_CALLBACK_1(Box2dLayer::onPauseLayerButtonClick, this));
    
    Menu* pMenu = Menu::create(play, home, NULL);
    pMenu->setAnchorPoint(Vec2::ZERO);
    pMenu->setPosition(Vec2::ZERO);
    pauseLayer->addChild(pMenu);
}

void Box2dLayer::onPauseLayerButtonClick(cocos2d::Ref *pRef) {
    Node* pNode = dynamic_cast<Node*>(pRef);
    SoundPlayer::getInstance()->playCommonEffect("sound/click.wav");
    if (pNode->getTag() == kPlayBtn) {
        pauseLayer->runAction(Sequence::create(ScaleTo::create(0.5, 0), CallFunc::create([=]{
            pauseLayer->removeFromParent();
            pauseLayer=nullptr;
        }), NULL));
        brickSprite->resume();
    }else {
        replaceTheScene<HomeScene>();
    }
}
