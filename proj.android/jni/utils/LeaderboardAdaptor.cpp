#include "LeaderboardAdaptor.h"
#include "GameSharing.h"

void LeaderboardAdaptor::authenticateLocalPlayer()
{
}

void LeaderboardAdaptor::submitScore(size_t score,const char* category)
{
	GameSharing::SubmitScore(score, 0);
}

void LeaderboardAdaptor::showLeaderboard()
{
	GameSharing::ShowLeaderboards(0);
}

void LeaderboardAdaptor::requestScore(std::function<void (int)> callback) {
	GameSharing::RequestCurrentScoreFromLeaderboard(0, callback);
}
