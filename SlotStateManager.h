#pragma once
#include "StateManager.h"
namespace Game {
    //„Q„u„p„|„y„x„p„ˆ„y„‘ StateManager, „~„y„‰„u„s„€ „~„u „x„~„p„u„„ „„‚„€ „„„€, „{„p„{„y„u „ƒ„€„ƒ„„„€„‘„~„y„‘ „y„ƒ„„€„|„„x„…„u„„.
    class SlotStateManager :
        public StateManager
    {
    private:
        std::vector<State::Ptr> _states;
        size_t _currentState = 0;
    protected:
        virtual State::Ptr ExpectedState() {
            if (GetCurrentState()->AwaitsChange()) {
                return GetNextExpecterState();
            }
            return GetCurrentState();
        };
        State::Ptr GetNextExpecterState() {
            return _states.at((_currentState + 1) % _states.size());
        }
        void OnStateChange(State::Ptr oldState, State::Ptr newState) {
            if (GetNextExpecterState() == newState) {
                _currentState = (_currentState + 1) % _states.size();
            }
            else {
                for (size_t i = 0; i < _states.size(); i++) {
                    if (_states.at(i) == newState) {
                        _currentState = i;
                        return;
                    }
                }
                AddState(newState);
                _currentState = _states.size() - 1;
            }
        }
    public:
        State::Ptr GetCurrentState() {
            return _states.at(_currentState);
        }
        void AddState(State::Ptr state) {
            for (auto managedState:_states) {
                if (managedState == state)
                {
                    return;
                }
            }
            _states.push_back(state);
        }

        
    };
}

