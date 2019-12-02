/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_GAMEMODECASTLE_HPP
#define INDIE_STUDIO_GAMEMODECASTLE_HPP

#include "engine/game_mode/AGameMode.hpp"

namespace engine {
	class GameModeCastle : public AGameMode {
	public:
		explicit GameModeCastle();
		~GameModeCastle() final = default;
	};
}

#endif //INDIE_STUDIO_GAMEMODECASTLE_HPP
