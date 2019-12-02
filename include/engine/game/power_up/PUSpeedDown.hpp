/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_SPEEDDOWN_HPP
#define INDIE_STUDIO_SPEEDDOWN_HPP

#include "engine/game/power_up/APowerUp.hpp"

namespace engine {
	class PUSpeedDown : public APowerUp {
	public:
		explicit PUSpeedDown();
		~PUSpeedDown() final = default;

		void	capacityActivation(IPlayer *player) final;
	};
}

#endif //INDIE_STUDIO_SPEEDDOWN_HPP
