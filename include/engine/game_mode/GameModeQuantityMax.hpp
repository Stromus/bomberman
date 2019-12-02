/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_GAMEMODEQUANTITYMAX_HPP
#define INDIE_STUDIO_GAMEMODEQUANTITYMAX_HPP

#include "engine/game_mode/AGameMode.hpp"

namespace engine {
	class GameModeQuantityMax : public AGameMode {
	public:
		explicit GameModeQuantityMax();
		~GameModeQuantityMax() final = default;
	};
}

#endif //INDIE_STUDIO_GAMEMODEQUANTITYMAX_HPP
