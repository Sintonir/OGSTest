#include "AlignedReelsBehaviour.h"

void Game::AlignedReelsBehaviour::Reset() {
	for (auto reel : _reelBehaviours) {
		reel->Reset();
	}
}

void Game::AlignedReelsBehaviour::SetupReels(std::vector<size_t> symbolsByReel) {
	_reelBehaviours.clear();
	GetNode()->RemoveAllChildren();
	for (size_t i = 0; i < symbolsByReel.size(); i++) {
		auto reelNode = std::make_shared<Scene::Node>();
		auto reel = std::make_shared<ReelRotateBehaviour>();
		reelNode->AddBehaviour(reel);
		reelNode->setPosition(sf::Vector2f(_width * i, 0));
		reel->SetBottomAlign(_baseAlign);
		reel->SetSymbolsOnReel(symbolsByReel.at(i));
		reel->SetRotationTime(_baseRotateTime + _timeDiff * i);
		if (_provider) {
			reel->SetSymbolProvider(_provider);
		}
		_reelBehaviours.push_back(reel);
		GetNode()->AddChild(reelNode);
	}
}

void Game::AlignedReelsBehaviour::SetBaseAlign(float align) {
	_baseAlign = align;
}

void Game::AlignedReelsBehaviour::SetWidth(float width) {
	_width = width;
}

void Game::AlignedReelsBehaviour::SetProvider(std::shared_ptr<SymbolProviderBase> provider) {
	_provider = provider;
	for (auto reel : _reelBehaviours)
	{
		reel->SetSymbolProvider(_provider);
	}
}

void Game::AlignedReelsBehaviour::SetAlignForReel(float align, size_t reel) {
	_reelBehaviours.at(reel)->SetBottomAlign(align);
}

bool Game::AlignedReelsBehaviour::IsRotate() {
	for (auto beh : _reelBehaviours) {
		if (beh->IsRotate())
		{
			return true;
		}
	}
	return false;
}


Game::ReelRotateBehaviour::Ptr Game::AlignedReelsBehaviour::GetReelBehaviour(size_t reel) {
	return _reelBehaviours.at(reel);
}

size_t Game::AlignedReelsBehaviour::GetSymbolId(size_t reel, size_t row) {
	return _reelBehaviours.at(reel)->GetSymbolId(row);
}

Scene::Node::Ptr Game::AlignedReelsBehaviour::GetSymbol(size_t reel, size_t row) {
	return _reelBehaviours.at(reel)->GetSymbol(row);
}

void Game::AlignedReelsBehaviour::Stop() {
	for (auto reel : _reelBehaviours)
		reel->Stop();
}

void Game::AlignedReelsBehaviour::Start() {
	for (auto reel : _reelBehaviours)
		reel->Start();
}

void Game::AlignedReelsBehaviour::SetMatrixFunc(std::function<std::vector<std::vector<int>>()> matrixFunc) {
	for (size_t i = 0; i < _reelBehaviours.size(); i++) {
		_reelBehaviours.at(i)->SetResultSymbolFunction([i, matrixFunc]() {
			auto matr = matrixFunc();
			return matr[i];
			});
	}
}

void Game::AlignedReelsBehaviour::SetRotateFunc(std::function<int(size_t)> func) {
	for (size_t i = 0; i < _reelBehaviours.size(); i++) {
		_reelBehaviours.at(i)->SetRotateSymbolFunction([i, func]() {return func(i); });
	}
}

