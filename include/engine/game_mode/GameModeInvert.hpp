/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_GAMEMODEINVERT_HPP
#define INDIE_STUDIO_GAMEMODEINVERT_HPP

#include "engine/game_mode/AGameMode.hpp"

namespace engine {
	class GameModeInvert : public AGameMode {
	public:
		explicit GameModeInvert();
		~GameModeInvert() final = default;
	};
}

#endif //INDIE_STUDIO_GAMEMODEINVERT_HPP
