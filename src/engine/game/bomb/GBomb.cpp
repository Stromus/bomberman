/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "engine/game/bomb/GBomb.hpp"

engine::GBomb::GBomb(const short &memberShipPlayer)
	: ABomb(memberShipPlayer)
{
	_meshName = "GBomb";
	_pierceBloc = true;
	_range = 100;
	_type = G_BOMB;
}

engine::IBomb * engine::GBomb::clone()
{
	engine::IBomb *bomb = new GBomb(this->_playerMemberShip);

	bomb->setRange(this->_range);
	return bomb;
}
