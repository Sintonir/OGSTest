#pragma once
#include "RotateInterface.h"
#include"AlignedReelsBehaviour.h"
namespace Game {
	//„Q„u„p„|„y„x„p„ˆ„y„‘ RotateInterface „‰„u„‚„u„x AlignedReelsBehaviour.
	class AlignedReelsRotateInterface :
		public RotateInterface
	{
		std::shared_ptr<AlignedReelsBehaviour> _reelsBehaviour;
	public:
		AlignedReelsRotateInterface(std::shared_ptr<AlignedReelsBehaviour> reelsBehaviour);
		virtual bool IsRotateActive();
		virtual void Start();
		virtual void Stop();
	};
}

