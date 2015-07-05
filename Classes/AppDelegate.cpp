#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "Box2dLayer.h"
#include "GB2ShapeCache-x.h"
#include "STVisibleRect.h"
#include "SuperGlobal.h"
#include "LoadingScene.h"
USING_NS_CC;
USING_NS_ST;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//void AppDelegate::initGLContextAttrs()
//{
//    //set OpenGL context attributions,now can only set six attributions:
//    //red,green,blue,alpha,depth,stencil
//
//    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
//    
//    GLView::setGLContextAttrs(glContextAttrs);
//}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);


    cocos2d::Director::getInstance()->setProjection(Director::Projection::_2D);
    
    STVisibleRect::setupVisibleRect(glview->getFrameSize(), Size(768, 1024));
    
    Size realDesignSize = STVisibleRect::getRealDesignSize();
    
    glview->setDesignResolutionSize(realDesignSize.width, realDesignSize.height, ResolutionPolicy::NO_BORDER);
    
    GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile("BrickShape.plist");
    // create a scene. it's an autorelease object
    
    replaceTheScene<FinishScene>();
   
    

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
