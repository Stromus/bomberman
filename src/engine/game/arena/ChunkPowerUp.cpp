/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "engine/game/power_up/PULavaBomb.hpp"
#include "engine/game/power_up/PUPBomb.hpp"
#include "engine/game/power_up/PUGBomb.hpp"
#include "engine/game/power_up/PUGhost.hpp"
#include "engine/game/power_up/PUInvertControl.hpp"
#include "engine/game/power_up/PUShield.hpp"
#include "engine/game/power_up/PUAutobomb.hpp"
#include "engine/game/power_up/PUQuantityDown.hpp"
#include "engine/game/power_up/PUSpeedDown.hpp"
#include "engine/game/power_up/PUFireDown.hpp"
#include "engine/game/power_up/PUSpeedUp.hpp"
#include "engine/game/power_up/PUQuantityUp.hpp"
#include "engine/game/power_up/PUFireUp.hpp"
#include "engine/game/arena/ChunkPowerUp.hpp"
#include "time/Random.hpp"
#include "render/Animator.hpp"

engine::ChunkPowerUp::ChunkPowerUp(const irr::core::vector3df &pos, engine::IPowerUp::PowerUpType powerUpType)
	: AChunk(IChunk::POWERUP, pos)
{
	switch (powerUpType) {
	case engine::IPowerUp::FIRE_UP:
		this->_powerUp = new PUFireUp();
		break;
	case engine::IPowerUp::FIRE_DOWN:
		this->_powerUp = new PUFireDown();
		break;
	case engine::IPowerUp::SPEED_UP:
		this->_powerUp = new PUSpeedUp();
		break;
	case engine::IPowerUp::SPEED_DOWN:
		this->_powerUp = new PUSpeedDown();
		break;
	case engine::IPowerUp::QUANTITY_UP:
		this->_powerUp = new PUQuantityUp();
		break;
	case engine::IPowerUp::QUANTITY_DOWN:
		this->_powerUp = new PUQuantityDown();
		break;
	case engine::IPowerUp::SHIELD:
		this->_powerUp = new PUShield();
		break;
	case engine::IPowerUp::INVERT_CONTROL:
		this->_powerUp = new PUInvertControl();
		break;
	case engine::IPowerUp::AUTOBOMB:
		this->_powerUp = new AutoBomb();
		break;
	case engine::IPowerUp::P_BOMB:
		this->_powerUp = new PUPBomb();
		break;
	case engine::IPowerUp::G_BOMB:
		this->_powerUp = new PUGBomb();
		break;
	case engine::IPowerUp::LAVA_BOMB:
		this->_powerUp = new PULavaBomb();
		break;
	case engine::IPowerUp::GHOST:
		this->_powerUp = new PUGhost();
		break;
	default:
		if (Random::getRandomNumber(0, 100) > 85)
			createSpecialPU();
		else
			createStatsPU();
		break;
	}
	_meshPowerUp = Irrlicht::getInstance()->createMesh(_powerUp->getMeshName(), _position,\
	irr::core::vector3df(1, 1, 1));
	render::Animator::addRotationAnimator(_meshPowerUp, irr::core::vector3df(0, 0.5f, 0));
}

engine::ChunkPowerUp::~ChunkPowerUp()
{}

void engine::ChunkPowerUp::createSpecialPU() noexcept
{
	if (Random::getRandomNumber(0, 100) > 70)
		createCapacityPU();
	else
		createBombPU();
}

void engine::ChunkPowerUp::createBombPU() noexcept
{
	int	nb = Random::getRandomNumber(0, 100);

	if (nb >= 0 && nb < 40)
		_powerUp = new PULavaBomb();
	else if (nb >= 40 && nb < 80)
		_powerUp = new PUPBomb();
	else
		_powerUp = new PUGBomb();
}

void engine::ChunkPowerUp::createCapacityPU() noexcept
{
	int	nb = Random::getRandomNumber(0, 100);

	if (nb >= 0 && nb < 25)
		_powerUp = new PUGhost();
	else if (nb >= 25 && nb < 50)
		_powerUp = new PUInvertControl();
	else if (nb >= 50 && nb < 75)
		_powerUp = new PUShield();
	else
		_powerUp = new AutoBomb();
}

void engine::ChunkPowerUp::createStatsPU() noexcept
{
	if (Random::getRandomNumber(0, 100) > 50)
		createBonusStats();
	else
		createMalusStats();
}

void engine::ChunkPowerUp::createBonusStats() noexcept
{
	int	nb = Random::getRandomNumber(0, 100);

	if (nb >= 0 && nb < 33)
		_powerUp = new PUFireUp();
	else if (nb >= 33 && nb < 66)
		_powerUp = new PUSpeedUp();
	else
		_powerUp = new PUQuantityUp();
}

void engine::ChunkPowerUp::createMalusStats() noexcept
{
	int	nb = Random::getRandomNumber(0, 100);

	if (nb >= 0 && nb < 33)
		_powerUp = new PUFireDown();
	else if (nb >= 33 && nb < 66)
		_powerUp = new PUSpeedDown();
	else
		_powerUp = new PUQuantityDown();
}

engine::IPowerUp *engine::ChunkPowerUp::getPowerUp() noexcept
{
	return _powerUp;
}

void engine::ChunkPowerUp::stop()
{
	_meshPowerUp->getNode()->remove();
	AChunk::stop();
}
