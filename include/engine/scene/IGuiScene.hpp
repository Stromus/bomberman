/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_IGUISCENE_HPP
#define INDIE_STUDIO_IGUISCENE_HPP

namespace engine {
	class LoadGame;
};

#include "engine/load/LoadGame.hpp"
#include "render/MenuElement.hpp"

namespace engine {
	class IGuiScene {
	public:
		enum sceneIndex {
			SCENE_BEGIN_LOAD_MENU,
			SCENE_MAIN_MENU,
			SCENE_PAUSE,
			SCENE_SETTINGS,
			SCENE_CREDITS,
			SCENE_LOAD,
			SCENE_GAME_SETTINGS,
			SCENE_PLAYER_CHOICE,
			SCENE_GAME,
			SCENE_QUIT,
			SCENE_WINNER
		};

		virtual ~IGuiScene() = default;

		virtual void	desactivateVisibility() = 0;
		virtual void	activateVisibility() = 0;
		virtual void	updateScene(sceneIndex &index, sceneIndex lastScene, LoadGame &loadGame) = 0;
		virtual void	analyseEvent(std::pair<int, render::eventData> &event, sceneIndex &index,\
		sceneIndex lastScene, LoadGame &loadGame) = 0;
		virtual void	cleanScene() = 0;
	};
}

#endif //INDIE_STUDIO_IGUISCENE_HPP
