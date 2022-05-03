#pragma once
#include "State.h"
#include<vector>
namespace Game {
	//„I„~„„„u„‚„†„u„z„ƒ „}„p„Š„y„~„ „ƒ„€„ƒ„„„€„‘„~„y„z.
	class StateManager
	{
		protected:
			virtual void Update(float dt) {};
			virtual State::Ptr ExpectedState() = 0;
			virtual void OnStateChange(State::Ptr oldState, State::Ptr newState) {};
			virtual State::Ptr GetNextExpecterState() = 0;
		public:
			void ChangeState(State::Ptr newState);
			void ChangeToNextExpected() {
				ChangeState(GetNextExpecterState());
			}
			virtual State::Ptr GetCurrentState() = 0;
			void UpdateStateManaget(float dt);
	};

}