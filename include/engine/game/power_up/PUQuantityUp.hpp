/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_QUANTITYUP_HPP
#define INDIE_STUDIO_QUANTITYUP_HPP

#include "engine/game/power_up/APowerUp.hpp"

namespace engine {
	class PUQuantityUp : public APowerUp {
	public:
		explicit PUQuantityUp();
		~PUQuantityUp() final = default;

		void	capacityActivation(IPlayer *player) final;
	};
}

#endif //INDIE_STUDIO_QUANTITYUP_HPP
