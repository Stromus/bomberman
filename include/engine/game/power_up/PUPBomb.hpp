/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_PUPBOMB_HPP
#define INDIE_STUDIO_PUPBOMB_HPP

#include "engine/game/power_up/APowerUp.hpp"

namespace engine {
	class PUPBomb : public APowerUp {
	public:
		explicit PUPBomb();
		~PUPBomb() final = default;

		void	capacityActivation(IPlayer *player) final;
	};
}

#endif //INDIE_STUDIO_PBOMB_HPP
