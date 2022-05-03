#pragma once
#include"ReelRotateBehaviour.h"
#include"ObjectBehaviour.h"
#include"Node.h"
namespace Game {
	//„R„€„q„y„‚„p„u„„ „~„u„ƒ„{„€„|„„{„€ ReelRotateBehaviour „y „x„p„t„p„v„„ „y„} „€„q„‹„u„u „r„„‚„p„r„~„y„r„p„~„y„u „„‚„y „€„ƒ„„„p„~„€„r„{„u.
	class AlignedReelsBehaviour :public Scene::ObjectBehaviour
	{
		std::vector<std::shared_ptr<ReelRotateBehaviour>> _reelBehaviours;
		float _baseAlign = 400;
		float _bottomLine = 600;
		float _width = 110;
		std::shared_ptr<SymbolProviderBase> _provider;
		float _baseRotateTime = 2;
		float _timeDiff = 0.3f;
	public:
		virtual void OnActivate() {};
		virtual void OnDeactivate() {};
		virtual void Init() {};
		virtual void Update(float dt) {};
		virtual void Reset();
		virtual void OnObjectInitFinished() {};
		using Ptr = std::shared_ptr<AlignedReelsBehaviour>;
		void SetupReels(std::vector<size_t> symbolsByReel);
		void SetBaseAlign(float align);
		void SetWidth(float width);
		void SetProvider(std::shared_ptr<SymbolProviderBase> provider);
		void SetAlignForReel(float align, size_t reel);
		bool IsRotate();
		ReelRotateBehaviour::Ptr GetReelBehaviour(size_t reel);
		size_t GetSymbolId(size_t reel, size_t row);
		Scene::Node::Ptr GetSymbol(size_t reel, size_t row);
		void Stop();
		void Start();
		void SetMatrixFunc(std::function<std::vector < std::vector<int> >()>matrixFunc);
		void SetRotateFunc(std::function<int(size_t)>func);
	};
}

