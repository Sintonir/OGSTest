#pragma once
namespace Game {
	//„I„~„„„u„‚„†„u„z„ƒ „t„|„‘ „r„‚„p„‹„u„~„y„‘, „‰„„„€„q„ „r RotateState „}„€„w„~„€ „q„„|„€ „x„p„t„p„„„ „r„‚„p„‹„u„~„y„u „‚„p„x„~„„}„y „ƒ„„€„ƒ„€„q„p„}„y.
	class RotateInterface
	{
	public:
		virtual bool IsRotateActive() = 0;
		virtual void Start() = 0;
		virtual void Stop() = 0;
	};
}
