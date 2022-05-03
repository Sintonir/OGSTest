#include "ReelRotateBehaviour.h"
#include "SymbolBehaviour.h"

void Game::ReelRotateBehaviour::Init() {
    _provider = std::make_shared<SimpleSymbolProvider>();
    Reset();
}

void Game::ReelRotateBehaviour::Update(float dt) {
    float accel = 0;
    _phaseTime += dt;
    switch (_currentState) {
    case State::STOPPED:
        return;
    case State::STARTING:
        accel = StartingAcceleration();
        break;
    case State::FULLSPEED:
        _currentSpeed = _maxSpeed;
        accel = 0;
        break;
    case State::STOPPING:
        accel -= StoppingDecceleration();
        break;
    case State::BOUNCE:
        _currentSpeed = -_bounceSpeed;
        break;
    default:break;
    }
    float move = dt * _currentSpeed + dt * dt * accel / 2;
    int needDeleteSymbol = 0;
    for (auto symbol : _symbols) {
        symbol->move(sf::Vector2f(0, move));
        if (symbol->getPosition().y>_bottomAlign+_symbolHeight) {
            needDeleteSymbol++;
        }
    }
    for (int i = 0; i < needDeleteSymbol; i++) {
        GetNode()->RemoveChild(_symbols.front());
        _symbols.erase(_symbols.begin());

        size_t nextSymbol;
        auto result = _resultFunction();
        if (SymbolsUntilResult()-i >= 0||i - SymbolsUntilResult()>result.size()){
            nextSymbol = _rotateSymbolFunction();
        }
        else {
            nextSymbol = _resultFunction()[result.size() - i + SymbolsUntilResult()];
        }
        auto newSymbol = CreateSymbol(nextSymbol);
        newSymbol->SetActive(true);
        newSymbol->setPosition(_symbols.back()->getPosition() - sf::Vector2f(0, _symbolHeight));
        GetNode()->AddChild(newSymbol);
        _symbols.push_back(newSymbol);
    }
    _currentSpeed += accel * dt;
    auto state = _currentState;
    _currentState = CheckStateChange(_currentState);
    if (state != _currentState)
        _phaseTime = 0;

}

int Game::ReelRotateBehaviour::SymbolsUntilResult() const{
    float dist = 0;
    switch (_currentState) {
    case State::STOPPED:
            return 0;
    case State::BOUNCE:
        return 0;
    case State::STARTING:
        dist += _minFullspeedTime * _maxSpeed;
    case State::FULLSPEED:
        dist += _maxSpeed * _slowTime / 2;
    default:break;
    }
    switch (_currentState)
    {
    case State::STARTING:
        dist+=(_currentSpeed + _maxSpeed)*(_accelTime-_phaseTime)/2;
        break;
    case State::FULLSPEED:
        dist += _currentSpeed * (_minFullspeedTime-_phaseTime);
        break;
    case State::STOPPING:
        dist += (_currentSpeed) * (_slowTime - _phaseTime) / 2;
        break;
    default:break;
    }
    size_t symbols = dist / _symbolHeight;
    return  symbols - _maxSymbolsOnReel - _invisibleTop;
}

Game::ReelRotateBehaviour::State Game::ReelRotateBehaviour::CheckStateChange(State state) const {
    switch (state)
    {
    case State::STOPPED:
        return State::STOPPED;
    case State::STARTING:
        if (_phaseTime >= _accelTime)
            return State::FULLSPEED;
        else return State::STARTING;
    case State::FULLSPEED:
        if (_phaseTime >= _minFullspeedTime)
            return State::STOPPING;
        else return State::FULLSPEED;
    case State::STOPPING:
        if (_phaseTime >= _slowTime)
            return State::BOUNCE;
        else return State::STOPPING;
    case State::BOUNCE:
        if (_symbols.front()->getPosition().y <= _bottomAlign)
            return State::STOPPED;
        else return State::BOUNCE;
    default:
        return state;
    }
}

Scene::Node::Ptr Game::ReelRotateBehaviour::CreateSymbol(size_t symbol) {
    auto result = std::make_shared<Scene::Node>();
    result->SetDrawable(_provider->GetSymbolDrawable(symbol));
    result->AddBehaviour(std::make_shared<SymbolBehaviour>(symbol));
    return result;
}

void Game::ReelRotateBehaviour::Reset() {
    auto newSymbol = CreateSymbol(0);
    sf::Vector2f position = sf::Vector2f(0, _bottomAlign);
    for (size_t i = 0; i < _maxSymbolsOnReel; i++) {
        auto newSymbol = CreateSymbol(0);
        newSymbol->setPosition(position);
        GetNode()->AddChild(newSymbol);
        _symbols.push_back(newSymbol);
        position -= sf::Vector2f(0, _symbolHeight);
    }
}

void Game::ReelRotateBehaviour::Start() {
    _currentState = State::STARTING;
    _currentSpeed = 0;
    _phaseTime = 0;
}


Scene::Node::Ptr Game::ReelRotateBehaviour::GetSymbol(size_t numberFromTop)
{
    auto iter = _symbols.rbegin();
    
    for (size_t i = 0; i <= numberFromTop+_invisibleTop && iter != _symbols.rend(); i++, iter++) {
        
    }
    if (iter != _symbols.rend()) {
        return *iter;
    }
    else return Scene::Node::Ptr();

}

int Game::ReelRotateBehaviour::GetSymbolId(size_t numberFromTop) {
    auto symb = GetSymbol(numberFromTop);
    if(auto beh = symb->GetBehaviour<SymbolBehaviour>())
        return beh->GetId();
    return -1;
}

void Game::ReelRotateBehaviour::Stop() {
    _currentState = State::STOPPED;
    _phaseTime = 0;
    for (auto symbol : _symbols) {
        GetNode()->RemoveChild(symbol);
    }
    _symbols.clear();
    auto position = _bottomAlign;
    for (size_t i = 0; i < _maxSymbolsOnReel; i++) {
        Scene::Node::Ptr symb;
        if (i < _invisibleBottom) {
            symb = CreateSymbol(_rotateSymbolFunction());
        }
        else {
            symb = CreateSymbol(_resultFunction()[_maxSymbolsOnReel - _invisibleTop - i - 1]);
        }
        symb->setPosition(0, position);
        position -= _symbolHeight;
        _symbols.push_back(symb);
        GetNode()->AddChild(symb);
    }

}

