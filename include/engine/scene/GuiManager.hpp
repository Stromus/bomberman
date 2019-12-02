/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_GUIMANAGER_HPP
#define INDIE_STUDIO_GUIMANAGER_HPP

#include <map>
#include <memory>
#include "engine/scene/IGuiScene.hpp"

namespace engine {
	class GuiManager {
	public:
		explicit GuiManager();
		~GuiManager() = default;

		void	startScene();

	private:
		void	refreshScene();
		void	checkIndexs();

	private:
		IGuiScene::sceneIndex	_index;
		IGuiScene::sceneIndex	_previous;
		IGuiScene::sceneIndex	_lastScene;
		LoadGame		_loadGame;
		std::map<IGuiScene::sceneIndex, std::unique_ptr<IGuiScene *>>	_sceneList;
	};
}

#endif //INDIE_STUDIO_GUIMANAGER_HPP
