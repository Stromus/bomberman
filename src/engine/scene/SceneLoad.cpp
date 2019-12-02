/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "settings/Language.hpp"
#include "engine/scene/SceneLoad.hpp"
#include "open_target/Directory.hpp"
#include "exception/SettingsException.hpp"
#include "settings/Scale.hpp"
#include <algorithm>

engine::SceneLoad::SceneLoad()
{
	/* create background, return button, and title*/
	this->addInGraphElem(BACKGROUND, render::MenuElementCreator::createImage(0, Scale::scaleRes(0, 0, 1920, 1080),
		L"Default Text", "res/sprite/img/background_game.jpg", false));
	this->addInGraphElem(TITLE, render::MenuElementCreator::createText(0, Scale::scaleRes(575, 200, 975, 1000),
		L"LOAD", false));
	this->addInGraphElem(RETURN, render::MenuElementCreator::createButton(0,
		Scale::scaleRes(50, 900, 360, 1000), Language::getInstance()->getTranslate(Language::RETURN_MENU)));
	/* Get all files in .save/game directory */
	std::vector<std::string> files;

	try {
		Directory directory(".save/game");
		files = directory.getFilesOfDir();
	}
	catch (const ise::SettingsException &e) {
		std::cerr << e.what() << std::endl;
	}

	/* Exclude .getkeep file */
	auto firstOccurence = std::find(files.begin(), files.end(), ".gitkeep");
	if (firstOccurence != files.end())
		files.erase(firstOccurence);

	/* Draw save boxes */
	int xBegin = 575;
	int xEnd = 1375;
	int yBegin = 250;
	int yEnd = 350;

	std::string fileName;
	std::wstring wFileName;

	this->_saveNames = { "save1", "save2", "save3", "save4", "save5" };

	for (int i = 0; i != 5; ++i) {
		if (std::find(files.begin(), files.end(), this->_saveNames[i]) == files.end())
			this->_saveNames[i] = "None";
		/* remove file extension */
		fileName = this->_saveNames[i];
		wFileName.assign(fileName.begin(), fileName.end());
		this->addInGraphElem(i + 2, render::MenuElementCreator::createButton(0, Scale::scaleRes(xBegin, yBegin, xEnd, yEnd), wFileName));
		yBegin += 150;
		yEnd += 150;
	}

	/* Display */
	_menuDisplay = new render::MenuDisplay(_graphElem);
}

void engine::SceneLoad::analyseEvent(std::pair<int, render::eventData> &event,
	engine::IGuiScene::sceneIndex &index,
	engine::IGuiScene::sceneIndex lastScene, engine::LoadGame &loadGame)
{
	(void)lastScene;
	(void)loadGame;
	_menuDisplay->setValueText(TITLE, loadGame.getMode() == engine::LoadGame::LOAD ? L"LOAD" : L"SAVE");
	switch (event.first) {
	case SAVE_1:
		if (loadGame.getMode() == engine::LoadGame::LOAD) {
			loadGame.cleanPlayers();
			loadGame.cleanMap();
			Irrlicht::getInstance()->getDevice()->getTimer()->start();
			try {
				loadGame.loadFromSave(this->_saveNames[0]);
				index = IGuiScene::SCENE_GAME;
			}
			catch (const ise::IndieStudioException &e) {
				std::cerr << e.what() << std::endl;
				break; 
			}
		}
		else {
			loadGame.saveGame("save1");
			this->_saveNames[0] = "save1";
			_menuDisplay->setValueText(SAVE_1, L"save1");
		}
		break;
	case SAVE_2:
		if (loadGame.getMode() == engine::LoadGame::LOAD) {
			loadGame.cleanPlayers();
			loadGame.cleanMap();
			Irrlicht::getInstance()->getDevice()->getTimer()->start();
			try {
				loadGame.loadFromSave(this->_saveNames[1]);
				index = IGuiScene::SCENE_GAME;
			}
			catch (const ise::IndieStudioException &e) {
				std::cerr << e.what() << std::endl;
				break;
			}
		}
		else {
			loadGame.saveGame("save2");
			this->_saveNames[1] = "save2";
			_menuDisplay->setValueText(SAVE_2, L"save2");
		}
		break;
	case SAVE_3:
		if (loadGame.getMode() == engine::LoadGame::LOAD) {
			loadGame.cleanPlayers();
			loadGame.cleanMap();
			Irrlicht::getInstance()->getDevice()->getTimer()->start();
			try {
				loadGame.loadFromSave(this->_saveNames[2]);
				index = IGuiScene::SCENE_GAME;
			}
			catch (const ise::IndieStudioException &e) {
				std::cerr << e.what() << std::endl;
				break;
			}
		}
		else {
			loadGame.saveGame("save3");
			this->_saveNames[2] = "save3";
			_menuDisplay->setValueText(SAVE_3, L"save3");
		}
		break;
	case SAVE_4:
		if (loadGame.getMode() == engine::LoadGame::LOAD) {
			loadGame.cleanPlayers();
			loadGame.cleanMap();
			Irrlicht::getInstance()->getDevice()->getTimer()->start();
			try {
				loadGame.loadFromSave(this->_saveNames[3]);
				index = IGuiScene::SCENE_GAME;
			}
			catch (const ise::IndieStudioException &e) {
				std::cerr << e.what() << std::endl;
				break;
			}
		}
		else {
			loadGame.saveGame("save4");
			this->_saveNames[3] = "save4";
			_menuDisplay->setValueText(SAVE_4, L"save4");
		}
		break;
	case SAVE_5:
		if (loadGame.getMode() == engine::LoadGame::LOAD) {
			loadGame.cleanPlayers();
			loadGame.cleanMap();
			Irrlicht::getInstance()->getDevice()->getTimer()->start();
			try {
				loadGame.loadFromSave(this->_saveNames[4]);
				index = IGuiScene::SCENE_GAME;
			}
			catch (const ise::IndieStudioException &e) {
				std::cerr << e.what() << std::endl;
				break;
			}
		}
		else {
			loadGame.saveGame("save5");
			this->_saveNames[4] = "save5";
			_menuDisplay->setValueText(SAVE_5, L"save5");
		}
		break;
	case RETURN:
		index = lastScene;
		break;
	default: break;
	}
}
