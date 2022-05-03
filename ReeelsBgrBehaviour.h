#pragma once
#include "ObjectBehaviour.h"
#include "Drawable.h"
#include "Node.h"
namespace Game {
    //ÑHÑpÑÅÑÄÑ|Ñ~ÑëÑuÑÑ ÑÜÑÄÑ~Ñç ÑqÑpÑÇÑpÑqÑpÑ~ÑÄÑr.
    class ReeelsBgrBehaviour :
        public Scene::ObjectBehaviour
    {
    public:
        using Ptr = std::shared_ptr<ReeelsBgrBehaviour>;
    private:
        Scene::Drawable::Ptr _background;
        Scene::Drawable::Ptr _separator;
        float _width = 110;
        float _firstSeparatorOffset = 105;
        size_t _reelsNumber = 3;
    public:
        void Init();
        void SetBackground(Scene::Drawable::Ptr background) {
            _background = background;
        }
        void SetSeparator(Scene::Drawable::Ptr separator) {
            _separator = separator;
        }
        void SetWidth(float width) {
            _width = width;
        }
        void SetReelsNumber(size_t number) {
            _reelsNumber = number;
        }
    };
}

