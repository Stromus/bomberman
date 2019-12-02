/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_PUGBOMB_HPP
#define INDIE_STUDIO_PUGBOMB_HPP

#include "engine/game/power_up/APowerUp.hpp"

namespace engine {
	class PUGBomb : public APowerUp {
	public:
		explicit PUGBomb();
		~PUGBomb() final = default;

		void	capacityActivation(IPlayer *player) final;
	};
}

#endif //INDIE_STUDIO_GBOMB_HPP
