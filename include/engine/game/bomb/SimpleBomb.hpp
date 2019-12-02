/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_NORMALBOMB_HPP
#define INDIE_STUDIO_NORMALBOMB_HPP

#include "engine/game/bomb/ABomb.hpp"

namespace engine {
	class SimpleBomb : public ABomb {
	public:
		explicit SimpleBomb(const short &memberShipPlayer);
		~SimpleBomb() final = default;

		engine::IBomb *clone() final;
	};
}

#endif //INDIE_STUDIO_NORMALBOMB_HPP
