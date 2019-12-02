/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_INVERTCONTROL_HPP
#define INDIE_STUDIO_INVERTCONTROL_HPP

#include "engine/game/power_up/APowerUp.hpp"

namespace engine {
	class PUInvertControl : public APowerUp {
	public:
		explicit PUInvertControl();
		~PUInvertControl() final = default;

		void	capacityActivation(IPlayer *player) final;
	};
}

#endif //INDIE_STUDIO_INVERTCONTROL_HPP
