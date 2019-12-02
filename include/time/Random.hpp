/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_RANDOM_HPP
#define INDIE_STUDIO_RANDOM_HPP

class Random {
public:
	Random() = default;
	~Random() = default;

	static int	getRandomNumber(int min, int max) noexcept;
};

#endif //INDIE_STUDIO_RANDOM_HPP
