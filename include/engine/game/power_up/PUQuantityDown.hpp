/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_QUANTITYDOWN_HPP
#define INDIE_STUDIO_QUANTITYDOWN_HPP

#include "engine/game/power_up/APowerUp.hpp"

namespace engine {
	class PUQuantityDown : public APowerUp {
	public:
		explicit PUQuantityDown();
		~PUQuantityDown() final = default;

		void	capacityActivation(IPlayer *player) final;
	};
}

#endif //INDIE_STUDIO_QUANTITYDOWN_HPP
