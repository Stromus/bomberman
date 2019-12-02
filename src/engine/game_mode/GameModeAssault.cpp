/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "engine/game_mode/GameModeAssault.hpp"

engine::GameModeAssault::GameModeAssault()
	: AGameMode()
{
	_noWall = true;
	_stats = {15, 15, 5};
}
