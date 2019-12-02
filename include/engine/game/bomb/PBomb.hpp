/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_PBOMB_HPP
#define INDIE_STUDIO_PBOMB_HPP

#include "engine/game/bomb/ABomb.hpp"

namespace engine {
	class PBomb : public ABomb {
	public:
		explicit PBomb(const short &memberShipPlayer);
		~PBomb() final = default;

		engine::IBomb *clone();
	};
}
#endif //INDIE_STUDIO_PBOMB_HPP
