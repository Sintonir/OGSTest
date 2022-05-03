#include "State.h"
namespace Game {
	void State::Deactivate()
	{
		OnEnd();
	}

	void State::Activate()
	{
		OnStart();
	}
}