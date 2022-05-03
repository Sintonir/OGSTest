#pragma once
#include"Slot.h"
#include"StateManager.h"
#include "SlotStateManager.h"
#include "WaitingState.h"
#include"RotateState.h"
#include"WinShowState.h"
#include "Scene.h"
#include "DirectSceneCreator.h"
#include "ButtonBehaviour.h"
#include "ResultsGenerator.h"
#include "AlignedReelsRotateInterface.h"
#include "WinCaptionBehaviour.h"

namespace Game {
    //„Q„u„p„|„y„x„p„ˆ„y„‘ ISlot „ƒ „y„ƒ„„€„|„„x„€„r„p„~„y„u„} „„‚„‘„}„€„z „s„u„~„u„‚„p„ˆ„y„y „ƒ„ˆ„u„~„ „y„x „{„€„t„p.
    class DirectSceneGenerationSlot :
        public ISlot
    {
        std::shared_ptr<StateManager> _stateManager;
        std::shared_ptr<Scene::Scene> _scene;
        std::shared_ptr<GameLogic::IResultsGenerator> _generator;

    public:
        void Init();
        void Update(float dt);
        std::shared_ptr<Scene::Scene> GetScene();
    };
}

