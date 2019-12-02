/*
** EPITECH PROJECT, 2021
** indie_studio
** File Description:
** Created by simong,
*/

#include "engine/game/arena/AChunk.hpp"

engine::AChunk::AChunk(const engine::IChunk::chunkType &type,
	const irr::core::vector3df &pos)
	: _meshName("Floor"),
	_position(pos),
	_type(type),
	_breakable(false)
{
	_floor = Irrlicht::getInstance()->createMesh(_meshName, _position,\
	irr::core::vector3df(1, 1, 1));
}

engine::AChunk::~AChunk()
{}

bool engine::AChunk::isBreakable()
{
	return this->_breakable;
}

irr::core::vector3df engine::AChunk::getPosition()
{
	return this->_position;
}

engine::IChunk::chunkType engine::AChunk::getType()
{
	return this->_type;
}

std::string engine::AChunk::getMeshName()
{
	return this->_meshName;
}

void engine::AChunk::setBreakable(bool &breakable)
{
	this->_breakable = breakable;
}

void engine::AChunk::setPosition(irr::core::vector3df &position)
{
	this->_position = position;
}

void engine::AChunk::stop()
{
	_floor->getNode()->remove();
}

