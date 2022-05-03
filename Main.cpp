
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include "DirectSceneGenerationSlot.h"
#include<chrono>
int main() {

    auto window = std::make_shared<sf::RenderWindow >(sf::VideoMode(800, 600), "My window");
    auto slot = std::make_shared<Game::DirectSceneGenerationSlot>();
    slot->SetLocalMouseFunc([window]() {return sf::Mouse::getPosition(*window); });
    slot->Init();

    auto clock = sf::Clock();
    while (window->isOpen())
    {

        window->clear(sf::Color::Black);
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }
        slot->GetScene()->Draw(window);
        float dt = clock.getElapsedTime().asSeconds();
        clock.restart();
        if (dt > 0.1)
            dt = 0.1f;
        slot->Update(dt);
        window->display();
    }

	return 0;
}