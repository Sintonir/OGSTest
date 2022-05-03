#pragma once
#include <memory>
#include <string>
namespace Scene {
	class Node;
	//„P„€„x„r„€„|„‘„u„„ „{„€„~„„„‚„€„|„y„‚„€„r„p„„„ „„€„r„u„t„u„~„y„u „€„q„Œ„u„{„„„€„r „r „Š„y„‚„€„{„y„‡ „‚„p„}„{„p„‡.
	class ObjectBehaviour :public std::enable_shared_from_this<ObjectBehaviour>
	{
	private:
		std::shared_ptr<Node> _node;
	public:
		//„B„„x„„r„p„u„„„ƒ„‘ „„‚„y „p„{„„„y„r„p„ˆ„y„y „€„q„Œ„u„{„„„p.
		virtual void OnActivate() {};
		//„B„„x„„r„p„u„„„ƒ„‘ „„‚„y „t„u„p„{„„„y„r„p„ˆ„y„y „€„q„Œ„u„{„„„p
		virtual void OnDeactivate() {};
		//„B„„x„„r„p„u„„„ƒ„‘ „„‚„y „„‚„y„ƒ„€„u„t„y„~„u„~„y„y „{ „€„q„Œ„u„{„„„…
		virtual void Init() {};
		//„B„„x„„r„p„u„„„ƒ„‘ „„‚„y „€„q„~„€„r„|„u„~„y„y „€„q„Œ„u„{„„„p !!!„u„ƒ„|„y „€„~„p „p„{„„„y„r„u„~!!!
		virtual void Update(float dt) {};
		//„B„„x„„r„p„u„„„ƒ„‘ „„‚„y „ƒ„q„‚„€„ƒ„u „€„q„Œ„u„{„„„p.
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