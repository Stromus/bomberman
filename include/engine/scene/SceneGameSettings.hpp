/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_SCENEGAMESETTINGS_HPP
#define INDIE_STUDIO_SCENEGAMESETTINGS_HPP

#include "engine/game_mode/IGameMode.hpp"
#include "engine/scene/AGuiScene.hpp"

namespace engine {
	class SceneGameSettings : public AGuiScene {
	public:
		SceneGameSettings();
		~SceneGameSettings() final = default;

		void	analyseEvent(std::pair<int, render::eventData> &event, sceneIndex &index,\
		sceneIndex lastScene, LoadGame &loadGame) final;
	private:
		std::map<std::wstring, int> _difficultiesCorrespondance;
		std::map<std::wstring, IGameMode *> _gamemodeCorrespondance;

		enum element {
			BACKGROUND = 0,
			TAB,
			TITLE,
			MAP_SIZE_Y_TEXT,
			MAP_SIZE_Y_BAR,
			MAP_SIZE_Y_VALUE,
			MAP_SIZE_X_TEXT,
			MAP_SIZE_X_BAR,
			MAP_SIZE_X_VALUE,
			DIFFICULTY_TEXT,
			DIFFICULTY_LIST,
			GAMEMODE_TEXT,
			GAMEMODE_LIST,
			CONTINUE,
			RETURN
		};
	};
}
#endif //INDIE_STUDIO_SCENEGAMESETTINGS_HPP
