#pragma once
#include "ObjectBehaviour.h"
#include "AlignedReelsBehaviour.h"
namespace Game {
    //„R„€„x„t„p„v„„ „‚„p„}„{„y „r„€„{„‚„…„s „r„„y„s„‚„„Š„~„„‡ „ƒ„y„}„r„€„|„€„r.
    class WinShowFramesBehaviour :
        public Scene::ObjectBehaviour
    {
        std::shared_ptr<AlignedReelsBehaviour> _reels;
        std::vector<std::vector<Scene::Node::Ptr>> _frameNodes;
        float _combinationShowTime = 1.0f;
        float _timeSinceCombinationChanged = 0;
        size_t _currentCombination = 0;
    public:
        void AddCombination(std::vector<std::vector<bool>> pattern, sf::Color color);
        void ShowCombination(size_t index);
        void Init();
        void Reset();
        void Update(float dt);
        void OnActivate();
        void SetTimeForCombination(float time) {
            _combinationShowTime = time;
        }
    };
}

