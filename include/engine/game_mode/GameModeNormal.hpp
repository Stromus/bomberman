/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_GAMEMODENORMAL_HPP
#define INDIE_STUDIO_GAMEMODENORMAL_HPP

#include "engine/game_mode/AGameMode.hpp"

namespace engine {
	class GameModeNormal : public AGameMode {
	public:
		explicit GameModeNormal();
		~GameModeNormal() final = default;
	};
}

#endif //INDIE_STUDIO_GAMEMODENORMAL_HPP
