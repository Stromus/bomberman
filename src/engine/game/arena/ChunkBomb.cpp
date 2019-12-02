/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include <time/Timer.hpp>
#include "engine/game/arena/ChunkBomb.hpp"

engine::ChunkBomb::ChunkBomb(IBomb *bomb, const irr::core::vector3df &pos)
	: AChunk(IChunk::BOMB, pos)
{
	_bomb = bomb->clone();
	_bomb->setStatus(IBomb::LAID);
	_meshBomb = Irrlicht::getInstance()->createMesh(_bomb->getMeshName(), _position,\
	irr::core::vector3df(1, 1, 1));
	_tickID = timer::Timer::getInstance()->newTick(1.0);
	_nbTotalTick = 0;
}

engine::ChunkBomb::~ChunkBomb()
{}

bool engine::ChunkBomb::isExplosed() noexcept
{
	int save = _nbTotalTick;
	_nbTotalTick += timer::Timer::getInstance()->getTick(_tickID);
	if (save > _nbTotalTick)
		_nbTotalTick = save;
	if (_bomb->getStatus() != IBomb::DESTROYED &&\
	_nbTotalTick >= 2000.0) {
		_bomb->setStatus(IBomb::DESTROYED);
		timer::Timer::getInstance()->deleteTick(_tickID);
	}
	return _bomb->getStatus() == IBomb::DESTROYED;
}

engine::IBomb *engine::ChunkBomb::getBomb() const noexcept
{
	return _bomb;
}

int engine::ChunkBomb::getTickID()
{
	return (this->_tickID);
}

void engine::ChunkBomb::stop()
{
	_meshBomb->getNode()->remove();
	AChunk::stop();
}

void engine::ChunkBomb::explosedFaster()
{
	_bomb->setStatus(IBomb::DESTROYED);
}

void engine::ChunkBomb::setNbTotalTick(int tick) noexcept
{
	this->_nbTotalTick = tick;
}

int engine::ChunkBomb::getNbTotalTick() const noexcept
{
	return (this->_nbTotalTick);
}