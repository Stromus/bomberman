/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "engine/game/bomb/SimpleBomb.hpp"

engine::SimpleBomb::SimpleBomb(const short &memberShipPlayer)
	: ABomb(memberShipPlayer)
{
	_meshName = "Bomb";
	_type = SIMPLE_BOMB;
}

engine::IBomb * engine::SimpleBomb::clone()
{
	engine::IBomb *bomb = new SimpleBomb(this->_playerMemberShip);

	bomb->setRange(this->_range);
	return bomb;
}
