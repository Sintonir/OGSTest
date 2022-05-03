#include "ReeelsBgrBehaviour.h"

void Game::ReeelsBgrBehaviour::Init() {
    if (_background) {
        sf::Vector2f position(0, 0);
        for (size_t i = 0; i < _reelsNumber; i++) {
            auto bgrNode = std::make_shared<Scene::Node>();
            bgrNode->SetDrawable(_background);
            bgrNode->setPosition(position);
            bgrNode->SetPriority(-10);
            GetNode()->AddChild(bgrNode);
            position.x += _width;
        }
    }
    if (_separator) {
        sf::Vector2f position(_firstSeparatorOffset, 0);
        for (size_t i = 0; i < _reelsNumber - 1; i++) {
            auto sepNode = std::make_shared<Scene::Node>();
            sepNode->SetDrawable(_separator);
            sepNode->setPosition(position);
            sepNode->SetPriority(10);
            GetNode()->AddChild(sepNode);
            position.x += _width;
        }
    }
}
