#pragma once
#include"Scene.h"
//„I„~„„„u„‚„†„u„z„ƒ, „r „€„ƒ„~„€„r„~„€„}, „t„|„‘ „ƒ„€„x„t„p„~„y„‘ „ƒ„ˆ„u„~„.
class SceneManager
{
public:
	virtual std::shared_ptr<Scene::Scene> GetScene() = 0;
};

