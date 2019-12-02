/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#ifndef INDIE_STUDIO_AGUISCENE_HPP
#define INDIE_STUDIO_AGUISCENE_HPP

#include <string>
#include "render/MenuElement.hpp"
#include "engine/scene/IGuiScene.hpp"
#include "engine/scene/GuiManager.hpp"
#include "render/MenuElementCreator.hpp"

namespace engine {
	class AGuiScene : public IGuiScene {
	public:
		explicit AGuiScene();
		~AGuiScene() override;

		void	desactivateVisibility() override;
		void	activateVisibility() override;
		void	analyseEvent(std::pair<int, render::eventData> &event, sceneIndex &index,\
		sceneIndex lastScene, LoadGame &loadGame) override;
		void	updateScene(sceneIndex &index, sceneIndex lastScene, LoadGame &loadGame) override;
		void	addInGraphElem(int idx, const render::MenuElement &element);
		void	cleanScene() override;

	protected:
	render::MenuDisplay			*_menuDisplay;
	std::map<int, render::MenuElement>	_graphElem;
	};
}

#endif //INDIE_STUDIO_AGUISCENE_HPP
