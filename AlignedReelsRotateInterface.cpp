#include "AlignedReelsRotateInterface.h"

Game::AlignedReelsRotateInterface::AlignedReelsRotateInterface(std::shared_ptr<AlignedReelsBehaviour> reelsBehaviour) :_reelsBehaviour(reelsBehaviour) {}

bool Game::AlignedReelsRotateInterface::IsRotateActive() {
	return _reelsBehaviour->IsRotate();
}

void Game::AlignedReelsRotateInterface::Start() {
	_reelsBehaviour->Start();
}

void Game::AlignedReelsRotateInterface::Stop() {
	_reelsBehaviour->Stop();
}
