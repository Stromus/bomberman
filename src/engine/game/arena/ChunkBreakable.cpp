/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by khalyn,
*/

#include "engine/game/arena/ChunkBreakable.hpp"

engine::ChunkBreakable::ChunkBreakable(const irr::core::vector3df &pos)
	: AChunk(IChunk::BREAKABLE, pos)
{
	_bloc = Irrlicht::getInstance()->createMesh("BreakableCube",\
	pos, irr::core::vector3df(1, 1, 1));
}

engine::ChunkBreakable::~ChunkBreakable()
{}

void engine::ChunkBreakable::stop()
{
	_bloc->getNode()->remove();
	AChunk::stop();
}
