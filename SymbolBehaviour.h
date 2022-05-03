#pragma once
#include "ObjectBehaviour.h"
#include "SymbolProvider.h"

namespace Game {
    //Behaviour ���y�}�r���|�p, �t�|�� �����|�����u�~�y�� id ���y�}�r���|�p ���� �~���t�u �� �~�y�}.
    class SymbolBehaviour :
        public Scene::ObjectBehaviour
    {
        size_t _id;
    public:
        SymbolBehaviour(size_t id) : _id(id) {}
        size_t GetId() {
            return _id;
        }
    };
}