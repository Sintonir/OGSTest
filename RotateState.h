#pragma once
#include "State.h"
#include "RotateInterface.h"
#include "ResultsGenerator.h"
#include "Node.h"

namespace Game {
    class RotateState :
        public State
    {
		std::shared_ptr<RotateInterface> _rotate;
		Scene::Node::Ptr _stopButtonNode;
		std::shared_ptr<GameLogic::IResultsGenerator> _generator;

	protected:
		void OnStart() override;
		void OnEnd() override;
	public:
		void Update(float dt) override {}
		void SetRotate(std::shared_ptr<RotateInterface> rotate) {
			_rotate = rotate;
		}
		void SetButtonNode(Scene::Node::Ptr node) {
			_stopButtonNode = node;
		}
		bool AwaitsChange() {
			return !_rotate->IsRotateActive();
		}
		void SetResultsGenerator(std::shared_ptr<GameLogic::IResultsGenerator> generator) {
			_generator = generator;
		}
    };

}