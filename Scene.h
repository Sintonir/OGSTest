#pragma once
#include "Node.h"
namespace Scene {
	//�N�u ���r�u���u�~ �r �~�u���q�����t�y�}�������y �����t�u�|���~���z �������~�������y �����u�~��, �r���x�}���w�~�� ���r�p���y�� ������������ ���������r���z �~���t��.
	class Scene :public std::enable_shared_from_this<Scene>
	{
	private:
		Node::Ptr _rootNode;
	public:
		Node::Ptr GetRootObject() {
			return _rootNode;
		}
		void SetRootObject(Node::Ptr object) {
			_rootNode = object;
		}
		void Update(float dt) {
			_rootNode->UpdateNode(dt);
		}
		void Draw(std::shared_ptr<sf::RenderTarget> renderer) {
			_rootNode->DrawNode(renderer);
		}
	};

}