#include "WinShowFramesBehaviour.h"

void Game::WinShowFramesBehaviour::AddCombination(std::vector<std::vector<bool>> pattern, sf::Color color)
{
    _frameNodes.push_back(std::vector<Scene::Node::Ptr>());
    for (size_t i = 0; i < pattern.size(); i++) {
        for (size_t j = 0; j < pattern.at(i).size(); j++) {
            if (pattern.at(i).at(j)) {
                auto symb = _reels->GetSymbol(i, j);
                auto parent = symb->GetParent();
                auto frame = std::make_shared<Scene::Node>();
                frame->SetPriority(symb->GetPriority() + 1);
                frame->setPosition(symb->getPosition());
                frame->SetParent(parent);
                auto frameRect = std::make_shared<Scene::SFMLRectangle>();
                frameRect->SetColor(sf::Color::Transparent);
                frameRect->SetOutlineColor(color);
                frameRect->SetSize(sf::Vector2f(100, 100));
                frameRect->SetOutlineThickness(5);
                frame->setOrigin(50, 50);
                frame->SetDrawable(frameRect);
                frame->SetActive(false);
                _frameNodes.back().push_back(frame);
            }
        }
    }
}

void Game::WinShowFramesBehaviour::ShowCombination(size_t index) {
    _currentCombination = index;
    for (size_t i = 0; i < _frameNodes.size(); i++) {
        for (size_t j = 0; j < _frameNodes.at(i).size(); j++) {
            if (i != index)
                _frameNodes.at(i).at(j)->SetActive(false);
            else
                _frameNodes.at(i).at(j)->SetActive(true);
        }
    }
}

void Game::WinShowFramesBehaviour::Init() {
    _reels = GetNode()->GetBehaviour<AlignedReelsBehaviour>();
}

void Game::WinShowFramesBehaviour::Reset() {
    for (auto combination : _frameNodes) {
        for (auto node : combination) {
            node->SetParent(std::weak_ptr<Scene::Node>());
        }
    }
    _frameNodes.clear();
}

void Game::WinShowFramesBehaviour::Update(float dt)
{
    if (_frameNodes.empty())
        return;
    _timeSinceCombinationChanged += dt;
    if (_timeSinceCombinationChanged > _combinationShowTime) {
        ShowCombination((_currentCombination + 1)%_frameNodes.size());
        _timeSinceCombinationChanged = 0;
    }
}

void Game::WinShowFramesBehaviour::OnActivate() {
    _timeSinceCombinationChanged = 0;
}
