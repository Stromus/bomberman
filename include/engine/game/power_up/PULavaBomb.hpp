/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_PULAVABOMB_HPP
#define INDIE_STUDIO_PULAVABOMB_HPP

#include "engine/game/power_up/APowerUp.hpp"

namespace engine {
	class PULavaBomb : public APowerUp {
	public:
		explicit PULavaBomb();
		~PULavaBomb() final = default;

		void	capacityActivation(IPlayer *player) final;
	};
}

#endif //INDIE_STUDIO_LAVABOMB_HPP
