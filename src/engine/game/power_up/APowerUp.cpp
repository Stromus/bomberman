/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "time/Timer.hpp"
#include "engine/game/power_up/APowerUp.hpp"

engine::APowerUp::APowerUp(const PowerUpType &type)
	: _invulnerability(true),
	_type(type),
	_meshName("")
{
	_tickID = timer::Timer::getInstance()->newTick(INVULNERABILITY_TIME);
}

bool engine::APowerUp::isInvulnerable() noexcept
{
	if (_invulnerability && timer::Timer::getInstance()->getTick(_tickID) >= 1)
	{
		_invulnerability = false;
		timer::Timer::getInstance()->deleteTick(_tickID);
	}
	return _invulnerability;
}

void engine::APowerUp::capacityActivation(engine::IPlayer *player)
{
	(void)player;
}

int engine::APowerUp::getTickID()
{
	return (this->_tickID);
}

engine::IPowerUp::PowerUpType engine::APowerUp::getType()
{
	return _type;
}

std::string engine::APowerUp::getMeshName()
{
	return _meshName;
}
