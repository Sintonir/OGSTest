#pragma once
#include"Scene.h"
//�I�~���u�����u�z��, �r �����~���r�~���}, �t�|�� �����x�t�p�~�y�� �����u�~��.
class SceneManager
{
public:
	virtual std::shared_ptr<Scene::Scene> GetScene() = 0;
};
