/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "engine/game_mode/AGameMode.hpp"

engine::AGameMode::AGameMode()
	: _allDestructible(false),
	_noWall(false),
	_invertControl(false),
	_betterBomb(false),
	_ghost(false),
	_castle(false),
	_stats({1, 1, 1})
{}

bool engine::AGameMode::isAllDestructible() const noexcept
{
	return _allDestructible;
}

bool engine::AGameMode::isNoWall() const noexcept
{
	return _noWall;
}

bool engine::AGameMode::isCustomStats() const noexcept
{
	return !(_stats.speed == 1 && _stats.bombQuantity == 1 && _stats.fireRange == 1);
}

engine::IPlayer::stats engine::AGameMode::getCustomStats() const noexcept
{
	return _stats;
}

bool engine::AGameMode::isInverted() const noexcept
{
	return _invertControl;
}

bool engine::AGameMode::isBetterBomb() const noexcept
{
	return _betterBomb;
}

bool engine::AGameMode::isGhost() const noexcept
{
	return _ghost;
}

bool engine::AGameMode::isCastle() const noexcept
{
	return _castle;
}
