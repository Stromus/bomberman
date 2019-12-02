/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "engine/game/bomb/LavaBomb.hpp"

engine::LavaBomb::LavaBomb(const short &memberShipPlayer)
	: ABomb(memberShipPlayer)
{
	_meshName = "LavaBomb";
	_pierceBloc = true;
	_type = LAVA_BOMB;
}

engine::IBomb * engine::LavaBomb::clone()
{
	engine::IBomb *bomb = new LavaBomb(this->_playerMemberShip);

	bomb->setRange(this->_range);
	return bomb;
}
