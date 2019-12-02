/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_GHOST_HPP
#define INDIE_STUDIO_GHOST_HPP

#include "engine/game/power_up/APowerUp.hpp"

namespace engine {
	class PUGhost : public APowerUp {
	public:
		explicit PUGhost();
		~PUGhost() final = default;

		void	capacityActivation(IPlayer *player) final;
	};
}

#endif //INDIE_STUDIO_GHOST_HPP
