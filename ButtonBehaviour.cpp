#include "ButtonBehaviour.h"

Scene::ButtonBehaviour::ButtonBehaviour(std::function<sf::Vector2i()> localMousePosition) { _localMousePosition = localMousePosition; }

bool Scene::ButtonBehaviour::IsInBounds(sf::Vector2f position) {
	if (!GetNode()->IsActive()) {
		return false;
	}
	auto transform = GetNode()->GetGlobalTransform();
	auto box = GetNode()->GetDrawable()->GetBounds();
	auto globalBox = transform.transformRect(box);
	return globalBox.contains(position);
}

void Scene::ButtonBehaviour::Update(float dt) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2f mousePos(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
		if (_localMousePosition) {
			mousePos.x = _localMousePosition().x;
			mousePos.y = _localMousePosition().y;
		}
		if (IsInBounds(mousePos) && !_pressReacted) {
			_onButtonPressedFunction();
			_pressReacted = true;
		}
	}
	else {
		_pressReacted = false;
	}
}

void Scene::ButtonBehaviour::SetFunction(std::function<void()> function) {
	_onButtonPressedFunction = function;
}
