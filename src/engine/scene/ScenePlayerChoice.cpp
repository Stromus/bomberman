/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <algorithm>
#include <sound/Music.hpp>
#include "time/Random.hpp"
#include "settings/Scale.hpp"
#include "engine/game/player/AI.hpp"
#include "engine/game/player/Human.hpp"
#include "settings/GameSettings.hpp"
#include "settings/Language.hpp"
#include "render/MenuElement.hpp"
#include "engine/scene/ScenePlayerChoice.hpp"

engine::ScenePlayerChoice::ScenePlayerChoice()
{
	_nbHumanPlayer = 1;
	this->addInGraphElem(BACKGROUND,
		render::MenuElementCreator::createImage(0, Scale::scaleRes(0, 0, 1920, 1080),
			L"Default Text", "res/sprite/img/player_choice_background.jpg", false)
	);
	this->addInGraphElem(RETURN,
		render::MenuElementCreator::createButton(0, Scale::scaleRes(50, 50, 350, 125),
			Language::getInstance()->getTranslate(Language::RETURN_MENU))
	);
	this->addInGraphElem(PICK,
		render::MenuElementCreator::createText(0, Scale::scaleRes(880, 65, 1180, 140),
			Language::getInstance()->getTranslate(Language::PLAYER_CHOICE), false)
	);
	this->addInGraphElem(PLAY,
		render::MenuElementCreator::createButton(0, Scale::scaleRes(1670, 50, 1870, 125),
			Language::getInstance()->getTranslate(Language::PLAY))
	);

	/**/
	addInGraphElem(NB_PLAYER_TEXT, render::MenuElementCreator::createText(0, Scale::scaleRes(50, 170, 350, 210),\
	Language::getInstance()->getTranslate(Language::NB_PLAYERS), false));
	addInGraphElem(NB_PLAYER_BAR, render::MenuElementCreator::createScrollBar(0, Scale::scaleRes(400, 170, 900, 210), true, {0, 2}, 1));
	addInGraphElem(NB_PLAYER_VALUE, render::MenuElementCreator::createText(0, Scale::scaleRes(940, 170, 1200, 210),\
	std::to_wstring(_nbHumanPlayer), false));
	/**/
	this->addInGraphElem(SKIN_BB8_1,
		render::MenuElementCreator::createImage(0, Scale::scaleRes(120, 260, 300, 440),
			L"Default Text", "res/sprite/icon/BB8_basic.png", true)
	);
	this->addInGraphElem(SKIN_BB8_2,
		render::MenuElementCreator::createImage(0, Scale::scaleRes(420, 260, 600, 440),
			L"Default Text", "res/sprite/icon/BB8_blue.png", true)
	);
	this->addInGraphElem(SKIN_BB8_3,
		render::MenuElementCreator::createImage(0, Scale::scaleRes(720, 260, 900, 440),
			L"Default Text", "res/sprite/icon/BB8_green.png", true)
	);
	this->addInGraphElem(SKIN_BB8_4,
		render::MenuElementCreator::createImage(0, Scale::scaleRes(1020, 260, 1200, 440),
			L"Default Text", "res/sprite/icon/BB8_pink.png", true)
	);
	this->addInGraphElem(SKIN_BB8_5,
		render::MenuElementCreator::createImage(0, Scale::scaleRes(1320, 260, 1500, 440),
			L"Default Text", "res/sprite/icon/BB8_purple.png", true)
	);
	this->addInGraphElem(SKIN_BB8_6,
		render::MenuElementCreator::createImage(0, Scale::scaleRes(1620, 260, 1800, 440),
			L"Default Text", "res/sprite/icon/BB8_red.png", true)
	);
	this->addInGraphElem(SKIN_R2D2_1,
		render::MenuElementCreator::createImage(0, Scale::scaleRes(120, 630, 300, 810),
			L"Default Text", "res/sprite/icon/R2D2_basic.png", true)
	);
	this->addInGraphElem(SKIN_R2D2_2,
		render::MenuElementCreator::createImage(0, Scale::scaleRes(420, 630, 600, 810),
			L"Default Text", "res/sprite/icon/R2D2_gold.png", true)
	);
	this->addInGraphElem(SKIN_R2D2_3,
		render::MenuElementCreator::createImage(0, Scale::scaleRes(720, 630, 900, 810),
			L"Default Text", "res/sprite/icon/R2D2_green.png", true)
	);
	this->addInGraphElem(SKIN_R2D2_4,
		render::MenuElementCreator::createImage(0, Scale::scaleRes(1020, 630, 1200, 810),
			L"Default Text", "res/sprite/icon/R2D2_pink.png", true)
	);
	this->addInGraphElem(SKIN_R2D2_5,
		render::MenuElementCreator::createImage(0, Scale::scaleRes(1320, 630, 1500, 810),
			L"Default Text", "res/sprite/icon/R2D2_purple.png", true)
	);
	this->addInGraphElem(SKIN_R2D2_6,
		render::MenuElementCreator::createImage(0, Scale::scaleRes(1620, 630, 1800, 810),
			L"Default Text", "res/sprite/icon/R2D2_red.png", true)
	);
	this->addInGraphElem(BUTTON_BB8_1,
		render::MenuElementCreator::createButton(0, Scale::scaleRes(120, 450, 300, 500),
			Language::getInstance()->getTranslate(Language::CHOOSE))
	);
	this->addInGraphElem(BUTTON_BB8_2,
		render::MenuElementCreator::createButton(0, Scale::scaleRes(420, 450, 600, 500),
			Language::getInstance()->getTranslate(Language::CHOOSE))
	);
	this->addInGraphElem(BUTTON_BB8_3,
		render::MenuElementCreator::createButton(0, Scale::scaleRes(720, 450, 900, 500),
			Language::getInstance()->getTranslate(Language::CHOOSE))
	);
	this->addInGraphElem(BUTTON_BB8_4,
		render::MenuElementCreator::createButton(0, Scale::scaleRes(1020, 450, 1200, 500),
			Language::getInstance()->getTranslate(Language::CHOOSE))
	);
	this->addInGraphElem(BUTTON_BB8_5,
		render::MenuElementCreator::createButton(0, Scale::scaleRes(1320, 450, 1500, 500),
			Language::getInstance()->getTranslate(Language::CHOOSE))
	);
	this->addInGraphElem(BUTTON_BB8_6,
		render::MenuElementCreator::createButton(0, Scale::scaleRes(1620, 450, 1800, 500),
			Language::getInstance()->getTranslate(Language::CHOOSE))
	);
	this->addInGraphElem(BUTTON_R2D2_1,
		render::MenuElementCreator::createButton(0, Scale::scaleRes(120, 820, 300, 870),
			Language::getInstance()->getTranslate(Language::CHOOSE))
	);
	this->addInGraphElem(BUTTON_R2D2_2,
		render::MenuElementCreator::createButton(0, Scale::scaleRes(420, 820, 600, 870),
			Language::getInstance()->getTranslate(Language::CHOOSE))
	);
	this->addInGraphElem(BUTTON_R2D2_3,
		render::MenuElementCreator::createButton(0, Scale::scaleRes(720, 820, 900, 870),
			Language::getInstance()->getTranslate(Language::CHOOSE))
	);
	this->addInGraphElem(BUTTON_R2D2_4,
		render::MenuElementCreator::createButton(0, Scale::scaleRes(1020, 820, 1200, 870),
			Language::getInstance()->getTranslate(Language::CHOOSE))
	);
	this->addInGraphElem(BUTTON_R2D2_5,
		render::MenuElementCreator::createButton(0, Scale::scaleRes(1320, 820, 1500, 870),
			Language::getInstance()->getTranslate(Language::CHOOSE))
	);
	this->addInGraphElem(BUTTON_R2D2_6,
		render::MenuElementCreator::createButton(0, Scale::scaleRes(1620, 820, 1800, 870),
			Language::getInstance()->getTranslate(Language::CHOOSE))
	);
	_menuDisplay = new render::MenuDisplay(_graphElem);
	_menuDisplay->setValueText(NB_PLAYER_VALUE,
		std::to_wstring(_nbHumanPlayer));
	_menuDisplay->setValueScrollBar(NB_PLAYER_BAR, _nbHumanPlayer);
}

void engine::ScenePlayerChoice::playButtonPressed(engine::LoadGame &loadGame)
{
	for (auto &elem : _meshMap) {
		switch (elem.first) {
		case 0:
			if (elem.second.empty())
				elem.second = _meshSkin[static_cast<scene>(Random::getRandomNumber(0, 10) + BUTTON_BB8_1)];
			if (_nbHumanPlayer >= 1)
				loadGame.addPlayer(new Human(IPlayer::playerType::PLAYER1, 0,\
				{static_cast<float>(GameSettings::getInstance()->getSizeMap().x), 1.0f}, elem.second));
			else
				loadGame.addPlayer(new AI(0, {static_cast<float>(GameSettings::getInstance()->getSizeMap().x), 1.0f}, elem.second));
			break;
		case 1:
			if (elem.second.empty())
				elem.second = _meshSkin[static_cast<scene>(Random::getRandomNumber(0, 10) + BUTTON_BB8_1)];
			if (_nbHumanPlayer == 2)
				loadGame.addPlayer(new Human(IPlayer::playerType::PLAYER2, 1, {1.0f, 1.0f}, elem.second));
			else
				loadGame.addPlayer(new AI(1, {1.0f , 1.0f}, elem.second));
			break;
		case 2:
			if (elem.second.empty()) {
				elem.second = _meshSkin[static_cast<scene>(Random::getRandomNumber(0, 10) + BUTTON_BB8_1)];
			}
			loadGame.addPlayer(new AI(2, {1.0f, static_cast<float>(GameSettings::getInstance()->getSizeMap().y)}, elem.second));
			break;
		case 3:
			if (elem.second.empty()) {
				elem.second = _meshSkin[static_cast<scene>(Random::getRandomNumber(0, 10) + BUTTON_BB8_1)];
			}
			loadGame.addPlayer(new AI(3, {static_cast<float>(GameSettings::getInstance()->getSizeMap().x),\
				static_cast<float>(GameSettings::getInstance()->getSizeMap().y)}, elem.second));
			break;
		}
	}
}

void engine::ScenePlayerChoice::fillPlayerMeshMap(std::string &meshName, scene sceneID)
{
	for (auto i = 0; i < 4; i += 1) {
		if (_meshMap[i].empty()) {
			_meshMap[i] = meshName;
			_menuDisplay->remove(sceneID);
			return;
		}
	}
}

void engine::ScenePlayerChoice::analyseEvent(
	std::pair<int, render::eventData> &event,
	engine::IGuiScene::sceneIndex &index,
	engine::IGuiScene::sceneIndex lastScene, engine::LoadGame &loadGame)
{
	int value;

	(void)lastScene;
	switch (event.first) {
	case RETURN:
		_menuDisplay->removeMenu();
		_menuDisplay = new render::MenuDisplay(_graphElem);
		_meshMap[0].clear();
		_meshMap[1].clear();
		_meshMap[2].clear();
		_meshMap[3].clear();
		_nbHumanPlayer = 1;
		_menuDisplay->setValueText(NB_PLAYER_VALUE,
			std::to_wstring(_nbHumanPlayer));
		_menuDisplay->setValueScrollBar(NB_PLAYER_BAR, _nbHumanPlayer);
		index = IGuiScene::SCENE_GAME_SETTINGS;
		break;
	case PLAY:
		playButtonPressed(loadGame);
		_menuDisplay->removeMenu();
		_menuDisplay = new render::MenuDisplay(_graphElem);
		_meshMap[0].clear();
		_meshMap[1].clear();
		_meshMap[2].clear();
		_meshMap[3].clear();
		_nbHumanPlayer = 1;
		Music::getInstance()->play(Music::BATTLE, true);
		_menuDisplay->setValueText(NB_PLAYER_VALUE,
			std::to_wstring(_nbHumanPlayer));
		_menuDisplay->setValueScrollBar(NB_PLAYER_BAR, _nbHumanPlayer);
		index = IGuiScene::SCENE_GAME;
		break;
	case NB_PLAYER_BAR:
		value = event.second.position;
		if (value != -1) {
			_nbHumanPlayer = value;
			_menuDisplay->setValueText(NB_PLAYER_VALUE,
				std::to_wstring(_nbHumanPlayer));
		}
		break;
	case BUTTON_BB8_1:
		fillPlayerMeshMap(_meshSkin[BUTTON_BB8_1], BUTTON_BB8_1);
		break;
	case BUTTON_BB8_2:
		fillPlayerMeshMap(_meshSkin[BUTTON_BB8_2], BUTTON_BB8_2);
		break;
	case BUTTON_BB8_3:
		fillPlayerMeshMap(_meshSkin[BUTTON_BB8_3], BUTTON_BB8_3);
		break;
	case BUTTON_BB8_4:
		fillPlayerMeshMap(_meshSkin[BUTTON_BB8_4], BUTTON_BB8_4);
		break;
	case BUTTON_BB8_5:
		fillPlayerMeshMap(_meshSkin[BUTTON_BB8_5], BUTTON_BB8_5);
		break;
	case BUTTON_BB8_6:
		fillPlayerMeshMap(_meshSkin[BUTTON_BB8_6], BUTTON_BB8_6);
		break;
	case BUTTON_R2D2_1:
		fillPlayerMeshMap(_meshSkin[BUTTON_R2D2_1], BUTTON_R2D2_1);
		break;
	case BUTTON_R2D2_2:
		fillPlayerMeshMap(_meshSkin[BUTTON_R2D2_2], BUTTON_R2D2_2);
		break;
	case BUTTON_R2D2_3:
		fillPlayerMeshMap(_meshSkin[BUTTON_R2D2_3], BUTTON_R2D2_3);
		break;
	case BUTTON_R2D2_4:
		fillPlayerMeshMap(_meshSkin[BUTTON_R2D2_4], BUTTON_R2D2_4);
		break;
	case BUTTON_R2D2_5:
		fillPlayerMeshMap(_meshSkin[BUTTON_R2D2_5], BUTTON_R2D2_5);
		break;
	case BUTTON_R2D2_6:
		fillPlayerMeshMap(_meshSkin[BUTTON_R2D2_6], BUTTON_R2D2_6);
		break;
	default:
		break;
	}
}