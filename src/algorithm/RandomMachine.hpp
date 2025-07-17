#pragma once

#include "ColorTable.hpp"
#include "Learner.hpp"
#include <random>

class RandomMachine : public Learner {
	private:
	std::default_random_engine generator;
	std::uniform_int_distribution<> dist;
	enum Direction {
		Top = 0,
		Right = 1,
		Bottom = 2,
		Left = 3
	};


	public:
	RandomMachine(ColorTable* data);
	Color GetRandomColor(u32 y, u32 x, u32 direction);

};
