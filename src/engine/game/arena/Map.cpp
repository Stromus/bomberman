/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <engine/game/arena/ChunkBreakable.hpp>
#include <engine/game/arena/ChunkUnbreakable.hpp>
#include <engine/game/arena/ChunkBomb.hpp>
#include <engine/game/arena/ChunkPowerUp.hpp>
#include <settings/Controls.hpp>
#include <sound/Noise.hpp>
#include "engine/game/arena/ChunkEmpty.hpp"
#include "settings/GameSettings.hpp"
#include "time/Random.hpp"
#include "engine/game/arena/Map.hpp"
#include "engine/game/player/APlayer.hpp"
#include "render/Animator.hpp"
#include "engine/game/bomb/SimpleBomb.hpp"
#include "settings/GameSettings.hpp"
#include "exception/IndieStudioException.hpp"

engine::Map::Map(const generate &gen)
{
	_mapSize = {GameSettings::getInstance()->getSizeMap().x + 2, GameSettings::getInstance()->getSizeMap().y + 2};
	for (size_t i = 0; i < _mapSize.y; i += 1) {
		std::vector<IChunk *>	line;
		for (size_t j = 0; j < _mapSize.x; j += 1) {
			if (gen == GENERATE_MAP)
				line.push_back(generateNewChunk(i, j));
			else
				line.push_back(nullptr);
		}
		_map.push_back(line);
	}
}

engine::Map::~Map()
{
	for (auto line = _map.begin(); line != _map.end(); line++)
		line->clear();
	_map.clear();
}

engine::IChunk *engine::Map::generateRandomChunk(size_t y, size_t x)
{
	if (GameSettings::getInstance()->getGameMode()->isNoWall())
		return new ChunkEmpty(irr::core::vector3df(x, 1, y));
	if (GameSettings::getInstance()->getGameMode()->isCastle())
		return new ChunkBreakable(irr::core::vector3df(x, 1, y));
	if (Random::getRandomNumber(0, 100) >= 75)
		return new ChunkEmpty(irr::core::vector3df(x, 1, y));
	else
		return new ChunkBreakable(irr::core::vector3df(x, 1.f, y));
}

engine::IChunk *engine::Map::generateNewChunk(size_t y, size_t x)
{
	if (isBorderMap(y, x))
		return new ChunkUnbreakable(irr::core::vector3df(x, 1.f, y));
	if (isIndestructiblePosition(y, x))
		return new ChunkUnbreakable(irr::core::vector3df(x, 1.f, y));
	if (isPlayerEmplacement(y, x))
		return new ChunkEmpty(irr::core::vector3df(x, 1, y));
	return generateRandomChunk(y, x);
}

bool engine::Map::isBorderMap(size_t y, size_t x)
{
	return y == 0 || y == _mapSize.y - 1 || x == 0 || x == _mapSize.x - 1;
}

bool engine::Map::checkSide(size_t y, size_t x, Side side)
{
	switch (side) {
	case NORTH_WEST:
		return (y == 1 && x == 1) || (y == 2 && x == 1) || (y == 1 && x == 2);
	case NORTH_EAST:
		return (y == 1 && x == _mapSize.x - 2) || (y == 2 && x == _mapSize.x - 2) ||\
		(y == 1 && x == _mapSize.x - 3);
	case SOUTH_WEST:
		return (y == _mapSize.y - 2 && x == 1) || (y == _mapSize.y - 3 && x == 1) ||\
		(y == _mapSize.y - 2 && x == 2);
	case SOUTH_EAST:
		return (y == _mapSize.y - 2 && x == _mapSize.x - 2) ||\
		(y == _mapSize.y - 3 && x == _mapSize.x - 2) ||\
		(y == _mapSize.y - 2 && x == _mapSize.x - 3);
	default: return false;
	}
}

bool engine::Map::isPlayerEmplacement(size_t y, size_t x)
{
	return checkSide(y, x, NORTH_WEST) || checkSide(y, x, NORTH_EAST) ||\
	checkSide(y, x, SOUTH_WEST) || checkSide(y, x, SOUTH_EAST);
}

bool engine::Map::isIndestructiblePosition(size_t y, size_t x)
{
	if (GameSettings::getInstance()->getGameMode()->isAllDestructible())
		return false;
	return y % 2 == 0 && x % 2 == 0;
}

void engine::Map::update(std::map<short, short> &quantity, std::vector<engine::IPlayer *> &players)
{
	for (auto &q : quantity)
		q.second = 0;
	for (auto &line : _map)
		for (auto &cell : line) {
			if (cell->getType() == IChunk::BOMB && (reinterpret_cast<ChunkBomb *>(cell))->isExplosed()) {
				updateMapWithBombExplosion(reinterpret_cast<ChunkBomb *>(cell), players);
				cell->stop();
				cell = new ChunkEmpty({cell->getPosition().X, 1, cell->getPosition().Z});
			}
			if (cell->getType() == IChunk::BOMB)
				quantity.find(((ChunkBomb *)(cell))->getBomb()->getMemberShipPlayer())->second += 1;
		}
}

void engine::Map::updateMapWithBombExplosion(engine::ChunkBomb *chunk, std::vector<engine::IPlayer *> &players)
{
	short	range = chunk->getBomb()->getRange();

	if (chunk->getBomb()->getType() == IBomb::G_BOMB || chunk->getBomb()->getType() == IBomb::P_BOMB)
		range += 15;
	updateDirectionExplosion(range, {static_cast<int>(chunk->getPosition().X),\
	static_cast<int>(chunk->getPosition().Z)}, NORTH, chunk->getBomb()->getType(), players);
	updateDirectionExplosion(range, {static_cast<int>(chunk->getPosition().X),\
	static_cast<int>(chunk->getPosition().Z)}, WEST, chunk->getBomb()->getType(), players);
	updateDirectionExplosion(range, {static_cast<int>(chunk->getPosition().X),\
	static_cast<int>(chunk->getPosition().Z)}, SOUTH, chunk->getBomb()->getType(), players);
	updateDirectionExplosion(range, {static_cast<int>(chunk->getPosition().X),\
	static_cast<int>(chunk->getPosition().Z)}, EAST, chunk->getBomb()->getType(), players);
}

void engine::Map::updateDirectionExplosion(short range, Vector2<int> pos,\
const direction &dir, const IBomb::bombType &type, std::vector<engine::IPlayer *> &players)
{
	irr::core::vector2di save = { pos.x, pos.y };
	int	explsSize = 0;

	while (range >= 0) {
		for (auto it = players.begin(); it != players.end();) {
			if (floor((*it)->getPosition().y + 0.5f) == pos.y && floor((*it)->getPosition().x + 0.5f) == pos.x) {
				(*it)->setNbLife((*it)->getNbLife() - static_cast<short>(1));
				if ((*it)->getNbLife() == 0) {
					(*it)->stop();
					Noise::getInstance()->play(Noise::DEATH);
					it = players.erase(it);
				} else
					++it;
			}
			else
				++it;
		}
		switch (_map[pos.y][pos.x]->getType()) {
		case IChunk::POWERUP:
			if (!reinterpret_cast<ChunkPowerUp *>(_map[pos.y][pos.x])->getPowerUp()->isInvulnerable()) {
				reinterpret_cast<ChunkPowerUp *>(_map[pos.y][pos.x])->stop();
				_map[pos.y][pos.x] = new ChunkEmpty({static_cast<float>(pos.x), 1, static_cast<float>(pos.y)});
			}
			break;
		case IChunk::UNBREAKABLE:
			range = 0;
			break;
		case IChunk::BREAKABLE:
			if (type != IBomb::bombType::LAVA_BOMB && type != IBomb::bombType::G_BOMB)
				range = 0;
			reinterpret_cast<ChunkBreakable *>(_map[pos.y][pos.x])->stop();
			if (Random::getRandomNumber(0, 100) > 45)
				_map[pos.y][pos.x] = new ChunkEmpty({static_cast<float>(pos.x), 1, static_cast<float>(pos.y)});
			else
				_map[pos.y][pos.x] = new ChunkPowerUp({static_cast<float>(pos.x), 1, static_cast<float>(pos.y)});
			break;
		case IChunk::BOMB:
			reinterpret_cast<ChunkBomb *>(_map[pos.y][pos.x])->explosedFaster();
			break;
		default : break;
		}
		switch (dir) {
		case NORTH:
			pos.y += 1;
			break;
		case SOUTH:
			pos.y -= 1;
			break;
		case EAST:
			pos.x += 1;
			break;
		case WEST:
			pos.x -= 1;
			break;
		}
		explsSize += 1;
		range -= 1;
	}
	switch (type) {
	case IBomb::P_BOMB:
		render::Animator::addBeam(save, explsSize - 1, dir, irr::video::SColor(0, 150, 255, 0));
		break;
	case IBomb::LAVA_BOMB:
		render::Animator::addBeam(save, explsSize - 1, dir, irr::video::SColor(0, 255, 100, 0));
		break;
	case IBomb::G_BOMB:
		render::Animator::addBeam(save, explsSize - 1, dir, irr::video::SColor(0, 150, 255, 100));
		break;
	default:
		render::Animator::addBeam(save, explsSize - 1, dir, irr::video::SColor(0, 0, 150, 255));
		break;
	}
	Noise::getInstance()->play(Noise::BOMB_EXPLOSION);
}

std::vector<std::vector<engine::IChunk *>> &engine::Map::getMap()
{
	return this->_map;
}

bool engine::Map::analyseCollision(const engine::IPlayer::request &req, const IChunk::chunkType &type, const Controls::actions &act)
{
	if (int(req.requestPos.y - 0.3f) < 0 || int(req.requestPos.y - 0.3f) > GameSettings::getInstance()->getSizeMap().y + 2)
		return false;
	if (int(req.requestPos.x - 0.3f) < 0 || int(req.requestPos.x - 0.3f) > GameSettings::getInstance()->getSizeMap().x + 2)
		return false;
	switch (act) {
	case Controls::actions::MOVE_UP:
		if (_map[static_cast<int>(req.requestPos.y - 0.3f)][static_cast<int>(req.requestPos.x)]->getType() == type &&
			_map[static_cast<int>(req.requestPos.y - 0.3f)][static_cast<int>(req.requestPos.x - 0.3f)]->getType() == type &&
			_map[static_cast<int>(req.requestPos.y - 0.3f)][static_cast<int>(req.requestPos.x + 0.3f)]->getType() == type)
			return true;
		return false;
	case Controls::actions::MOVE_DOWN:
		if (_map[static_cast<int>(req.requestPos.y + 0.3f)][static_cast<int>(req.requestPos.x)]->getType() == type &&
			_map[static_cast<int>(req.requestPos.y + 0.3f)][static_cast<int>(req.requestPos.x + 0.3f)]->getType() == type &&
			_map[static_cast<int>(req.requestPos.y + 0.3f)][static_cast<int>(req.requestPos.x - 0.3f)]->getType() == type)
			return true;
		return false;
	case Controls::actions::MOVE_RIGHT:
		if (_map[static_cast<int>(req.requestPos.y)][static_cast<int>(req.requestPos.x - 0.3f)]->getType() == type &&
			_map[static_cast<int>(req.requestPos.y - 0.3f)][static_cast<int>(req.requestPos.x - 0.3f)]->getType() == type &&
			_map[static_cast<int>(req.requestPos.y + 0.3f)][static_cast<int>(req.requestPos.x - 0.3f)]->getType() == type)
			return true;
		return false;
		case Controls::actions::MOVE_LEFT:
			if (_map[static_cast<int>(req.requestPos.y)][static_cast<int>(req.requestPos.x + 0.3f)]->getType() == type &&
				_map[static_cast<int>(req.requestPos.y + 0.3f)][static_cast<int>(req.requestPos.x + 0.3f)]->getType() == type &&
				_map[static_cast<int>(req.requestPos.y - 0.3f)][static_cast<int>(req.requestPos.x + 0.3f)]->getType() == type)
			return true;
		return false;
	}
}

void engine::Map::analyseNewRequest(const engine::IPlayer::request &req, engine::IPlayer *player, const std::map<short, short> &quantity)
{
	switch (req.action) {
	case Controls::actions::BOMB:
		if (quantity.find(player->getPlayerID())->second == player->getBombQuantity())
			break;
		if (_map[static_cast<int>(req.requestPos.y)][static_cast<int>(req.requestPos.x)]->getType() == IChunk::chunkType::EMPTY) {
			_map[static_cast<int>(req.requestPos.y)][static_cast<int>(req.requestPos.x)] = new ChunkBomb(
				player->getBomb(), {floor(req.requestPos.x), 1, floor(req.requestPos.y)});
			reinterpret_cast<ChunkBomb *>(_map[static_cast<int>(req.requestPos.y)][static_cast<int>(req.requestPos.x)])->getBomb()->setRange(player->getFireRange());
		}
		break;
	case Controls::actions::MOVE_UP:
		if (analyseCollision(req, IChunk::POWERUP, Controls::actions::MOVE_UP) ||\
		analyseCollision(req, IChunk::EMPTY, Controls::actions::MOVE_UP) ||\
		(_map[static_cast<int>(player->getPosition().y + 0.5f)][static_cast<int>(player->getPosition().x + 0.5f)]->getType() == IChunk::chunkType::BOMB &&\
		analyseCollision(req, IChunk::BOMB, Controls::actions::MOVE_UP)) ||\
		(!player->isCollisionActivate() && analyseCollision(req, IChunk::BREAKABLE, Controls::actions::MOVE_UP)))
			player->setPosition({req.requestPos.x - 0.5f, req.requestPos.y - 0.5f});
		break;
	case Controls::actions::MOVE_DOWN:
		if (analyseCollision(req, IChunk::POWERUP, Controls::actions::MOVE_DOWN) ||\
		analyseCollision(req, IChunk::EMPTY, Controls::actions::MOVE_DOWN) ||\
		(_map[static_cast<int>(player->getPosition().y + 0.5f)][static_cast<int>(player->getPosition().x + 0.5f)]->getType() == IChunk::chunkType::BOMB &&\
		analyseCollision(req, IChunk::BOMB, Controls::actions::MOVE_DOWN)) ||\
		(!player->isCollisionActivate() && analyseCollision(req, IChunk::BREAKABLE, Controls::actions::MOVE_DOWN)))
			player->setPosition({req.requestPos.x - 0.5f, req.requestPos.y - 0.5f});
		break;
	case Controls::actions::MOVE_RIGHT:
		if (analyseCollision(req, IChunk::POWERUP, Controls::actions::MOVE_RIGHT) ||\
		analyseCollision(req, IChunk::EMPTY, Controls::actions::MOVE_RIGHT) ||\
		(_map[static_cast<int>(player->getPosition().y + 0.5f)][static_cast<int>(player->getPosition().x + 0.5f)]->getType() == IChunk::chunkType::BOMB &&\
		analyseCollision(req, IChunk::BOMB, Controls::actions::MOVE_RIGHT)) ||\
		(!player->isCollisionActivate() && analyseCollision(req, IChunk::BREAKABLE, Controls::actions::MOVE_RIGHT)))
			player->setPosition({req.requestPos.x - 0.5f, req.requestPos.y - 0.5f});
		break;
	case Controls::actions::MOVE_LEFT:
		if (analyseCollision(req, IChunk::POWERUP, Controls::actions::MOVE_LEFT) ||\
		analyseCollision(req, IChunk::EMPTY, Controls::actions::MOVE_LEFT) ||\
		(_map[static_cast<int>(player->getPosition().y + 0.5f)][static_cast<int>(player->getPosition().x + 0.5f)]->getType() == IChunk::chunkType::BOMB &&\
		analyseCollision(req, IChunk::BOMB, Controls::actions::MOVE_LEFT)) ||\
		(!player->isCollisionActivate() && analyseCollision(req, IChunk::BREAKABLE, Controls::actions::MOVE_LEFT)))
			player->setPosition({req.requestPos.x - 0.5f, req.requestPos.y - 0.5f});
		break;
	}
}

void engine::Map::setMapSize(Vector2<size_t> size)
{
	this->_mapSize = size;
}

bool engine::Map::isMapValid()
{
	for (auto column : this->_map) {
		for (auto chunk : column) {
			if (chunk == nullptr)
				throw ise::IndieStudioException(ise::CRITICAL, "Map is not fully loaded");
		}
	}
}