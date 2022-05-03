#pragma once
#include "State.h"
#include"WinShowFramesBehaviour.h"
#include<functional>
namespace Game {
    class WinShowState :
        public State
    {
        using WinPattern = std::vector<std::vector<bool>>;
        std::function<std::vector<WinPattern>()> _winPatternsFunction;
        std::shared_ptr<WinShowFramesBehaviour> _frames;
        Scene::Node::Ptr _captionNode;
        float _winShowLength = 5;
        float _time = 0;

    protected:
        virtual void OnStart();
        virtual void OnEnd();
    public:
        void Update(float dt) {
            _time += dt;
        }
        bool AwaitsChange() {
            if (_winPatternsFunction().empty())
                return true;
            return _time>_winShowLength;
        }
        void SetCaptionNode(Scene::Node::Ptr node) {
            _captionNode = node;
        }
        void SetFrames(std::shared_ptr<WinShowFramesBehaviour> frames)
        {
            _frames = frames;
        }
        void SetPatternsFunction(std::function<std::vector<WinPattern>()> func) {
            _winPatternsFunction = func;
        }
    };
}
