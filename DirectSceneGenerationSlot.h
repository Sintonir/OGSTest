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
    //?Q?u?p?|?y?x?p???y?? ISlot ?? ?y???????|???x???r?p?~?y?u?} ???????}???z ?s?u?~?u???p???y?y ?????u?~?? ?y?x ?{???t?p.
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

