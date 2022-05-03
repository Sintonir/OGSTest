#pragma once
#include "ObjectBehaviour.h"
#include "Node.h"
#include<functional>
namespace Scene {
	class ButtonBehaviour :
		public ObjectBehaviour
	{
		std::function<void()> _onButtonPressedFunction;
		bool _pressReacted = false;
		std::function<sf::Vector2i()> _localMousePosition;
	public:
		ButtonBehaviour(std::function<sf::Vector2i()> localMousePosition);
		bool IsInBounds(sf::Vector2f position);
		void Update(float dt);
		void SetFunction(std::function<void()>function);
	};

}
