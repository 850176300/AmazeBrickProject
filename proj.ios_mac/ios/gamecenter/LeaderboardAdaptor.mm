//
//  LeaderboardAdaptor.cpp
//  KGI2001
//
//  Created by wuguiling on 15/7/13.
//
//

#include "LeaderboardAdaptor.h"
#import "GameKitHelper.h"

void LeaderboardAdaptor::authenticateLocalPlayer()
{
    [[GameKitHelper sharedGameKitHelper]authenticateLocalPlayer];
}

void LeaderboardAdaptor::submitScore(size_t score,const char* category)
{
    
    [[GameKitHelper sharedGameKitHelper]submitScore:score category:[NSString stringWithUTF8String:category]];
}

void LeaderboardAdaptor::showLeaderboard()
{
    
    [[GameKitHelper sharedGameKitHelper]showLeaderboard];
}

void LeaderboardAdaptor::requestScore(std::function<void (int)> callback) {
    callback(0);
}