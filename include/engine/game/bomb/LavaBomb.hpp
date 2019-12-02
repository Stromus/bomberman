/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_LAVABOMB_HPP
#define INDIE_STUDIO_LAVABOMB_HPP

#include "engine/game/bomb/ABomb.hpp"

namespace engine {
	class LavaBomb : public ABomb {
	public:
		explicit LavaBomb(const short &memberShipPlayer);
		~LavaBomb() final = default;

		IBomb *clone() final;
	};
}
#endif //INDIE_STUDIO_LAVABOMB_HPP
