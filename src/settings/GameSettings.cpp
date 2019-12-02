/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "settings/GameSettings.hpp"

GameSettings	GameSettings::singleton;

GameSettings::GameSettings():
	_time(60),
	_difficulty(1),
	_gameMode(nullptr)
{}

GameSettings *GameSettings::getInstance()
{
	return &singleton;
}

int GameSettings::getDifficulty() const noexcept
{
	return _difficulty;
}

engine::IGameMode *GameSettings::getGameMode() const noexcept
{
	return _gameMode;
}

void GameSettings::setDifficulty(const int &difficulty) noexcept
{
	_difficulty = difficulty;
}

Vector2<size_t> GameSettings::getSizeMap() const noexcept
{
	return _mapSize;
}

void GameSettings::setMapSize(const Vector2<size_t> &size) noexcept
{
	_mapSize = size;
}

void	GameSettings::setGameMode(engine::IGameMode *gameMode) noexcept
{
	_gameMode = gameMode;
}