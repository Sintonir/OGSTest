#pragma once
#include "ObjectBehaviour.h"
#include "SymbolProvider.h"

namespace Game {
    //Behaviour „ƒ„y„}„r„€„|„p, „t„|„‘ „„€„|„…„‰„u„~„y„‘ id „ƒ„y„}„r„€„|„p „„€ „~„€„t„u „ƒ „~„y„}.
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
