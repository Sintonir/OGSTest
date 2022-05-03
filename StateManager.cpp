#include "StateManager.h"
namespace Game {
	void StateManager::UpdateStateManaget(float dt)
	{
		GetCurrentState()->Update(dt);
		Update(dt);
		auto currentState = GetCurrentState();
		auto targetState = ExpectedState();
	    if (currentState != targetState) {
			ChangeState(targetState);
		}
	}

	void StateManager::ChangeState(State::Ptr newState)
	{
		auto oldState = GetCurrentState();
		if (oldState == newState)
			return;
		oldState->Deactivate();
		newState->Activate();
		OnStateChange(oldState, newState);
	}
}