/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "engine/game/bomb/PBomb.hpp"

engine::PBomb::PBomb(const short &memberShipPlayer)
	: ABomb(memberShipPlayer)
{
	_meshName = "PBomb";
	_range = 100;
	_type = P_BOMB;
}

engine::IBomb * engine::PBomb::clone()
{
	engine::IBomb *bomb = new PBomb(this->_playerMemberShip);

	bomb->setRange(this->_range);
	return bomb;
}
