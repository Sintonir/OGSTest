#pragma once
#include"Scene.h"
#include <functional>
namespace Game {
	//�R�����~�������� �t�|�� ���q���u�t�y�~�u�~�y�� �����u�~�� �y �}�p���y�~�� �������������~�y�z.
	class ISlot
	{
	protected:
		std::function<sf::Vector2i()> _localMouseFunc;
	public:
		virtual void Update(float dt) = 0;
		virtual void Init() = 0;
		virtual std::shared_ptr<Scene::Scene> GetScene() = 0;
		void SetLocalMouseFunc(std::function<sf::Vector2i()> func) {
			_localMouseFunc = func;
		}
	};

}