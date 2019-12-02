/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_GAMEMODEASSAULT_HPP
#define INDIE_STUDIO_GAMEMODEASSAULT_HPP

#include "engine/game_mode/AGameMode.hpp"

namespace engine {
	class GameModeAssault : public AGameMode {
	public:
		explicit GameModeAssault();
		~GameModeAssault() final = default;
	};
}

#endif //INDIE_STUDIO_GAMEMODEASSAULT_HPP
