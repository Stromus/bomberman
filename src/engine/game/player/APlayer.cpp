/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <time/Timer.hpp>
#include "settings/Settings.hpp"
#include "engine/game/bomb/SimpleBomb.hpp"
#include "render/Irrlicht.hpp"
#include "engine/game/player/APlayer.hpp"

engine::APlayer::APlayer(const playerType &type, const short &ID, const Vector2<float> &pos,
	const std::string &meshName)
	: _type(type),
	_stats({ 1, 1, 1 }),
	_nbLife(1),
	_team(0),
	_playerID(ID),
	_checkCollision(true),
	_invertedControl(false),
	_plantBomb(false),
	_capacity(capacity::NONE),
	_bomb(new SimpleBomb(ID)),
	_pseudonyme("Player"),
	_position(pos),
	_movementSpeed(2),
	_then(Irrlicht::getInstance()->getDevice()->getTimer()->getTime()),
	_targetRotation(180),
	_rotationSpeed(360),
	_meshName(meshName)
{}

/************ SETTER ************/

void engine::APlayer::setTeam(playerType value)
{
	_type = value;
}

void engine::APlayer::setBombQuantity(short value)
{
	_stats.bombQuantity = value;
}

void engine::APlayer::setFireRange(short value)
{
	_stats.fireRange = value;
}

void engine::APlayer::setSpeed(short value)
{
	_stats.speed = value;
}

void engine::APlayer::setNbLife(short value)
{
	_nbLife = value;
}

void engine::APlayer::setTeam(short value)
{
	_team = value;
}

void engine::APlayer::setCapacity(engine::IPlayer::capacity value)
{
	_capacity = value;
}

void engine::APlayer::setBomb(engine::IBomb *bomb)
{
	_bomb = bomb;
}

void engine::APlayer::setCollision(bool collision)
{
	_checkCollision = collision;
}

void engine::APlayer::setInvertControl(bool control)
{
	_invertedControl = control;
}

void engine::APlayer::setPlantBomb(bool plant)
{
	_plantBomb = plant;
}

void engine::APlayer::setPosition(Vector2<float> pos)
{
	_position = pos;
}

void engine::APlayer::setThen(irr::u32 then)
{
	this->_then = then;
}

void engine::APlayer::setTargetRotation(int targetRotation)
{
	this->_targetRotation = targetRotation;
}

void engine::APlayer::setRotationSpeed(int rotationSpeed)
{
	this->_rotationSpeed = rotationSpeed;
}

/************ GETTER ************/


engine::IPlayer::playerType engine::APlayer::getType() const
{
	return _type;
}

std::wstring engine::APlayer::getTypeName() const
{
	switch (_type) {
		case playerType::AI:
			return L"AI";
		case playerType::PLAYER1:
			return L"Player 1";
		case playerType::PLAYER2:
			return L"Player 2";
		default:
			return L"Unknown";
	}
}

short engine::APlayer::getBombQuantity() const
{
	return _stats.bombQuantity;
}

short engine::APlayer::getFireRange() const
{
	return _stats.fireRange;
}

short engine::APlayer::getSpeed() const
{
	return _stats.speed;
}

short engine::APlayer::getNbLife() const
{
	return _nbLife;
}

short engine::APlayer::getTeam() const
{
	return _team;
}

std::wstring engine::APlayer::getTeamName() const
{
	return L"Team " + std::to_wstring(_team);
}

int engine::APlayer::getTargetRotation() const
{
	return this->_targetRotation;
}

engine::IPlayer::capacity engine::APlayer::getCapacity() const
{
	return _capacity;
}

std::wstring engine::APlayer::getCapacityName() const
{
	switch (_capacity) {
		case capacity::NONE:
			return L"None";
		case capacity::SHIELD:
			return L"Shield";
		case capacity::GHOST:
			return L"Ghost";
		case capacity::INVERT_CONTROL:
			return L"Invert control";
		case capacity::AUTOBOMB:
			return L"Auto-bomb";
		default:
			return L"Unknown";
	}
}

engine::IBomb *engine::APlayer::getBomb() const
{
	return _bomb;
}

bool engine::APlayer::isCollisionActivate() const
{
	return _checkCollision;
}

bool engine::APlayer::isControlInverted() const
{
	return _invertedControl;
}

bool engine::APlayer::isPlantBombActivate() const
{
	return _plantBomb;
}

Vector2<float> engine::APlayer::getPosition() const
{
	return _position;
}

const std::string engine::APlayer::getMeshName() const
{
	return this->_meshName;
}

engine::IPlayer::playerType engine::APlayer::getPlayerType() const
{
	return _type;
}

void engine::APlayer::putBomb()
{
	_requests.push({Controls::actions::BOMB, {_position.x + 0.5f, _position.y + 0.5f}});
}

short engine::APlayer::getPlayerID() const
{
	return _playerID;
}

std::queue<engine::IPlayer::request> &engine::APlayer::getPlayerRequests()
{
	return _requests;
}

void engine::APlayer::stop()
{
	_meshNode->getNode()->remove();
}

void engine::APlayer::update(const std::vector<std::vector<engine::IChunk *>> &map, const std::vector<engine::IPlayer *> &players)
{
	_meshNode->getNode()->setPosition({_position.x, 1, _position.y});

	auto rotation = static_cast<int>(_meshNode->getNode()->getRotation().Y);
	if (rotation != _targetRotation) {
		if (abs(_targetRotation - (rotation + 360)) < abs(_targetRotation - rotation))
			rotation += 360;
		else if (abs(_targetRotation - (rotation - 360)) < abs(_targetRotation - rotation))
			rotation -= 360;
		if (_targetRotation > rotation) {
			rotation += _rotationSpeed * 0.1;
			if (_targetRotation < rotation)
				rotation = _targetRotation;
		} else {
			rotation -= _rotationSpeed * 0.1;
			if (_targetRotation > rotation)
				rotation = _targetRotation;
		}
	}
	_meshNode->getNode()->setRotation({0, static_cast<irr::f32>(rotation % 360), 0});
	const irr::u32 now = Irrlicht::getInstance()->getDevice()->getTimer()->getTime();
	_frameDeltaTime = static_cast<irr::f32>((now - _then) / 1000.f);
	_then = now;
	updatePlayer(map, players);
}

void engine::APlayer::updatePlayer(const std::vector<std::vector<engine::IChunk *>> &map,\
const std::vector<engine::IPlayer *> &players)
{
	(void)map;
	(void)players;
}

void engine::APlayer::createRequest(Controls::actions action)
{
	if (_capacity == capacity::INVERT_CONTROL) {
		switch (action) {
		case Controls::actions::MOVE_UP:
			action = Controls::actions::MOVE_DOWN;
			break;
		case Controls::actions::MOVE_DOWN:
			action = Controls::actions::MOVE_UP;
			break;
		case Controls::actions::MOVE_LEFT:
			action = Controls::actions::MOVE_RIGHT;
			break;
		case Controls::actions::MOVE_RIGHT:
			action = Controls::actions::MOVE_LEFT;
			break;
		}
	}
	switch (action) {
	case Controls::actions::MOVE_UP:
		_requests.push({Controls::actions::MOVE_UP, {_position.x + 0.5f,\
		(_position.y + 0.5f - (_frameDeltaTime * (_stats.speed + 1)))}});
		_targetRotation = 0;
		break;
	case Controls::actions::MOVE_DOWN:
		_requests.push({Controls::actions::MOVE_DOWN, {_position.x + 0.5f,\
		_position.y + 0.5f + (_frameDeltaTime * (_stats.speed + 1))}});
		_targetRotation = 180;
		break;
	case Controls::actions::MOVE_LEFT:
		_requests.push({Controls::actions::MOVE_LEFT, {_position.x + 0.5f + (_frameDeltaTime * (_stats.speed + 1)),\
		_position.y + 0.5f}});
		_targetRotation = 270;
		break;
	case Controls::actions::MOVE_RIGHT:
		_requests.push({Controls::actions::MOVE_RIGHT, {_position.x + 0.5f - (_frameDeltaTime * (_stats.speed + 1)),\
		_position.y + 0.5f}});
		_targetRotation = 90;
		break;
	default: break;
	}
}
