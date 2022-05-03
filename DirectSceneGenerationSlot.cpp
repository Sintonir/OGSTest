#include "DirectSceneGenerationSlot.h"

void Game::DirectSceneGenerationSlot::Update(float dt) {
	_stateManager->UpdateStateManaget(dt);
	_scene->Update(dt);
}

std::shared_ptr<Scene::Scene> Game::DirectSceneGenerationSlot::GetScene() {
	return _scene;
}

void Game::DirectSceneGenerationSlot::Init() {
	auto sceneGenerator = std::make_shared<DirectSceneCreator>();
	_scene = sceneGenerator->GetScene();
	auto sceneRootNode = _scene->GetRootObject();


	auto resultGenerator = std::make_shared<GameLogic::RandomResultGenerator>();
	_generator = resultGenerator;
	auto patternChecker = std::make_shared<GameLogic::SimplePatternChecker>();
	resultGenerator->SetPatternChecker(patternChecker);

	auto buttonStartNode = sceneRootNode->FindChildByName("buttonStart");
	auto buttonStopNode = sceneRootNode->FindChildByName("buttonStop");
	auto reelsNode = sceneRootNode->FindChildByName("reels");
	auto winCaptionNode = sceneRootNode->FindChildByName("winCaption");

	auto reelsBehaviour = reelsNode->GetBehaviour<AlignedReelsBehaviour>();
	auto rotate = std::make_shared<AlignedReelsRotateInterface>(reelsBehaviour);
	reelsBehaviour->SetMatrixFunc([resultGenerator]() {return resultGenerator->GetResultMatrix(); });
	reelsBehaviour->SetRotateFunc([resultGenerator](size_t reel) {return resultGenerator->GetRotateSymbol(reel); });

	winCaptionNode->GetBehaviour<WinCaptionBehaviour>()->SetPrizeFunction([resultGenerator]() {return resultGenerator->GetPrize(); });

	auto winFramesBehaviour = reelsNode->GetBehaviour<WinShowFramesBehaviour>();
	auto slotStateManager = std::make_shared<SlotStateManager>();
	_stateManager = slotStateManager;

	auto waitingState = std::make_shared<WaitingState>();
	waitingState->SetButtonNode(buttonStartNode);
	slotStateManager->AddState(waitingState);

	auto rotateState = std::make_shared<RotateState>();
	rotateState->SetRotate(rotate);
	rotateState->SetButtonNode(buttonStopNode);
	rotateState->SetResultsGenerator(_generator);
	slotStateManager->AddState(rotateState);

	for (size_t i = 0; i < 3; i++) {
		std::vector<std::vector<bool>> pattern;
		pattern.resize(3);
		for (size_t j = 0; j < 3; j++)
		{
			pattern.at(j).resize(3, false);
		}
		for (size_t j = 0; j < 3; j++) {
			pattern.at(j).at(i) = true;
		}
		resultGenerator->AddPattern(pattern);
	}

	auto winShowState = std::make_shared<WinShowState>();
	winShowState->SetCaptionNode(winCaptionNode);
	winShowState->SetFrames(winFramesBehaviour);
	winShowState->SetPatternsFunction([resultGenerator]() {return resultGenerator->GetWinPatterns(); });
	slotStateManager->AddState(winShowState);

	auto buttonStartBeh = std::make_shared<Scene::ButtonBehaviour>(_localMouseFunc);
	buttonStartNode->AddBehaviour(buttonStartBeh);
	buttonStartBeh->SetFunction([manager = _stateManager.get(), state = rotateState.get()](){manager->ChangeState(state->shared_from_this()); });

	auto buttonStopBeh = std::make_shared<Scene::ButtonBehaviour>(_localMouseFunc);
	buttonStopNode->AddBehaviour(buttonStopBeh);
	buttonStopBeh->SetFunction([manager = _stateManager.get(), state = winShowState.get()](){manager->ChangeState(state->shared_from_this()); });
	buttonStopNode->SetActive(false);

}
