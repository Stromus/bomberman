/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <iostream>
#include <engine/scene/SceneWinnerScreen.hpp>
#include "sound/Music.hpp"
#include "sound/Noise.hpp"
#include "time/FPSControl.hpp"
#include "settings/Language.hpp"
#include "engine/scene/ScenePause.hpp"
#include "engine/scene/SceneMainMenu.hpp"
#include "engine/scene/SceneSettings.hpp"
#include "engine/scene/SceneGameSettings.hpp"
#include "engine/scene/SceneGame.hpp"
#include "engine/scene/SceneCredits.hpp"
#include "engine/scene/SceneLoad.hpp"
#include "engine/scene/ScenePlayerChoice.hpp"
#include "engine/scene/SceneBeginLoadMenu.hpp"
#include "engine/scene/AGuiScene.hpp"
#include "exception/SettingsException.hpp"
#include "exception/SceneException.hpp"
#include "open_target/Directory.hpp"

engine::GuiManager::GuiManager()
	: _index(IGuiScene::SCENE_BEGIN_LOAD_MENU),
	_previous(IGuiScene::SCENE_BEGIN_LOAD_MENU),
	_lastScene(IGuiScene::SCENE_BEGIN_LOAD_MENU)
{
	_sceneList.insert(std::make_pair(IGuiScene::SCENE_BEGIN_LOAD_MENU, std::make_unique<IGuiScene *>(new SceneBeginLoadMenu())));
	_sceneList.insert(std::make_pair(IGuiScene::SCENE_MAIN_MENU, std::make_unique<IGuiScene *>(new SceneMainMenu())));
	_sceneList.insert(std::make_pair(IGuiScene::SCENE_PAUSE, std::make_unique<IGuiScene *>(new ScenePause())));
	_sceneList.insert(std::make_pair(IGuiScene::SCENE_SETTINGS, std::make_unique<IGuiScene *>(new SceneSettings())));
	_sceneList.insert(std::make_pair(IGuiScene::SCENE_CREDITS, std::make_unique<IGuiScene *>(new SceneCredits())));
	_sceneList.insert(std::make_pair(IGuiScene::SCENE_GAME, std::make_unique<IGuiScene *>(new SceneGame())));
	_sceneList.insert(std::make_pair(IGuiScene::SCENE_GAME_SETTINGS, std::make_unique<IGuiScene *>(new SceneGameSettings())));
	_sceneList.insert(std::make_pair(IGuiScene::SCENE_LOAD, std::make_unique<IGuiScene *>(new SceneLoad())));
	_sceneList.insert(std::make_pair(IGuiScene::SCENE_PLAYER_CHOICE, std::make_unique<IGuiScene *>(new ScenePlayerChoice())));
	_sceneList.insert(std::make_pair(IGuiScene::SCENE_WINNER, std::make_unique<IGuiScene *>(new SceneWinnerScreen())));
	(*(_sceneList.find(_index))->second)->activateVisibility();
}

void engine::GuiManager::refreshScene()
{
	for (auto &scene : _sceneList) {
		(*(scene.second))->cleanScene();
	}
	_sceneList.clear();
	_sceneList.insert(std::make_pair(IGuiScene::SCENE_MAIN_MENU, std::make_unique<IGuiScene *>(new SceneMainMenu())));
	_sceneList.insert(std::make_pair(IGuiScene::SCENE_PAUSE, std::make_unique<IGuiScene *>(new ScenePause())));
	_sceneList.insert(std::make_pair(IGuiScene::SCENE_SETTINGS, std::make_unique<IGuiScene *>(new SceneSettings())));
	_sceneList.insert(std::make_pair(IGuiScene::SCENE_CREDITS, std::make_unique<IGuiScene *>(new SceneCredits())));
	_sceneList.insert(std::make_pair(IGuiScene::SCENE_GAME, std::make_unique<IGuiScene *>(new SceneGame())));
	_sceneList.insert(std::make_pair(IGuiScene::SCENE_GAME_SETTINGS, std::make_unique<IGuiScene *>(new SceneGameSettings())));
	_sceneList.insert(std::make_pair(IGuiScene::SCENE_LOAD, std::make_unique<IGuiScene *>(new SceneLoad())));
	_sceneList.insert(std::make_pair(IGuiScene::SCENE_PLAYER_CHOICE, std::make_unique<IGuiScene *>(new ScenePlayerChoice())));
	_sceneList.insert(std::make_pair(IGuiScene::SCENE_WINNER, std::make_unique<IGuiScene *>(new SceneWinnerScreen())));
	(*(_sceneList.find(_index))->second)->activateVisibility();
}

void engine::GuiManager::checkIndexs()
{
	if (_index != _previous) {
		(*(_sceneList.find(_previous))->second)->desactivateVisibility();
		(*(_sceneList.find(_index))->second)->activateVisibility();
		_lastScene = _previous;
	}
	_previous = _index;
}

void engine::GuiManager::startScene()
{
	Language *language = Language::getInstance();

	while (_index != IGuiScene::SCENE_QUIT &&\
	Irrlicht::getInstance()->getDevice()->run()) {
		FPSControl::getInstance()->beginLoop();
		if (language->isLanguageUpdated())
			refreshScene();
		Music::getInstance()->updateVolume();
		Noise::getInstance()->updateVolume();
		Irrlicht::getInstance()->draw();
		checkIndexs();
		(*(_sceneList.find(_index))->second)->updateScene(_index, _lastScene, _loadGame);
		FPSControl::getInstance()->endLoop();
	}
}