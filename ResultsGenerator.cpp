#include "ResultsGenerator.h"

void GameLogic::IResultsGenerator::SetPatternChecker(std::shared_ptr<IPatternChecker> checker) {
	_patternChecker = checker;
}

void GameLogic::IResultsGenerator::SetSymbolRewards(std::vector<std::vector<size_t>> rewards)
{
	_symbolRewards = rewards;
}

GameLogic::IResultsGenerator::WinLine GameLogic::IResultsGenerator::CheckPatternWin(const WinPattern& pattern, const std::vector<std::vector<int>>& matrix) {

	WinLine result;
	if (!_patternChecker)
		return result;
	auto symbolNumbers = _patternChecker->SymbolsNumInPattern(pattern, matrix);
	for (size_t i = 0; i < _symbolRewards.size(); i++) {
		if (symbolNumbers.find(i) == symbolNumbers.end()) {
			continue;
		}
		auto rewards = _symbolRewards.at(i);
		auto reward = rewards.at(symbolNumbers.at(i));
		if (reward > result._reward) {
			result._symbol = i;
			result._reward = reward;
			result._winSymbols = symbolNumbers.at(i);
		}
	}
	if (result._reward > 0) {
		result._pattern = _patternChecker->PatternForSymbol(result._symbol, pattern, matrix);
	}
	return result;
}

int GameLogic::RandomResultGenerator::GetRotateSymbol(size_t reel) {
	return _symbolsDistr(_randomnessForRotate);
}

std::vector<std::vector<int>> GameLogic::RandomResultGenerator::GetResultMatrix() {
	return _resultMatrix;
}

void GameLogic::IResultsGenerator::AddPattern(const WinPattern& pattern) {
	_patterns.push_back(pattern);
}

std::vector<GameLogic::IResultsGenerator::WinLine> GameLogic::IResultsGenerator::GetWinLines() {
	std::vector<WinLine> result;
	for (auto pattern : _patterns) {
		auto line = CheckPatternWin(pattern, GetResultMatrix());
		if (line._reward > 0) {
			result.push_back(line);
		}
	}
	return result;
}

size_t GameLogic::IResultsGenerator::GetPrize() {
	auto winLines = GetWinLines();
	size_t prize = 0;
	for (auto line : winLines) {
		prize += line._reward;
	}
	return prize;
}

void GameLogic::RandomResultGenerator::GenerateResult() {
	_resultMatrix.resize(3);
	for (size_t i = 0; i < _resultMatrix.size(); i++) {
		_resultMatrix.at(i).resize(3);
		for (size_t j = 0; j < _resultMatrix.at(i).size(); j++) {
			_resultMatrix.at(i).at(j) = _symbolsDistr(_randomnessForResult);
		}
	}
}

std::vector<GameLogic::IResultsGenerator::WinPattern> GameLogic::IResultsGenerator::GetWinPatterns() {
	std::vector<WinPattern> result;
	auto lines = GetWinLines();
	for (auto line : lines) {
		result.push_back(line._pattern);
	}
	return result;
}

std::map<int, size_t> GameLogic::SimplePatternChecker::SymbolsNumInPattern(const WinPattern& pattern, const std::vector<std::vector<int>>& matrix) {
	std::map<int, size_t> result;
	for (size_t i = 0; i < pattern.size(); i++) {
		for (size_t j = 0; j < pattern.at(i).size(); j++) {
			if (!pattern.at(i).at(j)) {
				continue;
			}
			if (result.find(matrix.at(i).at(j)) == result.end()) {
				result[matrix.at(i).at(j)] = 1;
			}
			else {
				result[matrix.at(i).at(j)] ++;
			}
		}
	}
	return result;
}

GameLogic::IResultsGenerator::WinPattern GameLogic::SimplePatternChecker::PatternForSymbol(int symbol, const WinPattern& pattern, const std::vector<std::vector<int>>& matrix) {
	auto result = pattern;
	for (size_t i = 0; i < result.size(); i++) {
		for (size_t j = 0; j < result.at(i).size(); j++) {
			if (!result.at(i).at(j)) {
				continue;
			}
			else {
				result.at(i).at(j) = matrix.at(i).at(j) == symbol;
			}
		}
	}
	return result;
}
