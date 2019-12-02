/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_GAMEMODEDESTRUCTIBLE_HPP
#define INDIE_STUDIO_GAMEMODEDESTRUCTIBLE_HPP

#include "engine/game_mode/AGameMode.hpp"

namespace engine {
	class GameModeDestructible : public AGameMode {
	public:
		explicit GameModeDestructible();
		~GameModeDestructible() final = default;
	};
}

#endif //INDIE_STUDIO_GAMEMODEDESTRUCTIBLE_HPP
