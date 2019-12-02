/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_GAMEMODESPEEDMAX_HPP
#define INDIE_STUDIO_GAMEMODESPEEDMAX_HPP

#include "engine/game_mode/AGameMode.hpp"

namespace engine {
	class GameModeSpeedMax : public AGameMode {
	public:
		explicit GameModeSpeedMax();
		~GameModeSpeedMax() final = default;
	};
}

#endif //INDIE_STUDIO_GAMEMODESPEEDMAX_HPP
