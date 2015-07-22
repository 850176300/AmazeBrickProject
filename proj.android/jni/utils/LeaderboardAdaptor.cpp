#include "LeaderboardAdaptor.h"
#include "GameSharing.h"

void LeaderboardAdaptor::authenticateLocalPlayer()
{
}

void LeaderboardAdaptor::submitScore(size_t score,const char* category)
{
	GameSharing::getInstance()->SubmitScore(score, 0);
}

void LeaderboardAdaptor::showLeaderboard()
{
	GameSharing::getInstance()->ShowLeaderboards(0);
}

void LeaderboardAdaptor::requestScore(std::function<void (int)> callback) {
//	GameSharing::getInstance()->RequestCurrentScoreFromLeaderboard(0, callback);
}
