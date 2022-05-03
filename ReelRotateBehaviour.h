#pragma once
#include "ObjectBehaviour.h"
#include "SymbolProvider.h"
#include "Node.h"
#include <list>
#include <functional>
namespace Game {
    //„B„‚„p„‹„p„u„„ „q„p„‚„p„q„p„~„. „A„€„|„„Š„y„~„ƒ„„„r„€ „„p„‚„p„}„u„„„‚„€„r „ƒ„„„€„y„|„€ „q„ „x„p„t„p„r„p„„„ „‰„u„‚„u„x „{„€„~„†„y„s„…„‚„p„ˆ„y„€„~„~„„u „†„p„z„|„ „y„|„y „‡„€„„„‘ „q„ „‰„u„‚„u„x „†„…„~„{„ˆ„y„y „r „{„€„t„u.
    class ReelRotateBehaviour :
        public Scene::ObjectBehaviour
    {
    protected:
        enum struct State {
            STOPPED = 0,
            STARTING,
            FULLSPEED,
            STOPPING,
            BOUNCE
        };
    private:
        std::list<Scene::Node::Ptr> _symbols;
        float _bottomAlign = 400;
        //„X„„„€„q„ „ƒ„y„}„r„€„|„ „~„u „„‚„€„„p„t„p„|„y „y „~„u „„€„‘„r„|„‘„|„y„ƒ„ „ƒ„|„y„Š„{„€„} „‚„u„x„{„€, „t„€„|„w„u„~ „q„„„„ „{„p„{ „}„y„~„y„}„…„} „€„t„y„~ „‚„‘„t „ƒ„y„}„r„€„|„€„r, „{„€„„„€„‚„„z „~„u „q„…„t„u„„ „r„y„t„u„~ „„‚„y „€„ƒ„„„p„~„€„r„{„u.
        size_t _maxSymbolsOnReel = 4;
        size_t _invisibleTop = 0;
        size_t _invisibleBottom = 1;
        float _maxSpeed = 1000;
        float _accelTime = 0.3f;
        float _minFullspeedTime = 2.0f;
        float _slowTime = 1.0f;
        float _bounce = 50;
        float _bounceSpeed = 150;
        float _symbolHeight = 110;
        float _phaseTime = 0;
        float _currentSpeed = 0;
        State _currentState = State::STOPPED;
        std::function<int()> _rotateSymbolFunction = []() {return 0; };
        std::function<std::vector<int>()>_resultFunction = []() {return std::vector<int>( { 1, 2, 3 }); };
        std::shared_ptr<SymbolProviderBase> _provider;
    public:
        //„K „ƒ„€„w„p„|„u„~„y„, „~„u „t„|„‘ „r„ƒ„u„‡ „„p„‚„p„}„u„„„‚„€„r „‘ „ƒ„€„x„t„p„| „x„p„t„p„„‹„y„u „y„‡ „†„…„~„{„ˆ„y„y.
        void SetBottomAlign(float align) {
            _bottomAlign = align;
        }
        void SetRotationTime(float time) {
            _minFullspeedTime = time;
        }
        void SetSymbolsOnReel(size_t symbols) {
            _maxSymbolsOnReel = symbols;
        }
        virtual void OnActivate() {};
        virtual void OnDeactivate() {};
        virtual void Init();;
        float StartingAcceleration() {
            return _maxSpeed / _accelTime;
        }
        float StoppingDecceleration() {
            return _maxSpeed / _slowTime;
        }
        virtual void Update(float dt);
        int SymbolsUntilResult() const;
        State CheckStateChange(State state)const;
        Scene::Node::Ptr CreateSymbol(size_t symbol);
        void SetRotateSymbolFunction(std::function<int()> func) {
            _rotateSymbolFunction = func;
        }
        void SetResultSymbolFunction(std::function<std::vector<int>()> func) {
            _resultFunction = func;
        }
        virtual void Reset();;
        virtual void OnObjectInitFinished() {};
        virtual void Start();
        void Stop();
        Scene::Node::Ptr GetSymbol(size_t numberFromTop);
        int GetSymbolId(size_t numberFromTop);
        void SetSymbolProvider(std::shared_ptr<SymbolProviderBase> provider) {
            _provider = provider;
        }
        bool IsRotate() {
            return _currentState != State::STOPPED;
        }
    };

}