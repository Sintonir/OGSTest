#include "WinShowState.h"

namespace Game {
    void WinShowState::OnStart() {
        auto patterns = _winPatternsFunction();
        for (auto& pattern : patterns) {
            _frames->AddCombination(pattern, sf::Color::White);
        }
        _frames->ShowCombination(0);
        _captionNode->SetActive(true);
        _time = 0;
    }

    void WinShowState::OnEnd() {
        _frames->Reset();
        _captionNode->SetActive(false);
    }
}