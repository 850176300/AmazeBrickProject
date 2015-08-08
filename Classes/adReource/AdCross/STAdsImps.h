//
//  STAdsImps.h
//  AmazingBrick
//
//  Created by liuwei on 15/7/29.
//
//

#ifndef __AmazingBrick__STAdsImps__
#define __AmazingBrick__STAdsImps__

#include <stdio.h>
#include "STAdsDelegate.h"
#include "SingleTon.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;
class STAdsImps : public SingleTon<STAdsImps> , public STAdsDelegate{
    friend class SingleTon<STAdsImps>;
public:
    /**
     * @brief This event is called once an ad loads successfully.
     */
    virtual void onBannerLoadSuccessfully() {};
    
    /**
     * @brief This event is called if an ad fails to load.
     */
    virtual void onBannerLoadFailed(int errorCode) {};
    
    /**
     * @brief Sent when the banner has just taken over the screen.
     */
    virtual void onBannerClicked() {};
    
    /**
     * @brief Sent when an expanded banner has collapsed back to its original size.
     */
    virtual void onBannerDismissed() {};
    
    /**
     * @brief This event is called once an interstitial ad loads successfully.
     */
    virtual void onInterstitialAdLoaded(int type) {};
    
    /**
     * @brief This event is called if an interstitial ad fails to load.
     */
    virtual void onInterstitialAdFailed(int errorCode,int type) {
        UserDefault::getInstance()->setIntegerForKey("AdWaitingCount", 3);
        UserDefault::getInstance()->flush();

    };
    
    /**
     * @brief This event is called if an interstitial ad shown.
     */
    virtual void onInterstitialShown(int type) {};
    
    /**
     * @brief This event is called if an interstitial ad closed.
     */
    virtual void onInterstitialDismissed(int  type) {};
    
};

#endif /* defined(__AmazingBrick__STAdsImps__) */
