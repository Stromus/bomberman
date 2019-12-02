/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "engine/scene/AGuiScene.hpp"

engine::AGuiScene::AGuiScene()
	: _menuDisplay(nullptr)
{}

engine::AGuiScene::~AGuiScene()
{
	if (_menuDisplay != nullptr)
		delete(_menuDisplay);
}

void engine::AGuiScene::desactivateVisibility()
{
	_menuDisplay->hideMenu();
}

void engine::AGuiScene::activateVisibility()
{
	_menuDisplay->displayMenu();
}

void engine::AGuiScene::updateScene(engine::IGuiScene::sceneIndex &index,
	engine::IGuiScene::sceneIndex lastScene, engine::LoadGame &loadGame)
{
	int	event = 0;

	_menuDisplay->updateMenu();
	while (event != -1) {
		std::pair<int, render::eventData> ev = _menuDisplay->getNextEvent();
		event = ev.first;
		analyseEvent(ev, index, lastScene, loadGame);
	}
}

void engine::AGuiScene::addInGraphElem(int idx, const render::MenuElement &element)
{
	_graphElem.insert(std::pair<int, render::MenuElement>(idx, element));
}

void engine::AGuiScene::analyseEvent(std::pair<int, render::eventData> &event,
	engine::IGuiScene::sceneIndex &index,
	engine::IGuiScene::sceneIndex lastScene, engine::LoadGame &loadGame)
{}

void engine::AGuiScene::cleanScene()
{
	_menuDisplay->removeMenu();
}