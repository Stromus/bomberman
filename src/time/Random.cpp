/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <random>
#include "time/Random.hpp"

int Random::getRandomNumber(int min, int max) noexcept
{
	std::random_device	rd;
	std::mt19937		rng(rd());
	std::uniform_int_distribution<int> uni(min, max);

	return uni(rng);
}
