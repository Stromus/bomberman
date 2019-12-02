/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_GBOMB_HPP
#define INDIE_STUDIO_GBOMB_HPP

#include "engine/game/bomb/ABomb.hpp"

namespace engine {
	class GBomb : public ABomb {
	public:
		explicit GBomb(const short &memberShipPlayer);
		~GBomb() final = default;

		IBomb *clone() final;
	};
}

#endif //INDIE_STUDIO_GBOMB_HPP
