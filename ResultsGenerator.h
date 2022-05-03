#pragma once
#include <vector>
#include <map>
#include <memory>
#include <random>
namespace GameLogic {
	//„P„‚„€„r„u„‚„‘„u„„ „„p„„„„„u„‚„~ „~„p „~„p„|„y„‰„y„u „r„„y„s„‚„„Š„~„„‡ „{„€„}„q„y„~„p„ˆ„y„z. „S.„{. „{„€„}„q„y„~„p„ˆ„y„y „}„€„s„…„„ „x„p„ƒ„‰„y„„„„r„p„„„„ƒ„‘ „„€-„‚„p„x„~„€„}„… („|„„q„„u „„€„t„‚„‘„t „y„t„…„‹„y„u, „„„€„|„„{„€ „ƒ„|„u„r„p, „ƒ„|„u„r„p „|„y„q„€ „ƒ„„‚„p„r„p...) „ƒ„€„x„t„p„ „y„~„„„u„‚„†„u„z„ƒ.
	class IPatternChecker {
	public:
		using WinPattern = std::vector<std::vector<bool>>;
		virtual std::map<int, size_t> SymbolsNumInPattern(const WinPattern& pattern, const std::vector<std::vector<int>>& matrix) = 0;
		virtual WinPattern PatternForSymbol(int symbol, const WinPattern& pattern, const std::vector<std::vector<int>>& matrix) = 0;
	};
	//„@„q„ƒ„„„‚„p„{„„„~„„z „{„|„p„ƒ„ƒ. „H„p„t„p„v„„ „y„~„„„u„‚„†„u„z„ƒ „t„|„‘ „s„u„~„u„‚„p„ˆ„y„y „ƒ„y„}„r„€„|„p „r„€ „r„‚„p„‹„u„~„y„y „y „}„p„„„‚„y„ˆ„…-„‚„u„x„…„|„„„„p„„, „p „„„p„{ „w„u „„€„t„ƒ„‰„y„„„r„„r„u„„ „„‚„y„x„ „y „r„„y„s„‚„„Š„~„„u „ƒ„y„}„r„€„|„.
	class IResultsGenerator
	{
	public:
		using WinPattern = std::vector<std::vector<bool>>;
	private:
		std::shared_ptr<IPatternChecker> _patternChecker;
		std::vector<std::vector<size_t>> _symbolRewards = { {0,0,4,20}, {0,0,3,15}, {0,0,2,10}, {0,0,1,5} };
		std::vector<WinPattern> _patterns;
	public:
		virtual std::vector<std::vector<int>> GetResultMatrix() = 0;
		virtual int GetRotateSymbol(size_t reel) = 0;
		virtual void GenerateResult() = 0;


		void SetPatternChecker(std::shared_ptr<IPatternChecker> checker);
		virtual void SetSymbolRewards(std::vector<std::vector<size_t>> symbolRewards);

		virtual size_t GetPrize();
		struct WinLine {
			WinPattern _pattern;
			int _symbol = 0;
			size_t _reward = 0;
			size_t _winSymbols = 0;
		};
		WinLine CheckPatternWin(const WinPattern& pattern, const std::vector<std::vector<int>>& matrix);
		virtual std::vector<WinLine> GetWinLines();
		virtual std::vector<WinPattern> GetWinPatterns();
		void AddPattern(const WinPattern& pattern);
	};
	//
	class RandomResultGenerator:public IResultsGenerator {
	public:
	private:
		std::vector<std::vector<int>> _resultMatrix;
		//„X„y„ƒ„|„p „r„r„u„t„u„~„ „„‚„€„ƒ„„„€ „~„p„€„q„…„}.
		std::mt19937 _randomnessForResult = std::mt19937(224827);
		std::mt19937 _randomnessForRotate = std::mt19937(853201);
		std::uniform_int_distribution<int> _symbolsDistr = std::uniform_int_distribution<int>(0, 3);
	public:
		int GetRotateSymbol(size_t reel) override;
		virtual std::vector<std::vector<int>> GetResultMatrix() override;
		void GenerateResult()override;
	};
	//„R„p„}„„z „„‚„€„ƒ„„„€„z „r„p„‚„y„p„~„„ „r„„y„s„‚„„Š„~„€„z „{„€„}„q„y„~„p„ˆ„y„y: „„‚„€„ƒ„„„€ „{„€„|„y„‰„u„ƒ„„„r„€ „ƒ„y„}„r„€„|„€„r.
	class SimplePatternChecker :public IPatternChecker {
		virtual std::map<int, size_t> SymbolsNumInPattern(const WinPattern& pattern, const std::vector<std::vector<int>>& matrix);
		virtual WinPattern PatternForSymbol(int symbol, const WinPattern& pattern, const std::vector<std::vector<int>>& matrix);
	};
}