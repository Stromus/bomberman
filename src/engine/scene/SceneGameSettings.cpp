/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "settings/Settings.hpp"
#include "engine/game_mode/GameModeSpeedMax.hpp"
#include "engine/game_mode/GameModeQuantityMax.hpp"
#include "engine/game_mode/GameModeFireMax.hpp"
#include "engine/game_mode/GameModeCasper.hpp"
#include "engine/game_mode/GameModeInvert.hpp"
#include "engine/game_mode/GameModeCastle.hpp"
#include "engine/game_mode/GameModeBombPlus.hpp"
#include "engine/game_mode/GameModeAssault.hpp"
#include "engine/game_mode/GameModeStatsPlus.hpp"
#include "engine/game_mode/GameModeDestructible.hpp"
#include "engine/game_mode/GameModeNormal.hpp"
#include "settings/Language.hpp"
#include "engine/scene/SceneGameSettings.hpp"
#include "settings/GameSettings.hpp"
#include "settings/Scale.hpp"

engine::SceneGameSettings::SceneGameSettings()
{
	GameSettings::getInstance()->setDifficulty(1);
	GameSettings::getInstance()->setMapSize({9, 9});
	GameSettings::getInstance()->setGameMode(new GameModeNormal());

	_difficultiesCorrespondance.insert(std::make_pair(L"Easy", 1));
	_difficultiesCorrespondance.insert(std::make_pair(L"Medium", 2));
	_difficultiesCorrespondance.insert(std::make_pair(L"Hard", 3));

	_gamemodeCorrespondance.insert(std::make_pair(L"Normal", new GameModeNormal()));
	_gamemodeCorrespondance.insert(std::make_pair(L"Assault", new GameModeAssault()));
	_gamemodeCorrespondance.insert(std::make_pair(L"Stats+", new GameModeStatsPlus()));
	_gamemodeCorrespondance.insert(std::make_pair(L"Destructible+", new GameModeDestructible()));
	_gamemodeCorrespondance.insert(std::make_pair(L"Fire MAX", new GameModeFireMax()));
	_gamemodeCorrespondance.insert(std::make_pair(L"Speed MAX", new GameModeSpeedMax()));
	_gamemodeCorrespondance.insert(std::make_pair(L"Quantity MAX", new GameModeQuantityMax()));
	_gamemodeCorrespondance.insert(std::make_pair(L"Casper", new GameModeCasper()));
	_gamemodeCorrespondance.insert(std::make_pair(L"trevnI", new GameModeInvert()));
	_gamemodeCorrespondance.insert(std::make_pair(L"Castle", new GameModeCastle()));
	_gamemodeCorrespondance.insert(std::make_pair(L"Military Weapon", new GameModeBombPlus()));

	/* Title */
	this->addInGraphElem(TITLE, render::MenuElementCreator::createText(0, Scale::scaleRes(800, 100, 1250, 300),
		Language::getInstance()->getTranslate(Language::GAME_SETTINGS), false));

	/* draw tab */
	addInGraphElem(TAB, render::MenuElementCreator::createTabControl(0, Scale::scaleRes(50, 50, 1870, 1000)));

	/* Button continue / return */
	this->addInGraphElem(RETURN, render::MenuElementCreator::createButton(0, Scale::scaleRes(225, 880, 475, 950),
		Language::getInstance()->getTranslate(Language::RETURN_MENU)));
	this->addInGraphElem(CONTINUE, render::MenuElementCreator::createButton(0, Scale::scaleRes(1250, 880, 1850, 950),
		Language::getInstance()->getTranslate(Language::PLAYER_CHOICE)));

	/* Back ground */
	this->addInGraphElem(BACKGROUND, render::MenuElementCreator::createImage(0, Scale::scaleRes(0, 0, 1920, 1080),
		L"Default Text", "res/sprite/img/background_game.jpg", false));

	addInGraphElem(MAP_SIZE_Y_BAR, render::MenuElementCreator::createScrollBar(0, Scale::scaleRes(475, 225, 1075, 275), true, {9, 25}, 2));
	addInGraphElem(MAP_SIZE_Y_TEXT, render::MenuElementCreator::createText(0, Scale::scaleRes(150, 220, 450, 300),\
	Language::getInstance()->getTranslate(Language::LINES), false));
	addInGraphElem(MAP_SIZE_Y_VALUE, render::MenuElementCreator::createText(0, Scale::scaleRes(1100, 225, 1250, 300),\
	std::to_wstring(GameSettings::getInstance()->getSizeMap().y), false));

	addInGraphElem(MAP_SIZE_X_BAR, render::MenuElementCreator::createScrollBar(0, Scale::scaleRes(475, 325, 1075, 375), true, {9, 25}, 2));
	addInGraphElem(MAP_SIZE_X_TEXT, render::MenuElementCreator::createText(0, Scale::scaleRes(150, 320, 450, 400),\
	Language::getInstance()->getTranslate(Language::COLUMNS), false));
	addInGraphElem(MAP_SIZE_X_VALUE, render::MenuElementCreator::createText(0, Scale::scaleRes(1100, 325, 1250, 400),\
	std::to_wstring(GameSettings::getInstance()->getSizeMap().x), false));


	/* Difficulties */
	this->addInGraphElem(DIFFICULTY_TEXT, render::MenuElementCreator::createText(0, Scale::scaleRes(150, 480, 500, 580),\
	Language::getInstance()->getTranslate(Language::AI_DIFFICULTY), false));
	std::vector<std::wstring> difficulties = { L"Easy", L"Medium", L"Hard" };
	this->addInGraphElem(DIFFICULTY_LIST, render::MenuElementCreator::createListBox(0,\
	Scale::scaleRes(500, 450, 800, 550), difficulties, true));

	/* Gamemode */
	this->addInGraphElem(GAMEMODE_TEXT, render::MenuElementCreator::createText(0, Scale::scaleRes(150, 705, 500, 805), Language::getInstance()->getTranslate(Language::GAME_MODE), false));
	std::vector<std::wstring> gamemodes = { L"Normal", L"Assault", L"Stats+", L"Destructible+", L"Fire MAX",\
	L"Speed MAX", L"Quantity MAX", L"Casper", L"trevnI", L"Castle", L"Military Weapon"};
	this->addInGraphElem(GAMEMODE_LIST, render::MenuElementCreator::createListBox(0, Scale::scaleRes(500, 675, 800, 775), gamemodes, true));

	_menuDisplay = new render::MenuDisplay(this->_graphElem);
}

void engine::SceneGameSettings::analyseEvent(std::pair<int, render::eventData> &event,
	engine::IGuiScene::sceneIndex &index,
	engine::IGuiScene::sceneIndex lastScene, engine::LoadGame &loadGame)
{
	GameSettings	*settings = GameSettings::getInstance();
	int		value;
	std::wstring	eventString;

	switch (event.first) {
	case GAMEMODE_LIST:
		eventString = event.second.string;
		settings->setGameMode(_gamemodeCorrespondance.at(eventString));
		break;

	case MAP_SIZE_X_BAR:
		value = event.second.position;
		if (value != -1) {
			settings->setMapSize({static_cast<size_t>(value), settings->getSizeMap().y});
			_menuDisplay->setValueText(MAP_SIZE_X_VALUE, std::to_wstring(settings->getSizeMap().x));
		}
		break;

	case MAP_SIZE_Y_BAR:
		value = event.second.position;
		if (value != -1) {
			settings->setMapSize({settings->getSizeMap().x, static_cast<size_t>(value)});
			_menuDisplay->setValueText(MAP_SIZE_Y_VALUE, std::to_wstring(settings->getSizeMap().y));
		}
		break;

	case DIFFICULTY_LIST:
		eventString = event.second.string;
		settings->setDifficulty(this->_difficultiesCorrespondance.at(eventString));
		break;

	case RETURN:
		index = IGuiScene::SCENE_MAIN_MENU;
		break;

	case CONTINUE:
		loadGame.cleanPlayers();
		loadGame.generateMap();
		index = IGuiScene::SCENE_PLAYER_CHOICE;
		break;

	default:
		break;
	}
}
