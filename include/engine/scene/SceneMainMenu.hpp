/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_MAINMENU_HPP
#define INDIE_STUDIO_MAINMENU_HPP

#include "engine/scene/AGuiScene.hpp"

namespace engine {
	class SceneMainMenu : public AGuiScene {
	public:
		enum scene {
			BACKGROUND = 0,
			BUTTON_NEW_GAME,
			BUTTON_LOAD,
			BUTTON_SETTINGS,
			BUTTON_CREDITS,
			BUTTON_QUIT
		};
		SceneMainMenu();
		~SceneMainMenu() final = default;

		void	analyseEvent(std::pair<int, render::eventData> &event, sceneIndex &index,\
		sceneIndex lastScene, LoadGame &loadGame) final;
	};
}
#endif //INDIE_STUDIO_MAINMENU_HPP
