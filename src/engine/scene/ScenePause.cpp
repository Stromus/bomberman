/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <sound/Music.hpp>
#include <time/Timer.hpp>
#include <settings/Scale.hpp>
#include "settings/Language.hpp"
#include "engine/scene/ScenePause.hpp"
#include "open_target/File.hpp"

engine::ScenePause::ScenePause()
{
	this->addInGraphElem(BACKGROUND, render::MenuElementCreator::createImage(0, Scale::scaleRes(0, 0, 1920, 1080),
		L"Default Text", "res/sprite/img/background_game.jpg", false));
	this->addInGraphElem(CONTINUE, render::MenuElementCreator::createButton(0,\
	Scale::scaleRes(805, 350, 1115, 450), Language::getInstance()->getTranslate(Language::CONTINUE)));
	this->addInGraphElem(LOAD, render::MenuElementCreator::createButton(0,\
	Scale::scaleRes(805, 470, 1115, 570), Language::getInstance()->getTranslate(Language::LOADING)));
	this->addInGraphElem(SAVE, render::MenuElementCreator::createButton(0, \
	Scale::scaleRes(805, 590, 1115, 690), Language::getInstance()->getTranslate(Language::SAVE)));
	this->addInGraphElem(SETTINGS, render::MenuElementCreator::createButton(0,\
	Scale::scaleRes(805, 710, 1115, 810), Language::getInstance()->getTranslate(Language::SETTINGS)));
	this->addInGraphElem(QUIT, render::MenuElementCreator::createButton(0,\
	Scale::scaleRes(805, 830, 1115, 930), Language::getInstance()->getTranslate(Language::QUIT_GAME)));

	_menuDisplay = new render::MenuDisplay(_graphElem);
}

void engine::ScenePause::analyseEvent(std::pair<int, render::eventData> &event,
	engine::IGuiScene::sceneIndex &index,
	engine::IGuiScene::sceneIndex lastScene, engine::LoadGame &loadGame)
{
	switch (event.first) {
	case CONTINUE:
		timer::Timer::getInstance()->desactivatePause();
		Irrlicht::getInstance()->getDevice()->getTimer()->start();
		index = IGuiScene::SCENE_GAME;
		break;
	case LOAD:
		loadGame.setMode(engine::LoadGame::loadMode::LOAD);
		index = IGuiScene::SCENE_LOAD;
		break;
	case SAVE:
		loadGame.setMode(engine::LoadGame::loadMode::SAVE);
		index = IGuiScene::SCENE_LOAD;
		break;
	case SETTINGS:
		index = IGuiScene::SCENE_SETTINGS;
		break;
	case QUIT:
		Music::getInstance()->play(Music::MENU, true);
		timer::Timer::getInstance()->deleteAllTicks();
		index = IGuiScene::SCENE_MAIN_MENU;
		loadGame.cleanPlayers();
		Irrlicht::getInstance()->getDevice()->getTimer()->start();
		break;
	default: break;
	}
}
