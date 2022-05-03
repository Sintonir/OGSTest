#include "WinCaptionBehaviour.h"

void Game::WinCaptionBehaviour::OnActivate() {
    auto caption = std::dynamic_pointer_cast<Scene::Caption>(GetNode()->GetDrawable());
    if (!caption||!_prizeFunction)
        return;
    caption->SetText("Your win is "+std::to_string(_prizeFunction()));
    auto bounds = caption->GetBounds();
    caption->SetOrigin(sf::Vector2f(bounds.width / 2, bounds.height / 2));

}
