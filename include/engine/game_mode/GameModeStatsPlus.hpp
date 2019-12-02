/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_GAMEMODESTATSPLUS_HPP
#define INDIE_STUDIO_GAMEMODESTATSPLUS_HPP

#include "engine/game_mode/AGameMode.hpp"

namespace engine {
	class GameModeStatsPlus : public AGameMode {
	public:
		explicit GameModeStatsPlus();
		~GameModeStatsPlus() final = default;
	};
}

#endif //INDIE_STUDIO_GAMEMODESTATSPLUS_HPP
