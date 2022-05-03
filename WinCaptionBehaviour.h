#pragma once
#include "ObjectBehaviour.h"
#include "Node.h"
#include "Caption.h"
#include <functional>
namespace Game {
    //„H„p„t„p„v„„ „„€„{„p„x „{„€„‚„‚„u„{„„„~„€„s„€ „r„„y„s„‚„„Š„p.
    class WinCaptionBehaviour :
        public Scene::ObjectBehaviour
    {
        std::function<size_t()> _prizeFunction;
    public:
        void SetPrizeFunction(std::function<size_t()>function) {
            _prizeFunction = function;
        }
        void OnActivate();
    };
}

