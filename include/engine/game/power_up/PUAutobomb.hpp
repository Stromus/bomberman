/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_AUTOBOMB_HPP
#define INDIE_STUDIO_AUTOBOMB_HPP

#include "engine/game/power_up/APowerUp.hpp"

namespace engine {
	class AutoBomb : public APowerUp {
	public:
		explicit AutoBomb();
		~AutoBomb() final = default;

		void	capacityActivation(IPlayer *player) final;
	};
}

#endif //INDIE_STUDIO_AUTOBOMB_HPP
