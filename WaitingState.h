#pragma once
#include"State.h"
#include"Node.h"
namespace Game {
	class WaitingState :public State
	{
		Scene::Node::Ptr _startButtonNode;
	public:
		void Update(float dt) override {}
		void OnStart() override {
			_startButtonNode->SetActive(true);
		}
		void OnEnd() override {
			_startButtonNode->SetActive(false);
		}
		void SetButtonNode(Scene::Node::Ptr node) {
			_startButtonNode = node;
		}
		bool AwaitsChange() {
			return false;
		}

	};

}