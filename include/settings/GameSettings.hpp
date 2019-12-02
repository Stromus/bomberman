/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_GAMESETTINGS_HPP
#define INDIE_STUDIO_GAMESETTINGS_HPP

#include <cstdlib>
#include "template/Vector.hpp"
#include "engine/game_mode/IGameMode.hpp"

class GameSettings {
public:
	GameSettings(const GameSettings &gameSettings) = delete;
	GameSettings(GameSettings &&gameSettings) = delete;
	GameSettings& operator=(const GameSettings &gameSettings) = delete;

public:
	static GameSettings	*getInstance();

	int			getDifficulty() const noexcept;
	Vector2<size_t>		getSizeMap() const noexcept;
	engine::IGameMode	*getGameMode() const noexcept;

	void			setDifficulty(const int &difficulty) noexcept;
	void			setMapSize(const Vector2<size_t> &size) noexcept;
	void			setGameMode(engine::IGameMode *gameMode) noexcept;

private:
	explicit GameSettings();
	static GameSettings	singleton;

private:
	int			_time;
	int			_difficulty;
	Vector2<size_t>		_mapSize;
	engine::IGameMode	*_gameMode;
};

#endif //INDIE_STUDIO_GAMESETTINGS_HPP
