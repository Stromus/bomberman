/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <sound/Music.hpp>
#include <settings/Language.hpp>
#include <settings/Scale.hpp>
#include "engine/scene/SceneWinnerScreen.hpp"

engine::SceneWinnerScreen::SceneWinnerScreen()
{
	_victoryPlayer = -1;
	addInGraphElem(TAB_WINNER, render::MenuElementCreator::createTabControl(0, Scale::scaleRes(700, 400, 1220, 600)));
	addInGraphElem(RETURN_MENU_BUTTON, render::MenuElementCreator::createButton(0,\
	Scale::scaleRes(1495, 930, 1820, 1030), Language::getInstance()->getTranslate(Language::QUIT)));
	addInGraphElem(BACKGROUND_IMG, render::MenuElementCreator::createImage(0, Scale::scaleRes(0, 0, 1920, 1080),
		L"Default Text", "res/sprite/img/winner_background.jpg", false));
	addInGraphElem(TEXT_WINNER, render::MenuElementCreator::createText(0, Scale::scaleRes(775, 475, 1220, 575),\
	L"Example", false));
	_menuDisplay = new render::MenuDisplay(_graphElem);
}

void engine::SceneWinnerScreen::analyseEvent(std::pair<int, render::eventData> &event,
	sceneIndex &index, sceneIndex lastScene, LoadGame &loadGame)
{
	switch (event.first) {
	case RETURN_MENU_BUTTON:
		Music::getInstance()->play(Music::MENU, true);
		index = IGuiScene::SCENE_MAIN_MENU;
		break;
	default: break;
	}
}

void engine::SceneWinnerScreen::updateScene(engine::IGuiScene::sceneIndex &index,
	engine::IGuiScene::sceneIndex lastScene, engine::LoadGame &loadGame)
{
	int	event = 0;

	if (loadGame.getWinner() != _victoryPlayer) {
		if (loadGame.getWinner() == 0)
			_menuDisplay->setValueText(TEXT_WINNER, Language::getInstance()->getTranslate(Language::ALL_DEATH));
		else
			_menuDisplay->setValueText(TEXT_WINNER, Language::getInstance()->getTranslate(Language::PLAYER) +\
			std::to_wstring(loadGame.getWinner()) + Language::getInstance()->getTranslate(Language::VICTORIOUS));
		_victoryPlayer = loadGame.getWinner();
	}
	_menuDisplay->updateMenu();
	while (event != -1) {
		std::pair<int, render::eventData> ev = _menuDisplay->getNextEvent();
		event = ev.first;
		analyseEvent(ev, index, lastScene, loadGame);
	}
}
