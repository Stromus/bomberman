/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_SCENEWINNERSCREEN_HPP
#define INDIE_STUDIO_SCENEWINNERSCREEN_HPP

#include "engine/scene/AGuiScene.hpp"

namespace engine {
	class SceneWinnerScreen : public AGuiScene {
	public:
		enum scene {
			BACKGROUND_IMG,
			RETURN_MENU_BUTTON,
			TAB_WINNER,
			TEXT_WINNER
		};
		SceneWinnerScreen();
		~SceneWinnerScreen() final = default;

		void	analyseEvent(std::pair<int, render::eventData> &event, sceneIndex &index,\
		sceneIndex lastScene, LoadGame &loadGame) final;
		void	updateScene(engine::IGuiScene::sceneIndex &index,\
		engine::IGuiScene::sceneIndex lastScene, engine::LoadGame &loadGame) final;
		int				_victoryPlayer;
	};
}

#endif //INDIE_STUDIO_SCENEWINNERSCREEN_HPP
