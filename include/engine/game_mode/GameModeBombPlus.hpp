/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_GAMEMODEBOMBPLUS_HPP
#define INDIE_STUDIO_GAMEMODEBOMBPLUS_HPP

#include "engine/game_mode/AGameMode.hpp"

namespace engine {
	class GameModeBombPlus : public AGameMode {
	public:
		explicit GameModeBombPlus();
		~GameModeBombPlus() final = default;
	};
}

#endif //INDIE_STUDIO_GAMEMODEBOMBPLUS_HPP
