/*
** EPITECH PROJECT, 2021
** indie_studio
** File Description:
** Created by simong,
*/

#include "engine/game/bomb/ABomb.hpp"

engine::ABomb::ABomb(const short &memberShipPlayer)
	: _pierceBloc(false),
	_status(UNUSED),
	_range(1),
	_meshName(""),
	_playerMemberShip(memberShipPlayer)
{}

/************ GETTER ************/

engine::IBomb::bombStatus engine::ABomb::getStatus()
{
	return _status;
}

short engine::ABomb::getRange()
{
	return _range;
}

Vector2<size_t> engine::ABomb::getPosition()
{
	return _position;
}

/************ SETTER ************/

void engine::ABomb::setStatus(engine::IBomb::bombStatus status)
{
	_status = status;
}

void engine::ABomb::setRange(short range)
{
	_range = range;
}

void engine::ABomb::setPosition(Vector2<size_t> position)
{
	_position = position;
}

engine::IBomb * engine::ABomb::clone()
{
	engine::IBomb *bomb = new ABomb(this->_playerMemberShip);

	bomb->setRange(this->_range);
	return bomb;
}

std::string engine::ABomb::getMeshName()
{
	return _meshName;
}

engine::IBomb::bombType engine::ABomb::getType()
{
	return _type;
}


std::wstring engine::ABomb::getTypeName()
{
	switch (_type) {
		case bombType::SIMPLE_BOMB:
			return L"Simple Bomb";
		case bombType::P_BOMB:
			return L"Power Bomb";
		case bombType::G_BOMB:
			return L"Giga Bomb";
		case bombType::LAVA_BOMB:
			return L"Lava Bomb";
		default:
			return L"Unknown";
	}
}

short engine::ABomb::getMemberShipPlayer()
{
	return _playerMemberShip;
}

