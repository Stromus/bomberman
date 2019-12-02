/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_SPEEDUP_HPP
#define INDIE_STUDIO_SPEEDUP_HPP

#include "engine/game/power_up/APowerUp.hpp"

namespace engine {
	class PUSpeedUp : public APowerUp {
	public:
		explicit PUSpeedUp();
		~PUSpeedUp() final = default;

		void	capacityActivation(IPlayer *player) final;
	};
}

#endif //INDIE_STUDIO_SPEEDUP_HPP
