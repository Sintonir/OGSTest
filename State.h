#pragma once
#include <memory>
namespace Game {
	//„@„q„ƒ„„„‚„p„{„„„~„„z „q„p„x„€„r„„z „{„|„p„ƒ„ƒ „ƒ„€„ƒ„„„€„‘„~„y„‘. 
	class State :public std::enable_shared_from_this<State>
	{
	public:
		using Ptr = std::shared_ptr<State>;
	protected:
		virtual void OnStart() = 0;
		virtual void OnEnd() = 0;
	public:
		void Deactivate();
		void Activate();
		virtual void Update(float dt) = 0;
		//„R„€„ƒ„„„€„‘„~„y„u „}„€„w„u„„ „}„u„~„‘„„„„ƒ„‘ „„€ „r„r„€„t„… „y„|„y „p„r„„„€„}„p„„„y„‰„u„ƒ„{„y „„‚„y „{„p„{„y„‡-„„„€ „…„ƒ„|„€„r„y„‘„‡. „O„q„u „ƒ„y„„„…„p„ˆ„y„y „€„q„‚„p„q„p„„„„r„p„„„„ƒ„‘ „r „}„p„Š„y„~„u „ƒ„€„ƒ„„„€„‘„~„y„z, „~„€ „t„|„‘ „r„„„€„‚„€„z „u„z „~„u„€„q„‡„€„t„y„}„€ „x„~„p„„„ - „r„„„€„|„~„u„~„€ „|„y „…„ƒ„|„€„r„y„u „ƒ„}„u„~„ „ƒ„€„ƒ„„„€„‘„~„y„‘.
		virtual bool AwaitsChange() = 0;
	};

}