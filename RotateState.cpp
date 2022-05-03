#include "RotateState.h"

void Game::RotateState::OnStart() {
	_rotate->Start();
	_stopButtonNode->SetActive(true);
	_generator->GenerateResult();
}

void Game::RotateState::OnEnd() {
	if (_rotate->IsRotateActive())
		_rotate->Stop();
	_stopButtonNode->SetActive(false);
}
