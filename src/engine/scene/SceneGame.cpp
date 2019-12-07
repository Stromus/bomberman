/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <time/Random.hpp>
#include <sound/Music.hpp>
#include "engine/game/player/APlayer.hpp"
#include "engine/scene/SceneGame.hpp"
#include "settings/GameSettings.hpp"
#include "settings/Scale.hpp"
#include "settings/Language.hpp"
#include "exception/SettingsException.hpp"
#include "time/Timer.hpp"

void engine::SceneGame::desactivateVisibility()
{
	Irrlicht::getInstance()->setDrawScene3D(false);
	_menuDisplay->hideMenu();
}

void engine::SceneGame::activateVisibility()
{
	auto mapSize = GameSettings::getInstance()->getSizeMap();
	mapSize.x += 2;
	mapSize.y += 2;
	Irrlicht::getInstance()->getSceneManager()->addCameraSceneNode(nullptr, irr::core::vector3df(mapSize.x / 2, std::max(mapSize.x, mapSize.y) * 0.8, mapSize.y * 0.7), irr::core::vector3df(mapSize.x / 2, -3, mapSize.y / 2));
	Irrlicht::getInstance()->getSceneManager()->getActiveCamera()->bindTargetAndRotation(true);
	Irrlicht::getInstance()->setDrawScene3D(true);
	timer::Timer::getInstance()->desactivatePause();
	_menuDisplay->displayMenu();
}

engine::SceneGame::SceneGame()
	: _p1_dead(false),
	  _p2_dead(false),
	  _p3_dead(false),
	  _p4_dead(false)
{
	// init GUI
	addInGraphElem(P1_TYPE, render::MenuElementCreator::createText(0, Scale::scaleRes(50, 50, 400, 100), L"Type :", false, {255, 255, 255, 255}));
	addInGraphElem(P1_BOMB_QUANTITY, render::MenuElementCreator::createText(0, Scale::scaleRes(50, 100, 400, 150), L"Bomb Quantity :", false, {255, 255, 255, 255}));
	addInGraphElem(P1_FIRE_RANGE, render::MenuElementCreator::createText(0, Scale::scaleRes(50, 150, 400, 200), L"Fire Range :", false, {255, 255, 255, 255}));
	addInGraphElem(P1_SPEED, render::MenuElementCreator::createText(0, Scale::scaleRes(50, 200, 400, 250), L"Speed :", false, {255, 255, 255, 255}));
	addInGraphElem(P1_NB_LIFE, render::MenuElementCreator::createText(0, Scale::scaleRes(50, 250, 400, 300), L"NB Life :", false, {255, 255, 255, 255}));
	addInGraphElem(P1_TEAM, render::MenuElementCreator::createText(0, Scale::scaleRes(50, 300, 400, 350), L"Team :", false, {255, 255, 255, 255}));
	addInGraphElem(P1_CAPACITY, render::MenuElementCreator::createText(0, Scale::scaleRes(50, 350, 400, 400), L"Capacity :", false, {255, 255, 255, 255}));
	addInGraphElem(P1_BOMB, render::MenuElementCreator::createText(0, Scale::scaleRes(50, 400, 400, 450), L"Bomb :", false, {255, 255, 255, 255}));

	addInGraphElem(P2_TYPE, render::MenuElementCreator::createText(0, Scale::scaleRes(1520, 50, 1870, 100), L"Type :", false, {255, 255, 255, 255}));
	addInGraphElem(P2_BOMB_QUANTITY, render::MenuElementCreator::createText(0, Scale::scaleRes(1520, 100, 1870, 150), L"Bomb Quantity :", false, {255, 255, 255, 255}));
	addInGraphElem(P2_FIRE_RANGE, render::MenuElementCreator::createText(0, Scale::scaleRes(1520, 150, 1870, 200), L"Fire Range :", false, {255, 255, 255, 255}));
	addInGraphElem(P2_SPEED, render::MenuElementCreator::createText(0, Scale::scaleRes(1520, 200, 1870, 260), L"Speed :", false, {255, 255, 255, 255}));
	addInGraphElem(P2_NB_LIFE, render::MenuElementCreator::createText(0, Scale::scaleRes(1520, 250, 1870, 300), L"NB Life :", false, {255, 255, 255, 255}));
	addInGraphElem(P2_TEAM, render::MenuElementCreator::createText(0, Scale::scaleRes(1520, 300, 1870, 350), L"Team :", false, {255, 255, 255, 255}));
	addInGraphElem(P2_CAPACITY, render::MenuElementCreator::createText(0, Scale::scaleRes(1520, 350, 1870, 400), L"Capacity :", false, {255, 255, 255, 255}));
	addInGraphElem(P2_BOMB, render::MenuElementCreator::createText(0, Scale::scaleRes(1520, 400, 1870, 450), L"Bomb :", false, {255, 255, 255, 255}));

	addInGraphElem(P3_TYPE, render::MenuElementCreator::createText(0, Scale::scaleRes(1520, 630, 1870, 680), L"Type :", false, {255, 255, 255, 255}));
	addInGraphElem(P3_BOMB_QUANTITY, render::MenuElementCreator::createText(0, Scale::scaleRes(1520, 680, 1870, 730), L"Bomb Quantity :", false, {255, 255, 255, 255}));
	addInGraphElem(P3_FIRE_RANGE, render::MenuElementCreator::createText(0, Scale::scaleRes(1520, 730, 1870, 780), L"Fire Range :", false, {255, 255, 255, 255}));
	addInGraphElem(P3_SPEED, render::MenuElementCreator::createText(0, Scale::scaleRes(1520, 780, 1870, 830), L"Speed :", false, {255, 255, 255, 255}));
	addInGraphElem(P3_NB_LIFE, render::MenuElementCreator::createText(0, Scale::scaleRes(1520, 830, 1870, 880), L"NB Life :", false, {255, 255, 255, 255}));
	addInGraphElem(P3_TEAM, render::MenuElementCreator::createText(0, Scale::scaleRes(1520, 880, 1870, 930), L"Team :", false, {255, 255, 255, 255}));
	addInGraphElem(P3_CAPACITY, render::MenuElementCreator::createText(0, Scale::scaleRes(1520, 930, 1870, 980), L"Capacity :", false, {255, 255, 255, 255}));
	addInGraphElem(P3_BOMB, render::MenuElementCreator::createText(0, Scale::scaleRes(1520, 980, 1870, 1030), L"Bomb :", false, {255, 255, 255, 255}));

	addInGraphElem(P4_TYPE, render::MenuElementCreator::createText(0, Scale::scaleRes(50, 630, 400, 680), L"Type :", false, {255, 255, 255, 255}));
	addInGraphElem(P4_BOMB_QUANTITY, render::MenuElementCreator::createText(0, Scale::scaleRes(50, 680, 400, 730), L"Bomb Quantity :", false, {255, 255, 255, 255}));
	addInGraphElem(P4_FIRE_RANGE, render::MenuElementCreator::createText(0, Scale::scaleRes(50, 730, 400, 780), L"Fire Range :", false, {255, 255, 255, 255}));
	addInGraphElem(P4_SPEED, render::MenuElementCreator::createText(0, Scale::scaleRes(50, 780, 400, 830), L"Speed :", false, {255, 255, 255, 255}));
	addInGraphElem(P4_NB_LIFE, render::MenuElementCreator::createText(0, Scale::scaleRes(50, 830, 400, 880), L"NB Life :", false, {255, 255, 255, 255}));
	addInGraphElem(P4_TEAM, render::MenuElementCreator::createText(0, Scale::scaleRes(50, 880, 400, 930), L"Team :", false, {255, 255, 255, 255}));
	addInGraphElem(P4_CAPACITY, render::MenuElementCreator::createText(0, Scale::scaleRes(50, 930, 400, 980), L"Capacity :", false, {255, 255, 255, 255}));
	addInGraphElem(P4_BOMB, render::MenuElementCreator::createText(0, Scale::scaleRes(50, 980, 400, 1030), L"Bomb :", false, {255, 255, 255, 255}));
	
	// init 3D scene
	auto smgr = Irrlicht::getInstance()->getSceneManager();
	auto driver = Irrlicht::getInstance()->getVideo();
	irr::scene::ITerrainSceneNode *terrain = smgr->addTerrainSceneNode(
		"res/sprite/img/terrain-heightmap.bmp",
		0,										   // parent node
		-1,										   // node id
		irr::core::vector3df(-50.f, -10.f, -50.f), // position
		irr::core::vector3df(0.f, 0.f, 0.f),	   // rotation
		irr::core::vector3df(0.5f, 0.02f, 0.5f),   // scale
		irr::video::SColor(255, 255, 255, 255),	// vertexColor
		5,										   // maxLOD
		irr::scene::ETPS_17,					   // patchSize
		4										   // smoothFactor
	);
	if (!terrain)
		throw ise::IndieStudioException(ise::WARNING, "Cannot load game scene background");
	terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	terrain->setMaterialTexture(0, driver->getTexture("res/sprite/img/terrain-texture.jpg"));
	terrain->setMaterialTexture(1, driver->getTexture("res/sprite/img/detailmap3.jpg"));
	terrain->setMaterialType(irr::video::EMT_DETAIL_MAP);
	terrain->scaleTexture(1.0f, 20.0f);

	_menuDisplay = new render::MenuDisplay(_graphElem);
}

void engine::SceneGame::analyseEvent(std::pair<int, render::eventData> &event,
									 engine::IGuiScene::sceneIndex &index,
									 engine::IGuiScene::sceneIndex lastScene, engine::LoadGame &loadGame)
{
	loadGame.updateGame(Controls::getInstance()->getNextKey());
	if (Controls::getInstance()->getNextKey() == Controls::KEY_ESC)
	{
		index = engine::IGuiScene::SCENE_PAUSE;
		timer::Timer::getInstance()->activatePause();
		Irrlicht::getInstance()->getDevice()->getTimer()->stop();
	}
	if (!Controls::getInstance()->isEmpty())
		Controls::getInstance()->eraseNextKey();
}

void engine::SceneGame::updateScene(engine::IGuiScene::sceneIndex &index,
									engine::IGuiScene::sceneIndex lastScene, engine::LoadGame &loadGame)
{
	auto tmp = std::pair<int, render::eventData>();
	analyseEvent(tmp, index, lastScene, loadGame);

	auto *p1 = loadGame.getPlayerByID(0);
	if (p1 != nullptr)
	{
		this->_menuDisplay->setValueText(P1_TYPE, L"Type : " + p1->getTypeName());
		this->_menuDisplay->setValueText(P1_BOMB_QUANTITY, L"Bomb Quantity : " + std::to_wstring(p1->getBombQuantity()));
		this->_menuDisplay->setValueText(P1_FIRE_RANGE, L"Fire Range : " + std::to_wstring(p1->getFireRange()));
		this->_menuDisplay->setValueText(P1_SPEED, L"Speed : " + std::to_wstring(p1->getSpeed()));
		this->_menuDisplay->setValueText(P1_NB_LIFE, L"NB Life : " + std::to_wstring(p1->getNbLife()));
		this->_menuDisplay->setValueText(P1_TEAM, L"Team : " + p1->getTeamName());
		this->_menuDisplay->setValueText(P1_CAPACITY, L"Capacity : " + p1->getCapacityName());
		this->_menuDisplay->setValueText(P1_BOMB, L"Bomb : " + p1->getBomb()->getTypeName());
	}
	else if (!_p1_dead)
	{
		this->_menuDisplay->remove(P1_TYPE);
		this->_menuDisplay->remove(P1_BOMB_QUANTITY);
		this->_menuDisplay->remove(P1_FIRE_RANGE);
		this->_menuDisplay->remove(P1_SPEED);
		this->_menuDisplay->remove(P1_NB_LIFE);
		this->_menuDisplay->remove(P1_TEAM);
		this->_menuDisplay->remove(P1_CAPACITY);
		this->_menuDisplay->remove(P1_BOMB);
		_p1_dead = true;
	}

	auto *p2 = loadGame.getPlayerByID(1);
	if (p2 != nullptr)
	{
		this->_menuDisplay->setValueText(P2_TYPE, L"Type : " + p2->getTypeName());
		this->_menuDisplay->setValueText(P2_BOMB_QUANTITY, L"Bomb Quantity : " + std::to_wstring(p2->getBombQuantity()));
		this->_menuDisplay->setValueText(P2_FIRE_RANGE, L"Fire Range : " + std::to_wstring(p2->getFireRange()));
		this->_menuDisplay->setValueText(P2_SPEED, L"Speed : " + std::to_wstring(p2->getSpeed()));
		this->_menuDisplay->setValueText(P2_NB_LIFE, L"NB Life : " + std::to_wstring(p2->getNbLife()));
		this->_menuDisplay->setValueText(P2_TEAM, L"Team : " + p2->getTeamName());
		this->_menuDisplay->setValueText(P2_CAPACITY, L"Capacity : " + p2->getCapacityName());
		this->_menuDisplay->setValueText(P2_BOMB, L"Bomb : " + p2->getBomb()->getTypeName());
	}
	else if (!_p2_dead)
	{
		this->_menuDisplay->remove(P2_TYPE);
		this->_menuDisplay->remove(P2_BOMB_QUANTITY);
		this->_menuDisplay->remove(P2_FIRE_RANGE);
		this->_menuDisplay->remove(P2_SPEED);
		this->_menuDisplay->remove(P2_NB_LIFE);
		this->_menuDisplay->remove(P2_TEAM);
		this->_menuDisplay->remove(P2_CAPACITY);
		this->_menuDisplay->remove(P2_BOMB);
		_p2_dead = true;
	}

	auto *p3 = loadGame.getPlayerByID(2);
	if (p3 != nullptr)
	{
		this->_menuDisplay->setValueText(P3_TYPE, L"Type : " + p3->getTypeName());
		this->_menuDisplay->setValueText(P3_BOMB_QUANTITY, L"Bomb Quantity : " + std::to_wstring(p3->getBombQuantity()));
		this->_menuDisplay->setValueText(P3_FIRE_RANGE, L"Fire Range : " + std::to_wstring(p3->getFireRange()));
		this->_menuDisplay->setValueText(P3_SPEED, L"Speed : " + std::to_wstring(p3->getSpeed()));
		this->_menuDisplay->setValueText(P3_NB_LIFE, L"NB Life : " + std::to_wstring(p3->getNbLife()));
		this->_menuDisplay->setValueText(P3_TEAM, L"Team : " + p3->getTeamName());
		this->_menuDisplay->setValueText(P3_CAPACITY, L"Capacity : " + p3->getCapacityName());
		this->_menuDisplay->setValueText(P3_BOMB, L"Bomb : " + p3->getBomb()->getTypeName());
	}
	else if (!_p3_dead)
	{
		this->_menuDisplay->remove(P3_TYPE);
		this->_menuDisplay->remove(P3_BOMB_QUANTITY);
		this->_menuDisplay->remove(P3_FIRE_RANGE);
		this->_menuDisplay->remove(P3_SPEED);
		this->_menuDisplay->remove(P3_NB_LIFE);
		this->_menuDisplay->remove(P3_TEAM);
		this->_menuDisplay->remove(P3_CAPACITY);
		this->_menuDisplay->remove(P3_BOMB);
		_p3_dead = true;
	}

	auto *p4 = loadGame.getPlayerByID(3);
	if (p4 != nullptr)
	{
		this->_menuDisplay->setValueText(P4_TYPE, L"Type : " + p4->getTypeName());
		this->_menuDisplay->setValueText(P4_BOMB_QUANTITY, L"Bomb Quantity : " + std::to_wstring(p4->getBombQuantity()));
		this->_menuDisplay->setValueText(P4_FIRE_RANGE, L"Fire Range : " + std::to_wstring(p4->getFireRange()));
		this->_menuDisplay->setValueText(P4_SPEED, L"Speed : " + std::to_wstring(p4->getSpeed()));
		this->_menuDisplay->setValueText(P4_NB_LIFE, L"NB Life : " + std::to_wstring(p4->getNbLife()));
		this->_menuDisplay->setValueText(P4_TEAM, L"Team : " + p4->getTeamName());
		this->_menuDisplay->setValueText(P4_CAPACITY, L"Capacity : " + p4->getCapacityName());
		this->_menuDisplay->setValueText(P4_BOMB, L"Bomb : " + p4->getBomb()->getTypeName());
	}
	else if (!_p4_dead)
	{
		this->_menuDisplay->remove(P4_TYPE);
		this->_menuDisplay->remove(P4_BOMB_QUANTITY);
		this->_menuDisplay->remove(P4_FIRE_RANGE);
		this->_menuDisplay->remove(P4_SPEED);
		this->_menuDisplay->remove(P4_NB_LIFE);
		this->_menuDisplay->remove(P4_TEAM);
		this->_menuDisplay->remove(P4_CAPACITY);
		this->_menuDisplay->remove(P4_BOMB);
		_p4_dead = true;
	}

	if (loadGame.getNbPlayers() <= 1)
	{
		loadGame.updateWinner();
		loadGame.cleanPlayers();
		_p1_dead = false;
		_p2_dead = false;
		_p3_dead = false;
		_p4_dead = false;
		_menuDisplay->removeMenu();
		_menuDisplay = new render::MenuDisplay(_graphElem);
		index = engine::IGuiScene::SCENE_WINNER;
		Music::getInstance()->play(Music::WINNER, false);
	}
}