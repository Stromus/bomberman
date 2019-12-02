/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <algorithm>
#include <irrXML.h>
#include <time/Random.hpp>
#include "engine/game/arena/ChunkPowerUp.hpp"
#include "engine/game/arena/ChunkEmpty.hpp"
#include "engine/game/arena/ChunkUnbreakable.hpp"
#include "engine/game/arena/ChunkBreakable.hpp"
#include "settings/GameSettings.hpp"
#include "engine/game/player/AI.hpp"
#include "engine/game/player/Human.hpp"
#include "settings/GameSettings.hpp"
#include "engine/game/bomb/SimpleBomb.hpp"
#include "engine/game/bomb/GBomb.hpp"
#include "engine/game/bomb/LavaBomb.hpp"
#include "engine/game/bomb/PBomb.hpp"
#include "engine/load/LoadGame.hpp"
#include "settings/Settings.hpp"
#include "open_target/File.hpp"
#include "exception/SettingsException.hpp"
#include "template/Vector.hpp"

engine::LoadGame::LoadGame()
	:_map(nullptr),
	_mode(LOAD),
	_players(std::vector<engine::IPlayer *>())
{
	_quantityPerPlayer.insert(std::pair<short, short>(0, 0));
	_quantityPerPlayer.insert(std::pair<short, short>(1, 0));
	_quantityPerPlayer.insert(std::pair<short, short>(2, 0));
	_quantityPerPlayer.insert(std::pair<short, short>(3, 0));
}

void engine::LoadGame::setMode(loadMode mode)
{
	this->_mode = mode;
}

engine::LoadGame::loadMode engine::LoadGame::getMode()
{
	return (this->_mode);
}

engine::LoadGame::~LoadGame()
{
	_quantityPerPlayer.clear();
}

void engine::LoadGame::cleanMap()
{
	if (_map != nullptr) {
		for (auto &line : _map->getMap()) {
			for (auto &col : line) {
				if (col)
					col->stop();
			}
			line.clear();
		}
		delete _map;
		_map = nullptr;
	}
}

void engine::LoadGame::generateMap()
{
	cleanMap();
	_map = new engine::Map(engine::Map::GENERATE_MAP);
}

void engine::LoadGame::updateGame(Controls::keyIS key)
{
	if (key != Controls::ERROR) {
		int team = Settings::getInstance()->getTeam(Controls::BOMB, key);
		for (auto &player : _players) {
			if (player->getType() == team && player->getType() != IPlayer::AI)
				player->putBomb();
		}
	}
	_map->update(_quantityPerPlayer, _players);
	for (auto &player : _players) {
		player->update(_map->getMap(), _players);
		auto &map = _map->getMap();
		if (map[floor(player->getPosition().y + 0.5f)][floor(player->getPosition().x + 0.5f)]->getType() == IChunk::POWERUP) {
			reinterpret_cast<ChunkPowerUp *>(map[floor(player->getPosition().y + 0.5f)][floor(player->getPosition().x + 0.5f)])->getPowerUp()->capacityActivation(player);
			map[floor(player->getPosition().y + 0.5f)][floor(player->getPosition().x + 0.5f)]->stop();
			map[floor(player->getPosition().y + 0.5f)][floor(player->getPosition().x + 0.5f)] =\
			new ChunkEmpty({floor(player->getPosition().x + 0.5f), 1, floor(player->getPosition().y + 0.5f)});
		}
		while (!player->getPlayerRequests().empty()) {
			_map->analyseNewRequest(player->getPlayerRequests().front(), player, _quantityPerPlayer);
			player->getPlayerRequests().pop();
		}
	}
}

void engine::LoadGame::interpretPlayerBomb(std::map<std::wstring, std::wstring> playerDatas, engine::IPlayer *player)
{
	int membership = std::stoi(playerDatas.at(L"membership"));
	int type = std::stoi(playerDatas.at(L"typeBomb"));

	engine::IBomb *bomb = nullptr;

	switch (type) {
	case engine::IBomb::SIMPLE_BOMB:
		bomb = new engine::SimpleBomb(membership);
		break;
	case engine::IBomb::P_BOMB:
		bomb = new engine::PBomb(membership);
		break;
	case engine::IBomb::G_BOMB:
		bomb = new engine::GBomb(membership);
		break;
	case engine::IBomb::LAVA_BOMB:
		bomb = new engine::LavaBomb(membership);
		break;
	default:
		throw ise::IndieStudioException(ise::CRITICAL, "Unable to load save");
		break;
	}
	bomb->setRange(std::stoi(playerDatas.at(L"range")));
	player->setBomb(bomb);
}

std::vector<std::map<std::wstring, std::wstring>> engine::LoadGame::convertXmlToMap(const std::string &file)
{
	std::vector<std::map<std::wstring, std::wstring>> allContents;
	irr::io::IXMLReader* xml = Irrlicht::getInstance()->getDevice()->getFileSystem()->createXMLReader((SAVE_DIRECTORY + file).data());

	if (xml == 0)
		throw ise::IndieStudioException(ise::CRITICAL, "Unable to load");

	int i = 0;
	std::wstring string;
	std::map<std::wstring, std::wstring > content;

	while (xml && xml->read()) {
		std::wstring nodeName(xml->getNodeName());
		if (xml->getNodeType() == irr::io::EXN_ELEMENT_END) {
			allContents.push_back(content);
			content.clear();
		}
		else if (nodeName == L"Player" || nodeName == L"Chunk" || nodeName == L"Settings") {
			content.insert(std::make_pair(L"savedData", xml->getNodeName()));
		}
		else {
			std::wstring test = xml->getAttributeValueSafe(L"value");
			if (test.empty())
				test = L"0";
			content.insert(std::make_pair(xml->getNodeName(), test));
		}
	}
	return (allContents);
}

void engine::LoadGame::loadPlayer(const std::map<std::wstring, std::wstring> &playerDatas)
{
	int type = stoi(playerDatas.at(L"type"));
	short ID = stoi(playerDatas.at(L"ID"));
	Vector2<float> pos;
	std::string meshName;
	engine::IPlayer *player;
	engine::IPlayer::capacity capacity = static_cast<engine::IPlayer::capacity>(std::stoi(playerDatas.at(L"capacity")));

	auto test = playerDatas.at(L"mesh");
	meshName.assign(test.begin(), test.end());
	pos.x = stof(playerDatas.at(L"x"));
	pos.y = stof(playerDatas.at(L"y"));
	if (type == 0)
		player = new engine::AI(ID, pos, meshName);
	else
		player = player = new engine::Human(static_cast<engine::IPlayer::playerType>(type), ID, pos, meshName);
	player->setBombQuantity(std::stoi(playerDatas.at(L"bombQuantity")));
	player->setFireRange(std::stoi(playerDatas.at(L"fireRange")));
	player->setSpeed(std::stoi(playerDatas.at(L"speed")));
	player->setNbLife(std::stoi(playerDatas.at(L"nbLife")));
	player->setCollision(std::stoi(playerDatas.at(L"checkCollision")));
	player->setInvertControl(std::stoi(playerDatas.at(L"invertedControl")));
	player->setPlantBomb(std::stoi(playerDatas.at(L"plantBomb")));
	player->setCapacity(capacity);
	player->setTargetRotation(std::stoi(playerDatas.at(L"targetRotation")));
	this->interpretPlayerBomb(playerDatas, player);
	_players.push_back(player);
}

void engine::LoadGame::loadSettings(const std::map<std::wstring, std::wstring> &playerDatas)
{
	GameSettings *settings = GameSettings::getInstance();

	settings->setDifficulty(std::stoi(playerDatas.at(L"difficulty")));
	settings->setMapSize({ static_cast<size_t>(std::stoi(playerDatas.at(L"x"))), static_cast<size_t>(std::stoi(playerDatas.at(L"y")))});
	
	this->_map = new engine::Map(engine::Map::NOT_GENERATE_MAP);
}

engine::IBomb *engine::LoadGame::loadBomb(const std::map<std::wstring, std::wstring> &datas)
{
	int membership = std::stoi(datas.at(L"membership"));
	int type = std::stoi(datas.at(L"typeBomb"));

	engine::IBomb *bomb = nullptr;

	switch (type) {
	case engine::IBomb::SIMPLE_BOMB:
		bomb = new engine::SimpleBomb(membership);
		break;
	case engine::IBomb::P_BOMB:
		bomb = new engine::PBomb(membership);
		break;
	case engine::IBomb::G_BOMB:
		bomb = new engine::GBomb(membership);
		break;
	case engine::IBomb::LAVA_BOMB:
		bomb = new engine::LavaBomb(membership);
		break;
	default:
		throw ise::IndieStudioException(ise::CRITICAL, "Unable to load save");
		break;
	}
	bomb->setRange(std::stoi(datas.at(L"range")));
	return (bomb);
}

void engine::LoadGame::loadMap(std::map<std::wstring, std::wstring> &chunkDatas)
{
	int x = std::stoi(chunkDatas.at(L"x"));
	int y = std::stoi(chunkDatas.at(L"y"));
	int z = std::stoi(chunkDatas.at(L"z"));

	int type = std::stoi(chunkDatas.at(L"type"));

	engine::IChunk *chunk = nullptr;

	engine::IPowerUp::PowerUpType puType;
	engine::IBomb *bomb;

	switch (type) {
	case engine::IChunk::BREAKABLE:
		chunk = new engine::ChunkBreakable({static_cast<irr::f32>(x), static_cast<irr::f32>(y), static_cast<irr::f32>(z)});
		break;
	case engine::IChunk::UNBREAKABLE:
		chunk = new engine::ChunkUnbreakable({ static_cast<irr::f32>(x), static_cast<irr::f32>(y), static_cast<irr::f32>(z)});
		break;
	case engine::IChunk::POWERUP:
		puType = static_cast<engine::IPowerUp::PowerUpType>(std::stoi(chunkDatas.at(L"typePowerUp")));
		chunk = new engine::ChunkPowerUp({ static_cast<irr::f32>(x), static_cast<irr::f32>(y), static_cast<irr::f32>(z) }, puType);
		break;
	case engine::IChunk::BOMB:
		bomb = this->loadBomb(chunkDatas);
		chunk = new engine::ChunkBomb(bomb, {static_cast<irr::f32>(x), static_cast<irr::f32>(y), static_cast<irr::f32>(z) });
		static_cast<engine::ChunkBomb *>(chunk)->setNbTotalTick(std::stoi(chunkDatas.at(L"nbTotalTick")));
		break;
	default:
		chunk = new engine::ChunkEmpty({ static_cast<irr::f32>(x), static_cast<irr::f32>(y), static_cast<irr::f32>(z) });
		break;
	}

	GameSettings *settings = GameSettings::getInstance();
	if (!(z <= settings->getSizeMap().y + 2) || !(x <= settings->getSizeMap().x + 2) ||
		z < 0 || x < 0)
		throw ise::IndieStudioException(ise::CONFIGURATION, "Unable to load save");
	auto &map = this->_map->getMap();
	map[z][x] = chunk;
	this->_nbChunk += 1;
}

void engine::LoadGame::loadFromSave(const std::string &file)
{
	auto allContents = this->convertXmlToMap(file);

	try {
		this->_nbChunk = 0;
		for (auto &map : allContents) {
			auto savedData = map.at(L"savedData");
			if (savedData == L"Player") {
				this->loadPlayer(map);
			}
			else if (savedData == L"Settings") {
				this->loadSettings(map);
			}
			else if (savedData == L"Chunk") {
				this->loadMap(map);
			}
			else
				throw ise::IndieStudioException(ise::CRITICAL, "Unable to load save");
		}
		GameSettings *settings = GameSettings::getInstance();
		if (this->_nbChunk != (settings->getSizeMap().x + 2) * (settings->getSizeMap().y + 2))
			throw std::out_of_range("Invalid number of chunks");
	}
	catch (const std::out_of_range &e) {
		std::cerr << e.what() << std::endl;
		throw ise::IndieStudioException(ise::CRITICAL, "Unable to load save");
	}
	this->_map->isMapValid();
}

unsigned long engine::LoadGame::getNbPlayers()
{
	return _players.size();
}

const engine::IPlayer const* engine::LoadGame::getPlayerByID(const short id) const{
	auto res = std::find_if(_players.begin(), _players.end(), [id](engine::IPlayer *p) -> bool {
		return p->getPlayerID() == id;
	});
	if (res == _players.end()) {
		return nullptr;
	}
	return *res;
}

void engine::LoadGame::addPlayer(engine::IPlayer *player)
{
	if (GameSettings::getInstance()->getGameMode()->isCustomStats()) {
		IPlayer::stats custom = GameSettings::getInstance()->getGameMode()->getCustomStats();
		(custom.bombQuantity == 0 ? (custom.bombQuantity += 1) : (custom.bombQuantity));
		player->setBombQuantity(custom.bombQuantity);
		(custom.speed == 0 ? (custom.speed += 1) : (custom.speed));
		player->setSpeed(custom.speed);
		(custom.fireRange == 0 ? (custom.fireRange += 1) : (custom.fireRange));
		player->setFireRange(custom.fireRange);
	}
	if (GameSettings::getInstance()->getGameMode()->isGhost()) {
		player->setCollision(false);
		player->setCapacity(engine::IPlayer::capacity::GHOST);
	}
	if (GameSettings::getInstance()->getGameMode()->isInverted()) {
		player->setInvertControl(true);
		player->setCapacity(engine::IPlayer::capacity::INVERT_CONTROL);
	}
	if (GameSettings::getInstance()->getGameMode()->isBetterBomb()) {
		player->setBomb(new LavaBomb(player->getPlayerID()));
		player->setFireRange(3);
	}
	_players.push_back(player);
}

void engine::LoadGame::cleanPlayers()
{
	for (auto it = _players.begin(); it != _players.end();) {
		if (*it) {
			(*it)->stop();
			it = _players.erase(it);
		}
	}
	_players.clear();
}

void engine::LoadGame::saveStats(irr::io::IXMLWriter* xwriter, engine::IPlayer *player)
{
	int bombQuantity = player->getBombQuantity();
	xwriter->writeElement(L"bombQuantity", true, L"value", std::to_wstring(bombQuantity).data());
	xwriter->writeLineBreak();

	int fireRange = player->getFireRange();
	xwriter->writeElement(L"fireRange", true, L"value", std::to_wstring(fireRange).data());
	xwriter->writeLineBreak();

	int speed = player->getSpeed();
	xwriter->writeElement(L"speed", true, L"value", std::to_wstring(speed).data());
	xwriter->writeLineBreak();
}

void engine::LoadGame::savePos(irr::io::IXMLWriter* xwriter, engine::IPlayer *player)
{
	float x = player->getPosition().x;
	xwriter->writeElement(L"x", true, L"value", std::to_wstring(x).data());
	xwriter->writeLineBreak();

	float y = player->getPosition().y;
	xwriter->writeElement(L"y", true, L"value", std::to_wstring(y).data());
	xwriter->writeLineBreak();
}

void engine::LoadGame::savePlayerBomb(irr::io::IXMLWriter* xwriter, engine::IPlayer *player)
{
	xwriter->writeElement(L"range", true, L"value",
		std::to_wstring(player->getBomb()->getRange()).data());
	xwriter->writeLineBreak();

	xwriter->writeElement(L"typeBomb", true, L"value",
		std::to_wstring(player->getBomb()->getType()).data());
	xwriter->writeLineBreak();

	xwriter->writeElement(L"membership", true, L"value",
		std::to_wstring(player->getBomb()->getMemberShipPlayer()).data());
	xwriter->writeLineBreak();
}

void engine::LoadGame::savePlayer(irr::io::IXMLWriter* xwriter)
{
	for (auto &player : this->_players) {
		xwriter->writeElement(L"Player");
		xwriter->writeLineBreak();

		xwriter->writeElement(L"type", true, L"value", std::to_wstring(player->getType()).data());
		xwriter->writeLineBreak();

		this->saveStats(xwriter, player);

		xwriter->writeElement(L"nbLife", true, L"value", std::to_wstring(player->getNbLife()).data());
		xwriter->writeLineBreak();

		xwriter->writeElement(L"team", true, L"value", std::to_wstring(player->getTeam()).data());
		xwriter->writeLineBreak();

		xwriter->writeElement(L"ID", true, L"value", std::to_wstring(player->getPlayerID()).data());
		xwriter->writeLineBreak();

		xwriter->writeElement(L"checkCollision", true, L"value", std::to_wstring(player->isCollisionActivate()).data());
		xwriter->writeLineBreak();

		xwriter->writeElement(L"invertedControl", true, L"value", std::to_wstring(player->isControlInverted()).data());
		xwriter->writeLineBreak();

		xwriter->writeElement(L"plantBomb", true, L"value", std::to_wstring(player->isPlantBombActivate()).data());
		xwriter->writeLineBreak();

		xwriter->writeElement(L"capacity", true, L"value", std::to_wstring(player->getCapacity()).data());
		xwriter->writeLineBreak();

		std::wstring wmeshName;
		std::string meshName(player->getMeshName());
		wmeshName.assign(meshName.begin(), meshName.end());
		xwriter->writeElement(L"mesh", true, L"value", wmeshName.data());
		xwriter->writeLineBreak();

		this->savePos(xwriter, player);

		xwriter->writeElement(L"targetRotation", true, L"value", std::to_wstring(player->getTargetRotation()).data());
		xwriter->writeLineBreak();

		this->savePlayerBomb(xwriter, player);

		xwriter->writeClosingTag(L"Player");
		xwriter->writeLineBreak();
	}
}

void engine::LoadGame::saveGameSettings(irr::io::IXMLWriter* xwriter)
{
	auto gameSettings = GameSettings::getInstance();

	xwriter->writeElement(L"Settings");
	xwriter->writeLineBreak();

	xwriter->writeElement(L"difficulty", true, L"value", std::to_wstring(gameSettings->getDifficulty()).data());
	xwriter->writeLineBreak();

	xwriter->writeElement(L"x", true, L"value", std::to_wstring(gameSettings->getSizeMap().x).data());
	xwriter->writeLineBreak();

	xwriter->writeElement(L"y", true, L"value", std::to_wstring(gameSettings->getSizeMap().y).data());
	xwriter->writeLineBreak();

	xwriter->writeClosingTag(L"Settings");
	xwriter->writeLineBreak();
}

void engine::LoadGame::saveMap(irr::io::IXMLWriter* xwriter)
{
	auto map = this->_map->getMap();

	for (auto chunkVector : map) {
		for (auto chunk : chunkVector) {

			std::wstring wmeshName;
			auto meshName = chunk->getMeshName();
			wmeshName.assign(meshName.begin(), meshName.end());

			xwriter->writeElement(L"Chunk");
			xwriter->writeLineBreak();

			xwriter->writeElement(L"breakable", true, L"value", std::to_wstring(chunk->isBreakable()).data());
			xwriter->writeLineBreak();

			xwriter->writeElement(L"meshName", true, L"value", wmeshName.data());
			xwriter->writeLineBreak();

			xwriter->writeElement(L"x", true, L"value", std::to_wstring(chunk->getPosition().X).data());
			xwriter->writeLineBreak();

			xwriter->writeElement(L"y", true, L"value", std::to_wstring(chunk->getPosition().Y).data());
			xwriter->writeLineBreak();

			xwriter->writeElement(L"z", true, L"value", std::to_wstring(chunk->getPosition().Z).data());
			xwriter->writeLineBreak();

			xwriter->writeElement(L"type", true, L"value", std::to_wstring(chunk->getType()).data());
			xwriter->writeLineBreak();

			if (chunk->getType() == engine::IChunk::BOMB) {
				engine::ChunkBomb *bomb = static_cast<engine::ChunkBomb *>(chunk);

				xwriter->writeElement(L"nbTotalTick", true, L"value", std::to_wstring(bomb->getNbTotalTick()).data());
				xwriter->writeLineBreak();

				xwriter->writeElement(L"range", true, L"value",
					std::to_wstring(bomb->getBomb()->getRange()).data());
				xwriter->writeLineBreak();

				xwriter->writeElement(L"typeBomb", true, L"value",
					std::to_wstring(bomb->getBomb()->getType()).data());
				xwriter->writeLineBreak();

				xwriter->writeElement(L"membership", true, L"value",
					std::to_wstring(bomb->getBomb()->getMemberShipPlayer()).data());
				xwriter->writeLineBreak();
			}

			if (chunk->getType() == engine::IChunk::POWERUP) {
				engine::ChunkPowerUp *chunkPowerUp = static_cast<engine::ChunkPowerUp *>(chunk);

				xwriter->writeElement(L"typePowerUp", true, L"value", std::to_wstring(chunkPowerUp->getPowerUp()->getType()).data());
				xwriter->writeLineBreak();

				xwriter->writeElement(L"invulnerability", true, L"value", std::to_wstring(chunkPowerUp->getPowerUp()->isInvulnerable()).data());
				xwriter->writeLineBreak();

				xwriter->writeElement(L"tickID", true, L"value", std::to_wstring(chunkPowerUp->getPowerUp()->getTickID()).data());
				xwriter->writeLineBreak();

				std::wstring wmeshNamePowerUp;
				auto meshNamePowerUp = chunkPowerUp->getPowerUp()->getMeshName();
				wmeshNamePowerUp.assign(meshNamePowerUp.begin(), meshNamePowerUp.end());

				xwriter->writeElement(L"meshNamePowerUp", true, L"value", wmeshNamePowerUp.data());
				xwriter->writeLineBreak();
			}
			xwriter->writeClosingTag(L"Chunk");
			xwriter->writeLineBreak();
		}
	}
}

void engine::LoadGame::saveGame(const std::string &fileName)
{
	auto device = Irrlicht::getInstance()->getDevice();
	irr::io::IXMLWriter* xwriter = device->getFileSystem()->createXMLWriter((SAVE_DIRECTORY + fileName).data());

	if (xwriter == 0)
		return;
	//write xml header
	xwriter->writeXMLHeader();
	xwriter->writeLineBreak();

	this->savePlayer(xwriter);
	this->saveGameSettings(xwriter);
	this->saveMap(xwriter);

	xwriter->drop();
}

int engine::LoadGame::getWinner()
{
	return _winnerID;
}

void engine::LoadGame::updateWinner()
{
	if (_players.size() == 0) {
		_winnerID = 0;
		return;
	}
	_winnerID = _players.front()->getPlayerID() + 1;
}
