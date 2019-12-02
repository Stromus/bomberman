/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <sound/Music.hpp>
#include "settings/Scale.hpp"
#include "settings/Language.hpp"
#include "engine/scene/SceneMainMenu.hpp"

engine::SceneMainMenu::SceneMainMenu()
{
	this->addInGraphElem(BACKGROUND, render::MenuElementCreator::createImage(0, Scale::scaleRes(0, 0, 1920, 1080),
		L"Default Text", "res/sprite/img/main_menu.png", false));
	this->addInGraphElem(BUTTON_NEW_GAME, render::MenuElementCreator::createButton(0,\
	Scale::scaleRes(805, 350, 1115, 450), Language::getInstance()->getTranslate(Language::NEW_GAME)));
	this->addInGraphElem(BUTTON_LOAD, render::MenuElementCreator::createButton(0,\
	Scale::scaleRes(805, 470, 1115, 570), Language::getInstance()->getTranslate(Language::LOADING)));
	this->addInGraphElem(BUTTON_SETTINGS, render::MenuElementCreator::createButton(0,\
	Scale::scaleRes(805, 590, 1115, 690), Language::getInstance()->getTranslate(Language::SETTINGS)));
	//this->addInGraphElem(BUTTON_CREDITS, render::MenuElementCreator::createButton(0,\
	//Scale::scaleRes(805, 830, 1115, 930), Language::getInstance()->getTranslate(Language::CREDITS)));
	this->addInGraphElem(BUTTON_QUIT, render::MenuElementCreator::createButton(0,\
	Scale::scaleRes(805, 710, 1115, 810), Language::getInstance()->getTranslate(Language::QUIT)));

	_menuDisplay = new render::MenuDisplay(_graphElem);
}

void engine::SceneMainMenu::analyseEvent(std::pair<int, render::eventData> &event,
	engine::IGuiScene::sceneIndex &index,
	engine::IGuiScene::sceneIndex lastScene, engine::LoadGame &loadGame)
{
	(void)lastScene;
	(void)loadGame;
	switch (event.first) {
	case BUTTON_NEW_GAME:
		index = IGuiScene::SCENE_GAME_SETTINGS;
		break;
	case BUTTON_LOAD:
		loadGame.setMode(engine::LoadGame::LOAD);
		index = IGuiScene::SCENE_LOAD;
		break;
	case BUTTON_SETTINGS:
		index = IGuiScene::SCENE_SETTINGS;
		break;
	/*case BUTTON_CREDITS:
		Music::getInstance()->play(Music::CREDITS, true);
		index = IGuiScene::SCENE_CREDITS;
		break;*/
	case BUTTON_QUIT:
		index = IGuiScene::SCENE_QUIT;
		break;
	default: break;
	}
}