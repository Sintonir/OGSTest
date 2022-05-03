#pragma once
#include <vector>
#include <map>
#include <memory>
#include <random>
namespace GameLogic {
	//�P�����r�u�����u�� ���p�����u���~ �~�p �~�p�|�y���y�u �r���y�s�������~���� �{���}�q�y�~�p���y�z. �S.�{. �{���}�q�y�~�p���y�y �}���s���� �x�p�����y�����r�p�������� ����-���p�x�~���}�� (�|���q���u �����t�����t �y�t�����y�u, �����|���{�� ���|�u�r�p, ���|�u�r�p �|�y�q�� �������p�r�p...) �����x�t�p�� �y�~���u�����u�z��.
	class IPatternChecker {
	public:
		using WinPattern = std::vector<std::vector<bool>>;
		virtual std::map<int, size_t> SymbolsNumInPattern(const WinPattern& pattern, const std::vector<std::vector<int>>& matrix) = 0;
		virtual WinPattern PatternForSymbol(int symbol, const WinPattern& pattern, const std::vector<std::vector<int>>& matrix) = 0;
	};
	//�@�q�������p�{���~���z �{�|�p����. �H�p�t�p�v�� �y�~���u�����u�z�� �t�|�� �s�u�~�u���p���y�y ���y�}�r���|�p �r�� �r���p���u�~�y�y �y �}�p�����y����-���u�x���|�����p��, �p ���p�{ �w�u �����t�����y���r���r�u�� �����y�x�� �y �r���y�s�������~���u ���y�}�r���|��.
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
		//�X�y���|�p �r�r�u�t�u�~�� ������������ �~�p���q���}.
		std::mt19937 _randomnessForResult = std::mt19937(224827);
		std::mt19937 _randomnessForRotate = std::mt19937(853201);
		std::uniform_int_distribution<int> _symbolsDistr = std::uniform_int_distribution<int>(0, 3);
	public:
		int GetRotateSymbol(size_t reel) override;
		virtual std::vector<std::vector<int>> GetResultMatrix() override;
		void GenerateResult()override;
	};
	//�R�p�}���z �������������z �r�p���y�p�~�� �r���y�s�������~���z �{���}�q�y�~�p���y�y: ������������ �{���|�y���u�����r�� ���y�}�r���|���r.
	class SimplePatternChecker :public IPatternChecker {
		virtual std::map<int, size_t> SymbolsNumInPattern(const WinPattern& pattern, const std::vector<std::vector<int>>& matrix);
		virtual WinPattern PatternForSymbol(int symbol, const WinPattern& pattern, const std::vector<std::vector<int>>& matrix);
	};
}