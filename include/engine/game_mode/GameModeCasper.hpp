/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_GAMEMODECASPER_HPP
#define INDIE_STUDIO_GAMEMODECASPER_HPP

#include "engine/game_mode/AGameMode.hpp"

namespace engine {
	class GameModeCasper : public AGameMode {
	public:
		explicit GameModeCasper();
		~GameModeCasper() final = default;
	};
}

#endif //INDIE_STUDIO_GAMEMODECASPER_HPP
