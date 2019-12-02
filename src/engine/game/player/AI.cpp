/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <iostream>
#include <time/Random.hpp>
#include <engine/game/arena/ChunkPowerUp.hpp>
#include <algorithm>
#include "settings/GameSettings.hpp"
#include "engine/game/player/AI.hpp"

engine::AI::AI(const short &ID, const Vector2<float> &pos, const std::string &meshName)
	: APlayer(IPlayer::AI, ID, pos, meshName),
	_collisionMap(),
	_explosionMap(),
	_currentObj(NOTHING),
	_positionToReach(),
	_ancientPos({0.0f, 0.0f})
{
	_meshNode = Irrlicht::getInstance()->createMesh(meshName, {(pos.x), 1, (pos.y)}, irr::core::vector3df(1, 1, 1));
}

void engine::AI::updatePlayer(const std::vector<std::vector<engine::IChunk *>> &map, const std::vector<engine::IPlayer *> &players)
{
	_map = map;
	_players = players;
	updateCollisionMap(map);
	updateExplosionMap(map);
	beginAIAlgorithm(players);
}

void engine::AI::initializeCollisionMap(const std::vector<std::vector<engine::IChunk *>> &map)
{
	for (auto &line : map) {
		std::vector<bool> lineCol;
		for (auto &col : line)
			lineCol.push_back(col->getType() == IChunk::EMPTY || col->getType() == IChunk::POWERUP);
		_collisionMap.push_back(lineCol);
	}
}

void engine::AI::updateCollisionMap(const std::vector<std::vector<engine::IChunk *>> &map)
{
	if (_collisionMap.empty())
		initializeCollisionMap(map);
	for (auto i = 0; i < GameSettings::getInstance()->getSizeMap().y + 2; i += 1)
		for (auto j = 0; j < GameSettings::getInstance()->getSizeMap().x + 2; j += 1)
			_collisionMap[i][j] = map[i][j]->getType() == IChunk::EMPTY || map[i][j]->getType() == IChunk::POWERUP ||\
			(map[i][j]->getType() == IChunk::BREAKABLE && !_checkCollision);
}

void engine::AI::initializeExplosionMap(const std::vector<std::vector<engine::IChunk *>> &map)
{
	for (auto &line : map) {
		std::vector<bool> lineCol;
		for (auto &col : line)
			lineCol.push_back(col->getType() == IChunk::BOMB);
		_explosionMap.push_back(lineCol);
	}
}

void engine::AI::updateExplosionMap(const std::vector<std::vector<engine::IChunk *>> &map)
{
	if (_explosionMap.empty())
		initializeExplosionMap(map);
	for (auto i = 0; i < GameSettings::getInstance()->getSizeMap().y + 2; i += 1)
		for (auto j = 0; j < GameSettings::getInstance()->getSizeMap().x + 2; j += 1)
			_explosionMap[i][j] = false;
	for (auto i = 0; i < GameSettings::getInstance()->getSizeMap().y + 2; i += 1)
		for (auto j = 0; j < GameSettings::getInstance()->getSizeMap().x + 2; j += 1)
			if (map[i][j]->getType() == IChunk::BOMB)
				addExplosionRangeToExplosionMap(map, i, j, reinterpret_cast<ChunkBomb *>(map[i][j]));
}

void engine::AI::addExplosionRangeToExplosionMap(const std::vector<std::vector<engine::IChunk *>> &map, int i,\
							int j, const engine::ChunkBomb *chunk)
{
	_explosionMap[i][j] = true;
	calculExplosionRange(map, i - 1, j, chunk->getBomb(), 0);
	calculExplosionRange(map, i + 1, j, chunk->getBomb(), 1);
	calculExplosionRange(map, i, j - 1, chunk->getBomb(), 2);
	calculExplosionRange(map, i, j + 1, chunk->getBomb(), 3);
}

void engine::AI::calculExplosionRange(const std::vector<std::vector<engine::IChunk *>> &map, int i,\
							int j, engine::IBomb *bomb, short dir)
{
	short	range;

	(bomb->getType() == IBomb::G_BOMB || bomb->getType() == IBomb::P_BOMB ? (range = 15) : (range = bomb->getRange()));
	while (range > 0) {
		if (map[i][j]->getType() == IChunk::UNBREAKABLE ||
			((bomb->getType() != IBomb::G_BOMB && bomb->getType() != IBomb::LAVA_BOMB) &&\
			map[i][j]->getType() == IChunk::BREAKABLE))
			return;
		_explosionMap[i][j] = true;
		switch (dir) {
		case 0:
			i -= 1;
			break;
		case 1:
			i += 1;
			break;
		case 2:
			j -= 1;
			break;
		case 3:
			j += 1;
			break;
		default: break;
		}
		range -= 1;
	}
}

/**********************************************************************/

void engine::AI::beginAIAlgorithm(const std::vector<engine::IPlayer *> &players)
{
	if (_ancientPos.x == _position.x && _ancientPos.y == _position.y) {
		_position.x = floor(_ancientPos.x + 0.5f);
		_position.y = floor(_ancientPos.y + 0.5f);
		_currentObj = NOTHING;
	}
	if (_currentObj == NOTHING) {
		_meshNode->switchAnimation(render::MeshNode::IDLE);
		createNewObjectif(players);
		_meshNode->switchAnimation(render::MeshNode::WALK);
	}
	else
		createNewRequestFromObjectif(players);
	if (_plantBomb)
		_requests.push({Controls::actions::BOMB, {floor(_position.x + 0.5f), floor(_position.y + 0.5f)}});
}

bool engine::AI::amISafe()
{
	return !_explosionMap[floor(_position.y + 0.5f)][floor(_position.x + 0.5f)];
}

void engine::AI::createNewObjectif(const std::vector<engine::IPlayer *> &players)
{
	if (!amISafe())
		breadthAlgorithm(BREADTH_SAFE_ZONE, -1);
	else {
		int nb = Random::getRandomNumber(0, 2);
		while (_currentObj == NOTHING && nb < 10) {
			if (!amISafe()) {
				breadthAlgorithm(BREADTH_SAFE_ZONE, -1);
				break;
			}
			switch (nb % 3) {
			case 0:
				if (GameSettings::getInstance()->getDifficulty() >= 2)
					breadthAlgorithm(BREADTH_POWER_UP, -1);
				break;
			case 1:
				if (_checkCollision)
					breadthAlgorithm(BREADTH_BLOC, -1);
				break;
			case 2:
				breadthAlgorithm(BREADTH_PLAYERS, -1);
				break;
			}
			nb = nb + 1;
		}
	}
	if ((_currentObj == NOTHING && foundEnemyPlayer(_position.x, _position.y)) || _plantBomb)
		_requests.push({Controls::actions::BOMB, {floor(_position.x + 0.5f), floor(_position.y + 0.5f)}});
}

void engine::AI::createNewRequestFromObjectif(const std::vector<engine::IPlayer *> &players)
{
	objectif posToReach = _positionToReach.front();
	if (abs(posToReach.x - _position.x) < 0.1 && abs(posToReach.y - _position.y) < 0.1) {
		_position.x = floor(posToReach.x + 0.5f);
		_position.y = floor(posToReach.y + 0.5f);
		if (_currentObj == POWER_UP_TO_TAKE) {
			if (_map[floor(_positionToReach.back().y + 0.5f)][floor(_positionToReach.back().x + 0.5f)]->getType() != IChunk::POWERUP) {
				_currentObj = NOTHING;
				return;
			}
		}
		if (_currentObj == PLAYER_TO_KILL) {
			if (abs(_position.x - _positionToReach.back().x) < 3.0f && abs(_position.y - _positionToReach.back().y) < 3.0f) {
				if (Random::getRandomNumber(0, 100) > 50) {
					_requests.push({Controls::actions::BOMB, {floor(_position.x + 0.5f), floor(_position.y + 0.5f)}});
					_currentObj = NOTHING;
				}
			}
			if (Random::getRandomNumber(0, 100) > 70)
				breadthAlgorithm(BREADTH_PLAYERS, -1);
		}
		_positionToReach.pop();
		if (_positionToReach.empty()) {
			if (_currentObj == BLOC_TO_DESTROY)
				_requests.push({Controls::actions::BOMB, {floor(_position.x + 0.5f), floor(_position.y + 0.5f)}});
			_currentObj = NOTHING;
			return;
		}
		posToReach = _positionToReach.front();
		if (!amISafe() && _currentObj != SURVIVE_FROM_EXPLS)
			breadthAlgorithm(BREADTH_SAFE_ZONE, -1);
		if (!canGoOnThisChunk(posToReach.x, posToReach.y) &&\
		_map[floor(posToReach.y + 0.5f)][floor(posToReach.x + 0.5f)]->getType() != IChunk::BOMB)
			breadthAlgorithm(BREADTH_SAFE_ZONE, -1);
		if (!canGoOnThisChunk(posToReach.x, posToReach.y)) {
			_currentObj = NOTHING;
			return;
		}
	}
	_ancientPos = _position;
	if (abs(posToReach.x - _position.x) > 0.1) {
		if (posToReach.x - _position.x > 0.0)
			(_invertedControl ? (createRequest(Controls::actions::MOVE_RIGHT)) : (createRequest(Controls::actions::MOVE_LEFT)));
		else
			(_invertedControl ? (createRequest(Controls::actions::MOVE_LEFT)) : (createRequest(Controls::actions::MOVE_RIGHT)));
	}
	else if (abs(posToReach.y - _position.y) > 0.1)
		if (posToReach.y - _position.y < 0.0)
			(_invertedControl ? (createRequest(Controls::actions::MOVE_DOWN)) : (createRequest(Controls::actions::MOVE_UP)));
		else
			(_invertedControl ? (createRequest(Controls::actions::MOVE_UP)) : (createRequest(Controls::actions::MOVE_DOWN)));
}

bool engine::AI::foundEnemyPlayer(float x, float y)
{
	for (auto &player : _players) {
		if (player->getPlayerID() != _playerID) {
			if (floor(player->getPosition().x + 0.5f) == floor(x + 0.5f) &&\
			floor(player->getPosition().y + 0.5f) == floor(y + 0.5f))
				return true;
		}
	}
	return false;
}

bool engine::AI::foundGoodPowerUp(float x, float y)
{
	if (_map[floor(y + 0.5f)][floor(x + 0.5f)]->getType() == IChunk::POWERUP) {
		auto pu = reinterpret_cast<ChunkPowerUp *>(_map[floor(y + 0.5f)][floor(x + 0.5f)]);
		if (pu->getPowerUp()->getType() == IPowerUp::QUANTITY_UP || pu->getPowerUp()->getType() == IPowerUp::FIRE_UP ||\
		pu->getPowerUp()->getType() == IPowerUp::SPEED_UP || pu->getPowerUp()->getType() == IPowerUp::LAVA_BOMB ||\
		pu->getPowerUp()->getType() == IPowerUp::G_BOMB || pu->getPowerUp()->getType() == IPowerUp::P_BOMB ||\
		pu->getPowerUp()->getType() == IPowerUp::SHIELD || pu->getPowerUp()->getType() == IPowerUp::GHOST)
			return true;
	}
	return false;
}

void engine::AI::checkStopCondition(std::queue<objectif> obj, float x, float y, int range, const engine::AI::breadthType &type)
{
	switch (type) {
	case BREADTH_SAFE_ZONE:
		if (canGoOnThisChunk(x, y)) {
			_collisionMap[floor(y + 0.5f)][floor(x + 0.5f)] = false;
			obj.push({x, y, range});
			if (AmISafeOnThisChunk(x, y)) {
				_validPaths.push_back(obj);
				_currentObj = SURVIVE_FROM_EXPLS;
				return;
			}
			_paths.push(obj);
		}
		break;
	case BREADTH_PLAYERS:
		if (canGoOnThisChunk(x, y) && AmISafeOnThisChunk(x, y)) {
			_collisionMap[floor(y + 0.5f)][floor(x + 0.5f)] = false;
			obj.push({x, y, range});
			if (foundEnemyPlayer(x, y)) {
				_validPaths.push_back(obj);
				_currentObj = PLAYER_TO_KILL;
				return;
			}
			_paths.push(obj);
		}
		break;
	case BREADTH_BLOC:
		if (_map[floor(y + 0.5f)][floor(x + 0.5f)]->getType() == IChunk::BREAKABLE) {
			_collisionMap[floor(y + 0.5f)][floor(x + 0.5f)] = false;
			_validPaths.push_back(obj);
			_currentObj = BLOC_TO_DESTROY;
			return;
		}
		if (canGoOnThisChunk(x, y) && AmISafeOnThisChunk(x, y)) {
			_collisionMap[floor(y + 0.5f)][floor(x + 0.5f)] = false;
			obj.push({x, y, range});
			_paths.push(obj);
		}
		break;
	case BREADTH_POWER_UP:
		if (canGoOnThisChunk(x, y) && AmISafeOnThisChunk(x, y)) {
			_collisionMap[floor(y + 0.5f)][floor(x + 0.5f)] = false;
			obj.push({x, y, range});
			if (foundGoodPowerUp(x, y)) {
				_validPaths.push_back(obj);
				_currentObj = POWER_UP_TO_TAKE;
				return;
			}
			_paths.push(obj);
		}
		break;
	}
}

int engine::AI::getMinValueInAllPaths(int rangeMax)
{
	int	min;

	(rangeMax == -1 ? (min = 100) : (min = rangeMax));
	for (auto &obj : _validPaths) {
		if (min > obj.back().range)
			min = obj.back().range;
	}
	return min;
}

void engine::AI::breadthAlgorithm(const breadthType &type, int rangeMax)
{
	std::vector<std::vector<bool>> saveCol = _collisionMap;

	_paths = {};
	_validPaths = {};
	objectif	init = {_position.x, _position.y, 0};

	std::queue<objectif>	queueInit;
	queueInit.push(init);
	_paths.push(queueInit);
	while (!_paths.empty()) {
		std::queue<objectif> objs = _paths.front();
		objectif pos = objs.back();
		if (!_validPaths.empty() && pos.range > getMinValueInAllPaths(pos.range))
			break;
		_collisionMap[floor(pos.y + 0.5f)][floor(pos.x + 0.5f)] = false;
		checkStopCondition(objs, pos.x, pos.y + 1.f, pos.range + 1, type);
		checkStopCondition(objs, pos.x, pos.y - 1.f, pos.range + 1, type);
		checkStopCondition(objs, pos.x + 1.f, pos.y, pos.range + 1, type);
		checkStopCondition(objs, pos.x - 1.f, pos.y, pos.range + 1, type);
		_paths.pop();
	}
	if (!_validPaths.empty()) {
		int min = getMinValueInAllPaths(rangeMax);
		_validPaths.erase(std::remove_if(_validPaths.begin(), _validPaths.end(),
			[&](const std::queue<objectif> &o) {
				return o.back().range > min;
			}), _validPaths.end());
		if (!_validPaths.empty()) {
			auto select = Random::getRandomNumber(0, static_cast<int>(_validPaths.size() - 1));
			_positionToReach = _validPaths[select];
		}
		else
			_currentObj = NOTHING;
	}
	else
		_currentObj = NOTHING;
	_collisionMap = saveCol;
	if (_currentObj != NOTHING)
		_meshNode->switchAnimation(render::MeshNode::WALK);
}

bool engine::AI::canGoOnThisChunk(float x, float y)
{
	return _collisionMap[floor(y + 0.5f)][floor(x + 0.5f)];
}

bool engine::AI::AmISafeOnThisChunk(float x, float y)
{
	return !_explosionMap[floor(y + 0.5f)][floor(x + 0.5f)];
}
