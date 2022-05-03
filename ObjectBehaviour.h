#pragma once
#include <memory>
#include <string>
namespace Scene {
	class Node;
	//�P���x�r���|���u�� �{���~�������|�y�����r�p���� �����r�u�t�u�~�y�u ���q���u�{�����r �r ���y�����{�y�� ���p�}�{�p��.
	class ObjectBehaviour :public std::enable_shared_from_this<ObjectBehaviour>
	{
	private:
		std::shared_ptr<Node> _node;
	public:
		//�B���x���r�p�u������ �����y �p�{���y�r�p���y�y ���q���u�{���p.
		virtual void OnActivate() {};
		//�B���x���r�p�u������ �����y �t�u�p�{���y�r�p���y�y ���q���u�{���p
		virtual void OnDeactivate() {};
		//�B���x���r�p�u������ �����y �����y�����u�t�y�~�u�~�y�y �{ ���q���u�{����
		virtual void Init() {};
		//�B���x���r�p�u������ �����y ���q�~���r�|�u�~�y�y ���q���u�{���p !!!�u���|�y ���~�p �p�{���y�r�u�~!!!
		virtual void Update(float dt) {};
		//�B���x���r�p�u������ �����y ���q�������u ���q���u�{���p.
		virtual void Reset() {};
		using Ptr = std::shared_ptr<ObjectBehaviour>;
		void LinkToNode(std::shared_ptr<Node> node) {
			_node = node;
			Init();
		}
		std::shared_ptr<Node> GetNode() {
			return _node;
		}
		virtual ~ObjectBehaviour() noexcept {}
	};

}