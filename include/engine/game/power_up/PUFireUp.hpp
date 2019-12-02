/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_FIREUP_HPP
#define INDIE_STUDIO_FIREUP_HPP

#include "engine/game/power_up/APowerUp.hpp"

namespace engine {
	class PUFireUp : public APowerUp {
	public:
		explicit PUFireUp();
		~PUFireUp() final = default;

		void	capacityActivation(IPlayer *player) final;
	};
}
#endif //INDIE_STUDIO_FIREUP_HPP
