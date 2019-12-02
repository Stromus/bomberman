/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_POWERDOWN_HPP
#define INDIE_STUDIO_POWERDOWN_HPP

#include "engine/game/power_up/APowerUp.hpp"

namespace engine {
	class PUFireDown : public APowerUp {
	public:
		explicit PUFireDown();
		~PUFireDown() final = default;

		void	capacityActivation(IPlayer *player) final;
	};
}

#endif //INDIE_STUDIO_POWERDOWN_HPP
