/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_SHIELD_HPP
#define INDIE_STUDIO_SHIELD_HPP

#include "engine/game/power_up/APowerUp.hpp"

namespace engine {
	class PUShield : public APowerUp {
	public:
		explicit PUShield();
		~PUShield() final = default;

		void	capacityActivation(IPlayer *player) final;
	};
}

#endif //INDIE_STUDIO_SHIELD_HPP
